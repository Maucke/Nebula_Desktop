/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "OLED_Animation.h"
#include "OLED_Driver.h"
#include "OLED_GFX.h"
#include "OLED_FFT.h"
#include "sys.h"
#include "zhfont.h"
//#include "sk6812.h"
#include "motion.h"
#include "stdio.h"
#include "stmflash.h"
#include "string.h"
#include "math.h"
#include "sensorui.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

uint8_t Flag_Refrash = False;
uint8_t Flag_Blink = False;
uint8_t Flag_Sleep = False;
uint8_t Flag_Continue = False;
uint8_t Flag_Reception = True;
uint8_t OfflineCount = 6;
uint8_t WiFiOfflineCount = 6;
uint8_t SystemActive = True;
u8 datatemp[256] = {};
u16 RandomX=30,RandomY=30;

u16 DisSwRun = 0;
u16 SleepCount = 0;
u16 MenuCount = 0;
u16 ColorPointer[3];
//	
//u8 SETUpdate = False;
//u8 UIDUpdate = False;
//u8 AddrUpdate = False;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */


OLED_GFX oled = OLED_GFX();
OLED_FFT fft = OLED_FFT();
OLED_Animation motion = OLED_Animation();
u16 own_hour,own_min,own_sec;
char vtimec[10]="--:--";
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

u16 Display_Mode = MODE_OFFLINE;
u16 Current_Mode = MODE_OFFLINE;

u16 DATA_THEME = MODE_DATE;

#define BOOTBMP Logo_asus

u8 Dataleng;
char DataDis[20];
char DataDisf[3];

u8 DataDisType=0;
u8 UnitDisType=0;
u8 HWDisType=0;
u8 Show_Float=False;

static u16 PulseRun = 4060 ,dir = True;
u8 CptOnline = False;
u8 WiFiOnline = False;

void Mode_In(void)
{
	
	SetCurrent(STSOK,0) ;
	SetTarget(STSOK,0);
	SetTarget(DIM,64);
	switch(Current_Mode)
	{
		case MODE_DATE:TIME_Mode_In();break;
		case MODE_DATE_1:TIME_1_Mode_In();break;
		case MODE_NORMAL:NORMAL_Mode_In();break;
//		case MODE_GAME:NORMAL_Mode_In();break;
		case MODE_GAME:GAME_Mode_In();break;
		case MODE_MUSIC:MUSIC_Mode_In();break;
#if Dounsn == 1
		case MODE_BILI:BILI_Mode_In();break;
		case MODE_WEATH:WEATH_Mode_In();break;
		case MODE_WEATH_1:WEATH_1_Mode_In();break;
		case MODE_WEATH_2:WEATH_2_Mode_In();break;
		case MODE_MENU:MENU_Mode_In();break;
#endif
	}
}


void Mode_Out(void)
{
	SetTarget(STSOK,15);
	SetTarget(DIM,20);
	switch(Current_Mode)
	{
		case MODE_DATE:TIME_Mode_Out();break;
		case MODE_DATE_1:TIME_1_Mode_Out();break;
		case MODE_NORMAL:NORMAL_Mode_Out();break;
//		case MODE_GAME:NORMAL_Mode_Out();break;
		case MODE_GAME:GAME_Mode_Out();break;
		case MODE_MUSIC:MUSIC_Mode_Out();break;
#if Dounsn == 1
		case MODE_BILI:BILI_Mode_Out();break;
		case MODE_WEATH:WEATH_Mode_Out();break;
		case MODE_WEATH_1:WEATH_1_Mode_Out();break;
		case MODE_WEATH_2:WEATH_2_Mode_Out();break;
		case MODE_MENU:MENU_Mode_Out();break;
#endif
	}
	DampMPos(0.1);
}

void Mode_Run(void)
{
	SetTarget(DIM,64);
	switch(Current_Mode)
	{
		case MODE_DATE:TIME_Mode_Run();break;
		case MODE_DATE_1:TIME_Mode_Run();break;
		case MODE_NORMAL:NORMAL_Mode_Run();break;
//		case MODE_GAME:NORMAL_Mode_Run();break;
//		case MODE_GAME:GAME_Mode_Run();break;
//		case MODE_MUSIC:MUSIC_Mode_Run();break;
#if Dounsn == 1
		case MODE_BILI:BILI_Mode_Run();break;
		case MODE_WEATH:WEATH_Mode_Run();break;
		case MODE_WEATH_1:WEATH_1_Mode_Run();break;
		case MODE_WEATH_2:WEATH_2_Mode_Run();break;
		case MODE_MENU:MENU_Mode_Run();break;
#endif
	}
}

void Mode_Display(void)
{
	switch(Current_Mode)
	{
		case MODE_DEFALUT:Current_Mode = MODE_DATE;break;
		case MODE_DATE:TIME_Display();break;
		case MODE_DATE_1:TIME_1_Display();break;
		case MODE_NORMAL:NORMAL_Display();break;
//		case MODE_GAME:NORMAL_Display();break;
		case MODE_GAME:GAME_Display();break;
		case MODE_MUSIC:MUSIC_Display();break;
#if Dounsn == 1
		case MODE_BILI:BILI_Display();break;
		case MODE_WEATH:WEATH_Display();break;
		case MODE_WEATH_1:WEATH_1_Display();break;
		case MODE_WEATH_2:WEATH_2_Display();break;
		case MODE_MENU:MENU_Display();break;
#endif
		default:Current_Mode = Display_Mode;break;
	}
}


void Display_Run(void)
{
	if(Flag_Refrash)
	{
		Flag_Refrash = False;
		if(Flag_Sleep)
		{
			Flag_Sleep = False;
			SLEEP_Display();
		}
		
		DampAutoPos();
		if(Display_Mode == Current_Mode)
		{
			Mode_Run();
		}
		else
		{
			Mode_Out();
			if(pit[STSOK].match)
			{
				SleepCount = 0;
				Current_Mode = Display_Mode;
				Mode_In();
			}
		}
		oled.Display_SetDim(pit[DIM].current);
		oled.Clear_Screen();
		if(Current_Mode!=MODE_GAME)
		{
			motion.OLED_AllMotion(Device_Cmd.commandmotion,Device_Cmd.commandspeed);
		}
		Mode_Display();
		oled.Refrash_Screen();
	}
	HAL_Delay(1);
}

void GAME_Display(void)
{
	static int i,roun=0;
	static char tempstr[100];
	roun++;
	oled.Display_bbmp(21,46,86,43,GeForce_B_Back,color_min);
	oled.Display_bbmp(6+5,105,23,13,shadowleft,color_min);
	oled.Display_bbmp(99-5,105,23,13,shadowright,color_min);

	motion.OLED_AllMotion(Device_Cmd.commandmotion,Device_Cmd.commandspeed);
	oled.Display_hbmp(pit[SSLF].current,22,54,9,userleft,color_now);
	oled.Display_hbmp(pit[SSRT].current,22,54,9,userright,color_now);
	oled.Display_hbmp(10,pit[SSDN].current,108,21,userbottom,color_now);
	
	
	oled.Display_hbmp(35,pit[SSDN].current+3,58,3,usermgndbar,0xFFFF);
	oled.Display_hbmp(pit[SSMLF].current,47,21,37,usermleft,color_half);
	oled.Display_hbmp(pit[SSMRT].current,47,21,37,usermright,color_half);
	for(i=0;i<9;i++)
			oled.Draw_Pixel(9+28+4+8+i*5,pit[SSUP].current+8,color_min);
	
	oled.Draw_Line(0,0,pit[SSRD].current,pit[SSRD].current,color_now);
	oled.Draw_Line(127,0,127-pit[SSRD].current,pit[SSRD].current,color_now);
	oled.Draw_Line(pit[SSRD].current,127-pit[SSRD].current,0,127,color_now);
	oled.Draw_Line(127-pit[SSRD].current,127-pit[SSRD].current,127,127,color_now);
	
	oled.Display_hbmp(9-5+pit[SSRD].current,pit[SSRD].current,28,10,GeForce_LOAD,color_now);
	oled.Display_hbmp(101+5-pit[SSRD].current,pit[SSRD].current,21,10,GeForce_SYS,color_now);
	oled.Display_hbmp(27+1,33,74,10,GeForce_TEMP,color_now);
	oled.Display_hbmp(48,88,33,13,GeForce_CENT,color_now);
	oled.Draw_Line(20,96-2,pit[SSLLF].current,96-2,0xFFFF);
	oled.Draw_Line(pit[SSLRT].current,96-2,108,96-2,0xFFFF);
	oled.Draw_Line(27,33+10,27+73,33+10,color_min);
//	sprintf(tempstr,"%02d",);
	oled.OLED_SHFAny(38,48,Device_Str.cputemp,25,0xFFFF);
	sprintf(tempstr,"%03d",Device_Msg.cpuload/10);
	oled.OLED_SHFAny(29-8+pit[SSLF].current,15,tempstr,10,0xFFFF);
	sprintf(tempstr,"%03d",Device_Msg.gputemp/10);
	oled.OLED_SHFAny(69+1+8-pit[SSLF].current,15,tempstr,10,0xFFFF);
//	oled.Refrash_Screen();
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
  /* USER CODE END 1 */
  

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USART1_UART_Init();
  MX_USART3_UART_Init();
  MX_TIM6_Init();
  MX_TIM7_Init();
  MX_TIM8_Init();
  MX_ADC1_Init();
  MX_TIM3_Init();
  MX_TIM5_Init();
  /* USER CODE BEGIN 2 */
	__HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE);
  HAL_UART_Receive_DMA(&huart1,Uart_Recv1_Buf,Uart_Max_Length);
#if Dounsn == 1
	__HAL_UART_ENABLE_IT(&huart3, UART_IT_IDLE);
  HAL_UART_Receive_DMA(&huart3,Uart_Recv3_Buf,Uart_Max_Length);
#endif
	HAL_TIM_Base_Start_IT(&htim5);
	HAL_TIM_Base_Start_IT(&htim6);
	HAL_TIM_Base_Start_IT(&htim7);
	HAL_TIM_Base_Start_IT(&htim8);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
  oled.Device_Init();
	UsartCommand(&huart1,0xA002,3);//获取命令
	InitData();
#if Dounsn == 1
	InitWifi();
#endif
	motion.OLED_AllMotion_Init();
	Recvcmd();
	
	if(Display_Mode != MODE_OFFLINE)
		OFFLINE_Mode();
	else
		printf("%s is online\r\n",Device_Name);
#if Dounsn == 1
//	WAITWIFI_Mode();
	
	SetCurrent(PWPTDN,128);
	SetCurrent(PWPTRTICON,40);
	SetCurrent(PWPTLF,-80) ;
	SetCurrent(PWPTUP,-20) ;
	SetCurrent(PWPTRT,140);
	SetCurrent(PWPTLINE,41);
	
	SetTarget(PWPTDN,128);
	SetTarget(PWPTRTICON,40);
	SetTarget(PWPTUP,-20) ;
	SetTarget(PWPTLF,-80) ;
	SetTarget(PWPTRT,140);
	SetTarget(PWPTLINE,41);
