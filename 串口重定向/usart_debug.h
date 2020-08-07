/*使用说明：使用标准库重定向printf()函数 
	1.配置串口和串口handle
	2.在需要的地方添加usart_debug.h头文件
	3.使用printf()函数--不支持浮点数输出 
*/

#ifndef __USART_DEBUG_H
#define __USART_DEBUG_H

#define USART_DEBUG USART3			/*配置使用的串口*/
#define huart_debug huart3 			/*配置使用的串口handle*/ 

/*stm32cubemx配置串口后自动生成的头文件，这里包含以下*/
#include "usart.h"
/*重定向需要使用到的头文件*/ 
#include "stdio.h"

/*告知连接器不从c库链接使用半主机的函数--不使用半主机模式*/
#pragma import(__use_no_semihosting)

/*重新定义__write函数*/ 
int _write(int fd, char *ptr, int len)
{
	HAL_UART_Transmit(&huart_debug, (uint8_t *)ptr, len, 0xFFFF);
	return len;
}

/*定义_sys_exit()以避免使用半主机模式*/ 
void _sys_exit(int x)
{
	x = x;
}

/*标准库需要的支持类型*/ 
struct __FILE
{
	int handle;
};
FILE __stdout;

/*重定向fputc()*/
int fputc(int ch, FILE *stream)
{
	/*堵塞判断串口是否发送完成*/
	while((USART_DEBUG->SR & 0x40) == 0)
	;
	/*串口发送完成，将该字节发送*/
	USART_DEBUG->DR = (uint8_t) ch;
	return ch;
}
 
#endif /*__USART_DEBUG_H*/  
