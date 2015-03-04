#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include<fstream>
#include<iostream>
using namespace std;

#pragma comment(lib,"ws2_32.lib")
int Listen = 0;

int main(void)
{
    
    int connfd = 0;
    struct sockaddr_in servAddr;
    char buffer[1025];
    //int num;

    WSADATA wsaData;
    int Listen;

    if (WSAStartup(MAKEWORD(1,1), &wsaData) == SOCKET_ERROR) {
        printf ("Error in  initialising WSA.\n");
        return -1;
    }

    Listen = socket(AF_INET, SOCK_STREAM, 0);
    
    printf("Socket Created\n"); 

    memset(&servAddr, '0', sizeof(servAddr));
    memset(buffer, '0', sizeof(buffer));

    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(55556);

    bind(Listen, (struct sockaddr*)&servAddr,sizeof(servAddr));

    listen(Listen,1);
    FILE *fp = fopen("server.txt","rb");
    if(fp==NULL)
        {
            printf("Error Opening file");
            return 1;   
        }   
        char * buff=new char [512];
            int nread = fread(buff,1,512,fp);
            printf("Bytes read %d \n", nread);

    while(1)
    {
        connfd = accept(Listen, (struct sockaddr*)NULL ,NULL);

        FILE *fp = fopen("server.txt","rb");
        if(fp==NULL)
        {
            printf("Error Opening file");
            return 1;   
        }   
        char * buff=new char [512];
            int nread = fread(buff,1,512,fp);
          //  printf("Bytes ead %d \n", nread);
        while(1)
        {
            /*Read 512 bytes */
            char * buff=new char [512];
            int nread = fread(buff,1,512,fp);
            printf("Bytes read %d \n", nread);        

            if(nread > 0)
            {
                printf("Sending \n");
                send(connfd, buff, nread,0);
            }
            else
                printf("Could'nt read from File!");

            if (nread < 512)
            {
                if (feof(fp))
                    printf("End of file\n");
                if (ferror(fp))
                    printf("Error reading\n");
                break;
            }
        }
        shutdown(Listen,SD_SEND);
        //sleep(1);
        getchar();
    }
    return 0;
}