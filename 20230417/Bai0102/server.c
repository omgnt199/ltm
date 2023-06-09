#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
//Ham tim so lan xuat hien xau
int findcountstring(char *str1, char *str2){
    int count = 0;
    while(strstr(str2,str1)!= NULL){
        count++;
        char *s;
        s = strstr(str2,str1);
        strcpy(str2,&s[10]);
    }
    return count;
}
int main() 
{
    int listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listener == -1)
    {
        perror("socket() failed");
        return 1;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(9090);

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
    char buf[2048];
    char str[] = "0123456789";
    int ret = recv(client,buf, sizeof(buf), 0);
    buf[ret] = 0;
    printf("So lan xuat hien xau ky tu la:%d\n",findcountstring(str,buf));
    close(client);
    close(listener);    
    return 0;
}