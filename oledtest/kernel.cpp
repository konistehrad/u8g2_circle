//
// kernel.cpp
//
// OLED Test - Minimal bindings for HW I2C LED usage via u8g2
// Copyright (C) 2014-2019  C. Kreyling <konistehrad@gmail.com>
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
// 
#include "kernel.h"

static const char FromKernel[] = "kernel";

CKernel::CKernel (void)
: m_Screen (m_Options.GetWidth (), m_Options.GetHeight ()),
#if RASPPI >= 4 && AARCH == 64
  m_Serial (&m_Interrupt, FALSE),   // FIQ not supported
#else
  m_Serial (&m_Interrupt, TRUE),
#endif
  m_Timer (&m_Interrupt),
  m_Logger (m_Options.GetLogLevel(), &m_Timer),
  m_Console (&m_Serial),
  m_I2CMaster (CMachineInfo::Get()->GetDevice(DeviceI2CMaster))
{
}

CKernel::~CKernel (void)
{
}

void CKernel::DieWithBlinkPattern(uint8_t count)
{
  while(1)
  {
    m_ActLED.Blink(count, 200, 200);
    CTimer::SimpleMsDelay(2000);
  }
}

boolean CKernel::Initialize (void)
{
  boolean bOK = TRUE;

  if (bOK)
  {
    bOK = m_Screen.Initialize ();
  }
  if(!bOK) this->DieWithBlinkPattern(1);

  if (bOK)
  {
    bOK = m_Serial.Initialize (115200);
  }
  if(!bOK) this->DieWithBlinkPattern(2);
  
  if (bOK)
  {
    CDevice *pTarget = m_DeviceNameService.GetDevice(m_Options.GetLogDevice (), FALSE);
    if (pTarget == 0)
    {
      pTarget = &m_Screen;
    }

    bOK = m_Logger.Initialize (pTarget);
  }
  if(!bOK) this->DieWithBlinkPattern(3);

  if (bOK)
  {
    bOK = m_Interrupt.Initialize ();
  }
  if(!bOK) this->DieWithBlinkPattern(4);

  if (bOK)
  {
    bOK = m_Timer.Initialize ();
  }
  if(!bOK) this->DieWithBlinkPattern(5);

  if (bOK)
  {
    bOK = m_Console.Initialize ();
  }
  if(!bOK) this->DieWithBlinkPattern(6);

  if (bOK)
  {
    bOK = m_I2CMaster.Initialize ();
  }
  if(!bOK) this->DieWithBlinkPattern(7);

  return bOK;
}

TShutdownMode CKernel::Run (void)
{
  m_Logger.Write(FromKernel, LogNotice, "Compile time: " __DATE__ " " __TIME__);

  // REQUIRED STEP: initialize u8g2<->circle HAL
  m_u8hal.i2cMaster = &m_I2CMaster;
  m_u8hal.timer = &m_Timer;
  m_u8hal.logger = &m_Logger;
  
  // REQUIRED STEP: assign HAL to the user pointer
  u8g2_SetUserPtr(&m_u8g2, &m_u8hal); 

  // REQUIRED STEP: set up Circle-specific callbacks
  u8g2_Setup_ssd1306_i2c_128x64_noname_f(&m_u8g2, U8G2_R0, u8x8_byte_arm_circle_hw_i2c, u8x8_arm_circle_gpio_and_delay);

  // Now, use all your favorite general u8g2_* bindings!
  u8g2_InitDisplay(&m_u8g2);
  u8g2_SetPowerSave(&m_u8g2, 0);
  u8g2_ClearDisplay(&m_u8g2);
  m_Logger.Write(FromKernel, LogNotice, "u8 init complete!");

  boolean heartbeat = false;
  while(1) {
    uint8_t drawWidth = 0;
    uint8_t lineY = 0;

    heartbeat = !heartbeat;
    u8g2_ClearBuffer(&m_u8g2);
    u8g2_SetFont(&m_u8g2, u8g2_font_helvR10_tr);

    lineY = 15;
    drawWidth = u8g2_DrawStr(&m_u8g2, 5, lineY, "U8G2 on Circle");

    u8g2_SetFont(&m_u8g2, u8g2_font_helvR08_tr);
    lineY = 25;
    m_formatter.Format("%d Mhz", m_CPUThrottle.GetClockRate() / 1000000);
    drawWidth = u8g2_DrawStr(&m_u8g2, 5, lineY, "Clock speed: ");
    drawWidth += u8g2_DrawStr(&m_u8g2, 5 + drawWidth, lineY, m_formatter);

    lineY = 35;
    m_formatter.Format("%d C", m_CPUThrottle.GetTemperature());
    drawWidth = u8g2_DrawStr(&m_u8g2, 5, lineY, "Temperature: ");
    drawWidth += u8g2_DrawStr(&m_u8g2, 5 + drawWidth, lineY, m_formatter);
    
    lineY = 45;
    m_formatter.Format("%d seconds", CTimer::Get()->GetUptime());
    drawWidth = u8g2_DrawStr(&m_u8g2, 5, lineY, "Uptime: ");
    drawWidth += u8g2_DrawStr(&m_u8g2, 5 + drawWidth, lineY, m_formatter);

    if(heartbeat)
    {
      u8g2_DrawBox(&m_u8g2, m_u8g2.width - 5, m_u8g2.height - 5, 2, 2);
    }
    u8g2_SendBuffer(&m_u8g2);
    
    m_Scheduler.Yield();
  }

  return ShutdownHalt;
}
