#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define _GNU_SOURCE

int main(int argc, char *argv)
{

	struct  shminfo maxshm;
	struct shmid_ds buf;
	int i, j;
	int index = shmctl(0, SHM_INFO, &buf);
	perror("shmctl");

	for (i=1; i <= index; i++)
	{
		memset(&buf, 0, sizeof(buf));
		j = shmctl(i, SHM_STAT, &buf);
		printf("shm id :%d\n", j);
	}

	printf("shm index : %d\n", index);
	
	
	return 0;
}
