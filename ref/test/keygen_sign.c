#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "test_params.h"

int main()
{
    int ret = 0;
    int i;

    /* Make stdout buffer more responsive. */
    setbuf(stdout, NULL);

    unsigned char pk[SPX_PK_BYTES];
    unsigned char sk[SPX_SK_BYTES];
    unsigned char *m = malloc(SPX_MLEN);
    unsigned char *sm = malloc(SPX_SMLEN);
    unsigned long long smlen;

    randombytes(m, SPX_MLEN);

    printf("unsigned char m[%u] = {", SPX_MLEN);
    for(i=0;i<SPX_MLEN-1;i++) 
      printf("0x%02x, ", m[i]);
    printf("0x%02x};\n\n", m[i]);


    if (crypto_sign_keypair(pk, sk)) {
        printf("failed!\n");
        return -1;
    }

    printf("unsigned char sk[%u] = {", SPX_SK_BYTES);
    for(i=0;i<SPX_SK_BYTES-1;i++) 
      printf("0x%02x, ", sk[i]);
    printf("0x%02x};\n\n", sk[i]);

    printf("unsigned char pk[%u] = {", SPX_PK_BYTES);
    for(i=0;i<SPX_PK_BYTES-1;i++) 
      printf("0x%02x, ", pk[i]);
    printf("0x%02x};\n\n", pk[i]);

    crypto_sign(sm, &smlen, m, SPX_MLEN, sk);

    if (smlen != SPX_SMLEN) {
      printf("  X smlen incorrect [%llu != %u]!\n", smlen, SPX_BYTES);
      return -1;
    }

    printf("unsigned char sm[%u] = {", SPX_SMLEN);
    for(i=0;i<SPX_SMLEN-1;i++) 
      printf("0x%02x, ", sm[i]);
    printf("0x%02x};\n\n", sm[i]);

    free(m);
    free(sm);

    return ret;
}
