#include "stm8s.h"
#include <stdio.h>
#define CLK_PIN GPIOD,GPIO_PIN_2
#define CE_PIN GPIOD,GPIO_PIN_3
#define DT_PIN GPIOD,GPIO_PIN_4
void writeAllow(){
    GPIO_WriteLow(CLK_PIN);
    GPIO_WriteHigh(CE_PIN);
    GPIO_Init(DT_PIN,GPIO_MODE_OUT_PP_LOW_SLOW);
    for(short i=0;i<8;i++){
        GPIO_WriteLow(CLK_PIN);
        if((0x8E>>i)&1) GPIO_WriteHigh(DT_PIN);
        else GPIO_WriteLow(DT_PIN);
        GPIO_WriteHigh(CLK_PIN);
    }
    for(short i=0;i<8;i++){
        GPIO_WriteLow(DT_PIN);
        GPIO_WriteLow(CLK_PIN);
        GPIO_WriteHigh(CLK_PIN);
    }
    GPIO_WriteLow(CE_PIN);
}
void setTime(short time,short command){
    writeAllow();
    GPIO_WriteLow(CLK_PIN);
    GPIO_WriteHigh(CE_PIN);
    GPIO_Init(DT_PIN,GPIO_MODE_OUT_PP_LOW_SLOW);
    for(short i=0;i<8;i++){
        GPIO_WriteLow(CLK_PIN);
        if((command>>i)&1) GPIO_WriteHigh(DT_PIN);
        else GPIO_WriteLow(DT_PIN);
        GPIO_WriteHigh(CLK_PIN);
    }
    short timeReg=0;
    timeReg=((time/10)<<4)|(time%10);
    for(short i=0;i<8;i++){
        GPIO_WriteLow(CLK_PIN);
        if((timeReg>>i)&1) GPIO_WriteHigh(DT_PIN);
        else GPIO_WriteLow(DT_PIN);
        GPIO_WriteHigh(CLK_PIN);
    }
    GPIO_WriteLow(CE_PIN);
}
short getTime(short command){
    GPIO_WriteLow(CLK_PIN);
    GPIO_WriteHigh(CE_PIN);
    GPIO_Init(DT_PIN,GPIO_MODE_OUT_PP_LOW_SLOW);
    for(short i=0;i<8;i++){
        GPIO_WriteLow(CLK_PIN);
        if((command>>i)&1) GPIO_WriteHigh(DT_PIN);
        else GPIO_WriteLow(DT_PIN);
        GPIO_WriteHigh(CLK_PIN);
    }
    GPIO_Init(DT_PIN,GPIO_MODE_IN_FL_NO_IT);
    short res=0;
    for(short i=0;i<8;i++){
        GPIO_WriteLow(CLK_PIN);
        GPIO_WriteHigh(CLK_PIN);
        if(GPIO_ReadInputPin(DT_PIN)) res=res|(1<<i);
    }
    GPIO_WriteLow(CE_PIN);
    if(command==0x85) return ((res&0x30)>>4)*10+(res&0x0F);
    else return (res>>4)*10+(res&0x0F);
}
short getSec(){
    return getTime(0x81);
}
short getMin(){
    return getTime(0x83);
}
short getHour(){
    return getTime(0x85);
}
void setMin(short min){
    setTime(min,0x82);
}
void setHour(short hour){
    setTime(hour,0x84);
}
void main() {
    CLK_SYSCLKConfig(CLK_PRESCALER_HSIDIV1);
    GPIO_Init(CLK_PIN,GPIO_MODE_OUT_PP_LOW_SLOW);
    GPIO_Init(CE_PIN,GPIO_MODE_OUT_PP_LOW_SLOW);
  //  setHour(2);
 //   setMin(20);
  //  setTime(0,0x80);
 //   while(1){
 //     printf("%d:%d:%d\n",getHour(),getMin(),getSec());
 //       for(long i;i<60000;i++);
 //   }
    
//  while (1) {
//  } 
}
