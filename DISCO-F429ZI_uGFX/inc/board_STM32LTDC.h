/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.org/license.html
 */

//We need  initialize only SDRAM, FMC, LCD peripherals and ili9341 SPI. uGFX already uses HAL drivers for SDRAM

#ifndef _GDISP_LLD_BOARD_H
#define _GDISP_LLD_BOARD_H

#undef Red
#undef Green
#undef Blue

#include "stm32f4xx_hal.h"


#define SDRAM_OK         						 ((uint8_t)0x00)
#define SDRAM_ERROR     						 ((uint8_t)0x01)
#define SDRAM_DEVICE_ADDR    					 ((uint32_t)0xD0000000)
#define SDRAM_DEVICE_SIZE      					 ((uint32_t)0x800000)  /* SDRAM device size in Bytes */
#define SDRAM_DMAx_CHANNEL        				 DMA_CHANNEL_0
#define SDRAM_DMAx_STREAM       				 DMA2_Stream0
#define SDRAM_DMAx_IRQn							 DMA2_Stream0_IRQn
#define SDRAM_MEMORY_WIDTH     					 FMC_SDRAM_MEM_BUS_WIDTH_16
#define SDRAM_CAS_LATENCY       				 FMC_SDRAM_CAS_LATENCY_3
#define SDCLOCK_PERIOD        				 	 FMC_SDRAM_CLOCK_PERIOD_2
#define SDRAM_READBURST      				  	 FMC_SDRAM_RBURST_DISABLE
#define SDRAM_TIMEOUT      					     ((uint32_t)0xFFFF)

#define SDRAM_MODEREG_BURST_LENGTH_1             ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_LENGTH_2             ((uint16_t)0x0001)
#define SDRAM_MODEREG_BURST_LENGTH_4             ((uint16_t)0x0002)
#define SDRAM_MODEREG_BURST_LENGTH_8             ((uint16_t)0x0004)
#define SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL      ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_TYPE_INTERLEAVED     ((uint16_t)0x0008)
#define SDRAM_MODEREG_CAS_LATENCY_2              ((uint16_t)0x0020)
#define SDRAM_MODEREG_CAS_LATENCY_3              ((uint16_t)0x0030)
#define SDRAM_MODEREG_OPERATING_MODE_STANDARD    ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_PROGRAMMED ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_SINGLE     ((uint16_t)0x0200)

#define REFRESH_COUNT           				((uint32_t)1386)   /* SDRAM refresh counter */
#define __DMAx_CLK_ENABLE       				__HAL_RCC_DMA2_CLK_ENABLE

//LCD SPI
#define LCD_SPIx                          		SPI5
#define LCD_SPIx_CLK_ENABLE()             		__HAL_RCC_SPI5_CLK_ENABLE()
#define LCD_SPIx_GPIO_PORT                		GPIOF                      /* GPIOF */
#define LCD_SPIx_AF                       		GPIO_AF5_SPI5
#define LCD_SPIx_GPIO_CLK_ENABLE()        		__HAL_RCC_GPIOF_CLK_ENABLE()
#define LCD_SPIx_GPIO_CLK_DISABLE()       		__HAL_RCC_GPIOF_CLK_DISABLE()
#define LCD_SPIx_SCK_PIN                  		GPIO_PIN_7                 /* PF.07 */
#define LCD_SPIx_MISO_PIN                 		GPIO_PIN_8                 /* PF.08 */
#define LCD_SPIx_MOSI_PIN                 		GPIO_PIN_9                 /* PF.09 */
#define SPIx_TIMEOUT_MAX              			((uint32_t)0x1000)

#define LCD_CS_LOW()       HAL_GPIO_WritePin(LCD_NCS_GPIO_PORT, LCD_NCS_PIN, GPIO_PIN_RESET)
#define LCD_CS_HIGH()      HAL_GPIO_WritePin(LCD_NCS_GPIO_PORT, LCD_NCS_PIN, GPIO_PIN_SET)

