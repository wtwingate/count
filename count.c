#include <stdio.h>

void count(FILE *fp);

int main(int argc, char *argv[])
{
	FILE *fp;

	if (argc == 1) {  /* no args; count standard input */
		count(stdin);
	} else {
		fp = fopen(argv[1], "r");
		if (fp == NULL) {
			printf("Error: can't open %s\n", argv[1]); 
			return 1;
		} else {
			count(fp);
			fclose(fp);
		}
	}
	return 0;
}

void count(FILE *fp)
{
	int c;
	long words, lines, chars, bytes;

	words = lines = chars = bytes = 0;
	while ((c = getc(fp)) != EOF) {
		bytes ++;
	}
	printf("%ld\n", bytes);
}
