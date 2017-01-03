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
