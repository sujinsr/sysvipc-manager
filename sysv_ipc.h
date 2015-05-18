#ifndef SYSV_IPC_H
#define SYSV_IPC_H

#include "ipcmanager.h"

void read_sysvipc( const Cmdarg *cmdOpts);
void display_sysvipc( const Cmdarg *cmdOpts);
void remove_sysvipc( const Cmdarg *cmdOptions);


typedef enum _Listtype {
    SHM_TYPE = 1,
    SEM_TYPE,
    MSG_TYPE
} Listtype;

typedef struct _Ipclist {
    int             ipcid;
    void            *data;
    struct _Ipclist *next;
} Ipclist;

#endif