#endif
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		
		if(Current_Mode == MODE_OFFLINE||Current_Mode == MODE_SHOW)
			OFFLINE_Mode();
		else
			Display_Run();
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

int cont_str_1(char *s)
{
	int i = 0;      
	while ( s[++i] != '\0')   ;
	return i;
}
void WAITWIFI_Mode(void)
{
	oled.Display_FadeinAll(Logo_wifioffline);
	while(WifiActive == False)
	{
		HAL_Delay(5);
	}
	UsartPrint(&huart3,ESP_Set_Addr,set.addr);
	HAL_Delay(10);
	UsartPrintuid(&huart3,ESP_Set_Uid,set.uid);
	if(set.autotimeset)
	{
		own_sec = WiFi_Msg.second;
		own_min = WiFi_Msg.minute;
		own_hour = WiFi_Msg.hour;
	}
	oled.Display_FadeoutAll();
}



void BILI_Mode_In(void)
{
	SetCurrent(PBLOGO,-40) ;
	SetCurrent(PBNUM,140) ;
	SetTarget(PBNUM,140) ;
	
	SetCurrent(PBPTbk,140) ;
	SetCurrent(PBPT22,128) ;
	SetCurrent(PBPT33,128) ;
	
	SetTarget(RDHourColor, oled.WheelPw(rand()%96));
	SetTarget(RDMinColor, oled.WheelPw(rand()%96));
	SetTarget(RDSecColor, oled.WheelP(rand()%96));
}

void BILI_Mode_Out(void)
{
	SetTarget(PBLOGO,-40) ;
	SetTarget(PBNUM,140) ;
	SetTarget(PBLINER,pit[PBLINEL].current);
	
	SetTarget(PBPTbk,140) ;
	SetTarget(PBPT22,128) ;
	SetTarget(PBPT33,128) ;
}

void BILI_Mode_Run(void)
{
	static u16 runcount = 0;
	u16 BiLen = cont_str(WiFi_Msg.bilifans);
	
	if(BiLen>1)
	{
		SetTarget(PBLINEL,64+3-(BiLen*12+30)/2);
		SetTarget(PBLINER,64+(BiLen*12+30)/2);
		SetTarget(PBLOGO,32-(BiLen*12+30)/4);
		SetTarget(PBNUM,64+(BiLen*12+30)/2-BiLen*12);
	}
	else
		SetTarget(PBLOGO,26);
	runcount++;
	SetTarget(PBPTbk,118+5-runcount%500/100);

	SetTarget(PBPT22,60+5-(runcount+75)%150/30);
	SetTarget(PBPT33,60+5-runcount%200/40);
	
}

void BILI_Display(void)
{
	oled.Display_bmp(0,pit[PBPTbk].current,128,10,Bilibilibk);
	oled.Display_bmp(7,pit[PBPT22].current,51,63,Bilibili22);
	oled.Display_bmp(34,pit[PBPT33].current,51,63,Bilibili33);
	
	oled.Display_bmp(pit[PBLOGO].current,8+8,30,27,Corn_Bilibili);
	oled.OLED_SHF12x24(pit[PBNUM].current,11+8,WiFi_Msg.bilifans,color_now);
	if(cont_str(WiFi_Msg.bilifans)>1)
		oled.Draw_Line(pit[PBLINEL].current,36+8,pit[PBLINER].current,36+8,color_half);
}

void OFFLINE_Mode_In(void)
{
	int i;
	oled.Display_SetDim(0);
	oled.Clear_Screen();
	
#if Dounsn == 1
	oled.Display_bmp(Logo_nebula);
#else
	switch(Device_Cmd.commandlogotheme)
	{
		case 0:oled.Display_bmp(Logo_asus);break;
		case 1:oled.Display_bmp(Logo_msi);break;
		case 2:oled.Display_bmp(Logo_amd);break;
		case 3:oled.Display_bmp(Logo_radeon);break;
		case 4:oled.Display_bmp(Logo_nvidia);break;
		case 5:oled.Display_bmp(Logo_custorm);break;
		default:oled.Display_bmp(Logo_msi);break;
	}
#endif
	oled.Refrash_Screen();
	for(i=0;i<65;i++)
	{
		oled.Display_SetDim(i);
		HAL_Delay(10);
	}
}

void OFFLINE_Mode_Out(void)
{
	int i;
	for(i=0;i<65;i++)
	{
		oled.Display_SetDim(64-i);
		HAL_Delay(10);
	}
	oled.Clear_Screen();
	oled.Refrash_Screen();
	oled.Display_SetDim(64);
}

void OFFLINE_Mode(void)
{
	OFFLINE_Mode_In();
	while(Display_Mode == MODE_OFFLINE||Display_Mode == MODE_DEFALUT)
	{
		if(Flag_Refrash)
		{
			Flag_Refrash = False;
			if(Flag_Sleep)
			{
				Flag_Sleep = False;
				SLEEP_Display();
			}
			if(!(Device_Cmd.commandset&0x8))
			{
				oled.Clear_Screen();
				motion.OLED_AllMotion(Device_Cmd.commandmotion,Device_Cmd.commandspeed);
			}
			oled.Refrash_Screen();
		}
		HAL_Delay(1);
	}
	SleepCount = 0;
	Current_Mode = Display_Mode;
	Mode_In();
	if(Display_Mode != MODE_GAME)
	{
//		UsartCommand(&huart1,0xA001,3);//获取设备名
//		HAL_Delay(1);
		UsartCommand(&huart1,0xA002,3);//获取命令
//		UsartCommand(&huart1,0xA003,3);//获取硬盘信息
//		HAL_Delay(1);
		UsartPrint(&huart1,0xC001,Device_Name);
		HAL_Delay(40);
		UsartPrint(&huart1,0xC001," Active\n");
		
		
#if Dounsn == 1
		UsartPrint(&huart3,ESP_Set_Addr,set.addr);
		HAL_Delay(10);
		UsartPrintuid(&huart1,ESP_Set_Uid,set.uid);
		UsartPrintuid(&huart3,ESP_Set_Uid,set.uid);
#endif
	}
	if(set.autotimeset)
	{
//		own_sec = Device_Msg.uartsecond;
//		own_min = Device_Msg.uartminute;
//		own_hour = Device_Msg.uarthour;
	}
	HAL_Delay(1000);
	OFFLINE_Mode_Out(); 
}