#define LCD_WRX_LOW()      HAL_GPIO_WritePin(LCD_WRX_GPIO_PORT, LCD_WRX_PIN, GPIO_PIN_RESET)
#define LCD_WRX_HIGH()     HAL_GPIO_WritePin(LCD_WRX_GPIO_PORT, LCD_WRX_PIN, GPIO_PIN_SET)

#define LCD_RDX_LOW()      HAL_GPIO_WritePin(LCD_RDX_GPIO_PORT, LCD_RDX_PIN, GPIO_PIN_RESET)
#define LCD_RDX_HIGH()     HAL_GPIO_WritePin(LCD_RDX_GPIO_PORT, LCD_RDX_PIN, GPIO_PIN_SET)

#define LCD_WRX_PIN                             GPIO_PIN_13
#define LCD_WRX_GPIO_PORT                       GPIOD
#define LCD_WRX_GPIO_CLK_ENABLE()               __HAL_RCC_GPIOD_CLK_ENABLE()
#define LCD_WRX_GPIO_CLK_DISABLE()              __HAL_RCC_GPIOD_CLK_DISABLE()
#define LCD_RDX_PIN                             GPIO_PIN_12
#define LCD_RDX_GPIO_CLK_ENABLE()               __HAL_RCC_GPIOD_CLK_ENABLE()
#define LCD_RDX_GPIO_CLK_DISABLE()              __HAL_RCC_GPIOD_CLK_DISABLE()
#define LCD_RDX_GPIO_PORT                       GPIOD
#define LCD_NCS_PIN                             GPIO_PIN_2
#define LCD_NCS_GPIO_PORT                       GPIOC
#define LCD_NCS_GPIO_CLK_ENABLE()               __HAL_RCC_GPIOC_CLK_ENABLE()
#define LCD_NCS_GPIO_CLK_DISABLE()              __HAL_RCC_GPIOC_CLK_DISABLE()


static SPI_HandleTypeDef SpiHandle;


static const ltdcConfig driverCfg = {
	240, 320,
	10, 2,
	20, 2,
	10, 4,
	0,
	0x000000,
	{
		(LLDCOLOR_TYPE *)SDRAM_DEVICE_ADDR,	// frame
		240, 320,							// width, height
		240 * LTDC_PIXELBYTES,				// pitch
		LTDC_PIXELFORMAT,					// fmt
		0, 0,								// x, y
		240, 320,							// cx, cy
		LTDC_COLOR_FUCHSIA,					// defcolor
		0x980088,							// keycolor
		LTDC_BLEND_FIX1_FIX2,				// blending
		0,									// palette
		0,									// palettelen
		0xFF,								// alpha
		LTDC_LEF_ENABLE						// flags
	},
	LTDC_UNUSED_LAYER_CONFIG
};

static void configureLcdClock(void)
{
	#if 1
		RCC_PeriphCLKInitTypeDef	periph_clk_init_struct;

		periph_clk_init_struct.PLLSAI.PLLSAIN = 192;
		periph_clk_init_struct.PeriphClockSelection = RCC_PERIPHCLK_LTDC;
		periph_clk_init_struct.PLLSAI.PLLSAIR = 4;
		periph_clk_init_struct.PLLSAIDivR = RCC_PLLSAIDIVR_8;
		HAL_RCCEx_PeriphCLKConfig(&periph_clk_init_struct);
	#else
		#define LCD_PLLSAIQ_VALUE                 7

		/* PLLSAI activation.*/
		/*RCC->PLLSAICFGR = (LCD_PLLSAIN_VALUE << 6) | (LCD_PLLSAIR_VALUE << 28) | (LCD_PLLSAIQ_VALUE << 24);
		RCC->DCKCFGR = (RCC->DCKCFGR & ~RCC_DCKCFGR_PLLSAIDIVR) | LCD_PLLSAIDIVR_VALUE;
		RCC->CR |= RCC_CR_PLLSAION;*/
	#endif
}

