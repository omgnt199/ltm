#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>


// Client gửi file sang server

int main(int argc, char* argv[])
{
    //Xu ly tham so dau vao
    char SERVER_ADDR[12];//Dia chi IP cua server
    int SERVER_PORT;//Cong server
    strcpy(SERVER_ADDR,argv[1]);
    sscanf(argv[2],"%d",&SERVER_PORT);

    int client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(SERVER_ADDR);
    addr.sin_port = htons(SERVER_PORT);
    int ret = connect(client, (struct sockaddr *)&addr, sizeof(addr));
    if (ret == -1)
    {
        perror("connect() failed");
        return 1;
    }
    while(1){
        char mssv[14];
        char hoten[30];
        char ngaysinh[20];
        char noi = '-';
        char dtb[5];
        char buf[2048];
        printf("Nhap thong tin sinh vien:\n");
        printf("1.MSSV :");
        fgets(mssv,sizeof(mssv),stdin);
        printf("2.Ho ten :");
        fgets(hoten,sizeof(hoten),stdin);
        printf("3.Ngay sinh (dd/mm/yyyy) :");
        fgets(ngaysinh,sizeof(ngaysinh),stdin);
        printf("4.Diem trunh binh :");
        fgets(dtb,sizeof(dtb),stdin);
        dtb[strlen(dtb)-1]  = 0;
        strcpy(buf,mssv);
        strcat(buf,hoten);
        strcat(buf,ngaysinh);
        strcat(buf,dtb);
        if(buf[0] == '\n') break;        //Dung nhap tin nhan khi nguoi dung nhap ky tu "xuong dong"
        send(client, buf,strlen(buf) , 0);
    }
    close(client);
}