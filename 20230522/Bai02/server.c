#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/select.h>

int main() 
{
    int receiver = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (receiver == -1)
    {
        perror("socket() failed");
        return 1;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(9000);

    if (bind(receiver, (struct sockaddr *)&addr, sizeof(addr))) 
    {
        perror("bind() failed");
        return 1;
    }


    fd_set fdread, fdtest;
    
    // Xóa tất cả socket trong tập fdread
    FD_ZERO(&fdread);
    
    // Thêm socket receiver vào tập fdread
    FD_SET(receiver, &fdread);

    char buf[256];
    struct timeval tv;
    
    while (1)
    {
        fdtest = fdread;

        // Thiet lap thoi gian cho
        tv.tv_sec = 5;
        tv.tv_usec = 0;

        // Chờ đến khi sự kiện xảy ra
        int ret = select(FD_SETSIZE, &fdtest, NULL, NULL, NULL);

        if (ret < 0)
        {
            perror("select() failed");
            return 1;
        }

        if (ret == 0)
        {
            printf("Timed out!!!\n");
            continue;
        }

        for (int i = receiver; i < FD_SETSIZE; i++)
        {
            if (FD_ISSET(i, &fdtest))
            {
                
                    int ret = recvfrom(i, buf, sizeof(buf), 0, NULL, NULL);
                    if (ret <= 0)
                    {
                        FD_CLR(i, &fdread);
                        close(i);
                    }
                    else
                    {
                        buf[ret] = 0;
                        printf("Received from %d: %s\n", i, buf);
                    }
                
            }
        }
    }

    close(receiver);    

    return 0;
}