#ifndef __OLED_DRIVER_H
#define __OLED_DRIVER_H

#include "stm32f1xx_hal.h"
#include "ASCII_Font.h"
#include "weatherui.h"
#include "sys.h"


extern const unsigned char gImage_weather_ic_39_clear_mtrl[];
extern const unsigned char gImage_weather_ic_39_cloudy_mtrl[];
extern const unsigned char gImage_weather_ic_39_flurries_mtrl[];
extern const unsigned char gImage_weather_ic_39_fog_mtrl[];
extern const unsigned char gImage_weather_ic_39_hot_mtrl[];
extern const unsigned char gImage_weather_ic_39_hurricane_mtrl[];
extern const unsigned char gImage_weather_ic_39_ice_mtrl[];
extern const unsigned char gImage_weather_ic_39_mostlyclear_mtrl[];
extern const unsigned char gImage_weather_ic_39_partlysunny_mtrl[];
extern const unsigned char gImage_weather_ic_39_partlysunnywithflurries_mtrl[];
extern const unsigned char gImage_weather_ic_39_partlysunnywithshower_mtrl[];
extern const unsigned char gImage_weather_ic_39_partlysunnywiththundershower_mtrl[];
extern const unsigned char gImage_weather_ic_39_rain_mtrl[];
extern const unsigned char gImage_weather_ic_39_rainandsnowmixed_mtrl[];
extern const unsigned char gImage_weather_ic_39_shower_mtrl[];
extern const unsigned char gImage_weather_ic_39_snow_mtrl[];
extern const unsigned char gImage_weather_ic_39_sunny_mtrl[];
extern const unsigned char gImage_weather_ic_39_thunderstorm_mtrl[];
extern const unsigned char gImage_weather_ic_39_windy_mtrl[];


extern const unsigned char gImage_weather_citylist_ic_34_unknown_mtrl[];
extern const unsigned char gImage_weather_citylist_ic_34_clear_mtrl[];
extern const unsigned char gImage_weather_citylist_ic_34_cloudy_mtrl[];
extern const unsigned char gImage_weather_citylist_ic_34_flurries_mtrl[];
extern const unsigned char gImage_weather_citylist_ic_34_fog_mtrl[];
extern const unsigned char gImage_weather_citylist_ic_34_hot_mtrl[];
extern const unsigned char gImage_weather_citylist_ic_34_hurricane_mtrl[];
extern const unsigned char gImage_weather_citylist_ic_34_ice_mtrl[];
extern const unsigned char gImage_weather_citylist_ic_34_mostlyclear_mtrl[];
extern const unsigned char gImage_weather_citylist_ic_34_partlysunny_mtrl[];
extern const unsigned char gImage_weather_citylist_ic_34_partlysunnywithflurries_mtrl[];
extern const unsigned char gImage_weather_citylist_ic_34_partlysunnywithshower_mtrl[];
extern const unsigned char gImage_weather_citylist_ic_34_partlysunnywiththundershower_mtrl[];
extern const unsigned char gImage_weather_citylist_ic_34_rain_mtrl[];
extern const unsigned char gImage_weather_citylist_ic_34_rainandsnowmixed_mtrl[];
extern const unsigned char gImage_weather_citylist_ic_34_shower_mtrl[];
extern const unsigned char gImage_weather_citylist_ic_34_snow_mtrl[];
extern const unsigned char gImage_weather_citylist_ic_34_sunny_mtrl[];
extern const unsigned char gImage_weather_citylist_ic_34_thunderstorm_mtrl[];
extern const unsigned char gImage_weather_citylist_ic_34_windy_mtrl[];



extern uint16_t color_now,color_half,color_min,color_minest;
extern const unsigned char Logo_asus[32768];
extern const unsigned char Logo_msi[32768];
extern const unsigned char Logo_amd[32768];
extern const unsigned char Logo_radeon[32768];
extern const unsigned char Logo_nvidia[32768];
extern const unsigned char Logo_razer[32768];
extern const unsigned char Logo_custorm[32768];
extern const unsigned char Logo_bilibili[32768];
extern const unsigned char Logo_wifioffline[32768];
extern const unsigned char Logo_nebula[32768];
extern const unsigned char BMP_Background[32768];
//extern const unsigned char gImage_test[];
extern const unsigned char BMP_TempBar[];
extern const unsigned char BMP_DataBackGround[];
extern const unsigned char Corn_BarUnit[][35];
extern const unsigned char Corn_Unit[][72];
extern const unsigned char Corn_Top[][6400];
extern const unsigned char Corn_Rule[];
extern const unsigned char Corn_RuleIndex[];
extern const unsigned char Corn_Bilibili[];
extern const unsigned char Bilibili22[];
extern const unsigned char Bilibili33[];
extern const unsigned char Bilibilibk[];
extern const unsigned char Icon_Temp[];
extern const unsigned char Icon_Humi[];
extern const unsigned char Icon_Day[];
extern const unsigned char Icon_Night[];
extern const unsigned char Bmp_Green[];
extern const unsigned char GeForce_19x23[];
extern const unsigned char gImage_weather_ic_39_partlysunnywiththundershower_mtrl[];
extern const unsigned char gImage_weather_citylist_ic_34_partlysunnywithshower_mtrl[];
#define UT_RPM 0
#define UT_DEG 1
#define UT_MHZ 2
#define UT_PREC 3

