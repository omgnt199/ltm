#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>

int main() {
    int client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(9090); 

    if (connect(client, (struct sockaddr *)&addr, sizeof(addr))) {
        perror("connect() failed");
        return 1;
    }
    // Truyen nhan du lieu
    FILE *f = fopen("soict.txt","r");
    char buf[2048];
    //Lay du lieu trong file
    fscanf(f,"%s",buf);
    //Truyen du lieu sang server
    int len = strlen(buf);
    int dataleft = strlen(buf);//Byte du lieu chua gui
    int datasent;//Byte du lieu da gui
    int index = 0;
    while(dataleft>0){
        datasent = send(client, &buf[index],dataleft, 0);
        if(datasent<0) break;
        dataleft -= datasent;
        index += datasent;
    }
    close(client);
    return 0;
}