__weak void LCD_MspInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* Enable the LTDC and DMA2D Clock */
	__HAL_RCC_LTDC_CLK_ENABLE();
	__HAL_RCC_DMA2D_CLK_ENABLE();

	/* Enable GPIOs clock */
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOF_CLK_ENABLE();
	__HAL_RCC_GPIOG_CLK_ENABLE();

	/* GPIOs Configuration */
	/*
	+------------------------+-----------------------+----------------------------+
	+                       LCD pins assignment                                   +
	+------------------------+-----------------------+----------------------------+
	|  LCD_TFT R2 <-> PC.10  |  LCD_TFT G2 <-> PA.06 |  LCD_TFT B2 <-> PD.06      |
	|  LCD_TFT R3 <-> PB.00  |  LCD_TFT G3 <-> PG.10 |  LCD_TFT B3 <-> PG.11      |
	|  LCD_TFT R4 <-> PA.11  |  LCD_TFT G4 <-> PB.10 |  LCD_TFT B4 <-> PG.12      |
	|  LCD_TFT R5 <-> PA.12  |  LCD_TFT G5 <-> PB.11 |  LCD_TFT B5 <-> PA.03      |
	|  LCD_TFT R6 <-> PB.01  |  LCD_TFT G6 <-> PC.07 |  LCD_TFT B6 <-> PB.08      |
	|  LCD_TFT R7 <-> PG.06  |  LCD_TFT G7 <-> PD.03 |  LCD_TFT B7 <-> PB.09      |
	-------------------------------------------------------------------------------
			|  LCD_TFT HSYNC <-> PC.06  | LCDTFT VSYNC <->  PA.04 |
			|  LCD_TFT CLK   <-> PG.07  | LCD_TFT DE   <->  PF.10 |
			 -----------------------------------------------------
	*/

	/* GPIOA configuration */
	GPIO_InitStructure.Pin = GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_6 |
						   GPIO_PIN_11 | GPIO_PIN_12;
	GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	GPIO_InitStructure.Speed = GPIO_SPEED_FAST;
	GPIO_InitStructure.Alternate= GPIO_AF14_LTDC;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* GPIOB configuration */
	GPIO_InitStructure.Pin = GPIO_PIN_8 | \
						   GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);

	/* GPIOC configuration */
	GPIO_InitStructure.Pin = GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_10;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStructure);

	/* GPIOD configuration */
	GPIO_InitStructure.Pin = GPIO_PIN_3 | GPIO_PIN_6;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStructure);

	/* GPIOF configuration */
	GPIO_InitStructure.Pin = GPIO_PIN_10;
	HAL_GPIO_Init(GPIOF, &GPIO_InitStructure);

	/* GPIOG configuration */
	GPIO_InitStructure.Pin = GPIO_PIN_6 | GPIO_PIN_7 | \
						   GPIO_PIN_11;
	HAL_GPIO_Init(GPIOG, &GPIO_InitStructure);

	/* GPIOB configuration */
	GPIO_InitStructure.Pin = GPIO_PIN_0 | GPIO_PIN_1;
	GPIO_InitStructure.Alternate= GPIO_AF9_LTDC;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);

	/* GPIOG configuration */
	GPIO_InitStructure.Pin = GPIO_PIN_10 | GPIO_PIN_12;
	HAL_GPIO_Init(GPIOG, &GPIO_InitStructure);
}

