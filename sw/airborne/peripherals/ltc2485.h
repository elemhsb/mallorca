/*
 * Copyright (C) 2013 ELEMHSB
 *
 * This file is part of paparazzi.
 *
 * paparazzi is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * paparazzi is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with paparazzi; see the file COPYING.  If not, write to
 * the Free Software Foundation, 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 */

/* driver for the ADC LTC2485 (24 bits I2C) Linear */

#ifndef LTC_2485_H
#define LTC_2485_H

#include "std.h"
#include "mcu_periph/i2c.h"


/* I2C slave address */
#ifndef LTC2485_I2C_ADDR
#define LTC2485_I2C_ADDR 0x2A           // slave address byte (I2c address(7bits) + R/W @ 0)
#endif

/* I2C conf register */
#define LTC2485_POINTER_CONV_REG    0x00 // access to the Conversion register (16bits)
#define LTC2485_POINTER_CONFIG_REG  0x01 // access to the Configuration register (16bits)

/* LTC2485 default conf */
#ifndef LTC2485_IN
#define LTC2485_IN 0x00 // ADC source VIN
#endif
#ifndef LTC2485_REJECT
#define LTC2485_REJECT 0x00 // Reject frequency 50/60
#endif
#ifndef LTC2485_MODE
#define LTC2485_MODE 0x00 // Sample Mode SLOW, autozero
#endif

#define LTC2485_CONFIG (LTC2485_IN|LTC2485_REJECT|LTC2485_MODE)

/* Default I2C device */
#ifndef LTC2485_I2C_DEV
#define LTC2485_I2C_DEV i2c1
#endif

struct ltc2485_periph {
  struct i2c_transaction trans;
  uint8_t i2c_addr;
  bool_t config_done;
  bool_t data_available;
};

#if USE_LTC2485
extern struct ltc2485_periph ltc2485;
#warning "############ ltc2485.h"
#endif

extern void ltc2485_init(void);
extern void ltc2485_read(struct ltc2485_periph * p);

// Generic Event Macro
#define _Ltc2485Event(_p) {\
  if (!_p.config_done) { \
    if (_p.trans.status == I2CTransSuccess) { _p.config_done = TRUE; _p.trans.status = I2CTransDone; } \
    if (_p.trans.status == I2CTransFailed) { _p.trans.status = I2CTransDone; } \
  } else { \
    if (_p.trans.status == I2CTransSuccess) { _p.data_available = TRUE; _p.trans.status = I2CTransDone; } \
    if (_p.trans.status == I2CTransFailed) { _p.trans.status = I2CTransDone; } \
  } \
}

#if USE_LTC2485
#define Ltc2485Event() _Ltc2485Event(ltc2485)
#else
#define Ltc2485Event() {}
#endif


// Get value macro
// @param ltc2485 periph
#define Ltc2485GetValue(_p) ((int32_t)(((int32_t)_p.trans.buf[0]<<24)|(int32_t)_p.trans.buf[1]<<16)(int32_t)_p.trans.buf[2]<<8)|_p.trans.buf[3]))

#endif // LTC_2485_H
