GR-SAKURA_btstack
=================

GR-SAKURAのUSB HOSTを使用してUSB Bluetooth ドングルでSPP通信ができるようにします

GR-SAKURAでUSB HOSTを使う場合ジャンパーの設定(J13,J15の接続)が必要です
J1の接続も必要と思われる

##動作確認環境
 ドングル
 BT-MicroEDR1X PLANEX

 接続先
 Android 2.3.6

##わかっている問題
インタラプト転送とバルク転送のリードタイミングをバルク通信を間引いて調整しています


##手順

btstackをダウンロード
btstack - A Portable User-Space Bluetooth Stack - Google Project Hosting 
<http://code.google.com/p/btstack/>


このリポジトリのファイルとbtstackのファイルを以下のフォルダ構成にします
<pre>
┬─bt_spp.c
│  bt_spp.h
│  gr_sketch.cpp
│  usb_bt.c
│  usb_bt.h
│  
└─btstack
    ├─hal
    │      rx_hal.c
    │      
    ├─include
    │  └─btstack
    │          btstack.h
    │          config.h
    │          hal_cpu.h
    │          hal_tick.h
    │          hal_uart_dma.h
    │          hci_cmds.h
    │          linked_list.h
    │          memory_pool.h
    │          run_loop.h
    │          sdp_util.h
    │          utils.h
    │          
    └─src
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

##btstackの以下のファイルを変更します

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

##SPP通信の詳細

bt_spp.c

bt_spp_recive_callback
接続中のSPPから受信した場合に呼ばれます


bt_spp_send
接続中のSPPに送信します

packet_handler
ペアリングの番号や装置名を設定しています