__weak void SDRAM_MspInit(SDRAM_HandleTypeDef  *hsdram, void *Params)
{
	static DMA_HandleTypeDef dmaHandle;
	GPIO_InitTypeDef GPIO_InitStructure;

	if(hsdram != (SDRAM_HandleTypeDef  *)NULL)
	{
	/* Enable FMC clock */
	__HAL_RCC_FMC_CLK_ENABLE();

	/* Enable chosen DMAx clock */
	__DMAx_CLK_ENABLE();

	/* Enable GPIOs clock */
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOF_CLK_ENABLE();
	__HAL_RCC_GPIOG_CLK_ENABLE();

	/*-- GPIOs Configuration -----------------------------------------------------*/
	/*
	+-------------------+--------------------+--------------------+--------------------+
	+                       SDRAM pins assignment                                      +
	+-------------------+--------------------+--------------------+--------------------+
	| PD0  <-> FMC_D2   | PE0  <-> FMC_NBL0  | PF0  <-> FMC_A0    | PG0  <-> FMC_A10   |
	| PD1  <-> FMC_D3   | PE1  <-> FMC_NBL1  | PF1  <-> FMC_A1    | PG1  <-> FMC_A11   |
	| PD8  <-> FMC_D13  | PE7  <-> FMC_D4    | PF2  <-> FMC_A2    | PG8  <-> FMC_SDCLK |
	| PD9  <-> FMC_D14  | PE8  <-> FMC_D5    | PF3  <-> FMC_A3    | PG15 <-> FMC_NCAS  |
	| PD10 <-> FMC_D15  | PE9  <-> FMC_D6    | PF4  <-> FMC_A4    |--------------------+
	| PD14 <-> FMC_D0   | PE10 <-> FMC_D7    | PF5  <-> FMC_A5    |
	| PD15 <-> FMC_D1   | PE11 <-> FMC_D8    | PF11 <-> FMC_NRAS  |
	+-------------------| PE12 <-> FMC_D9    | PF12 <-> FMC_A6    |
					 | PE13 <-> FMC_D10   | PF13 <-> FMC_A7    |
					 | PE14 <-> FMC_D11   | PF14 <-> FMC_A8    |
					 | PE15 <-> FMC_D12   | PF15 <-> FMC_A9    |
	+-------------------+--------------------+--------------------+
	| PB5 <-> FMC_SDCKE1|
	| PB6 <-> FMC_SDNE1 |
	| PC0 <-> FMC_SDNWE |
	+-------------------+

	*/

	/* Common GPIO configuration */
	GPIO_InitStructure.Mode  = GPIO_MODE_AF_PP;
	GPIO_InitStructure.Speed = GPIO_SPEED_FAST;
	GPIO_InitStructure.Pull  = GPIO_NOPULL;
	GPIO_InitStructure.Alternate = GPIO_AF12_FMC;

	/* GPIOB configuration */
	GPIO_InitStructure.Pin = GPIO_PIN_5 | GPIO_PIN_6;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);

	/* GPIOC configuration */
	GPIO_InitStructure.Pin = GPIO_PIN_0;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStructure);

	/* GPIOD configuration */
	GPIO_InitStructure.Pin = GPIO_PIN_0 | GPIO_PIN_1  | GPIO_PIN_8 |
						   GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_14 |
						   GPIO_PIN_15;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStructure);

	/* GPIOE configuration */
	GPIO_InitStructure.Pin = GPIO_PIN_0  | GPIO_PIN_1  | GPIO_PIN_7 |
						   GPIO_PIN_8  | GPIO_PIN_9  | GPIO_PIN_10 |
						   GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 |
						   GPIO_PIN_14 | GPIO_PIN_15;
	HAL_GPIO_Init(GPIOE, &GPIO_InitStructure);

	/* GPIOF configuration */
	GPIO_InitStructure.Pin = GPIO_PIN_0  | GPIO_PIN_1 | GPIO_PIN_2 |
						   GPIO_PIN_3  | GPIO_PIN_4 | GPIO_PIN_5 |
						   GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 |
						   GPIO_PIN_14 | GPIO_PIN_15;
	HAL_GPIO_Init(GPIOF, &GPIO_InitStructure);

	/* GPIOG configuration */
	GPIO_InitStructure.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_4 |
						   GPIO_PIN_5 | GPIO_PIN_8 | GPIO_PIN_15;
	HAL_GPIO_Init(GPIOG, &GPIO_InitStructure);

	/* Configure common DMA parameters */
	dmaHandle.Init.Channel             = SDRAM_DMAx_CHANNEL;
	dmaHandle.Init.Direction           = DMA_MEMORY_TO_MEMORY;
	dmaHandle.Init.PeriphInc           = DMA_PINC_ENABLE;
	dmaHandle.Init.MemInc              = DMA_MINC_ENABLE;
	dmaHandle.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
	dmaHandle.Init.MemDataAlignment    = DMA_MDATAALIGN_WORD;
	dmaHandle.Init.Mode                = DMA_NORMAL;
	dmaHandle.Init.Priority            = DMA_PRIORITY_HIGH;
	dmaHandle.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;
	dmaHandle.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
	dmaHandle.Init.MemBurst            = DMA_MBURST_SINGLE;
	dmaHandle.Init.PeriphBurst         = DMA_PBURST_SINGLE;

	dmaHandle.Instance = SDRAM_DMAx_STREAM;

	/* Associate the DMA handle */
	__HAL_LINKDMA(hsdram, hdma, dmaHandle);

	/* Deinitialize the stream for new transfer */
	HAL_DMA_DeInit(&dmaHandle);

	/* Configure the DMA stream */
	HAL_DMA_Init(&dmaHandle);

	/* NVIC configuration for DMA transfer complete interrupt */
	HAL_NVIC_SetPriority(SDRAM_DMAx_IRQn, 0x0F, 0);
	HAL_NVIC_EnableIRQ(SDRAM_DMAx_IRQn);
	} /* of if(hsdram != (SDRAM_HandleTypeDef  *)NULL) */
}



