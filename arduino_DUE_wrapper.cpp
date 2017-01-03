/* Simulink Arduino Block Driver Library for Autocode Generation
 * 
 * This file is part of the Simulink Arduino Block Driver Library 
 * for Autocode Generation with Simulink
 *
 * This Library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This Library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this Library.  If not, see
 * <http://www.gnu.org/licenses/>.
 *
 */
/**
 * @file arduino_DUE_wrapper.cpp
 *
 * Wrapper code for Arduino Due Board
 *
 * @author Marcell Mocher <marcell.mocher@fh-joanneum.at>
 * @details Flight mechanics group FH JOANNEUM Graz
 */

#include <Arduino.h>
#include "arduino_DUE_wrapper.h"

#include "libraries/arduino/SD/MinimumSerial.cpp"
#include "libraries/arduino/SD/SdFat.cpp"
#include "libraries/arduino/SD/SdFatUtil.cpp"

#include "libraries/arduino/SD/FatFile.cpp"
#include "libraries/arduino/SD/FatFileLFN.cpp"
#include "libraries/arduino/SD/FatFilePrint.cpp"
#include "libraries/arduino/SD/FatFileSFN.cpp"
#include "libraries/arduino/SD/FatVolume.cpp"
#include "libraries/arduino/SD/FmtNumber.cpp"
#include "libraries/arduino/SD/fstream.cpp"
#include "libraries/arduino/SD/istream.cpp"
#include "libraries/arduino/SD/ostream.cpp"
#include "libraries/arduino/SD/StdioStream.cpp"

#include "libraries/arduino/SD/SdSpiCard.cpp"
#include "libraries/arduino/SD/SdSpiESP8266.cpp"
#include "libraries/arduino/SD/SdSpiParticle.cpp"
#include "libraries/arduino/SD/SdSpiSAM3X.cpp"
#include "libraries/arduino/SD/SdSpiSTM32F1.cpp"
#include "libraries/arduino/SD/SdSpiTeensy3.cpp"


extern "C" {
    
#include "libraries/arduino/SPI_DUE/SPI.cpp"
#include "libraries/arduino/Wire_DUE/Wire.cpp"
#include "libraries/arduino/Servo/sam/Servo.cpp"
#include "libraries/arduino/PWMIN/PWMIN.cpp"
    
    Servo _servo[8];
    SdFat sd;
    SdFile file;
}

char file_name[50];
bool i2c_init = false;

extern "C" void _i2c_init(void){
    if(i2c_init == false){
    delay(500);
    Wire.begin();
    delay(500);
    i2c_init = true;
    }
    return;
}

extern "C" void _serial_init(uint8_T num, uint32_T baud){
    switch(num)
    {
        case 0:
            Serial.begin(baud);
            break;
        case 1:
            Serial1.begin(baud);
            break;
        case 2:
            Serial2.begin(baud);
            break;
        case 3:
            Serial3.begin(baud);
            break;
    }
    return;
}


extern "C" void _i2c_read_register(uint8_T addr, uint8_T reg,uint8_T len,uint8_T * val) {  
    Wire.beginTransmission(addr);
    Wire.write(reg);
    Wire.endTransmission();
    Wire.requestFrom(addr,len);
    if(Wire.available() >= len){
        for(int i = 0;i < len;i++){
            val[i] = Wire.read();
        }
    }
    return;
}

extern "C" void _i2c_write_register(uint8_T addr, uint8_T reg,uint8_T val) {
    Wire.beginTransmission(addr);
    Wire.write(reg);
    Wire.write(val);
    Wire.endTransmission();
    return;
}

extern "C" void _serial_print(uint8_T num,double val){
    switch(num)
    {
        case 0:
            Serial.print(val,4);
            break;
        case 1:
            Serial1.print(val);
            break;
        case 2:
            Serial2.print(val);
            break;
        case 3:
            Serial3.print(val);
            break;
    }
    return;
}


extern "C" void _serial_write(uint8_T num,uint8_T* val,uint8_T length){
    switch(num)
    {
        case 0:
            Serial.write(val,length);
            break;
        case 1:
            Serial1.write(val,length);
            break;
        case 2:
            Serial2.write(val,length);
            break;
        case 3:
            Serial3.write(val,length);
            break;
    }
    return;
}

extern "C" uint8_T _serial_read(uint8_T num){
    uint8_T val = 0;
    switch(num)
    {
        case 0:
            val = Serial.read();
            break;
        case 1:
            val = Serial1.read();
            break;
        case 2:
            val = Serial2.read();
            break;
        case 3:
            val = Serial3.read();
            break;
    }
    return val;
}

