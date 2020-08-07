#include "w25xx.h"
#include "spi.h"
#include "main.h"
#include "stdint.h"

/*��װ��д����
SPI ��дһ���ֽ�
//TxData:Ҫд����ֽ�
//����ֵ:��ȡ�����ֽ�
*/
uint8_t SPI_ReadWriteByte(uint8_t TxData)
{
    uint8_t Rxdata;
    HAL_SPI_TransmitReceive(&hspix, &TxData, &Rxdata, 1, 1000);
    return Rxdata; //�����յ�������
}

/*********************************************************************
*
*	function name  : SPI_W25X_ReadSR   
*	function       : read W25Q16 status register
*	input          :
*	output         :  nonce
*	return         :  byte
*	revised record ��1.
*                  2.
*remarks         :  
BIT:   7    6    5    4    3    2    1    0
       SPR  RV   TB   BP2  BP1  BP0  WEL  BUSY
SPR:Ĭ��0,״̬�Ĵ�������λ,���WPʹ��
TB,BP2,BP1,BP0:FLASH����д��������
WEL:дʹ������
BUSY:æ���λ(1,æ;0,����)
Ĭ��:0x00
**********************************************************************/
uint8_t SPI_W25X_ReadSR(void)
{
    uint8_t byte = 0;

    W25XCS_L;                               /*enable chip selection*/
    SPI_ReadWriteByte(W25X_ReadStatusReg); /*send read status register command */
    byte = SPI_ReadWriteByte(0Xff);        /*read one byte */
    W25XCS_H;                               /*disable chip selection*/

    return byte;
}
/*********************************************************************
*
*	function name  : SPI_W25X_Write_SR   
*	function       : write W25Q16 status register
*	input          : sr
*	output         :  nonce
*	return         :  nonce
*	revised record ��1.
*                  2.
*remarks         :  

**********************************************************************/
void SPI_W25X_Write_SR(uint8_t sr)
{
    W25XCS_L;                                /*enable chip selection*/
    SPI_ReadWriteByte(W25X_WriteStatusReg); /*send write status register command */
    SPI_ReadWriteByte(sr);                  /*write one byte*/
    W25XCS_H;                                /*disable chip selection*/
}

/*********************************************************************
*
*	function name  : SPI_W25X_Write_Enable   
*	function       : enble W25Q16 write
*	input          : nonce
*	output         : nonce
*	return         : nonce
*	revised record ��1.
*                  2.
*remarks         :  
**********************************************************************/
void SPI_W25X_Write_Enable(void)
{
    W25XCS_L;                             /*enable chip selection*/
    SPI_ReadWriteByte(W25X_WriteEnable); /*send write enable*/
    W25XCS_H;                             /*disable chip selection*/
}

/*********************************************************************
*
*	function name  : SPI_W25X_Write_Disable   
*	function       : disable W25Q16 write
*	input          : nonce
*	output         : nonce
*	return         : nonce
*	revised record ��1.
*                  2.
*remarks         :  
**********************************************************************/
void SPI_W25X_Write_Disable(void)
{
    W25XCS_L;                              /*enable chip selection*/
    SPI_ReadWriteByte(W25X_WriteDisable); /*send write disable*/
    W25XCS_H;                              /*disable chip selection*/
}

/*********************************************************************
*
*	function name  : SPI_W25X_ReadID   
*	function       : read w25q16 ID 
*	input          : nonce
*	output         : nonce
*	return         : Temp
*	revised record ��1.
*                  2.
*remarks         :  ID:0XEF14
**********************************************************************/
uint16_t SPI_W25X_ReadID(void)
{
    uint16_t Temp = 0;

    W25XCS_L; /*enable chip selection*/
    SPI_ReadWriteByte(W25X_ManufactDeviceID);
    SPI_ReadWriteByte(0x00);
    SPI_ReadWriteByte(0x00);
    SPI_ReadWriteByte(0x00);
    Temp |= SPI_ReadWriteByte(0xFF) << 8;
    Temp |= SPI_ReadWriteByte(0xFF);
    W25XCS_H; /*disable chip selection*/

    return Temp;
}

/*********************************************************************
*
*	function name  : SPI_W25X_Read   
*	function       : reading data of specified length at specified address 
*	input          : 1 pBuffer ��data store
                   2 ReadAddr: address to start reading(24bit)
                   3 NumByteToRead��Bytes to read(���65535)
*	output         : nonce
*	return         : nonce
*	revised record ��1.
*                  2.
*remarks         :  
**********************************************************************/
void SPI_W25X_Read(uint8_t *pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead)
{
    uint16_t i;

    W25XCS_L;
    SPI_ReadWriteByte(W25X_ReadData);
    SPI_ReadWriteByte((uint8_t)((ReadAddr) >> 16));
    SPI_ReadWriteByte((uint8_t)((ReadAddr) >> 8));
    SPI_ReadWriteByte((uint8_t)ReadAddr);

    for (i = 0; i < NumByteToRead; i++)
    {
        pBuffer[i] = SPI_ReadWriteByte(0XFF);
    }
    W25XCS_H;
}

