#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
    char SERVER_ADDR[20];
    int SERVER_PORT;
    strcpy(SERVER_ADDR, argv[1]);
    sscanf(argv[2],"%d",&SERVER_PORT);
    int sender = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(SERVER_ADDR);
    addr.sin_port = htons(SERVER_PORT);
    char buf[256];
    while (1)
    {
        printf("Chat: ");
        fgets(buf, sizeof(buf), stdin);
        int ret = sendto(sender, buf, strlen(buf), 0,
            (struct sockaddr *)&addr, sizeof(addr));
    }
}