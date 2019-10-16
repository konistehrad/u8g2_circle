//
// kernel.h
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
#pragma once

#define U8X8_USE_PINS
#define U8X8_WITH_USER_PTR

#include <circle/types.h>
#include <circle/memory.h>
#include <circle/actled.h>
#include <circle/koptions.h>
#include <circle/devicenameservice.h>
#include <circle/cputhrottle.h>
#include <circle/exceptionhandler.h>
#include <circle/interrupt.h>
#include <circle/screen.h>
#include <circle/serial.h>
#include <circle/timer.h>
#include <circle/logger.h>
#include <circle/input/console.h>
#include <circle/i2cmaster.h>
#include <circle/sched/scheduler.h>
#include <circle/sched/synchronizationevent.h>
#include <u8g2/u8g2.h>
#include <u8g2/U8g2lib.h>

enum TShutdownMode
{
  ShutdownNone,
  ShutdownHalt,
  ShutdownReboot
};

class CKernel
{
public:
  CKernel (void);
  ~CKernel (void);

  boolean Initialize (void);

  TShutdownMode Run (void);

private:
  static void TimerHandler (TKernelTimerHandle hTimer, void *pParam, void *pContext);
  static void LeftInterruptHandler (void *pParam);
  static void RightInterruptHandler (void *pParam);

  void DieWithBlinkPattern(uint8_t);

  CMemorySystem   m_Memory;
  CActLED     m_ActLED;
  CKernelOptions    m_Options;
  CDeviceNameService  m_DeviceNameService;
  CCPUThrottle    m_CPUThrottle;
  CExceptionHandler m_ExceptionHandler;
  CInterruptSystem  m_Interrupt;
  CScreenDevice   m_Screen;
  CSerialDevice   m_Serial;
  CTimer      m_Timer;
  CLogger     m_Logger;
  CConsole    m_Console;
  CI2CMaster  m_I2CMaster;

  CScheduler    m_Scheduler;
  CSynchronizationEvent m_Event;
  
  u8g2_t m_u8g2;
  // This is the HAL that will provide the necessary
  // objects to the u8g2 bindings
  CircleU8x8Hal m_u8hal;
  CString m_formatter;
};