/*********************************************************************
*
*	function name  : SPI_W25X_Read   
*	function       : reading data of specified length at specified address 
*	input          : 1 pBuffer ��data store
                   2 ReadAddr: address to start reading(24bit)
                   3 NumByteToRead��Bytes to read(���65535)
*	output         : nonce
*	return         : nonce
*	revised record ��1.
*                  2.
*remarks         :  
**********************************************************************/
uint8_t SPI_W25X_Read_onebyte(unsigned int ReadAddr)
{

    uint8_t tmp;
    W25XCS_L;
    SPI_ReadWriteByte(W25X_ReadData);
    SPI_ReadWriteByte((uint8_t)((ReadAddr) >> 16));
    SPI_ReadWriteByte((uint8_t)((ReadAddr) >> 8));
    SPI_ReadWriteByte((uint8_t)ReadAddr);

    tmp = SPI_ReadWriteByte(0XFF);
    W25XCS_H;
    return tmp;
}

/*********************************************************************
*
*	function name  : SPI_W25X_Write_onebyte   
*	function       : reading data of specified length at specified address 
*	input          : 1 pBuffer ��data store
                   2 ReadAddr: address to start reading(24bit)
                   3 NumByteToRead��Bytes to read(���65535)
*	output         : nonce
*	return         : nonce
*	revised record ��1.
*                  2.
*remarks         :  
**********************************************************************/
void SPI_W25X_Write_onebyte(uint16_t WriteAddr, uint8_t data)
{
    W25XCS_L;
    W25XCS_H;
}
//-----------------------------------------------------------------------------
//��һҳ(0~65535)��д������256���ֽڵ�����
//��ָ����ַ��ʼд�����256�ֽڵ�����
//pBuffer:���ݴ洢����ַ
//WriteAddr:д�����׵�ַ
//NumByteToWrite:��д����ֽ���(���256,�Ҳ��ó�����ҳ��ʣ���ֽ���)
void SPI_W25X_Write_Page(uint8_t *pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
    uint16_t i;

    SPI_W25X_Write_Enable(); //ʹ��Ƭѡ
    W25XCS_L;
    SPI_ReadWriteByte(W25X_PageProgram);
    SPI_ReadWriteByte((uint8_t)((WriteAddr) >> 16));
    SPI_ReadWriteByte((uint8_t)((WriteAddr) >> 8));
    SPI_ReadWriteByte((uint8_t)WriteAddr);

    for (i = 0; i < NumByteToWrite; i++)
    {
        SPI_ReadWriteByte(pBuffer[i]);
    }

    W25XCS_H;             //�ر�Ƭѡ
    SPI_W25X_Wait_Busy(); //�ȴ�д�����
}
//-----------------------------------------------------------------------------
//�޼���дSPI FLASH
//����ȷ����д�ĵ�ַ��Χ�ڵ�����ȫ��Ϊ0XFF,�����ڷ�0XFF��д������ݽ�ʧ��!
//�����Զ���ҳ����
//��ָ����ַ��ʼд��ָ�����ȵ�����,����Ҫȷ����ַ��Խ��!
//pBuffer:���ݴ洢��
//WriteAddr:��ʼд��ĵ�ַ(24bit)
//NumByteToWrite:Ҫд����ֽ���(���65535)
//CHECK OK
void SPI_W25X_Write_NoCheck(uint8_t *pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
    uint16_t pageremain;

    pageremain = 256 - WriteAddr % 256;
    if (NumByteToWrite <= pageremain)
        pageremain = NumByteToWrite; //������256�ֽ�
    while (1)
    {
        SPI_W25X_Write_Page(pBuffer, WriteAddr, pageremain);
        if (NumByteToWrite == pageremain)
            break; //д�����
        else
        {
            pBuffer += pageremain;
            WriteAddr += pageremain;

            NumByteToWrite -= pageremain; //��ȥ�Ѿ�д����ֽ�
            if (NumByteToWrite > 256)
                pageremain = 256;
            else
                pageremain = NumByteToWrite; //����256���ֽ�
        }
    }
}
//-----------------------------------------------------------------------------
//дW25X
//��ָ����ַ��ʼд��ָ�����ȵ�����
//pBuffer:���ݴ洢��
//WriteAddr:��ʼд��ĵ�ַ(24bit)
//NumByteToWrite:Ҫд����ֽ���(���65535)
uint8_t W25X_BUF[4096];
void SPI_W25X_Write(uint8_t *pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
    uint32_t secpos;
    uint16_t secoff;
    uint16_t secremain;
    uint16_t i;

    secpos = WriteAddr / 4096; //������ַ
    secoff = WriteAddr % 4096; //�������ڵ�ƫ��
    secremain = 4096 - secoff; //����ʣ��ռ�

    if (NumByteToWrite <= secremain)
        secremain = NumByteToWrite; //������4096�ֽ�
    while (1)
    {
        SPI_W25X_Read(W25X_BUF, secpos * 4096, 4096); //��������
        for (i = 0; i < secremain; i++)               //У��
        {
            if (W25X_BUF[secoff + i] != 0XFF)
                break; //��Ҫ����
        }

        if (i < secremain) //��Ҫ����
        {
            SPI_W25X_Erase_Sector(secpos);  //����������
            for (i = 0; i < secremain; i++) //����
            {
                W25X_BUF[i + secoff] = pBuffer[i];
            }
            SPI_W25X_Write_NoCheck(W25X_BUF, secpos * 4096, 4096); //д����
        }
        else
            SPI_W25X_Write_NoCheck(pBuffer, WriteAddr, secremain); //�Ѿ�����,ֱ��д��ʣ������

        if (NumByteToWrite == secremain)
            break; //д�����
        else       //д��δ��
        {
            secpos++;   //������ַ��1
            secoff = 0; //ƫ��λ��Ϊ0

            pBuffer += secremain;
            WriteAddr += secremain;
            NumByteToWrite -= secremain;

            if (NumByteToWrite > 4096)
                secremain = 4096; //��һ�����Բ���
            else
                secremain = NumByteToWrite; //��һ��������д��
        }
    }
}
//-----------------------------------------------------------------------------
//��������оƬ
//��Ƭ����ʱ��:
//W25X16:25s
//W25X32:40s
//W25X64:40s
//�ȴ�ʱ�䳬��...
void SPI_W25X_Erase_Chip(void)
{
    SPI_W25X_Write_Enable(); //SET WEL
    SPI_W25X_Wait_Busy();
    W25XCS_L;                           //ʹ��Ƭѡ
    SPI_ReadWriteByte(W25X_ChipErase); //����Ƭ��������
    W25XCS_H;                           //�ر�Ƭѡ
    SPI_W25X_Wait_Busy();               //�ȴ�оƬ��������
}
//-----------------------------------------------------------------------------
//����һ������
//Dst_Addr:������ַ 0~511 for w25x16
//����һ��ɽ��������ʱ��:150ms
void SPI_W25X_Erase_Sector(uint32_t Dst_Addr)
{
    Dst_Addr *= 4096;
    SPI_W25X_Write_Enable(); //SET WEL
    SPI_W25X_Wait_Busy();
    W25XCS_L;                                        //ʹ��Ƭѡ
    SPI_ReadWriteByte(W25X_SectorErase);            //������������ָ��
    SPI_ReadWriteByte((uint8_t)((Dst_Addr) >> 16)); //����24bit��ַ
    SPI_ReadWriteByte((uint8_t)((Dst_Addr) >> 8));
    SPI_ReadWriteByte((uint8_t)Dst_Addr);
    W25XCS_H;             //�ر�Ƭѡ
    SPI_W25X_Wait_Busy(); //�ȴ��������
}
//-----------------------------------------------------------------------------
//�ȴ�����
void SPI_W25X_Wait_Busy(void)
{
    while ((SPI_W25X_ReadSR() & 0x01) == 0x01)
        ; // �ȴ�BUSYλ���
}
//-----------------------------------------------------------------------------
//�������ģʽ
void SPI_W25X_PowerDown(void)
{
    W25XCS_L;                           //ʹ��Ƭѡ
    SPI_ReadWriteByte(W25X_PowerDown); //���͵�������
    W25XCS_H;                           //�ر�Ƭѡ
    HAL_Delay(3);                       //�ȴ�TPD
}
//-----------------------------------------------------------------------------
//����
void SPI_W25X_WAKEUP(void)
{
    W25XCS_L;                                  //ʹ��Ƭѡ
    SPI_ReadWriteByte(W25X_ReleasePowerDown); //  send W25X_PowerDown command 0xAB
    W25XCS_H;                                  //�ر�Ƭѡ
    HAL_Delay(3);                              //�ȴ�TRES1
}
