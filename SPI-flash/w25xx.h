#ifndef __W25X_H
#define __W25X_H

#include "main.h"
#define hspix hspi1     /*����ʹ�õ�spi handle*/
#define W25XCS_L HAL_GPIO_WritePin(SPI_FLASH_CS_GPIO_Port, SPI_FLASH_CS_Pin, GPIO_PIN_RESET);   /*����spi-cs����*/
#define W25XCS_H HAL_GPIO_WritePin(SPI_FLASH_CS_GPIO_Port, SPI_FLASH_CS_Pin, GPIO_PIN_SET);
#define FLASH_ID 0XEF16             //W25X64��ID

//W25X16ָ���
#define W25X_WriteEnable 0x06       //дʹ��
#define W25X_WriteDisable 0x04      //д��ֹ
#define W25X_ReadStatusReg 0x05     //��״̬�Ĵ���
#define W25X_WriteStatusReg 0x01    //д״̬�Ĵ���
#define W25X_ReadData 0x03          //������
#define W25X_FastReadData 0x0B      //���
#define W25X_FastReadDual 0x3B      //���˫���
#define W25X_PageProgram 0x02       //ҳ���
#define W25X_BlockErase 0xD8        //�����(64K)
#define W25X_SectorErase 0x20       //��������(4K)
#define W25X_ChipErase 0xC7         //оƬ����
#define W25X_PowerDown 0xB9         //����
#define W25X_ReleasePowerDown 0xAB  //�ͷŵ���
#define W25X_DeviceID 0xAB          //������ID
#define W25X_ManufactDeviceID 0x90  //������ID+����ID
#define W25X_JedecDeviceID 0x9F     //��JEDEC ID

extern uint16_t SPI_W25X_ReadID(void);
uint8_t SPI_W25X_ReadSR(void);
void SPI_W25X_Write_SR(unsigned char sr);
void SPI_W25X_Write_Enable(void);
void SPI_W25X_Write_Disable(void);
void SPI_W25X_Read(unsigned char *pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead);
void SPI_W25X_Write(unsigned char *pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
void SPI_W25X_Erase_Chip(void);
void SPI_W25X_Erase_Sector(uint32_t Dst_Addr);
void SPI_W25X_Wait_Busy(void);
void SPI_W25X_PowerDown(void);
void SPI_W25X_WAKEUP(void);

uint8_t SPI_W25X_Read_onebyte(unsigned int ReadAddr);
void SPI_W25X_Write_onebyte(uint16_t WriteAddr, uint8_t data);

#endif