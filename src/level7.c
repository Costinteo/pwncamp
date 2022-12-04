#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

char PASSWORD[] = "3m:OS%.DR";
char TRUE_CMD[] = "IK^\nZKYY\x04^R^";
char RED_CMD[] = "OIBE\nDE^\nBOXO";
char BLUE_CMD[] = "\x75\x5e\x1a\x1a\x41\x75\x5e\x42\x4f\x75\x48\x46\x5f\x4f\x5a\x43\x46\x46";
char PRINT_CMD[] = "\x5a\x58\x43\x44\x5e\x4c\xa\x46\x1e\x50\x4b\x58\x5f\x59\x75\x4d\x58\x1a\x5f\x5a";
char PASS_MSG[] = "zFOKYO\nCDZ_^\nZKYY]EXN\nKY\nLCXY^\nKXM_GOD^";
char GRATS_MSG[] = "kIIOYY\nMXKD^ON";

void hash(char * word) {
	for (uint16_t k=3;*word;*word=(*word^k)%94+33,k=k*(k-1)+*word,++word);
}

void system_cmd(char * cmd) {
	memfrob(cmd, strlen(cmd));
	system(cmd);
	memfrob(cmd, strlen(cmd));
}

int main(int argc, char * argv[]) {
	if (argc != 2) {
		memfrob(PASS_MSG, strlen(PASS_MSG));
		printf("%s\n", PASS_MSG);
		return 1;
	}

	char s[32] = "";
	char pass[32] = "";
	scanf("%31s", s);
	strncpy(pass, argv[1], 31);
	int pos = 0;
	
	hash(pass);
	if (!strcmp(pass, PASSWORD) && strlen(s) == 9 && s[0] == s[1] + s[8] && s[2] == s[5] - 11 && s[3] == s[8] + s[4] + 10) {

		while (1) {
			switch (s[pos]) {
			case '1':
				pos -= 1;
				break;
			case '3':
				++pos;
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
				if (!strcmp(pass, PASSWORD)) {
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
			case 'm':
				++pos;
				break;
			case 'n':
				pos += 2;
				break;
			case 'h':
				pos += 2;
				break;
			case 'c':
				system_cmd(RED_CMD);
				system_cmd(BLUE_CMD);
				pos += 2;
				break;
			case '-':
				pos += 20;
				if (!strcmp(pass, PASSWORD)) {
					setreuid(geteuid(), geteuid());
					memfrob(GRATS_MSG, strlen(GRATS_MSG));
					printf("%s\n", GRATS_MSG);
					system_cmd(TRUE_CMD);
				}
				break;
			case 'S':
				pos += 7;
				break;
			case 'U':
				pos *= 2 + 5;
				if (!strcmp(pass, PASSWORD)) {
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
			case '@':
				++pos;
				break;
			default:
				goto EXIT;
			}
		}
	}
EXIT:
	return 0;
}

