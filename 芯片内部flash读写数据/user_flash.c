/*使用说明：读写芯片内部flash--stm32cubemx-hal库
    1、使用stm32cubemx配置和建立自己的工程文件
    2、添加user_flash.h和user_flash.c文件到工程中
    3、在需要使用的地方include "user_flash.h"头文件
    4、直接调用以下函数
        void flash_write(uint32_t add, uint8_t data)
        //功能：flash写入一个字节
        //参数：add-写入的地址；data-写入的数据
        //返回：void
        ----------------------------------------------
        uint8_t flash_read(uint32_t add)
        //功能：flash读出一个字节
        //参数：add-读取的地址
        //返回：temp-读取的字节
        ----------------------------------------------
        void flash_read_buf(uint32_t add, uint8_t *data, uint8_t len)
        //功能：flash写入一个数组的数据
        //参数：add-写入数据的起始地址；data-写入数组名；len-写入数据长度
        //返回：void
        ----------------------------------------------
        void flash_write_buf(uint32_t add,uint8_t *data,uint8_t len)
        //功能：flash读出一个数组的数据
        //参数：add-读取数据的起始地址；data-读出数据存放数组名；len-读取数据长度
        //返回：void
*/
#include "user_flash.h"
/*
void flash_write(uint32_t add, uint8_t data)
//功能：flash写入一个字节
//参数：add-写入的地址；data-写入的数据
//返回：void
*/
void flash_write(uint32_t add, uint8_t data)
{
    FLASH_EraseInitTypeDef My_Flash;            //声明 FLASH_EraseInitTypeDef 结构体为 My_Flash
    HAL_FLASH_Unlock();                         //解锁Flash

    My_Flash.TypeErase = FLASH_TYPEERASE_PAGES; //标明Flash执行页面只做擦除操作
    My_Flash.PageAddress = add;                 //声明要擦除的地址
    My_Flash.NbPages = 1;                       //说明要擦除的页数，此参数必须是Min_Data = 1和Max_Data =(最大页数-初始页的值)之间的值

    uint32_t PageError = 0;                     //设置PageError,如果出现错误这个变量会被设置为出错的FLASH地址
    HAL_FLASHEx_Erase(&My_Flash, &PageError);   //调用擦除函数擦除

    uint16_t Write_Flash_Data = data;
    /*对Flash进行烧写，FLASH_TYPEPROGRAM_HALFWORD 声明操作的Flash地址的16位的，此外还有32位跟64位的操作，自行翻查HAL库的定义即可*/
    HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, add, Write_Flash_Data);
    HAL_FLASH_Lock();                           //锁住Flash
}
/*
uint8_t flash_read(uint32_t add)
//功能：flash读出一个字节
//参数：add-读取的地址
//返回：temp-读取的字节
*/
uint8_t flash_read(uint32_t add)
{
    uint8_t temp;
    temp = *(__IO uint8_t *)(add);
    return temp;
}
/*
void flash_read_buf(uint32_t add, uint8_t *data, uint8_t len)
//功能：flash写入一个数组的数据
//参数：add-写入数据的起始地址；data-写入数组名；len-写入数据长度
//返回：void
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
//功能：flash读出一个数组的数据
//参数：add-读取数据的起始地址；data-读出数据存放数组名；len-读取数据长度
//返回：void
*/
void flash_write_buf(uint32_t add, uint8_t *data, uint8_t len)
{
    uint8_t i = 0;
    FLASH_EraseInitTypeDef My_Flash;            //声明 FLASH_EraseInitTypeDef 结构体为 My_Flash
    HAL_FLASH_Unlock();                         //解锁Flash

    My_Flash.TypeErase = FLASH_TYPEERASE_PAGES; //标明Flash执行页面只做擦除操作
    My_Flash.PageAddress = add;                 //声明要擦除的地址
    My_Flash.NbPages = 1;                       //说明要擦除的页数，此参数必须是Min_Data = 1和Max_Data =(最大页数-初始页的值)之间的值

    uint32_t PageError = 0;                     //设置PageError,如果出现错误这个变量会被设置为出错的FLASH地址
    HAL_FLASHEx_Erase(&My_Flash, &PageError);   //调用擦除函数擦除

    for (i = 0; i < len; i++)
    {
        /*对Flash进行烧写，FLASH_TYPEPROGRAM_HALFWORD 声明操作的Flash地址的16位的，此外还有32位跟64位的操作，自行翻查HAL库的定义即可*/
        HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, (add + i * BYTE_SIZE), data[i]);
    }

    HAL_FLASH_Lock();                           //锁住Flash
}