uint8_t SDRAM_Init(void)
{
	static SDRAM_HandleTypeDef SdramHandle;
	static FMC_SDRAM_TimingTypeDef Timing;
	static FMC_SDRAM_CommandTypeDef Command;
	static uint8_t sdramstatus = SDRAM_ERROR;

	__IO uint32_t tmpmrd =0;


	/* SDRAM device configuration */
	SdramHandle.Instance = FMC_SDRAM_DEVICE;

	/* FMC Configuration -------------------------------------------------------*/
	/* FMC SDRAM Bank configuration */
	/* Timing configuration for 90 Mhz of SD clock frequency (180Mhz/2) */
	/* TMRD: 2 Clock cycles */
	Timing.LoadToActiveDelay    = 2;
	/* TXSR: min=70ns (7x11.11ns) */
	Timing.ExitSelfRefreshDelay = 7;
	/* TRAS: min=42ns (4x11.11ns) max=120k (ns) */
	Timing.SelfRefreshTime      = 4;
	/* TRC:  min=70 (7x11.11ns) */
	Timing.RowCycleDelay        = 7;
	/* TWR:  min=1+ 7ns (1+1x11.11ns) */
	Timing.WriteRecoveryTime    = 2;
	/* TRP:  20ns => 2x11.11ns*/
	Timing.RPDelay              = 2;
	/* TRCD: 20ns => 2x11.11ns */
	Timing.RCDDelay             = 2;

	/* FMC SDRAM control configuration */
	SdramHandle.Init.SDBank             = FMC_SDRAM_BANK2;
	/* Row addressing: [7:0] */
	SdramHandle.Init.ColumnBitsNumber   = FMC_SDRAM_COLUMN_BITS_NUM_8;
	/* Column addressing: [11:0] */
	SdramHandle.Init.RowBitsNumber      = FMC_SDRAM_ROW_BITS_NUM_12;
	SdramHandle.Init.MemoryDataWidth    = SDRAM_MEMORY_WIDTH;
	SdramHandle.Init.InternalBankNumber = FMC_SDRAM_INTERN_BANKS_NUM_4;
	SdramHandle.Init.CASLatency         = SDRAM_CAS_LATENCY;
	SdramHandle.Init.WriteProtection    = FMC_SDRAM_WRITE_PROTECTION_DISABLE;
	SdramHandle.Init.SDClockPeriod      = SDCLOCK_PERIOD;
	SdramHandle.Init.ReadBurst          = SDRAM_READBURST;
	SdramHandle.Init.ReadPipeDelay      = FMC_SDRAM_RPIPE_DELAY_1;

	/* SDRAM controller initialization */
	/* __weak function can be surcharged by the application code */
	SDRAM_MspInit(&SdramHandle, (void *)NULL);
	if(HAL_SDRAM_Init(&SdramHandle, &Timing) != HAL_OK)
	{
	sdramstatus = SDRAM_ERROR;
	}
	else
	{
	sdramstatus = SDRAM_OK;
	}

	/* SDRAM initialization sequence */
	//BSP_SDRAM_Initialization_sequence(REFRESH_COUNT);


	/* Step 1:  Configure a clock configuration enable command */
	Command.CommandMode             = FMC_SDRAM_CMD_CLK_ENABLE;
	Command.CommandTarget           = FMC_SDRAM_CMD_TARGET_BANK2;
	Command.AutoRefreshNumber       = 1;
	Command.ModeRegisterDefinition  = 0;

	/* Send the command */
	HAL_SDRAM_SendCommand(&SdramHandle, &Command, SDRAM_TIMEOUT);

	/* Step 2: Insert 100 us minimum delay */
	/* Inserted delay is equal to 1 ms due to systick time base unit (ms) */
	//HAL_Delay(1);
	wait_ms(1);

	/* Step 3: Configure a PALL (precharge all) command */
	Command.CommandMode             = FMC_SDRAM_CMD_PALL;
	Command.CommandTarget           = FMC_SDRAM_CMD_TARGET_BANK2;
	Command.AutoRefreshNumber       = 1;
	Command.ModeRegisterDefinition  = 0;

	/* Send the command */
	HAL_SDRAM_SendCommand(&SdramHandle, &Command, SDRAM_TIMEOUT);

	/* Step 4: Configure an Auto Refresh command */
	Command.CommandMode             = FMC_SDRAM_CMD_AUTOREFRESH_MODE;
	Command.CommandTarget           = FMC_SDRAM_CMD_TARGET_BANK2;
	Command.AutoRefreshNumber       = 4;
	Command.ModeRegisterDefinition  = 0;

	/* Send the command */
	HAL_SDRAM_SendCommand(&SdramHandle, &Command, SDRAM_TIMEOUT);

	/* Step 5: Program the external memory mode register */
	tmpmrd = (uint32_t)SDRAM_MODEREG_BURST_LENGTH_1          |
					 SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL   |
					 SDRAM_MODEREG_CAS_LATENCY_3           |
					 SDRAM_MODEREG_OPERATING_MODE_STANDARD |
					 SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;

	Command.CommandMode             = FMC_SDRAM_CMD_LOAD_MODE;
	Command.CommandTarget           = FMC_SDRAM_CMD_TARGET_BANK2;
	Command.AutoRefreshNumber       = 1;
	Command.ModeRegisterDefinition  = tmpmrd;

	/* Send the command */
	HAL_SDRAM_SendCommand(&SdramHandle, &Command, SDRAM_TIMEOUT);

	/* Step 6: Set the refresh rate counter */
	/* Set the device refresh rate */
	HAL_SDRAM_ProgramRefreshRate(&SdramHandle, REFRESH_COUNT);

	return sdramstatus;
}

