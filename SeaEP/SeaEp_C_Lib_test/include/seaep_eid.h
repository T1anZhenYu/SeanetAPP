#ifndef SEAEP_EID_H
#define SEAEP_EID_H
#ifdef __cplusplus
extern "C" {
#endif

#define EID_LEN 20

int createEid(unsigned char eid[EID_LEN]);
char* geteid() ;
int get_device_eid(unsigned char device_eid[EID_LEN]) ;

#ifdef __cplusplus
}
#endif

#endif

