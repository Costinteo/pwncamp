#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

char PASSWORD[] = "19o>B][;I=/IYLI%yljj";
char TRUE_CMD[] = "IK^\nZKYY\x04^R^";
char RED_CMD[] = "OIBE\nDE^\nBOXO";
char BLUE_CMD[] = "\x75\x5e\x1a\x1a\x41\x75\x5e\x42\x4f\x75\x48\x46\x5f\x4f\x5a\x43\x46\x46";
char PRINT_CMD[] = "\x5a\x58\x43\x44\x5e\x4c\xa\x46\x1e\x50\x4b\x58\x5f\x59\x75\x4d\x58\x1a\x5f\x5a";

void hash(char * word) {
	for (uint16_t k=3;*word;*word=(*word^k)%94+33,k=k*(k-1)+*word,++word);
}

void system_cmd(char * cmd) {
	memfrob(cmd, strlen(cmd));
	system(cmd);
	memfrob(cmd, strlen(cmd));
}

int main(int argc, char * argv[]) {
	if (!argv[1]) {
		return 1;
	}

	char s[256];
	scanf("%245s", s);
	strncat(s, argv[1], sizeof(s) - strlen(s) - 1);
	int pos = 1;
	while (1) {
		switch (*(argv[pos])) {
		case '0':
			pos += 3;
			break;
		case '3':
			hash(s);
			pos -= 2;
			break;
		case '7':
			pos += 10;
			system_cmd(BLUE_CMD);
			break;
		case '8':
			pos *= 4;
			break;
		case '9':
			pos *= 3;
			break;
		case 'a':
			if (!strcmp(s, PASSWORD)) {
				system_cmd(RED_CMD);
			}
			pos += 10;
			break;
		case 'd':
			goto EXIT;
		case 'g':
			system_cmd(PRINT_CMD);
			pos ^= 2;
			break;
		case 'l':
			pos = pos * 2 + 6;
			break;
		case 'o':
			system_cmd(PRINT_CMD);
			pos ^= 5;
			break;
		case 'r':
			pos += 13;
			break;
		case 's':
			pos *= 2;
			break;
		case 'x':
			pos += 2;
			setreuid(geteuid(), geteuid());
			break;
		case 'C':
			system_cmd(RED_CMD);
			system_cmd(BLUE_CMD);
			break;
		case 'K':
			pos += 20;
			if (!strcmp(s, PASSWORD)) {
				system_cmd(TRUE_CMD);
			}
			break;
		case 'S':
			pos += 7;
			break;
		case 'U':
			pos *= 2 + 5;
			if (!strcmp(s, PASSWORD)) {
				system_cmd(PRINT_CMD);
			}
			break;
		case 'W':
			pos = 3;
			break;
		case 'Y':
			if (pos > 20) {
				system_cmd(RED_CMD);
			}
			break;
		case '.':
			pos = pos * 2 + 5;
			break;
		default:
			goto EXIT;
		}
	}
EXIT:
	return 0;
}
