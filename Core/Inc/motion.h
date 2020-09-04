#ifndef __MOTIOH_H__ 	                                                                                                                                                                                                                                                                                                                                           
#define __MOTIOH_H__ 

#include "sys.h"

#define PITITEM 80
typedef struct
{
	float target;
	float current;
	u8 match;
	u8 channel;
} PIT;

//extern u8 NMatchcount;
extern PIT pit[PITITEM];

void DampAutoPos(void);
void DampCustormPos(u16 index,float step);

void SetCurrent(u8 index,float value);
void SetTarget(u8 index,float value);
void SetChannel(u8 index,u8 able);
void DampMPos(float step);

#define POSNRCT 0
#define POSNRCD 1
#define POSNTOP 4
#define POSNBAR 3
#define POSNBAT 6
#define POSNBRO 2

#define CRTVANE 8
#define CRTVADS 5
#define DAMPTYP 9

#define PNTHOUR 10
#define PNTMIN 11
#define PNTSEC 12

#define RDRadius 13
#define RDRadiusC 14
#define RDRadiusB 15
#define RDHourRadius 16
#define RDMinRadius 17
#define RDSecRadius 18
#define RDRuleDelaut 19

#define RDHourColor 20
#define RDMinColor 21
#define RDSecColor 22

#define RDRadiusA 23
#define PNTTIME 24
#define PNTTIMEY 25

#define PBLOGO	26
#define PBNUM 	27
#define PBLINEL 	28
#define PBLINER 	29
#define PBPT22 	30
#define PBPT33 	31
#define PBPTbk 	32

#define PWPTUP 	33
#define PWPTDN 	34
#define PWPTRT 	35
#define PWPTLF 	36
#define PWPTRTICON 	37
#define PWPTLINE 	38

#define MENUL1I1X 39
#define MENUL1I2X 40
#define MENUL1I3X 41
#define MENUL1I4X 42
#define MENUL1I5X 43
#define MENUL1I6X 61
#define MENUL1I7X 62

#define MENUL1I1Y 44
#define MENUL1I2Y 45
#define MENUL1I3Y 46
#define MENUL1I4Y 47
#define MENUL1I5Y 48
#define MENUL1I6Y 63
#define MENUL1I7Y 64

#define MENUL3SX 49
#define MENUL2IX 50
#define MENUL2S1X 51
#define MENUL2S2X 52
//#define MENUL2I5X 53

//#define MENUL2I1Y 54
//#define MENUL2I2Y 55
//#define MENUL2I3Y 56
//#define MENUL2I4Y 57
//#define MENUL2I5Y 58

#define MENUL1Y 59
#define MENUL2X 60
#define DIM 65
#define UNUSE 66

#define SSLF  53
#define SSRT  54
#define SSMLF 55
#define SSMRT 56
#define SSLLF 57
#define SSLRT 58

#define SSUP  61
#define SSDN  62
#define SSRD  63

#define STSOK  64
#endif
