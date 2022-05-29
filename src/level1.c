#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

#define FILE_OFFSET 3

char FILES[10][256] = {
	"config.txt",
	"pass.txt",
	"project_ideas.txt",
	"sbom_1.xml",
	"sbom_2.xml",
	"sbom_3.xml",
	"comm_partner.cfg",
	"chat_logs.txt",
	"useful_commands.txt",
	"todo"
};

int main() {
	int16_t x;
	scanf("%d", &x);
	if (x < 0) {
		printf("Invalid array index!\n");
	}
	int8_t file_index = x + FILE_OFFSET;
	
	setreuid(geteuid(), geteuid());

	char line[256];
	FILE * f = fopen(FILES[file_index], "r");
	while (fgets(line, sizeof(line), f) != NULL) {
		printf("%s", line);		
	}
	return 0;
}
