#include"../include/write.h"
#include<stdio.h>
#include"cjson/cJSON.h"
# include <stdlib.h>
void writeFile(const char* filePath){
    unsigned char* chunkList;
    int chunkNum;
    chunkList = fileCut(filePath,CHUNKSIZE,&chunkNum);
    cJSON *pJsonRoot = NULL;
    unsigned char tempEID[EID_LEN];
    char tempNum[10];
    for(int i = 0; i < chunkNum; i++){
        sprintf(tempNum, "%d", i); 
        strncpy(tempEID,chunkList+EID_LEN*i,EID_LEN);
        cJSON_AddStringToObject(pJsonRoot,tempNum,tempEID);
    }
    cJSON_Print(pJsonRoot);
    cJSON_Delete(pJsonRoot);

}