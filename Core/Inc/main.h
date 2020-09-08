/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#define HIGH 1
#define LOW 0

#define True		1		
#define False		0		
 
/*!< STM32F10x Standard Peripheral Library old types (maintained for legacy purpose) */
typedef int32_t  s32;
typedef int16_t s16;
typedef int8_t  s8;

typedef const int32_t sc32;  /*!< Read Only */
typedef const int16_t sc16;  /*!< Read Only */
typedef const int8_t sc8;   /*!< Read Only */

typedef __IO int32_t  vs32;
typedef __IO int16_t  vs16;
typedef __IO int8_t   vs8;

typedef __I int32_t vsc32;  /*!< Read Only */
typedef __I int16_t vsc16;  /*!< Read Only */
typedef __I int8_t vsc8;   /*!< Read Only */

typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;

typedef const uint32_t uc32;  /*!< Read Only */
typedef const uint16_t uc16;  /*!< Read Only */
typedef const uint8_t uc8;   /*!< Read Only */

typedef __IO uint32_t  vu32;
typedef __IO uint16_t vu16;
typedef __IO uint8_t  vu8;

typedef __I uint32_t vuc32;  /*!< Read Only */
typedef __I uint16_t vuc16;  /*!< Read Only */
typedef __I uint8_t vuc8;   /*!< Read Only */
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 
//IO�ڵ�ַӳ��
#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C 
#define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C 
#define GPIOC_ODR_Addr    (GPIOC_BASE+12) //0x4001100C 
#define GPIOD_ODR_Addr    (GPIOD_BASE+12) //0x4001140C 
#define GPIOE_ODR_Addr    (GPIOE_BASE+12) //0x4001180C 
#define GPIOF_ODR_Addr    (GPIOF_BASE+12) //0x40011A0C    
#define GPIOG_ODR_Addr    (GPIOG_BASE+12) //0x40011E0C    

#define GPIOA_IDR_Addr    (GPIOA_BASE+8) //0x40010808 
#define GPIOB_IDR_Addr    (GPIOB_BASE+8) //0x40010C08 
#define GPIOC_IDR_Addr    (GPIOC_BASE+8) //0x40011008 
#define GPIOD_IDR_Addr    (GPIOD_BASE+8) //0x40011408 
#define GPIOE_IDR_Addr    (GPIOE_BASE+8) //0x40011808 
#define GPIOF_IDR_Addr    (GPIOF_BASE+8) //0x40011A08 
#define GPIOG_IDR_Addr    (GPIOG_BASE+8) //0x40011E08 
 
//IO�ڲ���,ֻ�Ե�һ��IO��!
//ȷ��n��ֵС��16!
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //��� 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //���� 

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //��� 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //���� 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //��� 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //���� 

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //��� 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //���� 

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //��� 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //����

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //��� 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //����

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //��� 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //����

//����Ϊ��ຯ��
void WFI_SET(void);		//ִ��WFIָ��
void INTX_DISABLE(void);//�ر������ж�
void INTX_ENABLE(void);	//���������ж�
void MSR_MSP(u32 addr);	//���ö�ջ��ַ

#define MAKEWORD(low, high)		(((u8)(low)) | (((u8)(high)) << 8))

extern uint8_t fall_pot[250];	//��¼����������
extern uint8_t flow_pot[250];

typedef struct{
	u8 autotimeset;
	char addr[7];
	u8 hour;
	u8 min;
	char hourc[3];
	char minc[3];
	u16 motionset;
	u16 rgbcolor;
	u16 rgbmode;
	char uid[20];
	u8 autoswdis;
	u8 autoswtime;
	char autoswtimec[3];
	u8 fanswdis;
}ConfigSet;
extern ConfigSet set;
	
extern u8 UIDUpdate;
extern u8 AddrUpdate;
extern u8 CptOnline;
extern u8 WiFiOnline;
#define Radius 60
#define RadiusC 56
#define RadiusB 53
#define HourRadius 30
#define MinRadius 40
#define SecRadius 50
#define RLV Radius/2
	
#define SLEEPTIME    20*60
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

void SLEEP_Display(void);

void OFFLINE_Mode_In(void);
void OFFLINE_Mode_Out(void);
void OFFLINE_Mode(void);

void NORMAL_Mode_In(void);
void NORMAL_Mode_Out(void);
void NORMAL_Mode_Run(void);
void NORMAL_Display(void);
void NORMAL_Mode(void);

