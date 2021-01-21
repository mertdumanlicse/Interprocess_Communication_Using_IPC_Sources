/*
     SERVER - receives messages from clients
 */
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "local.h"
#include <iostream>
#include <cstdio>
#include <ctype.h>
#include <stdlib.h>
using namespace std;
int
main(int argc, char *argv[ ]) {
  int     mid, n;
  MESSAGE msg;
  void    process_msg(char *, int);
  if (argc != 3) {
    cerr << "Usage: " << argv[0] << " msq_id &" << endl;
    return 1;
  }
  mid = atoi(argv[1]);
  while (1) {
    memset( msg.buffer, 0x0, BUFSIZ );
    if ((n=msgrcv(mid, &msg, BUFSIZ, SERVER, 0)) == -1 ) {
     perror("Server: msgrcv");
     return 2;
    } else if (n == 0) break;
int pidID[5];
int q;
for(q=0;q<5;q++){
pidID[q] = 0;
}
int count = 0;
int id;
id = msg.msg_fm;
while(count < 5){
if(pidID[count]==0){
pidID[count] = id;
id = 0;
}
count = count + 1;
}
char *pidnames[5];
int p;
for(p=0;p<5;p++){
pidnames[p] = "A";
}
int count2 = 0;
char name[20];
strcpy(name,msg.name);
int x;
while(count2 < 5){
x=strlen(pidnames[count2]);
if(x == 1){
pidnames[count2] = name;
strcpy(name,"A");
}
count2 = count2 + 1; 
}
int k = 0;
int index;
while(k < 5){
if(strcmp(msg.receivername,pidnames[k]) == 0 )
index = k;
k = k +1 ;}
int l = 0;
int index2;
while(l < 5){
if(strcmp(msg.name,pidnames[l]) == 0 )
index2 = l;
l = l +1 ;}

    msg.msg_to = pidID[index];
    msg.msg_fm = pidID[index2];
    n += sizeof(msg.msg_fm);
    if (msgsnd(mid, &msg, n, 0) == -1 ) {
      perror("Server: msgsnd");
      return 3;
    }
  }
  msgctl(mid, IPC_RMID, (struct msqid_ds *) 0 );
  exit(0);
}
