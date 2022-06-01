#include <stdio.h>
#include <string.h>
#include <unistd.h>

const char PASSWORD[] = "\x40\x2c\x7a\x22\x26\x26\x73\x30\x56\x1b\x79\x2c\x39\x20\x30\x27\x5a\x74\x27";
FILE * VAULT;
char VAULT_NAME[] = "\x04\x5a\x4b\x59\x59\x75\x5c\x4b\x5f\x46\x5e";

void xcrypt(char * pass, const char * key) {
	int pos = 0;
	for (;*pass;*pass^key[pos++%strlen(key)], pass++);
}

void store_pass(const char * pass, const char * platform) {
	char entry[64] = "";
	strncat(entry, platform, strlen(platform));
	strcat(entry, ":");
	strncat(entry, pass, strlen(pass));
}

void load_pass(const char * plaftorm) {

}

int main(int argc, char * argv[]) {
	memfrob(VAULT_NAME, strlen(VAULT_NAME));
	VAULT = fopen(VAULT_NAME, "a+");
	char line[256];
	fgets(line, sizeof(line), VAULT);
	puts(line);
	// get arguments
	// decide what you're going to do
	// password manager
	// hidden buffer overflow (strncat?)
	// decrypt password hidden in pass.txt
	// use some stupid encryption, leaking info by xoring some parts twice by mistake
	return 0;
}
