/*
  Simple utility to translate a paper tape file
  which is a file composed of three octal digits
  per line, to a standard text file.

  So a file that contains "101\n102\n103\n" 
  will be translated to: "ABC"
*/

#include <stdio.h>
#include <stdlib.h>

int main(int ac, char** av) {	
	if (ac != 1) {
		printf("usage p2txt <infile >outfile\n");
		exit(1);
	}
	
	av++;
	
	size_t size = 80;
	char *buffer = malloc(size);
	ssize_t nchars = 0;	
	while ((nchars = getline(&buffer, &size, stdin)) > 0) {
		if (nchars==4) {
		    char d1 = buffer[0] - 060;
			char d2 = buffer[1] - 060;
			char d3 = buffer[2] - 060;
			char c = (d1*0100 + d2*010 + d3) & 0177;
			if (c == 014) { // ^L -> ~
				putchar('\n');
				c = 0176; //~
			}
			if (c && c != 015) // skip nulls and CRs.  
				putchar(c);
		} else {
			printf("bad line encountered: %s\n", buffer);
		}
	}		
}


