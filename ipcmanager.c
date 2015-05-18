#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "ipcmanager.h"
#include "sysv_ipc.h"

/* Function prototype declartion */
void usage();

int main(int argc, char **argv)
{
     uid_t          uid;
     unsigned int   options;
     Cmdarg         cmdOptions = {0, 0};
     int            c = 0;

    while ( (c = getopt(argc, argv, "S:M:d:a")) != -1)
    {
        switch (c)
        {
            case 'M':
                cmdOptions.opts |= OPTION_MANAGER;
            case 'S':
                if ( !strcmp(optarg, "shm") )
                    cmdOptions.opts |= OPTION_SHM;
                else if ( !strcmp(optarg, "sem") )
                    cmdOptions.opts |= OPTION_SEM;
                else if ( !strcmp(optarg, "msq") )
                    cmdOptions.opts |= OPTION_MSG;
                else
                    cmdOptions.opts |= OPTION_ALL;
                break;
                
            case 'd':
                cmdOptions.opts |= OPTION_DAYS;
                cmdOptions.days = atoi(optarg);
                break;
                
            case 'a':
                cmdOptions.opts |= OPTION_NOAUTH;
                break;
                
            case 'h':
            case '?':
                usage();
                break;
                
            default:
                printf("wrong command line option, exit....\n");
                return 1;
        }
        
    }

    read_sysvipc(&cmdOptions);
    display_sysvipc(&cmdOptions);
    
#if 0
    /* check program is running in root user. This is a bad idea even to clean
     * ipc resource in previlege mode give more secure */
    if ( getuid() ) {
        fprintf(stderr, "Run program as root user.\n");
        return 1;
    }
    printf("root user.\n");
#endif

    if (cmdOptions.opts & OPTION_MANAGER) {
        remove_sysvipc(&cmdOptions);
    }
    
    return 0;
}


void usage()
{
    
}