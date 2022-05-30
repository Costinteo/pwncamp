#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char PASSWORD[] = "(Fxt4xu*iqF)w|";
int XORKEY = 25;

void crypt(char * txt) {
	for (;*txt;*txt^=XORKEY,++txt);
}

int main() {
	int ruid = getuid();
	int euid = geteuid();
	char buffer[32];
	scanf("%s", buffer);
	if (ruid == euid) {
		crypt(buffer);
		if (!strcmp(buffer, PASSWORD)) {
			setreuid(ruid, euid);
			FILE * f = fopen("pass.txt", "r");
			char line[256];
			while (fgets(line, sizeof(line), f)) {
				puts(line);
			}
		}
	}
	return 0;
}
