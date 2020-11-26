#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <omp.h>
#include <openssl/md5.h>

char *str2md5(const char *str, int length) {
    int n;
    MD5_CTX c;
    unsigned char digest[16];
    char *out = (char*)malloc(33);

    MD5_Init(&c);

    while (length > 0) {
        if (length > 512) {
            MD5_Update(&c, str, 512);
        } else {
            MD5_Update(&c, str, length);
        }
        length -= 512;
        str += 512;
    }

    MD5_Final(digest, &c);

    for (n = 0; n < 16; ++n) {
        snprintf(&(out[n*2]), 16*2, "%02x", (unsigned int)digest[n]);
    }

    return out;
}

int main()
{
	int i;
	volatile bool flag = false;
		#pragma omp parallel for shared(flag)
		for (i = 0 ; i <= 99999999; i++) {
			if(flag)
				continue;
			char password[8]; 
			sprintf(password,"%08d",i);
					
			printf("%s\n",password);
			// hash
			char *passwordMD5 = str2md5(password, strlen(password));

			// compare
			if (strcmp("95dbb48a7b21a9cff9221eb0b431fa3c", passwordMD5) == 0) {
				printf("Found!\nPassword is ");
				password[8] = '\0';
				printf("%s", password);
				printf("\n");
				flag = true;
				free(passwordMD5);
			}
			free(passwordMD5);
		}
	return 0;
}
