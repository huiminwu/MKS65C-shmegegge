#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main() {
	key_t key = 12345678910;
	int shmid;
	
	if ((shmid = shmget(key, 200, 0644 | IPC_CREAT)) == -1) {
		perror("shmget");
		exit(1);
	}
	return 0;
}
