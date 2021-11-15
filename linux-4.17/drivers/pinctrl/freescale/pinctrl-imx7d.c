/*
 * Freescale imx7d pinctrl driver
 *
 * Author: Anson Huang <Anson.Huang@freescale.com>
 * Copyright (C) 2014-2015 Freescale Semiconductor, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/err.h>
#include <linux/init.h>
#include <linux/io.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/pinctrl/pinctrl.h>

#include "pinctrl-imx.h"

enum imx7d_pads {
	MX7D_PAD_RESERVE0 = 0,
	MX7D_PAD_RESERVE1 = 1,
	MX7D_PAD_RESERVE2 = 2,
	MX7D_PAD_RESERVE3 = 3,
	MX7D_PAD_RESERVE4 = 4,
	MX7D_PAD_GPIO1_IO08 = 5,
	MX7D_PAD_GPIO1_IO09 = 6,
	MX7D_PAD_GPIO1_IO10 = 7,
	MX7D_PAD_GPIO1_IO11 = 8,
	MX7D_PAD_GPIO1_IO12 = 9,
	MX7D_PAD_GPIO1_IO13 = 10,
	MX7D_PAD_GPIO1_IO14 = 11,
	MX7D_PAD_GPIO1_IO15 = 12,
	MX7D_PAD_EPDC_DATA00 = 13,
	MX7D_PAD_EPDC_DATA01 = 14,
	MX7D_PAD_EPDC_DATA02 = 15,
	MX7D_PAD_EPDC_DATA03 = 16,
	MX7D_PAD_EPDC_DATA04 = 17,
	MX7D_PAD_EPDC_DATA05 = 18,
	MX7D_PAD_EPDC_DATA06 = 19,
	MX7D_PAD_EPDC_DATA07 = 20,
	MX7D_PAD_EPDC_DATA08 = 21,
	MX7D_PAD_EPDC_DATA09 = 22,
	MX7D_PAD_EPDC_DATA10 = 23,
	MX7D_PAD_EPDC_DATA11 = 24,
	MX7D_PAD_EPDC_DATA12 = 25,
	MX7D_PAD_EPDC_DATA13 = 26,
	MX7D_PAD_EPDC_DATA14 = 27,
	MX7D_PAD_EPDC_DATA15 = 28,
	MX7D_PAD_EPDC_SDCLK = 29,
	MX7D_PAD_EPDC_SDLE = 30,
	MX7D_PAD_EPDC_SDOE = 31,
	MX7D_PAD_EPDC_SDSHR = 32,
	MX7D_PAD_EPDC_SDCE0 = 33,
	MX7D_PAD_EPDC_SDCE1 = 34,
	MX7D_PAD_EPDC_SDCE2 = 35,
	MX7D_PAD_EPDC_SDCE3 = 36,
	MX7D_PAD_EPDC_GDCLK = 37,
	MX7D_PAD_EPDC_GDOE = 38,
	MX7D_PAD_EPDC_GDRL = 39,
	MX7D_PAD_EPDC_GDSP = 40,
	MX7D_PAD_EPDC_BDR0 = 41,
	MX7D_PAD_EPDC_BDR1 = 42,
	MX7D_PAD_EPDC_PWR_COM = 43,
	MX7D_PAD_EPDC_PWR_STAT = 44,
	MX7D_PAD_LCD_CLK = 45,
	MX7D_PAD_LCD_ENABLE = 46,
	MX7D_PAD_LCD_HSYNC = 47,
	MX7D_PAD_LCD_VSYNC = 48,
	MX7D_PAD_LCD_RESET = 49,
	MX7D_PAD_LCD_DATA00 = 50,
	MX7D_PAD_LCD_DATA01 = 51,
	MX7D_PAD_LCD_DATA02 = 52,
	MX7D_PAD_LCD_DATA03 = 53,
	MX7D_PAD_LCD_DATA04 = 54,
	MX7D_PAD_LCD_DATA05 = 55,
	MX7D_PAD_LCD_DATA06 = 56,
	MX7D_PAD_LCD_DATA07 = 57,
	MX7D_PAD_LCD_DATA08 = 58,
	MX7D_PAD_LCD_DATA09 = 59,
	MX7D_PAD_LCD_DATA10 = 60,
	MX7D_PAD_LCD_DATA11 = 61,
	MX7D_PAD_LCD_DATA12 = 62,
	MX7D_PAD_LCD_DATA13 = 63,
	MX7D_PAD_LCD_DATA14 = 64,
	MX7D_PAD_LCD_DATA15 = 65,
	MX7D_PAD_LCD_DATA16 = 66,
	MX7D_PAD_LCD_DATA17 = 67,
	MX7D_PAD_LCD_DATA18 = 68,
	MX7D_PAD_LCD_DATA19 = 69,
	MX7D_PAD_LCD_DATA20 = 70,
	MX7D_PAD_LCD_DATA21 = 71,
	MX7D_PAD_LCD_DATA22 = 72,
	MX7D_PAD_LCD_DATA23 = 73,
	MX7D_PAD_UART1_RX_DATA = 74,
	MX7D_PAD_UART1_TX_DATA = 75,
	MX7D_PAD_UART2_RX_DATA = 76,
	MX7D_PAD_UART2_TX_DATA = 77,
	MX7D_PAD_UART3_RX_DATA = 78,
	MX7D_PAD_UART3_TX_DATA = 79,
	MX7D_PAD_UART3_RTS_B = 80,
	MX7D_PAD_UART3_CTS_B = 81,
	MX7D_PAD_I2C1_SCL = 82,
	MX7D_PAD_I2C1_SDA = 83,
	MX7D_PAD_I2C2_SCL = 84,
	MX7D_PAD_I2C2_SDA = 85,
	MX7D_PAD_I2C3_SCL = 86,
	MX7D_PAD_I2C3_SDA = 87,
	MX7D_PAD_I2C4_SCL = 88,
	MX7D_PAD_I2C4_SDA = 89,
	MX7D_PAD_ECSPI1_SCLK = 90,
	MX7D_PAD_ECSPI1_MOSI = 91,
	MX7D_PAD_ECSPI1_MISO = 92,
	MX7D_PAD_ECSPI1_SS0 = 93,
	MX7D_PAD_ECSPI2_SCLK = 94,
	MX7D_PAD_ECSPI2_MOSI = 95,
	MX7D_PAD_ECSPI2_MISO = 96,
	MX7D_PAD_ECSPI2_SS0 = 97,
	MX7D_PAD_SD1_CD_B = 98,
	MX7D_PAD_SD1_WP = 99,
	MX7D_PAD_SD1_RESET_B = 100,
	MX7D_PAD_SD1_CLK = 101,
	MX7D_PAD_SD1_CMD = 102,
	MX7D_PAD_SD1_DATA0 = 103,
	MX7D_PAD_SD1_DATA1 = 104,
	MX7D_PAD_SD1_DATA2 = 105,
	MX7D_PAD_SD1_DATA3 = 106,
	MX7D_PAD_SD2_CD_B = 107,
	MX7D_PAD_SD2_WP = 108,
	MX7D_PAD_SD2_RESET_B = 109,
	MX7D_PAD_SD2_CLK = 110,
	MX7D_PAD_SD2_CMD = 111,
	MX7D_PAD_SD2_DATA0 = 112,
	MX7D_PAD_SD2_DATA1 = 113,
	MX7D_PAD_SD2_DATA2 = 114,
	MX7D_PAD_SD2_DATA3 = 115,
	MX7D_PAD_SD3_CLK = 116,
	MX7D_PAD_SD3_CMD = 117,
	MX7D_PAD_SD3_DATA0 = 118,
	MX7D_PAD_SD3_DATA1 = 119,
	MX7D_PAD_SD3_DATA2 = 120,
	MX7D_PAD_SD3_DATA3 = 121,
	MX7D_PAD_SD3_DATA4 = 122,
	MX7D_PAD_SD3_DATA5 = 123,
	MX7D_PAD_SD3_DATA6 = 124,
	MX7D_PAD_SD3_DATA7 = 125,
	MX7D_PAD_SD3_STROBE = 126,
	MX7D_PAD_SD3_RESET_B = 127,
	MX7D_PAD_SAI1_RX_DATA = 128,
	MX7D_PAD_SAI1_TX_BCLK = 129,
	MX7D_PAD_SAI1_TX_SYNC = 130,
	MX7D_PAD_SAI1_TX_DATA = 131,
	MX7D_PAD_SAI1_RX_SYNC = 132,
	MX7D_PAD_SAI1_RX_BCLK = 133,
	MX7D_PAD_SAI1_MCLK = 134,
	MX7D_PAD_SAI2_TX_SYNC = 135,
	MX7D_PAD_SAI2_TX_BCLK = 136,
	MX7D_PAD_SAI2_RX_DATA = 137,
	MX7D_PAD_SAI2_TX_DATA = 138,
	MX7D_PAD_ENET1_RGMII_RD0 = 139,
	MX7D_PAD_ENET1_RGMII_RD1 = 140,
	MX7D_PAD_ENET1_RGMII_RD2 = 141,
	MX7D_PAD_ENET1_RGMII_RD3 = 142,
	MX7D_PAD_ENET1_RGMII_RX_CTL = 143,
	MX7D_PAD_ENET1_RGMII_RXC = 144,
	MX7D_PAD_ENET1_RGMII_TD0 = 145,
	MX7D_PAD_ENET1_RGMII_TD1 = 146,
	MX7D_PAD_ENET1_RGMII_TD2 = 147,
	MX7D_PAD_ENET1_RGMII_TD3 = 148,
	MX7D_PAD_ENET1_RGMII_TX_CTL = 149,
	MX7D_PAD_ENET1_RGMII_TXC = 150,
	MX7D_PAD_ENET1_TX_CLK = 151,
	MX7D_PAD_ENET1_RX_CLK = 152,
	MX7D_PAD_ENET1_CRS = 153,
	MX7D_PAD_ENET1_COL = 154,
};

enum imx7d_lpsr_pads {
	MX7D_PAD_GPIO1_IO00 = 0,
	MX7D_PAD_GPIO1_IO01 = 1,
	MX7D_PAD_GPIO1_IO02 = 2,
	MX7D_PAD_GPIO1_IO03 = 3,
	MX7D_PAD_GPIO1_IO04 = 4,
	MX7D_PAD_GPIO1_IO05 = 5,
	MX7D_PAD_GPIO1_IO06 = 6,
	MX7D_PAD_GPIO1_IO07 = 7,
};

/* Pad names for the pinmux subsystem */
static const struct pinctrl_pin_desc imx7d_pinctrl_pads[] = {
	IMX_PINCTRL_PIN(MX7D_PAD_RESERVE0),
	IMX_PINCTRL_PIN(MX7D_PAD_RESERVE1),
	IMX_PINCTRL_PIN(MX7D_PAD_RESERVE2),
	IMX_PINCTRL_PIN(MX7D_PAD_RESERVE3),
	IMX_PINCTRL_PIN(MX7D_PAD_RESERVE4),
	IMX_PINCTRL_PIN(MX7D_PAD_GPIO1_IO08),
	IMX_PINCTRL_PIN(MX7D_PAD_GPIO1_IO09),
	IMX_PINCTRL_PIN(MX7D_PAD_GPIO1_IO10),
	IMX_PINCTRL_PIN(MX7D_PAD_GPIO1_IO11),
	IMX_PINCTRL_PIN(MX7D_PAD_GPIO1_IO12),
	IMX_PINCTRL_PIN(MX7D_PAD_GPIO1_IO13),
	IMX_PINCTRL_PIN(MX7D_PAD_GPIO1_IO14),
	IMX_PINCTRL_PIN(MX7D_PAD_GPIO1_IO15),
	IMX_PINCTRL_PIN(MX7D_PAD_EPDC_DATA00),
	IMX_PINCTRL_PIN(MX7D_PAD_EPDC_DATA01),
	IMX_PINCTRL_PIN(MX7D_PAD_EPDC_DATA02),
	IMX_PINCTRL_PIN(MX7D_PAD_EPDC_DATA03),
	IMX_PINCTRL_PIN(MX7D_PAD_EPDC_DATA04),
	IMX_PINCTRL_PIN(MX7D_PAD_EPDC_DATA05),
	IMX_PINCTRL_PIN(MX7D_PAD_EPDC_DATA06),
	IMX_PINCTRL_PIN(MX7D_PAD_EPDC_DATA07),
	IMX_PINCTRL_PIN(MX7D_PAD_EPDC_DATA08),
	IMX_PINCTRL_PIN(MX7D_PAD_EPDC_DATA09),
	IMX_PINCTRL_PIN(MX7D_PAD_EPDC_DATA10),
	IMX_PINCTRL_PIN(MX7D_PAD_EPDC_DATA11),
	IMX_PINCTRL_PIN(MX7D_PAD_EPDC_DATA12),
	IMX_PINCTRL_PIN(MX7D_PAD_EPDC_DATA13),
	IMX_PINCTRL_PIN(MX7D_PAD_EPDC_DATA14),
	IMX_PINCTRL_PIN(MX7D_PAD_EPDC_DATA15),
	IMX_PINCTRL_PIN(MX7D_PAD_EPDC_SDCLK),
	IMX_PINCTRL_PIN(MX7D_PAD_EPDC_SDLE),
	IMX_PINCTRL_PIN(MX7D_PAD_EPDC_SDOE),
	IMX_PINCTRL_PIN(MX7D_PAD_EPDC_SDSHR),
	IMX_PINCTRL_PIN(MX7D_PAD_EPDC_SDCE0),
	IMX_PINCTRL_PIN(MX7D_PAD_EPDC_SDCE1),
	IMX_PINCTRL_PIN(MX7D_PAD_EPDC_SDCE2),
	IMX_PINCTRL_PIN(MX7D_PAD_EPDC_SDCE3),
	IMX_PINCTRL_PIN(MX7D_PAD_EPDC_GDCLK),
	IMX_PINCTRL_PIN(MX7D_PAD_EPDC_GDOE),
	IMX_PINCTRL_PIN(MX7D_PAD_EPDC_GDRL),
	IMX_PINCTRL_PIN(MX7D_PAD_EPDC_GDSP),
	IMX_PINCTRL_PIN(MX7D_PAD_EPDC_BDR0),
	IMX_PINCTRL_PIN(MX7D_PAD_EPDC_BDR1),
	IMX_PINCTRL_PIN(MX7D_PAD_EPDC_PWR_COM),
	IMX_PINCTRL_PIN(MX7D_PAD_EPDC_PWR_STAT),
	IMX_PINCTRL_PIN(MX7D_PAD_LCD_CLK),
	IMX_PINCTRL_PIN(MX7D_PAD_LCD_ENABLE),
	IMX_PINCTRL_PIN(MX7D_PAD_LCD_HSYNC),
	IMX_PINCTRL_PIN(MX7D_PAD_LCD_VSYNC),
	IMX_PINCTRL_PIN(MX7D_PAD_LCD_RESET),
	IMX_PINCTRL_PIN(MX7D_PAD_LCD_DATA00),
	IMX_PINCTRL_PIN(MX7D_PAD_LCD_DATA01),
	IMX_PINCTRL_PIN(MX7D_PAD_LCD_DATA02),
	IMX_PINCTRL_PIN(MX7D_PAD_LCD_DATA03),
	IMX_PINCTRL_PIN(MX7D_PAD_LCD_DATA04),
	IMX_PINCTRL_PIN(MX7D_PAD_LCD_DATA05),
	IMX_PINCTRL_PIN(MX7D_PAD_LCD_DATA06),
	IMX_PINCTRL_PIN(MX7D_PAD_LCD_DATA07),
	IMX_PINCTRL_PIN(MX7D_PAD_LCD_DATA08),
	IMX_PINCTRL_PIN(MX7D_PAD_LCD_DATA09),
	IMX_PINCTRL_PIN(MX7D_PAD_LCD_DATA10),
	IMX_PINCTRL_PIN(MX7D_PAD_LCD_DATA11),
	IMX_PINCTRL_PIN(MX7D_PAD_LCD_DATA12),
	IMX_PINCTRL_PIN(MX7D_PAD_LCD_DATA13),
	IMX_PINCTRL_PIN(MX7D_PAD_LCD_DATA14),
	IMX_PINCTRL_PIN(MX7D_PAD_LCD_DATA15),
	IMX_PINCTRL_PIN(MX7D_PAD_LCD_DATA16),
	IMX_PINCTRL_PIN(MX7D_PAD_LCD_DATA17),
	IMX_PINCTRL_PIN(MX7D_PAD_LCD_DATA18),
	IMX_PINCTRL_PIN(MX7D_PAD_LCD_DATA19),
	IMX_PINCTRL_PIN(MX7D_PAD_LCD_DATA20),
	IMX_PINCTRL_PIN(MX7D_PAD_LCD_DATA21),
	IMX_PINCTRL_PIN(MX7D_PAD_LCD_DATA22),
	IMX_PINCTRL_PIN(MX7D_PAD_LCD_DATA23),
	IMX_PINCTRL_PIN(MX7D_PAD_UART1_RX_DATA),
	IMX_PINCTRL_PIN(MX7D_PAD_UART1_TX_DATA),
	IMX_PINCTRL_PIN(MX7D_PAD_UART2_RX_DATA),
	IMX_PINCTRL_PIN(MX7D_PAD_UART2_TX_DATA),
	IMX_PINCTRL_PIN(MX7D_PAD_UART3_RX_DATA),
	IMX_PINCTRL_PIN(MX7D_PAD_UART3_TX_DATA),
	IMX_PINCTRL_PIN(MX7D_PAD_UART3_RTS_B),
	IMX_PINCTRL_PIN(MX7D_PAD_UART3_CTS_B),
	IMX_PINCTRL_PIN(MX7D_PAD_I2C1_SCL),
	IMX_PINCTRL_PIN(MX7D_PAD_I2C1_SDA),
	IMX_PINCTRL_PIN(MX7D_PAD_I2C2_SCL),
	IMX_PINCTRL_PIN(MX7D_PAD_I2C2_SDA),
	IMX_PINCTRL_PIN(MX7D_PAD_I2C3_SCL),
	IMX_PINCTRL_PIN(MX7D_PAD_I2C3_SDA),
	IMX_PINCTRL_PIN(MX7D_PAD_I2C4_SCL),
	IMX_PINCTRL_PIN(MX7D_PAD_I2C4_SDA),
	IMX_PINCTRL_PIN(MX7D_PAD_ECSPI1_SCLK),
	IMX_PINCTRL_PIN(MX7D_PAD_ECSPI1_MOSI),
	IMX_PINCTRL_PIN(MX7D_PAD_ECSPI1_MISO),
	IMX_PINCTRL_PIN(MX7D_PAD_ECSPI1_SS0),
	IMX_PINCTRL_PIN(MX7D_PAD_ECSPI2_SCLK),
	IMX_PINCTRL_PIN(MX7D_PAD_ECSPI2_MOSI),
	IMX_PINCTRL_PIN(MX7D_PAD_ECSPI2_MISO),
	IMX_PINCTRL_PIN(MX7D_PAD_ECSPI2_SS0),
	IMX_PINCTRL_PIN(MX7D_PAD_SD1_CD_B),
	IMX_PINCTRL_PIN(MX7D_PAD_SD1_WP),
	IMX_PINCTRL_PIN(MX7D_PAD_SD1_RESET_B),
	IMX_PINCTRL_PIN(MX7D_PAD_SD1_CLK),
	IMX_PINCTRL_PIN(MX7D_PAD_SD1_CMD),
	IMX_PINCTRL_PIN(MX7D_PAD_SD1_DATA0),
	IMX_PINCTRL_PIN(MX7D_PAD_SD1_DATA1),
	IMX_PINCTRL_PIN(MX7D_PAD_SD1_DATA2),
	IMX_PINCTRL_PIN(MX7D_PAD_SD1_DATA3),
	IMX_PINCTRL_PIN(MX7D_PAD_SD2_CD_B),
	IMX_PINCTRL_PIN(MX7D_PAD_SD2_WP),
	IMX_PINCTRL_PIN(MX7D_PAD_SD2_RESET_B),
	IMX_PINCTRL_PIN(MX7D_PAD_SD2_CLK),
	IMX_PINCTRL_PIN(MX7D_PAD_SD2_CMD),
	IMX_PINCTRL_PIN(MX7D_PAD_SD2_DATA0),
	IMX_PINCTRL_PIN(MX7D_PAD_SD2_DATA1),
	IMX_PINCTRL_PIN(MX7D_PAD_SD2_DATA2),
	IMX_PINCTRL_PIN(MX7D_PAD_SD2_DATA3),
	IMX_PINCTRL_PIN(MX7D_PAD_SD3_CLK),
	IMX_PINCTRL_PIN(MX7D_PAD_SD3_CMD),
	IMX_PINCTRL_PIN(MX7D_PAD_SD3_DATA0),
	IMX_PINCTRL_PIN(MX7D_PAD_SD3_DATA1),
	IMX_PINCTRL_PIN(MX7D_PAD_SD3_DATA2),
	IMX_PINCTRL_PIN(MX7D_PAD_SD3_DATA3),
	IMX_PINCTRL_PIN(MX7D_PAD_SD3_DATA4),
	IMX_PINCTRL_PIN(MX7D_PAD_SD3_DATA5),
	IMX_PINCTRL_PIN(MX7D_PAD_SD3_DATA6),
	IMX_PINCTRL_PIN(MX7D_PAD_SD3_DATA7),
	IMX_PINCTRL_PIN(MX7D_PAD_SD3_STROBE),
	IMX_PINCTRL_PIN(MX7D_PAD_SD3_RESET_B),
	IMX_PINCTRL_PIN(MX7D_PAD_SAI1_RX_DATA),
	IMX_PINCTRL_PIN(MX7D_PAD_SAI1_TX_BCLK),
	IMX_PINCTRL_PIN(MX7D_PAD_SAI1_TX_SYNC),
	IMX_PINCTRL_PIN(MX7D_PAD_SAI1_TX_DATA),
	IMX_PINCTRL_PIN(MX7D_PAD_SAI1_RX_SYNC),
	IMX_PINCTRL_PIN(MX7D_PAD_SAI1_RX_BCLK),
	IMX_PINCTRL_PIN(MX7D_PAD_SAI1_MCLK),
	IMX_PINCTRL_PIN(MX7D_PAD_SAI2_TX_SYNC),
	IMX_PINCTRL_PIN(MX7D_PAD_SAI2_TX_BCLK),
	IMX_PINCTRL_PIN(MX7D_PAD_SAI2_RX_DATA),
	IMX_PINCTRL_PIN(MX7D_PAD_SAI2_TX_DATA),
	IMX_PINCTRL_PIN(MX7D_PAD_ENET1_RGMII_RD0),
	IMX_PINCTRL_PIN(MX7D_PAD_ENET1_RGMII_RD1),
	IMX_PINCTRL_PIN(MX7D_PAD_ENET1_RGMII_RD2),
	IMX_PINCTRL_PIN(MX7D_PAD_ENET1_RGMII_RD3),
	IMX_PINCTRL_PIN(MX7D_PAD_ENET1_RGMII_RX_CTL),
	IMX_PINCTRL_PIN(MX7D_PAD_ENET1_RGMII_RXC),
	IMX_PINCTRL_PIN(MX7D_PAD_ENET1_RGMII_TD0),
	IMX_PINCTRL_PIN(MX7D_PAD_ENET1_RGMII_TD1),
	IMX_PINCTRL_PIN(MX7D_PAD_ENET1_RGMII_TD2),
	IMX_PINCTRL_PIN(MX7D_PAD_ENET1_RGMII_TD3),
	IMX_PINCTRL_PIN(MX7D_PAD_ENET1_RGMII_TX_CTL),
	IMX_PINCTRL_PIN(MX7D_PAD_ENET1_RGMII_TXC),
	IMX_PINCTRL_PIN(MX7D_PAD_ENET1_TX_CLK),
	IMX_PINCTRL_PIN(MX7D_PAD_ENET1_RX_CLK),
	IMX_PINCTRL_PIN(MX7D_PAD_ENET1_CRS),
	IMX_PINCTRL_PIN(MX7D_PAD_ENET1_COL),
};

