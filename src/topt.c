/*
 * Translates every byte in the program's input to
 * a printable line of three octal digits.  Outputs
 * to stdout or a named file given with the `-o`
 * option.  Default input is stdin.  If multiple
 * named files are given, they are concatenated into
 * a single output "tape".
 *
 * For example, a file that contains "ABC" will be
 * translated to "101\n102\n103\n".
 *
 * usage: topt [-t] [-o outfile] [file...]
 *
 * Use `-t` for text files to add a carriage return before
 * each newline and set the high bit in each output byte.
 *
 * Remember that the emulator requires that output files
 * have a `.txt` extension.
 */

#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef unsigned char byte;

const int HIGH_BIT = 0200;

static void leader(int n, FILE *outFile);
static void convertFileToOctal(FILE *inFile, bool textMode, FILE *outFile);
static void putByteInOctal(byte b, FILE *outFile);
static void usage(void);

int main(int argc, char *argv[]) {
	int c;
	bool textFlag = false;
	char *inFileName, *outFileName;
	FILE *inFile, *outFile = stdout;

	while ((c = getopt(argc, argv, "to:")) != -1) {
		switch (c) {
		case 'o':
			outFileName = optarg;
			outFile = fopen(outFileName, "w");
			if (outFile == NULL) {
				fprintf(stderr,
				    "Error opening '%s' for writing: %s\n",
				    outFileName, strerror(errno));
				return EXIT_FAILURE;
			}
		case 't':
			fprintf(stderr, "text mode.\n");
			textFlag = true;
			break;
		default:
			usage();
			break;
		}
	}
	argc -= optind;
	argv += optind;

	leader(10, outFile);
	if (argc == 0)
		convertFileToOctal(stdin, textFlag, outFile);
	else
		while ((inFileName = *argv++) != NULL) {
			if (strcmp(inFileName, "-") == 0) {
				convertFileToOctal(stdin, textFlag, outFile);
				continue;
			}
			inFile = fopen(inFileName, "r");
			if (inFile == NULL) {
				fprintf(stderr,
				    "Error opening '%s' for reading: %s\n",
				    inFileName, strerror(errno));
				fclose(outFile);
				return EXIT_FAILURE;
			}
			convertFileToOctal(inFile, textFlag, outFile);
			fclose(inFile);
		}
	leader(10, outFile);
	fclose(outFile);

	return EXIT_SUCCESS;
}

static void leader(int n, FILE *outFile) {
	for (int i = 0; i < n; i++)
		putByteInOctal(HIGH_BIT, outFile);
}

static void convertFileToOctal(FILE *inFile, bool textFlag, FILE *outFile) {
	const int NL = 012;	// Newline
	const int FF = 014;	// Form feed (^L)
	const int CR = 015;	// Carriage return
	int c;

	while ((c = fgetc(inFile)) != EOF) {
		if (textFlag) {
			if (isascii(c) && islower(c))
				c = toupper(c);
			if (c == '~')
				c = FF;
			if (c == NL)
				putByteInOctal(CR | HIGH_BIT, outFile);
			c |= HIGH_BIT;
		}
		putByteInOctal(c, outFile);
	}
}

static void putByteInOctal(byte b, FILE *outFile) {
	fprintf(outFile, "%03o\n", b);
}

static void usage(void) {
	fprintf(stderr, "usage topt [-t] [-o outfile] [file...]\n");
	exit(EXIT_FAILURE);
}
