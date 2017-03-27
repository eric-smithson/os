#include <linux/init.h>           
#include <linux/module.h>         
#include <linux/device.h>         
#include <linux/kernel.h>         
#include <linux/fs.h>             
#include <asm/uaccess.h>   
#include <linux/slab.h> 
#define  DEVICE_NAME "grp42"    ///< The device will appear at /dev/grp42 using this value
#define  CLASS_NAME  "grp42"       
#define  BUFFERSIZE 1024
MODULE_LICENSE("GPL");            
MODULE_AUTHOR("Group 42");    
MODULE_DESCRIPTION("Assignment 2");  
MODULE_VERSION("0.1");            

static int    majorNumber;                  ///< Stores the device number -- determined automatically
// static char   message[1024] = {0};           ///< Memory for the string that is passed from userspace
static short  size_of_message;              ///< Used to remember the size of the string stored
static int    numberOpens = 0;              ///< Counts the number of times the device is opened
static struct class*  ebbcharClass  = NULL; ///< The device-driver class struct pointer
static struct device* ebbcharDevice = NULL; ///< The device-driver device struct pointer
static int    size_of_buffer = 0;

typedef struct node
{
   unsigned char name;
   struct node* nextNode;
}g42Node;

g42Node* rear;
//node* temp;
g42Node* front;

// The prototype functions for the character driver -- must come before the struct definition
static int     dev_open(struct inode *, struct file *);
static int     dev_release(struct inode *, struct file *);
static ssize_t dev_read(struct file *, char *, size_t, loff_t *);
static ssize_t dev_write(struct file *, const char *, size_t, loff_t *);
static int enqueue(unsigned char name);
static unsigned char dequeue(void);
static int isEmpty(void);

/** @brief Devices are represented as file structure in the kernel. The file_operations structure from
 *  /linux/fs.h lists the callback functions that you wish to associated with your file operations
 *  using a C99 syntax structure. char devices usually implement open, read, write and release calls
 */
static struct file_operations fops =
{
   .open = dev_open,
   .read = dev_read,
   .write = dev_write,
   .release = dev_release,
};





int enqueue(unsigned char name)
{
	if( size_of_buffer < BUFFERSIZE)
	{ 
		g42Node *temp = kmalloc(sizeof(g42Node),GFP_KERNEL);

	  //temp.name = malloc(sizeof(process.name));
	  temp->name = name;
	  //temp->arrival = process->arrival;
	  //temp->burst = process->burst;
	  //process->nextNode = NULL;
	  if(front == NULL && rear == NULL)
	  {
		front = rear = temp;
		return 0;
	  }

		rear->nextNode = temp;
		rear = temp;
		size_of_buffer++;
	}
	else
	{
		printk(KERN_INFO "buffer is full");
		return -1;
	}


	return 0;
}

unsigned char dequeue()
{
	unsigned char value;
	g42Node* temp = front;
	if(temp == NULL)
	{
		//fprintf(fpr,"Queue is empty\n");
		return '\0';
	}
	else
	{
		value = temp->name;
		if(temp->nextNode == NULL)
		{
			//free(front->name);
			kfree(front);

			front = rear = NULL;

		}
		else
		{

			temp = temp->nextNode;
			front->nextNode = NULL;
			//free(front->name);
			kfree(front);
			front = temp;
			//fprintf(fpr,"sucessful dequeue\n");

		}
	}
	

	size_of_buffer--;
	return value;

}
int isEmpty()
{
	if(front == NULL)
	{
		printk(KERN_INFO "THERE ARE NO MORE DATA");

		return 1;
	}
	else return 0;
}


/** @brief The LKM initialization function
 *  The static keyword restricts the visibility of the function to within this C file. The __init
 *  macro means that for a built-in driver (not a LKM) the function is only used at initialization
 *  time and that it can be discarded and its memory freed up after that point.
 *  @return returns 0 if successful
 */
static int __init ebbchar_init(void){
   printk(KERN_INFO "group42: Initializing the group42 LKM\n");

   // Try to dynamically allocate a major number for the device -- more difficult but worth it
   majorNumber = register_chrdev(0, DEVICE_NAME, &fops);
   if (majorNumber<0){
      printk(KERN_ALERT "group42 failed to register a major number\n");
      return majorNumber;
   }
   // printk(KERN_INFO "group42: registered correctly with major number %d\n", majorNumber);

   // Register the device class
   ebbcharClass = class_create(THIS_MODULE, CLASS_NAME);
   if (IS_ERR(ebbcharClass)){                // Check for error and clean up if there is
      unregister_chrdev(majorNumber, DEVICE_NAME);
      printk(KERN_ALERT "Failed to register device class\n");
      return PTR_ERR(ebbcharClass);          // Correct way to return an error on a pointer
   }
   printk(KERN_INFO "group42: device class registered correctly with major number :%d\n",majorNumber);

   // Register the device driver
   ebbcharDevice = device_create(ebbcharClass, NULL, MKDEV(majorNumber, 0), NULL, DEVICE_NAME);
   if (IS_ERR(ebbcharDevice)){               // Clean up if there is an error
      class_destroy(ebbcharClass);           // Repeated code but the alternative is goto statements
      unregister_chrdev(majorNumber, DEVICE_NAME);
      printk(KERN_ALERT "Failed to create the device\n");
      return PTR_ERR(ebbcharDevice);
   }
   front = rear = NULL;

   printk(KERN_INFO "initialzed group42 driver\n"); // Made it! device was initialized
   return 0;
}

