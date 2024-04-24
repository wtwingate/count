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
		} else
			count(fp);
	}
	return 0;
}

void count(FILE *fp)
{
	int c;
	int words, lines, chars, bytes;

	while ((c = getc(fp)) != EOF) {
		putchar(c);
	}
}
