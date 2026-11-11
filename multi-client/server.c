#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<math.h>


int check_amstrong(int n){
    int org_n = n;
    int arr[10];
    int sum = 0;
    int i =0;
    while(n >0){
        arr[i] = n%10;
        n = n/10;
        i++;
    }
    for(int j=0;j<i;j++){
        sum = sum + (pow(arr[j],i));
    }

    if(sum == org_n){
        return 1;
    }
    return 0;
}

int main(){

    int server_fd = socket(AF_INET,SOCK_STREAM,0);

    struct sockaddr_in server_addr,client_addr;
    int len = sizeof(client_addr);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind(server_fd,(struct sockaddr*)&server_addr,sizeof(server_addr));

    listen(server_fd,10);



    char buf[100] = {0};
    int n;

    while (1)
    {
        int client1 = accept(server_fd,(struct sockaddr*)&client_addr,&len);
        printf("Client:1 - %d\n",client1);
        int client2 = accept(server_fd,(struct sockaddr*)&client_addr,&len);
         printf("Client:2 - %d\n",client2);

         int amstrong = -1;

        if(fork() == 0){
            if(amstrong == -1){
                recv(client1,&n,sizeof(int),0);
                amstrong = check_amstrong(n);
                printf("\n%d--",amstrong);
                
            }
            
            if(amstrong == 0){
                    printf("Hereee\n");
                    send(client1,"Not Amstrong",13,0);
                    close(client1);
                    exit(1);
            }else if(amstrong == 1){
                send(client2,"Amstrong",9,0);
                send(client1,"---",4,0);
                close(client1);
                close(client2);
                exit(1);
            }
                close(client1);
                close(client2);
                exit(1);
            }
            

        }

    close(server_fd);  
    return 0;
}