#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>

int main(int argc, char *argv[]) 
{
    //Xu ly tham so dong lenh
    char SERVER_ADDR[] = "127.0.0.1";
    int SERVER_PORT;
    sscanf(argv[1],"%d",&SERVER_PORT);
    int listener = socket(AF_INET, SOCK_DGRAM, IPPROTO_TCP);
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
    int clientAddrLen = sizeof(clientAddr);
    int client = accept(listener, (struct sockaddr *)&clientAddr, &clientAddrLen);
    if (client == -1)
    {
        perror("accept() failed");
        return 1;
    }
    printf("New client connected: %d\n", client);
    // Truyen nhan du lieu
    FILE *f = fopen("file_receiver.txt","w");
    char buf[2048];
    int ret = recvfrom(client,buf, sizeof(buf), 0,NULL,NULL);
    buf[ret] = 0;
    close(client);
    close(listener);    
    return 0;
}