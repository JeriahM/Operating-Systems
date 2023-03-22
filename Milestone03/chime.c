#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

char g_bKeepLooping = 1;

#define MAX_THREADS 5

struct ChimeThreadInfo
{
    int        nIndex;
    float      fChimeInterval;
    char       bIsValid;
    pthread_t  ThreadID;
};

struct ChimeThreadInfo  TheThreads[MAX_THREADS];

void * ThreadChime (void * pData)
{
    struct ChimeThreadInfo  * pThreadInfo;

    /* Which chime are we? */
    pThreadInfo = (struct ChimeThreadInfo *) pData;

    while(g_bKeepLooping)
    {
        sleep(pThreadInfo->fChimeInterval);
        printf("Ding - Chime %d with an interval of %.1f s!\n", pThreadInfo->nIndex, pThreadInfo->fChimeInterval);
    }

    return NULL;
}

#define BUFFER_SIZE 1024

int main (int argc, char *argv[])
{
    char szBuffer[BUFFER_SIZE];

    /* Set all of the thread information to be invalid (none allocated) */
    for(int j=0; j<MAX_THREADS; j++)
    {
        TheThreads[j].bIsValid = 0;
    }

    while(1)
    {
        /* Prompt and flush to stdout */
        printf("CHIME>");
        fflush(stdout);

        /* Wait for user input via fgets */
        fgets(szBuffer, BUFFER_SIZE, stdin);
		char *arg = strtok(szBuffer, " ");

        /* If the command is quit - join any active threads and finish up gracefully */
		if(strcmp(arg, "exit\n")==0){
    		for(int j=0; j<MAX_THREADS; j++){
				if(TheThreads[j].bIsValid != 0){
					printf("Joining Chime %d (Thread %d)\n", j, TheThreads[threads].ThreadID);
					pthread_join(&TheThreads[j]->ThreadID, NULL);
					printf("Join Complete for Chime %d\n", j);
				}
    		}

			printf("Exit chime program ...\n");
			return 0;
		}
        /* If the command is chime, the second argument is the chime number (integer) and the 
           third number is the new interval (floating point). If necessary, start the thread
           as needed */
		else if(strcmp(arg, "chime")==0){
			int thread = atoi(strtok(NULL, " "));
			if(thread<0 || thread>4){
				printf("Cannot adjust chime %d, out of range\n", thread);
				return 1;
			}
			float interval = 0; //default value
			interval = atof(strtok(NULL, " "));
			if(interval<0){
				printf("Cannot have interval of negative time\n");
				return 1;
			}
			

			if(TheThreads[thread].bIsValid == 0){
				TheThreads[thread].bIsValid = 1;
				TheThreads[thread].nIndex = thread;
				TheThreads[thread].fChimeInterval = interval;
				//TheThreads[thread].ThreadID = ;
				printf("Starting thread %d for chime %d, interval of %.1f s\n", 
					TheThreads[thread].ThreadID, TheThreads[thread].nIndex, TheThreads[thread].fChimeInterval);
				printf("test\n");
				//pthread_create(&TheThreads[thread].ThreadID, NULL, ThreadChime, (void *) TheThreads[thread].ThreadID);
			}else {
				TheThreads[thread].fChimeInterval = interval;
				printf("Adjusting chime %d to have an interval of %.1f s\n", 
					TheThreads[thread].nIndex, TheThreads[thread].fChimeInterval);
				//pthread_create(&TheThreads[thread], NULL, ThreadChime, TheThreads[thread]);
			}
		}
        /* Optionally, provide appropriate protection against changing the
           chime interval and reading it in a thread at the same time by using a
           mutex.  Note that it is not strictly necessary to do that */
		else{
			printf("Unknown command: %s\n", arg);
			return 1;
		}
	}
}

