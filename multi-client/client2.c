#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<unistd.h>

int main(){


    int server_fd = socket(AF_INET,SOCK_STREAM,0);

    struct sockaddr_in server_addr;
    // int len = sizeof(client_addr);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    connect(server_fd,(struct sockaddr*)&server_addr,sizeof(server_addr));

    char buf[100] = {0};
    // int n = 154;
    // send(server_fd,&n,sizeof(int),0);
    recv(server_fd,buf,sizeof(buf),0);
    
    printf("%s",buf);
    close(server_fd);
}