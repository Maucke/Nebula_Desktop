/**
  ******************************************************************************
  * File Name          : USART.c
  * Description        : This file provides code for the configuration
  *                      of the USART instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "usart.h"

/* USER CODE BEGIN 0 */
#include <string.h>
#include "sys.h"
#include "main.h"
#include "motion.h"
#include <stdio.h>
#include "stmflash.h"
/* USER CODE END 0 */

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart3;
DMA_HandleTypeDef hdma_usart1_rx;
DMA_HandleTypeDef hdma_usart1_tx;
DMA_HandleTypeDef hdma_usart3_rx;

/* USART1 init function */

void MX_USART1_UART_Init(void)
{

  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }

}
/* USART3 init function */

void MX_USART3_UART_Init(void)
{

  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspInit 0 */

  /* USER CODE END USART1_MspInit 0 */
    /* USART1 clock enable */
    __HAL_RCC_USART1_CLK_ENABLE();
  
    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART1 GPIO Configuration    
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USART1 DMA Init */
    /* USART1_RX Init */
    hdma_usart1_rx.Instance = DMA1_Channel5;
    hdma_usart1_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_usart1_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart1_rx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart1_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart1_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart1_rx.Init.Mode = DMA_NORMAL;
    hdma_usart1_rx.Init.Priority = DMA_PRIORITY_HIGH;
    if (HAL_DMA_Init(&hdma_usart1_rx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(uartHandle,hdmarx,hdma_usart1_rx);

    /* USART1_TX Init */
    hdma_usart1_tx.Instance = DMA1_Channel4;
    hdma_usart1_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_usart1_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart1_tx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart1_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart1_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart1_tx.Init.Mode = DMA_NORMAL;
    hdma_usart1_tx.Init.Priority = DMA_PRIORITY_LOW;
    if (HAL_DMA_Init(&hdma_usart1_tx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(uartHandle,hdmatx,hdma_usart1_tx);

    /* USART1 interrupt Init */
    HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspInit 1 */

  /* USER CODE END USART1_MspInit 1 */
  }
  else if(uartHandle->Instance==USART3)
  {
  /* USER CODE BEGIN USART3_MspInit 0 */

  /* USER CODE END USART3_MspInit 0 */
    /* USART3 clock enable */
    __HAL_RCC_USART3_CLK_ENABLE();
  
    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**USART3 GPIO Configuration    
    PB10     ------> USART3_TX
    PB11     ------> USART3_RX 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* USART3 DMA Init */
    /* USART3_RX Init */
    hdma_usart3_rx.Instance = DMA1_Channel3;
    hdma_usart3_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_usart3_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart3_rx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart3_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart3_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart3_rx.Init.Mode = DMA_NORMAL;
    hdma_usart3_rx.Init.Priority = DMA_PRIORITY_LOW;
    if (HAL_DMA_Init(&hdma_usart3_rx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(uartHandle,hdmarx,hdma_usart3_rx);

    /* USART3 interrupt Init */
    HAL_NVIC_SetPriority(USART3_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART3_IRQn);
  /* USER CODE BEGIN USART3_MspInit 1 */

  /* USER CODE END USART3_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspDeInit 0 */

  /* USER CODE END USART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();
  
    /**USART1 GPIO Configuration    
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX 
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9|GPIO_PIN_10);

    /* USART1 DMA DeInit */
    HAL_DMA_DeInit(uartHandle->hdmarx);
    HAL_DMA_DeInit(uartHandle->hdmatx);

    /* USART1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspDeInit 1 */

  /* USER CODE END USART1_MspDeInit 1 */
  }
  else if(uartHandle->Instance==USART3)
  {
  /* USER CODE BEGIN USART3_MspDeInit 0 */

  /* USER CODE END USART3_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART3_CLK_DISABLE();
  
    /**USART3 GPIO Configuration    
    PB10     ------> USART3_TX
    PB11     ------> USART3_RX 
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_10|GPIO_PIN_11);

    /* USART3 DMA DeInit */
    HAL_DMA_DeInit(uartHandle->hdmarx);

    /* USART3 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART3_IRQn);
  /* USER CODE BEGIN USART3_MspDeInit 1 */

  /* USER CODE END USART3_MspDeInit 1 */
  }
} 

/* USER CODE BEGIN 1 */
int std::fputc(int ch, FILE *f)
{
	HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xffff);
	return 1;
}


uint8_t Nix2Num(uint8_t Input)
{
	switch(Input)
	{
		case 0x3f:return 0;
		case 0x06:return 1;
		case 0x5b:return 2;
		case 0x4f:return 3;
		case 0x66:return 4;
		case 0x6d:return 5;
		case 0x7d:return 6;
		case 0x07:return 7;
		case 0x7f:return 8;
		case 0x6f:return 9;
		default:return 0xff;
	}
}

CLOCK_MSG Clock_Msg;
DEVICE_CMD Device_Cmd={1,14,6,100,6,250,1,170,250,1,5};
DEVICE_MSG Device_Msg;
DEVICE_STR Device_Str;
WIFI_MSG WiFi_Msg;

const char *Week[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };

void ConvertData(void)
{
	if(Device_Msg.cputemp)
	{
	sprintf(Device_Str.cputemp,"%02d",Device_Msg.cputemp/10);
	sprintf(Device_Str.cputempf,"%1d",Device_Msg.cputemp%10);
	}
	if(Device_Msg.cpuclock)
	sprintf(Device_Str.cpuclock,"%dMhz ",Device_Msg.cpuclock);
	sprintf(Device_Str.cpuload,"%02.1f%%  ",(double)Device_Msg.cpuload/10);
	if(Device_Msg.cpufan)
	sprintf(Device_Str.cpufan,"%dRpm ",Device_Msg.cpufan);
	
	if(Device_Msg.gputemp)
	sprintf(Device_Str.gputemp,"%02d.%1d$ ",Device_Msg.gputemp/10,Device_Msg.gputemp%10);
	if(Device_Msg.gpuclock)
	sprintf(Device_Str.gpuclock,"%dMhz ",Device_Msg.gpuclock);
	sprintf(Device_Str.gpuload,"%02.1f%%  ",(double)Device_Msg.gpuload/10);
	if(Device_Msg.gpufan)
	sprintf(Device_Str.gpufan,"%dRpm ",Device_Msg.gpufan);
	
	if(Device_Msg.maintemp)
	sprintf(Device_Str.maintemp,"%03.1f$ ",(double)Device_Msg.maintemp/10);
	if(Device_Msg.mainfan)
	sprintf(Device_Str.mainfan,"%dRpm ",Device_Msg.mainfan);
	
	sprintf(Device_Str.ramload,"%02.1f%% ",(double)Device_Msg.ramload/10);
	
	if(Device_Msg.ramusrdata)
	sprintf(Device_Str.ramusrdata,"%d",Device_Msg.ramusrdata);
	
	if(Device_Msg.cpufan)	
	sprintf(Device_Str.ncpufan,"%04d",Device_Msg.cpufan);
	if(Device_Msg.cpuclock)
	sprintf(Device_Str.ncpuclock,"%04d",Device_Msg.cpuclock);
	if(Device_Msg.gpufan)
	sprintf(Device_Str.ngpufan,"%04d",Device_Msg.gpufan);
	if(Device_Msg.gputemp)
	sprintf(Device_Str.ngputemp,"%02d.%1d",Device_Msg.gputemp/10,Device_Msg.gputemp%10);
	
	
	if(Device_Msg.cputemp)
		sprintf(Device_Str.vcputemp,"%03d#",Device_Msg.cputemp);	
	if(Device_Msg.gputemp)
		sprintf(Device_Str.vgputemp,"%03d#",Device_Msg.gputemp);	
	
//	sprintf(Device_Str.vhour,"%02d",Device_Msg.uarthour);	
//	sprintf(Device_Str.vmin,"%02d",Device_Msg.uartminute);	
//	sprintf(Device_Str.vsec,"%02d",Device_Msg.uartsecond);	
//	sprintf(Device_Str.date,"%s. %02d-%02d",Week[Device_Msg.uartweek],Device_Msg.uartmonth,Device_Msg.uartday);	

}
void InitWifi(void)
{
	sprintf(WiFi_Msg.weather,"Unknow");
	WiFi_Msg.weathernum = 67;
	
	sprintf(WiFi_Msg.temp,"--$");
	sprintf(WiFi_Msg.utemp,"--");
	sprintf(WiFi_Msg.uhumidity,"--");
	sprintf(WiFi_Msg.humidity,"--%%");
	sprintf(WiFi_Msg.winddir,"Unknow");
	sprintf(WiFi_Msg.windpw,"SPD:--m/s");
	sprintf(WiFi_Msg.reporttime,"No Information");
	
	WiFi_Msg.weather1num = 67;
	sprintf(WiFi_Msg.week1,"Unknow");
	sprintf(WiFi_Msg.weather1,"Unknow");
	sprintf(WiFi_Msg.temp1,"--$");
	sprintf(WiFi_Msg.ntemp1,"--$");
	sprintf(WiFi_Msg.utemp1,"--");
	sprintf(WiFi_Msg.untemp1,"--");
	
	WiFi_Msg.weather2num = 67;
	sprintf(WiFi_Msg.week2,"Unknow");
	sprintf(WiFi_Msg.weather2,"Unknow");
	sprintf(WiFi_Msg.temp2,"--$");
	sprintf(WiFi_Msg.ntemp2,"--$");
	sprintf(WiFi_Msg.utemp2,"--");
	sprintf(WiFi_Msg.untemp2,"--");
	
	WiFi_Msg.weather3num = 67;
	sprintf(WiFi_Msg.week3,"Unknow");
	sprintf(WiFi_Msg.weather3,"Unknow");
	sprintf(WiFi_Msg.temp3,"--$");
	sprintf(WiFi_Msg.ntemp3,"--$");
	sprintf(WiFi_Msg.utemp3,"--");
	sprintf(WiFi_Msg.untemp3,"--");
	
}
void InitData(void)
{
	sprintf(Device_Str.cputemp,"--.-$ ");
	sprintf(Device_Str.cpuclock,"----Mhz ");
	sprintf(Device_Str.cpuload,"--.-%%  ");
	sprintf(Device_Str.cpufan,"----Rpm ");
	
	sprintf(Device_Str.gputemp,"--.-$ ");
	sprintf(Device_Str.gpuclock,"----Mhz ");
	sprintf(Device_Str.gpuload,"--.-%%  ");
	sprintf(Device_Str.gpufan,"----Rpm ");
	
	sprintf(Device_Str.maintemp,"--.-$ ");
	sprintf(Device_Str.mainfan,"----Rpm ");
	
	sprintf(Device_Str.ramload,"--.-%% ");
	sprintf(Device_Str.ramusrdata,"----");
	
	sprintf(Device_Str.ngputemp,"--.-");	
	sprintf(Device_Str.ncpuclock,"----");	
	sprintf(Device_Str.ngpufan,"----");	
	sprintf(Device_Str.ncpufan,"----");	
	
	
//	sprintf(Device_Str.vtime,"--:--");
//	sprintf(Device_Str.vhour,"--");	
//	sprintf(Device_Str.vmin,"--");	
//	sprintf(Device_Str.vsec,"--");	
//	sprintf(Device_Str.date,"--Unkown--");	

	memset(&Device_Msg,0,sizeof(Device_Msg));
}

void Judge_Mode()
{
//	static u8 normalcount=6,gamecount=6;
//	if(Device_Msg.gpuload>800)
//	{
//		gamecount ++;
//		if(gamecount>=10)
//		{
//			gamecount = 10;Display_Mode = MODE_GAME;
//			normalcount = 0;
//		}
//	}
//	else if(Device_Msg.gpuload<200)
//	{
//		normalcount ++;
//		if(normalcount>=10)
//		{
//			normalcount = 10;
//			gamecount = 0;
//		}
//	}
	Display_Mode = MODE_MENU;
}
uint8_t Uart_Recv1_Buf[Uart_Max_Length] = {0};
uint16_t Uart_Recv1_Length = 0;
uint8_t Uart_Overflow1_Flag = False;
uint8_t Uart_Recv3_Buf[Uart_Max_Length] = {0};
uint16_t Uart_Recv3_Length = 0;
uint8_t Uart_Overflow3_Flag = False;
u8 WifiActive = True;
char Device_Name[20] = "Nebula\0\0\0\0\0\0";

u8 ReponseID[40]={0xFF,0x55,'O','K'};

void AnalysisComputermsg(uint8_t *Buf)
{
	static u8 Timefix = 0;
	int i;
	if(Buf[0] == 0xFF &&Buf[1] == 0x55)
	{
		if(Buf[4] == 0x2)
		{
			switch (MAKEWORD(Buf[3], Buf[2]))
			{
			case CPU_Temp:
				Device_Msg.cputemp = MAKEWORD(Buf[6],Buf[5]);
				break;
			case CPU_Clock:
				Device_Msg.cpuclock = MAKEWORD(Buf[6],Buf[5]);
				break;
			case CPU_Load:
				Device_Msg.cpuload = MAKEWORD(Buf[6],Buf[5]);
				break;
			case CPU_Fan:
				Device_Msg.cpufan = MAKEWORD(Buf[6],Buf[5]);
				break;
			case CPU_POWER:
				Device_Msg.cpupower = MAKEWORD(Buf[6],Buf[5]);
				break;

			case GPU_Temp:
				Device_Msg.gputemp = MAKEWORD(Buf[6],Buf[5]);
				break;
			case GPU_Clock:
				Device_Msg.gpuclock = MAKEWORD(Buf[6],Buf[5]);
				break;
			case GPU_Load:
				Device_Msg.gpuload = MAKEWORD(Buf[6],Buf[5]);
				break;
			case GPU_Fan:
				Device_Msg.gpufan = MAKEWORD(Buf[6],Buf[5]);
				break;


			case Main_Temp:
				Device_Msg.maintemp = MAKEWORD(Buf[6],Buf[5]);
				break;
			case Main_Fan:
				Device_Msg.mainfan = MAKEWORD(Buf[6],Buf[5]);
				break;
			case Main_Vol:
				Device_Msg.mainvoltage = MAKEWORD(Buf[6],Buf[5]);
				break;

			case RAM_Load:
				Device_Msg.ramload = MAKEWORD(Buf[6],Buf[5]);
				break;
			case RAM_Data:
				Device_Msg.ramusrdata = MAKEWORD(Buf[6],Buf[5]);
				break;

			case HDD_Load:
				Device_Msg.hddload = MAKEWORD(Buf[6],Buf[5]);
				break;
			case HDD_Temp:
				Device_Msg.hddtemp = MAKEWORD(Buf[6],Buf[5]);
				break;

			case Uart_Year:
				Device_Msg.uartyear = MAKEWORD(Buf[6],Buf[5]);
				break;
			case Uart_Month:
				Device_Msg.uartmonth = MAKEWORD(Buf[6],Buf[5]);
				break;
			case Uart_Day:
				Device_Msg.uartday = MAKEWORD(Buf[6],Buf[5]);
				break;
			case Uart_Week:
				Device_Msg.uartweek = MAKEWORD(Buf[6],Buf[5]);
				break;
			case Uart_Hour:
				Device_Msg.uarthour = MAKEWORD(Buf[6],Buf[5]);
				break;
			case Uart_Minute:
				Device_Msg.uartminute = MAKEWORD(Buf[6],Buf[5]);
				break;
			case Uart_Second:
				Device_Msg.uartsecond = MAKEWORD(Buf[6],Buf[5]);
				break;
			case End_Frame_ADDR:
				if(MAKEWORD(Buf[6],Buf[5]) == 0x5A5A)
				{
					ConvertData();		
					Uart_Overflow1_Flag = True;
					
					
					if(set.autotimeset)
					if(Timefix++ == 1||Timefix == 5)
					{
						own_sec = Device_Msg.uartsecond;
						own_min = Device_Msg.uartminute;
						own_hour = Device_Msg.uarthour;
					}
					CptOnline = 2;
//					if(Device_Cmd.commandmode == 1) 
//						Judge_Mode();
//					else if(Display_Mode == MODE_OFFLINE)
//						Display_Mode = MODE_DEFALUT;
				}break;
			case 0x3F3F:
//				STMFLASH_Read(FLASH_NAME_ADDR,(u16*)Device_Name,20);
				ReponseID[2] = (Buf[5] & 0x5A) | (Buf[6] & 0xA5);
				ReponseID[3] = (Buf[5] ^ 0x57) | (Buf[6] & 0x57);
				ReponseID[4] = cont_str(Device_Name);
				for(i=0;i<ReponseID[4];i++)
					ReponseID[5+i] = Device_Name[i];
				HAL_UART_Transmit(&huart1,ReponseID,ReponseID[4]+5,0xffff);
				SendCommand();
				break;
			}
		}
	}
}

void SendCommand(void)
{
	u8 Buf[23] = {0xFF,0x55,0x80,0x0A,18};
	Buf[5] = Device_Cmd.commandmode>>8;
	Buf[6] = Device_Cmd.commandmode&0xff;
	
	Buf[7] = Device_Cmd.commandmotion>>8;
	Buf[8] = Device_Cmd.commandmotion&0xff;
	
	Buf[9] = Device_Cmd.commandstyle>>8;
	Buf[10] = Device_Cmd.commandstyle&0xff;
	
	Buf[11] = Device_Cmd.commandspeed>>8; 
	Buf[12] = Device_Cmd.commandspeed&0xff;
	
	Buf[13] = Device_Cmd.commandbrightness>>8;
	Buf[14] = Device_Cmd.commandbrightness&0xff;
	
	Buf[15] = Device_Cmd.commandset>>8;
	Buf[16] = Device_Cmd.commandset&0xff;
	
	Buf[17] = Device_Cmd.commandrgbmode>>8; 
	Buf[18] = Device_Cmd.commandrgbmode&0xff;
	
	Buf[19] = Device_Cmd.commandrgbcolor>>8;
	Buf[20] = Device_Cmd.commandrgbcolor&0xff;
	
	Buf[21] = Device_Cmd.commandrgbbrightness>>8;
	Buf[22] = Device_Cmd.commandrgbbrightness&0xff;
	if(CptOnline)
		HAL_UART_Transmit(&huart1,Buf,Buf[4]+5,0xffff);
}

u8 SaveFlag = False;

void AnalysisCommand(uint8_t *Buf)
{
//	u16 Temp;
	int i;
	if(Buf[0] == 0xFF &&Buf[1] == 0x55)
	{
//		if(Buf[4] == 0x2)
		{
			switch (MAKEWORD(Buf[3], Buf[2]))
			{
				case Command_Mode:
						Device_Cmd.commandmode = MAKEWORD(Buf[6],Buf[5]); 
						if(Device_Cmd.commandmode > 1 && Display_Mode != MODE_MENU) 
						{
							if(Device_Cmd.commandmode == 2)
								Display_Mode = DATA_THEME;
							else
								Display_Mode = Device_Cmd.commandmode;
						}
						else if(Display_Mode == MODE_OFFLINE)
							Display_Mode = DATA_THEME;
				break;
				case Command_Motion:
					if(Device_Cmd.commandmotion != MAKEWORD(Buf[6],Buf[5]))
					{
						Device_Cmd.commandmotion = MAKEWORD(Buf[6],Buf[5]);
						SaveFlag = True;
					}break;
				case Command_Style:
					if(Device_Cmd.commandstyle != MAKEWORD(Buf[6],Buf[5]))
					{
						Device_Cmd.commandstyle = MAKEWORD(Buf[6],Buf[5]);
//						SaveFlag = True;
					}break;
				case Command_Speed:
					if(Device_Cmd.commandspeed != MAKEWORD(Buf[6],Buf[5]))
					{
						Device_Cmd.commandspeed = MAKEWORD(Buf[6],Buf[5]);
//						SaveFlag = True;
					}break;
				case Command_Brightness:
					if(Device_Cmd.commandbrightness != MAKEWORD(Buf[6],Buf[5]))
					{
						Device_Cmd.commandbrightness = MAKEWORD(Buf[6],Buf[5]);
//						SaveFlag = True;
					}break;
				case Command_Set:
					if(Device_Cmd.commandset != MAKEWORD(Buf[6],Buf[5]))
					{
						Device_Cmd.commandset = MAKEWORD(Buf[6],Buf[5]);
						SaveFlag = True;
					}break;
				case Command_RGBMode:
					if(Device_Cmd.commandrgbmode != MAKEWORD(Buf[6],Buf[5]))
					{
						Device_Cmd.commandrgbmode = MAKEWORD(Buf[6],Buf[5]);
						SaveFlag = True;
					}break;
				case Command_RGBBrightness:
					if(Device_Cmd.commandrgbbrightness != MAKEWORD(Buf[6],Buf[5]))
					{
						Device_Cmd.commandrgbbrightness = MAKEWORD(Buf[6],Buf[5]);
						SaveFlag = True;
					}break;
				case Command_RGBColor:
					if(Device_Cmd.commandrgbcolor != MAKEWORD(Buf[6],Buf[5]))
					{
						Device_Cmd.commandrgbcolor = MAKEWORD(Buf[6],Buf[5]);
						SaveFlag = True;
					}break;
				case Command_TOPTHEME:
					if(Device_Cmd.commandtoptheme != MAKEWORD(Buf[6],Buf[5]))
					{
						Device_Cmd.commandtoptheme = MAKEWORD(Buf[6],Buf[5]);
						if(Device_Cmd.commandtoptheme<2)
							printf("Current top %d\r\n",Device_Cmd.commandtoptheme);
						else
							printf("Current top 1\r\n");
						SaveFlag = True;
					}break;
				case Command_LOGOTHEME:
					if(Device_Cmd.commandlogotheme != MAKEWORD(Buf[6],Buf[5]))
					{
						Device_Cmd.commandlogotheme = MAKEWORD(Buf[6],Buf[5]);
						if(Device_Cmd.commandlogotheme<6)
							printf("Current logo %d\r\n",Device_Cmd.commandlogotheme);
						else
							printf("Current logo 5\r\n");
						SaveFlag = True;
					}break;
				case Command_DEVICENAME:
					memset(&Device_Name,0,sizeof(Device_Name));
				
					for(i=0;i<Buf[4];i++) Device_Name[i] = Buf[i + 5];
					SaveFlag = True;
					break;
			}
		}
	}
}

void AnalysisComputername(uint8_t *Buf)
{
	u8 i;
	if(Buf[0] == 0xFF &&Buf[1] == 0x55)
	{
		if(Buf[4] > 0x2)
		{
			switch (MAKEWORD(Buf[3], Buf[2]))
			{
			case 0x101:for(i=0;i<Buf[4];i++) Device_Msg.cpuname[i] = Buf[i + 5];break;
			case 0x102:for(i=0;i<Buf[4];i++) Device_Msg.gpuname[i] = Buf[i + 5];break;
			case 0x103:for(i=0;i<Buf[4];i++) Device_Msg.mainname[i] = Buf[i + 5];break;
			}
		}
	}
}


void ClearFFT(void)
{
	int i;
	for(i=0;i<Uart_FFT_Length;i++) 
		Device_Msg.fft[i] = 0;
	
	Device_Msg.leftvol = 0;
	Device_Msg.rightvol = 0;
}


void AnalysisFFT(uint8_t *Buf)
{
	u16 i;
	if(Buf[0] == 0xFF &&Buf[1] == 0x55)
	{
		if(Buf[4] >= 0x2)
		{
			switch (MAKEWORD(Buf[3], Buf[2]))
			{
				case FFT_Data:for(i=0;i<Buf[4];i++) Device_Msg.fft[i] = Buf[i + 5];
				CptOnline = 3;
					break;
				case Left_Vol:
					Device_Msg.leftvol = MAKEWORD(Buf[6],Buf[5]);break;
				case Right_Vol:
					Device_Msg.rightvol = MAKEWORD(Buf[6],Buf[5]);break;
			}
			Uart_Overflow1_Flag = True;
		}
	}
}

#define SAVESIZE 128

u8 Flash_SaveCMD[SAVESIZE];
void Tranfcmd(void)
{
	int i;
	Flash_SaveCMD[0] = Device_Cmd.commandmode>>8;
	Flash_SaveCMD[1] = Device_Cmd.commandmode&0xff;
	
	Flash_SaveCMD[2] = Device_Cmd.commandmotion>>8;
	Flash_SaveCMD[3] = Device_Cmd.commandmotion&0xff;
	
	Flash_SaveCMD[4] = Device_Cmd.commandstyle>>8;
	Flash_SaveCMD[5] = Device_Cmd.commandstyle&0xff;
	
	Flash_SaveCMD[6] = Device_Cmd.commandspeed>>8; 
	Flash_SaveCMD[7] = Device_Cmd.commandspeed&0xff;
	
	Flash_SaveCMD[8] = Device_Cmd.commandbrightness>>8;
	Flash_SaveCMD[9] = Device_Cmd.commandbrightness&0xff;
	
	Flash_SaveCMD[10] = Device_Cmd.commandset>>8;
	Flash_SaveCMD[11] = Device_Cmd.commandset&0xff;
	
	Flash_SaveCMD[12] = Device_Cmd.commandrgbmode>>8; 
	Flash_SaveCMD[13] = Device_Cmd.commandrgbmode&0xff;
	
	Flash_SaveCMD[14] = Device_Cmd.commandrgbcolor>>8;
	Flash_SaveCMD[15] = Device_Cmd.commandrgbcolor&0xff;
	
	Flash_SaveCMD[16] = Device_Cmd.commandrgbbrightness>>8;
	Flash_SaveCMD[17] = Device_Cmd.commandrgbbrightness&0xff;
	
	Flash_SaveCMD[18] = Device_Cmd.commandtoptheme>>8;
	Flash_SaveCMD[19] = Device_Cmd.commandtoptheme&0xff;
	
	Flash_SaveCMD[20] = Device_Cmd.commandlogotheme>>8;
	Flash_SaveCMD[21] = Device_Cmd.commandlogotheme&0xff;
	
	for(i=0;i<6;i++)
		Flash_SaveCMD[22+i] = set.addr[i];
	for(i=0;i<10;i++)
		Flash_SaveCMD[32+i] = set.uid[i];
		
	Flash_SaveCMD[28] = set.autotimeset;
	Flash_SaveCMD[42] = set.autoswdis;
	Flash_SaveCMD[43] = set.fanswdis;
	Flash_SaveCMD[44] = set.autoswtime;
	Flash_SaveCMD[45] = DATA_THEME;
	
	for(i=0;i<20;i++)
		Flash_SaveCMD[48+i] = Device_Name[i];
	STMFLASH_Write(FLASH_SAVE_ADDR,(u16*)Flash_SaveCMD,SAVESIZE);
//	STMFLASH_Write(FLASH_NAME_ADDR,(u16*)Device_Name,20);
}

#define VERIF 0x5A

void Recvcmd(void)
{
	int i;
	
//	STMFLASH_Read(FLASH_NAME_ADDR,(u16*)Device_Name,20);
	STMFLASH_Read(FLASH_SAVE_ADDR,(u16*)Flash_SaveCMD,SAVESIZE);
	if(Flash_SaveCMD[31]!=VERIF)
	{
		Flash_SaveCMD[31]=VERIF;
		Tranfcmd();
//		STMFLASH_Write(FLASH_NAME_ADDR,(u16*)Device_Name,20);
		
		STMFLASH_Read(FLASH_SAVE_ADDR,(u16*)Flash_SaveCMD,64);
	}
	Device_Cmd.commandmotion = MAKEWORD(Flash_SaveCMD[3],Flash_SaveCMD[2]);
	Device_Cmd.commandstyle = MAKEWORD(Flash_SaveCMD[5],Flash_SaveCMD[4]);
	Device_Cmd.commandspeed = MAKEWORD(Flash_SaveCMD[7],Flash_SaveCMD[6]);
	Device_Cmd.commandbrightness = MAKEWORD(Flash_SaveCMD[9],Flash_SaveCMD[8]);
	Device_Cmd.commandset = MAKEWORD(Flash_SaveCMD[11],Flash_SaveCMD[10]);

	Device_Cmd.commandrgbmode = MAKEWORD(Flash_SaveCMD[13],Flash_SaveCMD[12]);
	Device_Cmd.commandrgbcolor = MAKEWORD(Flash_SaveCMD[15],Flash_SaveCMD[14]);
	Device_Cmd.commandrgbbrightness = MAKEWORD(Flash_SaveCMD[17],Flash_SaveCMD[16]);
	Device_Cmd.commandtoptheme = MAKEWORD(Flash_SaveCMD[19],Flash_SaveCMD[18]);
	Device_Cmd.commandlogotheme = MAKEWORD(Flash_SaveCMD[21],Flash_SaveCMD[20]);
	for(i=0;i<6;i++)
		set.addr[i] = Flash_SaveCMD[22+i];
	for(i=0;i<10;i++)
		set.uid[i] = Flash_SaveCMD[32+i];
	set.autotimeset = Flash_SaveCMD[28];		
	set.autoswdis = Flash_SaveCMD[42];
	set.fanswdis = Flash_SaveCMD[43];
	set.autoswtime = Flash_SaveCMD[44];
	DATA_THEME = Flash_SaveCMD[45];
	for(i=0;i<20;i++)
		Device_Name[i] = Flash_SaveCMD[48+i];
}

void delay_ms(unsigned int Ms)
{
	unsigned char i, j;
	do
	{
		i = 15;
		j = 90;
		do
		{
			while (--j);
		} while (--i);
	}while(--Ms);
}
 

u8 Uartdata[7]={0xFF,0x55,0,0,0x02,0,0};

void UsartCommand(UART_HandleTypeDef *huart,u16 Addr,u16 Data)
{
	Uartdata[2] = (Addr>>8)&0xFF;
	Uartdata[3] = Addr&0xFF;
	
	Uartdata[5] = (Data>>8)&0xFF;
	Uartdata[6] = Data&0xFF;
	HAL_UART_Transmit(huart,Uartdata,7, 0xffff);
	delay_ms(5);
}

int cont_str(char *s)
{
	int i = 0;      
	while ( s[++i] != '\0')   ;
	return i;
}

u8 UartPrint[255]={0xFF,0x55,0,0,0,0,0};
void UsartPrint(UART_HandleTypeDef *huart,u16 Addr,char *Data)
{
	u8 i,Length;
	UartPrint[2] = (Addr>>8)&0xFF;
	UartPrint[3] = Addr&0xFF;
	
	Length = cont_str(Data) ;
	UartPrint[4] = Length;
	for(i=0;i<Length;i++)
		UartPrint[5+i] = Data[i];
	HAL_UART_Transmit(huart,UartPrint,Length+5, 0xffff);
}

void UsartPrintuid(UART_HandleTypeDef *huart,u16 Addr,char *Data)
{
	u8 i;
	u8 dlt = 0;
	UartPrint[2] = (Addr>>8)&0xFF;
	UartPrint[3] = Addr&0xFF;

	for(i=0;i<255;i++)
	{
		if(Data[i] == '-')
		{
			dlt++;
		}
		else if(Data[i] != 0)
		{
			UartPrint[5+i-dlt] = Data[i];
		}
		else
		{
			break;
		}
		
	}
	UartPrint[4] = i-dlt;

//	UartPrint[UartPrint[4]+4] = 0;
	HAL_UART_Transmit(huart,UartPrint,UartPrint[4]+5, 0xffff);
}


u8 UartClear[]={0xFF,0x55,0xC0,0x02};
void UsartClear(UART_HandleTypeDef *huart)
{
	HAL_UART_Transmit(huart,UartClear,5, 0xffff);
	delay_ms(5);
}

void AnalysisWiFiString(uint8_t *Buf)
{
	u8 i;
	if(Buf[0] == 0xFF &&Buf[1] == 0x55)
	{
		switch (MAKEWORD(Buf[3], Buf[2]))
		{
		case ESP_Weather:memset(&WiFi_Msg.weather,0,sizeof(WiFi_Msg.weather));for(i=0;i<Buf[4];i++) WiFi_Msg.weather[i] = Buf[i + 5];break;
		case ESP_Temp:memset(&WiFi_Msg.temp,0,sizeof(WiFi_Msg.temp));memset(&WiFi_Msg.utemp,0,sizeof(WiFi_Msg.utemp));for(i=0;i<Buf[4];i++) WiFi_Msg.utemp[i] = Buf[i + 5];
			sprintf(WiFi_Msg.temp,"%s$",WiFi_Msg.utemp);break;
		case ESP_Humi:memset(&WiFi_Msg.humidity,0,sizeof(WiFi_Msg.humidity));memset(&WiFi_Msg.uhumidity,0,sizeof(WiFi_Msg.uhumidity));
			for(i=0;i<Buf[4];i++) WiFi_Msg.uhumidity[i] = Buf[i + 5];
			sprintf(WiFi_Msg.humidity,"%s%%",WiFi_Msg.uhumidity);break;
		case ESP_Wind_Dir:memset(&WiFi_Msg.winddir,0,sizeof(WiFi_Msg.winddir));for(i=0;i<Buf[4];i++) WiFi_Msg.winddir[i] = Buf[i + 5];break;
		case ESP_Wind_Pw:memset(&WiFi_Msg.windpw,0,sizeof(WiFi_Msg.windpw));for(i=0;i<Buf[4];i++) WiFi_Msg.windpw[i] = Buf[i + 5];
			sprintf(WiFi_Msg.windpw,"SPD:<%cm/s",WiFi_Msg.windpw[0]);break;
		case ESP_Report_Tm:memset(&WiFi_Msg.reporttime,0,sizeof(WiFi_Msg.reporttime));for(i=0;i<Buf[4];i++) WiFi_Msg.reporttime[i] = Buf[i + 5];break;
			
//		case ESP_D1_Weeek:memset(&WiFi_Msg.week1,0,sizeof(WiFi_Msg.week1));for(i=0;i<Buf[4];i++) WiFi_Msg.week1[i] = Buf[i + 5];break;
		case ESP_D1_Weather:memset(&WiFi_Msg.weather1,0,sizeof(WiFi_Msg.weather1));for(i=0;i<Buf[4];i++) WiFi_Msg.weather1[i] = Buf[i + 5];break;
		case ESP_D1_Temp:memset(&WiFi_Msg.temp1,0,sizeof(WiFi_Msg.temp1));memset(&WiFi_Msg.utemp1,0,sizeof(WiFi_Msg.utemp1));for(i=0;i<Buf[4];i++) WiFi_Msg.utemp1[i] = Buf[i + 5];
			sprintf(WiFi_Msg.temp1,"%s$",WiFi_Msg.utemp1);break;
		case ESP_D1_NTemp:memset(&WiFi_Msg.ntemp1,0,sizeof(WiFi_Msg.ntemp1));memset(&WiFi_Msg.untemp1,0,sizeof(WiFi_Msg.untemp1));for(i=0;i<Buf[4];i++) WiFi_Msg.untemp1[i] = Buf[i + 5];
			sprintf(WiFi_Msg.ntemp1,"%s$",WiFi_Msg.untemp1);break;
			
//		case ESP_D2_Weeek:memset(&WiFi_Msg.week2,0,sizeof(WiFi_Msg.week2));for(i=0;i<Buf[4];i++) WiFi_Msg.week2[i] = Buf[i + 5];break;
		case ESP_D2_Weather:memset(&WiFi_Msg.weather2,0,sizeof(WiFi_Msg.weather2));for(i=0;i<Buf[4];i++) WiFi_Msg.weather2[i] = Buf[i + 5];break;
		case ESP_D2_Temp:memset(&WiFi_Msg.temp2,0,sizeof(WiFi_Msg.temp2));memset(&WiFi_Msg.utemp2,0,sizeof(WiFi_Msg.utemp2));for(i=0;i<Buf[4];i++) WiFi_Msg.utemp2[i] = Buf[i + 5];
			sprintf(WiFi_Msg.temp2,"%s$",WiFi_Msg.utemp2);break;
		case ESP_D2_NTemp:memset(&WiFi_Msg.ntemp2,0,sizeof(WiFi_Msg.ntemp2));memset(&WiFi_Msg.untemp2,0,sizeof(WiFi_Msg.untemp2));for(i=0;i<Buf[4];i++) WiFi_Msg.untemp2[i] = Buf[i + 5];
			sprintf(WiFi_Msg.ntemp2,"%s$",WiFi_Msg.untemp2);break;
			
//		case ESP_D3_Weeek:memset(&WiFi_Msg.week3,0,sizeof(WiFi_Msg.week3));for(i=0;i<Buf[4];i++) WiFi_Msg.week3[i] = Buf[i + 5];break;
		case ESP_D3_Weather:memset(&WiFi_Msg.weather3,0,sizeof(WiFi_Msg.weather3));for(i=0;i<Buf[4];i++) WiFi_Msg.weather3[i] = Buf[i + 5];break;
		case ESP_D3_Temp:memset(&WiFi_Msg.temp3,0,sizeof(WiFi_Msg.temp3));memset(&WiFi_Msg.utemp3,0,sizeof(WiFi_Msg.utemp3));for(i=0;i<Buf[4];i++) WiFi_Msg.utemp3[i] = Buf[i + 5];
			sprintf(WiFi_Msg.temp3,"%s$",WiFi_Msg.utemp3);break;
		case ESP_D3_NTemp:memset(&WiFi_Msg.ntemp3,0,sizeof(WiFi_Msg.ntemp3));memset(&WiFi_Msg.untemp3,0,sizeof(WiFi_Msg.untemp3));for(i=0;i<Buf[4];i++) WiFi_Msg.untemp3[i] = Buf[i + 5];
			sprintf(WiFi_Msg.ntemp3,"%s$",WiFi_Msg.untemp3);break;
			
//				case ESP_Bili_Fow:sprintf(WiFi_Msg.bilifans,"%d",MAKEWORD(Buf[6],Buf[5]));printf("fans:%d",WiFi_Msg.bilifans);break;
		case ESP_Bili_Fow:memset(&WiFi_Msg.bilifans,0,sizeof(WiFi_Msg.bilifans));for(i=0;i<Buf[4];i++) WiFi_Msg.bilifans[i] = Buf[i + 5];
			break;
//		case ESP_Set_Addr:memset(&Address,0,sizeof(Address));for(i=0;i<Buf[4];i++) Address[i] = Buf[i + 5];
//			break;
		}
	}
}
ConfigSet temps;

u8 Timefix = 0;

void AnalysisKey(uint8_t *Buf)
{
	u16 Temp;
	if(Buf[0] == 0xFF &&Buf[1] == 0x55)
	{
		if(Buf[4] == 0x2)
		{
			switch (MAKEWORD(Buf[3], Buf[2]))
			{
			case ESP_KEY_MODE:
				DisSwRun = 0;SleepCount = 0;MenuCount = 0;
				if(Display_Mode == MODE_MENU&& MenuLevel != 1)
				{
					if(MenuLevel == 2)
					{
						switch(Selectitem&0xF0)
						{
							case 0x10:
								set.autotimeset = temps.autotimeset;
								break;
							case 0x20:
								sprintf(set.addr,"%s",temps.addr);
								break;
							case 0x30:
								Device_Cmd.commandmotion = temps.motionset;SendCommand();
								break;
							case 0x40:
								Device_Cmd.commandrgbcolor = temps.rgbcolor;
								Device_Cmd.commandrgbmode = temps.rgbmode;SendCommand();
								break;
							case 0x50:
								set.autoswdis = temps.autoswdis;
								set.fanswdis = temps.fanswdis;
								set.autoswtime = temps.autoswtime;
								sprintf(set.autoswtimec,"%02d",set.autoswtime);
								break;
							case 0x60:
								sprintf(set.uid,"%s",temps.uid);
								break;
						}
						MenuLevel--;
						Selectitem&=0x000F;
						Selectitem|=0x1110;
					}
				}
				else
				{
					Selectitem = 0x1111;
					if(Display_Mode == MODE_DATE||Display_Mode == MODE_DATE_1)
						Display_Mode = MODE_WEATH;
					else if(Display_Mode == MODE_WEATH||Display_Mode == MODE_WEATH_1||Display_Mode == MODE_WEATH_2)
					{	
						if(set.fanswdis) Display_Mode = MODE_BILI;
						else Display_Mode = DATA_THEME;
					}
					else if(Display_Mode == MODE_BILI)
						Display_Mode = DATA_THEME;
					else if(Display_Mode == MODE_MENU)
						Display_Mode = DATA_THEME;
				}
			break;
			case ESP_KEY_SW:
				DisSwRun = 0;SleepCount = 0;MenuCount = 0;
				if(Display_Mode == MODE_MENU)
				{
					if(MenuLevel == 1)
					{
						Temp = (Selectitem&0xF)+1;
						if(Temp > 6)
							Temp = 1;
						Selectitem &= ~0xF;
						Selectitem|=Temp;
					}
					else if(MenuLevel == 2)
					{
						switch(Selectitem&0xF0)
						{
							case 0x10:
								if(!set.autotimeset)
								{
									Temp = (Selectitem&0xF00)+0x100;
									if(Temp>0x300)
									{
										Selectitem &= ~0xF00;
										Selectitem|=0x100;
										MenuLevel--;
										if(!set.autotimeset)
										{
											own_sec = 0;
											own_min = set.min;
											own_hour = set.hour;
										}
										SaveFlag = True;
										break;
									}
									Selectitem &= ~0xF00;
									Selectitem|=Temp;
								}
								else
								{
									MenuLevel--;Timefix = 0;
									SaveFlag = True;break;
								}
								break;
							case 0x20:
									Temp = (Selectitem&0xF00)+0x100;
									if(Temp>0x600)
									{
										Selectitem &= ~0xF00;
										Selectitem|=0x100;
										MenuLevel--;
										SaveFlag = True;
//										AddrUpdate = True;
										UsartPrint(&huart3,ESP_Set_Addr,set.addr);
										break;
									}
									Selectitem &= ~0xF00;
									Selectitem|=Temp;
								break;
							case 0x30:
									Temp = (Selectitem&0xF00)+0x100;
									if(Temp>0x400)
									{
										Selectitem &= ~0xF00;
										Selectitem|=0x100;
										MenuLevel--;
										SaveFlag = True;
										break;
									}
									Selectitem &= ~0xF00;
									Selectitem|=Temp;
								break;
							case 0x40:
									Temp = (Selectitem&0xF00)+0x100;
									if(Device_Cmd.commandrgbmode == 3)
									{
										if(Temp>0x400)
										{
											Selectitem &= ~0xF00;
											Selectitem|=0x100;
											MenuLevel--;
											SaveFlag = True;
											break;
										}
									}
									else
									{
										if(Temp>0x300)
										{
											Selectitem &= ~0xF00;
											Selectitem|=0x100;
											MenuLevel--;
											SaveFlag = True;
											break;
										}
									}
									
									Selectitem &= ~0xF00;
									Selectitem|=Temp;
								break;
							case 0x50:
									Temp = (Selectitem&0xF00)+0x100;
									if(!set.autoswdis)
										Temp += 0x100;
									if(Temp>0x300)
									{
										Selectitem &= ~0xF00;
										Selectitem|=0x100;
										MenuLevel--;
										SaveFlag = True;
										break;
									}
									Selectitem &= ~0xF00;
									Selectitem|=Temp;
								break;
							case 0x60:
									Temp = (Selectitem&0xF00)+0x100;
									if(Temp>0xA00)
									{
										Selectitem &= ~0xF00;
										Selectitem|=0x100;
										MenuLevel--;
										SaveFlag = True;
//										UIDUpdate = True;
										UsartPrint(&huart3,ESP_Set_Uid,set.uid);
										break;
									}
									Selectitem &= ~0xF00;
									Selectitem|=Temp;
								break;
						}
					}		
				}
				else
				{
					if(Display_Mode == MODE_DATE)
					{
						DATA_THEME = MODE_DATE_1;
						Display_Mode = DATA_THEME;
						SaveFlag = True;
					}
					else if(Display_Mode == MODE_DATE_1)
					{
						DATA_THEME = MODE_DATE;
						Display_Mode = DATA_THEME;
						SaveFlag = True;
					}
					else if(Display_Mode == MODE_WEATH)
						Display_Mode = MODE_WEATH_1;
					else if(Display_Mode == MODE_WEATH_1)
						Display_Mode = MODE_WEATH_2;
					else if(Display_Mode == MODE_WEATH_2)
						Display_Mode = MODE_WEATH;
//					else
//						Display_Mode = MODE_WEATH;
				}
			break;
			case ESP_KEY_MENU:
				DisSwRun = 0;SleepCount = 0;MenuCount = 0;
				if(Display_Mode == MODE_MENU)
				{
					if(MenuLevel == 1)
					{
						MenuLevel = 2;
						Temp = (Selectitem&0xF);
						Temp<<=4;
						Selectitem&=~0xF0;
						Selectitem|=Temp;
						
						switch(Selectitem&0xF0)
						{
							case 0x10:
								temps.autotimeset = set.autotimeset;
								set.hour = own_hour;//��ʼ������ʱ��
								sprintf(set.hourc,"%02d",set.hour);
								set.min = own_min;//��ʼ������ʱ��
								sprintf(set.minc,"%02d",set.min);break;
							case 0x20:
								sprintf(temps.addr,"%s",set.addr);break;
							case 0x30:
								temps.motionset = Device_Cmd.commandmotion;break;
							case 0x40:
								temps.rgbcolor = Device_Cmd.commandrgbcolor;
								temps.rgbmode = Device_Cmd.commandrgbmode;break;
							case 0x50:
								temps.autoswdis = set.autoswdis;
								temps.fanswdis = set.fanswdis;
								temps.autoswtime = set.autoswtime;
								sprintf(set.autoswtimec,"%02d",set.autoswtime);
							break;
							case 0x60:
								sprintf(temps.uid,"%s",set.uid);break;
						}
					}
					else if(MenuLevel == 2)
					{		
						switch(Selectitem&0xF0)
						{
							case 0x10:
							{
								switch(Selectitem&0xF00)
								{
									case 0x100:
									set.autotimeset = 1-set.autotimeset;
									break;
									case 0x200:
										set.hour++;if(set.hour==24) set.hour = 0;
										sprintf(set.hourc,"%02d",set.hour);
									break;
									case 0x300:
										set.min++;if(set.min==60) set.min = 0;
										sprintf(set.minc,"%02d",set.min);
									break;
								}
							}break;
							case 0x20:
							{
								Temp = ((Selectitem&0xF00)>>8)-1;
								set.addr[Temp]++;if(set.addr[Temp]>'9') set.addr[Temp] = '0';
							}break;		
							case 0x30:
							{
									switch(Selectitem&0xF00)
									{ 
										case 0x100:
										if(Device_Cmd.commandmotion&0x8) Device_Cmd.commandmotion&=~0x8;else Device_Cmd.commandmotion|=0x8;
										break;
										case 0x200:
										if(Device_Cmd.commandmotion&0x4) Device_Cmd.commandmotion&=~0x4;else Device_Cmd.commandmotion|=0x4;
										break;
										case 0x300:
										if(Device_Cmd.commandmotion&0x2) Device_Cmd.commandmotion&=~0x2;else Device_Cmd.commandmotion|=0x2;
										break;
										case 0x400:
										if(Device_Cmd.commandmotion&0x1) Device_Cmd.commandmotion&=~0x1;else Device_Cmd.commandmotion|=0x1;
										break;
									}
									SendCommand();
							}break;	
							case 0x40:
							{
									switch(Selectitem&0xF00)
									{ 
										case 0x100:
										Device_Cmd.commandrgbmode = 2;
										break;
										case 0x200:
										Device_Cmd.commandrgbmode = 1;
										break;
										case 0x300:
										Device_Cmd.commandrgbmode = 3;
										break;
										case 0x400:
										Device_Cmd.commandrgbcolor++;if(Device_Cmd.commandrgbcolor>255) Device_Cmd.commandrgbcolor = 0;
										break;
									}
									SendCommand();
							}break;		
							case 0x50:
							{
									switch(Selectitem&0xF00)
									{ 
										case 0x100:
											set.autoswdis = 1-set.autoswdis;
										break;
										case 0x200:
											set.autoswtime++;if(set.autoswtime==60) set.autoswtime = 5;
											sprintf(set.autoswtimec,"%02d",set.autoswtime);
										break;
										case 0x300:
											set.fanswdis = 1-set.fanswdis;
										break;
									}
							}break;		
							case 0x60:
							{
								Temp = ((Selectitem&0xF00)>>8)-1;
								if(set.uid[Temp] == '-') set.uid[Temp] = '0';
								else
								{
									set.uid[Temp]++;if(set.uid[Temp]>'9') set.uid[Temp] = '-';
								}
							}break;		
						}	
					}				
				}
				else
				{
					if(Display_Mode == MODE_MENU)
						Display_Mode = DATA_THEME;
					else if(Display_Mode != MODE_MENU)
						Display_Mode = MODE_MENU;
				}
				break;
				}
		}
	}
}


void AnalysisWiFiInter(uint8_t *Buf)
{
	if(Buf[0] == 0xFF &&Buf[1] == 0x55)
	{
		if(Buf[4] == 0x2)
		{
			switch (MAKEWORD(Buf[3], Buf[2]))
			{
			case ESP_WeatherNum:WiFi_Msg.weathernum = MAKEWORD(Buf[6],Buf[5]);break;
			case ESP_D1_WeatherNum:WiFi_Msg.weather1num = MAKEWORD(Buf[6],Buf[5]);break;
			case ESP_D2_WeatherNum:WiFi_Msg.weather2num = MAKEWORD(Buf[6],Buf[5]);break;
			case ESP_D3_WeatherNum:WiFi_Msg.weather3num = MAKEWORD(Buf[6],Buf[5]);break;
				
			case ESP_D1_Weeek:WiFi_Msg.week1num = MAKEWORD(Buf[6],Buf[5]);break;
			case ESP_D2_Weeek:WiFi_Msg.week2num = MAKEWORD(Buf[6],Buf[5]);break;
			case ESP_D3_Weeek:WiFi_Msg.week3num = MAKEWORD(Buf[6],Buf[5]);break;
				
			case ESP_Year:WiFi_Msg.year = MAKEWORD(Buf[6],Buf[5]);break;
			case ESP_Month:WiFi_Msg.month = MAKEWORD(Buf[6],Buf[5]);break;
			case ESP_Day:WiFi_Msg.day = MAKEWORD(Buf[6],Buf[5]);break;
			case ESP_Week:WiFi_Msg.week = MAKEWORD(Buf[6],Buf[5]);break;
			case ESP_Hour:WiFi_Msg.hour = MAKEWORD(Buf[6],Buf[5]);break;
			case ESP_Minute:WiFi_Msg.minute = MAKEWORD(Buf[6],Buf[5]);break;
			case ESP_Second:WiFi_Msg.second = MAKEWORD(Buf[6],Buf[5]);
				if(set.autotimeset)
//				if(Timefix++ == 1||Timefix == 5)
				{
					own_sec = WiFi_Msg.second;
					own_min = WiFi_Msg.minute;
					own_hour = WiFi_Msg.hour;
				}
				break;
//				
//				case ESP_Bili_Fow:sprintf(WiFi_Msg.bilifans,"%d",MAKEWORD(Buf[6],Buf[5]));printf("fans:%d",WiFi_Msg.bilifans);break;
			case ESP_Bili_Msg:WiFi_Msg.bilimsg = MAKEWORD(Buf[6],Buf[5]);Uart_Overflow3_Flag = 1-Uart_Overflow3_Flag;WifiActive = True;
						if(Display_Mode == MODE_OFFLINE)
							Display_Mode = DATA_THEME;break;
			}
		}
	}
}
/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
