#include <stdio.h>

#define TRUE   1
#define FALSE  0

unsigned char parse_args(int argc, char *argv[]);
void count(FILE *fp, unsigned char opts, char *fname);

int main(int argc, char *argv[])
{
	FILE *fp;
	char *fname;
	unsigned char opts;

	if (argc == 1) {  /* no args; count standard input */
		count(stdin, 0, "");
	} else {
		fname = argv[1];
		fp = fopen(fname, "r");
		if (fp == NULL) {
			printf("Error: can't open %s\n", fname); 
			return 1;
		} else {
			count(fp, 0, fname);
			fclose(fp);
		}
	}
	return 0;
}

unsigned char parse_args(int argc, char *argv[])
{
	return 0;
}

void count(FILE *fp, unsigned char opts, char *fname)
{
	int c;
	int in_word;
	long words, lines, chars, bytes;

	in_word = FALSE;
	words = lines = chars = bytes = 0;
	while ((c = getc(fp)) != EOF) {
		bytes ++;
		chars ++;
		if (c == '\n') {
			lines++;
		}
		if (c == ' ' || c == '\t' || c == '\n') {
			in_word = FALSE;
		} else if (in_word == FALSE) {
			in_word = TRUE;
			words++;
		}
	}

	printf("%ld\t%ld\t%ld\t%s\n", lines, words, bytes, fname);
}
