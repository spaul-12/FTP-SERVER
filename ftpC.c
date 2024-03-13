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
#define CLIENT_CONTROL_PORT 55000
#define SERVER_CONTROL_PORT 50000
#define MAX 81


void checkStatusCode(char *response,int clientC_FD)
{
    int code = atoi(response);

    switch(code){

        case 200:
        {
            printf("\nsuccessful\n");
            break;
        }
        case 503:
        {
            printf("\ninvalid server request\n");
            close(clientC_FD);
            exit(0);
        }
        case 550:
        {
            printf("\ninvalid port specified\n");
            close(clientC_FD);
            exit(0);
        }

    }
    return ;
}

void handleClientConnection(int clientC_FD)
{
    char buffer[MAX];
    char response[MAX];

    bzero(buffer,MAX);
    sprintf(buffer,"%d",CLIENT_CONTROL_PORT);

    //send port Y to server
    write(clientC_FD,buffer,sizeof(buffer));
    bzero(response,MAX);
    
    recv(clientC_FD,response,sizeof(response),0);
    checkStatusCode(response,clientC_FD);

    // options for the client
    while(1)
    {
        bool flag = false;
        int ch;
        printf(" 1. To change server directory\n 2. get file from server \n 3. send file to server\n 4. quit\n");
        scanf("%d",&ch);
        bzero(buffer,MAX);
        switch(ch)
        {
            case 1:
            {
                break;
            }
            case 2:
            {
                break;
            }
            case 3:
            {
                break;
            }
            case 4:
            {
                flag = true;
                break;
            }
        }
        if(flag)
        break;
    }
    close(clientC_FD);
}

int main()
{
    int clientC_FD;
    struct sockaddr_in server_addr;

    clientC_FD = socket(AF_INET,SOCK_STREAM,0);

    if(clientC_FD<0)
    {
        printf("failed to create client socket\n");
        exit(0);
    }

    bzero(&server_addr,sizeof(server_addr));


    //assign server ip and port
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(SERVER_CONTROL_PORT);

    // connect client with server
    if(connect(clientC_FD,(struct sockaddr *)&server_addr,sizeof(server_addr))<0)
    {
        printf("error connecting with server...\n");
        exit(0);
    }
    else
    printf("connected with server..\n");

    handleClientConnection(clientC_FD);

}