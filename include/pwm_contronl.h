#ifndef  __PWM_CONTRONL__
#define  __PWM_CONTRONL__
#include "wifiiot_gpio.h"
#define PWMCOM1 WIFI_IOT_PWM_PORT_PWM2
#define PWMCOM2 WIFI_IOT_PWM_PORT_PWM5
#define PWMCOM3 WIFI_IOT_PWM_PORT_PWM1
#define PWMCOM4 WIFI_IOT_PWM_PORT_PWM3

unsigned int pwm_com_stop(WifiIotPwmPort com_t);
unsigned int pwm_com_stop(WifiIotPwmPort com_t);
void pwm_contronl_init(void);


#endif // !  
