GR-SAKURA_btstack
=================

GR-SAKURA��USB HOST���g�p����USB Bluetooth �h���O����SPP�ʐM���ł���悤�ɂ��܂�

GR-SAKURA��USB HOST���g���ꍇ�W�����p�[�̐ݒ�(J13,J15�̐ڑ�)���K�v�ł�
J1�̐ڑ����K�v�Ǝv����

##����m�F��
 �h���O��
 BT-MicroEDR1X PLANEX

 �ڑ���
 Android 2.3.6

##�킩���Ă�����
�C���^���v�g�]���ƃo���N�]���̃��[�h�^�C�~���O���o���N�ʐM���Ԉ����Ē������Ă��܂�


##�菇

btstack���_�E�����[�h
btstack - A Portable User-Space Bluetooth Stack - Google Project Hosting 
<http://code.google.com/p/btstack/>


���̃��|�W�g���̃t�@�C����btstack�̃t�@�C�����ȉ��̃t�H���_�\���ɂ��܂�
<pre>
����bt_spp.c
��  bt_spp.h
��  gr_sketch.cpp
��  usb_bt.c
��  usb_bt.h
��  
����btstack
    ����hal
    ��      rx_hal.c
    ��      
    ����include
    ��  ����btstack
    ��          btstack.h
    ��          config.h
    ��          hal_cpu.h
    ��          hal_tick.h
    ��          hal_uart_dma.h
    ��          hci_cmds.h
    ��          linked_list.h
    ��          memory_pool.h
    ��          run_loop.h
    ��          sdp_util.h
    ��          utils.h
    ��          
    ����src
            btstack_memory.c
            btstack_memory.h
            bt_control.h
            debug.h
            hci.c
            hci.h
            hci_cmds.c
            hci_dump.c
            hci_dump.h
            hci_transport.h
            hci_transport_rxusb.c
            l2cap.c
            l2cap.h
            l2cap_signaling.c
            l2cap_signaling.h
            linked_list.c
            memory_pool.c
            remote_device_db.h
            remote_device_db_memory.c
            rfcomm.c
            rfcomm.h
            run_loop.c
            run_loop_embedded.c
            run_loop_private.h
            sdp.c
            sdp.h
            sdp_util.c
            utils.c
</pre>

##btstack�̈ȉ��̃t�@�C����ύX���܂�

<pre>
hci_cmds.c

127c127
<                 pos += 248;
---
>                 pos += len+1;
</pre>

<pre>
run_loop_embedded.c

146c146
<     while (1) {
---
> //    while (1) {
166c166
<         hal_cpu_disable_irqs();
---
> /*        hal_cpu_disable_irqs();
172c172
<     }
---
>     }*/
</pre>

##SPP�ʐM�̏ڍ�

bt_spp.c

bt_spp_recive_callback
�ڑ�����SPP�����M�����ꍇ�ɌĂ΂�܂�


bt_spp_send
�ڑ�����SPP�ɑ��M���܂�

packet_handler
�y�A�����O�̔ԍ��⑕�u����ݒ肵�Ă��܂�

