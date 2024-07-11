/* message_Q_send.c
 * The Linux Channel
 * Author: Kiran Kankipati
 * Updated: 11-Jul-2017
 */

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>

#define MAXBUF 8024

// message structure
typedef struct __msgbuf_ { long mtype; char buf[MAXBUF]; } message_buf;

void main()
{
    int msqid;
    key_t key = 1234;
    message_buf buf;

	 buf.mtype = 1;
    if ((msqid = msgget(key, IPC_CREAT | 0666 )) < 0) { printf("msgget error !\n"); return; }

    memset(buf.buf, 0xab, MAXBUF); // set the entire buffer with 0xab (i.e 1010 1011 binary)

 	 while(1)
    {
    	msgsnd(msqid, &buf, MAXBUF, IPC_NOWAIT);
    }
}