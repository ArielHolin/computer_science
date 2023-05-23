/*******************************************************************************
 * C Program for Message Queue (Reader Process)                                *
 * ipc_mqr1.c                                                                  *
 * Author: Ariel                                                               *
 * Reviewer:                                                                   *
 * ****************************************************************************/
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
  
// structure for message queue
struct msg_buffer
{
    long mesg_type;
    char mesg_text[100];
}msg_buffer;
  
int main(void)
{
    key_t key;
    int msgid;
  
    // ftok to generate unique key
    key = ftok("progfile", 65);
  
    // msgget creates a message queue
    // and returns identifier
    msgid = msgget(key, 0666 | IPC_CREAT);
  
    // msgrcv to receive message
    msgrcv(msgid, &msg_buffer, sizeof(msg_buffer), 1, 0);
  
    // display the message
    printf("Data Received is : %s \n", msg_buffer.mesg_text);
  
    printf("Reader process 1 terminated...\n");
  
    return 0;
}