u16 Selectitem = 0x1111;
u16 MenuLevel = 0x1;
#define ITEMRC 24  //一行高度
#define ITEMAC 128 //屏幕高度
#define ITEMNUM 6 //屏幕高度
u16 color_menu[ITEMNUM];
void MENU_Mode_Run()
{
	int i;
	if(MenuCount>12)
		SetTarget(MENUL3SX,(- MenuCount*4.5)+183);
	else
		SetTarget(MENUL3SX,-1);
	if(MenuLevel == 1)
	{
		SetTarget(MENUL1Y,0);
		switch(Selectitem&0xF)
		{
			case 1:
			SetTarget(MENUL1I1X,10);SetTarget(MENUL1I1Y,ITEMRC*(0+1));	
			SetTarget(MENUL1I2X,20);SetTarget(MENUL1I2Y,ITEMRC*(1+1));
			SetTarget(MENUL1I3X,20);SetTarget(MENUL1I3Y,ITEMRC*(2+1));
			SetTarget(MENUL1I4X,20);SetTarget(MENUL1I4Y,ITEMRC*(3+1));
			SetTarget(MENUL1I5X,20);SetTarget(MENUL1I5Y,ITEMRC*(4+1));
			SetTarget(MENUL1I6X,20);SetTarget(MENUL1I6Y,ITEMRC*(5+1));
			for(i=0;i<ITEMNUM;i++) color_menu[i] = color_half; color_menu[0] = color_now;
			break;
			case 2:
			SetTarget(MENUL1I1X,-128);SetTarget(MENUL1I1Y,ITEMRC-10);	
			SetTarget(MENUL1I2X,10);SetTarget(MENUL1I2Y,ITEMRC*(1+0));
			SetTarget(MENUL1I3X,20);SetTarget(MENUL1I3Y,ITEMRC*(2+0));
			SetTarget(MENUL1I4X,20);SetTarget(MENUL1I4Y,ITEMRC*(3+0));
			SetTarget(MENUL1I5X,20);SetTarget(MENUL1I5Y,ITEMRC*(4+0));
			SetTarget(MENUL1I6X,20);SetTarget(MENUL1I6Y,ITEMRC*(5+0));
			for(i=0;i<ITEMNUM;i++) color_menu[i] = color_half; color_menu[1] = color_now;
			break;
			case 3:
			SetTarget(MENUL1I1X,-128);SetTarget(MENUL1I1Y,ITEMRC-10);	
			SetTarget(MENUL1I2X,-128);SetTarget(MENUL1I2Y,ITEMRC-10);
			SetTarget(MENUL1I3X,10);SetTarget(MENUL1I3Y,ITEMRC*(2-1));
			SetTarget(MENUL1I4X,20);SetTarget(MENUL1I4Y,ITEMRC*(3-1));
			SetTarget(MENUL1I5X,20);SetTarget(MENUL1I5Y,ITEMRC*(4-1));
			SetTarget(MENUL1I6X,20);SetTarget(MENUL1I6Y,ITEMRC*(5-1));
			for(i=0;i<ITEMNUM;i++) color_menu[i] = color_half; color_menu[2] = color_now;
			break;
			case 4:
			SetTarget(MENUL1I1X,-128);SetTarget(MENUL1I1Y,ITEMRC-10);	
			SetTarget(MENUL1I2X,-128);SetTarget(MENUL1I2Y,ITEMRC-10);
			SetTarget(MENUL1I3X,-128);SetTarget(MENUL1I3Y,ITEMRC-10);
			SetTarget(MENUL1I4X,10);SetTarget(MENUL1I4Y,ITEMRC*(3-2));
			SetTarget(MENUL1I5X,20);SetTarget(MENUL1I5Y,ITEMRC*(4-2));
			SetTarget(MENUL1I6X,20);SetTarget(MENUL1I6Y,ITEMRC*(5-2));
			for(i=0;i<ITEMNUM;i++) color_menu[i] = color_half; color_menu[3] = color_now;
			break;
			case 5:
			SetTarget(MENUL1I1X,-128);SetTarget(MENUL1I1Y,ITEMRC-10);	
			SetTarget(MENUL1I2X,-128);SetTarget(MENUL1I2Y,ITEMRC-10);
			SetTarget(MENUL1I3X,-128);SetTarget(MENUL1I3Y,ITEMRC-10);
			SetTarget(MENUL1I4X,-128);SetTarget(MENUL1I4Y,ITEMRC-10);
			SetTarget(MENUL1I5X,10);SetTarget(MENUL1I5Y,ITEMRC*(4-3));
			SetTarget(MENUL1I6X,10);SetTarget(MENUL1I6Y,ITEMRC*(5-3));
			for(i=0;i<ITEMNUM;i++) color_menu[i] = color_half; color_menu[4] = color_now;
			break;
			case 6:
			SetTarget(MENUL1I1X,-128);SetTarget(MENUL1I1Y,ITEMRC-10);	
			SetTarget(MENUL1I2X,-128);SetTarget(MENUL1I2Y,ITEMRC-10);
			SetTarget(MENUL1I3X,-128);SetTarget(MENUL1I3Y,ITEMRC-10);
			SetTarget(MENUL1I4X,-128);SetTarget(MENUL1I4Y,ITEMRC-10);
			SetTarget(MENUL1I5X,-128);SetTarget(MENUL1I5Y,ITEMRC-10);
			SetTarget(MENUL1I6X,10);SetTarget(MENUL1I6Y,ITEMRC*(5-4));
			for(i=0;i<ITEMNUM;i++) color_menu[i] = color_half; color_menu[5] = color_now;
			break;
		}
		SetTarget(MENUL2IX,128);
		SetTarget(MENUL2S1X,128);//恢复指示线位置
		SetTarget(MENUL2S2X,128);//恢复指示线位置
	}
	else if(MenuLevel == 2)
	{
		SetTarget(MENUL1Y,-24);
		SetTarget(MENUL2IX,0);
		switch(Selectitem&0xF0)
		{
			case 0x10:
			SetTarget(MENUL1I1X,20);SetTarget(MENUL1I1Y,0);	
			SetTarget(MENUL1I2X,20);SetTarget(MENUL1I2Y,ITEMAC+ITEMRC*1);
			SetTarget(MENUL1I3X,20);SetTarget(MENUL1I3Y,ITEMAC+ITEMRC*2);
			SetTarget(MENUL1I4X,20);SetTarget(MENUL1I4Y,ITEMAC+ITEMRC*3);
			SetTarget(MENUL1I5X,20);SetTarget(MENUL1I5Y,ITEMAC+ITEMRC*4);
			SetTarget(MENUL1I6X,20);SetTarget(MENUL1I6Y,ITEMAC+ITEMRC*5);
			for(i=0;i<ITEMNUM;i++) color_menu[i] = color_half; color_menu[0] = 0xFFFF;
			
			switch(Selectitem&0xF00)
			{
				case 0x100:
				SetTarget(MENUL2S1X,20);//恢复指示线位置
				SetTarget(MENUL2S2X,20);//恢复指示线位置
				break;
				case 0x200:
				SetTarget(MENUL2S1X,28+pit[MENUL2IX].current);
				SetTarget(MENUL2S2X,28+24+pit[MENUL2IX].current);
				break;
				case 0x300:
				SetTarget(MENUL2S1X,28+36+pit[MENUL2IX].current);
				SetTarget(MENUL2S2X,28+24+36+pit[MENUL2IX].current);
				break;
			}
			break;
			case 0x20:
			SetTarget(MENUL1I1X,-128);SetTarget(MENUL1I1Y,-ITEMRC*1);	
			SetTarget(MENUL1I2X,20);SetTarget(MENUL1I2Y,0);
			SetTarget(MENUL1I3X,20);SetTarget(MENUL1I3Y,ITEMAC+ITEMRC*1);
			SetTarget(MENUL1I4X,20);SetTarget(MENUL1I4Y,ITEMAC+ITEMRC*2);
			SetTarget(MENUL1I5X,20);SetTarget(MENUL1I5Y,ITEMAC+ITEMRC*3);
			SetTarget(MENUL1I6X,20);SetTarget(MENUL1I6Y,ITEMAC+ITEMRC*4);
			for(i=0;i<ITEMNUM;i++) color_menu[i] = color_half; color_menu[1] = 0xFFFF;
			
			SetTarget(MENUL2S1X,20+12*(((Selectitem&0xF00)>>8)-1)+pit[MENUL2IX].current);
			SetTarget(MENUL2S2X,20+12*((Selectitem&0xF00)>>8)+pit[MENUL2IX].current);
//			
			break;
			case 0x30:
			SetTarget(MENUL1I1X,-128);SetTarget(MENUL1I1Y,-ITEMRC*2);	
			SetTarget(MENUL1I2X,-128);SetTarget(MENUL1I2Y,-ITEMRC*1);
			SetTarget(MENUL1I3X,20);SetTarget(MENUL1I3Y,0);
			SetTarget(MENUL1I4X,20);SetTarget(MENUL1I4Y,ITEMAC+ITEMRC*1);
			SetTarget(MENUL1I5X,20);SetTarget(MENUL1I5Y,ITEMAC+ITEMRC*2);
			SetTarget(MENUL1I6X,20);SetTarget(MENUL1I6Y,ITEMAC+ITEMRC*3);
			for(i=0;i<ITEMNUM;i++) color_menu[i] = color_half; color_menu[2] = 0xFFFF;
			break;
			case 0x40:
			SetTarget(MENUL1I1X,-128);SetTarget(MENUL1I1Y,-ITEMRC*3);	
			SetTarget(MENUL1I2X,-128);SetTarget(MENUL1I2Y,-ITEMRC*2);
			SetTarget(MENUL1I3X,-128);SetTarget(MENUL1I3Y,-ITEMRC*1);
			SetTarget(MENUL1I4X,20);SetTarget(MENUL1I4Y,0);
			SetTarget(MENUL1I5X,20);SetTarget(MENUL1I5Y,ITEMAC+ITEMRC*1);
			SetTarget(MENUL1I6X,20);SetTarget(MENUL1I6Y,ITEMAC+ITEMRC*2);
			for(i=0;i<ITEMNUM;i++) color_menu[i] = color_half; color_menu[3] = 0xFFFF;
			break;
			case 0x50:
			SetTarget(MENUL1I1X,-128);SetTarget(MENUL1I1Y,-ITEMRC*4);	
			SetTarget(MENUL1I2X,-128);SetTarget(MENUL1I2Y,-ITEMRC*3);
			SetTarget(MENUL1I3X,-128);SetTarget(MENUL1I3Y,-ITEMRC*2);
			SetTarget(MENUL1I4X,-128);SetTarget(MENUL1I4Y,-ITEMRC*1);
			SetTarget(MENUL1I5X,20);SetTarget(MENUL1I5Y,0);
			SetTarget(MENUL1I6X,20);SetTarget(MENUL1I6Y,ITEMAC+ITEMRC*1);
			for(i=0;i<ITEMNUM;i++) color_menu[i] = color_half; color_menu[4] = 0xFFFF;
			break;
			case 0x60:
			SetTarget(MENUL1I1X,-128);SetTarget(MENUL1I1Y,-ITEMRC*5);	
			SetTarget(MENUL1I2X,-128);SetTarget(MENUL1I2Y,-ITEMRC*4);
			SetTarget(MENUL1I3X,-128);SetTarget(MENUL1I3Y,-ITEMRC*3);
			SetTarget(MENUL1I4X,-128);SetTarget(MENUL1I4Y,-ITEMRC*2);
			SetTarget(MENUL1I5X,-128);SetTarget(MENUL1I5Y,-ITEMRC*1);
			SetTarget(MENUL1I6X,20);SetTarget(MENUL1I6Y,0);
			for(i=0;i<ITEMNUM;i++) color_menu[i] = color_half; color_menu[5] = 0xFFFF;
	
			SetTarget(MENUL2S1X,12*(((Selectitem&0xF00)>>8)-1)+pit[MENUL2IX].current);
			SetTarget(MENUL2S2X,12*((Selectitem&0xF00)>>8)+pit[MENUL2IX].current);
			break;
		}
	}
}

void MENU_Mode_In(void)
{
	SetCurrent(MENUL1I1X,20);
	SetCurrent(MENUL1I2X,20);
	SetCurrent(MENUL1I3X,20);
	SetCurrent(MENUL1I4X,20);
	SetCurrent(MENUL1I5X,20);
	SetCurrent(MENUL1I6X,20);
	
	SetCurrent(MENUL1I1Y,ITEMRC*(0-5)*2);
	SetCurrent(MENUL1I2Y,ITEMRC*(1-5)*2);
	SetCurrent(MENUL1I3Y,ITEMRC*(2-5)*2);
	SetCurrent(MENUL1I4Y,ITEMRC*(3-5)*2);
	SetCurrent(MENUL1I5Y,ITEMRC*(4-5)*2);
	SetCurrent(MENUL1I6Y,ITEMRC*(5-5)*2);
	
	SetCurrent(MENUL2S1X,28);
	SetCurrent(MENUL2S2X,28+24);
	SetCurrent(MENUL1Y,-128-128);
	
	SetCurrent(MENUL3SX,-1);
	SetTarget(MENUL3SX,-1);
}

void MENU_Mode_Out(void)
{
	SetTarget(MENUL1I1X,20);
	SetTarget(MENUL1I2X,20);
	SetTarget(MENUL1I3X,20);
	SetTarget(MENUL1I4X,20);
	SetTarget(MENUL1I5X,20);
	SetTarget(MENUL1I6X,20);
	
	SetTarget(MENUL1I1Y,ITEMRC*(0+5)+70);
	SetTarget(MENUL1I2Y,ITEMRC*(1+5)+70);
	SetTarget(MENUL1I3Y,ITEMRC*(2+5)+70);
	SetTarget(MENUL1I4Y,ITEMRC*(3+5)+70);
	SetTarget(MENUL1I5Y,ITEMRC*(4+5)+70);
	SetTarget(MENUL1I6Y,ITEMRC*(5+5)+70);
	
	SetTarget(MENUL3SX,-1);
	SetTarget(MENUL1Y,-24);
	
}

