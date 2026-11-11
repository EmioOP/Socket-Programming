#include<stdio.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
int main(){
    int server_fd = socket(AF_INET,SOCK_STREAM,0);

    struct sockaddr_in server_addr,client_addr;
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind(server_fd,(struct sockaddr*)&server_addr,sizeof(server_addr));

    listen(server_fd,20);

    int len = sizeof(client_addr);

    while(1){
    int client_fd = accept(server_fd,(struct sockaddr*)&server_addr,&len);

    while (1)
    {
        char msg[100] = {0};
        recv(client_fd,msg,sizeof(msg),0);
        if(strcmp(msg,"stop") == 0){
            send(client_fd,"Client Disconected.",20,0);
            close(client_fd);
            break;
        }
        printf("Client -> %s\n",msg);
        memset(msg,0,100);
        printf("Enter Your message: ");
        scanf("%s",&msg);

        send(client_fd,msg,sizeof(msg),0);
    }

    close(client_fd);
    }
    
    close(server_fd);

    return 0;

}