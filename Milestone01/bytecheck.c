#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>

int main(int argc, char *argv[]){
	if(argc != 3){
		fprintf(stdout, "Usage: ./bytecheck file.txt byteValue\n");
		return 1;
	}
	
	char* path = argv[1];
	char* byte = argv[2];
	struct stat s;
	if (stat(path, &s) < 0){
		fprintf(stderr, "%s\n", strerror(errno));
		return 1;
	}
	
	if(s.st_size > 25000){
		fprintf(stdout, "Error: File is over 25 kB (file size was %lu).\n", s.st_size);
	}

	/* Open file and create buffer*/
	FILE *stream = fopen(path, "r");
	char buffer[BUFSIZ];
	
	/* Read contents of file */
	fread(buffer, 1, BUFSIZ, stream);
	
	/* Parsing contents of file */
	int count = 0;
	while((buffer = strchr(buffer, byte)) != NULL){
	/* Searches buffer for byte and returns char * to first instance where byte occurs,
	 * if byte isn't in buffer it returns null
	 * */
		count++;
	}
	fclose(stream);
	fprintf(stdout, "%s, %d\n", byte, count);
	return 0;
}
