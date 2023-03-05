#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

int main(int argc, char *argv[]){
	if(argc != 1){
		fprintf(stdout, "Usage: ./singleshell");
		return 1;
	}
		
	fprintf(stdout, "Execute: ");
	/* Get command for code to run */
	char input[BUFSIZ];
	int i, spaces=1;
	fgets(input, BUFSIZ, stdin);
	/* Count number of spaces */
	for(i=0;i<strlen(input);i++){
		spaces += isspace(input[i]);
	}
	char *args[spaces];
	/* split input into arguments */
	for(i=0;i<spaces;i++){
		if(i==0)
			args[i] = strtok(input, " ");
		else
			args[i] = strtok(NULL, " \n");
	}

	int rc = fork();
	if (rc < 0){
		fprintf(stderr, "fork failed\n");
		exit(1);
	}
	else if (rc == 0){
		/* Execute command */
		fprintf(stdout, "Executing: %s\n", args[0]);
		
		/* Output results */
		execvp(args[0], args);

		fprintf(stdout, "Execution complete!\n");
	}
	else{
		// parent(check control-C)
	}

	return 0;
}
