#ifndef DISP_H
#define DISP_H

#include "stdint.h"

extern void disp_init(void);
extern void disp_clean(void);
extern void disp_tick(void);
extern void disp_set(int col, int row, uint8_t val);
extern void disp_set_noupdate(int col, int row, uint8_t val);
extern void disp_update_rows(void);
extern uint8_t disp_get(int col, int row);

extern void disp_hw_init(void);
extern void disp_hw_update_row(int num_row, const uint8_t *data);

#endif

