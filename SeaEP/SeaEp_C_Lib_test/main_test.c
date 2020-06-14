#include "include/seaep_config.h"
#include "include/seaep_action.h"
#include "include/seaep_eid.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CONFIG_FILENAME "seaep.config"
#define APP_DELAY_LEVEL 3

/*
#ȫ�����ֽ���ϵͳ��ַglobalResolutionSystem=192.168.47.12
#��ǿ���ֽ���ϵͳ�н����ڵ�ʱ�ӵȼ�delayLevels=1,2,3
#��ǿ���ֽ���ϵͳ�н����ڵ�ʱ����ֵ����λ����delayParameters=10,50,100
#��ʹ�õ���ǿ���ֽ����ڵ�ʱ�ӵȼ�delayLevelsInUse=1,2,3
#��ʹ�õ���ǿ���ֽ����ڵ�IDresolverIdsInUse=879899,324983,928349
#��ʹ�õ���ǿ���ֽ����ڵ������ַresolverNasInUse=192.100.65.31,192.100.65.31,192.100.65.33
#��ײ�����ڵ��ھ�IDneighborIds=456456,65756,345234,457456
#��ײ�����ڵ��ھ������ַneighborIds=192.100.65.32,192.100.65.34,192.100.65.35,192.100.65.36
*/

 
int main(int argc, char **argv)
{
    int i;

    //seaep_request_delaytime("1:1:1:1:1:1:1:3",10061);return 0;
    seaep_init_config(CONFIG_FILENAME, 5);
    //sleep(100);
    //return 0;

    seaep_set_config(CONFIG_FILENAME, "192.168.189.202","192.168.189.202",APP_DELAY_LEVEL);



    char eid[EID_LEN];
    int ret  = createEid(eid);

    //seaep_request_rnlist();
    char IP[]={0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20};
    seaep_registerwithIP(eid, 500, 1, 1,IP);




    na_list_info*resolve_list = seaep_resolve(eid, 500);
    if(resolve_list){
        for(i=0;i<resolve_list->na_num;i++)
            printf("nalist[%d] %s\n",i,resolve_list->na_list[i]);
    }

    
    seaep_unregisterwithIP(eid,IP);
    return 0;
}

