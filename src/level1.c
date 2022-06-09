#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

#define FILE_OFFSET 3

char FILES[10][20] = {
	"/home/level1/config.txt",
	"/home/level1/pass.txt",
	"/home/level1/project_ideas.txt",
	"/home/level1/test1.xml",
	"/home/level1/test2.xml",
	"/home/level1/test3.xml",
	"/home/level1/comm_partners.cfg",
	"/home/level1/chat_logs.txt",
	"/home/level1/useful_commands.txt",
	"/home/level1/todo"
};

int main() {
	int16_t x;
	printf("Input number for file to read:\n");
	for (int i = FILE_OFFSET; i < 10; i++) {
		printf("%d. %s\n", i - FILE_OFFSET, FILES[i]);
	}
	scanf("%d", &x);
	if (x < 0) {
		printf("Invalid array index!\n");
		return 1;
	}
	int8_t file_index = x + FILE_OFFSET;
	
	setreuid(geteuid(), geteuid());

	char line[256];
	FILE * f = fopen(FILES[file_index], "r");
	while (fgets(line, sizeof(line), f)) {
		puts(line);		
	}
	return 0;
}
