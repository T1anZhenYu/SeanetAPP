#ifndef SEAEP_CONFIG_H
#define SEAEP_CONFIG_H


#ifdef __cplusplus
extern "C" {
#endif


typedef enum
{
    SEAEP_RT_SUCCESS=0,        
    SEAEP_RT_FAILED=-1
}SEAP_RT_VALUE;


long seaep_config_handle_init(const char *config_name);

//#ȫ�����ֽ���ϵͳ��ַglobalResolutionSystem=192.168.47.12
const char * seaep_config_read_global_resolutionname(long seaep_handle);

//#��ײ�����ڵ�
const char * seaep_config_read_c1node(long seaep_handle);

//#��ײ�����ڵ㼶��
int seaep_config_read_c1node_delaylevel(long seaep_handle);

//#��ǿ���ֽ���ϵͳ�н����ڵ�ʱ�ӵȼ�delayLevels=1,2,3
int   seaep_config_read_delay_levels_num(long seaep_handle);

SEAP_RT_VALUE   seaep_config_read_delay_levels(long seaep_handle, int *delaylevels);

int   seaep_config_read_delay_parms_num(long seaep_handle);

//#��ǿ���ֽ���ϵͳ�н����ڵ�ʱ����ֵ����λ����delayParameters=10,50,100
SEAP_RT_VALUE   seaep_config_read_delay_parms(long seaep_handle, int *delayparms);

//#��ʹ�õ���ǿ���ֽ����ڵ�ʱ�ӵȼ�delayLevelsInUse=1,2,3
int   seaep_config_read_delay_levels_inuse_num(long seaep_handle);

SEAP_RT_VALUE   seaep_config_read_delay_levels_inuse(long seaep_handle, int *delaylevels);

//#��ʹ�õ���ǿ���ֽ����ڵ�IDresolverIdsInUse=879899,324983,928349
int   seaep_config_read_resolverIds_inuse_num(long seaep_handle);

SEAP_RT_VALUE   seaep_config_read_resolverIds_inuse(long seaep_handle, int *ids);

//#��ʹ�õ���ǿ���ֽ����ڵ������ַresolverNasInUse=192.100.65.31,192.100.65.31,
int   seaep_config_read_resolvernas_inuse_num(long seaep_handle);

const char *  seaep_config_read_resolvernas_inuse(long seaep_handle, int  number);

//#��ײ�����ڵ��ھ�IDneighborIds=456456,65756,345234,457456
int   seaep_config_read_neighborIds_num(long seaep_handle);

SEAP_RT_VALUE   seaep_config_read_neighborIds(long seaep_handle, int *ids);

//#��ײ�����ڵ��ھ������ַneighborIds=192.100.65.32,192.100.65.34,192.100.65.35,192.100.65.36
int   seaep_config_read_neighbornas_num(long seaep_handle);

const char *  seaep_config_read_neighbornas(long seaep_handle, int  number);

SEAP_RT_VALUE seaep_config_close_handle(long seaep_handle);



//all write interface
SEAP_RT_VALUE seaep_config_write_global_resolutionname(const char *filename, const char * gr_name);

SEAP_RT_VALUE seaep_config_write_global_c1node(const char *filename, const char *c1_na);

SEAP_RT_VALUE   seaep_config_write_delay_levels(const char *filename, int *delaylevels, int num_delaylevels);

SEAP_RT_VALUE   seaep_config_write_delay_parms(const char *filename, int *delayparms, int num_delaylevels);

SEAP_RT_VALUE   seaep_config_write_delay_levels_inuse(const char *filename,  int *delaylevels_inuse, int num_delaylevels_innum);

SEAP_RT_VALUE   seaep_config_write_resolverIds_inuse(const char *filename,  int *ids, int idnums);

SEAP_RT_VALUE  seaep_config_write_resolvernas_inuse(const char * filename, char **resolvernas, int  number);

SEAP_RT_VALUE   seaep_config_write_neighborIds(const char * filename, int *ids, int idnums);

SEAP_RT_VALUE  seaep_config_write_neighbornas(const char * filename, char **neighbornas, int  number);

SEAP_RT_VALUE seaep_config_write_c1node_level(const char *filename, int delay_level);


#ifdef __cplusplus
}
#endif

#endif