void GAME_Mode_In(void);
void GAME_Mode_Out(void);
void GAME_Mode_Run(void);
void GAME_Display(void);
void GAME_Mode(void);

void TIME_Mode_In(void);
void TIME_Mode_Out(void);
void TIME_Mode_Run(void);
void TIME_Display(void);
void TIME_Mode(void);

void TIME_1_Mode_In(void);
void TIME_1_Mode_Out(void);
void TIME_1_Display(void);
void TIME_1_Mode(void);

void TIME_2_Mode_In(void);
void TIME_2_Mode_Out(void);
void TIME_2_Mode_Run(void);
void TIME_2_Display(void);
void TIME_2_Mode(void);

void BILI_Mode_In(void);
void BILI_Mode_Out(void);
void BILI_Mode_Run(void);
void BILI_Display(void);
void BILI_Mode(void);

void WEATH_Mode_In(void);
void WEATH_Mode_Out(void);
void WEATH_Mode_Run(void);
void WEATH_Display(void);
void WEATH_Mode(void);

void MENU_Mode_In(void);
void MENU_Mode_Out(void);
void MENU_Mode_Run(void);
void MENU_Display(void);
void MENU_Mode(void);

void WEATH_1_Mode_In(void);
void WEATH_1_Mode_Out(void);
void WEATH_1_Mode_Run(void);
void WEATH_1_Display(void);
void WEATH_1_Mode(void);

void WEATH_2_Mode_In(void);
void WEATH_2_Mode_Out(void);
void WEATH_2_Mode_Run(void);
void WEATH_2_Display(void);
void WEATH_2_Mode(void);

void MUSIC_Mode_In(void);
void MUSIC_Mode_Out(void);
void MUSIC_Mode_Run(void);
void MUSIC_Display(void);
void MUSIC_Mode(void);

void WAITWIFI_Mode(void);

void Display_Run(void);
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */
extern u16 Display_Mode;

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
#define MODE_DEFALUT      	0x00
#define MODE_OFFLINE    	  0x01
#define MODE_DATE    	  		0x02
#define MODE_MUSIC     			0x03
#define MODE_NORMAL   		  0x04
#define MODE_GAME  					0x05
#define MODE_SHOW		  		0x06
#define MODE_TIME		  		  0x07
#define MODE_BILI		  		  0x08
#define MODE_WEATH		  		  0x09
#define MODE_WEATH_1		  		  0x0A
#define MODE_WEATH_2		  		  0x0B
#define MODE_DATE_1    	  		0x0C
#define MODE_MENU    	  		0x0D

#define Nebula False
#define Dounsn True
extern u16 Selectitem;
extern u16 MenuLevel;
extern u16 DATA_THEME;
extern u16 DisSwRun;
extern u16 SleepCount;
extern u16 MenuCount;
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define OLED_D0_Pin GPIO_PIN_0
#define OLED_D0_GPIO_Port GPIOC
#define OLED_D1_Pin GPIO_PIN_1
#define OLED_D1_GPIO_Port GPIOC
#define OLED_D2_Pin GPIO_PIN_2
#define OLED_D2_GPIO_Port GPIOC
#define OLED_D3_Pin GPIO_PIN_3
#define OLED_D3_GPIO_Port GPIOC
#define OLED_RST_Pin GPIO_PIN_4
#define OLED_RST_GPIO_Port GPIOA
#define OLED_DC_Pin GPIO_PIN_5
#define OLED_DC_GPIO_Port GPIOA
#define OLED_CS_Pin GPIO_PIN_6
#define OLED_CS_GPIO_Port GPIOA
#define OLED_D5_Pin GPIO_PIN_5
#define OLED_D5_GPIO_Port GPIOC
#define OLED_WR_Pin GPIO_PIN_0
#define OLED_WR_GPIO_Port GPIOB
#define OLED_RD_Pin GPIO_PIN_1
#define OLED_RD_GPIO_Port GPIOB
#define OLED_PW_Pin GPIO_PIN_12
#define OLED_PW_GPIO_Port GPIOB
#define OLED_D6_Pin GPIO_PIN_6
#define OLED_D6_GPIO_Port GPIOC
#define OLED_D7_Pin GPIO_PIN_7
#define OLED_D7_GPIO_Port GPIOC
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
