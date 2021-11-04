#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "mbedtls/base64.h"

uint8_t buff[64];

int main(void)
{
    printf("base64 decode\n");

    for (uint32_t x=0;x<sizeof(buff);x++)
    {
        buff[x]=x;
    }
    size_t olen = 0;
    mbedtls_base64_encode(0,0,&olen,buff,sizeof(buff));

    uint8_t* dest = malloc(olen);
    if (dest)
    {
        size_t destLen = olen;
        mbedtls_base64_encode(dest,destLen,&olen,buff,sizeof(buff));
        printf("%s",dest);
        free(dest);
    }
}