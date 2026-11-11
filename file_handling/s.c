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

    listen(server_fd,15);

    int len = sizeof(client_addr);

    while (1)
    {
        int client_fd = accept(server_fd,(struct sockaddr*)&server_addr,&len);
        char filename[50]={0};

        recv(client_fd,filename,sizeof(filename),0);
        
        FILE *ptr = fopen(filename,"r");

        // char line[100];
        // char content[256] = {0};
        // while(fgets(line,sizeof(line),ptr) != NULL){
        //     strcat(content,line);
        // } -----> this is to read multi line strings


        int mat[3][3];
        int row,col;
        fscanf(ptr,"%d %d",&row,&col);

        printf("%d %d\n",row,col);

        for(int i=0;i<row;i++){
            for(int j=0;j<col;j++){
                fscanf(ptr,"%d ",&mat[i][j]);
                printf("%d ",mat[i][j]);
            }
            printf("\n");
        }

        fclose(ptr);

        send(client_fd,mat,sizeof(mat),0);

        close(client_fd);

    }
    close(server_fd);
    return 0;

}