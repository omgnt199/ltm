#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
    char SERVER_ADDR[20];
    int SERVER_PORT;
    char filename[30];
    strcpy(filename,argv[1]);
    strcpy(SERVER_ADDR,argv[2]);
    sscanf(argv[3],"%d",&SERVER_PORT);
    int client = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(SERVER_ADDR);
    addr.sin_port = htons(SERVER_PORT); 
    // Truyen nhan du lieu
    FILE *f = fopen(filename,"r");
    char buf[2048];
    char data[2048];
    strcpy(buf,filename);
    //Lay du lieu trong file
    fgets(data,sizeof(data),f);
    strcat(buf,"-");
    strcat(buf,data);
    //Truyen du lieu sang server
    int ret = sendto(client, buf,strlen(buf),0,(struct sockaddr*)&addr,sizeof(addr));
    close(client);
    return 0;
}