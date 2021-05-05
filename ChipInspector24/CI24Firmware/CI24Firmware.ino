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

#include "LogicDump.h"
#include "PinControl.h"

const char* HELP_COMMAND = "help";
const char* LOGICDUMP_COMMAND = "logicdump";

const char* LOGICDUMP_SUPPORTED_PIN_COUNTS_TEXT = "10, 12, 14, 16, 18, 20, 22 or 24";

// the setup routine runs once when you press reset:
void setup()
{
  Serial.begin(9600); // USB is always 12 Mbit/sec

  DebugCheckSocketPins();
}

String ReadCommandString()
{
  String result;

  for (;;)
  {
    while (Serial.available())
    {
      int data = Serial.read();
      if (data == '\n')
      {
        return result;
      }
      else if (data >= 0)
      {
        result += (char)data;
      }
    }
  }
}

void ShowHelp()
{
    Serial.println("Supported commands:");
    Serial.println();

    Serial.print(HELP_COMMAND);
    Serial.println(" - Show this help");
    Serial.println();
    
    Serial.print(LOGICDUMP_COMMAND);
    Serial.println(" <pin count> - Dump I/O logic tables for device.");
    Serial.print("<pin count> is one of ");
    Serial.println(LOGICDUMP_SUPPORTED_PIN_COUNTS_TEXT);
    Serial.print("For example: ");
    Serial.print(LOGICDUMP_COMMAND);
    Serial.println(" 24");
    Serial.println();
}

bool IsSupportedDevicePinCount(int pinCount)
{
  return pinCount >= 10 && pinCount <= 24 && (pinCount % 0x01) == 0;
}

// the loop routine runs over and over again forever:
void loop()
{
  // Initialize Teensy.
  delay(100);  // Just in case a previous operation needs time to settle.
  //TODO: Set all pins to inputs.

  // Show welcome message. 
  Serial.print("Enter command string. Enter '");
  Serial.print(HELP_COMMAND);
  Serial.println("' for list of commands.");
  
  String commandString = ReadCommandString().trim().toLowerCase();
  if (commandString.length() > 0)
  {   
    Serial.print("Received command string: ");
    Serial.println(commandString);

    if (commandString == HELP_COMMAND)
    {
      ShowHelp();
    }
    else if (commandString.startsWith(LOGICDUMP_COMMAND))
    {
      int pinCount = 0;

      if (sscanf(commandString.c_str() + strlen(LOGICDUMP_COMMAND), "%d", &pinCount) != 1 ||
          !IsSupportedDevicePinCount(pinCount))
      {
        Serial.print("Please specify one of the supported pin counts: ");
        Serial.println(LOGICDUMP_SUPPORTED_PIN_COUNTS_TEXT);
      }
      else
      {
        LogicDump(pinCount);
      }
    }
    else
    {
        Serial.println("Unrecognised command.");
    }
  }
}
