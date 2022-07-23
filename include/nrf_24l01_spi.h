#ifndef  __NRF_21L01_SPI___
#define  __NRF_21L01_SPI___

#include "hi_io.h"
#include "hi_spi.h"


/** 口线操作函数定义 */
#define RF24L01_SET_CE_HIGH( )		set_ce_value(1);
#define RF24L01_SET_CE_LOW( )		set_ce_value(0);	

#define RF24L01_GET_IRQ_STATUS( )	get_IrQ_value();



#define BUFFSIZE   64 


void set_ce_value(unsigned char value);
unsigned char get_IrQ_value();

unsigned int nrf_24l01_spi_init();

typedef  struct nrf_24l01_spi_type
{
    int fd;
    unsigned char Txbuf[BUFFSIZE];
    unsigned char Tx_value;
    unsigned char Rxbuf[BUFFSIZE];
    unsigned char Rx_value;
    unsigned int send_len ;
    unsigned int recv_len ;
}nrf_24l01_spi_type;

#endif // !