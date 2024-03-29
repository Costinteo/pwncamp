#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

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
		fclose(f);
	} else {
		printf("File not found!\n");
	}
}

void make_tmp(char * tmp) {
	char buffer[7];
	time_t rawtime;
	struct tm * timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	*strchr(tmp, 'X') = '\0';
	sprintf(buffer, "%d%d%d\0", timeinfo->tm_mday, timeinfo->tm_min, timeinfo->tm_sec);
	strcat(tmp, buffer);
}

int main() {
	FILE * f = NULL;
	char * debug_mode = getenv("DEBUG");

	if (debug_mode && !strcmp(debug_mode, "TRUE")) {
		make_tmp(template);
		write_log(template, "DEBUG MODE IS ENABLED!", 0);
		write_log(template, "Testing logging.", 0);
		setreuid(geteuid(), geteuid());
		sleep(1);
		read_log(template);
	}

	return 0;
}
