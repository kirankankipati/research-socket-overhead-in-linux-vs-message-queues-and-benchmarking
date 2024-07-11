/* message_Q_recv.c
 * The Linux Channel
 * Author: Kiran Kankipati
 * Updated: 11-Jul-2017
 */

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAXBUF 8024

// message structure
typedef struct __msgbuf_ { long mtype; char buf[MAXBUF]; } message_buf;


void main()
{	 int len;
    int msqid;
    key_t key = 1234;
    message_buf buf;
    
	 uint64_t received_bytes=0;
	 struct timeval start, end;
  	 gettimeofday(&start, NULL);
  	 if((msqid = msgget(key, 0666)) < 0) { printf("msgget error !\n"); return; }
    while(1)
    { len = msgrcv(msqid, &buf, MAXBUF, 1, 0);
		if(len>0)
		{ received_bytes+=len;
			gettimeofday(&end, NULL);
			if((end.tv_sec - start.tv_sec)>=1) 
			{ 	printf("received_bytes: %lu MBs\n", (received_bytes/1024)/1024);
				received_bytes=0;
				gettimeofday(&start, NULL);
			}
		}
    }
}
