#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
void error_handling(char *message);
int main(int argc,char *argv[])
{
    int sock;
    struct sockaddr_in serv_addr;
    char message[30];
    int strlen;
    
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
        
    strlen=read(sock,message,sizeof(message)-1);
    if(strlen==-1) error_handling("read error");
        
    printf("Message from server:%s\n",message);
    close(sock);
    return 0;
}

void error_handling(char *message){
    fputs(message,stderr);
    fputs('\n',stderr);
    exit(1);
}
