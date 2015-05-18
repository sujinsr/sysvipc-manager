#ifndef IPCMANAGER_H
#define IPCMANAGER_H

#define OPTION_SHM      0x0001      /* Process only Shared memory IPC */
#define OPTION_SEM      0x0002      /* Process only Semaphore IPC */
#define OPTION_MSG      0x0004      /* Process only Message que IPC */
#define OPTION_ALL      0x0008      /* Process on all 3 IPC */
#define OPTION_DAYS     0x0010      /* Reserved for future use */
#define OPTION_MANAGER  0x0020      /* Reserved for future use */
#define OPTION_NOAUTH   0x0040      /* No authentication requried when delete IPC */

typedef struct {
    unsigned int    opts;
    int             days;
} Cmdarg;

#endif