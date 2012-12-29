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


/*
 * usb_bt.c
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tkusbhost.h"

#include "hci_cmds.h"
#include "hci_dump.h"
#include "bt_spp.h"
#include "usb_bt.h"

int usb_connected = 0;
unsigned char usb_int_buf[16];
unsigned char usb_bulk_buf[64];

static void (*usb_bt_event_handler)(unsigned char packet_type, unsigned char *packet, int size) = NULL;
int count = 0;
int usb_task(void)
{
int stat = -1;
    if(usb_connected == 0)
    {
        if(tkusbh_connect(500) != TKUSBH_OK)
        {
            printf("*Connection TIMEOUT. Retry...\n");
            return stat;
        }
        // ShowDescriptors();
        usb_connected = 1;

        printf("*Connected\n");

        bt_init();

        tkusbh_start_interrupt_trans(1,5,INTERRUPT_IN,NULL);
    }

    if(tkusbh_is_connected() == TKUSBH_DISCONNECT)
    {
        bt_terminate();

        tkusbh_disconnect(TIMEOUT_INFINITE);
        printf("*DisConnected...\n");
        usb_connected = 0;

        return stat;
    }

    {
        stat = tkusbh_interrupt_read(1,usb_int_buf,16);
        if(stat >= 0 && stat!=3)
        {
            if(usb_bt_event_handler != NULL)
            {
                usb_bt_event_handler(USB_BT_EVENT_INTERRUPT_READ, usb_int_buf, stat);
            }
        }
        if(count > 100000)
        {
            stat = tkusbh_bulk_read(2, usb_bulk_buf, 64, 1);
            if(stat >= 0)
            {
                if(usb_bt_event_handler != NULL)
                {
                    usb_bt_event_handler(USB_BT_EVENT_BULK_READ, usb_bulk_buf, stat);
                }
            }
            count= 0;
        }
        count++;
    }
return stat;
}

int usb_getstatus(void)
{
    return usb_connected;
}

int usb_bt_control_write( unsigned char *packet, int size)
{
    int ret = 0;
    unsigned short req = (USB_DIR_H2D|USB_REQ_TYPE_CLASS|USB_REQ_RECIPIENT_INTERFACE);
    ret = tkusbh_control_msg(req, 0, 0, size, packet, 3000);

    return ret;
}

int usb_bt_bulk_write( unsigned char *packet, int size)
{
    int ret = 0;
    ret = tkusbh_bulk_write(2, packet, size ,3000);
    return ret;
}

void usb_bt_register_packet_handler(void (*handler)(unsigned char packet_type, unsigned char *packet, int size))
{
    usb_bt_event_handler = handler;
}
