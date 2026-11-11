#include<stdio.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

int main(){
    int sock_fd = socket(AF_INET,SOCK_STREAM,0);

    struct sockaddr_in addr;

    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock_fd,(struct sockaddr*)&addr,sizeof(addr));

    while (1)
    {
        char msg[100] = {0};
        printf("Enter Your message: ");
        scanf("%s",&msg);
        if(strcmp(msg,"stop") == 0){
            send(sock_fd,msg,sizeof(msg),0);
            recv(sock_fd,msg,sizeof(msg),0);
            printf("%s\n",msg);
            break;
        }
        send(sock_fd,msg,sizeof(msg),0);
        memset(msg,0,100);
        recv(sock_fd,msg,sizeof(msg),0);
        printf("Server -> %s\n",msg);
    }

    close(sock_fd);
    
}