ConfigSet set={1,"340207",12,0,"12","00",0,0,0,"-49890113-",1,15,"05",1};
u16 color_setitem[8];
void MENU_Display()
{
	int i;
	oled.Draw_Line(-1,127,pit[MENUL3SX].current,127,color_half);//选中小时
	if(MenuLevel == 1)
	{
		oled.Display_hbmp(20,pit[MENUL1Y].current,88,24,menutop,0xFFFF);
		oled.Display_hbmp(pit[MENUL1I1X].current,6+pit[MENUL1I1Y].current,80,20,menusettime,color_menu[0]);
		oled.Display_hbmp(pit[MENUL1I2X].current,6+pit[MENUL1I2Y].current,80,20,menusetaddr,color_menu[1]);
		oled.Display_hbmp(pit[MENUL1I3X].current,6+pit[MENUL1I3Y].current,80,20,menusetmotion,color_menu[2]);
		oled.Display_hbmp(pit[MENUL1I4X].current,6+pit[MENUL1I4Y].current,80,20,menusetcolor,color_menu[3]);
		oled.Display_hbmp(pit[MENUL1I5X].current,6+pit[MENUL1I5Y].current,80,20,menusetdisplay,color_menu[4]);
		oled.Display_hbmp(pit[MENUL1I6X].current,6+pit[MENUL1I6Y].current,80,20,menusetuid,color_menu[5]);
	}
	else if(MenuLevel == 2)
	{
		oled.Display_hbmp(20,pit[MENUL1Y].current,88,24,menutop,0xFFFF);
			
		switch(Selectitem&0xF00)
		{
			case 0x100:for(i=0;i<4;i++) color_setitem[i] = color_half; color_setitem[0] = color_now;break;
			case 0x200:for(i=0;i<4;i++) color_setitem[i] = color_half; color_setitem[1] = color_now;break;
			case 0x300:for(i=0;i<4;i++) color_setitem[i] = color_half; color_setitem[2] = color_now;break;
			case 0x400:for(i=0;i<4;i++) color_setitem[i] = color_half; color_setitem[3] = color_now;break;
		}
				
		switch(Selectitem&0xF0)
		{
			case 0x10:
				oled.Display_hbmp(pit[MENUL1I1X].current,6+pit[MENUL1I1Y].current,80,20,menusettime,color_menu[0]);
					
				oled.Display_hbmp(20+pit[MENUL2IX].current,40,80,14,autosynctime,color_setitem[0]);
				if(set.autotimeset)
					oled.Display_hbmp(4+pit[MENUL2IX].current,40,16,15,iconok,color_setitem[0]);
				else
					oled.Display_hbmp(4+pit[MENUL2IX].current,40,16,15,iconnotok,color_setitem[0]);
				oled.OLED_SHF12x24(28+pit[MENUL2IX].current,60,set.hourc,color_setitem[1]);
				oled.OLED_SHF12x24(28+24+pit[MENUL2IX].current,60,":",color_half);
				oled.OLED_SHF12x24(28+36+pit[MENUL2IX].current,60,set.minc,color_setitem[2]);
				if((!set.autotimeset)&&(Selectitem&0xF00)>0x100)
					oled.Draw_Line(pit[MENUL2S1X].current,83,pit[MENUL2S2X].current,83,color_half);//选中小时
			break;
			case 0x20:
				oled.Display_hbmp(pit[MENUL1I2X].current,6+pit[MENUL1I2Y].current,80,20,menusetaddr,color_menu[1]);
				oled.OLED_SHF12x24(20+pit[MENUL2IX].current,50,set.addr,color_now);
				oled.Draw_Line(pit[MENUL2S1X].current,73,pit[MENUL2S2X].current,73,color_half);//
				oled.Draw_Line(pit[MENUL2S1X].current,50,pit[MENUL2S2X].current,50,color_half);//
				oled.Display_hbmp(92-28-24+pit[MENUL2IX].current,74,52,14,iconaddres,color_half);
			break;
			case 0x30:
				oled.Display_hbmp(pit[MENUL1I3X].current,6+pit[MENUL1I3Y].current,80,20,menusetmotion,color_menu[2]);
			
				if(Device_Cmd.commandmotion&0x8)
					oled.Display_hbmp(14+pit[MENUL2IX].current,40,16,15,iconok,color_setitem[0]);
				else
					oled.Display_hbmp(14+pit[MENUL2IX].current,40,16,15,iconnotok,color_setitem[0]);
					
				if(Device_Cmd.commandmotion&0x4)
					oled.Display_hbmp(14+pit[MENUL2IX].current,40+22,16,15,iconok,color_setitem[1]);
				else
					oled.Display_hbmp(14+pit[MENUL2IX].current,40+22,16,15,iconnotok,color_setitem[1]);
				if(Device_Cmd.commandmotion&0x2)
					oled.Display_hbmp(14+pit[MENUL2IX].current,40+22*2,16,15,iconok,color_setitem[2]);
				else
					oled.Display_hbmp(14+pit[MENUL2IX].current,40+22*2,16,15,iconnotok,color_setitem[2]);
				if(Device_Cmd.commandmotion&0x1)
					oled.Display_hbmp(14+pit[MENUL2IX].current,40+22*3,16,15,iconok,color_setitem[3]);
				else
					oled.Display_hbmp(14+pit[MENUL2IX].current,40+22*3,16,15,iconnotok,color_setitem[3]);
			
			
				oled.Display_hbmp(30+pit[MENUL2IX].current,40,54,14,iconmind,color_setitem[0]);
				oled.Display_hbmp(30+pit[MENUL2IX].current,40+22,54,14,iconstar,color_setitem[1]);
				oled.Display_hbmp(30+pit[MENUL2IX].current,40+22*2,54,14,iconsnow,color_setitem[2]);
				oled.Display_hbmp(30+pit[MENUL2IX].current,40+22*3,40,14,iconcircle,color_setitem[3]);
			break;
			case 0x40:
				oled.Display_hbmp(pit[MENUL1I4X].current,6+pit[MENUL1I4Y].current,80,20,menusetcolor,color_menu[3]);
				switch(Device_Cmd.commandrgbmode)
				{
					case 2:
						oled.Display_hbmp(4+pit[MENUL2IX].current,40,16,15,iconradok,color_setitem[0]);
						oled.Display_hbmp(4+pit[MENUL2IX].current,40+20,16,15,iconradnok,color_setitem[1]);
						oled.Display_hbmp(4+pit[MENUL2IX].current,40+20*2,16,15,iconradnok,color_setitem[2]);break;
					case 1:
						oled.Display_hbmp(4+pit[MENUL2IX].current,40,16,15,iconradnok,color_setitem[0]);
						oled.Display_hbmp(4+pit[MENUL2IX].current,40+20,16,15,iconradok,color_setitem[1]);
						oled.Display_hbmp(4+pit[MENUL2IX].current,40+20*2,16,15,iconradnok,color_setitem[2]);break;
					case 3:
						oled.Display_hbmp(4+pit[MENUL2IX].current,40,16,15,iconradnok,color_setitem[0]);
						oled.Display_hbmp(4+pit[MENUL2IX].current,40+20,16,15,iconradnok,color_setitem[1]);
						oled.Display_hbmp(4+pit[MENUL2IX].current,40+20*2,16,15,iconradok,color_setitem[2]);break;
				}
				
				oled.Display_hbmp(20+pit[MENUL2IX].current,40,80,14,iconautocolor1,color_setitem[0]);
				oled.Display_hbmp(20+pit[MENUL2IX].current,40+20,80,14,iconautocolor2,color_setitem[1]);
				oled.Display_hbmp(20+pit[MENUL2IX].current,40+20*2,80,14,iconmanualcolor,color_setitem[2]);
				
				if(Device_Cmd.commandrgbmode==3)
				{
					oled.Fill_Rect(20+pit[MENUL2IX].current,40+20*3+10,80,3,0x7BCF);
					oled.Fill_Rect(20+pit[MENUL2IX].current+(Device_Cmd.commandrgbcolor/3.5f),40+20*3-2+10,7,7,color_setitem[3]);
				}
				
				break;
			case 0x50:
				oled.Display_hbmp(pit[MENUL1I5X].current,6+pit[MENUL1I5Y].current,80,20,menusetdisplay,color_menu[4]);
				
				oled.Display_hbmp(20+pit[MENUL2IX].current,40,56,14,iconautoswdis,color_setitem[0]);
				if(set.autoswdis)
					oled.Display_hbmp(4+pit[MENUL2IX].current,40,16,15,iconok,color_setitem[0]);
				else
					oled.Display_hbmp(4+pit[MENUL2IX].current,40,16,15,iconnotok,color_setitem[0]);
				oled.OLED_SHF12x24(28+pit[MENUL2IX].current,60,set.autoswtimec,color_setitem[1]);
				oled.Display_hbmp(20+36+pit[MENUL2IX].current,66,14,14,hzsec,color_setitem[1]);
				
				oled.Display_hbmp(20+pit[MENUL2IX].current,90,68,14,iconfansdis,color_setitem[2]);
				if(set.fanswdis)
					oled.Display_hbmp(4+pit[MENUL2IX].current,90,16,15,iconok,color_setitem[2]);
				else
					oled.Display_hbmp(4+pit[MENUL2IX].current,90,16,15,iconnotok,color_setitem[2]);
				break;
			case 0x60:
				oled.Display_hbmp(pit[MENUL1I6X].current,6+pit[MENUL1I6Y].current,80,20,menusetuid,color_menu[5]);
			
				oled.OLED_SHF12x24(pit[MENUL2IX].current,50,set.uid,color_now);
				oled.Draw_Line(pit[MENUL2S1X].current,73,pit[MENUL2S2X].current,73,color_half);//
				oled.Draw_Line(pit[MENUL2S1X].current,50,pit[MENUL2S2X].current,50,color_half);//
				oled.Display_hbmp(92+pit[MENUL2IX].current,74,24,14,iconuid,color_half);
				break;
		}	
	}
}

