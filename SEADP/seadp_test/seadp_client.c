#include "seanet_socket.h"
#include <netinet/in.h>
#include <stdlib.h>
#include <fcntl.h>                          // 提供open()函数
#include <sys/types.h>                      // 提供mode_t类型
#include <sys/stat.h>                       // 提供open()函数的符号
#include <unistd.h>                         // 提供close()函数
#include <stdio.h>

#define LOCAL_ID 0
#define DST_ID 0


// #define LOCAL_IP "3ffe::146"
// #define IDNA_IP "3ffe::144"
// #define LOCAL_PORT 8000    // 客户端要绑定的端口
#define BUFFER_SIZE 100000000  //比chunk size 大就行

int main(int argc, char **argv){
    unsigned char * LOCAL_IP = argv[1];
    unsigned char * IDNA_IP = argv[2];
    unsigned short LOCAL_PORT = atoi(argv[3]);
    unsigned char *filename[2];
    filename[0] = "./output/chunk1";
    filename[1] = "./output/chunk2";    

    int i=2;
    for(;i>0;i--){
        seanet_socket* sock = sea_socket(PROTO_IPV6,PROTO_SEADP);
        if(sock<=0){
            printf("seanet_socket creat error!!!\n");
            goto end;
        }
        //设置本地 IP 地址
        unsigned char l_ip[16];
        inet_pton(AF_INET6,LOCAL_IP,l_ip);
        sea_setsockopt(sock, SET_LOCALNA,l_ip,16);

        // 给IDP 设置ID和NA的映射关系
        eid_ip_t idna;
        bzero(idna.Eid,20); //ID赋值，这里ID为全零
        idna.Eid[19]=i;
        inet_pton(AF_INET6,IDNA_IP,idna.IP); //ID 解析到的 NA
        sea_setsockopt(sock,SET_EIDNA,&idna,sizeof(eid_ip_t));

        sea_idport_t local_idport;
        local_idport.Port=htons(LOCAL_PORT);
        bzero(local_idport.Eid,20);
        srand(get_time_ms());
        local_idport.Eid[19]= rand()/100;

        if(sea_bind(sock,&local_idport)!=0){
            printf("bind error!!!\n" );
            goto end;
        }

        unsigned char chunkid[20];
        bzero(chunkid,20);  // 设置要获取的chunk ID
        chunkid[19]=i;
        if(sea_seteid(sock,chunkid)!=0){
            printf("set id error!!!\n");
            goto end;
        }
        unsigned char * buff = (unsigned char * )malloc(BUFFER_SIZE);

        int64_t start_time = get_time_ms();
        uint32_t len = sea_recv(sock,buff,BUFFER_SIZE,1,0); // 接收到的chunk 数据 会存储到buff中，返回值为chunk size
        int64_t end_time = get_time_ms();
        double time= ((double)(end_time - start_time))/1000;
        printf(" time : %lf s\n",time);
        double chunksize = ((double)len)/1024/1024;
        printf("chunk size %lf MB\n",chunksize);
        double bw = chunksize/time;
        printf("带宽： %lf\n",bw);
        if(len>0){
            printf("recv chunk finish!!! chunksize %d\n",len);
            printf("filename is :%s\n",filename[i-1]);
            int *fp = open(filename[i-1], O_WRONLY | O_CREAT);
            if (fp == NULL)
            {
                return 0;
            }
            len=write(fp,buff,len);
            if(len>0){
                printf("chunk recv over!!!\n");
            }
            close(fp);
        }else{
            printf("recv error!!!\n");
        }
        free(buff);
        buff=NULL;



    end:
        sea_close(sock);
    }


    return 0;
}
