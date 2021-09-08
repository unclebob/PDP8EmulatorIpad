/*
Simple utility to translate a binary file, character by character
into lines composed of three octal digits. 

So a file that contains "ABC" 
will be translated to: 101\n102\n103\n

use -t for text files.  It will add \r before each \n

usage: topt [-t] <infile >outfile

Remember that paper tapes must have a .txt extension.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

void putCharInOctal(int c) {
	putchar('0'+((c>>6)&7));
	putchar('0'+((c>>3)&7));
	putchar('0'+(c&7));
	putchar('\n');
}

void leader(int n) {
	for (int i=0; i<n; i++)	
		putCharInOctal(0200);
}

int main(int ac, char** av) {
	int textFlag = 0;
	
	if (ac > 2) {
		fprintf(stderr, "usage topt [-t] <infile >outfile\n");
		exit(1);
	}
	
	av++;

	if (strcmp(*av, "-t") == 0) {
		fprintf(stderr, "text mode.\n");
		textFlag = 1;
	}
	
	leader(10);

	int c;
	while ((c = getchar()) != EOF) {
		if (textFlag) {
			c|=0200;
			if (c >= 0341 && c <= 0372) // lower case
				c-=040; //toupper
			if (c == 0212) //lf
				putCharInOctal(0215);//cr
		}
		putCharInOctal(c);
	}
		
	leader(10);
}


