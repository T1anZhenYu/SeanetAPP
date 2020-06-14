#include "../include/filecut.h"
int count = 0;
void createEID(unsigned char* chunkEid)
{
    for (int i = 0; i < EIDSIZE; i++) {
        chunkEid[i] = '1' + count;
    }
    count++;
}
unsigned char* fileCut(const char* filePath, const int chunkSize, int* chunkNum)
{
    FILE *fp1, *fp2;
    fp1 = fopen(filePath, "r");
    if (fp1 == NULL) {
        printf("open file failed\n");
        return NULL;
    }
    struct stat statbuf;
    stat(filePath, &statbuf);
    int fileSize = statbuf.st_size;
    int extra = 0;
    if (fileSize % chunkSize != 0) {
        extra = 1;
    }
    *chunkNum = (int)(fileSize / chunkSize) + extra;
    printf("chunkNun:%d\n", *chunkNum);
    unsigned char* chunkList = (unsigned char*)malloc(sizeof(unsigned char) * *chunkNum * chunkSize);
    strcpy(chunkList, "");
    unsigned char buffer[chunkSize];
    unsigned char chunkEid[EIDSIZE];
    char tempPath[200];
    int sizeRead = 0;
    do {
        sizeRead = fread(buffer, sizeof(char), chunkSize, fp1);
        // printf("sizeRead:%d\n", sizeRead);
        if (sizeRead == 0) {
            break;
        }
        createEID(chunkEid);
        strncat(chunkList, chunkEid, EID_LEN);
        strcpy(tempPath, "");
        strcpy(tempPath,TMPPATH);
        strncat(tempPath, chunkEid, EID_LEN);
        // printf("here\n");
        // strcat(tempPath,'\0');

        if (sizeRead > 0) {
            // printf("sizeRead:%d\n", sizeRead);
            // printf("tempPath:%s\n", tempPath);

            fp2 = fopen(tempPath, "w+");
            if (fp2 == NULL) {
                printf("open %s failed\n", tempPath);
                return NULL;
            }
            int res = fwrite(buffer, sizeof(char), sizeRead, fp2);
            if (res == 0) {
                printf("write failed\n");
            }
            fclose(fp2);
        }

    } while (sizeRead != 0);
    // printf("chunkList:%s\n", chunkList);
    fclose(fp1);
    return chunkList;
}
int main()
{
    int chunkNum = 0;
    unsigned char* chunkList;
    chunkList = fileCut("/Users/tian/tian/seanet/SeanetAPP/5M", 1000, &chunkNum);
    unsigned char* temp = chunkList;
    int count = 0;
    // printf("here\n");
    // printf("chunkList:%s\n",chunkList);
    for (int i = 0; i < (chunkNum-10)*EID_LEN; i++) {

        if (i > 0 && i % (EID_LEN) == 0) {
            printf(" : %d\n",i/EID_LEN);
        }
        printf("%c", chunkList[i]);

     
    }
    free(chunkList);
}