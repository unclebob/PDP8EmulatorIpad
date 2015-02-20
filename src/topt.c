/*
  Simple utility to translate a binary file, character by character
  into lines composed of three octal digits. 

  So a file that contains "ABC" 
  will be translated to: 101\n102\n103\n
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

void putCharInOctal(int c, FILE* outFile) {
		fputc('0'+((c>>6)&7), outFile);
		fputc('0'+((c>>3)&7), outFile);
  	fputc('0'+(c&7), outFile);
    fputc('\n', outFile);
}

void leader(int n, FILE* outFile) {
	for (int i=0; i<n; i++)	
		putCharInOctal(0200, outFile);
}

int main(int ac, char** av) {
	int textFlag = 0;
	
	if (ac != 2 && ac != 3) {
		printf("usage topt [-t] file\n");
		exit(1);
	}
	
  av++;

  if (strcmp(*av, "-t") == 0) {
		printf("text mode.\n");
		textFlag = 1;
		av++;
	}
	
	FILE* inFile = fopen(*av, "r");
  char outFileName[100];
  bzero(outFileName, 100);
  strcpy(outFileName, *av);
  strcat(outFileName, ".txt");
  printf("Creating %s\n", outFileName);
  FILE* outFile = fopen(outFileName, "w");

	leader(10, outFile);

	int c;
  while ((c = fgetc(inFile)) != EOF) {
	if (textFlag) {
		c+=0200;
		if (c == 0212)
			putCharInOctal(0215, outFile);
	  }
		putCharInOctal(c, outFile);
	}
		
	leader(10, outFile);
	fclose(inFile);
	fclose(outFile);
}


