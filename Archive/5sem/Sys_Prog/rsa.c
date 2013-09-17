#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define TRUE 1
#define FALSE 0

unsigned long rand_e(void){
	unsigned long e;
	srand(time(NULL));
	while (e%2 == 0){
	e = 1+ rand()%65536;
	}
	return e;
}

int witness(unsigned short a, unsigned short n) {
	unsigned long d = 1;
	unsigned long b = n-1;
	unsigned long c;
	while(b != 0) {
		if(b & 1) {
			d = (d*a) % n;
		}
		c = a;
		a = (a*a)%n;
		b = b >> 1;
		if((a == 1) && (c != 1) && (c != n-1)){
			return TRUE;
		}
	}
	if (d == 1) {
		return FALSE;
	}
	return TRUE;
}

int miller(unsigned short n, int s) {
	unsigned short a;
	for(; s > 0 ; s--) {
		a = rand();
		a = abs(a)%n;
		if(witness(a, n) == TRUE) {
			return FALSE;
		}
	}
	return TRUE;
}


unsigned short gen_prime() {
	unsigned short n;
	int s = 15;
	int is_simple = FALSE;
	
	while(is_simple != TRUE) {
		n = 0;
		while(abs(n) < 256) {
			n = rand();
		}
		n = abs(n);
		if(miller(n, s) == TRUE) {
			is_simple = TRUE;
		}
	}
	return n;
}

unsigned long long* extended_euclid(unsigned long a, unsigned long b, unsigned long long* ret) {
	unsigned long long tmp;
	if(b == 0) {
		ret[0] = a;
		ret[1] = 1;
		ret[2] = 0;
		return ret;
	}
	ret = extended_euclid(b, a % b, ret);
	tmp = ret[1];
	ret[1] = ret[2];
	ret[2] = tmp-a/b*ret[2];
	return ret;
}

unsigned long long mod_exp(unsigned long long a, unsigned long long b, unsigned long long n) {
	int d = 1;
	while(b != 0) {
		if((b&1) == 1) {
			d = (d*a)%n;
		}
		b = b >> 1;
		a = (a*a)%n;
	}
	return d;
}


void generated_keys(char* file_public_key, char* file_secret_key) {
	FILE *public_key ,*secret_key;
	unsigned short p = 0, q = 0; 
	unsigned long n; 
	unsigned long f; 
	unsigned long e; 
	unsigned long d = 0; 
	unsigned long long *ret;
	int stop = FALSE;
	srand(time(NULL));
	e = rand_e();
	while(p == q) {
		p = gen_prime();
		q = gen_prime();
	}
	printf("%lu\n",e);
	printf("%u\n",p);
	printf("%u\n",q);
	n = p*q;
	f = (p-1)*(q-1);
	if ((ret= (unsigned long long*)calloc(3, sizeof(unsigned long long)))==NULL){ printf("calloc error:"); exit(1);}
	ret = extended_euclid(e, f, ret);
	while(stop != TRUE) {
		ret = extended_euclid(e, f, ret);
		if(ret[0] == 1) {
			if((long)ret[1] < 0) {
				d = (unsigned long)((long)ret[1]+f);
			} else {
				d = (unsigned long)ret[1];
			}
			stop = TRUE;
		} else {
			e = rand_e();
		}		
	}
	free(ret);
	public_key = fopen(file_public_key, "wb");
	secret_key = fopen(file_secret_key, "wb");
	fwrite(&e, 1, sizeof(e), public_key); 
	fwrite(&n, 1, sizeof(n), public_key);
	fwrite(&d, 1, sizeof(d), secret_key); 
	fwrite(&n, 1, sizeof(n), secret_key);
	fclose(public_key);
	fclose(secret_key);
	printf("Ключи сгенерированы (файлы: %s, %s)\n", file_public_key, file_secret_key);
}


void crypt(char* file_input, char* file_public_key) {
	unsigned long e, n; 
	unsigned char m;
	unsigned long c; 
	FILE* public_key;
	FILE* input_msg;
	FILE *crypt_msg;
	if((public_key = fopen(file_public_key, "rb")) == NULL) {
		printf("Ошибка! Невозможно открыть файл %s\n", file_public_key);
		exit(1);
	}
	if((input_msg = fopen(file_input, "rb")) == NULL) {
		printf("Ошибка! Невозможно открыть файл %s\n", file_input);
		exit(1);
	}
	crypt_msg = fopen("crypt_msg", "wb");
	fread(&e, 1, sizeof(e), public_key);
	fread(&n, 1, sizeof(n), public_key);
	fread(&m, 1, sizeof(m), input_msg);
	while(!feof(input_msg)) {
		c = mod_exp((unsigned long long)m, (unsigned long long)e, (unsigned long long)n);
		fwrite(&c, 1, sizeof(c), crypt_msg);
		fread(&m, 1, sizeof(m), input_msg);
	}
	fclose(crypt_msg);
	fclose(input_msg);
	fclose(public_key);
	printf("Сообщение зашифровано (файл: crypt_msg)\n");
}


void decrypt(char* file_crypt, char* file_secret_key) {
	unsigned long d, n; 
	unsigned long c; 
	unsigned char m; 
	FILE *secret_key;
	FILE *crypt_msg;
	FILE* decrypt_msg;
	if((secret_key = fopen(file_secret_key, "rb")) == NULL) {
		printf("Ошибка! Невозможно открыть файл %s\n", file_secret_key);
		exit(1);
	}
	if((crypt_msg = fopen(file_crypt, "rb")) == NULL) {
		printf("Ошибка! Невозможно открыть файл %s\n", file_crypt);
		exit(1);
	}
  decrypt_msg = fopen("decrypt_msg", "w");
	fread(&d, 1, sizeof(d), secret_key);
	fread(&n, 1, sizeof(n), secret_key);
	fread(&c, 1, sizeof(c), crypt_msg);
	while(!feof(crypt_msg)) {
		m = mod_exp((unsigned long long)c, (unsigned long long)d, (unsigned long long)n);
		fwrite(&m, 1, sizeof(m), decrypt_msg);
		fread(&c, 1, sizeof(c), crypt_msg);
	}
	fclose(secret_key);
	fclose(crypt_msg);
	fclose(decrypt_msg);	
	printf("Сообщение расшифровано (файл: decrypt_msg)\n");
}


int main(int argc, char* argv[]) {
	if(argc < 4) {
		printf("Ошибка! Для работы программы необходимо указать ключ и два входных файла:\n");
		printf("\t1) ./*.out -gen <public_key> <secret_key> - для генерации ключей\n");
		printf("\t2) ./*.out -crypt <input> <public_key> - для шифрования файла <input>\n");
		printf("\t3) ./*.out -decrypt <crypt> <secret_key> - для дешифрования файла <crypt>\n");
		exit(1);
	}
	if(strcmp("-gen", argv[1]) == 0) {
		generated_keys(argv[2], argv[3]);
	} else if(strcmp("-crypt", argv[1]) == 0) {
		crypt(argv[2], argv[3]);
	} else if(strcmp("-decrypt", argv[1]) == 0) {
		decrypt(argv[2], argv[3]);
	} else {
		printf("Ошибка! Неизвестный ключ. Используйте\n");
		printf("\t-gen для генерации ключей\n");
		printf("\t-crypt для шифрования файла\n");
		printf("\t-decrypt для дешифрования файла\n");
	}
	return 0;
}

