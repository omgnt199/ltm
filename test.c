#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>
#include <time.h>
int findcountstring(char *str1, char *str2){

}
int main(){
    FILE *f = fopen("/home/omgbk/homework/20230417/Bai0102/soict.txt","r");
    char buf[2048];
    char p[] = "0123456789";
    char *s;
    fscanf(f,"%s",buf);
    int len = strlen(buf);
    s = strstr(buf,"0123456789");
    printf("%s\n",s);
    
    return 0;
}