void NORMAL_Mode_Run(void)
{ 
	switch(DataDisType)
	{
		case 3:
			if(Device_Msg.cpufan>0)
			{
				
				SetCurrent(POSNRCD,0+8) ;
				SetTarget(POSNRCD,0+8);
				SetTarget(CRTVANE,Device_Msg.cpufan);
				HWDisType = CU_CPU;
				Show_Float = False;
				sprintf(DataDis,"%04d",(u16)pit[CRTVANE].target);
				UnitDisType=UT_RPM;
				pit[CRTVADS].target = pit[CRTVANE].target/50/80*118;
				
				if(pit[CRTVADS].target>=117)
					pit[CRTVADS].target=117;
			}
			else if(Current_Mode != MODE_GAME)
			{
				DataDisType++;return;
//				sprintf(DataDis,"----");
//				UnitDisType=UT_RPM;
//				pit[CRTVANE].target = 0;
			}
			break;
		case 0:
			if(Device_Msg.cputemp>0)
			{
				SetTarget(POSNRCD,11+8)  ;
				pit[CRTVANE].target = Device_Msg.cputemp/10;
				HWDisType = CU_CPU;
				Show_Float = True;
				sprintf(DataDis,"%02d",(u16)pit[CRTVANE].target);
				sprintf(DataDisf,"%01d",Device_Msg.cputemp%10);
				UnitDisType=UT_DEG;
				
				pit[CRTVADS].target = pit[CRTVANE].target/80*118;
				
				if(pit[CRTVADS].target>=117)
					pit[CRTVADS].target=117;
				
			}
			else if(Current_Mode != MODE_GAME)
			{
				DataDisType++;return;
			}
			break;
		case 1:
			if(Device_Msg.cpuclock>0)
			{
				SetCurrent(POSNRCD,0+8) ;
				SetTarget(POSNRCD,0+8)  ;
				pit[CRTVANE].target = Device_Msg.cpuclock;
				HWDisType = CU_CPU;
				Show_Float = False;
				sprintf(DataDis,"%04d",(u16)pit[CRTVANE].target);
				UnitDisType=UT_MHZ;
				pit[CRTVADS].target = pit[CRTVANE].target/50/80*118;
				
				if(pit[CRTVADS].target>=117)
					pit[CRTVADS].target=117;
			}
			else if(Current_Mode != MODE_GAME)
			{
				DataDisType++;return;
//				sprintf(DataDis,"----");
//				UnitDisType=UT_MHZ;
//				pit[CRTVANE].target = 0;
			}
			break;
		case 2:
			SetTarget(POSNRCD,11+8)  ;
			pit[CRTVANE].target = Device_Msg.cpuload/10;
			HWDisType = CU_CPU;
			Show_Float = True;
//			if(Device_Msg.cpuload>0)
			{
				sprintf(DataDis,"%02d",(u16)pit[CRTVANE].target);
				sprintf(DataDisf,"%01d",Device_Msg.cpuload%10);
				UnitDisType=UT_PREC;
				pit[CRTVADS].target = pit[CRTVANE].target/80*118;
				
				if(pit[CRTVADS].target>=117)
					pit[CRTVADS].target=117;
				
			}break;
		case 7:
			if(Device_Msg.gpufan>0)
			{
				SetCurrent(POSNRCD,0+8) ;
				SetTarget(POSNRCD,0+8) ;
				pit[CRTVANE].target = Device_Msg.gpufan;
				HWDisType = CU_GPU;
				Show_Float = False;
				sprintf(DataDis,"%04d",(u16)pit[CRTVANE].target);
				UnitDisType=UT_RPM;
				pit[CRTVADS].target = pit[CRTVANE].target/50/80*118;
				if(pit[CRTVADS].target>=117)
					pit[CRTVADS].target=117;
				
			}
			else if(Current_Mode != MODE_GAME)
			{
				DataDisType++;return;
//				sprintf(DataDis,"----");
//				UnitDisType=UT_RPM;
//				pit[CRTVANE].target = 0;
			}
			break;
		case 4:
			if(Device_Msg.gputemp>0)
			{
				SetTarget(POSNRCD,11+8) ;
				pit[CRTVANE].target = Device_Msg.gputemp/10;
				HWDisType = CU_GPU;
				Show_Float = True;
				sprintf(DataDis,"%02d",(u16)pit[CRTVANE].target);
				sprintf(DataDisf,"%01d",Device_Msg.gputemp%10);
				UnitDisType=UT_DEG;
				pit[CRTVADS].target = pit[CRTVANE].target/80*118;
				
				if(pit[CRTVADS].target>=117)
					pit[CRTVADS].target=117;
			}
			else if(Current_Mode != MODE_GAME)
			{
				DataDisType++;return;
			}
			break;
		case 5:
			if(Device_Msg.gpuclock>0)
			{
				SetCurrent(POSNRCD,0+8) ;
				SetTarget(POSNRCD,0+8) ;
				pit[CRTVANE].target = Device_Msg.gpuclock;
				HWDisType = CU_GPU;
				Show_Float = False;
				sprintf(DataDis,"%04d",(u16)pit[CRTVANE].target);
				UnitDisType=UT_MHZ;
				pit[CRTVADS].target = pit[CRTVANE].target/50/80*118;
				
				if(pit[CRTVADS].target>=117)
					pit[CRTVADS].target=117;
			}
			else if(Current_Mode != MODE_GAME)
			{
				DataDisType++;return;
//				sprintf(DataDis,"----");
//				UnitDisType=UT_MHZ;
//				pit[CRTVANE].target = 0;
			}
			break;
		case 6:
			SetTarget(POSNRCD,11+8);
			pit[CRTVANE].target = Device_Msg.gpuload/10;
			HWDisType = CU_GPU;
			Show_Float = True;
//			if(Device_Msg.gpuload>0)
			{
				sprintf(DataDis,"%02d",(u16)pit[CRTVANE].target);
				sprintf(DataDisf,"%01d",Device_Msg.gpuload%10);
				UnitDisType=UT_PREC;
				
				pit[CRTVADS].target = pit[CRTVANE].target/80*118;
				
				if(pit[CRTVADS].target>=117)
					pit[CRTVADS].target=117;
				
			}break;
		case 8:
			SetTarget(POSNRCD,11+8);
			pit[CRTVANE].target = Device_Msg.ramload/10;
			HWDisType = CU_RAM;
			Show_Float = True;
//			if(Device_Msg.gpuload>0)
			{
				sprintf(DataDis,"%02d",(u16)pit[CRTVANE].target);
				sprintf(DataDisf,"%01d",Device_Msg.ramload%10);
				UnitDisType=UT_PREC;
				pit[CRTVADS].target = pit[CRTVANE].target/80*118;
				
				if(pit[CRTVADS].target>=117)
					pit[CRTVADS].target=117;
				
			}break;
	}
}

void GAME_Mode_In(void)
{
	SetTarget(SSLF,8) ;
	SetTarget(SSRT,66) ;
	SetTarget(SSMLF,8);
	SetTarget(SSMRT,98);
	SetTarget(SSLLF,40);
	SetTarget(SSLRT,88);
	SetTarget(SSUP,0);
	SetTarget(SSDN,112-7);
	SetTarget(SSRD,5);
	
	SetCurrent(SSLF,8-80) ;
	SetCurrent(SSRT,66+80) ;
	SetCurrent(SSMLF,8-120);
	SetCurrent(SSMRT,98+120);
	SetCurrent(SSLLF,40-20);
	SetCurrent(SSLRT,88+20);
	SetCurrent(SSUP,0-20);
	SetCurrent(SSDN,112-7+40);
	SetCurrent(SSRD,5-5);
}

void GAME_Mode_Out(void)
{
	SetTarget(SSLF,8-80) ;
	SetTarget(SSRT,66+80) ;
	SetTarget(SSMLF,8-88);
	SetTarget(SSMRT,98+88);
	SetTarget(SSLLF,40-20);
	SetTarget(SSLRT,88+20);
	SetTarget(SSUP,0-20);
	SetTarget(SSDN,112-7+40);
	SetTarget(SSRD,5-5);
}

void NORMAL_Mode_In(void)
{
	SetCurrent(POSNBAR,148) ;
	SetCurrent(POSNBAT,170) ;
	SetCurrent(POSNRCD,4) ;
	SetTarget(POSNRCT,25);
	SetTarget(POSNTOP,0);
	SetTarget(POSNBAR,103);
	SetTarget(POSNBAT,115);
	SetTarget(DAMPTYP,0);
	
}

void NORMAL_Mode_Out(void)
{
	SetTarget(POSNRCT,-73) ;
	SetTarget(POSNTOP,60) ;
	SetTarget(POSNBAR,148) ;
	SetTarget(POSNBAT,170) ;
	SetTarget(DAMPTYP,0);
	
}

void NORMAL_Display(void)
{
	if(Device_Cmd.commandtoptheme<=6)
	{
		oled.Display_bmp(pit[POSNTOP].current,pit[POSNRCT].current-25,128,25,Corn_Top[Device_Cmd.commandtoptheme]);
	}
	else
	{
		oled.Display_bmp(pit[POSNTOP].current,pit[POSNRCT].current-25,128,25,Corn_Top[5]);
	}
		
	oled.Display_bbmp(0,pit[POSNRCT].current,128,73,BMP_DataBackGround);
	oled.Display_bbmp(89,pit[POSNRCT].current+69,35,5,Corn_BarUnit[UnitDisType],color_half);
	oled.OLED_SF22x40(pit[POSNRCD].current,11+pit[POSNRCT].current,DataDis);
	if(pit[DAMPTYP].match)
		oled.Display_bbmp(10,pit[POSNRCT].current+62,23,7,Corn_DataType[HWDisType],color_half);
	else
		oled.Display_bbmp(10,pit[POSNRCT].current+62,23,7,Corn_DataType[HWDisType]);
	oled.Display_bbmp(98,11+pit[POSNRCT].current,24,24,Corn_Unit[UnitDisType],color_half);
	if((Show_Float)&&pit[CRTVANE].target < 100)
	{
		oled.OLED_SF12x24(pit[POSNRCD].current+52,pit[POSNRCT].current+27,DataDisf,color_half);
		oled.Fill_Rect(pit[POSNRCD].current+46,pit[POSNRCT].current+45,2,4,color_half);
	}
	oled.Display_bbmp(0,pit[POSNBAT].current,128,5,Corn_Rule);
	oled.Display_bbmp(0,pit[POSNBAT].current+5,128,5,Corn_RuleIndex,color_half);
	oled.Fill_Rect(3+2,pit[POSNBAR].current+2,pit[CRTVADS].current,6,color_half);
	oled.Draw_Rect(3,pit[POSNBAR].current,121,10);
}



void ShowWeather(u16 Num,u16 hour)
{
	if (Num == 0) {//晴天
		if(hour>=18||hour<8)
		{
			oled.OLED_HF14x14(22-3+pit[PWPTLF].current,85,10,color_now);
			oled.OLED_HF14x14(36-3+pit[PWPTLF].current,85,3,color_now);
			oled.Display_bmp(-2+pit[PWPTLF].current/2,25+pit[PWPTLF].current,68,68,gImage_weather_citylist_ic_34_clear_mtrl);
		}
		else
		{
			oled.OLED_HF14x14(22-3+pit[PWPTLF].current,90,10,color_now);
			oled.OLED_HF14x14(36-3+pit[PWPTLF].current,90,3,color_now);
			oled.Display_bmp(-2+pit[PWPTLF].current/2,25+pit[PWPTLF].current,68,68,gImage_weather_citylist_ic_34_sunny_mtrl);
		}
	}
	else if (Num >= 1 && Num <= 3) {//多云
		if(hour>=18||hour<8)
			oled.Display_bmp(-2+pit[PWPTLF].current/2,25+pit[PWPTLF].current,68,68,gImage_weather_citylist_ic_34_mostlyclear_mtrl);
		else
			oled.Display_bmp(-2+pit[PWPTLF].current/2,25+pit[PWPTLF].current,68,68,gImage_weather_citylist_ic_34_partlysunny_mtrl);
		oled.OLED_HF14x14(22-3+pit[PWPTLF].current,85,4,color_now);
		oled.OLED_HF14x14(36-3+pit[PWPTLF].current,85,5,color_now);
	}
	else if (Num == 4) {//阴天
		oled.Display_bmp(-2+pit[PWPTLF].current/2,25+pit[PWPTLF].current,68,68,gImage_weather_citylist_ic_34_cloudy_mtrl);
		oled.OLED_HF14x14(22-3+pit[PWPTLF].current,80,15,color_now);
		oled.OLED_HF14x14(36-3+pit[PWPTLF].current,80,3,color_now);
	}
	else if (Num >= 5 && Num <= 17) {//有风
		oled.Display_bmp(-2+pit[PWPTLF].current/2,25+pit[PWPTLF].current,68,68,gImage_weather_citylist_ic_34_windy_mtrl);
		oled.OLED_HF14x14(22-3+pit[PWPTLF].current,85,11,color_now);
		oled.OLED_HF14x14(36-3+pit[PWPTLF].current,85,20,color_now);
	}
	else if (Num >= 18 && Num <= 21) {//小雨
		oled.Display_bmp(-2+pit[PWPTLF].current/2,25+pit[PWPTLF].current,68,68,gImage_weather_citylist_ic_34_shower_mtrl);
		oled.OLED_HF14x14(22-3+pit[PWPTLF].current,88,8,color_now);
		oled.OLED_HF14x14(36-3+pit[PWPTLF].current,88,16,color_now);
	}
	else if (Num >= 22 && Num <= 29) {//大雨
		oled.Display_bmp(-2+pit[PWPTLF].current/2,25+pit[PWPTLF].current,68,68,gImage_weather_citylist_ic_34_rain_mtrl);
		oled.OLED_HF14x14(22-3+pit[PWPTLF].current,88,7,color_now);
		oled.OLED_HF14x14(36-3+pit[PWPTLF].current,88,16,color_now);
	}
	else if (Num >= 30 && Num <= 32) {//小雨
		oled.Display_bmp(-2+pit[PWPTLF].current/2,25+pit[PWPTLF].current,68,68,gImage_weather_citylist_ic_34_shower_mtrl);
		oled.OLED_HF14x14(22-3+pit[PWPTLF].current,88,8,color_now);
		oled.OLED_HF14x14(36-3+pit[PWPTLF].current,88,16,color_now);
	}
	else if (Num >= 33 && Num <= 40) {//大雨
		oled.Display_bmp(-2+pit[PWPTLF].current/2,25+pit[PWPTLF].current,68,68,gImage_weather_citylist_ic_34_rain_mtrl);
		oled.OLED_HF14x14(22-3+pit[PWPTLF].current,88,7,color_now);
		oled.OLED_HF14x14(36-3+pit[PWPTLF].current,88,16,color_now);
	}
	else if (Num >= 41 && Num <= 49) {//下雪
		oled.Display_bmp(-2+pit[PWPTLF].current/2,25+pit[PWPTLF].current,68,68,gImage_weather_citylist_ic_34_snow_mtrl);
		oled.OLED_HF14x14(22-3+pit[PWPTLF].current,88,6,color_now);
		oled.OLED_HF14x14(36-3+pit[PWPTLF].current,88,17,color_now);
	}
	else if (Num >= 50 && Num <= 54) {//沙尘
		oled.Display_bmp(-2+pit[PWPTLF].current/2,25+pit[PWPTLF].current,68,68,gImage_weather_citylist_ic_34_windy_mtrl);
		oled.OLED_HF14x14(22-3+pit[PWPTLF].current,85,13,color_now);
		oled.OLED_HF14x14(36-3+pit[PWPTLF].current,85,9,color_now);
	}
	else if (Num >= 55 && Num <= 64) {//雾霾
		oled.Display_bmp(-2+pit[PWPTLF].current/2,25+pit[PWPTLF].current,68,68,gImage_weather_citylist_ic_34_fog_mtrl);
		oled.OLED_HF14x14(22-3+pit[PWPTLF].current,88,18,color_now);
		oled.OLED_HF14x14(36-3+pit[PWPTLF].current,88,19,color_now);
	}
	else {//未知
		oled.Display_bmp(-2+pit[PWPTLF].current/2,25+pit[PWPTLF].current,68,68,gImage_weather_citylist_ic_34_unknown_mtrl);
		oled.OLED_HF14x14(22-3+pit[PWPTLF].current,80,12,color_now);
		oled.OLED_HF14x14(36-3+pit[PWPTLF].current,80,14,color_now);
	}
}

