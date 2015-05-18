
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>


int main(int argc, char *argv)
{
	int i, msqid, noMsq;
	struct msqid_ds msqstru;
	
	noMsq = msgctl(0, MSG_INFO, &msqstru);
	perror("semctl");

	for (i=1; i <= noMsq; i++)
	{
		//memset(&buf, 0, sizeof(buf));
		msqid = msgctl(i, MSG_STAT, &msqstru);
		printf("shm id :%d\n", msqid);
	}

	printf("shm index : %d\n", noMsq);
	
	
	return 0;
}
