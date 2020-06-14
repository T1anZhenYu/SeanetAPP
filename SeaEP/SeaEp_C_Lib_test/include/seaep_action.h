#ifndef SEAEP_ACTION_H
#define SEAEP_ACTION_H

#ifdef __cplusplus
extern "C" {
#endif

#include "resolve_name_list.h"

#define SEAEP_ACTION_REGISTER 0x9
#define SEAEP_ACTION_RESOLVER 0xb
#define SEAEP_ACTION_LOGOUT 0xd
#define SEAEP_ACTION_RNL 0x7
#define SEAEP_ACTION_MEASURE 0x1b //00011011  
#define SEAEP_ACTION_UPDATE_RNL 0x15 //00010101



#define SEAEP_ACTION_RESPONSE_RNL 0x8 //00001000
#define SEAEP_ACTION_RESPONSE_RIGSTER 0xa//00001010
#define SEAEP_ACTION_RESPONSE_RESOLVE 0xc//00001000
#define SEAEP_ACTION_RESPONSE_LOGOUT 0xd//00001000
#define SEAEP_ACTION_RESPONSE_MEASURE 0x1c //00011100 
#define SEAEP_ACTION_RESPONSE_UPDATE_RNL 0x16 //00010110


#define SEAEP_GATEWAY_PROT 10010
#define SEAEP_GATEWAY_REGISTER_EID 0xfc//11111100
#define SEAEP_GATEWAY_RESPONSE_REGISTER_EID 0xfd//11111101
#define SEAEP_GATEWAY_REQUEST_IPV6NA 0xfe //11111110
#define SEAEP_GATEWAY_RESPONSE_REQUEST_IPV6NA 0xff //11111111

#define STATUS_OK 1
#define STATUS_FAILED 0

#define EID_LEN 20
#define IP_LEN 16

typedef enum{
    SEAEP_EVENT_NETWORK_CHANGE=0,
    SEAP_EVENT_EID_CHANG,
    SEAP_EVENT_BUT
}SEAP_EVENT;

//for external call

int seaep_init_config(const char * config_filename, int rnl_update_interval);

int seaep_set_config(const char * config_filename, const char *global_resolve_node,const char *resolve_node, int delay_level);

int seaep_request_rnlist();

int seaep_register(char eid[EID_LEN],unsigned char delayParameter,unsigned char ttl, int isGlobalVisable);

int seaep_registerwithIP(char eid[EID_LEN],  int delayParameter,unsigned char ttl, int isGlobalVisable,char na_ip[16]);

na_list_info* seaep_resolve(char eid[EID_LEN], int delayParameter);

int seaep_unregister(char eid[EID_LEN]);
int seaep_unregisterwithIP(char eid[EID_LEN],char na_ip[16]);

unsigned int seaep_request_delaytime(char * server_addr, int port);

int seaep_update_rnl(char * server_addr, int port,char delay_level);

int renew_rn_list();

int seaep_request_ipv6na(int local_gw);


// internal interface
void* seaep_process_resolve_msg(char *recv_data, int len);

void * seaep_process_register_msg(char *recv_data, int len);

void * seaep_process_rnlist_request(char *recv_data, int len);

void* seaep_process_delaytime_msg(char *recv_data, int len);

void* seaep_process_unregister_msg(char *recv_data, int len);

void* seaep_process_update_rnl_msg(char *recv_data, int len);

int seaep_register_eidtoAP(char eid[EID_LEN],int local_ip,int local_gw);

void* seaep_process_eidtoAP_msg(char *recv_data, int len);

void* seaep_process_ipv6na_msg(char *recv_data, int len);
//wait for to do 
int seaep_start_daemon();

int seaep_set_active_netdevice(const char * devicename);

const char * seaep_get_active_netdevice();

int seaep_notify_event(SEAP_EVENT event);

#ifdef __cplusplus
}
#endif


#endif
