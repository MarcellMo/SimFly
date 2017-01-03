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
 * @file arduino_nano_wrapper.h
 *
 * Wrapper code for Arduino Due Board
 *
 * @author Marcell Mocher <marcell.mocher@fh-joanneum.at>
 * @details Flight mechanics group FH JOANNEUM Graz
 */

#ifndef _ARDUINO_DUE_WRAPPER_H_
#define _ARDUINO_DUE_WRAPPER_H_
#include "rtwtypes.h"
    
#ifdef __cplusplus
extern "C" {
#endif
    
#include "libraries/arduino/SPI_AVR/SPI.h"
#include "libraries/arduino/Wire_AVR/Wire.h"
#include "libraries/arduino/Servo/Servo.h"
#include "libraries/arduino/PWMIN/PWMIN.h"
#include "libraries/arduino/Wire_AVR/twi.h"
    /**
     * Initialize Wire library
     */
    void _i2c_init(void);
    
    /**
     * Initialize LED pins
     */
    void _led_init(void);
    
    /**
     * Initialize UART Serial connection
     * @param led	number of led 0 = g 1 = y 2 = r 3 = b
     * @param status true if on
     */
    void _led_on_off(uint8_T led, boolean status);
    
    /**
     * Initialize UART Serial connection
     * @param num	number of serial port
     * @param baud	Baudrate to be set
     */
    void _serial_init(uint8_T num,uint32_T baud);
    
    /**
     * Read specified number of values from I2C bus
     * @param addr slave address
     * @param reg register address
     * @param len length of the message
     * @param val pointer to the array the message is written in
     * @return	see param val
     */
    void _i2c_read_register(uint8_T addr, uint8_T reg,uint8_T len,uint8_T * val);
    
    /**
     * Writes one byte to a register to slave device via I2C
     * @param addr slave address
     * @param reg register address
     * @param val value to write
     */
    void _i2c_write_register(uint8_T addr, uint8_T reg,uint8_T val);
    
    /**
     * Calls function Serial.print()  takes a numer and writes ASCII to serial
     * @param num number of serial port
     * @param val value which should be written
     */
    void _serial_print(uint8_T num,double val);
    
    /**
     * Calls function SerialX.write()  writes a byte to serial
     * @param num number of serial port
     * @param val value which should be written
     */
    void _serial_write(uint8_T num,uint8_T val);
    
    /**
     * Calls function SerialX.read()  reads a byte from serial
     * @param num number of serial port
     * @return val value from serial port
     */
    uint8_T _serial_read(uint8_T num);
    
    /**
     * Calls function SerialX.read()  reads a byte from serial
     * @param num number of serial port
     * @return val bytes available at serial port
     */
    uint8_T _serial_available(uint8_T num);
    
    /**
     * Initialization for esc write function. Attaches esc to specific port
     * @param num number of esc which should be initialized from 0 - 7
     */
    void _servo_attach(uint8_T num);
    
    /**
     * sends pwm signal to esc
     * @param num number of esc
     * @param val pulselength in us written to esc
     */
    void _servo_write_us(uint8_T num,uint32_T val);
    
    /**
     * Attach pwm inputs
     * @param  pinLenght number of servos pwm in signals that are attached 1-8
     */
    void _pwmin_attach(uint8_T pinLength);
    
    /**
     * Read out pwm inputs
     * @param pinLenght number of servos pwm in signals
     * @param pwm pointer to array where pwm signals are written in
     * @param status pointer to array where status signals are written in
     * @return	see pwm and status
     */
    void _pwmin_step(uint8_T pinLength,uint16_t *pwm, bool *status);
    
    /**
     * calls micros() to get the time
     * @return  time in us since startup
     */
    uint32_T _get_time(void);
    
    /**
     * calls delayMicroseconds()
     * @param  time in us for delay fun
     */
    void _delay_us(uint32_T time);
    
    /**
     * initialize sd card
     * @return true if sd card is ready
     */
    boolean _sd_init(void);
    
    /**
     * writes val to sd card
     * @param val float (single) to sd card
     * @param decimal decimals after comma to print
     */
    void _sd_print(double val, uint8_T decimal);
    
    /**
     * writes val to sd card with comma
     * @param val byte to sd card
     */
    void  _sd_print_c(double val, uint8_T decimal);
    
    /**
     * writes new line
     * @param val byte to sd card
     */
    void _sd_nl(void);
    
    /**
     * writes val to sd card with new line
     * @param val byte to sd card
     */
    void _sd_print_nl(double val, uint8_T decimal);
    
    /**
     * writes val to sd card with tab
     * @param val byte to sd card
     */
    void _sd_print_tab(double val, uint8_T decimal);
    
    
     /**
     * opens the logfile on sd card
     * @return if save was successful
     */
    boolean _sd_open(void);
    
    /**
     * closes the datafile on sd card
     * @return if save was successful
     */
    void _sd_close(void);
    
    
#ifdef __cplusplus
}
#endif
#endif // _ARDUINO_WRAPPER_H_
