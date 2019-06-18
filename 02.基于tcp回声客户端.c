#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#define BUF_SIZE 1024
void error_handling(char *message);
int main(int argc,char *argv[])
{
    int sock,sum=0,cnt;
    struct sockaddr_in serv_addr;
    char message[1024];
    int len;
    
    if(argc!=3){
        printf("Usage:%s <IP> <PORT>\n",agrv[0]);
        exit(1);
    }
    
    sock=socket(PF_INET,SOCK_STREAM,0);
    if(sock==-1) error_handling("socket error");
    
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=inet_addr(argv[1]);   ///若字符串有效则将字符串转换为32位二进制网络字节序的IPV4地址，否则为INADDR_NONE
    serv_addr.sin_port=htons(atoi(argv[2]));
    
    if(connect(sock,(struct *sockaddr_in)&serv_addr),sizeof(serv_addr))==-1)
        error_handling("connect error");
    
    scanf("%s",message);
    len=write(sock,message,sizeof(message));
    if(len==-1) error_handling("read error");
    while(sum<len){
        cnt=read(sock,&message[sum],BUF_SIZE-1);
        if(cnt==-1) error_handling("read error");
        sum+=cnt;
    }
    message[sum]='\0';
    printf("Message from server:%s\n",message);
    close(sock);
    return 0;
}

void error_handling(char *message){
    fputs(message,stderr);
    fputs('\n',stderr);
    exit(1);
}
