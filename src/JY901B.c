#include "JY901B.h"

#include "ohos_init.h"
#include "cmsis_os2.h"
#include "wifiiot_errno.h"
#include "wifiiot_gpio.h"
#include "wifiiot_gpio_ex.h"
#include "wifiiot_i2c.h"
#include "wifiiot_i2c_ex.h"

#define I2C_TASK_STACK_SIZE 1024 * 8
#define I2C_TASK_PRIO 2

void init_jy901b(void)
{
    GpioInit();
    //GPIO_0复用为I2C1_SDA
    IoSetFunc(WIFI_IOT_IO_NAME_GPIO_0, WIFI_IOT_IO_FUNC_GPIO_0_I2C1_SDA);
    //GPIO_1复用为I2C1_SCL
    IoSetFunc(WIFI_IOT_IO_NAME_GPIO_1, WIFI_IOT_IO_FUNC_GPIO_1_I2C1_SCL);
    //baudrate: 400kbps
    I2cInit(WIFI_IOT_I2C_IDX_1, 400000);
    I2cSetBaudrate(WIFI_IOT_I2C_IDX_1, 400000);
    //printf("jy901  start \n");
}

static short CharToShort(unsigned char cData[])
{
	return ((short)cData[1]<<8)|cData[0];
}
unsigned char  jy901b_read_data(unsigned char address,struct JY901B_type * j901b_t)
{
    unsigned int status = 0;
    WifiIotI2cData nt3h1101_i2c_data = {0};
    unsigned char  buffer[1] = {address};

    if(j901b_t)
    { 
         //printf("j901b_t type is NULL \n");
         return -1;
    }
    nt3h1101_i2c_data.sendBuf = buffer;
    nt3h1101_i2c_data.sendLen = 1;
    nt3h1101_i2c_data.receiveBuf = j901b_t->chrTemp;
    nt3h1101_i2c_data.receiveLen = JY901B_DATA_SIZE;
    status = I2cWriteread(WIFI_IOT_I2C_IDX_1, (JY901B_ADDR_SLAVE<<1)|0x00, &nt3h1101_i2c_data);
    if (status != 0)
    {
        //printf("===== Error: I2C write status = 0x%x! =====\r\n", status);
        return 0;
    }
    j901b_t->a[0] = (float)CharToShort(j901b_t->chrTemp+0)/32768*16;
	j901b_t->a[1] = (float)CharToShort(j901b_t->chrTemp+2)/32768*16;
	j901b_t->a[2] = (float)CharToShort(j901b_t->chrTemp+4)/32768*16;
	j901b_t->w[0] = (float)CharToShort(j901b_t->chrTemp+6)/32768*2000;
	j901b_t->w[1] = (float)CharToShort(j901b_t->chrTemp+8)/32768*2000;
    j901b_t->w[2] = (float)CharToShort(j901b_t->chrTemp+10)/32768*2000;
	j901b_t->h[0] = CharToShort(j901b_t->chrTemp+12);
	j901b_t->h[1] = CharToShort(j901b_t->chrTemp+14);
	j901b_t->h[2] = CharToShort(j901b_t->chrTemp+16);
	j901b_t->Angle[0] = (float)CharToShort(j901b_t->chrTemp+18)/32768*180; //x 
    j901b_t->Angle[1] = (float)CharToShort(j901b_t->chrTemp+20)/32768*180; //y
	j901b_t->Angle[2] = (float)CharToShort(j901b_t->chrTemp+22)/32768*180; //z
    return 1;
}
