#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>

int usage(int input){
	fprintf(stdout, "Usage: ./bitflip inputFile\n
			-help: call usage\n
			-o XXX: overrides file name to write where XXX is output file name to use also override appending of extension\n
			-maxsize XXX: override max size of bytes that can be written\n
			-bfr: Reverse order of bytes and bit-flip the bits in the file with .bfr extension\n
			-r: Reverse order of bytes in file without bit-flip and use extension of .r\n
			\n-bfr and -r cannot be used together\n");
	return input;
}

int main(int argc, char *argv[]){
	int argind = 1;
	char* path = '';
	char* output = '';
	/* Input/Default arguments */
	int maxsize = 25000;
	int rExtension = 0;
	int bfrExtension = 0;

	/* Parse command line arguments */
	while (argind < argc && strlen(argv[argind]) > 1){
		char * arg = argv[argind++];
		if(arg[0] == '-'){
			switch (arg[1]){
				case 'h':
					return usage(0);
					break;
				case 'm':
					maxsize = atoi(arg);
					arg = argv[argind++];
					break;
				case 'o':
					arg = argv[argind++];
					output = strdup(arg); // updating output file
					break;
				case 'r':
					rExtension = 1; // set r extension
					break;
				case 'b':
					bfrExtension = 1; // set bfr extension
					break;
				default:
					return usage(1);
					break;
			}
		}
		else{
			path = strdup(arg);
			arg = argv[argind++];
			if (path == '\0')
				usage(1);
		}
	}


	struct stat s;
	if (stat(path, &s) < 0){
		fprintf(stderr, "%s\n", strerror(errno));
		return 1;
	}
	
	if(s.st_size > maxsize){
		fprintf(stdout, "Error: File is over %d bytes (file size was %lu).\n", maxsize, s.st_size);
		return 1;
	}
	
	fprintf(stdout, "Input: %s was %lu bytes", path, s.st_size);

	/* Open file and create buffer*/
	FILE *stream = fopen(path, "r");
	char buffer[BUFSIZ];
	
	/* Read contents of file */
	fread(buffer, 1, BUFSIZ, stream);
	fclose(stream);
	
	/* Parsing contents of file */
	int count = 0;
	
	
	/* obtain output file path*/
	if(output == '\0'){
		output = strdup(path);	
	}

	if(rExtension == 1){
		strncat(output, ".r", 2);
	}
	else if (bfrExtension == 1){
		strncat(output, ".bfr", 4);
	}
	else {
		strncat(output, ".bf", 3);
	}
	
	/* write content to output file */
	stream = fopen(output, "w");
	fprintf(stream, "%s\n", XXX);
	fclose(output);
	fprintf(stdout, "Output: %s was output successfully");
	return 0;
}
