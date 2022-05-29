#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char template[] = "/tmp/log.XXXXXX";
int log_msg_count = 0;

void write_log(char filename[], const char msg[], int severity) {
	FILE * f = NULL;
	char log_data[512];
	snprintf(log_data, sizeof(log_data),
			"LOG MSG:%d, severity:%d, %s\n",
			log_msg_count++, severity, msg);
	f = fopen(filename, "a+");
	fputs(log_data, f);
	fclose(f);
}

void read_log(char filename[]) {
	FILE * f = NULL;
	char line[256];
	if (f = fopen(filename, "r")) {
		while (fgets(line, sizeof(line), f)) {
			printf("%s", line);
		}
	} else {
		printf("File not found!\n");
	}
	fclose(f);
}

int main() {
	FILE * f = NULL;
	char * debug_mode = getenv("DEBUG");

	if (debug_mode && !strcmp(debug_mode, "TRUE")) {
		mktemp(template);
		write_log(template, "DEBUG MODE IS ENABLED!", 0);
		write_log(template, "Testing logging.", 0);
		setreuid(geteuid(), geteuid());
		read_log(template);
	}

	return 0;
}
