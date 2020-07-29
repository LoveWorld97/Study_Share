/*ʹ��˵������доƬ�ڲ�flash--stm32cubemx-hal��
    1��ʹ��stm32cubemx���úͽ����Լ��Ĺ����ļ�
    2�����user_flash.h��user_flash.c�ļ���������
    3������Ҫʹ�õĵط�include "user_flash.h"ͷ�ļ�
    4��ֱ�ӵ������º���
        void flash_write(uint32_t add, uint8_t data)
        //���ܣ�flashд��һ���ֽ�
        //������add-д��ĵ�ַ��data-д�������
        //���أ�void
        ----------------------------------------------
        uint8_t flash_read(uint32_t add)
        //���ܣ�flash����һ���ֽ�
        //������add-��ȡ�ĵ�ַ
        //���أ�temp-��ȡ���ֽ�
        ----------------------------------------------
        void flash_read_buf(uint32_t add, uint8_t *data, uint8_t len)
        //���ܣ�flashд��һ�����������
        //������add-д�����ݵ���ʼ��ַ��data-д����������len-д�����ݳ���
        //���أ�void
        ----------------------------------------------
        void flash_write_buf(uint32_t add,uint8_t *data,uint8_t len)
        //���ܣ�flash����һ�����������
        //������add-��ȡ���ݵ���ʼ��ַ��data-�������ݴ����������len-��ȡ���ݳ���
        //���أ�void
*/
#include "user_flash.h"
/*
void flash_write(uint32_t add, uint8_t data)
//���ܣ�flashд��һ���ֽ�
//������add-д��ĵ�ַ��data-д�������
//���أ�void
*/
void flash_write(uint32_t add, uint8_t data)
{
    FLASH_EraseInitTypeDef My_Flash;            //���� FLASH_EraseInitTypeDef �ṹ��Ϊ My_Flash
    HAL_FLASH_Unlock();                         //����Flash

    My_Flash.TypeErase = FLASH_TYPEERASE_PAGES; //����Flashִ��ҳ��ֻ����������
    My_Flash.PageAddress = add;                 //����Ҫ�����ĵ�ַ
    My_Flash.NbPages = 1;                       //˵��Ҫ������ҳ�����˲���������Min_Data = 1��Max_Data =(���ҳ��-��ʼҳ��ֵ)֮���ֵ

    uint32_t PageError = 0;                     //����PageError,������ִ�����������ᱻ����Ϊ�����FLASH��ַ
    HAL_FLASHEx_Erase(&My_Flash, &PageError);   //���ò�����������

    uint16_t Write_Flash_Data = data;
    /*��Flash������д��FLASH_TYPEPROGRAM_HALFWORD ����������Flash��ַ��16λ�ģ����⻹��32λ��64λ�Ĳ��������з���HAL��Ķ��弴��*/
    HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, add, Write_Flash_Data);
    HAL_FLASH_Lock();                           //��סFlash
}
/*
uint8_t flash_read(uint32_t add)
//���ܣ�flash����һ���ֽ�
//������add-��ȡ�ĵ�ַ
//���أ�temp-��ȡ���ֽ�
*/
uint8_t flash_read(uint32_t add)
{
    uint8_t temp;
    temp = *(__IO uint8_t *)(add);
    return temp;
}
/*
void flash_read_buf(uint32_t add, uint8_t *data, uint8_t len)
//���ܣ�flashд��һ�����������
//������add-д�����ݵ���ʼ��ַ��data-д����������len-д�����ݳ���
//���أ�void
*/
void flash_read_buf(uint32_t add, uint8_t *data, uint8_t len)
{
    uint8_t i = 0;
    for (i = 0; i < len; i++)
    {
        data[i] = *(__IO uint8_t *)(add + i * BYTE_SIZE);
    }
}
/*
void flash_write_buf(uint32_t add,uint8_t *data,uint8_t len)
//���ܣ�flash����һ�����������
//������add-��ȡ���ݵ���ʼ��ַ��data-�������ݴ����������len-��ȡ���ݳ���
//���أ�void
*/
void flash_write_buf(uint32_t add, uint8_t *data, uint8_t len)
{
    uint8_t i = 0;
    FLASH_EraseInitTypeDef My_Flash;            //���� FLASH_EraseInitTypeDef �ṹ��Ϊ My_Flash
    HAL_FLASH_Unlock();                         //����Flash

    My_Flash.TypeErase = FLASH_TYPEERASE_PAGES; //����Flashִ��ҳ��ֻ����������
    My_Flash.PageAddress = add;                 //����Ҫ�����ĵ�ַ
    My_Flash.NbPages = 1;                       //˵��Ҫ������ҳ�����˲���������Min_Data = 1��Max_Data =(���ҳ��-��ʼҳ��ֵ)֮���ֵ

    uint32_t PageError = 0;                     //����PageError,������ִ�����������ᱻ����Ϊ�����FLASH��ַ
    HAL_FLASHEx_Erase(&My_Flash, &PageError);   //���ò�����������

    for (i = 0; i < len; i++)
    {
        /*��Flash������д��FLASH_TYPEPROGRAM_HALFWORD ����������Flash��ַ��16λ�ģ����⻹��32λ��64λ�Ĳ��������з���HAL��Ķ��弴��*/
        HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, (add + i * BYTE_SIZE), data[i]);
    }

    HAL_FLASH_Lock();                           //��סFlash
}