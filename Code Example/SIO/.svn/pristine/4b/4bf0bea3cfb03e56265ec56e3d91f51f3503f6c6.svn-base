==========================================================================
                  SIO Project for 8FX Series (MB95200)
==========================================================================
               Fujitsu Microelectronics (Shanghai) Co., LTD.       
                                                            
 The following  software  is for  demonstration  purposes only.  It is not
 fully  tested, nor validated  in order  to fullfill  its task  under  all
 circumstances.  Therefore,  this software or  any part of it must only be
 used in an evaluation laboratory environment.                        
 This software is subject to the rules of our standard DISCLAIMER, that is
 delivered with our  SW-tools on the Fujitsu Microcontrollers CD or on our 
 Internet Page:  http://www.fujitsu.com/cn/fmc/
==========================================================================
               
History
Date      Ver     Author  Softune     Description
14.04.08  1.0     XXX     V30L31      original version
==========================================================================

This is a project template for the MB95200 Series. 
It includes some basic settings for e.g. Linker, C-Compiler 
which must be checked and modified in detail, 
corresponding to the user application.

Description:
In this example:

SIO TX side will keep on sending data to RX side and toggle LED2 if correct 
data returned from RX side.

SIO RX side will toggle LED4 if recieved correct data from TX side.

Then the infinity sign will be animated.

NOTE: 
-----
This template uses the headerfile _mb95200.h 
of the 8FX chip MB95200.
Take care that not all resources will be available 
in each 8FX flash-/mask-device.

Further, ROM and RAM settings are limited within this project.
Correct these settings within the Linker-Options:

- Softune Workbench
  - Project
    - Setup Poject
      - Linker: Category: Disposition-Connection

        RAM  240 byte: 0x90 - 0x17F
             496 byte: 0x90 - 0x27F
    
        ROM    4k :  0xF000 - 0xFFFF
               8k :  0xE000 - 0xFFFF
              16k :  0xC000 - 0xFFFF
       
Please check the datasheet and hardwaremanual of the related product.


