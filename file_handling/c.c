#include<stdio.h>
#include<arpa/inet.h>



int main(){
    int sock_fd = socket(AF_INET,SOCK_STREAM,0);

    FILE *ptr;
    ptr =fopen("ex1.txt","w");

    struct sockaddr_in addr;

    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock_fd,(struct sockaddr*)&addr,sizeof(addr));

    int mat[3][3];

        char response[100] = {0};
        send(sock_fd,"ex.txt",7,0);
        recv(sock_fd,mat,sizeof(mat),0);

        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                printf("%d ",mat[i][j]);
                fprintf(ptr,"%d ",mat[i][j]);
            }
            fprintf(ptr,"\n");
            printf("\n");
        }

        printf("Response: %s",response);
    
}