/* Pad names for the pinmux subsystem */
static const struct pinctrl_pin_desc imx7d_lpsr_pinctrl_pads[] = {
	IMX_PINCTRL_PIN(MX7D_PAD_GPIO1_IO00),
	IMX_PINCTRL_PIN(MX7D_PAD_GPIO1_IO01),
	IMX_PINCTRL_PIN(MX7D_PAD_GPIO1_IO02),
	IMX_PINCTRL_PIN(MX7D_PAD_GPIO1_IO03),
	IMX_PINCTRL_PIN(MX7D_PAD_GPIO1_IO04),
	IMX_PINCTRL_PIN(MX7D_PAD_GPIO1_IO05),
	IMX_PINCTRL_PIN(MX7D_PAD_GPIO1_IO06),
	IMX_PINCTRL_PIN(MX7D_PAD_GPIO1_IO07),
};

static const struct imx_pinctrl_soc_info imx7d_pinctrl_info = {
	.pins = imx7d_pinctrl_pads,
	.npins = ARRAY_SIZE(imx7d_pinctrl_pads),
	.gpr_compatible = "fsl,imx7d-iomuxc-gpr",
};

static const struct imx_pinctrl_soc_info imx7d_lpsr_pinctrl_info = {
	.pins = imx7d_lpsr_pinctrl_pads,
	.npins = ARRAY_SIZE(imx7d_lpsr_pinctrl_pads),
	.flags = ZERO_OFFSET_VALID,
};

static const struct of_device_id imx7d_pinctrl_of_match[] = {
	{ .compatible = "fsl,imx7d-iomuxc", .data = &imx7d_pinctrl_info, },
	{ .compatible = "fsl,imx7d-iomuxc-lpsr", .data = &imx7d_lpsr_pinctrl_info },
	{ /* sentinel */ }
};

static int imx7d_pinctrl_probe(struct platform_device *pdev)
{
	const struct imx_pinctrl_soc_info *pinctrl_info;

	pinctrl_info = of_device_get_match_data(&pdev->dev);
	if (!pinctrl_info)
		return -ENODEV;

	return imx_pinctrl_probe(pdev, pinctrl_info);
}

static struct platform_driver imx7d_pinctrl_driver = {
	.driver = {
		.name = "imx7d-pinctrl",
		.of_match_table = of_match_ptr(imx7d_pinctrl_of_match),
	},
	.probe = imx7d_pinctrl_probe,
};

static int __init imx7d_pinctrl_init(void)
{
	return platform_driver_register(&imx7d_pinctrl_driver);
}
arch_initcall(imx7d_pinctrl_init);