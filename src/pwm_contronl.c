#include "ohos_init.h"
#include "cmsis_os2.h"
#include "wifiiot_pwm.h"
#include "wifiiot_gpio.h"
#include "wifiiot_gpio_ex.h"
#include "pwm_contronl.h"

void pwm_contronl_init(void)
{
    //初始化GPIO
    GpioInit();
    //COM1
    IoSetFunc(WIFI_IOT_IO_NAME_GPIO_2, WIFI_IOT_IO_FUNC_GPIO_2_PWM2_OUT);
    GpioSetDir(WIFI_IOT_IO_NAME_GPIO_2, WIFI_IOT_GPIO_DIR_OUT);
    PwmInit(WIFI_IOT_PWM_PORT_PWM2);
    //COM2
    IoSetFunc(WIFI_IOT_IO_NAME_GPIO_3, WIFI_IOT_IO_FUNC_GPIO_3_PWM5_OUT);
    GpioSetDir(WIFI_IOT_IO_NAME_GPIO_3, WIFI_IOT_GPIO_DIR_OUT);
    PwmInit(WIFI_IOT_PWM_PORT_PWM5);
    //COM3
    IoSetFunc(WIFI_IOT_IO_NAME_GPIO_4, WIFI_IOT_IO_FUNC_GPIO_4_PWM1_OUT);
    GpioSetDir(WIFI_IOT_IO_NAME_GPIO_4, WIFI_IOT_GPIO_DIR_OUT);
    PwmInit(WIFI_IOT_PWM_PORT_PWM1);
    //COM4
    IoSetFunc(WIFI_IOT_IO_FUNC_GPIO_12_GPIO, WIFI_IOT_IO_FUNC_GPIO_6_PWM3_OUT);
    GpioSetDir(WIFI_IOT_IO_FUNC_GPIO_12_GPIO, WIFI_IOT_GPIO_DIR_OUT);
    PwmInit(WIFI_IOT_PWM_PORT_PWM3);
}
/**
 * @brief 
 * 
 * @param com_t  COM  
 * @param duty_t 占空比
 * @param freq_t  频率
 * @return int 
 */
int pwm_com_set(WifiIotPwmPort com_t ,unsigned short duty_t ,unsigned short freq_t)
{
    return  PwmStart(com_t, duty_t, freq_t);
}
unsigned int pwm_com_stop(WifiIotPwmPort com_t)
{
  return PwmStop(com_t);
}