#define CU_CPU 0
#define CU_GPU 1
#define CU_RAM 2

#define TP_RAD 0
#define TP_NVI 1

#define OCX 64
#define OCY 64
#define PI 3.14159f

#define SSD1351_WIDTH   128
#define SSD1351_HEIGHT  128

#define SSD1351_CMD_SETCOLUMN       0x15
#define SSD1351_CMD_SETROW          0x75
#define SSD1351_CMD_WRITERAM        0x5C
#define SSD1351_CMD_READRAM         0x5D
#define SSD1351_CMD_SETREMAP        0xA0
#define SSD1351_CMD_STARTLINE       0xA1
#define SSD1351_CMD_DISPLAYOFFSET 	0xA2
#define SSD1351_CMD_DISPLAYALLOFF 	0xA4
#define SSD1351_CMD_DISPLAYALLON  	0xA5
#define SSD1351_CMD_NORMALDISPLAY 	0xA6
#define SSD1351_CMD_INVERTDISPLAY 	0xA7
#define SSD1351_CMD_FUNCTIONSELECT 	0xAB
#define SSD1351_CMD_DISPLAYOFF      0xAE
#define SSD1351_CMD_DISPLAYON     	0xAF
#define SSD1351_CMD_PRECHARGE       0xB1
#define SSD1351_CMD_DISPLAYENHANCE  0xB2
#define SSD1351_CMD_CLOCKDIV        0xB3
#define SSD1351_CMD_SETVSL          0xB4
#define SSD1351_CMD_SETGPIO 		    0xB5
#define SSD1351_CMD_PRECHARGE2      0xB6
#define SSD1351_CMD_SETGRAY         0xB8
#define SSD1351_CMD_USELUT          0xB9
#define SSD1351_CMD_PRECHARGELEVEL 	0xBB
#define SSD1351_CMD_VCOMH           0xBE
#define SSD1351_CMD_CONTRASTABC     0xC1
#define SSD1351_CMD_CONTRASTMASTER  0xC7
#define SSD1351_CMD_MUXRATIO        0xCA
#define SSD1351_CMD_COMMANDLOCK     0xFD
#define SSD1351_CMD_HORIZSCROLL     0x96
#define SSD1351_CMD_STOPSCROLL      0x9E
#define SSD1351_CMD_STARTSCROLL     0x9F


#define swap(a, b) { uint16_t t = a; a = b; b = t; }

#define OLED_CS PAout(6)
#define OLED_RST PAout(4)
#define OLED_A0 PAout(5)
#define OLED_WR PBout(0)
#define OLED_RD PBout(1)  

#define DATAOUT(x) GPIOC->ODR = x; //�������
#define DATAIN     GPIOC->IDR;   //��������

#define OLED_CMD  0		    //д����
#define OLED_DATA 1				//д����

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
typedef unsigned short uint16_t;
typedef unsigned char  uint8_t;
typedef unsigned char  uint8;                   /* defined for unsigned 8-bits integer variable 	�޷���8λ���ͱ���  */
typedef signed   char  int8;                    /* defined for signed 8-bits integer variable		�з���8λ���ͱ���  */
typedef unsigned short uint16;                  /* defined for unsigned 16-bits integer variable 	�޷���16λ���ͱ��� */
typedef signed   short int16;                   /* defined for signed 16-bits integer variable 		�з���16λ���ͱ��� */
typedef unsigned int   uint32;                  /* defined for unsigned 32-bits integer variable 	�޷���32λ���ͱ��� */
typedef signed   int   int32;                   /* defined for signed 32-bits integer variable 		�з���32λ���ͱ��� */
typedef float          fp32;                    /* single precision floating point variable (32bits) �����ȸ�������32λ���ȣ� */
typedef double         fp64;                    /* double precision floating point variable (64bits) ˫���ȸ�������64λ���ȣ� */


