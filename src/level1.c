#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

#define FILE_OFFSET 3

char FILES[10][20] = {
	"config.txt",
	"pass.txt",
	"project_ideas.txt",
	"test1.xml",
	"test2.xml",
	"test3.xml",
	"comm_partner.cfg",
	"chat_logs.txt",
	"useful_commands.txt",
	"todo"
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
