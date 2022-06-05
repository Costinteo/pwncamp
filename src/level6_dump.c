#include <unistd.h>
#include <fcntl.h>

char DATA[] = "&\\9&&4dJ4o(a47JPD!}n{wgun<e6lJq`3/4Cv$5ua_9c6'V6s2sp5k*Y<{Kh#58!G#!{~k2Mib7z0BtHTv9@0zRzJyP!d^EvPm='FZ4O]rn9z6&nA$L-'T=7\"W:V7o=DRTQ5*@87El)0oAV7>H%y1go1=CN1V\%gNjUz$tWYp27#82^Py4k625f\\81dtj.:!Lip_-R9Hh]Z8Z~$KQ/;6k5]CQWec:_FZtM4`vcy@#1UiiTC$60fH]O<qkkI1>{~5Edt+<Y0$]d'ah8hr\"K@#KSp\"}3h&^!2,w0*PMczsE(>KC9\\wy2rgl7s\"0t9o83z0Sqzwrt6U?/860=1bC32%j]{&L[c38n@3@0vtey6f~sOLKl,.}Da2{'nf4m-}4;<:C^8?&XWZMX~D~nn-P2G^1OhTyqf1\"d:&KKl:9@9p|xS8nbw+P:'|TK9==NoW&5%jLcZ5j(T9k8~:mr*@-4Td9YBdIr6+1?Pir0D>ISA]5FbV|1n\"zF:ip5/?%?}-~5%+";

int main(int argc, char * argv[]) {
	int i;
	char buffer[32] = {};
	char key = argv[2][0];
	for (i = 0; argv[1][i]; i++) {
		buffer[i] = argv[1][i] ^ key;
		key++;
		if (buffer[i] != DATA[511 - 10 + i]) {
			return 1;
		}
	}
	if (DATA[511 - 10 + i]) return 1;
	int fd = open("pass.txt", O_RDONLY);
	char password[256] = {};
	read(fd, password, sizeof(password));
	for (int i = 0; password[i]; i++) {
		write(1, password + i, 1);
	}
	return 0;
}
