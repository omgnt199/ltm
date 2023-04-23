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
    fscanf(f,"%s",buf);
    int len = strlen(buf);
    int dataleft = strlen(buf);
    int datasent;
    int index;
    while(dataleft>0){
        datasent = send(client, buf,dataleft, 0);
        // if(datasent<0) break;
        dataleft -= datasent;
        index += datasent;
        printf("%d %d\n",datasent,dataleft);
        if(datasent<0) break;
    }
    // Ket thuc, dong socket
    close(client);

    return 0;
}