/** @brief The LKM cleanup function
 *  Similar to the initialization function, it is static. The __exit macro notifies that if this
 *  code is used for a built-in driver (not a LKM) that this function is not required.
 */
static void __exit ebbchar_exit(void){
   device_destroy(ebbcharClass, MKDEV(majorNumber, 0));     // remove the device
   class_unregister(ebbcharClass);                          // unregister the device class
   class_destroy(ebbcharClass);                             // remove the device class
   unregister_chrdev(majorNumber, DEVICE_NAME);             // unregister the major number
   //printk(KERN_INFO "deinitialized group42 driver\n");
}

/** @brief The device open function that is called each time the device is opened
 *  This will only increment the numberOpens counter in this case.
 *  @param inodep A pointer to an inode object (defined in linux/fs.h)
 *  @param filep A pointer to a file object (defined in linux/fs.h)
 */
static int dev_open(struct inode *inodep, struct file *filep){
   numberOpens++;
   printk(KERN_INFO "Group42: Character device has been opened\n");
   return 0;
}

/** @brief This function is called whenever device is being read from user space i.e. data is
 *  being sent from the device to the user. In this case is uses the copy_to_user() function to
 *  send the buffer string to the user and captures any errors.
 *  @param filep A pointer to a file object (defined in linux/fs.h)
 *  @param buffer The pointer to the buffer to which this function writes the data
 *  @param len The length of the b
 *  @param offset The offset if required
 */
static ssize_t dev_read(struct file *filep, char *buffer, size_t len, loff_t *offset){
   int error_count = 0;
   int i;
   int size;
   if(BUFFERSIZE - size_of_buffer > len)
   {
   		size = len +1;
   }
   else
   {
   		size = BUFFERSIZE - size_of_buffer +1;
   		printk(KERN_INFO "Group42: Not enough data in buffer there is only %d byte in buffer \n",size_of_buffer);
   		return 0;

   }
   unsigned char string[size];
   for(i = 0; i < size;i++)
   {
   	  if(!isEmpty())
      	string[i] = dequeue();
   }
   	string[--i] = '\0';

   // copy_to_user has the format ( * to, *from, size) and returns 0 on success
   error_count = copy_to_user(buffer, string, size);


   if (error_count==0){            // if true then have success
      printk(KERN_INFO "Group42: Character device is read\n");
      return (size_of_message=0);  // clear the position to the start and return 0
   }
   else {
      printk(KERN_INFO "Group42: Character device failed to read\n");
      return -EFAULT;              // Failed -- return a bad address message (i.e. -14)
   }
}

/** @brief This function is called whenever the device is being written to from user space i.e.
 *  data is sent to the device from the user. The data is copied to the message[] array in this
 *  LKM using the sprintf() function along with the length of the string.
 *  @param filep A pointer to a file object
 *  @param buffer The buffer to that contains the string to write to the device
 *  @param len The length of the array of data that is being passed in the const char buffer
 *  @param offset The offset if required
 */
static ssize_t dev_write(struct file *filep, const char *buffer, size_t len, loff_t *offset)
{
	int i;
	for (i=0;i<len;i++)
	{
		if(enqueue(*(buffer+i)) != 0)
			break;
		
	}

   //sprintf(message, "%s(%zu letters)", buffer, len);   // appending received string with its length
   //size_of_message = strlen(message);                 // store the length of the stored message
   printk(KERN_INFO "Group42: Character device successfully written\n");

   return i;
}

/** @brief The device release function that is called whenever the device is closed/released by
 *  the userspace program
 *  @param inodep A pointer to an inode object (defined in linux/fs.h)
 *  @param filep A pointer to a file object (defined in linux/fs.h)
 */
static int dev_release(struct inode *inodep, struct file *filep){
   printk(KERN_INFO "Group42: Device successfully closed\n");
   return 0;
}

/** @brief A module must use the module_init() module_exit() macros from linux/init.h, which
 *  identify the initialization function at insertion time and the cleanup function (as
 *  listed above)
 */
module_init(ebbchar_init);
module_exit(ebbchar_exit);
