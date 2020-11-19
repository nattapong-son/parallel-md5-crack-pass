#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include <openssl/sha.h>
 
typedef unsigned char byte;
 
int matches(byte *a, byte* b) {
	for (int i = 0; i < 32; i++)
		if (a[i] != b[i])
			return 0;
	return 1;
}
 
 
byte* StringHashToByteArray(const char* s) {
	byte* hash = (byte*) malloc(32);
	char two[3];
	two[2] = 0;
	for (int i = 0; i < 32; i++) {
		two[0] = s[i * 2];
		two[1] = s[i * 2 + 1];
		hash[i] = (byte)strtol(two, 0, 16);
	}
	return hash;
}
 
void printResult(byte* password, byte* hash) {
	char sPass[6];
	memcpy(sPass, password, 5);
	sPass[5] = 0;
	printf("%s => ", sPass);
	for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
		printf("%02x", hash[i]);
	printf("\n");
}
 
int main(int argc, char **argv)
{
 
#pragma omp parallel
	{
 
#pragma omp for
		for (int a = 0; a < 26; a++)
		{
			byte password[5] = { 97 + a };
			byte* one =   StringHashToByteArray("95dbb48a7b21a9cff9221eb0b431fa3c");
			for (password[1] = 97; password[1] < 123; password[1]++)
				for (password[2] = 97; password[2] < 123; password[2]++)
					for (password[3] = 97; password[3] < 123; password[3]++)
						for (password[4] = 97; password[4] < 123; password[4]++) {
							byte *hash = SHA256(password, 5, 0);
							if (matches(one, hash))
								printResult(password, hash);
						}
			free(one);
		}
	}
 
	return 0;
}