
#ifndef PWMIN_H
#define PWMIN_H
#include <Arduino.h>


void rcreceive_init(uint8_t pins[],uint8_t pinLength);
void rcreceive_step(uint8_t pins[],uint8_t pinLength,uint16_t* data,bool* status);
void calc0();
void calc1();
void calc2();
void calc3();
void calc4();
void calc5();
void calc6();
void calc7();
#endif
