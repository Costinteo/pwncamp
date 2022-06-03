#include <stdio.h>

char RED[] = "3.14_1s-pi";
char HERRING[] = "gh0st-1n_th3-sh3ll";
char THROWAWAY[] = "the_cak3-IS-A-LI3";
char EGG[] = "SHad0w-br0k3rs";
char EASTER[] = "s3rot0nin";
char TNT[] = "tr1ni7rot0luen3";
char STREET[] = "ses4m3-pupp3t";

int main(int argc, char * argv[]) {
	char buffer[256] = {};
	if (argc < 5) {
		return 1;
	}


	scanf("%255s", buffer);
	if (!strncmp(buffer, STREET + 2, 3) && buffer[3] == '_' &&
		!strncmp(buffer + 4, EASTER, 2)  &&
		!strncmp(buffer + 6, RED + 8, 2) &&
		!strncmp(buffer + 8, TNT + 9, 2)) {
		setreuid(geteuid(), geteuid());
		system("cat pass.txt");
	}

	return 0;
}
