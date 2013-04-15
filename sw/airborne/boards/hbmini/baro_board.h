
#ifndef BOARDS_BOOZ_BARO_H
#define BOARDS_BOOZ_BARO_H

#if ! HBminiBMP

#include "std.h"

#include "subsystems/sensors/baro.h"
#include "mcu_periph/adc.h"
#include "mcu_periph/dac.h"
#include "mcu_periph/uart.h"
#include "messages.h"
#include "subsystems/datalink/downlink.h"


/* struct BaroBoard {
  uint16_t offset;
  uint16_t value_filtered;
  bool_t   data_available;
}; */

extern struct BaroBoard baro_board;

extern void baro_board_calibrate(void);

#define BaroEvent(_b_abs_handler, _b_diff_handler) {  \
    if (baro_board.data_available) {      \
      _b_abs_handler();         \
      baro_board.data_available = FALSE;    \
    }             \
  }

static inline void baro_board_SetOffset(uint16_t _o) {
  baro_board.offset = _o;
  DACSet(_o);
}

#else // HBminiBMP

#define BaroEvent(_b_abs_handler, _b_diff_handler) {  \
    if (baro_board.data_available) {      \
      _b_abs_handler();         \
      baro_board.data_available = FALSE;    \
    }             \
  }

// #ifndef BARO_BMP_H
// #define BARO_BMP_H

#include "std.h"
// neu
//#include "subsystems/sensors/baro.h"

#define BMP085_EEPROM_AC1   0xAA
#define BMP085_EEPROM_AC2   0xAC
#define BMP085_EEPROM_AC3   0xAE
#define BMP085_EEPROM_AC4   0xB0
#define BMP085_EEPROM_AC5   0xB2
#define BMP085_EEPROM_AC6   0xB4
#define BMP085_EEPROM_B1    0xB6
#define BMP085_EEPROM_B2    0xB8
#define BMP085_EEPROM_MB    0xBA
#define BMP085_EEPROM_MC    0xBC
#define BMP085_EEPROM_MD    0xBE

#define BMP085_CTRL_REG     0xF4

#define BMP085_START_TEMP   0x2E
#define BMP085_START_P0     0x34
#define BMP085_START_P1     0x74
#define BMP085_START_P2     0xB4
#define BMP085_START_P3     0xF4

#define BMP085_DAT_MSB      0xF6
#define BMP085_DAT_LSB      0xF7
#define BMP085_DAT_XLSB     0xF8

#define BARO_BMP_UNINIT       0
#define BARO_BMP_IDLE         1
#define BARO_BMP_START_TEMP   2
#define BARO_BMP_READ_TEMP    3
#define BARO_BMP_START_PRESS  4
#define BARO_BMP_READ_PRESS   5

#define BARO_BMP_DT 0.05
extern bool_t baro_bmp_enabled;
extern float baro_bmp_r;
extern float baro_bmp_sigma2;

extern uint8_t  baro_bmp_status;
extern uint32_t baro_bmp_pressure;
extern uint16_t baro_bmp_temperature;
extern int32_t  baro_bmp_altitude;
extern int32_t baro_bmp;
extern int32_t baro_bmp_offset;

struct BaroBoard {
  uint16_t offset;
  uint16_t value_filtered;
  bool_t   data_available;
};
extern struct BaroBoard baro_board;

void baro_bmp_init(void);
void baro_bmp_periodic(void);
void baro_bmp_event(void);

#endif /*HBminiBMP */
#endif /* BOARDS_BOOZ_BARO_H */