void WEATH_Mode_In(void)
{
//	SetCurrent(PWPTDN,128);
//	SetCurrent(PWPTRTICON,40);
//	SetCurrent(PWPTLF,-80) ;
//	SetCurrent(PWPTUP,-20) ;
//	SetCurrent(PWPTRT,140);
//	SetCurrent(PWPTLINE,41);
}

void WEATH_Mode_Out(void)
{
	if(Display_Mode != MODE_WEATH_1&&Display_Mode != MODE_WEATH_2)
	{
		SetTarget(PWPTDN,128);
	}
	SetTarget(PWPTRTICON,40);
	SetTarget(PWPTUP,-20) ;
	SetTarget(PWPTLF,-80) ;
	SetTarget(PWPTRT,140);
	SetTarget(PWPTLINE,41);
	
	
}

void WEATH_Mode_Run()
{
	SetTarget(PWPTUP,12);
	SetTarget(PWPTLF,0);
	SetTarget(PWPTRT,0);
	SetTarget(PWPTDN,128-26);
	SetTarget(PWPTRTICON,0);
	SetTarget(PWPTLINE,0);
	
}

void WEATH_Display(void)
{
	oled.Display_bmp(0,pit[PWPTDN].current,128,30,Bmp_Green);
	oled.OLED_HF14x14(49,pit[PWPTUP].current,2,color_now);//今
	oled.OLED_HF14x14(63,pit[PWPTUP].current,3,color_now);//天
	ShowWeather(WiFi_Msg.weathernum,own_hour);
	oled.Display_bmp(32+pit[PWPTRTICON].current,40-5,24,24,Icon_Temp);
	oled.Display_bmp(32+pit[PWPTRTICON].current,65-5,24,24,Icon_Humi);
	
	if(cont_str_1(WiFi_Msg.utemp) == 1)
	{
		oled.OLED_SHF12x24(68+20+6+pit[PWPTRT].current,40-4,WiFi_Msg.utemp,color_now);oled.OLED_HF14x14(92+20+pit[PWPTRT].current-24+6+cont_str_1(WiFi_Msg.utemp)*12,42-4,1,color_half);
	}
	else
	{
		oled.OLED_SHF12x24(68+20+pit[PWPTRT].current,40-4,WiFi_Msg.utemp,color_now);oled.OLED_HF14x14(92+20+pit[PWPTRT].current-24+cont_str_1(WiFi_Msg.utemp)*12,42-4,1,color_half);
	}
	if(cont_str_1(WiFi_Msg.uhumidity) == 1)
	{
		oled.OLED_SHF12x24(68+20+6+pit[PWPTRT].current,65-4,WiFi_Msg.uhumidity,color_now);oled.OLED_HF14x14(92+20+6+pit[PWPTRT].current,70-4,0,color_half);
	}
	else
	{
		oled.OLED_SHF12x24(68+20+pit[PWPTRT].current,65-4,WiFi_Msg.uhumidity,color_now);oled.OLED_HF14x14(92+20+pit[PWPTRT].current,70-4,0,color_half);
	}
	
	oled.Draw_Line(68+20-3+pit[PWPTLINE].current,62-3,68+20+38,62-3,color_half);
	
	
}


void WEATH_1_Mode_In(void)
{
//	if(Current_Mode != MODE_WEATH&&Current_Mode != MODE_WEATH_2)
//	{
//		SetCurrent(PWPTDN,128);
//	}
//	SetCurrent(PWPTRTICON,40);
//	SetCurrent(PWPTLF,-80) ;
//	SetCurrent(PWPTUP,-20) ;
//	SetCurrent(PWPTRT,140);
//	SetCurrent(PWPTLINE,41);
}

void WEATH_1_Mode_Out(void)
{
	if(Display_Mode != MODE_WEATH&&Display_Mode != MODE_WEATH_2)
	{
		SetTarget(PWPTDN,128);
	}
	SetTarget(PWPTRTICON,40);
	SetTarget(PWPTUP,-20) ;
	SetTarget(PWPTLF,-80) ;
	SetTarget(PWPTRT,140);
	SetTarget(PWPTLINE,41);
	
}

void WEATH_1_Mode_Run()
{
	SetTarget(PWPTUP,12);
	SetTarget(PWPTLF,0);
	SetTarget(PWPTRT,0);
	SetTarget(PWPTDN,128-26);
	SetTarget(PWPTRTICON,0);
	SetTarget(PWPTLINE,0);
	
}

void WEATH_1_Display(void)
{
	oled.Display_bmp(0,pit[PWPTDN].current,128,30,Bmp_Green);
	oled.OLED_HF14x14(49,pit[PWPTUP].current,21,color_now);//明
	oled.OLED_HF14x14(63,pit[PWPTUP].current,3,color_now);//天
	ShowWeather(WiFi_Msg.weather1num,own_hour);
	oled.Display_bmp(32+pit[PWPTRTICON].current,40-5,24,24,Icon_Night);
	oled.Display_bmp(32+pit[PWPTRTICON].current,65-5,24,24,Icon_Day);
	
	
	if(cont_str_1(WiFi_Msg.untemp1) == 1)
	{
		oled.OLED_SHF12x24(68+20+6+pit[PWPTRT].current,40-4,WiFi_Msg.untemp1,color_now);oled.OLED_HF14x14(92+20+pit[PWPTRT].current-24+cont_str_1(WiFi_Msg.untemp1)*12+6,42-4,1,color_half);
	}
	else
	{
		oled.OLED_SHF12x24(68+20+pit[PWPTRT].current,40-4,WiFi_Msg.untemp1,color_now);oled.OLED_HF14x14(92+20+pit[PWPTRT].current-24+cont_str_1(WiFi_Msg.untemp1)*12,42-4,1,color_half);
	}
	
	if(cont_str_1(WiFi_Msg.utemp1) == 1)
	{
		oled.OLED_SHF12x24(68+20+6+pit[PWPTRT].current,65-4,WiFi_Msg.utemp1,color_now);oled.OLED_HF14x14(92+20+pit[PWPTRT].current-24+cont_str_1(WiFi_Msg.utemp1)*12+6,70-4,1,color_half);
	}
	else
	{
		oled.OLED_SHF12x24(68+20+pit[PWPTRT].current,65-4,WiFi_Msg.utemp1,color_now);oled.OLED_HF14x14(92+20+pit[PWPTRT].current-24+cont_str_1(WiFi_Msg.utemp1)*12,70-4,1,color_half);
	}
	
	oled.Draw_Line(68+20-3+pit[PWPTLINE].current,62-3,68+20+38,62-3,color_half);
	
	
}


void WEATH_2_Mode_In(void)
{
//	if(Current_Mode != MODE_WEATH&&Current_Mode != MODE_WEATH_1)
//	{
//		SetCurrent(PWPTDN,128);
//	}
//		SetCurrent(PWPTRTICON,40);
//	SetCurrent(PWPTRT,140);
//	SetCurrent(PWPTUP,-20) ;
//	SetCurrent(PWPTLF,-80) ;
//	SetCurrent(PWPTLINE,41);
}

void WEATH_2_Mode_Out(void)
{
	if(Display_Mode != MODE_WEATH&&Display_Mode != MODE_WEATH_1)
	{
		SetTarget(PWPTDN,128);
	}
		SetTarget(PWPTRTICON,40);
	SetTarget(PWPTUP,-20) ;
	SetTarget(PWPTLF,-80) ;
	SetTarget(PWPTRT,140);
	SetTarget(PWPTLINE,41);
	
}

void WEATH_2_Mode_Run()
{
	SetTarget(PWPTUP,12);
	SetTarget(PWPTLF,0);
	SetTarget(PWPTRT,0);
	SetTarget(PWPTDN,128-26);
	SetTarget(PWPTRTICON,0);
	SetTarget(PWPTLINE,0);
	
}

