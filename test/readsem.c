
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

           union semun {
               int              val;    /* Value for SETVAL */
               struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
               unsigned short  *array;  /* Array for GETALL, SETALL */
               struct seminfo  *__buf;  /* Buffer for IPC_INFO
                                           (Linux-specific) */
           };



int main(int argc, char *argv)
{
	int i, semid, noSem;
	struct semid_ds semstru;
	union semun semopts;
	semopts.buf = &semstru;
	
	noSem = semctl(0, 0, SEM_INFO, semopts);
	perror("semctl");

	for (i=1; i <= noSem; i++)
	{
		//memset(&buf, 0, sizeof(buf));
		semid = semctl(i, 0, SEM_STAT, semopts);
		printf("shm id :%d\n", semid);
	}

	printf("shm index : %d\n", noSem);
	
	
	return 0;
}
