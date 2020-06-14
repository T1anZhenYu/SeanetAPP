#include<stdio.h>
#include<string.h>
#include <sys/stat.h>
#include<stdlib.h>
#include"../../SeaEP/SeaEp_C_Lib_test/include/seaep_eid.h"
#ifndef TMPPATH
#define TMPPATH "./temp/"
#endif
#ifndef EIDSIZE
#define EIDSIZE 20
#endif

unsigned char* fileCut(const char* filePath, const int chunkSize, int* chunkNum);