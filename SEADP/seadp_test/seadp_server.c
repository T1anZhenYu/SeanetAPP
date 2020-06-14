#include <unistd.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include "seanet_socket.h"

#define SERVER_LOCAL_PORT 9000 // 默认listen 端口 ，如果改变，需要更改客户端默认访问端口 ，一般不需要改

// #define LOCAL_IP "3ffe::144"

int main(int argc, char **argv)
{
    unsigned char * LOCAL_IP=argv[1];
    // 读取一个文件作为 chunk 测试使用
    unsigned char * filename = NULL;
    filename = "./test_file/1.jpg";
    int chunk_buffer_size1=0;
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("File Not Found!\n");
        return 0;
    }
    else
    {
        fseek(fp,0,SEEK_END);
        chunk_buffer_size1=ftell(fp);
        fseek(fp,0,SEEK_SET);
        printf("file_size1=%d\n",chunk_buffer_size1);
    }
    unsigned char *chunk1 = (unsigned char *)malloc(chunk_buffer_size1);
    if( chunk1 == NULL )
    {
      DBGPRINT( DBG_LEVEL_TRACE, "Error - unable to allocate required memory\n");
    }
    //bzero(chunk,chunk_buffer_size);
    fread(chunk1,sizeof(unsigned char),chunk_buffer_size1,fp);
    fclose(fp);


    filename = "./test_file/10mb.rar";
    int chunk_buffer_size2=0;
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("File Not Found!\n");
        return 0;
    }
    else
    {
        fseek(fp,0,SEEK_END);
        chunk_buffer_size2=ftell(fp);
        fseek(fp,0,SEEK_SET);
        printf("file_size2=%d\n",chunk_buffer_size2);
    }
    unsigned char *chunk2 = (unsigned char *)malloc(chunk_buffer_size2);
    if( chunk2 == NULL )
    {
      DBGPRINT( DBG_LEVEL_TRACE, "Error - unable to allocate required memory\n");
    }
    //bzero(chunk,chunk_buffer_size);
    fread(chunk2,sizeof(unsigned char),chunk_buffer_size2,fp);
    fclose(fp);


    seanet_socket* sock = sea_socket(PROTO_IPV6,PROTO_SEADP);
    if(sock<=0){
        printf("seanet_socket creat error!!!\n");
        goto end;
    }

    //设置本地IP
    unsigned char l_ip[16];
    inet_pton(AF_INET6,LOCAL_IP,l_ip);
    sea_setsockopt(sock, SET_LOCALNA,l_ip,16);

/*    // 设置 NA
    eid_ip_t idna;
    bzero(idna.Eid,20);
    inet_pton(AF_INET6,LOCAL_IP,idna.IP);
    sea_setsockopt(sock,SET_EIDNA,&idna,sizeof(eid_ip_t));*/

    sea_idport_t local_idport;
    local_idport.Port=htons(SERVER_LOCAL_PORT);
    bzero(local_idport.Eid,20);
    local_idport.Eid[19]=10;

    if(sea_bind(sock,&local_idport)!=0){
        printf("bind error!!!\n" );
        goto end;
    }
    int newport = 10000;
    int backlog = 20;
    while(1){
        // printf("wait REQ packet.\n");

        seanet_socket * newsock=sea_listen(sock,backlog);
        if(newsock != NULL){
            const reqid_info_t * reqid_info =sea_geteid(newsock); // 获取收到请求所请求的chunk ID和设备ID

            //TODO,match eid & chunk,CHUNK_SIZE & data

            //如果找到该ID的chunk 则发送
            //if( have chunk)

                //设置本地IP
            if(reqid_info->chunkEid[19]==1){
                inet_pton(AF_INET6,LOCAL_IP,l_ip);
                sea_setsockopt(newsock, SET_LOCALNA,l_ip,16);

                // 设置 NA

/*                eid_ip_t idna;
                memcpy(idna.Eid,reqid_info->chunkEid,20);
                printf(" chunkid \n");
                for(int i = 0;i<20;i++){
                    printf("%c",reqid_info->chunkEid[i]);
                }
                printf("\n");
/*                inet_pton(AF_INET6,"::1",idna.IP); //填入的解析ID NA
                sea_setsockopt(newsock,SET_EIDNA,&idna,sizeof(eid_ip_t));*/


                sea_idport_t sender_idport;
                sender_idport.Port=htons(0);
                // newport++; //更新未使用端口号
                bzero(sender_idport.Eid,20);
                unsigned char storage_flag = 1;
                unsigned char cache_flag = 2;
                sea_setsockopt(newsock,SET_STORAGE_FLAG,&storage_flag,1);
                sea_setsockopt(newsock,SET_CACHE_FLAG,&cache_flag,1);


                if(sea_bind(newsock,&sender_idport)!=0){
                    printf("bind error\n");
                }else{
                    printf("chunk sender pre to start ! \n");
                    sea_send(newsock,chunk1,chunk_buffer_size1,0);  // start a new thread
                }
            }else if(reqid_info->chunkEid[19]==2){
                inet_pton(AF_INET6,LOCAL_IP,l_ip);
                sea_setsockopt(newsock, SET_LOCALNA,l_ip,16);

                // 设置 NA

/*                eid_ip_t idna;
                memcpy(idna.Eid,reqid_info->chunkEid,20);
                printf(" chunkid \n");
                for(int i = 0;i<20;i++){
                    printf("%c",reqid_info->chunkEid[i]);
                }
                printf("\n");
/*                inet_pton(AF_INET6,"::1",idna.IP); //填入的解析ID NA
                sea_setsockopt(newsock,SET_EIDNA,&idna,sizeof(eid_ip_t));*/


                sea_idport_t sender_idport;
                sender_idport.Port=htons(0);
                // newport++; //更新未使用端口号
                bzero(sender_idport.Eid,20);


                if(sea_bind(newsock,&sender_idport)!=0){
                    printf("bind error\n");
                }else{
                    printf("chunk sender pre to start ! \n");
                    sea_send(newsock,chunk2,chunk_buffer_size2,0);  // start a new thread
                }

            }
            //如果 没有找到chunk 则关闭listen返回的套接字
            // sea_close(newsock);
        }
         usleep(1000);


    }

    end:
    free(chunk1);
    chunk1=NULL;
    sea_close(sock);
    return 0;

}

