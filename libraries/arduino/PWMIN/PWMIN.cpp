#include "PWMIN.h"

typedef struct {uint8_t pinNumber; uint8_t flag; uint32_t startTime; uint16_t durationTime;} rcChannel;    
volatile rcChannel rcc[8] = {{0,1,0,0}, {0,2,0,0}, {0,4,0,0}, {0,8,0,0}, {0,16,0,0}, {0,32,0,0}, {0,64,0,0}, {0,128,0,0}};
volatile uint8_t updateFlagGlobal = 0; // global update flags

void rcreceive_init(uint8_t pins[], uint8_t pinLength)
{  
    // attach interrupts to pins
    for (uint8_t idx=0; idx<pinLength; idx++){    
    rcc[idx].pinNumber = pins[idx];
        switch(idx){
          case 0:
            attachInterrupt(digitalPinToInterrupt(pins[idx]), calc0,CHANGE); 
            break;
          case 1:
            attachInterrupt(digitalPinToInterrupt(pins[idx]), calc1,CHANGE);
            break;
          case 2:
            attachInterrupt(digitalPinToInterrupt(pins[idx]), calc2,CHANGE);
            break;
          case 3:
            attachInterrupt(digitalPinToInterrupt(pins[idx]), calc3,CHANGE);
            break;
          case 4:
            attachInterrupt(digitalPinToInterrupt(pins[idx]), calc4,CHANGE);
            break;
          case 5:
            attachInterrupt(digitalPinToInterrupt(pins[idx]), calc5,CHANGE);
            break;
		  case 6:
            attachInterrupt(digitalPinToInterrupt(pins[idx]), calc6,CHANGE);
            break;
		  case 7:
            attachInterrupt(digitalPinToInterrupt(pins[idx]), calc7,CHANGE);
            break;     			
        }
    } // end attach interrupt to pins
} // end rcreceive_init 

void rcreceive_step(uint8_t pins[],uint8_t pinLength,uint16_t * data,bool * status)
{
    static uint8_t updateFlag; // local copy of update flag
    memset(status,0,4);
    // disable interrupts to prevent modification of data
    noInterrupts(); 
    // check shared update flag to see if any channels have a new signal
    if(updateFlagGlobal) {       
        updateFlag = updateFlagGlobal; 
        // update data if data was received
        for (int idx = 0; idx<=pinLength; idx++){
            if (updateFlag & rcc[idx].flag) {
                // data received, update data and set status to 1
                data[idx] = rcc[idx].durationTime;
                status[idx] = 1;
            }
        }     
    }
    // reset the global update flag
    updateFlagGlobal = 0;
    // enable interrupts to allow modification of data
    interrupts();
}

void calc0()
{
  int idx = 0;
  if(digitalRead(rcc[idx].pinNumber) == HIGH)
  { 
    rcc[idx].startTime = micros();
  }
  else
  {
    rcc[idx].durationTime = (uint16_t)(micros() - rcc[idx].startTime);
    updateFlagGlobal |= rcc[idx].flag;
  }
}

void calc1()
{
  int idx = 1;
  if(digitalRead(rcc[idx].pinNumber) == HIGH)
  { 
    rcc[idx].startTime = micros();
  }
  else
  {
    rcc[idx].durationTime = (uint16_t)(micros() - rcc[idx].startTime);
    updateFlagGlobal |= rcc[idx].flag;
  }
}

void calc2()
{
  int idx = 2;
  if(digitalRead(rcc[idx].pinNumber) == HIGH)
  { 
    rcc[idx].startTime = micros();
  }
  else
  {
    rcc[idx].durationTime = (uint16_t)(micros() - rcc[idx].startTime);
    updateFlagGlobal |= rcc[idx].flag;
  }
}

void calc3()
{
  int idx = 3;
  if(digitalRead(rcc[idx].pinNumber) == HIGH)
  { 
    rcc[idx].startTime = micros();
  }
  else
  {
    rcc[idx].durationTime = (uint16_t)(micros() - rcc[idx].startTime);
    updateFlagGlobal |= rcc[idx].flag;
  }
}

void calc4()
{
  int idx = 4;
  if(digitalRead(rcc[idx].pinNumber) == HIGH)
  { 
    rcc[idx].startTime = micros();
  }
  else
  {
    rcc[idx].durationTime = (uint16_t)(micros() - rcc[idx].startTime);
    updateFlagGlobal |= rcc[idx].flag;
  }
}

void calc5()
{
  int idx = 5;
  if(digitalRead(rcc[idx].pinNumber) == HIGH)
  { 
    rcc[idx].startTime = micros();
  }
  else
  {
    rcc[idx].durationTime = (uint16_t)(micros() - rcc[idx].startTime);
    updateFlagGlobal |= rcc[idx].flag;
  }
}
void calc6()
{
  int idx = 6;
  if(digitalRead(rcc[idx].pinNumber) == HIGH)
  { 
    rcc[idx].startTime = micros();
  }
  else
  {
    rcc[idx].durationTime = (uint16_t)(micros() - rcc[idx].startTime);
    updateFlagGlobal |= rcc[idx].flag;
  }
}
void calc7()
{
  int idx = 7;
  if(digitalRead(rcc[idx].pinNumber) == HIGH)
  { 
    rcc[idx].startTime = micros();
  }
  else
  {
    rcc[idx].durationTime = (uint16_t)(micros() - rcc[idx].startTime);
    updateFlagGlobal |= rcc[idx].flag;
  }
}