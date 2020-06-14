#ifndef SEANET_SOCKET_H
#define SEANET_SOCKET_H

#include <sys/uio.h>
#include <stdint.h>
#include <stdio.h>

#define DEBUG


#define DGB_LEVEL				DBG_LEVEL_ERROR

#define DBG_LEVEL_IDLE			100
#define DBG_LEVEL_MOMO			200
#define DBG_LEVEL_TRACE		300
#define DBG_LEVEL_NOTES		400
#define DBG_LEVEL_WARNING		500
#define DBG_LEVEL_ERROR		600
#define DBG_LEVEL_PANIC		700
#define DBG_LEVEL_SILENT		800
#define DBGPRINT(level, args...) 	\
	do{							\
		if(level >= DGB_LEVEL)	\
			printf(args);		\
		}while(0);



#define SEDNET_VERSION 1




#define MAX_CHUNK_SIZE 10000
#define MAX_UDP_PACKET_SIZE  1000

#define EID_LEN 20
#define PROTO_IPV4 4
#define PROTO_IPV6 6
#define PROTO_UDP 17
#define PROTO_SEADP 1 //tentative?
#define PROTO_SEANET 0x99

#define LISTEN_SOCKET 1
#define SENDER_SOCKET 2
#define RECEIVER_SOCKET 3

#define UDP_HDR_LEN 8
#define SEADP_HDR_LEN 20      //temp
#define ID_HDR_LEN 44
#define IPV4_HDR_LEN 20
#define IPV6_HDR_LEN 40

#define MAX_SREQ 124      //tentetive?


#define BUFFER_SIZE 1500


//填port需要使用htons()函数  
typedef struct
{
    unsigned char Eid[20];          //20bytes  EID
    unsigned short Port;            //16bits   Port
}sea_idport_t ;



typedef struct {
    char stat;                    //socket create stat;-1,error;1,normal;2,recv chunk finish; sock创建 1；sock绑定ID和端口 2； seadp receiver setid or listen have init 3;错误 -1
    unsigned char domain;         //domain:PROTO_ILISTENPV4,PROTO_IPV6
    unsigned char protocol;       //protocol:PROTO_UDP,PROTO_SEADP
    unsigned char recv_send_listen;
    sea_idport_t  local_idport;
    void * seadp_info;
    void * channel_id;
    void * ip_info;
}seanet_socket;


typedef enum {
    UDP_SEADP,
    SET_LOCALNA,
    SET_EIDNA,
    DEL_EIDNA,
    SET_STORAGE_FLAG,
    SET_CACHE_FLAG,
    // DEL_IDPLIST,
    OTHER
}optname_t;
typedef enum {
    GET_EIDNA
}g_optname_t;
//sea_idp.h
typedef struct{
    unsigned char Eid[20];
    unsigned char IP[16];
}eid_ip_t;

typedef struct{
    unsigned char *chunkEid;
    unsigned char *req_deviceID;
}reqid_info_t;



#ifdef __cplusplus
extern "C" {
#endif

seanet_socket *sea_socket(unsigned char domain, unsigned char protocol);

int sea_bind (seanet_socket *sock, sea_idport_t * id_port);
// ID+UDP
int sea_sendto (seanet_socket *sock, const void *buff, size_t nbytes, const sea_idport_t *id_port , int flags);
// ID+UDP

int sea_recvfrom (seanet_socket *sock, void *buff, sea_idport_t *id_port , int blocked ,int flags);


int sea_seteid (seanet_socket *sock, unsigned char peer_id[20]);   // init seadp receiver struct info


unsigned long sea_recv (seanet_socket *sock, void *buff, size_t nbytes, unsigned char wait_flag, int flags);


seanet_socket *sea_listen (seanet_socket *sock, int backlog);

const reqid_info_t * sea_geteid (seanet_socket *sock);

int sea_send (seanet_socket *sock, const void *buff, size_t nbytes, int flags);


int sea_close (seanet_socket *sock);

int sea_setsockopt (seanet_socket *sock,optname_t optname, const void *optval, const int optlen);

int sea_getsockopt (seanet_socket *sock, g_optname_t optname,  void *optval,const int optlen);

//static int para_cmp(unsigned char *firstPara,unsigned char *secondPara,size_t cmp_length);

#ifdef __cplusplus
}
#endif
#endif
