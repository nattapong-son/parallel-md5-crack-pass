#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include <openssl/md5.h>

typedef unsigned char byte;

void MD5_HashString(char *src, char *dest){
  MD5_CTX ctx;
  unsigned char digest[16];
  int i;
  MD5_Init(&ctx);
  MD5_Update(&ctx, src, strlen(src));
  MD5_Final(digest,&ctx);
  for (i = 0; i < 16; i++)  {
    sprintf(&dest[i*2],"%02x", digest[i]);
  }
}

int main(int argc, char **argv)
{

#pragma omp parallel
	{
		#pragma omp for
			for (int i = 0 ; i <= 9; i++) {
					for (int j = 0 ; j <= 9; j++) {
							for (int k = 0 ; k <= 9; k++) {
									for (int l = 0 ; l <= 9; l++) {
										for (int m = 0 ; m <= 9; m++) {
											for (int n = 0 ; n <= 9; n++) {
												for (int o = 0 ; o <= 9; o++) {
													for (int p = 0 ; p <= 9; p++) {
														char password[] = { '0' + i, '0' + j, '0' + k, '0' + l, '0' + m, '0' + n, '0' + o, '0' + p  };
														char copyOfPassword[8];
														// hash
														char passwordMD5[32];
														MD5_HashString(password, passwordMD5);

														// compare
														if (strcmp("95dbb48a7b21a9cff9221eb0b431fa3c", passwordMD5) == 0) {
															strcpy(copyOfPassword, password);
															printf("Found!\nPassword is ");
															for (int q = 0 ; q < 8 ; q++) {
																printf("%d", copyOfPassword[q]);
															}
															printf("\n");
														}
													}
												}
											}
										}
									}
							}
					}
			}
	}

	return 0;
}
