#include <stdio.h>
#include <string.h>
#include <unistd.h>

const char PASSWORD[] = "\x40\x2c\x7a\x22\x26\x26\x73\x30\x56\x1b\x79\x2c\x39\x20\x30\x27\x5a\x74\x27";
FILE * VAULT;
char VAULT_NAME[] = "\x04\x5a\x4b\x59\x59\x75\x5c\x4b\x5f\x46\x5e";

void xopen_vault(const char * mode) {
	setreuid(geteuid(), geteuid());
	memfrob(VAULT_NAME, strlen(VAULT_NAME));
	VAULT = fopen(VAULT_NAME, mode);
	memfrob(VAULT_NAME, strlen(VAULT_NAME));
}

void xreset_vault() {
	xopen_vault("w");
	fclose(VAULT);
}

void xcrypt(char * pass, const char * key) {
	int pos = 0;
	for (;*pass;*pass=*pass+key[pos%strlen(key)], pass++, pos++);
}

void store_pass(const char * platform, char * pass, const char * key) {
	xopen_vault("a+");
	char entry[64] = "";
	xcrypt(pass, key);
	strncat(entry, platform, strlen(platform));
	strcat(entry, ":");
	strncat(entry, pass, strlen(pass));
	fputs(entry, VAULT);
	fputs("\n", VAULT);
	fclose(VAULT);

}

void load_pass(const char * key, const char * platform) {
	xopen_vault("r");
	char line[256];
	while (fgets(line, sizeof(line), VAULT)) {
		char * delim = strchr(line, ':');
		*delim = '\0';
		if (!strcmp(line, platform)) {
			char password[64] = "";
			strcpy(password, delim + 1);
			password[strlen(password)] = '\0';
			xcrypt(password, key);
			puts(password);
		}
	}
	fclose(VAULT);
}

void print_menu() {
	puts("Welcome to xCrypt password manager! What do you want to do?");
	char menu[][256] = {
		"Store password;",
		"Load password;",
		"Reset vault;",
		"Exit;"
	};
	for (int i = 0; i < sizeof(menu) / sizeof(menu[0]); i++) {
		printf("%d. %s\n", i + 1, menu[i]);
	}
}

int main() {
	int option;
	char platform[128], pass[128], key[64];
	print_menu();
	scanf("%d", &option);

	switch (option) {
		case 1:
			puts("Input platform, password and key, separated by whitespaces (PLATFORM PASSWORD KEY):");
			scanf("%127s %127s %63s", platform, pass, key);
			store_pass(platform, pass, key);
			break;
		case 2:
			puts("Input platform and key, separated by whitespaces (PLATFORM KEY):");
			scanf("%127s %63s", platform, key);
			load_pass(key, platform);
			break;
		case 3:
			xreset_vault();
			break;
		case 4:
			break;
	}
	return 0;
}
