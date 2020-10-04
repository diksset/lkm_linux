#include <linux/kernel.h> /* Для printk() и т.д. */
#include <linux/module.h> 
#include <linux/init.h> /* Определения макросов */
#include <linux/fs.h>
//#include <asm/uaccess.h> /* put_user */

// Ниже мы задаём информацию о модуле, которую можно будет увидеть с помощью Modinfo
MODULE_LICENSE( "GPL" );
MODULE_AUTHOR( "Ivan Petrov" );
MODULE_DESCRIPTION( "just a dummy" );
MODULE_SUPPORTED_DEVICE( "my_dummy_device" );

#define SUCCESS 0
#define DEVICE_NAME "my_dummy_device" /* Имя нашего устройства */

// Поддерживаемые нашим устройством операции
static int device_open( struct inode *, struct file * );
static int device_release( struct inode *, struct file * );

// Глобальные переменные, объявлены как static, воизбежание конфликтов имен.
static int major_number; /* Старший номер устройства нашего драйвера */
static int is_device_open = 0; /* Используется ли девайс ? */

// Прописываем обработчики операций на устройством
static struct file_operations fops =
 {
  .open = device_open,
  .release = device_release
 };

// Функция загрузки модуля. Входная точка. Можем считать что это наш main()
static int __init dummy_init( void )
{
 printk( KERN_ALERT "Hello, World!\n" );

 // Регистрируем устройсво и получаем старший номер устройства
 major_number = register_chrdev( 0, DEVICE_NAME, &fops );

 if ( major_number < 0 )
 {
  printk( "Registering the character device failed with %d\n", major_number );
  return major_number;
 }

 // Сообщаем присвоенный нам старший номер устройства
 printk( "Module is loaded with number %d\n", major_number );

 return SUCCESS;
}

// Функция выгрузки модуля
static void __exit dummy_exit( void )
{
 // Освобождаем устройство
 unregister_chrdev( major_number, DEVICE_NAME );
 printk( "Module is unloaded!\n" );


 printk( KERN_ALERT "Goodbye, World!\n" );
}

// Указываем наши функции загрузки и выгрузки
module_init( dummy_init );
module_exit( dummy_exit );

static int device_open( struct inode *inode, struct file *file )
{
 if ( is_device_open )
  return -EBUSY;

 is_device_open++;

 return SUCCESS;
}

static int device_release( struct inode *inode, struct file *file )
{
 is_device_open--;
 return SUCCESS;
}