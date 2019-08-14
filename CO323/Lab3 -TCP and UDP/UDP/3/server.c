#include <sys/socket.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <stdio.h> 
#include <stdlib.h> 

void capitalize(char* mesg){
	int i=0;

  
       
        for(int i = 0; i < strlen(mesg); i++) {
        	mesg[i] = toupper((unsigned char) mesg[i]);
        }

}



int main(int argc, char**argv) 
{ 
	int sockfd,n;
	int m=0; 
	struct sockaddr_in servaddr, cliaddr; 
	socklen_t len; 
	char mesg[1000]; 
	char replyMsg[1000]; 
	char* ack ="ack";

	sockfd=socket(AF_INET,SOCK_DGRAM,0); 

	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY); 
	servaddr.sin_port=htons(32000); 
	bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr)); 

	
		len = sizeof(cliaddr); 
		n = recvfrom(sockfd,mesg,1000,0,(struct sockaddr *)&cliaddr,&len); 
		sendto(sockfd,ack,3,0,(struct sockaddr *)&cliaddr,sizeof(cliaddr)); 
		sscanf(mesg, "%d", &m); 
		
		while(m){
			n = recvfrom(sockfd,mesg,1000,0,(struct sockaddr *)&cliaddr,&len); 
			capitalize(mesg);
			sendto(sockfd,mesg,1000,0,(struct sockaddr *)&cliaddr,sizeof(cliaddr)); 
			mesg[n] = 0; 
			printf("Received: %s\n",mesg);	
			m--;
		}
	
	return 0; 
}