void WEATH_2_Display(void)
{
	oled.Display_bmp(0,pit[PWPTDN].current,128,30,Bmp_Green);
	oled.OLED_HF14x14(49,pit[PWPTUP].current,22,color_now);//后
	oled.OLED_HF14x14(63,pit[PWPTUP].current,3,color_now);//天
	ShowWeather(WiFi_Msg.weather2num,own_hour);
	oled.Display_bmp(32+pit[PWPTRTICON].current,40-5,24,24,Icon_Night);
	oled.Display_bmp(32+pit[PWPTRTICON].current,65-5,24,24,Icon_Day);
	
	
	if(cont_str_1(WiFi_Msg.untemp2) == 1)
	{
		oled.OLED_SHF12x24(68+20+6+pit[PWPTRT].current,40-4,WiFi_Msg.untemp2,color_now);oled.OLED_HF14x14(92+20+pit[PWPTRT].current-24+cont_str_1(WiFi_Msg.untemp2)*12+6,42-4,1,color_half);
	}
	else
	{
		oled.OLED_SHF12x24(68+20+pit[PWPTRT].current,40-4,WiFi_Msg.untemp2,color_now);oled.OLED_HF14x14(92+20+pit[PWPTRT].current-24+cont_str_1(WiFi_Msg.untemp2)*12,42-4,1,color_half);
	}
	
	if(cont_str_1(WiFi_Msg.utemp2) == 1)
	{
		oled.OLED_SHF12x24(68+20+6+pit[PWPTRT].current,65-4,WiFi_Msg.utemp2,color_now);oled.OLED_HF14x14(92+20+pit[PWPTRT].current-24+cont_str_1(WiFi_Msg.utemp2)*12+6,70-4,1,color_half);
	}
	else
	{
		oled.OLED_SHF12x24(68+20+pit[PWPTRT].current,65-4,WiFi_Msg.utemp2,color_now);oled.OLED_HF14x14(92+20+pit[PWPTRT].current-24+cont_str_1(WiFi_Msg.utemp2)*12,70-4,1,color_half);
	}
	oled.Draw_Line(68+20-3+pit[PWPTLINE].current,62-3,68+20+38,62-3,color_half);
}

void TIME_Mode_In(void)
{
	pit[RDHourColor].target = oled.WheelPw(rand()%96);
	pit[RDMinColor].target = oled.WheelPw(rand()%96);
	pit[RDSecColor].target = oled.WheelP(rand()%96);
	SetCurrent(RDRadius, Radius*2);
	SetCurrent(RDRadiusC, RadiusC*2);
	SetCurrent(RDRadiusB, RadiusB*2);
	SetTarget(RDRadius, Radius);
	SetTarget(RDRadiusC, RadiusC);
	SetTarget(RDRadiusB, RadiusB);
	SetTarget(RDHourRadius, HourRadius);
	SetTarget(RDMinRadius, MinRadius);
	SetTarget(RDSecRadius, SecRadius);
	SetTarget(RDRuleDelaut, 0);
	if(own_hour%12<6)
	{
		SetTarget(PNTTIME,22);
	}
	else
	{
		SetTarget(PNTTIME,22+60);
		if(pit[PNTTIME].target!=22+60)
			SetCurrent(PNTTIME,128+50);
	}
}

void TIME_Mode_Out(void)
{
	SetTarget(RDRadius, Radius*2);
	SetTarget(RDRadiusC, RadiusC*2);
	SetTarget(RDRadiusB, RadiusB*2);
	SetTarget(RDRuleDelaut, 180);
	if(Display_Mode != MODE_DATE_1)
	{
		SetTarget(RDHourRadius, 0);
		SetTarget(RDMinRadius, 0);
		SetTarget(RDSecRadius, 0);
		SetTarget(PNTHOUR,-90);
		SetTarget(PNTMIN,-90);
		SetTarget(PNTSEC,-90);
		if(pit[PNTTIME].current<60)
		{
			SetTarget(PNTTIME,-50);
		}
		else
		{
			SetTarget(PNTTIME,128+50);
		}
	}
	DampCustormPos(RDRadius,0.1);
}

void TIME_Display(void)
{
	int i;
	for(i=0;i<60;i++)
	{
		if(i%5==0)
			oled.Draw_Line((OCX+(pit[RDRadius].current*cos((i*6+pit[RDRuleDelaut].current)*PI/180))),(OCY+(pit[RDRadius].current*sin((i*6+pit[RDRuleDelaut].current)*PI/180))),(OCX+(pit[RDRadiusB].current*cos((i*6+pit[RDRuleDelaut].current)*PI/180))),(OCY+(pit[RDRadiusB].current*sin((i*6+pit[RDRuleDelaut].current)*PI/180))),color_half);
		else
			oled.Draw_Line((OCX+(pit[RDRadius].current*cos((i*6+pit[RDRuleDelaut].current)*PI/180))),(OCY+(pit[RDRadius].current*sin((i*6+pit[RDRuleDelaut].current)*PI/180))),(OCX+(pit[RDRadiusC].current*cos((i*6+pit[RDRuleDelaut].current)*PI/180))),(OCY+(pit[RDRadiusC].current*sin((i*6+pit[RDRuleDelaut].current)*PI/180))),color_min);
	}
	oled.Draw_Circle(OCX,OCY,pit[RDRadius].current+2,color_half);
	oled.Draw_Circle(OCX,OCY,pit[RDRadius].current);

	
	oled.OLED_SNF6x8(pit[PNTTIME].current,60,vtimec);
	
	oled.Draw_Line((OCX+(pit[RDHourRadius].current*cos(pit[PNTHOUR].current*PI/180))),(OCY+(pit[RDHourRadius].current*sin(pit[PNTHOUR].current*PI/180))),OCX,OCY,2,pit[RDHourColor].target);
	oled.Draw_Line((OCX+(pit[RDMinRadius].current*cos(pit[PNTMIN].current*PI/180))),(OCY+(pit[RDMinRadius].current*sin(pit[PNTMIN].current*PI/180))),OCX,OCY,pit[RDMinColor].target);
	oled.Draw_Line((OCX+(pit[RDSecRadius].current*cos(pit[PNTSEC].current*PI/180))),(OCY+(pit[RDSecRadius].current*sin(pit[PNTSEC].current*PI/180))),OCX,OCY,pit[RDSecColor].target);
//	oled.Draw_Line((OCX+(pit[RDSecRadius].current/5*cos((pit[PNTSEC].current+180)*PI/180))),(OCY+(pit[RDSecRadius].current/5*sin((pit[PNTSEC].current+180)*PI/180))),OCX,OCY,pit[RDSecColor].target);

	oled.Fill_Circle(OCX,OCY,3,0);
	oled.Draw_Circle(OCX,OCY,1);
	oled.Draw_Circle(OCX,OCY,3,color_half);
}

void TIME_1_Mode_In(void)
{
	pit[RDHourColor].target = oled.WheelPw(rand()%96);
	pit[RDMinColor].target = oled.WheelPw(rand()%96);
	pit[RDSecColor].target = oled.WheelP(rand()%96);
	SetCurrent(RDRadiusA, Radius);
	SetTarget(RDRadiusA, Radius/2);
	SetTarget(RDHourRadius, HourRadius);
	SetTarget(RDMinRadius, MinRadius);
	SetTarget(RDSecRadius, SecRadius);
	if(own_hour%12<6)
	{
		SetTarget(PNTTIME,22);
	}
	else
	{
		SetTarget(PNTTIME,22+60);
		if(pit[PNTTIME].target!=22+60)
			SetCurrent(PNTTIME,128+50);
	}
}
	
void TIME_1_Mode_Out(void)
{
	SetTarget(RDRadiusA, Radius);
	if(Display_Mode != MODE_DATE)
	{
		SetTarget(RDHourRadius, 0);
		SetTarget(RDMinRadius, 0);
		SetTarget(RDSecRadius, 0);
		SetTarget(PNTHOUR,-90);
		SetTarget(PNTMIN,-90);
		SetTarget(PNTSEC,-90);
		if(pit[PNTTIME].current<60)
		{
			SetTarget(PNTTIME,-50);
		}
		else
		{
			SetTarget(PNTTIME,128+50);
		}
	}
	
}

void TIME_1_Display(void)
{
	oled.Draw_Circle(OCX+RLV,OCY+RLV,pit[RDRadiusA].current,1,color_now);
	oled.Draw_Circle(OCX+RLV,OCY+RLV,pit[RDRadiusA].current+2,1,color_half); //右下
	
	oled.Draw_Circle(OCX-RLV,OCY+RLV,pit[RDRadiusA].current,2,color_now);
	oled.Draw_Circle(OCX-RLV,OCY+RLV,(pit[RDRadiusA].current+2),2,color_half);	//左下
	
	oled.Draw_Circle(OCX-RLV,OCY-RLV,pit[RDRadiusA].current,4,color_now);
	oled.Draw_Circle(OCX-RLV,OCY-RLV,(pit[RDRadiusA].current+2),4,color_half); //左上
	
	oled.Draw_Circle(OCX+RLV,OCY-RLV,pit[RDRadiusA].current,3,color_now);
	oled.Draw_Circle(OCX+RLV,OCY-RLV,(pit[RDRadiusA].current+2),3,color_half); //右上
	
	oled.Draw_Line(OCX+RLV+pit[RDRadiusA].current,OCY+RLV,OCX+RLV+pit[RDRadiusA].current,OCY-RLV,color_now);//右侧引导线
	oled.Draw_Line(OCX+RLV+(pit[RDRadiusA].current+2),OCY+RLV,OCX+RLV+(pit[RDRadiusA].current+2),OCY-RLV,color_half);//右侧引导线
	
	oled.Draw_Line(OCX-RLV-pit[RDRadiusA].current,OCY+RLV,OCX-RLV-pit[RDRadiusA].current,OCY-RLV,color_now);//左侧引导线
	oled.Draw_Line(OCX-RLV-(pit[RDRadiusA].current+2),OCY+RLV,OCX-RLV-(pit[RDRadiusA].current+2),OCY-RLV,color_half);//左侧引导线

	oled.OLED_SNF6x8(pit[PNTTIME].current,60,vtimec);
	oled.Draw_Line(pit[PNTTIME].current-1,60+9,pit[PNTTIME].current+30,60+9,color_half);
	
	oled.Draw_Line((OCX+(pit[RDHourRadius].current*cos(pit[PNTHOUR].current*PI/180))),(OCY+(pit[RDHourRadius].current*sin(pit[PNTHOUR].current*PI/180))),OCX,OCY,2,pit[RDHourColor].target);
	oled.Draw_Line((OCX+(pit[RDMinRadius].current*cos(pit[PNTMIN].current*PI/180))),(OCY+(pit[RDMinRadius].current*sin(pit[PNTMIN].current*PI/180))),OCX,OCY,pit[RDMinColor].target);
	oled.Draw_Line((OCX+(pit[RDSecRadius].current*cos(pit[PNTSEC].current*PI/180))),(OCY+(pit[RDSecRadius].current*sin(pit[PNTSEC].current*PI/180))),OCX,OCY,pit[RDSecColor].target);
//	oled.Draw_Line((OCX+(pit[RDSecRadius].current/5*cos((pit[PNTSEC].current+180)*PI/180))),(OCY+(pit[RDSecRadius].current/5*sin((pit[PNTSEC].current+180)*PI/180))),OCX,OCY,pit[RDSecColor].target);

	oled.Fill_Circle(OCX,OCY,3,0);
	oled.Draw_Circle(OCX,OCY,1);
	oled.Draw_Circle(OCX,OCY,3,color_half);
}

