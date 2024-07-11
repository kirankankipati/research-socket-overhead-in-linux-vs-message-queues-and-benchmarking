/* udp_socket_server.c
 * The Linux Channel
 * Author: Kiran Kankipati
 * Updated: 21-Jun-2017
 */

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/time.h>

#define MAXBUF 10240

int main()
{ int sockfd, len, i;
  unsigned char buf[MAXBUF];
  struct sockaddr_in udp_server_addr;
  struct sockaddr_in udp_client_addr;
  struct sockaddr_storage server_storage;
  socklen_t addr_size, client_addr_size;

  sockfd = socket(PF_INET, SOCK_DGRAM, 0); // create a UDP socket
  if(sockfd<=0) { printf("socket error !\n"); return 0; }

  /* configure settings to register UDP server */
  udp_server_addr.sin_family = AF_INET;
  udp_server_addr.sin_port = htons(6800); // server port
  udp_server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // local-host
  memset(udp_server_addr.sin_zero, '\0', sizeof udp_server_addr.sin_zero);  
  bind(sockfd, (struct sockaddr *) &udp_server_addr, sizeof(udp_server_addr)); // bind the socket
  addr_size = sizeof server_storage;
 
  uint64_t received_bytes=0;
  struct timeval start, end;
  gettimeofday(&start, NULL); 
  while(1)
  {
  	len = recvfrom(sockfd, buf, MAXBUF, 0, (struct sockaddr *)&server_storage, &addr_size); //receive data from client 
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
  //printf("Received from server: %d bytes\n", len); for(i=0;i<len;i++) { printf("%02x ", buf[i]); } printf("\n"); //print received data dump
	
  //memset(buf, 0xcd, MAXBUF); // set the entire buffer with 0xcd (i.e 1100 1101 binary)

  //sendto(sockfd, buf, MAXBUF, 0, (struct sockaddr *)&server_storage, addr_size); //send the data to client

  return 0;
}
