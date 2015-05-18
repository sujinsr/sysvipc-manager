#ifndef IPCLIST_H
#define IPCLIST_H

void addto_list(int, const void * , Listtype , Ipclist **, Ipclist **);
void display_list(Listtype type, Ipclist *list);
void list_remove(Ipclist *list, const Cmdarg *cmdOpts, Listtype type);


#endif
