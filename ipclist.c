/* Generic linked list implemenation all all three ipc resources */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <pwd.h>

#include "sysv_ipc.h"
#include "ipclist.h"

/* Function prototype declaration */
static Ipclist * create_node(int id, const void *ipc_ds, Listtype type);
static void display_shm(int shmid, struct shmid_ds *shm);
static void display_sem(int semid, struct semid_ds *sem);
static void display_msq(int msqid, struct msqid_ds *msq);
static int remove_shm(int shmid, struct shmid_ds *shm, int noauth);
static int remove_sem(int semid, struct semid_ds *sem, int noauth);
static int remove_msq(int msqid, struct msqid_ds *msq, int noauth);
static char *getname(uid_t uid);

static Ipclist * create_node(int id, const void * ipc_ds, Listtype type)
{
    struct shmid_ds *shmnode = NULL;
    struct semid_ds *semnode = NULL;
    struct msqid_ds *msgnode = NULL;
    Ipclist *newnode = NULL;
    
    newnode = malloc(sizeof(Ipclist));
    if (newnode == NULL) {
        perror("malloc");
        exit(1);
    }

    if (type = SHM_TYPE) {
        shmnode = malloc(sizeof(struct shmid_ds));
        memcpy(shmnode, ipc_ds, sizeof(struct shmid_ds));
        newnode->data = (void *)shmnode;
    }
    else if(type == SEM_TYPE) {
        semnode = malloc(sizeof(struct semid_ds));
        memcpy(semnode, ipc_ds, sizeof(struct semid_ds));
        newnode->data = (void *)semnode;
    }
    else {
        msgnode = malloc(sizeof(struct msqid_ds));
        memcpy(msgnode, ipc_ds, sizeof(struct msqid_ds));
        newnode->data = (void *)msgnode;
    }
    newnode->ipcid = id;
    newnode->next = NULL;
    return newnode;
}


void addto_list(int id, const void * ipc_ds, Listtype type , Ipclist **list_start, Ipclist **list_end)
{
       Ipclist *newnode = NULL;
       
       newnode = create_node(id, ipc_ds, type);
       
       if(*list_start == NULL) {
           *list_start = newnode;
           *list_end = newnode;
       }
       else {
           (*list_end)->next = newnode;
           *list_end = newnode;
       }
        return;
}

static char *getname(uid_t uid)
{
	struct passwd * user_entry;
	user_entry = getpwuid(uid);
	return user_entry->pw_name;
}

static void display_shm(int shmid, struct shmid_ds *shm)
{
	char *			user;
	key_t			key = shm->shm_perm.__key;
	unsigned short	perm = shm->shm_perm.mode & 511; //9 least significant bit for mode

	user = getname(shm->shm_perm.uid); 
	
	printf("0x%08x	%d		%zd	   %d	   %s	  %o	%d	%d\n", key, shmid, shm->shm_segsz, 
				(int)shm->shm_nattch, user, perm, (int)shm->shm_cpid, (int)shm->shm_lpid);	
}

static void display_sem(int semid, struct semid_ds *sem)
{
    printf("%d      0x%x        %d\n", 
                semid, sem->sem_perm.__key, (int)sem->sem_nsems);
}

static void display_msq(int msqid, struct msqid_ds *msq)
{
    printf("%d      0x%x        %d\n", 
                msqid, msq->msg_perm.__key, (int)msq->msg_qnum);
}

void display_list(Listtype type, Ipclist *list)
{
    struct shmid_ds *shmnode = NULL;
    struct semid_ds *semnode = NULL;
    struct msqid_ds *msqnode = NULL;

    while (list != NULL)
    {
        if (type == SHM_TYPE) {
            shmnode = list->data;
            display_shm(list->ipcid, shmnode);
        }
        else if(type == SEM_TYPE) {
            semnode = list->data;
            display_sem(list->ipcid, semnode);
        }
        else {
            msqnode = list->data;
            display_msq(list->ipcid, msqnode);
        }
        list = list->next;
    }
}

static int remove_shm(int shmid, struct shmid_ds *shm, int noauth)
{
    char yn;
    if (!noauth) {
        printf("Do you want to remove  shared memory id - %d\n \t(y/n)? ", shmid);
        scanf(" %c", &yn);
        if (yn != 'y') {
            printf("do not remove shm\n");
            return 1;
        }

    }
    printf("remove shm\n");
    return 0;
}

static int remove_sem(int semid, struct semid_ds *sem, int noauth)
{
    char yn = 0;
    if (!noauth) {
        printf("Do you want to remove semaphore id - %d\n", semid);
        scanf("%c", &yn);
        if (yn != 'y' || yn != 'Y')
            return 1;
    }
    printf("remove sem\n");
    return 0;
}

static int remove_msq(int msqid, struct msqid_ds *msq, int noauth)
{
    char yn = 0;
    if (!noauth) {
        printf("Do you want to remove message queue id - %d\n", msqid);
        scanf("%c", &yn);
        if (yn != 'y' || yn != 'Y')
            return 1;
    }
    printf("remove msq\n");
    return 0;
}

void list_remove(Ipclist *list, const Cmdarg *cmdOpts, Listtype type)
{
    struct shmid_ds *shm = NULL;
    struct semid_ds *sem = NULL;
    struct msqid_ds *msq = NULL;
    int noauth = 0;
    Ipclist *delnode = NULL;
    
    noauth = cmdOpts->opts & OPTION_NOAUTH;
    
    while (list != NULL)
    {
        if (type == SHM_TYPE) {
            shm = list->data;
            remove_shm(list->ipcid, shm, noauth);
        }
        else if (type == SEM_TYPE) {
            sem = list->data;
            remove_sem(list->ipcid, sem, noauth);
        }
        else {
            msq = list->data;
            remove_msq(list->ipcid, msq, noauth);
        }
        delnode = list;
        list = list->next;
        free(delnode->data);
        free(delnode);
    }
}