static void SPIx_Write(uint16_t Value)
{
  HAL_StatusTypeDef status = HAL_OK;

  status = HAL_SPI_Transmit(&SpiHandle, (uint8_t*) &Value, 1, SPIx_TIMEOUT_MAX);

  /* Check the communication status */
  if(status != HAL_OK)
  {
    /* Re-Initialize the BUS */
    //SPIx_Error();
  }
}

void ili9341_WriteReg(uint8_t Reg)
{
	/* Reset WRX to send command */
	LCD_WRX_LOW();

	/* Reset LCD control line(/CS) and Send command */
	LCD_CS_LOW();
	SPIx_Write(Reg);

	/* Deselect: Chip Select high */
	LCD_CS_HIGH();
}

void ili9341_WriteData(uint16_t RegValue)
{
	/* Set WRX to send data */
	LCD_WRX_HIGH();

	/* Reset LCD control line(/CS) and Send data */
	LCD_CS_LOW();
	SPIx_Write(RegValue);

	/* Deselect: Chip Select high */
	LCD_CS_HIGH();
}

void LCD_IO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

//  if(Is_LCD_IO_Initialized == 0)
//  {
//    Is_LCD_IO_Initialized = 1;

    /* Configure NCS in Output Push-Pull mode */
    LCD_WRX_GPIO_CLK_ENABLE();
    GPIO_InitStructure.Pin     = LCD_WRX_PIN;
    GPIO_InitStructure.Mode    = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pull    = GPIO_NOPULL;
    GPIO_InitStructure.Speed   = GPIO_SPEED_FAST;
    HAL_GPIO_Init(LCD_WRX_GPIO_PORT, &GPIO_InitStructure);

    LCD_RDX_GPIO_CLK_ENABLE();
    GPIO_InitStructure.Pin     = LCD_RDX_PIN;
    GPIO_InitStructure.Mode    = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pull    = GPIO_NOPULL;
    GPIO_InitStructure.Speed   = GPIO_SPEED_FAST;
    HAL_GPIO_Init(LCD_RDX_GPIO_PORT, &GPIO_InitStructure);

    /* Configure the LCD Control pins ----------------------------------------*/
    LCD_NCS_GPIO_CLK_ENABLE();

    /* Configure NCS in Output Push-Pull mode */
    GPIO_InitStructure.Pin     = LCD_NCS_PIN;
    GPIO_InitStructure.Mode    = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pull    = GPIO_NOPULL;
    GPIO_InitStructure.Speed   = GPIO_SPEED_FAST;
    HAL_GPIO_Init(LCD_NCS_GPIO_PORT, &GPIO_InitStructure);

    /* Set or Reset the control line */
    LCD_CS_LOW();
    LCD_CS_HIGH();

    // SPI init
    if(HAL_SPI_GetState(&SpiHandle) == HAL_SPI_STATE_RESET)
    {
		SpiHandle.Instance = LCD_SPIx ;

		SpiHandle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;

		SpiHandle.Init.Direction      = SPI_DIRECTION_2LINES;
		SpiHandle.Init.CLKPhase       = SPI_PHASE_1EDGE;
		SpiHandle.Init.CLKPolarity    = SPI_POLARITY_LOW;
		SpiHandle.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLED;
		SpiHandle.Init.CRCPolynomial  = 7;
		SpiHandle.Init.DataSize       = SPI_DATASIZE_8BIT;
		SpiHandle.Init.FirstBit       = SPI_FIRSTBIT_MSB;
		SpiHandle.Init.NSS            = SPI_NSS_SOFT;
		SpiHandle.Init.TIMode         = SPI_TIMODE_DISABLED;
		SpiHandle.Init.Mode           = SPI_MODE_MASTER;

		GPIO_InitTypeDef   GPIO_InitStructure;

		/* Enable SPIx clock */
		LCD_SPIx_CLK_ENABLE();

		/* Enable DISCOVERY_SPI GPIO clock */
		LCD_SPIx_GPIO_CLK_ENABLE();

		/* configure SPI SCK, MOSI and MISO */
		GPIO_InitStructure.Pin    = (LCD_SPIx_SCK_PIN | LCD_SPIx_MOSI_PIN | LCD_SPIx_MISO_PIN);
		GPIO_InitStructure.Mode   = GPIO_MODE_AF_PP;
		GPIO_InitStructure.Pull   = GPIO_PULLDOWN;
		GPIO_InitStructure.Speed  = GPIO_SPEED_MEDIUM;
		GPIO_InitStructure.Alternate = LCD_SPIx_AF;
		HAL_GPIO_Init(LCD_SPIx_GPIO_PORT, &GPIO_InitStructure);

		HAL_SPI_Init(&SpiHandle);


		/* Configure LCD */
		ili9341_WriteReg(0xCA);
		ili9341_WriteData(0xC3);
		ili9341_WriteData(0x08);
		ili9341_WriteData(0x50);
		ili9341_WriteReg(0xCF);
		ili9341_WriteData(0x00);
		ili9341_WriteData(0xC1);
		ili9341_WriteData(0x30);
		ili9341_WriteReg(0xED);
		ili9341_WriteData(0x64);
		ili9341_WriteData(0x03);
		ili9341_WriteData(0x12);
		ili9341_WriteData(0x81);
		ili9341_WriteReg(0xE8);
		ili9341_WriteData(0x85);
		ili9341_WriteData(0x00);
		ili9341_WriteData(0x78);
		ili9341_WriteReg(0xCB);
		ili9341_WriteData(0x39);
		ili9341_WriteData(0x2C);
		ili9341_WriteData(0x00);
		ili9341_WriteData(0x34);
		ili9341_WriteData(0x02);
		ili9341_WriteReg(0xF7);
		ili9341_WriteData(0x20);
		ili9341_WriteReg(0xEA);
		ili9341_WriteData(0x00);
		ili9341_WriteData(0x00);
		ili9341_WriteReg(0xB1);
		ili9341_WriteData(0x00);
		ili9341_WriteData(0x1B);
		ili9341_WriteReg(0xB6);
		ili9341_WriteData(0x0A);
		ili9341_WriteData(0xA2);
		ili9341_WriteReg(0xC0);
		ili9341_WriteData(0x10);
		ili9341_WriteReg(0xC1);
		ili9341_WriteData(0x10);
		ili9341_WriteReg(0xC5);
		ili9341_WriteData(0x45);
		ili9341_WriteData(0x15);
		ili9341_WriteReg(0xC7);
		ili9341_WriteData(0x90);
		ili9341_WriteReg(0x36);
		ili9341_WriteData(0xC8);
		ili9341_WriteReg(0xF2);
		ili9341_WriteData(0x00);
		ili9341_WriteReg(0xB0);
		ili9341_WriteData(0xC2);
		ili9341_WriteReg(0xB6);
		ili9341_WriteData(0x0A);
		ili9341_WriteData(0xA7);
		ili9341_WriteData(0x27);
		ili9341_WriteData(0x04);

		/* Colomn address set */
		ili9341_WriteReg(0x2A);
		ili9341_WriteData(0x00);
		ili9341_WriteData(0x00);
		ili9341_WriteData(0x00);
		ili9341_WriteData(0xEF);
		/* Page address set */
		ili9341_WriteReg(0x2B);
		ili9341_WriteData(0x00);
		ili9341_WriteData(0x00);
		ili9341_WriteData(0x01);
		ili9341_WriteData(0x3F);
		ili9341_WriteReg(0xF6);
		ili9341_WriteData(0x01);
		ili9341_WriteData(0x00);
		ili9341_WriteData(0x06);

		ili9341_WriteReg(0x2C);
		wait_ms(200);

		ili9341_WriteReg(0x26);
		ili9341_WriteData(0x01);

		ili9341_WriteReg(0xE0);
		ili9341_WriteData(0x0F);
		ili9341_WriteData(0x29);
		ili9341_WriteData(0x24);
		ili9341_WriteData(0x0C);
		ili9341_WriteData(0x0E);
		ili9341_WriteData(0x09);
		ili9341_WriteData(0x4E);
		ili9341_WriteData(0x78);
		ili9341_WriteData(0x3C);
		ili9341_WriteData(0x09);
		ili9341_WriteData(0x13);
		ili9341_WriteData(0x05);
		ili9341_WriteData(0x17);
		ili9341_WriteData(0x11);
		ili9341_WriteData(0x00);
		ili9341_WriteReg(0xE1);
		ili9341_WriteData(0x00);
		ili9341_WriteData(0x16);
		ili9341_WriteData(0x1B);
		ili9341_WriteData(0x04);
		ili9341_WriteData(0x11);
		ili9341_WriteData(0x07);
		ili9341_WriteData(0x31);
		ili9341_WriteData(0x33);
		ili9341_WriteData(0x42);
		ili9341_WriteData(0x05);
		ili9341_WriteData(0x0C);
		ili9341_WriteData(0x0A);
		ili9341_WriteData(0x28);
		ili9341_WriteData(0x2F);
		ili9341_WriteData(0x0F);

		ili9341_WriteReg(0x11);
		wait_ms(200);
		ili9341_WriteReg(0x29);
		/* GRAM start writing */
		ili9341_WriteReg(0x2C);
		}
}


static GFXINLINE void init_board(GDisplay* g) {

	// As we are not using multiple displays we set g->board to NULL as we don't use it.
	g->board = 0;

	switch(g->controllerdisplay) {
	case 0:
		configureLcdClock();

		LCD_MspInit();

		LCD_IO_Init();

		SDRAM_Init();

		break;
	}
}

static GFXINLINE void post_init_board(GDisplay* g)
{
	(void)g;
}

static GFXINLINE void set_backlight(GDisplay* g, uint8_t percent)
{
	(void)g;
	(void)percent;
}

#endif /* _GDISP_LLD_BOARD_H */
