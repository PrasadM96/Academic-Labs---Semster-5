#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int main(int argc, char**argv)
{
	int sockfd,n;
	struct sockaddr_in servaddr;
	char banner[] = "request";
	char buffer[1000];
	int size,i;
	int state=0;
	FILE *fptr;
    fptr = fopen("serverfile.txt", "a");//open the file for append
	
	if (argc != 2)
	{
	printf("usage: ./%s <IP address>\n",argv[0]);
	return -1;
	}
	
	/* socket to connect */
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	
	/* IP address information of the server to connect to */
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr=inet_addr(argv[1]);
	servaddr.sin_port=htons(32000);
	connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	
	
	sendto(sockfd,banner,strlen(banner),0, (struct sockaddr*)&servaddr,sizeof(servaddr)); //send the request string
	n=recvfrom(sockfd,buffer,10000,0,NULL,NULL);//resceive the file size
	buffer[n]=0;
    sscanf(buffer, "%d", &size); 
	printf("Received:%d\n",size);


	//check whether the size of the fileis round value or not
	int val;
	if(size/1000.0 >size/1000){
		val = (size/1000) +1;
	}else{
		val = (size/1000);
	}
	
	// receive the file content and append it to file
	for(i=0;i<val;i++){
		char buff[1000];
		n=recvfrom(sockfd,buff,1000,0,NULL,NULL);
		buff[n]=0;	
		//printf("%s\n",buff);
	    fprintf(fptr,"%s", buff);//write to file
	    state=1;
	}
	
	if(state==1)printf("file successfully received\n");
	
	fclose(fptr);//close the file
		
		
	
	return 0;
}
