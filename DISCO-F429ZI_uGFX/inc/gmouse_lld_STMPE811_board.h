/*
 * This file is subject to the terms of the GFX License. If a copy of


 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.org/license.html
 */
//Initialize STMPE811 SPI and data transfer functions

#undef Red
#undef Green
#undef Blue

#include "stm32f4xx_hal.h"

#ifndef _GINPUT_LLD_MOUSE_BOARD_H
#define _GINPUT_LLD_MOUSE_BOARD_H

// Resolution and Accuracy Settings
#define GMOUSE_STMPE811_PEN_CALIBRATE_ERROR		8
#define GMOUSE_STMPE811_PEN_CLICK_ERROR			6
#define GMOUSE_STMPE811_PEN_MOVE_ERROR			4
#define GMOUSE_STMPE811_FINGER_CALIBRATE_ERROR	14
#define GMOUSE_STMPE811_FINGER_CLICK_ERROR		18
#define GMOUSE_STMPE811_FINGER_MOVE_ERROR		14

// How much extra data to allocate at the end of the GMouse structure for the board's use
#define GMOUSE_STMPE811_BOARD_DATA_SIZE			0

// Options - Leave these commented to make it user configurable in the gfxconf.h
//#define GMOUSE_STMPE811_READ_PRESSURE		FALSE
//#define GMOUSE_STMPE811_SELF_CALIBRATE	FALSE
//#define GMOUSE_STMPE811_TEST_MODE			FALSE

// Set to FALSE because it does not work properly on this board even though the pin exists.
#define GMOUSE_STMPE811_GPIO_IRQPIN				FALSE

// If TRUE this is a really slow CPU and we should always clear the FIFO between reads.
#define GMOUSE_STMPE811_SLOW_CPU				FALSE

// Slave address
#define STMPE811_ADDR				0x82

// Maximum timeout
#define STMPE811_TIMEOUT			0x3000

GPIO_InitTypeDef GPIO_InitStruct;
I2C_HandleTypeDef hi2c3;

static bool_t init_board(GMouse* m, unsigned driverinstance) {
	(void)m;


	// This board only supports one touch panel
	if (driverinstance)
		return FALSE;

	//SDL
    GPIO_InitStruct.Pin = GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C3;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
    //SCL
    GPIO_InitStruct.Pin = GPIO_PIN_8;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C3;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    __HAL_RCC_I2C3_CLK_ENABLE();
    __HAL_RCC_I2C3_FORCE_RESET();
    __HAL_RCC_I2C3_RELEASE_RESET();

    // Enable and set Discovery I2Cx Interrupt to the lowest priority /
    //HAL_NVIC_SetPriority(I2C3_EV_IRQn, 0x0F, 0);
   // HAL_NVIC_EnableIRQ(I2C3_EV_IRQn);

    // Enable and set Discovery I2Cx Interrupt to the lowest priority /
   // HAL_NVIC_SetPriority(I2C3_ER_IRQn, 0x0F, 0);
    //HAL_NVIC_EnableIRQ(I2C3_ER_IRQn);

    hi2c3.Instance = I2C3;
    hi2c3.Init.ClockSpeed = 100000;
    hi2c3.Init.DutyCycle = I2C_DUTYCYCLE_2;
    hi2c3.Init.OwnAddress1 = 0;
    hi2c3.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    hi2c3.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    hi2c3.Init.OwnAddress2 = 0;
    hi2c3.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    hi2c3.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;


    HAL_I2C_Init(&hi2c3);

    //////STMPE811 IRQ
    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitStruct.Pin   = GPIO_PIN_15;
    GPIO_InitStruct.Pull  = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
    GPIO_InitStruct.Mode  = GPIO_MODE_INPUT;// GPIO_MODE_IT_FALLING;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* Enable and set GPIO EXTI Interrupt to the highest priority */
    //HAL_NVIC_SetPriority((IRQn_Type)(EXTI15_10_IRQn), 0x0F, 0x00);
   // HAL_NVIC_EnableIRQ((IRQn_Type)(EXTI15_10_IRQn));

    /* Peripheral clock enable */
    __HAL_RCC_I2C3_CLK_ENABLE();
    /* Peripheral interrupt init */
   // HAL_NVIC_SetPriority(I2C3_EV_IRQn, 0, 0);
    //HAL_NVIC_EnableIRQ(I2C3_EV_IRQn);



	return TRUE;
}

#if GMOUSE_STMPE811_GPIO_IRQPIN
	static bool_t getpin_irq(GMouse* m) {
		(void)		m;

		return !HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15);	//!palReadPad(GPIOA, 15);
	}
#endif

static GFXINLINE void aquire_bus(GMouse* m) {
	(void)		m;

}

static GFXINLINE void release_bus(GMouse* m) {
	(void)		m;

}

static void write_reg(GMouse* m, uint8_t reg, uint8_t val) {

    HAL_StatusTypeDef status = HAL_OK;

    status = HAL_I2C_Mem_Write(&hi2c3, STMPE811_ADDR, (uint16_t)reg, I2C_MEMADD_SIZE_8BIT, &val, 1, STMPE811_TIMEOUT);

    /* Check the communication status */
    if(status != HAL_OK)
    {
      /* Re-Initialize the BUS */
//      I2Cx_Error();
    }

}

static uint8_t read_byte(GMouse* m, uint8_t reg) {
	uint8_t		rxbuf[1];
	(void)		m;

	rxbuf[0] = 0;

    HAL_StatusTypeDef status = HAL_OK;

    //status = HAL_I2C_Mem_Read(&hi2c3, STMPE811_ADDR, (uint16_t)reg, I2C_MEMADD_SIZE_8BIT, rxbuf, 1, STMPE811_TIMEOUT);
    HAL_I2C_Master_Transmit(&hi2c3, STMPE811_ADDR, &reg, 1, 100);
    HAL_I2C_Master_Receive(&hi2c3, STMPE811_ADDR, rxbuf, 1, 100);


    /* Check the communication status */
    if(status != HAL_OK)
    {
      /* Re-Initialize the BUS */
//      I2Cx_Error();
    }

	return rxbuf[0];
}

static uint16_t read_word(GMouse* m, uint8_t reg) {
	uint8_t		rxbuf[2];
	(void)		m;

	rxbuf[0] = 0;
	rxbuf[1] = 0;

    HAL_StatusTypeDef status = HAL_OK;

    //status = HAL_I2C_Mem_Read(&hi2c3, STMPE811_ADDR, (uint16_t)reg, I2C_MEMADD_SIZE_8BIT, rxbuf, 2, STMPE811_TIMEOUT);

    HAL_I2C_Master_Transmit(&hi2c3, STMPE811_ADDR, &reg, 1, 100);
    HAL_I2C_Master_Receive(&hi2c3, STMPE811_ADDR, rxbuf, 2, 100);

    /* Check the communication status */
    if(status != HAL_OK)
    {
      /* Re-Initialize the BUS */
///      I2Cx_Error();
    }

	return (((uint16_t)rxbuf[0]) << 8) | rxbuf[1];
}

#endif
