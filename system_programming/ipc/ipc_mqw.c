/*******************************************************************************
 * C Program for Message Queue (Writer Process)                                *
 * ipc_mqw.c                                                                   *
 * Author: Ariel                                                               *
 * Reviewer:                                                                   *
 * ****************************************************************************/
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stddef.h>

#define MAX 10
#define NUM_READ_PROC 3
  
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
    msg_buffer.mesg_type = 1;
  
    printf("Write Data : ");
    fgets(msg_buffer.mesg_text,MAX,stdin);
  
    // msgsnd to send message
    for(size_t i = 0; i < NUM_READ_PROC; ++i)
    {
        msgsnd(msgid, &msg_buffer, sizeof(msg_buffer), 0);
    }
  
    // display the message
    printf("Data send is : %s \n", msg_buffer.mesg_text);
  
    printf("Writing process terminated...\n");

    return 0;
}