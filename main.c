#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main() {
	int shmid;
	
	if ((shmid = shmget(0, 200, 0644 | IPC_CREAT)) == -1) {
		perror("shmget");
		exit(1);
	}
    printf("Shared mem seg created at %d\n", shmid);

    char * data;
    data = shmat(shmid, (void *)0, 0);
    if (data) {
        printf("just created\n");
    } else {
        printf("contents: %s\n", data);
    }
    
    char input[100];
    printf("Do you want to change the data in the segment? (y/n)\n");
    fgets(input, 200, stdin);
    if(input[0] == 'y') {  
        printf("What would u want to add? \n");
        fgets(input, 200, stdin);
        strcpy(data, input);
        printf("New data in segment: %s\n", data);
    } else {
        printf("Okay, you do not want to change anything\n");
    }

    printf("Do you want to delete the segment? (y/n)\n");
    fgets(input, 200, stdin);
    if(input[0] == 'y') {
        shmdt(data);
        shmctl(shmid, IPC_RMID, NULL);
        printf("Deleted!\n");
    } else {
        printf("Okay, you do not want to delete this segment\n");
    }

	return 0;
}
