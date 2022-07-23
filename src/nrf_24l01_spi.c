#include "nrf_24l01_spi.h"

#include "wifiiot_spi.h"
#include "hal_wifiiot_spi.h"

#include "wifiiot_gpio.h"
#include "wifiiot_gpio_ex.h"


typedef unsigned char uint8_t;
typedef unsigned short uint16_t;


void set_ce_value(unsigned char value)
{
     GpioSetOutputVal(WIFI_IOT_GPIO_IDX_9,value);
}
unsigned char get_IrQ_value()
{
    unsigned char value ;
    GpioGetInputVal(WIFI_IOT_GPIO_IDX_10,&value);
    return value;
}
void nrf_24l01_gpio_init()
{
 GpioInit();
 //GPIO_CE  
 IoSetFunc(WIFI_IOT_IO_NAME_GPIO_9,  WIFI_IOT_IO_FUNC_GPIO_9_GPIO);
 GpioSetDir(WIFI_IOT_GPIO_IDX_9, WIFI_IOT_GPIO_DIR_OUT);
 //GPIO_IrQ
 IoSetFunc(WIFI_IOT_IO_NAME_GPIO_10,  WIFI_IOT_IO_FUNC_GPIO_10_GPIO);
 GpioSetDir(WIFI_IOT_GPIO_IDX_10, WIFI_IOT_GPIO_DIR_IN);

 /* IO 复用 */
 hi_io_set_func(HI_IO_NAME_GPIO_5, HI_IO_FUNC_GPIO_5_SPI0_CSN);
 hi_io_set_func(HI_IO_NAME_GPIO_6, HI_IO_FUNC_GPIO_6_SPI0_CK);
 hi_io_set_func(HI_IO_NAME_GPIO_7, HI_IO_FUNC_GPIO_7_SPI0_RXD);
 hi_io_set_func(HI_IO_NAME_GPIO_8, HI_IO_FUNC_GPIO_8_SPI0_TXD);
 hi_io_set_driver_strength(HI_IO_NAME_GPIO_8, HI_IO_DRIVER_STRENGTH_0);
}

unsigned int nrf_24l01_spi_init()
{

 unsigned int ret;

 hi_spi_cfg_init_param init_param;
 /* 主模式设置 */
 init_param.is_slave = HI_FALSE;
 hi_spi_cfg_basic_info spi_cfg;
 /* spi cfg 参数设置 */
 spi_cfg.cpha = 0; /* 极性 相性 */
 spi_cfg.cpol = 0; 
 spi_cfg.data_width = 7; /* 数据位宽 */
 spi_cfg.endian = 0; /* 小端 */
 spi_cfg.fram_mode = 0; /* 帧协议 */

 spi_cfg.freq = 8000000; /* 频率 */
 
 nrf_24l01_gpio_init(); //gpio init 
 
 ret = hi_spi_init(0, init_param, &spi_cfg);

 return ret;
}

/**
  * @brief :SPI收发一个字节
  * @param :
  *			@TxByte: 发送的数据字节
  * @note  :非堵塞式，一旦等待超时，函数会自动退出
  * @retval:接收到的字节
  */
uint8_t drv_spi_read_write_byte( uint8_t TxByte )
{
	uint8_t l_Data = 0;
	hi_spi_host_write(0,&TxByte,1);
  hi_spi_host_read(0,&l_Data,1);
	return l_Data;		
}