extern "C" uint8_T _serial_available(uint8_T num){
    uint8_T val = 0;
    switch(num)
    {
        case 0:
            val = Serial.available();
            break;
        case 1:
            val = Serial1.available();
            break;
        case 2:
            val = Serial2.available();
            break;
        case 3:
            val = Serial3.available();
            break;
    }
    return val;
}

extern "C" void _servo_attach(uint8_T num)
{   // Servo 1 = Pin 29
    // Serov 8 = Pin 22
    _servo[num-1].attach(30-num);
    return;
}

extern "C" void _servo_write_us(uint8_T num,uint32_T val)
{
    _servo[num-1].writeMicroseconds(val);
    return;
}

extern "C" void _pwmin_attach(uint8_T pinLength)
{   
    uint8_t pins[] = {37,36,35,34,33,32,31,30};
    rcreceive_init(pins, pinLength);
    return;
}
extern "C" void _pwmin_step(uint8_T pinLength,uint16_T *pwm, bool *status)
{
    uint8_t pins[] = {37,36,35,34,33,32,31,30};
    rcreceive_step(pins, pinLength,&pwm[0],&status[0]);
    return;
}

extern "C" uint32_T _get_time(void)
{
    return micros();
}

extern "C" void _delay_us(uint32_T time)
{
    delayMicroseconds(time);
    return;
}

extern "C" boolean _sd_init()
{
    bool sdFunctional;
    const uint8_t chipSelect = 4;
    
    pinMode(53, OUTPUT);
    if (!sd.begin(chipSelect, SPI_FULL_SPEED)) {
        sdFunctional = false;
    }else{
        sd.mkdir("logs");
        char file_dir[50];
        int file_number = 1;
        sprintf(file_dir,"logs/log%d",file_number);
        bool terminator = false;
        while(sd.exists(file_dir) && !terminator){
            file_number++;
            sprintf(file_dir,"logs/log%d",file_number);
            if(file_number>=999) terminator = true;
        }
        sd.mkdir(file_dir);
        sprintf(file_name,"%s/log.txt",file_dir);
        file.open(file_name, O_CREAT | O_APPEND  | O_WRITE);
        sdFunctional = true;
    }
    return sdFunctional;
}

extern "C" void _sd_print(double val, uint8_T decimal)
{
    file.print(val,decimal);
}

extern "C" void _sd_nl()
{
    file.println();
}

extern "C" void _sd_print_nl(double val, uint8_T decimal)
{
    file.println(val,decimal);
}

extern "C" void _sd_print_c(double val, uint8_T decimal)
{
    file.print(val,decimal);
    file.print(",");
}

extern "C" void _sd_print_tab(double val, uint8_T decimal)
{
    file.print(val,decimal);
    file.print("\t");
}

extern "C" boolean _sd_open(void)
{
    return file.open(file_name, O_CREAT | O_APPEND  | O_WRITE);
}

extern "C" void _sd_close(void)
{
    file.close();
    return;
}

extern "C" void _led_init(void)
{
    pinMode(47, OUTPUT); // green
    pinMode(48, OUTPUT); // yellow
    pinMode(49, OUTPUT); // red
    pinMode(50, OUTPUT); // blue
    return;
}

extern "C" void _led_on_off(uint8_T led, boolean status)
{
    switch (led)
    {
        case 0:
            if (status == true)
            digitalWrite(47, HIGH);
            else digitalWrite(47, LOW);
            break;
        case 1:
            if (status == true)
            digitalWrite(48, HIGH);
            else digitalWrite(48, LOW); 
            break;
        case 2:
            if (status == true)
            digitalWrite(49, HIGH);
            else digitalWrite(49, LOW);  
            break;
        case 3:
            if (status == true)
            digitalWrite(50, HIGH);
            else digitalWrite(50, LOW);
            break;      
    }
    
    return;
}


extern "C"  void _spi_52_init(void){
    SPI.begin(52);
    SPI.setClockDivider(10, 21); //  4Mhz SPI bus transfer speed
    SPI.setBitOrder(MSBFIRST);
    SPI.setDataMode(SPI_MODE1);
}

extern "C"  uint16_T _spi_52_read(void){
    unsigned int result1 = 0;
    unsigned int result2 = 0;
    result1 = SPI.transfer(52, 0b00000000, SPI_CONTINUE);
    result2 = SPI.transfer(52, 0b00000000);
    result1 &= 0b00111111; 
    result1 = result1 << 8;
    return result1 | result2;
}


extern "C"  void oneshot125_init(uint8_T pin){
  pinMode(30-pin, OUTPUT);
}

extern "C"  void oneshot125(uint8_T pin,uint8_T width){
  digitalWrite(30-pin, HIGH);
  delayMicroseconds(width);
  digitalWrite(30-pin, LOW);
}