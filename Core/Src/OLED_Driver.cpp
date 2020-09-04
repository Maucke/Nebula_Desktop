#include "OLED_Driver.h"
#include "main.h"
#include "gpio.h"
#include "stdlib.h"


uint8_t color_byte[2],color_Damp_byte[2];
uint8_t OLED_GRAM[256][128];
uint16_t wheel;

uint16_t color_now,color_half,color_min,color_minest;

#ifdef __cplusplus
extern "C"  {
#endif


OLED_Driver::OLED_Driver(void) {
}
  
u16 OLED_Driver::ConvertColor(u8 red,u8 green,u8 blue)
{
	return red<<11|green<<6|blue;
}

u16 FlowColorRAM[128];

void OLED_Driver::FlowColorFont(uint16_t coloru,uint16_t colord,u8 height)
{
	float Colorstep[3];
	int i;
	u16 red,green,blue;
	u16 red1,green1,blue1;

	red = coloru>>11;
	green = (coloru&0x7E0)>>5;
	blue = coloru&0x1F;
	
	red1 = colord>>11;
	green1 = colord&0x7E0>>5;
	blue1 = colord&0x1F;
	
	Colorstep[0]=float(red1-red)/height;
	Colorstep[1]=float(green1-green)/height;
	Colorstep[2]=float(blue1-blue)/height;
	
	for(i=0;i<height;i++)
	{
		red1 = (u8)(red+Colorstep[0]*i)&0x1f;
		green1 = (u8)(green+Colorstep[1]*i)&0x3f;
		blue1 = (u8)(blue+Colorstep[2]*i)&0x1f;
//		printf("%x %x %x\r\n",red1,green1,blue1);
//		HAL_Delay(100);
		FlowColorRAM[i] = red1<<11|green1<<5|blue1;
	}
}
void OLED_Driver::Set_Color(uint16_t color)  {
  
//  color_byte[0] = (uint8_t)(color >> 8);
//  color_byte[1] = (uint8_t)(color & 0x00ff);
	
	uint8_t red,green,blue;
	red = color_byte[0]>>3;
	green = ((color_byte[0]&0x7)<<3)|color_byte[1]>>5;
	blue = color_byte[1]&0x1f;
	
	color_now = red<<11|green<<5|blue;
	color_byte[0] = color_now>>8;
	color_byte[1] = color_now&0xff;
	red >>=1;
	green >>=1;
	blue >>=1;
	color_half = red<<11|green<<5|blue;
	red >>=1;
	green >>=1;
	blue >>=1;
	color_min = red<<11|green<<5|blue;
	red >>=1;
	green >>=1;
	blue >>=1;
	color_minest = red<<11|green<<5|blue;
}

uint16_t OLED_Driver::RandomColor(void){
	
	uint8_t red,green,blue;
	red = rand();
	__ASM("NOP");
	green = rand();
	__ASM("NOP");
	blue = rand();
	return (red<<11|green<<5|blue);
}

void OLED_Driver::Set_DampColor(uint16_t color)  {
  
  color_Damp_byte[0] = (uint8_t)(color >> 8);
  color_Damp_byte[1] = (uint8_t)(color & 0x00ff);
}



void OLED_Driver::Set_Wheel(u16 WheelPos)	{
	
	uint8_t red,green,blue;
	wheel = WheelPos;
	if(WheelPos < 32) 
	{
		red = 0;
		green = WheelPos;
		blue = (31 - WheelPos);
	}
	else if(WheelPos < (32*2)) 
	{          
		red = WheelPos-32;
		green = 32*2-1 - WheelPos;
		blue = 0;
	}
	else
	{
		red = (32*3)-1 - WheelPos;
		green = 0;
		blue = WheelPos-(32*2);
	}
	color_Damp_byte[0] = red<<3|(green>>2);
	color_Damp_byte[1] = green<<6|blue;
}

void OLED_Driver::Set_Wheelf(u16 WheelPos)	{
	
	uint8_t red,green,blue;
	wheel = WheelPos;
	if(WheelPos < 32) 
	{
		red = 31;
		green = WheelPos;
		blue = (31 - WheelPos);
	}
	else if(WheelPos < (32*2)) 
	{          
		red = WheelPos-32;
		green = 32*2-1 - WheelPos;
		blue = 31;
	}
	else
	{
		red = (32*3)-1 - WheelPos;
		green = 31;
		blue = WheelPos-(32*2);
	}
	color_Damp_byte[0] = red<<3|(green>>2);
	color_Damp_byte[1] = green<<6|blue;
}

u16 OLED_Driver::WheelP(u16 WheelPos)
{
	
	uint8_t red,green,blue;
	if(WheelPos < 32) 
	{
		red = 0;
		green = WheelPos;
		blue = (31 - WheelPos);
	}
	else if(WheelPos < (32*2)) 
	{          
		red = WheelPos-32;
		green = 32*2-1 - WheelPos;
		blue = 0;
	}
	else
	{
		red = (32*3)-1 - WheelPos;
		green = 0;
		blue = WheelPos-(32*2);
	}
	return (red<<11|green<<5|blue);
}	

u16 OLED_Driver::WheelPw(u16 WheelPos)
{
	
	uint8_t red,green,blue;
	if(WheelPos < 32) 
	{
		red = 31;
		green = WheelPos;
		blue = (31 - WheelPos);
	}
	else if(WheelPos < (32*2)) 
	{          
		red = WheelPos-32;
		green = 32*2-1 - WheelPos;
		blue = 31;
	}
	else
	{
		red = (32*3)-1 - WheelPos;
		green = 31;
		blue = WheelPos-(32*2);
	}
	return (red<<11|green<<5|blue);
}	

void OLED_Driver::Calc_Color(void){
				
	uint8_t red,green,blue;
	uint8_t red1,green1,blue1;
	red = color_byte[0]>>3;
	green = ((color_byte[0]&0x7)<<3)|color_byte[1]>>5;
	blue = color_byte[1]&0x1f;
	
	red1 = color_Damp_byte[0]>>3;
	green1 = ((color_Damp_byte[0]&0x7)<<3)|color_Damp_byte[1]>>5;
	blue1 = color_Damp_byte[1]&0x1f;
	
	if(red>red1)
	{
		red--;
	}
	else if(red<red1)
	{
		red++;
	}
	if(green>green1+1)
	{
		green-=2;
	}
	else if(green+1<green1)
	{
		green+=2;
	}
	if(blue>blue1)
	{
		blue--;
	}
	else if(blue<blue1)
	{
		blue++;
	}
	color_now = red<<11|green<<5|blue;
	color_byte[0] = color_now>>8;
	color_byte[1] = color_now&0xff;
	red >>=1;
	green >>=1;
	blue >>=1;
	color_half = red<<11|green<<5|blue;
	red >>=1;
	green >>=1;
	blue >>=1;
	color_min = red<<11|green<<5|blue;
	red >>=1;
	green >>=1;
	blue >>=1;
	color_minest = red<<11|green<<5|blue;
	
}


void OLED_Driver::Write_Command(uint8_t cmd)  {
	OLED_A0=OLED_CMD;
	OLED_CS=LOW;
	DATAOUT(cmd);
	OLED_CS=HIGH;
	OLED_A0=OLED_DATA;
}


void OLED_Driver::Write_Data(uint8_t dat) {
// 
//	OLED_CS=LOW;
	GPIOA->BRR = 1<<6;
	DATAOUT(dat);
	GPIOA->BSRR = 1<<6;
//	OLED_CS=HIGH;
  
}


void OLED_Driver::Write_Data(uint8_t* dat_p, uint16_t length) {
	int i;
  for(i=0;i<length;i++)
		Write_Data(dat_p[i]);
}


void OLED_Driver::RAM_Address(void)  {
  
  Write_Command(0x15);
  Write_Data(0x00);
  Write_Data(0x7f);

  Write_Command(0x75);
  Write_Data(0x00);
  Write_Data(0x7f);
}


void OLED_Driver::Refrash_Screen(void)  {
  
  int i,j;
  Calc_Color();
  RAM_Address();
  Write_Command(0x5C);
  for(i=0;i<128;i++)  {
    for(j=0;j<128;j++)  {
      Write_Data(OLED_GRAM[j*2][i]);//RAM data clear
      Write_Data(OLED_GRAM[j*2+1][i]);//RAM data clear
    }
  }
}
  

void OLED_Driver::Clear_Screen(void)  {
  
  int i,j;
  for(i=0;i<128;i++)  {
    for(j=0;j<128;j++)  {
      OLED_GRAM[2*i][j] = 0;
      OLED_GRAM[2*i+1][j] = 0;
    }
  }
}
void OLED_Driver::Fill_Color(void)  {
  
  int i,j;
  for(i=0;i<128;i++)  {
    for(j=0;j<128;j++)  {
      OLED_GRAM[2*i][j] = color_byte[0];
      OLED_GRAM[2*i+1][j] = color_byte[1];
    }
  }
}
  
void OLED_Driver::Fill_Color(uint16_t color)  {
  
  int i,j;
  color_byte[0] = (uint8_t)(color >> 8);
  color_byte[1] = (uint8_t)(color & 0xff);
  for(i=0;i<128;i++)  {
    for(j=0;j<128;j++)  {
      OLED_GRAM[2*i][j] = color_byte[0];
      OLED_GRAM[2*i+1][j] = color_byte[1];
    }
  }
}
  
void OLED_Driver::Set_Coordinate(uint16_t x, uint16_t y)  {

  if ((x >= SSD1351_WIDTH) || (y >= SSD1351_HEIGHT)) 
    return;
  //Set x and y coordinate
  Write_Command(SSD1351_CMD_SETCOLUMN);
  Write_Data(x);
  Write_Data(SSD1351_WIDTH-1);
  Write_Command(SSD1351_CMD_SETROW);
  Write_Data(y);
  Write_Data(SSD1351_HEIGHT-1);
  Write_Command(SSD1351_CMD_WRITERAM);
}
  
void OLED_Driver::Set_Address(uint8_t column, uint8_t row)  {
  
  Write_Command(SSD1351_CMD_SETCOLUMN);  
  Write_Data(column);	//X start 
  Write_Data(column);	//X end 
  Write_Command(SSD1351_CMD_SETROW); 
  Write_Data(row);	//Y start 
  Write_Data(row+7);	//Y end 
  Write_Command(SSD1351_CMD_WRITERAM); 
}
  
void OLED_Driver::Write_text(uint8_t dat) {
    
  uint8_t i;
    
  for(i=0;i<8;i++)  {
    if (dat & 0x01)	
      Write_Data(color_byte,2);
    else  {
      Write_Data(0x00);
      Write_Data(0x00);
    }
    dat >>= 1;
  }
}
  
void  OLED_Driver::Invert(bool v) {
  
  if (v)
    Write_Command(SSD1351_CMD_INVERTDISPLAY);
  else
    Write_Command(SSD1351_CMD_NORMALDISPLAY);
}

void OLED_Driver::Draw_Pixel(int16_t x, int16_t y)
{
  // Bounds check.
  if ((x >= SSD1351_WIDTH) || (y >= SSD1351_HEIGHT)) return;
  if ((x < 0) || (y < 0)) return;

	OLED_GRAM[2*x][y] = color_byte[0];
	OLED_GRAM[2*x+1][y] = color_byte[1];
  
}

void OLED_Driver::Draw_Pixel(int16_t x, int16_t y,uint16_t color)
{
  // Bounds check.
  if ((x >= SSD1351_WIDTH) || (y >= SSD1351_HEIGHT)) return;
  if ((x < 0) || (y < 0)) return;

	OLED_GRAM[2*x][y] = (uint8_t)(color >> 8);
	OLED_GRAM[2*x+1][y] = (uint8_t)(color & 0x00ff);
  
}
  
  
void OLED_Driver::Device_Init(void) {

  OLED_CS = LOW;
	OLED_WR=LOW;

  OLED_RST = LOW;
  HAL_Delay(40);
	OLED_RST = HIGH;
  HAL_Delay(20);
    
  Write_Command(0xfd);	// command lock
  Write_Data(0x12);
  Write_Command(0xfd);	// command lock
  Write_Data(0xB1);

  Write_Command(0xae);	// display off
  Write_Command(0xa4); 	// Normal Display mode

  Write_Command(0x15);	//set column address
  Write_Data(0x00);     //column address start 00
  Write_Data(0x7f);     //column address end 95
  Write_Command(0x75);	//set row address
  Write_Data(0x00);     //row address start 00
  Write_Data(0x7f);     //row address end 63	

  Write_Command(0xB3);
  Write_Data(0xF1);

  Write_Command(0xCA);	
  Write_Data(0x7F);

  Write_Command(0xa0);  //set re-map & data format
  Write_Data(0x74);     //Horizontal address increment

  Write_Command(0xa1);  //set display start line
  Write_Data(0x00);     //start 00 line

  Write_Command(0xa2);  //set display offset
  Write_Data(0x00);

  Write_Command(0xAB);	
  Write_Command(0x01);	

  Write_Command(0xB4);	
  Write_Data(0xA0);	  
  Write_Data(0xB5);  
  Write_Data(0x55);    

  Write_Command(0xC1);	
  Write_Data(0xC8);	
  Write_Data(0x80);
  Write_Data(0xC0);

  Write_Command(0xC7);	
  Write_Data(0x0F);

  Write_Command(0xB1);	
  Write_Data(0x32);

  Write_Command(0xB2);	
  Write_Data(0xA4);
  Write_Data(0x00);
  Write_Data(0x00);

  Write_Command(0xBB);	
  Write_Data(0x17);

  Write_Command(0xB6);
  Write_Data(0x01);

  Write_Command(0xBE);
  Write_Data(0x05);

  Write_Command(0xA6);

  Clear_Screen();
	Refrash_Screen();
  Write_Command(0xaf);	 //display on
}

  
// Draw a horizontal line ignoring any screen rotation.
void OLED_Driver::Draw_FastHLine(int16_t x, int16_t y, int16_t length) {
  // Bounds check
		int16_t x0=x;
    do
    {
        Draw_Pixel(x, y);   // 逐点显示，描出垂直线
        x++;
    }
    while(x0+length>=x);
}
// Draw a horizontal line ignoring any screen rotation.
void OLED_Driver::Draw_FastHLine(int16_t x, int16_t y, int16_t length,uint16_t color) {
  // Bounds check
		int16_t x0=x;
    do
    {
        Draw_Pixel(x, y,color);   // 逐点显示，描出垂直线
        x++;
    }
    while(x0+length>=x);
}
  
  // Draw a vertical line ignoring any screen rotation.
void OLED_Driver::Draw_FastVLine(int16_t x, int16_t y, int16_t length)  {
  // Bounds check
		int16_t y0=y;
    do
    {
        Draw_Pixel(x, y);   // 逐点显示，描出垂直线
        y++;
    }
    while(y0+length>=y);
}
  // Draw a vertical line ignoring any screen rotation.
void OLED_Driver::Draw_FastVLine(int16_t x, int16_t y, int16_t length,uint16_t color)  {
  // Bounds check
		int16_t y0=y;
    do
    {
        Draw_Pixel(x, y,color);   // 逐点显示，描出垂直线
        y++;
    }
    while(y0+length>=y);
}
  
void OLED_Driver::Display_bmp(const uint8_t *ch) {
  
  int i,j;
  for(i=0;i<128;i++)  {
    for(j=0;j<128;j++)  {
			if((ch[i*256+2*j+1]<<8)|ch[i*256+2*j])
			{
				OLED_GRAM[2*j][i] = ch[i*256+2*j+1];
				OLED_GRAM[2*j+1][i] = ch[i*256+2*j];
			}
    }
  }
} 
void OLED_Driver::Display_bmp(int x,int y,int w,int h,const uint8_t *ch) {
  int Temp;
  int i,j;
  for(i=y;i<y+h;i++)  {
    for(j=x;j<x+w;j++)  {
			Temp = (i-y)*w*2+2*(j-x);
			if(i>0&&(j+1+x)<128&&Temp<w*h*2&&i<128&&2*j+x*2>=0)
			{
				if(ch[Temp+1])
					OLED_GRAM[2*j+x*2][i] = ch[Temp+1];
				if(ch[Temp])
					OLED_GRAM[2*j+1+x*2][i] = ch[Temp];
			}
    }
  }
} 

void OLED_Driver::Display_bbmp(int x,int y,int w,int h,const uint8_t *ch) {
  
	u8 i,j,k;
	for(k=0;k<(h/8+1);k++)
		for(i=0;i<8;i++)
		{
			if(k*8+i>=h)
				return;
			for(j=0;j<w;j++)
					if(ch[k*w+j]&(1<<i))
						Draw_Pixel(x+j,y+k*8+i);
		}
}

void OLED_Driver::Display_bbmp(int x,int y,int w,int h,const uint8_t *ch,uint16_t color) {
  
	u8 i,j,k;
	for(k=0;k<(h/8+1);k++)
		for(i=0;i<8;i++)
		{
			if(k*8+i>=h)
				return;
			for(j=0;j<w;j++)
					if(ch[k*w+j]&(1<<i))
						Draw_Pixel(x+j,y+k*8+i,color);
		}
}

void OLED_Driver::Display_vifbmp(const uint8_t *ch) {
  
  int i,j;
  for(i=0;i<128;i++)  {
    for(j=0;j<128;j++)  {
			if(ch[i*256+2*j+1]|ch[i*256+2*j])
			{
				OLED_GRAM[2*j][i] = ch[i*256+2*j+1];
				OLED_GRAM[2*j+1][i] = ch[i*256+2*j];
			}
    }
  }
}
void OLED_Driver::Display_SetDim(u8 Light)
{
	if(Light>64) Light = 64;
  Write_Command(0xC1);	
  Write_Data(3*Light);	
  Write_Data(2*Light);
  Write_Data(3*Light);
}


void OLED_Driver::Display_FadeinAll(const uint8_t *ch) {
  
	uint8_t red,green,blue;
	uint8_t red1,green1,blue1;
	uint8_t Stop_Count = 0;
  int i,j;
	while(Stop_Count++<30)
	{
		for(i=0;i<128;i++)  {
			for(j=0;j<128;j++)  {
				
				red1 = ch[i*256+2*j+1]>>3;
				green1= ((ch[i*256+2*j+1]&0x7)<<3)|ch[i*256+2*j]>>5;
				blue1 = ch[i*256+2*j]&0x1f;
				
				red = OLED_GRAM[2*j][i]>>3;
				green = ((OLED_GRAM[2*j][i]&0x7)<<3)|OLED_GRAM[2*j+1][i]>>5;
				blue = OLED_GRAM[2*j+1][i]&0x1f;
				
				if(red>red1)
				{
					red--;
				}
				else if(red<red1)
				{
					red++;
				}
				if(green>green1+1)
				{
					green-=2;
				}
				else if(green+1<green1)
				{
					green+=2;
				}
				if(blue>blue1)
				{
					blue--;
				}
				else if(blue<blue1)
				{
					blue++;
				}
				
				OLED_GRAM[2*j][i] = red<<3|(green>>3);
				OLED_GRAM[2*j+1][i] = green<<5|blue;
			}
		}
		Refrash_Screen();
		HAL_Delay(5);
	}
	Display_bmp(ch);
	Refrash_Screen();
}

void OLED_Driver::Display_FadeoutAll() {
  
	uint8_t red,green,blue;
	uint8_t Stop_Count = 0;
  int i,j;
	while(Stop_Count++<30)
	{
		for(i=0;i<128;i++)  {
			for(j=0;j<128;j++)  {
				
				
				red = OLED_GRAM[2*j][i]>>3;
				green = ((OLED_GRAM[2*j][i]&0x7)<<3)|OLED_GRAM[2*j+1][i]>>5;
				blue = OLED_GRAM[2*j+1][i]&0x1f;
				
				if(red>0)
				{
					red--;
				}
				if(green>1)
				{
					green-=2;
				}
				if(blue>0)
				{
					blue--;
				}
				
				OLED_GRAM[2*j][i] = red<<3|(green>>3);
				OLED_GRAM[2*j+1][i] = green<<5|blue;
			}
		}
		Refrash_Screen();
		HAL_Delay(5);
	}
	Clear_Screen();
	Refrash_Screen();
}

void OLED_Driver::Display_FraginAll(const uint8_t *ch) {
  
	uint8_t Stop_Count = 0;
  int i,j;
	while(Stop_Count++<30)
	{
		for(i=0;i<128;i++)  {
			for(j=0;j<128;j++)  {
//				printf("%x\r\n",);
				if((rand()&6))
				{
					OLED_GRAM[2*j][i] = ch[i*256+2*j+1];
					OLED_GRAM[2*j+1][i] = ch[i*256+2*j];
				}
				__ASM("NOP");
			}
		}
		Refrash_Screen();
		HAL_Delay(5);
	}
	Display_bmp(ch);
	Refrash_Screen();
}
//default:8
void OLED_Driver::OLED_F8x16(int x,int y,u8 Num,uint16_t coloru,uint16_t colord)
{
	u8 i,j,k;
	for(k=0;k<2;k++)
		for(i=0;i<8;i++)
			for(j=0;j<8;j++)
				if(OCRB_F8x16[Num*16+k*8+j]&(1<<i))
					Draw_Pixel(x+j,y+k*8+i,FlowColorRAM[k*8+i]);
		
}	

void OLED_Driver::OLED_SF8x16(int x,int y,char *ch,uint16_t coloru,uint16_t colord)
{
	u8 c=0,j=0;
	FlowColorFont(coloru,colord,16);
	while(ch[j]!='\0')
	{
		c=ch[j]-' ';
		if(x<128-8)
		OLED_F8x16(x,y,c,coloru,colord);
		x+=8;
		j++;
	}
}

void OLED_Driver::OLED_NF6x8(int x,int y,u8 Num,u8 Offset)
{
	u8 i,j;
	
	for(i=0;i<8;i++)
	{
		for(j=0;j<3;j++)
		{
			if(!(((Font_Default6x8[(Num+Offset)*6+j*2]>>i)&1)<<1))
				Draw_Pixel(x+j*2,y+i);
			if(!((Font_Default6x8[(Num+Offset)*6+j*2+1]>>i)&1))
				Draw_Pixel(x+j*2+1,y+i);
		}
	}
}	

void OLED_Driver::OLED_SNF6x8(int x,int y,char *ch)
{
	u8 c=0,j=0;
	for(j=0;j<8;j++)
		Draw_Pixel(x-1,y+j);
	j = 0;
	while(ch[j]!='\0')
	{
		c=ch[j];
		if(x<253)
		{
			if(c=='$')
				OLED_NF6x8(x,y,11,0);
			else if(c=='.')
				OLED_NF6x8(x,y,10,0);
			else if(c==':')
				OLED_NF6x8(x,y,13,0);
			else if(c=='-')
				OLED_NF6x8(x,y,12,0);
			else
			{
				c=ch[j]-'0';
				OLED_NF6x8(x,y,c,0);
			}
		}
		x+=6;
		j++;
	}
	for(j=0;j<8;j++)
		Draw_Pixel(x,y+j);
}

//default:8
void OLED_Driver::OLED_F8x16(int x,int y,u8 Num,uint16_t color)
{
	u8 i,j,k;
	for(k=0;k<2;k++)
		for(i=0;i<8;i++)
			for(j=0;j<8;j++)
				if(OCRB_F8x16[Num*16+k*8+j]&(1<<i))
					Draw_Pixel(x+j,y+k*8+i,color);
		
}	

void OLED_Driver::OLED_SF8x16(int x,int y,char *ch,uint16_t color)
{
	u8 c=0,j=0;
	while(ch[j]!='\0')
	{
		c=ch[j]-' ';
		if(x<128-8)
		OLED_F8x16(x,y,c,color);
		x+=8;
		j++;
	}
}
void OLED_Driver::OLED_F8x16(int x,int y,u8 Num)
{
	u8 i,j,k;
	for(k=0;k<2;k++)
		for(i=0;i<8;i++)
			for(j=0;j<8;j++)
				if(OCRB_F8x16[Num*16+k*8+j]&(1<<i))
					Draw_Pixel(x+j,y+k*8+i);
		
}	

void OLED_Driver::OLED_SF8x16(int x,int y,char *ch)
{
	u8 c=0,j=0;
	while(ch[j]!='\0')
	{
		c=ch[j]-' ';
		if(x<128-8)
		OLED_F8x16(x,y,c);
		x+=8;
		j++;
	}
}
void OLED_Driver::OLED_F10x16(int x,int y,u8 Num,uint16_t coloru,uint16_t colord)
{
	u8 i,j,k;
	for(k=0;k<2;k++)
		for(i=0;i<8;i++)
			for(j=0;j<10;j++)
				if(OCR_F10x16[Num*20+k*10+j]&(1<<i))
					Draw_Pixel(x+j,y+k*8+i,FlowColorRAM[k*8+i]);
}	

void OLED_Driver::OLED_SF10x16(int x,int y,char *ch,uint16_t coloru,uint16_t colord)
{
	u8 c=0,j=0;
	FlowColorFont(coloru,colord,16);
	while(ch[j]!='\0')
	{
		c=ch[j]-' ';
		if(x<128-10)
		OLED_F10x16(x,y,c,coloru,colord);
		x+=10;
		j++;
	}
}
void OLED_Driver::OLED_F10x16(int x,int y,u8 Num,uint16_t color)
{
	u8 i,j,k;
	for(k=0;k<2;k++)
		for(i=0;i<8;i++)
			for(j=0;j<10;j++)
				if(OCR_F10x16[Num*20+k*10+j]&(1<<i))
					Draw_Pixel(x+j,y+k*8+i,color);
}	

void OLED_Driver::OLED_SF10x16(int x,int y,char *ch,uint16_t color)
{
	u8 c=0,j=0;
	while(ch[j]!='\0')
	{
		c=ch[j]-' ';
		if(x<128-10)
		OLED_F10x16(x,y,c,color);
		x+=10;
		j++;
	}
}
void OLED_Driver::OLED_F10x16(int x,int y,u8 Num)
{
	u8 i,j,k;
	for(k=0;k<2;k++)
		for(i=0;i<8;i++)
			for(j=0;j<10;j++)
				if(OCR_F10x16[Num*20+k*10+j]&(1<<i))
					Draw_Pixel(x+j,y+k*8+i);
}	

void OLED_Driver::OLED_SF10x16(int x,int y,char *ch)
{
	u8 c=0,j=0;
	while(ch[j]!='\0')
	{
		c=ch[j]-' ';
		if(x<128-10)
		OLED_F10x16(x,y,c);
		x+=10;
		j++;
	}
}

void OLED_Driver::OLED_F12x24(int x,int y,u8 Num,uint16_t coloru,uint16_t colord)
{
	u16 i,j,k;
	for(k=0;k<3;k++)
		for(i=0;i<8;i++)
			for(j=0;j<12;j++)
				if(Agency_F12x24[Num*36+k*12+j]&(1<<i))
					Draw_Pixel(x+j,y+k*8+i,FlowColorRAM[23-(k*8+i)]);
}	

void OLED_Driver::OLED_SF12x24(int x,int y,char *ch,uint16_t coloru,uint16_t colord)
{
	u8 c=0,j=0;
	FlowColorFont(coloru,colord,24);
	while(ch[j]!='\0')
	{
		c=ch[j]-' ';
		if(x<128-12)
		OLED_F12x24(x,y,c,coloru,colord);
		x+=12; 
		j++;
	}
}

void OLED_Driver::OLED_F12x24(int x,int y,u8 Num,uint16_t color)
{
	u16 i,j,k;
	for(k=0;k<3;k++)
		for(i=0;i<8;i++)
			for(j=0;j<12;j++)
				if(Agency_F12x24[Num*36+k*12+j]&(1<<i))
					Draw_Pixel(x+j,y+k*8+i,color);
}	

void OLED_Driver::OLED_SF12x24(int x,int y,char *ch,uint16_t color)
{
	u8 c=0,j=0;
	while(ch[j]!='\0')
	{
		c=ch[j]-' ';
		if(x<128-12)
		OLED_F12x24(x,y,c,color);
		x+=12; 
		j++;
	}
}

void OLED_Driver::OLED_F12x24(int x,int y,u8 Num)
{
	u16 i,j,k;
	for(k=0;k<3;k++)
		for(i=0;i<8;i++)
			for(j=0;j<12;j++)
				if(Agency_F12x24[Num*36+k*12+j]&(1<<i))
					Draw_Pixel(x+j,y+k*8+i);
}	

void OLED_Driver::OLED_SF12x24(int x,int y,char *ch)
{
	u8 c=0,j=0;
	while(ch[j]!='\0')
	{
		c=ch[j]-' ';
		if(x<128-12)
		OLED_F12x24(x,y,c);
		x+=12; 
		j++;
	}
}
const unsigned char Clock_HF18x26[] = { 
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X04,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XF9,0X00,0X06,0XE2,0X00,0X00,0X00,0X00,0X00,0XB9,0X00,0X06,0XE2,0X00,0X00,0X00,
0X00,0X00,0XBB,0X00,0X06,0XD1,0X00,0X00,0X00,0X00,0X00,0XBB,0X00,0X09,0XD1,0X02,
0XEF,0XFF,0XF4,0X00,0X9B,0X00,0X09,0XB0,0X02,0XEF,0XFF,0XF6,0X00,0X9D,0X10,0X0B,
0XB0,0X02,0XE4,0X01,0XD6,0X00,0X6D,0X10,0X0B,0XB0,0X04,0XF4,0X01,0XD9,0X00,0X6E,
0X20,0X0B,0X90,0X04,0XE2,0X01,0XD9,0X00,0X6E,0X20,0X1D,0X90,0X06,0XE2,0X00,0XB9,
0X00,0X4E,0X20,0X1D,0X90,0X06,0XE2,0X00,0XBB,0X00,0X4F,0X40,0X1D,0X90,0X06,0XE2,
0X00,0XBB,0X00,0X4F,0X40,0X1D,0X90,0X06,0XE2,0X00,0XB9,0X00,0X4E,0X20,0X0B,0X90,
0X04,0XE2,0X01,0XD9,0X00,0X6E,0X20,0X0B,0XB0,0X04,0XF4,0X01,0XD9,0X00,0X6E,0X20,
0X0B,0XB0,0X04,0XF4,0X01,0XD6,0X00,0X6D,0X10,0X09,0XB0,0X02,0XE4,0X02,0XE6,0X00,
0X9D,0X10,0X09,0XD1,0X02,0XEF,0XFF,0XF4,0X00,0X9D,0X10,0X06,0XD1,0X00,0X00,0X00,
0X00,0X00,0X9B,0X00,0X06,0XE2,0X00,0X00,0X00,0X00,0X00,0XBB,0X00,0X06,0XE2,0X00,
0X00,0X00,0X00,0X00,0XB9,0X00,0X04,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF9,0X00,0X04,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF9,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,//0
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X1D,0XFF,0XFF,0XFF,0XFF,0XF6,0X00,
0X00,0X00,0X1D,0X60,0X00,0X00,0X01,0XD6,0X00,0X00,0X00,0X1D,0X60,0X00,0X00,0X01,
0XD6,0X00,0X00,0X00,0X1D,0X60,0X00,0X00,0X01,0XD6,0X00,0X00,0X00,0X1D,0XFF,0XFF,
0XD1,0X01,0XD6,0X00,0X00,0X00,0X1D,0XFF,0XFF,0XD1,0X01,0XD6,0X00,0X00,0X00,0X00,
0X00,0X06,0XD1,0X01,0XD6,0X00,0X00,0X00,0X00,0X00,0X06,0XD1,0X01,0XD6,0X00,0X00,
0X00,0X00,0X00,0X06,0XD1,0X01,0XD6,0X00,0X00,0X00,0X00,0X00,0X06,0XD1,0X01,0XD6,
0X00,0X00,0X00,0X00,0X00,0X06,0XD1,0X01,0XD6,0X00,0X00,0X00,0X00,0X00,0X06,0XD1,
0X01,0XD6,0X00,0X00,0X00,0X00,0X00,0X06,0XD1,0X01,0XD6,0X00,0X00,0X00,0X00,0X00,
0X06,0XD1,0X01,0XD6,0X00,0X00,0X00,0X00,0X00,0X06,0XD1,0X01,0XD6,0X00,0X00,0X00,
0X00,0X00,0X06,0XD1,0X01,0XD6,0X00,0X00,0X00,0X00,0X00,0X06,0XD1,0X01,0XD6,0X00,
0X00,0X00,0X00,0X00,0X06,0XD1,0X01,0XD6,0X00,0X00,0X00,0X00,0X00,0X06,0XD1,0X01,
0XD6,0X00,0X00,0X00,0X00,0X00,0X06,0XD1,0X01,0XD6,0X00,0X00,0X00,0X00,0X00,0X06,
0XD1,0X01,0XD6,0X00,0X00,0X00,0X00,0X00,0X06,0XFF,0XFF,0XF6,0X00,0X00,0X00,0X00,
0X00,0X06,0XFF,0XFF,0XF6,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,//1
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X1D,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0X40,0X1D,0X60,0X00,0X00,0X00,0X00,0X00,0X4F,0X40,0X1D,0X60,0X00,0X00,0X00,
0X00,0X00,0X4F,0X40,0X1D,0X60,0X00,0X00,0X00,0X00,0X00,0X4F,0X40,0X1D,0XFF,0XFF,
0XFF,0XFF,0XFB,0X00,0X4F,0X40,0X1D,0XFF,0XFF,0XFF,0XFF,0XFB,0X00,0X4F,0X40,0X00,
0X00,0X00,0X00,0X00,0XBB,0X00,0X4F,0X40,0X00,0X00,0X00,0X00,0X00,0XBB,0X00,0X4F,
0X40,0X00,0X00,0X00,0X9F,0XFF,0XFB,0X00,0X4F,0X40,0X1D,0XFF,0XFF,0XFF,0XFB,0X00,
0X00,0X4F,0X40,0X1D,0XFE,0X20,0X00,0X00,0X00,0X00,0X4F,0X40,0X1D,0X60,0X00,0X00,
0X00,0X00,0X00,0X4F,0X40,0X1D,0X60,0X00,0X00,0X09,0XFF,0XFF,0XFF,0X40,0X1D,0X60,
0X06,0XFF,0XFF,0XFF,0XE2,0X00,0X00,0X1D,0X60,0X06,0XE2,0X00,0X00,0X00,0X00,0X00,
0X1D,0X60,0X06,0XD1,0X00,0X00,0X00,0X00,0X00,0X1D,0X60,0X06,0XD1,0X00,0X00,0X00,
0X00,0X00,0X1D,0X60,0X06,0XFF,0XFF,0XFF,0XFF,0XFE,0X20,0X1D,0X60,0X00,0X00,0X00,
0X00,0X00,0X4E,0X20,0X1D,0X60,0X00,0X00,0X00,0X00,0X00,0X4E,0X20,0X1D,0X60,0X00,
0X00,0X00,0X00,0X00,0X4E,0X20,0X1D,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0X20,0X1D,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0X20,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,//2
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X1D,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0X40,0X1D,0X60,0X00,0X00,0X00,0X00,0X00,0X4F,0X40,0X1D,0X60,0X00,0X00,0X00,
0X00,0X00,0X4F,0X40,0X1D,0X60,0X00,0X00,0X00,0X00,0X00,0X4F,0X40,0X1D,0XFF,0XFF,
0XFF,0XFF,0XFB,0X00,0X4F,0X40,0X1D,0XFF,0XFF,0XFF,0XFF,0XFB,0X00,0X4F,0X40,0X00,
0X00,0X00,0X00,0X00,0XBB,0X00,0X4F,0X40,0X00,0X00,0X00,0X00,0X00,0XBB,0X00,0X4F,
0X40,0X1D,0XFF,0XFF,0XFF,0XFF,0XFB,0X00,0X4F,0X40,0X1D,0XFF,0XFF,0XFF,0XFF,0XFB,
0X00,0X4F,0X40,0X1D,0X60,0X00,0X00,0X00,0X00,0X00,0X4F,0X40,0X1D,0X60,0X00,0X00,
0X00,0X00,0X00,0X4F,0X40,0X1D,0X60,0X00,0X00,0X00,0X00,0X00,0X4F,0X40,0X1D,0XFF,
0XFF,0XFF,0XFF,0XFB,0X00,0X4F,0X40,0X00,0X00,0X00,0X00,0X00,0XBB,0X00,0X4F,0X40,
0X00,0X00,0X00,0X00,0X00,0XBB,0X00,0X4F,0X40,0X00,0X00,0X00,0X00,0X00,0XBB,0X00,
0X4F,0X40,0X1D,0XFF,0XFF,0XFF,0XFF,0XFB,0X00,0X4F,0X40,0X1D,0X60,0X00,0X00,0X00,
0X00,0X00,0X4F,0X40,0X1D,0X60,0X00,0X00,0X00,0X00,0X00,0X4F,0X40,0X1D,0X60,0X00,
0X00,0X00,0X00,0X00,0X4F,0X40,0X1D,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X40,0X1D,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X40,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,//3
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X1D,0XFF,0XFF,0XD1,0X00,0XBF,0XFF,
0XFF,0X40,0X1D,0X60,0X06,0XD1,0X00,0XBB,0X00,0X4F,0X40,0X1D,0X60,0X06,0XD1,0X00,
0XBB,0X00,0X4F,0X40,0X1D,0X60,0X06,0XD1,0X00,0XBB,0X00,0X4F,0X40,0X1D,0X60,0X06,
0XD1,0X00,0XBB,0X00,0X4F,0X40,0X1D,0X60,0X06,0XD1,0X00,0XBB,0X00,0X4F,0X40,0X1D,
0X60,0X06,0XD1,0X00,0XBB,0X00,0X4F,0X40,0X1D,0X60,0X06,0XD1,0X00,0XBB,0X00,0X4F,
0X40,0X1D,0X60,0X06,0XFF,0XFF,0XFB,0X00,0X4F,0X40,0X1D,0X60,0X06,0XFF,0XFF,0XFB,
0X00,0X4F,0X40,0X1D,0X60,0X00,0X00,0X00,0X00,0X00,0X4F,0X40,0X1D,0X60,0X00,0X00,
0X00,0X00,0X00,0X4F,0X40,0X1D,0X60,0X00,0X00,0X00,0X00,0X00,0X4F,0X40,0X1D,0XFF,
0XFF,0XFF,0XFF,0XFB,0X00,0X4F,0X40,0X00,0X00,0X00,0X00,0X00,0XBB,0X00,0X4F,0X40,
0X00,0X00,0X00,0X00,0X00,0XBB,0X00,0X4F,0X40,0X00,0X00,0X00,0X00,0X00,0XBB,0X00,
0X4F,0X40,0X00,0X00,0X00,0X00,0X00,0XBB,0X00,0X4F,0X40,0X00,0X00,0X00,0X00,0X00,
0XBB,0X00,0X4F,0X40,0X00,0X00,0X00,0X00,0X00,0XBB,0X00,0X4F,0X40,0X00,0X00,0X00,
0X00,0X00,0XBB,0X00,0X4F,0X40,0X00,0X00,0X00,0X00,0X00,0XBF,0XFF,0XFF,0X40,0X00,
0X00,0X00,0X00,0X00,0XBF,0XFF,0XFF,0X40,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,//4
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X1D,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0X40,0X1D,0X60,0X00,0X00,0X00,0X00,0X00,0X4F,0X40,0X1D,0X60,0X00,0X00,0X00,
0X00,0X00,0X4F,0X40,0X1D,0X60,0X00,0X00,0X00,0X00,0X00,0X4F,0X40,0X1D,0X60,0X06,
0XFF,0XFF,0XFF,0XFF,0XFF,0X40,0X1D,0X60,0X06,0XFF,0XFF,0XFF,0XFF,0XFF,0X40,0X1D,
0X60,0X06,0XD1,0X00,0X00,0X00,0X00,0X00,0X1D,0X60,0X06,0XD1,0X00,0X00,0X00,0X00,
0X00,0X1D,0X60,0X06,0XFF,0XFF,0XD1,0X00,0X00,0X00,0X1D,0X60,0X00,0X09,0XFF,0XFF,
0XFF,0XFF,0X40,0X1D,0X60,0X00,0X00,0X00,0X00,0X0B,0XFF,0X40,0X1D,0X60,0X00,0X00,
0X00,0X00,0X00,0X4F,0X40,0X1D,0XFF,0XFF,0XFD,0X10,0X00,0X00,0X4F,0X40,0X00,0X00,
0XBF,0XFF,0XFF,0XFB,0X00,0X4F,0X40,0X00,0X00,0X00,0X00,0X01,0XDB,0X00,0X4F,0X40,
0X00,0X00,0X00,0X00,0X00,0XBB,0X00,0X4F,0X40,0X00,0X00,0X00,0X00,0X00,0XBB,0X00,
0X4F,0X40,0X1D,0XFF,0XFF,0XFF,0XFF,0XFB,0X00,0X4F,0X40,0X1D,0X90,0X00,0X00,0X00,
0X00,0X00,0X4F,0X40,0X1D,0X90,0X00,0X00,0X00,0X00,0X00,0X4F,0X40,0X1D,0X90,0X00,
0X00,0X00,0X00,0X00,0X4F,0X40,0X1D,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X40,0X1D,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X40,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,//5
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X1D,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0X40,0X1D,0X60,0X00,0X00,0X00,0X00,0X00,0X4F,0X40,0X1D,0X60,0X00,0X00,0X00,
0X00,0X00,0X4F,0X40,0X1D,0X60,0X00,0X00,0X00,0X00,0X00,0X4F,0X40,0X1D,0X60,0X06,
0XFF,0XFF,0XFF,0XFF,0XFF,0X40,0X1D,0X60,0X06,0XFF,0XFF,0XFF,0XFF,0XFF,0X40,0X1D,
0X60,0X06,0XD1,0X00,0X00,0X00,0X00,0X00,0X1D,0X60,0X06,0XD1,0X00,0X00,0X00,0X00,
0X00,0X1D,0X60,0X06,0XFF,0XFF,0XFF,0XFF,0XFF,0X40,0X1D,0X60,0X06,0XFF,0XFF,0XFF,
0XFF,0XFF,0X40,0X1D,0X60,0X00,0X00,0X00,0X00,0X00,0X4F,0X40,0X1D,0X60,0X00,0X00,
0X00,0X00,0X00,0X4F,0X40,0X1D,0X60,0X00,0X00,0X00,0X00,0X00,0X4F,0X40,0X1D,0X60,
0X06,0XFF,0XFF,0XFB,0X00,0X4F,0X40,0X1D,0X60,0X06,0XD1,0X00,0XBB,0X00,0X4F,0X40,
0X1D,0X60,0X06,0XD1,0X00,0XBB,0X00,0X4F,0X40,0X1D,0X60,0X06,0XD1,0X00,0XBB,0X00,
0X4F,0X40,0X1D,0X60,0X06,0XFF,0XFF,0XFB,0X00,0X4F,0X40,0X1D,0X60,0X00,0X00,0X00,
0X00,0X00,0X4F,0X40,0X1D,0X60,0X00,0X00,0X00,0X00,0X00,0X4F,0X40,0X1D,0X60,0X00,
0X00,0X00,0X00,0X00,0X4F,0X40,0X1D,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X40,0X1D,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X40,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,//6
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X1D,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0X40,0X1D,0X60,0X00,0X00,0X00,0X00,0X00,0X6E,0X20,0X1D,0X60,0X00,0X00,0X00,
0X00,0X00,0X6E,0X20,0X1D,0X60,0X00,0X00,0X00,0X00,0X00,0X6D,0X10,0X1D,0XFF,0XFF,
0XFF,0XFF,0XF6,0X00,0X9D,0X10,0X1D,0XFF,0XFF,0XFF,0XFF,0XF6,0X00,0X9D,0X10,0X00,
0X00,0X00,0X00,0X02,0XE4,0X00,0X9B,0X00,0X00,0X00,0X00,0X00,0X04,0XF4,0X00,0XBB,
0X00,0X00,0X00,0X00,0X00,0X04,0XF4,0X00,0XBB,0X00,0X00,0X00,0X00,0X00,0X04,0XE2,
0X00,0XB9,0X00,0X00,0X00,0X00,0X00,0X06,0XE2,0X01,0XD9,0X00,0X00,0X00,0X00,0X00,
0X06,0XD1,0X01,0XD6,0X00,0X00,0X00,0X00,0X00,0X06,0XD1,0X02,0XE6,0X00,0X00,0X00,
0X00,0X00,0X09,0XD1,0X02,0XE6,0X00,0X00,0X00,0X00,0X00,0X09,0XB0,0X02,0XE4,0X00,
0X00,0X00,0X00,0X00,0X0B,0XB0,0X04,0XF4,0X00,0X00,0X00,0X00,0X00,0X0B,0XB0,0X04,
0XF4,0X00,0X00,0X00,0X00,0X00,0X0B,0X90,0X04,0XE2,0X00,0X00,0X00,0X00,0X00,0X1D,
0X90,0X06,0XE2,0X00,0X00,0X00,0X00,0X00,0X1D,0X60,0X06,0XD1,0X00,0X00,0X00,0X00,
0X00,0X2E,0X60,0X06,0XD1,0X00,0X00,0X00,0X00,0X00,0X2E,0XFF,0XFF,0XD1,0X00,0X00,
0X00,0X00,0X00,0X2E,0XFF,0XFF,0XB0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,//7
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X04,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XF9,0X00,0X06,0XE2,0X00,0X00,0X00,0X00,0X00,0XB9,0X00,0X06,0XE2,0X00,0X00,0X00,
0X00,0X00,0XBB,0X00,0X06,0XD1,0X00,0X00,0X00,0X00,0X00,0XBB,0X00,0X09,0XD1,0X02,
0XEF,0XFF,0XF4,0X00,0X9B,0X00,0X09,0XB0,0X02,0XEF,0XFF,0XF6,0X00,0X9D,0X10,0X0B,
0XB0,0X02,0XE4,0X01,0XD6,0X00,0X6D,0X10,0X0B,0XB0,0X04,0XF4,0X01,0XD9,0X00,0X6E,
0X20,0X0B,0X90,0X04,0XFF,0XFF,0XF9,0X00,0X6E,0X20,0X1D,0X90,0X06,0XFF,0XFF,0XF9,
0X00,0X4E,0X20,0X1D,0X90,0X00,0X00,0X00,0X00,0X00,0X4F,0X40,0X1D,0X90,0X00,0X00,
0X00,0X00,0X00,0X4F,0X40,0X1D,0X90,0X00,0X00,0X00,0X00,0X00,0X4E,0X20,0X0B,0X90,
0X04,0XFF,0XFF,0XF9,0X00,0X6E,0X20,0X0B,0XB0,0X04,0XF4,0X01,0XD9,0X00,0X6E,0X20,
0X0B,0XB0,0X04,0XF4,0X01,0XD6,0X00,0X6D,0X10,0X09,0XB0,0X02,0XE4,0X02,0XE6,0X00,
0X9D,0X10,0X09,0XD1,0X02,0XEF,0XFF,0XF4,0X00,0X9D,0X10,0X06,0XD1,0X00,0X00,0X00,
0X00,0X00,0X9B,0X00,0X06,0XE2,0X00,0X00,0X00,0X00,0X00,0XBB,0X00,0X06,0XE2,0X00,
0X00,0X00,0X00,0X00,0XB9,0X00,0X04,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF9,0X00,0X04,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF9,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,//8
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X1D,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0X40,0X1D,0X90,0X00,0X00,0X00,0X00,0X00,0X4F,0X40,0X1D,0X90,0X00,0X00,0X00,
0X00,0X00,0X4F,0X40,0X1D,0X90,0X00,0X00,0X00,0X00,0X00,0X4F,0X40,0X1D,0X90,0X06,
0XFF,0XFF,0XFB,0X00,0X4F,0X40,0X1D,0X90,0X06,0XFF,0XFF,0XFB,0X00,0X4F,0X40,0X1D,
0X90,0X06,0XE2,0X00,0XBB,0X00,0X4F,0X40,0X1D,0X90,0X06,0XE2,0X00,0XBB,0X00,0X4F,
0X40,0X1D,0X90,0X06,0XFF,0XFF,0XFB,0X00,0X4F,0X40,0X1D,0X90,0X06,0XFF,0XFF,0XFB,
0X00,0X4F,0X40,0X1D,0X90,0X00,0X00,0X00,0X00,0X00,0X4F,0X40,0X1D,0X90,0X00,0X00,
0X00,0X00,0X00,0X4F,0X40,0X1D,0X90,0X00,0X00,0X00,0X00,0X00,0X4F,0X40,0X1D,0XFF,
0XFF,0XFF,0XFF,0XFB,0X00,0X4F,0X40,0X00,0X00,0X00,0X00,0X00,0XBB,0X00,0X4F,0X40,
0X00,0X00,0X00,0X00,0X00,0XBB,0X00,0X4F,0X40,0X00,0X00,0X00,0X00,0X00,0XBB,0X00,
0X4F,0X40,0X1D,0XFF,0XFF,0XFF,0XFF,0XFB,0X00,0X4F,0X40,0X1D,0X60,0X00,0X00,0X00,
0X00,0X00,0X4F,0X40,0X1D,0X60,0X00,0X00,0X00,0X00,0X00,0X4F,0X40,0X1D,0X60,0X00,
0X00,0X00,0X00,0X00,0X4F,0X40,0X1D,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X40,0X1D,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X40,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,//9
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X1D,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X40,0X1D,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0X40,0X1D,0X60,0X00,0X00,0X00,0X00,0X00,0X4F,0X40,0X1D,0X60,0X00,0X00,
0X00,0X00,0X00,0X4F,0X40,0X1D,0X60,0X00,0X00,0X00,0X00,0X00,0X4F,0X40,0X1D,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X40,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,//-
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0XDF,0XFF,0XFD,0X10,0X00,0X00,0X00,0X00,0X01,0XDF,0XFF,0XFD,0X10,0X00,0X00,0X00,
0X00,0X01,0XD6,0X00,0X6D,0X10,0X00,0X00,0X00,0X00,0X01,0XD6,0X00,0X6D,0X10,0X00,
0X00,0X00,0X00,0X01,0XD6,0X00,0X6D,0X10,0X00,0X00,0X00,0X00,0X01,0XDF,0XFF,0XFD,
0X10,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,0XDF,0XFF,0XFD,0X10,
0X00,0X00,0X00,0X00,0X01,0XD6,0X00,0X6D,0X10,0X00,0X00,0X00,0X00,0X01,0XD6,0X00,
0X6D,0X10,0X00,0X00,0X00,0X00,0X01,0XD6,0X00,0X6D,0X10,0X00,0X00,0X00,0X00,0X01,
0XDF,0XFF,0XFD,0X10,0X00,0X00,0X00,0X00,0X01,0XDF,0XFF,0XFD,0X10,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,//:
};

const unsigned char Clock_HF12x24[] = { 
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X03,0X8A,0XA7,0X10,0X00,0X00,0X5F,0XB8,0X9D,0XD2,0X00,0X01,0XD8,
0X00,0X00,0XBB,0X00,0X05,0XF2,0X00,0X00,0X5F,0X30,0X09,0XB0,0X00,0X00,0X1F,0X60,
0X0A,0XA0,0X00,0X00,0X0F,0X60,0X0A,0XA0,0X00,0X00,0X0F,0X60,0X0A,0XA0,0X00,0X00,
0X0F,0X60,0X0A,0XA0,0X00,0X00,0X0F,0X60,0X0A,0XA0,0X00,0X00,0X0F,0X60,0X0A,0XA0,
0X00,0X00,0X0F,0X60,0X0A,0XA0,0X00,0X00,0X0F,0X60,0X0A,0XA0,0X00,0X00,0X0F,0X60,
0X07,0XF0,0X00,0X00,0X2F,0X50,0X04,0XF5,0X00,0X00,0X8F,0X20,0X00,0X9D,0X52,0X27,
0XF7,0X00,0X00,0X08,0XFF,0XFF,0X70,0X00,0X00,0X00,0X23,0X31,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,//0

0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X06,0XA4,0X00,0X00,0X00,0X04,0XDD,0XBF,0X10,0X00,0X00,0X8F,
0X91,0X3F,0X30,0X00,0X00,0X55,0X00,0X3F,0X30,0X00,0X00,0X00,0X00,0X3F,0X30,0X00,
0X00,0X00,0X00,0X3F,0X30,0X00,0X00,0X00,0X00,0X3F,0X30,0X00,0X00,0X00,0X00,0X3F,
0X30,0X00,0X00,0X00,0X00,0X3F,0X30,0X00,0X00,0X00,0X00,0X3F,0X30,0X00,0X00,0X00,
0X00,0X3F,0X30,0X00,0X00,0X00,0X00,0X3F,0X30,0X00,0X00,0X00,0X00,0X3F,0X30,0X00,
0X00,0X00,0X00,0X3F,0X30,0X00,0X00,0X00,0X00,0X3F,0X30,0X00,0X00,0X00,0X00,0X3F,
0X30,0X00,0X00,0X00,0X00,0X3F,0X30,0X00,0X00,0X00,0X00,0X03,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,//1

0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X03,0X9A,0XA7,0X00,0X00,0X00,0X5F,0XB8,0X9D,0XD2,0X00,0X03,0XF8,
0X00,0X02,0XD9,0X00,0X03,0X90,0X00,0X00,0X5F,0X20,0X00,0X00,0X00,0X00,0X3F,0X30,
0X00,0X00,0X00,0X00,0X5F,0X20,0X00,0X00,0X00,0X00,0XB9,0X00,0X00,0X00,0X00,0X09,
0XF3,0X00,0X00,0X00,0X00,0X7F,0X50,0X00,0X00,0X00,0X05,0XF7,0X00,0X00,0X00,0X00,
0X3F,0X90,0X00,0X00,0X00,0X02,0XDA,0X00,0X00,0X00,0X00,0X0B,0XD1,0X00,0X00,0X00,
0X00,0XAF,0X20,0X00,0X00,0X00,0X05,0XF5,0X00,0X00,0X00,0X00,0X08,0XF6,0X66,0X66,
0X66,0X30,0X02,0XBF,0XFF,0XFF,0XFF,0X60,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,//2

0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X03,0X8A,0XA7,0X10,0X00,0X00,0X5F,0XB8,0X9D,0XD2,0X00,0X03,0XF7,
0X00,0X01,0XBB,0X00,0X01,0X50,0X00,0X00,0X5F,0X30,0X00,0X00,0X00,0X00,0X3F,0X30,
0X00,0X00,0X00,0X00,0X4F,0X30,0X00,0X00,0X00,0X00,0XAD,0X00,0X00,0X00,0X56,0X7B,
0XF4,0X00,0X00,0X00,0XAF,0XFF,0XA1,0X00,0X00,0X00,0X00,0X25,0XDB,0X00,0X00,0X00,
0X00,0X00,0X3F,0X50,0X00,0X00,0X00,0X00,0X0B,0XA0,0X00,0X00,0X00,0X00,0X0A,0XA0,
0X02,0X40,0X00,0X00,0X0D,0X90,0X09,0XD2,0X00,0X00,0X5F,0X50,0X01,0XDD,0X51,0X26,
0XF9,0X00,0X00,0X29,0XFF,0XFF,0X80,0X00,0X00,0X00,0X23,0X32,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,//3

0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X05,0X10,0X00,0X00,0X00,0X00,0X3F,0X70,0X00,0X00,0X00,
0X00,0X9D,0X00,0X00,0X00,0X00,0X05,0XF5,0X00,0X00,0X00,0X00,0X0D,0XA0,0X00,0X00,
0X00,0X00,0X6F,0X30,0X00,0X00,0X00,0X02,0XF8,0X00,0X00,0X00,0X00,0X09,0XD1,0X00,
0X00,0X00,0X00,0X3F,0X60,0X03,0XF3,0X00,0X00,0XBB,0X00,0X03,0XF3,0X00,0X06,0XF4,
0X00,0X03,0XF3,0X00,0X0D,0X90,0X00,0X03,0XF3,0X00,0X2F,0X96,0X66,0X68,0XF8,0X50,
0X05,0XDF,0XFF,0XFF,0XFF,0XA0,0X00,0X00,0X00,0X03,0XF3,0X00,0X00,0X00,0X00,0X03,
0XF3,0X00,0X00,0X00,0X00,0X03,0XF3,0X00,0X00,0X00,0X00,0X00,0X30,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,//4

0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X05,0X66,0X66,0X65,0X00,0X00,0X9F,0XFF,0XFF,0XFA,0X00,0X02,0XF6,
0X00,0X00,0X00,0X00,0X03,0XF6,0X00,0X00,0X00,0X00,0X03,0XF6,0X00,0X00,0X00,0X00,
0X03,0XF6,0X00,0X00,0X00,0X00,0X03,0XF6,0X00,0X00,0X00,0X00,0X03,0XF8,0X9F,0XFA,
0X50,0X00,0X01,0XFF,0X96,0X69,0XF7,0X00,0X00,0X34,0X00,0X00,0X7F,0X30,0X00,0X00,
0X00,0X00,0X1F,0X70,0X00,0X00,0X00,0X00,0X0A,0XA0,0X00,0X00,0X00,0X00,0X0A,0XA0,
0X00,0X20,0X00,0X00,0X0D,0X80,0X04,0XF5,0X00,0X00,0X5F,0X40,0X00,0XAF,0X62,0X26,
0XF9,0X00,0X00,0X08,0XFF,0XFF,0X80,0X00,0X00,0X00,0X23,0X32,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,//5

0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X03,0X9A,0XA6,0X00,0X00,0X00,0X7F,0XB7,0X9F,0XA0,0X00,0X03,0XF7,
0X00,0X02,0XD9,0X00,0X08,0XF1,0X00,0X00,0X55,0X00,0X0A,0XA0,0X00,0X00,0X00,0X00,
0X0A,0XA0,0X00,0X00,0X00,0X00,0X0A,0XA0,0X03,0X20,0X00,0X00,0X0A,0XA5,0XDF,0XFD,
0X50,0X00,0X0A,0XDF,0X63,0X38,0XF6,0X00,0X0A,0XF5,0X00,0X00,0X8D,0X00,0X0A,0XD0,
0X00,0X00,0X3F,0X50,0X0A,0XA0,0X00,0X00,0X0F,0X60,0X0A,0XA0,0X00,0X00,0X0F,0X60,
0X09,0XB0,0X00,0X00,0X2F,0X50,0X05,0XF4,0X00,0X00,0X8F,0X20,0X00,0XAD,0X63,0X38,
0XF6,0X00,0X00,0X08,0XFF,0XFD,0X60,0X00,0X00,0X00,0X13,0X30,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,//6

0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X03,0X66,0X66,0X66,0X61,0X00,0X06,0XFF,0XFF,0XFF,0XFD,0X00,0X00,0X00,
0X00,0X00,0X4F,0X30,0X00,0X00,0X00,0X00,0X7F,0X10,0X00,0X00,0X00,0X00,0XB9,0X00,
0X00,0X00,0X00,0X03,0XF5,0X00,0X00,0X00,0X00,0X08,0XF1,0X00,0X00,0X00,0X00,0X0D,
0X90,0X00,0X00,0X00,0X00,0X4F,0X50,0X00,0X00,0X00,0X00,0X8D,0X00,0X00,0X00,0X00,
0X00,0XD8,0X00,0X00,0X00,0X00,0X05,0XF4,0X00,0X00,0X00,0X00,0X09,0XD0,0X00,0X00,
0X00,0X00,0X1F,0X80,0X00,0X00,0X00,0X00,0X5F,0X30,0X00,0X00,0X00,0X00,0X9B,0X00,
0X00,0X00,0X00,0X00,0XF7,0X00,0X00,0X00,0X00,0X00,0X10,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,//7

0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X03,0X9A,0XA8,0X20,0X00,0X00,0X5F,0XB7,0X7D,0XF5,0X00,0X02,0XF7,
0X00,0X00,0XAD,0X00,0X07,0XF1,0X00,0X00,0X2F,0X50,0X0A,0XA0,0X00,0X00,0X0F,0X60,
0X07,0XF1,0X00,0X00,0X2F,0X50,0X03,0XF7,0X00,0X00,0X8F,0X20,0X00,0X7F,0X96,0X6B,
0XF5,0X00,0X00,0X3F,0XFF,0XFF,0XB2,0X00,0X02,0XDA,0X30,0X05,0XDD,0X00,0X09,0XD0,
0X00,0X00,0X2F,0X70,0X0F,0X70,0X00,0X00,0X0A,0XA0,0X0F,0X60,0X00,0X00,0X06,0XF0,
0X0F,0X70,0X00,0X00,0X0A,0XA0,0X09,0XD0,0X00,0X00,0X2F,0X70,0X02,0XDA,0X40,0X05,
0XDD,0X00,0X00,0X2B,0XFF,0XFF,0X92,0X00,0X00,0X00,0X35,0X52,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,//8

0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X03,0X9A,0XA7,0X10,0X00,0X00,0X5F,0XB7,0X8D,0XD2,0X00,0X02,0XF8,
0X00,0X00,0XBB,0X00,0X07,0XF1,0X00,0X00,0X4F,0X40,0X0A,0XA0,0X00,0X00,0X0F,0X60,
0X0A,0XA0,0X00,0X00,0X0F,0X60,0X0A,0XA0,0X00,0X00,0X2F,0X60,0X05,0XF2,0X00,0X00,
0X6F,0X60,0X00,0XDA,0X20,0X03,0XDF,0X60,0X00,0X2D,0XFA,0XBF,0X8F,0X60,0X00,0X00,
0X56,0X63,0X0F,0X60,0X00,0X00,0X00,0X00,0X0F,0X60,0X00,0X00,0X00,0X00,0X0F,0X60,
0X00,0X10,0X00,0X00,0X2F,0X50,0X02,0XF6,0X00,0X00,0X8F,0X20,0X00,0X7F,0X83,0X38,
0XF7,0X00,0X00,0X06,0XDF,0XFF,0X60,0X00,0X00,0X00,0X03,0X30,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,//9

0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X01,0XDF,0XFF,0XFF,0XFB,0X00,0X01,0XDF,0XFF,0XFF,0XFB,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,//-

0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X6F,0X60,0X00,0X00,0X00,0X00,0X6F,0X60,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X6F,0X60,0X00,0X00,0X00,0X00,0X6F,0X60,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,//:
};


void OLED_Driver::Display_hbmp(int x,int y,int w,int h,const u8 *ch,uint16_t color)
{
	u16 i,j;
	u16 red,green,blue;
	u16 red1,green1,blue1;
	u16 Factor;
//	color = 0xFFFF;
	red = color>>11;
	green = (color&0x7E0)>>5;
	blue = color&0x1F;
	for(j=0;j<h;j++)
		for(i=0;i<(w+1)/2;i++)
		{
			Factor = (ch[j*((w+1)/2)+i]&0xF0)>>4;
			if(red>=15)
				red1 = red-0xF+Factor;
			else
				red1 = Factor;
			if(green>=30)
				green1=green-30+Factor*2;
			else
				green1 = Factor*2;
			if(blue>=15)
				blue1=blue-15+Factor;
			else
				blue1=Factor;
			
			if(Factor)
				Draw_Pixel(x+i*2+0,y+j,red1<<11|(green1<<5)|(blue1));
			
			Factor = (ch[j*((w+1)/2)+i]&0xF);
			if(red>=15)
				red1 = red-0xF+Factor;
			else
				red1 = Factor;
			if(green>=30)
				green1=green-30+Factor*2;
			else
				green1 = Factor*2;
			if(blue>=15)
				blue1=blue-15+Factor;
			else
				blue1=Factor;
			
			if(Factor)
				Draw_Pixel(x+i*2+1,y+j,red1<<11|(green1<<5)|(blue1));
		}
}	
void OLED_Driver::OLED_HFAny(int x,int y,int w,int h,u8 Num,const unsigned char *ch,uint16_t color)
{
	u16 i,j;
	u16 red,green,blue;
	u16 red1,green1,blue1;
	u16 Factor;
//	color = 0xFFFF;
	red = color>>11;
	green = (color&0x7E0)>>5;
	blue = color&0x1F;
	for(j=0;j<h;j++)
		for(i=0;i<(w+1)/2;i++)
		{
			Factor = (ch[Num*h*((w+1)/2)+j*((w+1)/2)+i]&0xF0)>>4;
			if(red>=15)
				red1 = red-0xF+Factor;
			else
				red1 = Factor;
			if(green>=30)
				green1=green-30+Factor*2;
			else
				green1 = Factor*2;
			if(blue>=15)
				blue1=blue-15+Factor;
			else
				blue1=Factor;
			
			if(Factor)
				Draw_Pixel(x+i*2+0,y+j,red1<<11|(green1<<5)|(blue1));
			
			Factor = (ch[Num*h*((w+1)/2)+j*((w+1)/2)+i]&0xF);
			if(red>=15)
				red1 = red-0xF+Factor;
			else
				red1 = Factor;
			if(green>=30)
				green1=green-30+Factor*2;
			else
				green1 = Factor*2;
			if(blue>=15)
				blue1=blue-15+Factor;
			else
				blue1=Factor;
			
			if(Factor)
				Draw_Pixel(x+i*2+1,y+j,red1<<11|(green1<<5)|(blue1));
		}
}	
void OLED_Driver::OLED_SHFAny(int x,int y,char *ch,int w,uint16_t color)
{
	u8 c=0,j=0;
	while(ch[j]!='\0')
	{
		c=ch[j]-'0';
		switch(w)
		{
			case 10:OLED_HFAny(x,y,10,13,c,GeForce_10x13,color);break;
			case 19:OLED_HFAny(x,y,19,23,c,GeForce_19x23,color);break;
			case 25:OLED_HFAny(x,y,25,37,c,GeForce_25x37,color);break;
		}
		x+=w; 
		j++;
	}
}

void OLED_Driver::OLED_HF14x14(int x,int y,u8 Num,uint16_t color)
{
	u16 i,j;
	u16 red,green,blue;
	u16 red1,green1,blue1;
	u16 Factor;
//	color = 0xFFFF;
	red = color>>11;
	green = (color&0x7E0)>>5;
	blue = color&0x1F;
	for(j=0;j<14;j++)
		for(i=0;i<7;i++)
		{
			Factor = (DefaultH14x14[Num*98+j*7+i]&0xF0)>>4;
			if(red>=15)
				red1 = red-0xF+Factor;
			else
				red1 = Factor;
			if(green>=30)
				green1=green-30+Factor*2;
			else
				green1 = Factor*2;
			if(blue>=15)
				blue1=blue-15+Factor;
			else
				blue1=Factor;
			
			if(Factor)
				Draw_Pixel(x+i*2+0,y+j,red1<<11|(green1<<5)|(blue1));
			
			Factor = (DefaultH14x14[Num*98+j*7+i]&0xF);
			if(red>=15)
				red1 = red-0xF+Factor;
			else
				red1 = Factor;
			if(green>=30)
				green1=green-30+Factor*2;
			else
				green1 = Factor*2;
			if(blue>=15)
				blue1=blue-15+Factor;
			else
				blue1=Factor;
			
			if(Factor)
				Draw_Pixel(x+i*2+1,y+j,red1<<11|(green1<<5)|(blue1));
		}
}	

void OLED_Driver::OLED_HF18x26(int x,int y,u8 Num,uint16_t color)
{
	u16 i,j;
	u16 red,green,blue;
	u16 red1,green1,blue1;
	u16 Factor;
//	color = 0xFFFF;
	red = color>>11;
	green = (color&0x7E0)>>5;
	blue = color&0x1F;
	for(j=0;j<26;j++)
		for(i=0;i<9;i++)
		{
			Factor = (Clock_HF18x26[Num*234+j*9+i]&0xF0)>>4;
			if(red>=15)
				red1 = red-0xF+Factor;
			else
				red1 = Factor;
			if(green>=30)
				green1=green-30+Factor*2;
			else
				green1 = Factor*2;
			if(blue>=15)
				blue1=blue-15+Factor;
			else
				blue1=Factor;
			
			if(Factor)
				Draw_Pixel(x+i*2+0,y+j,red1<<11|(green1<<5)|(blue1));
			
			Factor = (Clock_HF18x26[Num*234+j*9+i]&0xF);
			if(red>=15)
				red1 = red-0xF+Factor;
			else
				red1 = Factor;
			if(green>=30)
				green1=green-30+Factor*2;
			else
				green1 = Factor*2;
			if(blue>=15)
				blue1=blue-15+Factor;
			else
				blue1=Factor;
			
			if(Factor)
				Draw_Pixel(x+i*2+1,y+j,red1<<11|(green1<<5)|(blue1));
		}
}	
void OLED_Driver::OLED_SHF18x26(int x,int y,char *ch,uint16_t color)
{
	u8 c=0,j=0;
	while(ch[j]!='\0')
	{
		c=ch[j]-'0';
		if(x<128-18)
		{
			if(ch[j]=='-')
				OLED_HF18x26(x,y,10,color);
			else if(ch[j]==':')
				OLED_HF18x26(x,y,11,color);
			else
				OLED_HF18x26(x,y,c,color);
		}
		x+=18; 
		j++;
	}
}

void OLED_Driver::OLED_HF12x24(int x,int y,u8 Num,uint16_t color)
{
	u16 i,j;
	u16 red,green,blue;
	u16 red1,green1,blue1;
	u16 Factor;
//	color = 0xFFFF;
	red = color>>11;
	green = (color&0x7E0)>>5;
	blue = color&0x1F;
	for(j=0;j<24;j++)
		for(i=0;i<6;i++)
		{
			Factor = (Clock_HF12x24[Num*144+j*6+i]&0xF0)>>4;
			if(red>=15)
				red1 = red-0xF+Factor;
			else
				red1 = Factor;
			if(green>=30)
				green1=green-30+Factor*2;
			else
				green1 = Factor*2;
			if(blue>=15)
				blue1=blue-15+Factor;
			else
				blue1=Factor;
			
			if(Factor)
				Draw_Pixel(x+i*2+0,y+j,red1<<11|(green1<<5)|(blue1));
			
			Factor = (Clock_HF12x24[Num*144+j*6+i]&0xF);
			if(red>=15)
				red1 = red-0xF+Factor;
			else
				red1 = Factor;
			if(green>=30)
				green1=green-30+Factor*2;
			else
				green1 = Factor*2;
			if(blue>=15)
				blue1=blue-15+Factor;
			else
				blue1=Factor;
			
			if(Factor)
				Draw_Pixel(x+i*2+1,y+j,red1<<11|(green1<<5)|(blue1));
		}
}	

void OLED_Driver::OLED_SHF12x24(int x,int y,char *ch,uint16_t color)
{
	u8 c=0,j=0;
	while(ch[j]!='\0')
	{
		c=ch[j]-'0';
		if(x<128-12)
		{
			if(ch[j]=='-')
				OLED_HF12x24(x,y,10,color);
			else if(ch[j]==':')
				OLED_HF12x24(x,y,11,color);
			else
				OLED_HF12x24(x,y,c,color);
		}
		x+=12; 
		j++;
	}
}


void OLED_Driver::OLED_F22x40(int x,int y,u8 Num,uint16_t coloru,uint16_t colord)
{
	u8 i,j,k;
	for(k=0;k<5;k++)
		for(i=0;i<8;i++)
			for(j=0;j<22;j++)
					if(Agency_F22x40[Num*110+k*22+j]&(1<<i))
						Draw_Pixel(x+j,y+k*8+i,FlowColorRAM[k*8+i]);
}	

//void OLED_Driver::OLED_SF22x40(int x,int y,char *ch,uint16_t coloru,uint16_t colord)
//{
//	u8 c=0,j=0;
//	FlowColorFont(coloru,colord,40);
//	while(ch[j]!='\0')
//	{
//		if(ch[j]!='-')
//			c=ch[j]-'0';
//		else
//			c=10;
//		if(x<128-22)
//		OLED_F22x40(x,y,c,coloru,colord);
//		x+=22;
//		j++;
//	}
//}

void OLED_Driver::OLED_F22x40(int x,int y,u8 Num,uint16_t color)
{
	u8 i,j,k;
	for(k=0;k<5;k++)
		for(i=0;i<8;i++)
			for(j=0;j<22;j++)
					if(Agency_F22x40[Num*110+k*22+j]&(1<<i))
						Draw_Pixel(x+j,y+k*8+i,color);
}	

void OLED_Driver::OLED_SF22x40(int x,int y,char *ch,uint16_t color)
{
	u8 c=0,j=0;
	while(ch[j]!='\0')
	{
		if(ch[j]!='-')
			c=ch[j]-'0';
		else
			c=10;
		if(x<128-22)
		OLED_F22x40(x,y,c,color);
		x+=22;
		j++;
	}
}
void OLED_Driver::OLED_F22x40(int x,int y,u8 Num)
{
	u8 i,j,k;
	for(k=0;k<5;k++)
		for(i=0;i<8;i++)
			for(j=0;j<22;j++)
					if(Agency_F22x40[Num*110+k*22+j]&(1<<i))
						Draw_Pixel(x+j,y+k*8+i);
}	

void OLED_Driver::OLED_SF22x40(int x,int y,char *ch)
{
	u8 c=0,j=0;
	while(ch[j]!='\0')
	{
		if(ch[j]!='-')
			c=ch[j]-'0';
		else
			c=10;
		if(x<128-22)
		OLED_F22x40(x,y,c);
		x+=22;
		j++;
	}
}

#ifdef __cplusplus
}
#endif


