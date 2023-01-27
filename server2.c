#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>//used to read,write and close
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

#define PORT1 6666


int main()
{
    //there will be 2 parameters
    //1st the file name and the 2nd is the port number
    

    int sockfd,newsockfd,portno,n;
    char buffer;

    struct sockaddr_in serv_addr,serv_addr1,cli_addr,cli_addr1; // to store the internet address of the client and the server 
    socklen_t clilen; //32 bit data type 

    sockfd = socket(AF_INET,SOCK_STREAM,0);

    if(sockfd<0)
    {
        printf("Error opening socket");
        exit(1);
    }
    bzero((char *) &serv_addr,sizeof(serv_addr)); //used to clear the contents of the serv_addr
    portno = PORT1;
   

    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=INADDR_ANY;
    serv_addr.sin_port=htons(portno);

    

    if(bind(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr))<0)
    {
        printf("Binding falied.");
        exit(1);
    }

    

    listen(sockfd,5);// maximum limit of clients that can connect to the server
    

    clilen=sizeof(cli_addr);
    

    newsockfd=accept(sockfd,(struct sockaddr *)&cli_addr,&clilen);
    

    if(newsockfd<0)
    {
        printf("Error on accept.");
        exit(1);
    }

    char protocol[500];
        
    n=read(newsockfd,&protocol,sizeof(char)*500); //the client must have a coprresponding write function.
    if(n<0)
    {
        printf("Error on reading");
        exit(1);
    }

    printf("\nReceived protocol = %s\n",protocol);

    FILE* fp;
    char buff[500];
    char inp[100];
    char ans[500];
    int k=0;
    fp=fopen("file.txt","r");

    
    char *token=strtok(protocol,".");
    if(strcmp(token,"0000001")==0)
    {
        token=strtok(NULL,".");
        while(fscanf(fp,"%s %s\n",inp,buff)!=EOF)
        {
            if(strcmp(buff,token)==0)
            {
                k=1;
                for(int i=0;i<100;i++) ans[i]=inp[i];
                break;
            }
        }
    }
    else
    {
        token=strtok(NULL,".");
        while(fscanf(fp,"%s %s\n",inp,buff)!=EOF)
        {
            if(strcmp(inp,token)==0)
            {
                k=1;
                for(int i=0;i<500;i++) ans[i]=buff[i];
                break;
            }
        }
    }
    if(k==0)
    {
        strcpy(ans,"Address not found.00000011");
    }
    else
    {
        strcat(ans,".00000011");
    }   
    n=write(newsockfd,&ans,sizeof(char)*500);
    
    if(n<0)
    {
        printf("Error on writitng");
        exit(1);
    }
        
       
    
    close(newsockfd);
    close(sockfd);
    

    return 0;
}