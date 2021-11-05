#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "mbedtls/base64.h"

bool b64encode = true;  // what operation will we perform? encode or decode
bool readFile = true;   // are we reading from file or command line?

void printHexAndAscii(uint8_t* buff, int len)
{

}

void reportSyntaxError(void)
{
    printf("Syntax Error.\n");
    printf("Usage: base64.exe [-encode | -decode] [-file | -cmdLine] [input]\n");
    printf("Ex: base64.exe -decode -cmdLine OTo7PD0+Pw==\n");
    printf("Ex: base64.exe -decode -file fileContainingB64String.txt\n");
    printf("Ex: base64.exe -encode -cmdLine AABBCCDDEEFF\n");
    printf("Ex: base64.exe -encode -file fileContainingHexString.txt\n");
}

int readFileToBuffer(char* fileName, char** buffer, int* olen)
{
    int fileSize = 0;
    int fileSize2;
    int rtn = 0;
    if (!fileName) return __LINE__;
    if (!buffer) return __LINE__;
    if (!olen) return __LINE__;

    FILE* fptr = fopen(fileName,"rb");
    if (!fptr) return __LINE__;

    //get file size
    fseek(fptr, 0L, SEEK_END);
    fileSize = ftell(fptr);
    fseek(fptr, 0L, SEEK_SET);

    //allocate buffer
    *buffer = malloc(fileSize);
    if (!*buffer) return __LINE__;

    fileSize2 = fread(*buffer,1,fileSize,fptr);
    fclose(fptr);

    //verify no error while reading
    if (fileSize2 != fileSize)
    {
        free(*buffer);
        return __LINE__;
    }

    *olen = fileSize;
    //if success here, app needs to free() buffer later...
    return 0;
}

int main(int argc, char *argv[])
{
    char* buffer = 0;
    int bufferSize = 0;

    printf("argc = %d\n", argc);
    //syntax
    // base64.exe [-encode | -decode] [-file | -cmdLine] [input]
    if (argc != 4)
    {
        reportSyntaxError();
        return __LINE__;
    }

    if (0 == strcmp(argv[1], "-encode"))
    {
        b64encode = true;
    }
    else if (0 == strcmp(argv[1], "-decode"))
    {
        b64encode = false;
    }
    else
    {
        reportSyntaxError();
        return __LINE__;
    }
    
    if (0 == strcmp(argv[2], "-file"))
    {
        readFile = true;
    }
    else if (0 == strcmp(argv[2], "-cmdLine"))
    {
        readFile = false;
    }
    else
    {
        reportSyntaxError();
        return __LINE__;
    }

    if (readFile)
    {
        if (readFileToBuffer(argv[3], &buffer, &bufferSize)) return __LINE__;
    }
    else
    {
        buffer = argv[3];
        bufferSize = strlen(argv[3]);
    }

    // process
    if (b64encode)
    {
        printf("base64 encode\n");
        printf("input: ");
        printf("%s\n",buffer);
        printf("\n");
    }
    else
    {
        printf("base64 decode\n");
        printf("input: ");
        printf("%s\n",buffer);
        //get olen
        size_t olen = 0;
        mbedtls_base64_decode(0,0,&olen,buffer,bufferSize);
        uint8_t* dest = malloc(olen);
        if (!dest) return __LINE__;
        if (mbedtls_base64_decode(dest,olen,&olen,buffer,bufferSize)) return __LINE__;
        printf("%s",dest);
        free(dest);
    }
}