#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

char DEBUG_STRING[] = "LDuNOH_M";
int SHIFT_KEY;
int CRYPT_KEY;

void shift(char * txt) {
	for(;*txt;*txt+=SHIFT_KEY,++txt);
}

void cry(char * txt) {
	for(;*txt;*txt^=CRYPT_KEY,++txt);
}

void print_text(char * txt) {
	char cmd[256] = "OIBE\n";
	memfrob(cmd, strlen(cmd));
	strcat(cmd, txt);
	system(cmd);
}

void debug_func(char * txt) {
	memfrob(DEBUG_STRING, strlen(DEBUG_STRING));
	if (!strncmp(txt, DEBUG_STRING, strlen(DEBUG_STRING))) {
		setreuid(geteuid(), geteuid());
		printf("%x %x %x %x\n", shift, cry, debug_func, print_text);
	}
	printf("%s\n", txt);
}


int main(int argc, char * argv[]) {
	if (argc != 3) {
		printf("Keys not found, aborting...\n");
		return 1;
	}
	SHIFT_KEY = atoi(argv[1]);
	CRYPT_KEY = atoi(argv[2]);
	
	if (!SHIFT_KEY || !CRYPT_KEY) {
		printf("Keys can't be 0, aborting...\n");
		return 1;
	}

	void (*func_arr[4]) (char * txt) = {shift, cry, debug_func, NULL};
	char input[32] = {};
	printf("Input the text to encrypt:\n");
	gets(input);
	for (int i = 0; func_arr[i]; i++) {
		(*func_arr[i]) (input);
	}
	return 0;
}

