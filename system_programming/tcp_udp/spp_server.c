/*******************************************************************************
 * spp_server.c - Server Functions for Ping Pong                               *
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

int UdpServer(void);
int TcpServer(void);
int UdpBroadcastServer(void);

int main(void)
{
    UdpServer();
    TcpServer();
    UdpBroadcastServer();
    return 0;
}

int UdpServer(void)
{
    int sockfd;
    char buffer[MAXLINE];
    char *pong = "pong...";
    struct sockaddr_in servaddr, cliaddr;
    size_t counter = 0;

    // Creating socket file descriptor
    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) 
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
       
    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));
       
    // Filling server information
    servaddr.sin_family = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);
       
    // Bind the socket with the server address
    if(bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
       
    int len, n;
   
    len = sizeof(cliaddr);  //len is value/resuslt
   
    while(counter < ITERATIONS)
    {
        n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, 
                 (struct sockaddr *)&cliaddr, &len);
        buffer[n] = '\0';
        printf("Client : %s\n", buffer);
        memset(buffer, 0, MAXLINE);
        sleep(1);
        sendto(sockfd, (const char *)pong, strlen(pong), MSG_CONFIRM, 
               (const struct sockaddr *)&cliaddr, len);
    
        ++counter;
    }
       
    return 0;
}

int TcpServer(void)
{
    int sockfd, connfd, len;
    char buffer[MAXLINE];
    char *pong = "pong...";
    struct sockaddr_in servaddr, cli;
    size_t counter = 0;
   
    // socket create and verification
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
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);
   
    // Binding newly created socket to given IP and verification
    if((bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr))) < 0) 
    {
        printf("socket bind failed...\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("Socket successfully binded..\n");
    }
   
    // Now server is ready to listen and verification
    if ((listen(sockfd, 5)) != 0) 
    {
        printf("Listen failed...\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("Server listening..\n");
    }
    len = sizeof(cli);
   
    // Accept the data packet from client and verification
    connfd = accept(sockfd, (struct sockaddr *)&cli, &len);
    if (connfd < 0) 
    {
        printf("server accept failed...\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("server accept the client...\n");
    }
   
    while(counter < ITERATIONS)
    {
        read(connfd, buffer, sizeof(buffer));
        printf("From Client: %s\n", buffer);
        memset(buffer, 0, MAXLINE);
        sleep(1);

        write(connfd, pong, sizeof(buffer));
        ++counter;
        sleep(1);
    }
   
    // After chatting close the socket
    close(sockfd);
    return 0;
}

int UdpBroadcastServer(void)
{
    int sockfd;
    struct sockaddr_in servaddr, cliaddr;
    int broadcast = '1';
    char *sendMSG ="Broadcasting Hello from ARIEL!";

    // Creating socket file descriptor
    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) 
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    if(setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &broadcast, 
                                                         sizeof(broadcast)) < 0)
    {
        perror("setsockopt");
        return EXIT_FAILURE;
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    cliaddr.sin_family = AF_INET;        
    cliaddr.sin_port = htons(PORT);   
    cliaddr.sin_addr.s_addr = inet_addr("10.100.102.255");

    sendto(sockfd, sendMSG, strlen(sendMSG) + 1, 0, (struct sockaddr *)&cliaddr, 
           sizeof(cliaddr));

    printf("Broadcast server terminated...\n");
    return 0;
}


