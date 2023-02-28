#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main(int argc, char *argv[]){
	if(argc != 1){
		fprintf(stdout, "Usage: ./singleshell");
		return 1;
	}
		
	fprintf(stdout, "Execute: ");
	/* Get command for code to run */
	char command[BUFSIZ];
	fgets(command, BUFSIZ, stdin);

	int rc = fork();
	if (rc < 0){
		fprintf(stderr, "fork failed\n");
		exit(1);
	}
	else if (rc == 0){
		/* Execute command */
		fprintf(stdout, "Executing: %s\n", command);
		
		/* Output results */
		execvp(command);

		fprintf(stdout, "Execution complete!\n");
	}
	else{
		// parent(check control-C)
	}

	return 0;
}
