#include <winsock2.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<fstream>
#include<iostream>

using namespace std;
#pragma comment(lib, "Ws2_32.lib")

int sockfd = 0;
int main(void)
{
    int recvBytes = 0;
    char recvBuff[256];
    memset(recvBuff, '0', sizeof(recvBuff));
    struct sockaddr_in serv_addr;
     WSADATA wsaData;
    int sockfd;

    if (WSAStartup(MAKEWORD(1,1), &wsaData) == SOCKET_ERROR) {
        printf ("Error initialising WSA.\n");
        return -1;
    }

    sockfd= socket(AF_INET, SOCK_STREAM, 0);
    
   if(sockfd < 0)
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(55556); 
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0)
    {
        printf("\n Error : Connect Failed \n");
        return 1;
    }

    FILE *fp;
    fp = fopen("client.txt","ab"); 
    if(NULL == fp)
    {
        printf("Error opening file");
        return 1;
    }

    //cout<<recvBuff;
    /* Receive 512 bytes */
    while((recvBytes = recv(sockfd, recvBuff, 512,0)) > 0)
    {
        printf("Bytes received %d\n",recvBytes);    
        fwrite(recvBuff, 1,recvBytes,fp);
    }

    getchar();

    if(recvBytes < 0)
    {
        printf("\n Read Error \n");
    }

}