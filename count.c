#include <ctype.h>
#include <stdio.h>
#include <string.h>

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
		return 0;
	}

	opts = parse_args(argc, argv);
	
	if (argv[argc-1][0] == '-') {  /* no file; only opts */
		count(stdin, opts, "");
		return 0;
	}
	
	fname = argv[argc-1];
	fp = fopen(fname, "r");
	if (fp == NULL) {
		printf("Error: can't open %s\n", fname); 
		return 1;
	} else {
		count(fp, opts, fname);
		fclose(fp);
	}
	return 0;
}

unsigned char parse_args(int argc, char *argv[])
{
	unsigned char opts = 0;

	for (int i = 0; i < argc; i++) {
		if (strcmp(argv[i], "-c") == 0) {
			/* count bytes */
			opts = opts | 0x01;
		} else if (strcmp(argv[i], "-l") == 0) {
			/* count lines */
			opts = opts | 0x02;
		} else if (strcmp(argv[i], "-w") == 0) {
			/* count words */
			opts = opts | 0x04;
		} else if (strcmp(argv[i], "-m") == 0) {
			/* count characters */
			opts = opts | 0x08;
		}
	}
	return opts;
}

void count(FILE *fp, unsigned char opts, char *fname)
{
	int c, in_word;
	long words, lines, chars, bytes;

	in_word = FALSE;
	words = lines = chars = bytes = 0;
	while ((c = getc(fp)) != EOF) {
		/*
		Info about encodings and how to handle UTF-8 multibyte chars in C:
		https://www.joelonsoftware.com/2003/10/08/the-absolute-minimum-every-software-developer-absolutely-positively-must-know-about-unicode-and-character-sets-no-excuses/
		https://dev.to/rdentato/utf-8-strings-in-c-1-3-42a4
		*/
		bytes ++;
		if ((c & 0xC0) != 0x80) /* check if current byte is part of a multibyte character */
			chars++;

		if (c == '\n')
			lines++;

		if (isspace(c)) {
			in_word = FALSE;
		} else if (in_word == FALSE) {
			in_word = TRUE;
			words++;
		}
	}

	if (opts == 0) {
		printf("\t%ld\t%ld\t%ld\t%s\n", lines, words, bytes, fname);
	} else {
		printf("\t");
		if ((opts & 0x02) == 0x02)
			printf("%ld\t", lines);
		if ((opts & 0x04) == 0x04)
			printf("%ld\t", words);
		if ((opts & 0x01) == 0x01)
			printf("%ld\t", bytes);
		if ((opts & 0x08) == 0x08)
			printf("%ld\t", chars);
		printf("%s\n", fname);
	}
}
