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
    int receiver = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (receiver == -1)
    {
        perror("socket() failed");
        return 1;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(SERVER_ADDR);
    addr.sin_port = htons(SERVER_PORT);

    if (bind(receiver, (struct sockaddr *)&addr, sizeof(addr))) 
    {
        perror("bind() failed");
        return 1;
    }
    // Truyen nhan du lieu
    FILE *f = fopen("file_receiver.txt","a+");
    char buf[2048];
    int ret = recvfrom(receiver,buf, sizeof(buf), 0,NULL,NULL);
    buf[ret] = 0;
    fprintf(f,"%s\n",buf);
    close(receiver);
    return 0;
}