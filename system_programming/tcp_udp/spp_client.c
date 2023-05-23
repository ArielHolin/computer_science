/*******************************************************************************
 * spp_clinet.c - Client Functions for Ping Pong                               *
 * Author: Ariel                                                               *
 * Reviewer:                                                                   *
 * ****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
   
#define PORT    8080
#define MAXLINE 1024
#define ITERATIONS 5

int UdpClient(void);
int TcpClient(void);
int UdpBroadcastClient(void);

int main(void)
{
    UdpClient();
    TcpClient();
    UdpBroadcastClient();
    return 0;
}

int UdpClient(void)
{
    int sockfd;
    char buffer[MAXLINE];
    char *ping = "ping...";
    struct sockaddr_in servaddr;
    size_t counter = 0;
   
    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) 
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
   
    memset(&servaddr, 0, sizeof(servaddr));
       
    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;
       
    int n, len;

    while(counter < ITERATIONS)   
    {
        sendto(sockfd, (const char *)ping, strlen(ping), MSG_CONFIRM, 
           (const struct sockaddr *) &servaddr, sizeof(servaddr));
           
        n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, 
                 (struct sockaddr *)&servaddr, &len);
        buffer[n] = '\0';
        printf("Server : %s\n", buffer);
        memset(buffer, 0, MAXLINE);
        sleep(1);
        ++counter;
    }
   
    close(sockfd);
    return 0;
}

int TcpClient(void)
{
    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;
    char buffer[MAXLINE];
    char *ping = "ping...";
    size_t counter = 0;
   
    // socket create and varification
    //sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    {
        perror("socket creation failed...\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("Socket successfully created..\n");
    }
    
    memset(&servaddr, 0, sizeof(servaddr));
   
    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);
   
    // connect the client socket to server socket
    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0) {
        printf("connection with the server failed...\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("connected to the server..\n");
    }
   
    while(counter < ITERATIONS)
    {
        write(sockfd, ping, strlen(ping) + 1);
        sleep(1);

        read(sockfd, buffer, sizeof(buffer));
        printf("From Server : %s\n", buffer);
        memset(buffer, 0, MAXLINE);
        sleep(1);
        ++counter;
    }
   
    // close the socket
    close(sockfd);
    return 0;
}

int UdpBroadcastClient(void)
{
    int sockfd, len;
    char buffer[MAXLINE];
    int broadcast = '1';
    struct sockaddr_in servaddr;

    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) 
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family = AF_INET;        
    servaddr.sin_port = htons(PORT);   
    servaddr.sin_addr.s_addr = INADDR_ANY;

    if(bind(sockfd,(struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("bind");
        return EXIT_FAILURE;
    }

    recvfrom(sockfd, buffer, MAXLINE, 0,(struct sockaddr *)&servaddr, &len);

 

    printf("Received Message is : %s\n", buffer);

    return 0;
}