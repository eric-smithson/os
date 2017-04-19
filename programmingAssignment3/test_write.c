/**
 * @file   testebbchar.c
 * @author Derek Molloy
 * @date   7 April 2015
 * @version 0.1
 * @brief  A Linux user space program that communicates with the ebbchar.c LKM. It passes a
 * string to the LKM and reads the response from the LKM. For this example to work the device
 * must be called /dev/ebbchar.
 * @see http://www.derekmolloy.ie/ for a full description and follow-up descriptions.
*/
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>

#define BUFFER_LENGTH 1024               ///< The buffer length (crude but fine)
static unsigned char receive[BUFFER_LENGTH];     ///< The receive buffer from the LKM

int main(){
   int ret, fdRead,fdWrite;
   char stringToSend[BUFFER_LENGTH];
   printf("Starting device test code example...\n");
   fdRead = open("/dev/grp42read", O_RDWR);             // Open the device with read/write access
   fdWrite = open("/dev/grp42write", O_RDWR);             // Open the device with read/write access

   if (fdWrite < 0 || fdRead <0){
      perror("Failed to open the device...");
      return errno;
   }
   printf("Type in a string to send to the kernel module:\n");
   scanf("%[^\n]%*c", stringToSend);                // Read in a string (with spaces)
   printf("Writing message to the device [%s].\n", stringToSend);
   ret = write(fdWrite, stringToSend, strlen(stringToSend)); // Send the string to the LKM
   if (ret < 0){
      perror("Failed to write the message to the device.");
      return errno;
   }

   // printf("Press ENTER to read back from the device...\n");
   // getchar();
// 
   // printf("Reading from the device...\n");
   // ret = read(fdRead, receive, 5);        // Read the response from the LKM
   // if (ret < 0){
      // perror("Failed to read the message from the device.");
      // return errno;
   // }
   // printf("The received message is: [%s]\n", receive);
   printf("End of write program\n");
   return 0;
}

