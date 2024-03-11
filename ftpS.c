// Name: Subrajit Paul
// Roll: 21CS8113

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/sendfile.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <arpa/inet.h>

#include <dirent.h>
#include <stdio.h>
#define SERVER_CONTROL_PORT 50000
#define MAX 81


bool isDigit(char num)
{
    return (num>='0' && num<='9');
}

// function to verify port of the client
int verifyPort(char* buffer)
{
    int len = sizeof(buffer);
    int port = 0;
    for(int i=0;i<len;i++)
    {
        if(!isDigit(buffer[i]))
        {
            return 503;  // invalid client response
        }
        port = port*10+(buffer[i]-'0');
    }
    
    if(port >= 1024 && port <= 65535)
    return 200;
    else 
    return 550;        // port invalid
}

// control socket functionality
void handleConnection(int clientC_FD)
{
    char buffer[MAX],server_response;
    bzero(buffer,MAX);
    bzero(server_response,MAX);

    //receive port Y from client
    recv(clientC_FD,buffer,sizeof(buffer),0);

    int code = verifyPort(buffer);
    sprintf(server_response,"%d",code);

    //send code 
    write(clientC_FD,server_response,sizeof(server_response));

    while(1)
    {
        bzero(buffer,MAX);
        recv(clientC_FD,buffer,sizeof(buffer),0);
        if( buffer[0]=='c' && buffer[1]=='d')
        {

        }
        else if(buffer[0]=='g' && buffer[1]=='e' && buffer[2]=='t')
        {
            
        }
        else if( buffer[0]=='p' && buffer[1]=='u' && buffer[2]=='t')
        {

        }
        else if( buffer[0]=='q' && buffer[1]=='u' && buffer[2]=='i' && buffer[3]=='t')
        {
            bzero(server_response,MAX);
            strcat(server_response,"421");
            
            write(clientC_FD,server_response,sizeof(server_response));
            break;
        }
        else
        {
            bzero(server_response,MAX);
            strcat(server_response,"502");       // invalid request

            write(clientC_FD,server_response,sizeof(server_response));
        }
    }
    close(clientC_FD);
    return ;
}

int main()
{
    int sockC_FD, clientC_FD, len;
    struct sockaddr_in server_addr, client_addr;

    // socket creation
    sockC_FD = socket(AF_INET, SOCK_STREAM, 0);
    if (sockC_FD < 0)
    {
        printf("socket creation failed..\n");
        exit(0);
    }

    // allowing reuse of address and port
    if (setsockopt(sockC_FD, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) < 0)
        perror("setsockopt(SO_REUSEADDR) failed");

    bzero(&server_addr, sizeof(server_addr));

    // assigning ip and port
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(SERVER_CONTROL_PORT);

    // binding socket to ip
    if ((bind(sockC_FD, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0))
    {
        printf("Bind failed");
        exit(0);
    }

    // listen for connections
    if (listen(sockC_FD, 10))
    {
        printf("Listening error..");
        exit(0);
    }
    printf("server listening... \n");

    len = sizeof(clientC_FD);
    while(clientC_FD = accept(sockC_FD, (struct socketaddr *)&clientC_FD, &len))
    {
        handleConnection(clientC_FD);
    }

    if(clientC_FD<0)
    {
        printf("Error accepting client connection\n");
        exit(0);
    }

}