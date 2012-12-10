/*GR-SAKURA Sketch Template Version: V1.00*/

/*
Copyright (c) 2012, Akinori Harada
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are
met:

  * Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
  * Redistributions in binary form must reproduce the above
    copyright notice, this list of conditions and the following disclaimer
    in the documentation and/or other materials provided with the
    distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <rxduino.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tkusbhost.h"

#include "usb_bt.h"
#include "bt_spp.h"

#define INTERVAL 100

void setup()
{
    pinMode(PIN_LED0,OUTPUT);
    pinMode(PIN_LED1,OUTPUT);
    pinMode(PIN_LED2,OUTPUT);
    pinMode(PIN_LED3,OUTPUT);
    digitalWrite(PIN_LED0, 0);
    digitalWrite(PIN_LED1, 0);
    digitalWrite(PIN_LED2, 0);
    digitalWrite(PIN_LED3, 0);
    Serial.begin(38400,SCI_SCI0P2x);
    Serial.setDefault(); // printfをSerialに出力

    Serial.print("USB Host + Bluetooth\n");

    if(tkusbh_init() != TKUSBH_OK)
    {
        Serial.print("!!! USB Host Initialization ERROR !!! system halt\n");
        while(1);
    }
}

void loop()
{
	if(usb_task()==3)
	{
		//インタラプトIN転送で受信したデータ長が3のときはシステムをリセットする(フリーズ対策)
		system_reboot( REBOOT_USERAPP );
	}
    bt_task();
    if(Serial.available())
    {
      char c = Serial.read();
      if(c == 'b')
      {
      }
    }
    
    if((GetBtCommand() & 0x01) == 0x01)
    {
        digitalWrite(PIN_LED2, 1);
    }else{
        digitalWrite(PIN_LED2, 0);
    }
    if((GetBtCommand() & 0x02) == 0x02)
    {
        digitalWrite(PIN_LED3, 1);
    }else{
        digitalWrite(PIN_LED3, 0);
    }
}

