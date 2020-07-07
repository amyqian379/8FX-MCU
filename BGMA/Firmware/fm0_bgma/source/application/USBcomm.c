/**********************************************************************/
/* file name: USBcomm.c                                               */
/* function description: USB communication interface.                 */
/**********************************************************************/
/* ALL RIGHTS RESERVED, COPYRIGHT (C) FUJITSU LIMITED. 2007           */
/**********************************************************************/
//#include "frameio.h"
#include "version.h"
#include "LPCdef.h"

static uint8_t *USBbuf;
static uint16_t USBbufsize;

/** Frame Handling **/
void USBsetlen(uint16_t len)
{
    USBbufsize = len;
}

/**********************************************************************/
/* Function Name: get_paramb                                          */
/* Description: read 1 byte data from USB buffer                      */
/* Parameters: offset                                                 */
/* Return:  ---required data                                          */
/**********************************************************************/
uint8_t get_paramb(uint16_t offset)
{
    return USBbuf[FRMIN_BODY+offset];
}

/**********************************************************************/
/* Function Name: get_paramh                                          */
/* Description: read 2 byte data from USB buffer                      */
/* Parameters: offset                                                 */
/* Return:  ---required data                                          */
/**********************************************************************/
uint16_t get_paramh(uint16_t offset)
{
    uint16_t data;
    uint8_t *p = (void *)(&data);
    
    p[0] = USBbuf[FRMIN_BODY+offset+1];
    p[1] = USBbuf[FRMIN_BODY+offset+0];
    return data;
}

/**********************************************************************/
/* Function Name: get_paramw                                          */
/* Description: read 4 byte data from USB buffer                      */
/* Parameters: offset                                                 */
/* Return:  ---required data                                          */
/**********************************************************************/
uint32_t get_paramw(uint16_t offset)
{
    uint32_t data;
    uint8_t *p = (void *)(&data);
    
    p[0] = USBbuf[FRMIN_BODY+offset+3];
    p[1] = USBbuf[FRMIN_BODY+offset+2];
    p[2] = USBbuf[FRMIN_BODY+offset+1];
    p[3] = USBbuf[FRMIN_BODY+offset+0];
    return data;
}

/**********************************************************************/
/* Function Name: put_paramb                                          */
/* Description: write 1 byte data to USB buffer                       */
/* Parameters: offset; data ---write value                            */
/* Return: none                                                       */
/**********************************************************************/
void put_paramb(uint16_t offset, uint8_t data)
{
    USBbuf[FRMOUT_BODY+offset] = data;
}

/**********************************************************************/
/* Function Name: put_paramh                                          */
/* Description: write 2 byte data to USB buffer                       */
/* Parameters: offset; data ---write value                            */
/* Return: none                                                       */
/**********************************************************************/
void put_paramh(uint16_t offset, uint16_t data)
{
    uint8_t *p = (void *)(&data);

    USBbuf[FRMOUT_BODY+offset+0] = p[1];
    USBbuf[FRMOUT_BODY+offset+1] = p[0];
}

/**********************************************************************/
/* Function Name: put_paramw                                          */
/* Description: write 4 byte data to USB buffer                       */
/* Parameters: offset; data ---write value                            */
/* Return: none                                                       */
/**********************************************************************/
void put_paramw(uint16_t offset, uint32_t  data)
{
    uint8_t *p = (void *)(&data);
    
    USBbuf[FRMOUT_BODY+offset+0] = p[3];
    USBbuf[FRMOUT_BODY+offset+1] = p[2];
    USBbuf[FRMOUT_BODY+offset+2] = p[1];
    USBbuf[FRMOUT_BODY+offset+3] = p[0];
}

/**********************************************************************/
/* Function Name: put_param16                                          */
/* Description: write 16 byte data to USB buffer                       */
/* Parameters: offset; data ---write value                            */
/* Return: none                                                       */
/**********************************************************************/
void put_param16(uint16_t offset, uint8_t  *data)
{
    uint8_t i;
    for(i=0;i<16;i++)
    {
        USBbuf[FRMOUT_BODY+offset+i] = *(data++);
    }
}

/**********************************************************************/
/* Function Name: put_frmlen                                          */
/* Description: set sending frame length                              */
/* Parameters: len                                                    */
/* Return: none                                                       */
/**********************************************************************/
void put_frmlen(uint16_t len)
{
    USBsetlen(FRMOUT_BODY+(uint16_t)len);
}

/**********************************************************************/
/* Function Name: put_normal                                          */
/* Description: initial frame buffer,set frame to normal              */
/* Parameters: none                                                   */
/* Return: none                                                       */
/**********************************************************************/
void put_normal(void)
{
    USBbuf[FRMOUT_ENUM] = 00U;       /* no error */
    put_frmlen(0);
}

/** Error Frame Handling **/
/**********************************************************************/
/* Function Name: set_errcode                                         */
/* Description: set error code frame: 01 err 00 00                    */
/* Parameters: err                                                    */
/* Return: NORMAL                                                     */
/**********************************************************************/
uint8_t set_errcode(uint8_t err)
{
    USBbuf[FRMOUT_ENUM]    = 0x01U;
    USBbuf[FRMOUT_ECODE]   = err;
    USBbuf[FRMOUT_EFLAG]   = 0x00U;
    USBbuf[FRMOUT_EFLAG+1] = 0x00U;
    USBsetlen(FRMOUT_ELEN1);
    return NORMAL;
}

/**********************************************************************/
/* Function Name: set_erradrs                                         */
/* Description: set error address frame                               */
/* Parameters: err; adrs ---error address                             */
/* Return: NORMAL                                                     */
/**********************************************************************/
uint8_t set_erradrs(uint8_t err, uint16_t adrs)
{
    USBbuf[FRMOUT_ENUM]    = 0x01U;
    USBbuf[FRMOUT_ECODE]   = err;
    USBbuf[FRMOUT_EFLAG]   = 0x00U;
    USBbuf[FRMOUT_EFLAG+1] = 0x01U;
    USBbuf[FRMOUT_EADRS+0] = 0x00U;
    USBbuf[FRMOUT_EADRS+1] = 0x00U;
    USBbuf[FRMOUT_EADRS+2] = adrs>>8;
    USBbuf[FRMOUT_EADRS+3] = adrs&0xFF;
    USBsetlen(FRMOUT_ELEN2);
    return NORMAL;
}

void set_usbbuf_pointer(uint8_t* pUSBbuf)
{
    USBbuf = pUSBbuf;
}

uint8_t* get_usbbuf_pointer(void)
{
    return USBbuf;
}


uint16_t get_usbbuf_size(void)
{
    return USBbufsize;
}
