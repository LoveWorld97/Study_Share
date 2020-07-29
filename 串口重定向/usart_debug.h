/*ʹ��˵����ʹ�ñ�׼���ض���printf()���� 
	1.���ô��ںʹ���handle
	2.����Ҫ�ĵط����usart_debug.hͷ�ļ�
	3.ʹ��printf()����--��֧�ָ�������� 
*/

#ifndef __USART_DEBUG_H
#define __USART_DEBUG_H

#define USART_DEBUG USART3			/*����ʹ�õĴ���*/
#define huart_debug huart3 			/*����ʹ�õĴ���handle*/ 

/*stm32cubemx���ô��ں��Զ����ɵ�ͷ�ļ��������������*/
#include "usart.h"
/*�ض�����Ҫʹ�õ���ͷ�ļ�*/ 
#include "stdio.h"

/*��֪����������c������ʹ�ð������ĺ���--��ʹ�ð�����ģʽ*/
#pragma import(__use_no_semihosting)

/*���¶���__write����*/ 
int _write(int fd, char *ptr, int len)
{
	HAL_UART_Transmit(&huart_debug, (uint8_t *)ptr, len, 0xFFFF);
	return len;
}

/*����_sys_exit()�Ա���ʹ�ð�����ģʽ*/ 
void _sys_exit(int x)
{
	x = x;
}

/*��׼����Ҫ��֧������*/ 
struct __FILE
{
	int handle;
};
FILE __stdout;

/*�ض���fputc()*/
int fputc(int ch, FILE *stream)
{
	/*�����жϴ����Ƿ������*/
	while((USART_DEBUG->ISR & 0x40) == 0)
	;
	/*���ڷ�����ɣ������ֽڷ���*/
	USART_DEBUG->TDR = (uint8_t) ch;
	return ch;
}
 
#endif /*__USART_DEBUG_H*/  
