#include <stdint.h>
#include <string.h>

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/i2c.h>
#include <libopencm3/stm32/syscfg.h>

#include "hw_defs.h"
#include "disp.h"
#include "ticker.h"

#define IS31_I2C_ADDR 0x50

/*
 * pre-computed LUT for gamma 1.8 and
 * 32 values
 */
static const uint8_t gamma18_lut[DISP_COLOR_DEPTH] = {
		0, 1, 2, 4, 6, 10, 13, 18,
		22, 28, 33, 39, 46, 53, 61, 69,
		78, 86, 96, 106, 116, 126, 138, 149,
		161, 173, 186, 199, 212, 226, 240, 255
};

static uint8_t gamma_lookup(uint8_t val)
{
	if (val > 31)
		val = 31;

	return gamma18_lut[val];
}

static void is31_unlock_cr(void)
{
	uint8_t cmd[2] = { 0xFE, 0xC5 };
	i2c_transfer7(I2C2, IS31_I2C_ADDR, cmd, 2, NULL, 0);
}

static void is31_select_pg(int pg)
{
	uint8_t cmd[2] = { 0xFD, pg };
	is31_unlock_cr();
	i2c_transfer7(I2C2, IS31_I2C_ADDR, cmd, 2, NULL, 0);
}

static void is31_write_pg_reg(uint8_t reg, uint8_t val)
{
	uint8_t cmd[2] = { reg, val };
	i2c_transfer7(I2C2, IS31_I2C_ADDR, cmd, 2, NULL, 0);
}

static uint8_t is31_read_pg_reg(uint8_t reg)
{
	uint8_t cmd[1] = {reg};
	uint8_t val;

	i2c_transfer7(I2C2, IS31_I2C_ADDR, cmd, 1, &val, 1);
	return val;
}

static void is31_init(void)
{
	/* enable the driver */
	is31_select_pg(3);
	/* reset */
	is31_read_pg_reg(0x11);
	/* enable chip */
	is31_write_pg_reg(0x00, 0x01);
	/* set current to maximum */
	is31_write_pg_reg(0x01, 0xff);
	/* set pull resistors */
	is31_write_pg_reg(0x0f, 0x5);
	is31_write_pg_reg(0x10, 0x5);

	/* enable LEDs on SW1-SW8 */
	is31_select_pg(0);
	for (int reg = 0; reg < 0x10; ++reg)
		is31_write_pg_reg(reg, 0x55);

#ifdef LED_TEST
	/* configure PWM 100% */
	is31_select_pg(1);
	for (int reg = 0x00; reg <= 0x7e; reg += 2)
		is31_write_pg_reg(reg, 0xff);

	ticker_msleep(1000);
#endif

	/* switch off all LEDs again */
	is31_select_pg(1);
	for (int reg = 0x00; reg <= 0x7e; reg += 2)
		is31_write_pg_reg(reg, 0x00);
}

void disp_hw_init(void)
{
	/* enable clocks for the GPIOs connected to the display */
	rcc_periph_clock_enable(DISP_GPIOS_RCC);
	/* enable clocks for the I2C2 module */
	rcc_periph_clock_enable(DISP_I2C_RCC);

	/*
	 * setup the GPIOs for the Output-Enable pins of the
	 * display driver
	 */
	gpio_mode_setup(DISP_GPIOP_SDB,
		GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, DISP_GPIO_SDB);

	/* setup GPIOs for the I2C pins */
	gpio_mode_setup(DISP_GPIOP_I2C, GPIO_MODE_AF,
			GPIO_PUPD_NONE, DISP_GPIO_SDA | DISP_GPIO_SCL);
	gpio_set_af(DISP_GPIOP_I2C, GPIO_AF5,
			DISP_GPIO_SDA | DISP_GPIO_SCL);

	/* configure the I2C module */
	i2c_reset(I2C2);
	i2c_peripheral_disable(I2C2);
	i2c_enable_analog_filter(I2C2);
	i2c_set_digital_filter(I2C2, 0);
	i2c_set_speed(I2C2, i2c_speed_fmp_1m, rcc_apb1_frequency / 1e6);
	/* enable "fast mode plus" drive capabilities on I2C2 pads */
	SYSCFG_CFGR1 |= SYSCFG_CFGR1_I2C2_FMP;
	i2c_enable_stretching(I2C2);
	i2c_set_7bit_addr_mode(I2C2);
	i2c_peripheral_enable(I2C2);

	/* enable the driver */
	gpio_set(DISP_GPIOP_SDB, DISP_GPIO_SDB);

	is31_init();
}

void disp_hw_update_row(int row, const uint8_t *data)
{
	is31_select_pg(1);
	/* set the PWM value */
	for (int col=0; col < DISP_COLS_NUM; ++col) {
		is31_write_pg_reg((DISP_COLS_NUM-col-1) * 16
				+ (DISP_ROWS_NUM - row - 1) * 2,
				gamma_lookup(data[col]));
	}
}
