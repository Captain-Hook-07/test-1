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

    
    int choice=0;
    printf("Enter 1 to search by id \nEnter 2 to search by name \n");
    printf("Enter your choice - ");
    scanf("%d",&choice);
    char protocol[500];
    if(choice==1)
    {
        int input=0;
        printf("\nEnter the id = ");
        scanf("%d",&input);
        char temp[100];
        sprintf(temp, "%d", input);
        //protocol="00001001."+temp+".00000011";
        strcat(protocol,"00001001.");
        strcat(protocol,temp);
        strcat(protocol,".00000011");
    }
    else if(choice==2)
    {
        char input[100];
        printf("\nEnter the name = ");
        scanf("%s",input);
        //protocol="0000001."+input+".00000011";
        strcat(protocol,"0000001.");
        strcat(protocol,input);
        strcat(protocol,".00000011");
    }
    else
    {
        printf("Wrong choice !!");
        exit(1);
    }

    n=write(sockfd,&protocol,sizeof(char)*500);
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
    printf("Received Protocol = %s\n",arr);
    char *token=strtok(arr,".");
    printf("Output: %s\n",token);
        

        
    

    close(sockfd);
    return 0;


}