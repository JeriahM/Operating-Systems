#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>

void usage(){
	fprintf(stdout, "Usage: ./bitflip inputFile\n
			-help: call usage\n
			-o XXX: overrides file name to write where XXX is output file name to use also override appending of extension\n
			-maxsize XXX: override max size of bytes that can be written\n
			-bfr: Reverse order of bytes and bit-flip the bits in the file with .bfr extension\n
			-r: Reverse order of bytes in file without bit-flip and use extension of .r\n
			\n-bfr and -r cannot be used together\n");
	return 1;
}

int main(int argc, char *argv[]){
	if(argc != 3){
		fprintf(stdout, "Usage: ./bytecheck file.txt byteValue\n");
		return 1;
	}
	
	char* path = argv[1];
	//char* byte = argv[2];
	struct stat s;
	if (stat(path, &s) < 0){
		fprintf(stderr, "%s\n", strerror(errno));
		return 1;
	}
	
	if(s.st_size > 25000){
		fprintf(stdout, "Error: File is over 25 kB (file size was %lu).\n", s.st_size);
		return 1;
	}

	/* Open file and create buffer*/
	FILE *stream = fopen(path, "r");
	char buffer[BUFSIZ];
	
	/* Read contents of file */
	fread(buffer, 1, BUFSIZ, stream);
	
	/* Parsing contents of file */
	int count = 0;
	
	

	fclose(stream);
	fprintf(stdout, "%d\n", count);
	return 0;
}
