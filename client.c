#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>//used to read,write and close
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>//defines the hostent structure

#define PORT 6666


int main()
{
    int sockfd,portno,n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    
    portno=PORT;
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(sockfd<0)
    {
        printf("Error in opening socket");
        exit(1);
    }

    server = gethostbyname("127.0.0.1");
    if(server==NULL)
    {
        fprintf(stderr,"Error ,no such host");
    }

    bzero((char *) &serv_addr,sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr,server->h_length); //coppies n bytes from hostent to serv_addr
    serv_addr.sin_port=htons(portno);

    if(connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr))<0)
    {
        printf("Connection failed");
        exit(1);
    }

    
     int input=0;
     printf("Enter a number - ");
     scanf("%d",&input);

    n=write(sockfd,&input,sizeof(int));
    if(n<0)
    {
        printf("Error on writing");
        exit(1);
    }

    char arr[500];
    bzero(arr,500);
    n=read(sockfd,arr,500);
    if(n<0)
    {
        printf("Error on reading");
    }
    printf("Output: %s\n",arr);
        

        
    

    close(sockfd);
    return 0;


}