/*
  U8g2lib.h

  Circle Bindings for Universal 8bit Graphics Library (https://github.com/konistehrad/u8g2_circle)

  Copyright (c) 2019, konistehrad@gmail.com
  All rights reserved.

  Redistribution and use in source and binary forms, with or without modification, 
  are permitted provided that the following conditions are met:

  * Redistributions of source code must retain the above copyright notice, this list 
    of conditions and the following disclaimer.
    
  * Redistributions in binary form must reproduce the above copyright notice, this 
    list of conditions and the following disclaimer in the documentation and/or other 
    materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND 
  CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
  NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  
*/

#ifndef _U8G2LIB_CIRCLE_H
#define _U8G2LIB_CIRCLE_H


#define U8X8_USE_PINS
#define U8X8_WITH_USER_PTR

#include <circle/i2cmaster.h>
#include <circle/spimaster.h>
#include <circle/gpiomanager.h>
#include <circle/gpiopin.h>
#include <circle/timer.h>
#include <circle/logger.h>

#include "u8g2.h"
#include "u8x8.h"

struct CircleU8x8Hal
{
  CI2CMaster* i2cMaster;

  CSPIMaster* spiMaster;

  CGPIOManager* pinManager;
  CGPIOPin* pins[U8X8_PIN_CNT] = {NULL};

  CTimer* timer;
  CLogger* logger;

  CGPIOPin* GetPin(u8x8_t *u8x8, unsigned i) 
  { 
    // check out-of-range
    if(i >= U8X8_PIN_CNT) return NULL;
    // check empty pin bank
    auto idx = u8x8->pins[i];
    if(idx == U8X8_PIN_NONE) return NULL;
    if(idx >= U8X8_PIN_CNT) return NULL;
    return pins[idx];
  }
  void TryWrite(u8x8_t *u8x8, unsigned i, unsigned value)
  {
    auto pin = GetPin(u8x8, i);
    if(pin != NULL) pin->Write(value);
  }
};

extern "C" uint8_t u8x8_arm_circle_gpio_and_delay(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);
extern "C" uint8_t u8x8_byte_arm_circle_hw_i2c(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);

#endif
