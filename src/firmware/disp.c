#include <stdint.h>
#include <string.h>

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

#include "hw_defs.h"
#include "disp.h"

static uint8_t disp_state[DISP_ROWS_NUM][DISP_COLS_NUM];

void disp_init(void)
{
	/* configure the LED matrix driver */
	disp_hw_init();

	disp_clean();
}

static void disp_row_update(int row_num)
{
	disp_hw_update_row(row_num, &disp_state[row_num][0]);
}

void disp_update_rows(void)
{
	for (int row = 0; row < DISP_ROWS_NUM; row++)
		disp_row_update(row);
}

void disp_clean(void)
{
	memset(disp_state, 0, sizeof(disp_state));
	disp_update_rows();
}

void disp_set_noupdate(int col, int row, uint8_t val)
{
	disp_state[row][col] = val;
}

void disp_set(int col, int row, uint8_t val)
{
	disp_set_noupdate(col, row, val);
	disp_row_update(row);
}

uint8_t disp_get(int col, int row)
{
	if (col < 0 || col >= DISP_COLS_NUM)
		return 0;
	if (row < 0 || row >= DISP_ROWS_NUM)
		return 0;

	return disp_state[row][col];
}
