#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <ctype.h>

int usage(int input){
	fprintf(stdout, "Usage: ./bitflip inputFile\n");
	fprintf(stdout, "-help: call usage\n");
	fprintf(stdout, "-o XXX: overrides file name to write where XXX is output file name to use also override appending of extension\n");
	fprintf(stdout, "-maxsize XXX: override max size of bytes that can be written\n");
	return input;
}

int main(int argc, char *argv[]){
	int argind = 1;
	char* path;
	char* output;
	/* Input/Default arguments */
	int maxsize = 25000;
	int overrideExt = 0;

	/* Parse command line arguments */
	while (argind < argc && strlen(argv[argind]) > 1){
		char * arg = argv[argind++];
		if(arg[0] == '-'){
			switch (arg[1]){
				case 'h':
					return usage(0);
					break;
				case 'm':
					arg = argv[argind++];
					int i;
					for(i=0;i<strlen(arg);i++){
						if(!isdigit(arg[i])){
							fprintf(stdout, "Error: must be number behind -maxsize\n");
							return 1;
						}
					}
					maxsize = atoi(arg);
					break;
				case 'o':
					arg = argv[argind++];
					output = strdup(arg); // updating output file
					overrideExt = 1;
					break;
				default:
					return usage(1);
					break;
			}
		}
		else{
			path = strdup(arg);
			if (!path)
				usage(1);
		}
	}

	struct stat s;
	if (stat(path, &s) < 0){
		fprintf(stderr, "%s\n", strerror(errno));
		return 1;
	}
	
	if(s.st_size > maxsize){
		fprintf(stdout, "Error: File is over %d bytes (file size was %lu bytes).\n", maxsize, s.st_size);
		return 1;
	}
	
	fprintf(stdout, "Input: %s was %lu bytes\n", path, s.st_size);

	/* obtain output file path*/
	if(!output){
		output = strdup(path);	
	}

	if (!overrideExt){
		strcat(output, ".bf");
	}

	/* Check output path if exists*/
	if((stat(output, &s)) > 0){
		char overwrite[1];
		if(S_ISREG(s.st_mode)){
			fprintf(stdout, "The file being written to already exists as a file, want to overwrite?(y|n)\n");
			fscanf(stdin, "%c", overwrite);
			if (overwrite[1] == 'n'){
				return 0;
			}
		}
		else if (S_ISDIR(s.st_mode)){
			fprintf(stdout, "The file being written to already exists as a directory, want to overwrite?(y|n)\n");
			fscanf(stdin, "%c", overwrite);
			if (overwrite[1] == 'n'){
				return 0;
			}
		}
	}

	/* Open file and create buffer*/
	FILE *stream = fopen(path, "r");
	char buffer[BUFSIZ];
	
	/* Read contents of file */
	fread(buffer, 1, BUFSIZ, stream);
	fclose(stream);
	
	/* flipping contents of file */
	char byValue;
	char flip[BUFSIZ];
	int index;
	for(index=0;index<strlen(buffer);index++){
		byValue = buffer[index];
		byValue = byValue ^ 0xFF;
		flip[index] = byValue;
	}

	
	/* write content to output file */
	stream = fopen(output, "w");
	fprintf(stream, "%s\n", flip);
	fclose(stream);
	fprintf(stdout, "Output: %s was output successfully\n", output);
	return 0;
}
