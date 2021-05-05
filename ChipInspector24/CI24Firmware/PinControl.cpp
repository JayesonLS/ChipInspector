/* 
Chip Inspector 24 Firmware
Copyright (C) 2021 Titanium Studios Pty. Ltd.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <Arduino.h>
#include "PinControl.h"

#define MAX_PINS 24
#define MAX_IO_PINS 22

static uint8_t socketDirectPins[MAX_PINS] =
{
  2, // 1
  1, // 2
  0, // 3
  27, // 4
  45, // 5
  44, // 6
  43, // 7
  42, // 8
  41, // 9
  40, // 10
  39, // 11
  38, // 12
  13, // 13
  35, // 14
  30, // 15
  11, // 16
  10, // 17
  9, // 18
  8, // 19
  7, // 20
  6, // 21
  5, // 22
  4, // 23
  (uint8_t)-1  // 24
};

static uint8_t socketResistorPins[MAX_PINS] =
{
  26, // 1
  37, // 2
  24, // 3
  22, // 4
  20, // 5
  18, // 6
  32, // 7
  33, // 8
  14, // 9
  15, // 10
  16, // 11
  17, // 12
  31, // 13
  12, // 14
  34, // 15
  29, // 16
  28, // 17
  19, // 18
  21, // 19
  23, // 20
  25, // 21
  36, // 22
  3, // 23
  (uint8_t)-1  // 24
};

static uint8_t socketAnalogDirectPins[MAX_PINS] =
{
  (uint8_t)-1, // 1
  (uint8_t)-1, // 2
  (uint8_t)-1, // 3
  (uint8_t)-1, // 4
  A7, // 5
  A6, // 6
  A5, // 7
  A4, // 8
  A3, // 9
  A2, // 10
  A1, // 11
  A0, // 12
  (uint8_t)-1, // 13
  (uint8_t)-1, // 14
  (uint8_t)-1, // 15
  (uint8_t)-1, // 16
  (uint8_t)-1, // 17
  (uint8_t)-1, // 18
  (uint8_t)-1, // 19
  (uint8_t)-1, // 20
  (uint8_t)-1, // 21
  (uint8_t)-1, // 22
  (uint8_t)-1, // 23
  (uint8_t)-1  // 24
};

void DebugCheckSocketPins()
{
  for (int i = 0; i < MAX_PINS; i++)
  {
    uint8_t directPin = socketDirectPins[i];
    uint8_t resistorPin = socketResistorPins[i];

    for (int j = 0; j < MAX_PINS; j++)
    {
      if (directPin != (uint8_t)-1)
      {
        if (directPin == socketDirectPins[j] && j != i)
        {
          Serial.println(String("!!!! ERROR !!!!: directPin[") + i + "] same as directPin[" + j + "].");
        }
        if (directPin == socketResistorPins[j])
        {
          Serial.println(String("!!!! ERROR !!!!: directPin[") + i + "] same as resistorPin[" + j + "].");
        }
      }
      if (resistorPin != (uint8_t)-1)
      {
        if (resistorPin == socketDirectPins[j])
        {
          Serial.println(String("!!!! ERROR !!!!: resistorPin[") + i + "] same as directPin[" + j + "].");
        }
        if (resistorPin == socketResistorPins[j] && j != i)
        {
          Serial.println(String("!!!! ERROR !!!!: resistorPin[") + i + "] same as resistorPin[" + j + "].");
        }
      }
    }
  }
}