void TIME_Mode_Run()
{
	pit[PNTHOUR].target = (own_hour%12-3)*30+own_min/2;
	pit[PNTMIN].target = (own_min-15)*6+own_sec/2/5;
	pit[PNTSEC].target = (own_sec-15)*6;
	if(pit[PNTHOUR].target == -90)
		pit[PNTHOUR].target = 270;
	else if(pit[PNTHOUR].current == 270)
		pit[PNTHOUR].current = -90;
	if(pit[PNTMIN].target == -90)
		pit[PNTMIN].target = 270;
	else if(pit[PNTMIN].current == 270)
		pit[PNTMIN].current = -90;
	if(pit[PNTSEC].target == -90)
		pit[PNTSEC].target = 270;
	else if(pit[PNTSEC].current == 270)
	{
		pit[RDHourColor].target = oled.WheelPw(rand()%96);
		pit[RDMinColor].target = oled.WheelPw(rand()%96);
		pit[RDSecColor].target = oled.WheelP(rand()%96);
		
		pit[PNTSEC].current = -90;
	}

	if(own_hour%12<6)
	{
		SetTarget(PNTTIME,22);
	}
	else
	{
		SetTarget(PNTTIME,22+60);
	}
}


void TIME_2_Mode(void)
{
	if(Flag_Refrash)
	{
		Flag_Refrash = False;
		if(Flag_Sleep)
		{
			Flag_Sleep = False;
			SLEEP_Display();
		}
		
		DampAutoPos();
//		if(Display_Mode == Current_Mode)
		{
			TIME_Mode_Run();
		}
//		else
//		{
//			Mode_Out();
//			if(pit[RDRadiusA].match)
//			{
//				Current_Mode = Display_Mode;
//				Mode_In();
//			}
//		}

		oled.Clear_Screen();
		motion.OLED_AllMotion(Device_Cmd.commandmotion,Device_Cmd.commandspeed);
//		oled.OLED_SHF18x26(19,37,vtimec,color_now);
		oled.OLED_SF22x40(10,42,"12");
		oled.OLED_SF22x40(10+64,42,"34");
		oled.Fill_Rect(60,50,8,8,color_half);
		oled.Fill_Rect(60,50+20,8,8,color_half);
	oled.Draw_Circle(OCX+RLV,OCY+RLV,pit[RDRadiusA].current,1,color_now);
	oled.Draw_Circle(OCX+RLV,OCY+RLV,pit[RDRadiusA].current+2,1,color_half); //右下
	
	oled.Draw_Circle(OCX-RLV,OCY+RLV,pit[RDRadiusA].current,2,color_now);
	oled.Draw_Circle(OCX-RLV,OCY+RLV,(pit[RDRadiusA].current+2),2,color_half);	//左下
	
	oled.Draw_Circle(OCX-RLV,OCY-RLV,pit[RDRadiusA].current,4,color_now);
	oled.Draw_Circle(OCX-RLV,OCY-RLV,(pit[RDRadiusA].current+2),4,color_half); //左上
	
	oled.Draw_Circle(OCX+RLV,OCY-RLV,pit[RDRadiusA].current,3,color_now);
	oled.Draw_Circle(OCX+RLV,OCY-RLV,(pit[RDRadiusA].current+2),3,color_half); //右上
	
	oled.Draw_Line(OCX+RLV+pit[RDRadiusA].current,OCY+RLV,OCX+RLV+pit[RDRadiusA].current,OCY-RLV,color_now);//右侧引导线
	oled.Draw_Line(OCX+RLV+(pit[RDRadiusA].current+2),OCY+RLV,OCX+RLV+(pit[RDRadiusA].current+2),OCY-RLV,color_half);//右侧引导线
	
	oled.Draw_Line(OCX-RLV-pit[RDRadiusA].current,OCY+RLV,OCX-RLV-pit[RDRadiusA].current,OCY-RLV,color_now);//左侧引导线
	oled.Draw_Line(OCX-RLV-(pit[RDRadiusA].current+2),OCY+RLV,OCX-RLV-(pit[RDRadiusA].current+2),OCY-RLV,color_half);//左侧引导线
//		oled.Draw_Line(18,37+28,18+18*5+1,37+28,color_half);
//		oled.Draw_Line(18,37+28+2,18+18*5+1,37+28+2,color_min);
//	oled.Display_bmp(0,128-30,128,30,Bmp_Green);
		oled.Refrash_Screen();
	}
	HAL_Delay(1);
}

void MUSIC_Mode_In(void)
{
	int i;
	for(i=0;i<sizeof(fall_pot);i++)
	{
		fall_pot[i] = 128;
		flow_pot[i] = 128;
	}
	ClearFFT();
	SetTarget(UNUSE,0);
}

void MUSIC_Mode_Out(void)
{
	ClearFFT();
	SetTarget(UNUSE,20);
}

void MUSIC_Mode_Run(void)
{
}


void MUSIC_Display(void)	
{
	static u8 Currentstyle = 0;
	int i;
	if(Currentstyle!=Device_Cmd.commandstyle)
	{
		Currentstyle=Device_Cmd.commandstyle;
		
		for(i=0;i<sizeof(fall_pot);i++)
		{
			fall_pot[i] = 128;
			flow_pot[i] = 128;
		}
	}
//		TIM3->CCR2=4000-Device_Msg.leftvol*4000/(256);
	switch(Device_Cmd.commandstyle)
	{
		case 1:fft.Display_Style1();break;
		case 2:fft.Display_Style2();break;
		case 3:fft.Display_Style3();break;
		case 4:fft.Display_Style4();break;
		case 5:fft.Display_Style5();break;
		case 6:fft.Display_Style6();break;
		default:fft.Display_Style1();break;
	}
}

void SLEEP_Display(void)
{
	u16 i;
	for(i=0;i<300;)
	{
		if(Flag_Refrash)
		{
			Flag_Refrash = False;i++;
			oled.Clear_Screen();
			motion.OLED_AllMotion(Device_Cmd.commandmotion,Device_Cmd.commandspeed);
			oled.Refrash_Screen();
		}
	}
	oled.Clear_Screen();
//UsartCommand(&huart1,0xA001,3);//获取设备名
	UsartCommand(&huart1,0xA002,3);//获取命令
//UsartCommand(&huart1,0xA003,3);//获取硬盘信息
}

void SWMode(void)
{
	if(Display_Mode == MODE_DATE||Display_Mode == MODE_DATE_1)
		Display_Mode = MODE_WEATH;
	else if(Display_Mode == MODE_WEATH)
		Display_Mode = MODE_WEATH_1;
	else if(Display_Mode == MODE_WEATH_1)
		Display_Mode = MODE_WEATH_2;
	else if(Display_Mode == MODE_WEATH_2)
	{	
		if(set.fanswdis) Display_Mode = MODE_BILI;
		else Display_Mode = DATA_THEME;
	}
	else
		Display_Mode = DATA_THEME;
}

u8 MODEPressCMD[] = {0xFF,0x55,0x06,0x01,0x02};

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	static u16 ContinueCount = 0;
	static u16 TimeCount = 0;
	static u16 TimeRun = 0;
	
	if(htim->Instance == htim5.Instance)
	{
		own_sec++;
		if(own_sec>=60)
		{
			own_sec=0;
			own_min++;
			if(own_min>=60)
			{
				own_min=0;
				own_hour++;
				if(own_hour>=24)
					own_hour=0;
			}
		}
		sprintf(vtimec,"%02d:%02d",own_hour,own_min);
	}
	if(htim->Instance == htim6.Instance)
	{
		if(ContinueCount++>20)
		{
			ContinueCount = 0;
			HAL_TIM_Base_Stop_IT(&htim6);
		}
	}
	if(htim->Instance == htim7.Instance)
	{
		if(Device_Cmd.commandgametype!=0xF)
		{
			DataDisType = Device_Cmd.commandgametype;
			pit[DAMPTYP].current = 30;
			TimeRun = 0;
		}
		else
		{
			if(TimeRun++>40)
			{
				TimeRun = 0;
				{
					DataDisType++;
					pit[DAMPTYP].current = 30;
					if(DataDisType>=8)
						DataDisType=0;
				}
			}
		}
		switch(Device_Cmd.commandrgbmode)
		{
			case 1:oled.Set_Wheelf(TimeCount%96);break;
			case 2:oled.Set_Wheel(TimeCount%96);break;
			case 3:oled.Set_Wheelf(Device_Cmd.commandrgbcolor*96/256);break;
			default:oled.Set_Wheelf(Device_Cmd.commandrgbcolor*96/256);break;
		}
		TimeCount++;
		
#if Dounsn == 1
		if(set.autoswdis&&Display_Mode!=MODE_MENU)
		{
			if(CptOnline != False&&Device_Cmd.commandmode != 1)
			{DisSwRun = 0;}
			else{
				DisSwRun++;
				if(DisSwRun>=set.autoswtime*2)
				{
					SWMode();
					DisSwRun = 0;
				}
			}
		}
		else if(Display_Mode==MODE_MENU)
		{
			MenuCount++;
			if(MenuCount >= 40)
			{
				AnalysisKey(MODEPressCMD);
				MenuCount = 0;
			}
		}
#endif
		if(OfflineCount < 1)
			OfflineCount++;
		else if(OfflineCount == 2)
		{
			ClearFFT();
			OfflineCount++;
		}
		else if(OfflineCount == 8)
		{
			InitData();
			CptOnline = False;
			Display_Mode = MODE_OFFLINE;
			OfflineCount++;
		}
		else if(OfflineCount <10)
		{
			OfflineCount++;
		}
		
#if Dounsn == 1
		if(WiFiOfflineCount == 28)
		{
//			InitWifi();
			WiFiOnline = False;
			WiFiOfflineCount++;
		}
		else if(WiFiOfflineCount <30)
		{
			WiFiOfflineCount++;
		}
#endif
		if(Uart_Overflow1_Flag)
		{
			Uart_Overflow1_Flag = False;
		}
		
		if(Uart_Overflow3_Flag)
		{
			Uart_Overflow3_Flag = False;
		}
//		printf("SleepCount:%d\r\n",SleepCount);
		if(SleepCount++>SLEEPTIME*2)
		{
			if(Device_Cmd.commandset&0x4)
				Flag_Sleep = True;
			SleepCount = 0;
		}
		if(SystemActive && pit[STSOK].match)
		{
			if(SaveFlag)
			{
				SaveFlag = False;
				Tranfcmd();
			}
//			if(UIDUpdate)
//			{
//				UIDUpdate = False;
//				UsartPrint(&huart3,ESP_Set_Uid,set.uid);
//			}
//			if(AddrUpdate)
//			{
//				AddrUpdate = False;
//				UsartPrint(&huart3,ESP_Set_Addr,set.addr);
//			}
		}
	}
	
	if(htim->Instance == htim8.Instance)
	{
//		SK6812_Wheel(0,Temp+=5);
//		SK6812_Refrash();
		Flag_Refrash = True;
		if(PulseRun>4020)
			dir = True;
		else if(PulseRun<50)
			dir = False;
			
		if(dir)
			TIM3->CCR2 = (PulseRun-=50);
		else
			TIM3->CCR2 = (PulseRun+=50);
	}
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
