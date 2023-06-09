#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int argc, char* argv[])
{

    char SERVER_ADDR[] = "127.0.0.1";
    int SERVER_PORT;
    char hello_file[100];
    char detail_file[100];
    sscanf(argv[1],"%d",&SERVER_PORT);
    strcpy(hello_file,argv[2]);
    strcpy(detail_file,argv[3]);
    int listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listener == -1)
    {
        perror("socket() failed");
        return 1;
    }
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(SERVER_ADDR);
    addr.sin_port = htons(SERVER_PORT);
    if (bind(listener, (struct sockaddr *)&addr, sizeof(addr)))
    {
        perror("bind() failed");
        return 1;
    }

    if (listen(listener, 5))
    {
        perror("listen() failed");
        return 1;
    }

    struct sockaddr_in clientAddr;
    int clientAddrLen = sizeof(addr);
    FILE *f_hello = fopen(hello_file,"w");
    FILE *f_detail =fopen(detail_file,"w");
    int client = accept(listener, (struct sockaddr *)&clientAddr, &clientAddrLen);
    printf("Client IP: %s:%d\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
    char hello[2048] = "Xin chao client voi dia chi IP ";
    char client_port[20];
    sprintf(client_port,"%d",ntohs(clientAddr.sin_port));
    strcat(hello,inet_ntoa(clientAddr.sin_addr));
    strcat(hello," va cong ung dung ");
    strcat(hello,client_port);
    fprintf(f_hello,"%s",hello);
    while(1){
        char buf[2048]; 
        int ret;
        ret = recv(client, buf, sizeof(buf), 0);
        if (ret <= 0)
            break;
        buf[ret] =0;
        fprintf(f_detail,"%s",buf);

    }
    fclose(f_hello);
    fclose(f_detail);
    close(client);
    close(listener);
}