extern uint8_t color_byte[2];
extern uint8_t color_fill_byte[2];
extern uint16_t wheel;
#ifdef __cplusplus
extern "C" {
#endif

  class OLED_Driver {
    
    public: 
      OLED_Driver(void);
		
			void MOLED_Fill(uint16_t data);
		
			u16 ConvertColor(u8 red,u8 green,u8 blue);
      void Device_Init(void);
      void Clear_Screen(void);
      void Refrash_Screen(void);
      void Fill_Color(uint16_t color);
      void Fill_Color(void);
      void Set_Coordinate(uint16_t x, uint16_t y);
			uint16_t RandomColor(void);

      void Write_text(uint8_t data1);
      void Set_Address(uint8_t column, uint8_t row);
      
      void Set_Color(uint16_t color);
      void Set_FillColor(uint16_t color);
    
      void Invert(bool v);
      void Draw_Pixel(int16_t x, int16_t y);
      void Draw_Pixel(int16_t x, int16_t y,uint16_t color);
    
      void Write_Data(uint8_t dat);
      void Write_Data(uint8_t* dat_p, uint16_t length);
    
      void MWrite_Data(uint8_t dat,u8 Index);
      void MWrite_Data(uint8_t* dat_p, uint16_t length,u8 Index);
			
      void Draw_FastHLine(int16_t x, int16_t y, int16_t length);
      void Draw_FastHLine(int16_t x, int16_t y, int16_t length,uint16_t color);
			
      void Draw_FastVLine(int16_t x, int16_t y, int16_t length);
      void Draw_FastVLine(int16_t x, int16_t y, int16_t length,uint16_t color);
      void Write_Command(uint8_t data1);
      void MWrite_Command(uint8_t data1,u8 Index);
      void Display_bmp(const uint8_t *ch);
      void Display_bmp(int x,int y,int w,int h,const uint8_t *ch);
			void Display_bbmp(int x,int y,int w,int h,const uint8_t *ch);
			void Display_bbmp(int x,int y,int w,int h,const uint8_t *ch,uint16_t color);
			void Display_hbmp(int x,int y,int w,int h,const u8 *ch,uint16_t color);
			void Display_vifbmp(const uint8_t *ch);
      void Display_FadeinAll(const uint8_t *ch);
      void Display_FadeoutAll(void);
			void Display_SetDim(u8 Light);
			
			void Display_FraginAll(const uint8_t *ch);
			void Display_FragoutAll(void);
			
			void Set_DampColor(uint16_t color);
			void Set_Wheel(uint16_t WheelPos);
			void Set_Wheelf(uint16_t WheelPos);
			u16 WheelPw(u16 WheelPos);
			
			void OLED_SNF6x8(int x,int y,char *ch);
			void OLED_SF8x16(int x,int y,char *ch);
			void OLED_SF10x16(int x,int y,char *ch);
			void OLED_SF12x24(int x,int y,char *ch);
			void OLED_SF22x40(int x,int y,char *ch);
			
			void OLED_SF8x16(int x,int y,char *ch,uint16_t coloru,uint16_t colord);
			void OLED_SF10x16(int x,int y,char *ch,uint16_t coloru,uint16_t colord);
			void OLED_SF12x24(int x,int y,char *ch,uint16_t coloru,uint16_t colord);
			void OLED_SF22x40(int x,int y,char *ch,uint16_t coloru,uint16_t colord);
			
			void OLED_SF8x16(int x,int y,char *ch,uint16_t color);
			void OLED_SF10x16(int x,int y,char *ch,uint16_t color);
			void OLED_SF12x24(int x,int y,char *ch,uint16_t color);
			void OLED_SF22x40(int x,int y,char *ch,uint16_t color);
			void FlowColorFont(uint16_t coloru,uint16_t colord,u8 height);
			u16 WheelP(u16 WheelPos);
			
			void OLED_HF12x24(int x,int y,u8 Num,uint16_t color);
			void OLED_SHF12x24(int x,int y,char *ch,uint16_t color);
			void OLED_HF18x26(int x,int y,u8 Num,uint16_t color);
			void OLED_SHF18x26(int x,int y,char *ch,uint16_t color);
			void OLED_HF14x14(int x,int y,u8 Num,uint16_t color);
			
			void OLED_HFAny(int x,int y,int w,int h,u8 Num,const unsigned char *ch,uint16_t color);
			void OLED_SHFAny(int x,int y,char *ch,int w,uint16_t color);
    private:  
			void OLED_NF6x8(int x,int y,u8 Num,u8 Offset);
			void OLED_F8x16(int x,int y,u8 Num);
			void OLED_F10x16(int x,int y,u8 Num);
			void OLED_F12x24(int x,int y,u8 Num);
			void OLED_F22x40(int x,int y,u8 Num);
			void OLED_F8x16(int x,int y,u8 Num,uint16_t coloru,uint16_t colord);
			void OLED_F10x16(int x,int y,u8 Num,uint16_t coloru,uint16_t colord);
			void OLED_F12x24(int x,int y,u8 Num,uint16_t coloru,uint16_t colord);
			void OLED_F22x40(int x,int y,u8 Num,uint16_t coloru,uint16_t colord);
			void OLED_F8x16(int x,int y,u8 Num,uint16_t color);
			void OLED_F10x16(int x,int y,u8 Num,uint16_t color);
			void OLED_F12x24(int x,int y,u8 Num,uint16_t color);
			void OLED_F22x40(int x,int y,u8 Num,uint16_t color);
      uint8_t Float2U8(float Input);
      void RAM_Address(void);
			void Calc_Color(void);
  };



#ifdef __cplusplus
}
#endif
  
#endif

