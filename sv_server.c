#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>
// Server nhan file tu client
struct Client{
    int index;
    int port;
    char ip[12];
};
int main(int argc, char* argv[])
{
    //Xu ly tham so dong lenh
    char SERVER_ADDR[] = "127.0.0.1";
    int SERVER_PORT;
    char detail_file[100];
    sscanf(argv[1],"%d",&SERVER_PORT);
    strcpy(detail_file,argv[2]);

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
    FILE *f_detail =fopen(detail_file,"a+");
    int client = accept(listener, (struct sockaddr *)&clientAddr, &clientAddrLen);
    printf("Client IP: %s:%d\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
    char clientIP[20];
    strcpy(clientIP,inet_ntoa(clientAddr.sin_addr));
    time_t timer;
    char time_buf[26];
    struct tm* tm_info;
    while(1){
        char buf[2048]; 
        int ret;
        ret = recv(client, buf, sizeof(buf), 0);
        if (ret <= 0)
            break;
        timer = time(NULL);
        tm_info = localtime(&timer);
        strftime(time_buf, 26, "%Y-%m-%d %H:%M:%S", tm_info);
        for(int i = 0;i <strlen(buf);i++){
            if(buf[i]== '\n') buf[i] = ' ';
        }
        char log[2048];
        strcpy(log,clientIP);
        strcat(log," ");
        strcat(log,time_buf);
        strcat(log," ");
        strcat(log,buf);
        log[strlen(log)] = '\n';
        fprintf(f_detail,"%s",log);
    }
    fclose(f_detail);
    close(client);
    close(listener);
}