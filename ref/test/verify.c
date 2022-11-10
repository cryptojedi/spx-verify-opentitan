#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "test_params.h"

#include "message_keys.inc"

int main()
{
  unsigned char *mout = malloc(SPX_SMLEN);
  unsigned long long mlen;
  int ret = 0;

  /* Test if signature is valid. */
  if (crypto_sign_open(mout, &mlen, sm, SPX_SMLEN, pk)) {
    printf("  X verification failed!\n");
    ret = -1;
  }
  else {
    printf("    verification succeeded.\n");
  }

  /* Test if the correct message was recovered. */
  if (mlen != SPX_MLEN) {
    printf("  X mlen incorrect [%llu != %u]!\n", mlen, SPX_MLEN);
    ret = -1;
  }
  else {
    printf("    mlen as expected [%llu].\n", mlen);
  }
  if (memcmp(m, mout, SPX_MLEN)) {
    printf("  X output message incorrect!\n");
    ret = -1;
  }
  else {
    printf("    output message as expected.\n");
  }

  free(mout);

  return ret;
}
