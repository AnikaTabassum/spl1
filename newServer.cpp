#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<sys/types.h>
#include<sys/socket.h>
#include<fstream>
#include<netinet/in.h>
#include <unistd.h>
using namespace std;

int main()
{
    //create a socket
    int network_socket;
    network_socket = socket(AF_INET, SOCK_STREAM, 0);   //socket(int domain, int type, int protocol)

    // specify an address for two socket

    struct sockaddr_in server_address; //declaring the stucture of theaddress
    server_address.sin_family= AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr= INADDR_ANY;

    int connection_status= connect(network_socket, (struct sockaddr *)&server_address, sizeof(server_address)); //

    if(connection_status==-1)
        printf("Error\n");
        int socket(int domain, int type, int protocol);

      
		 char fileS[12];
		 int tests[12];
		recv(network_socket, &fileS, sizeof(fileS),0);  
		
		/*for(int i=0;fileS[i]!='\0';i++)
		{
			cout<<fileS[i];
		}*/
		
      		int fileSize=0;
      		int z=0;
		if((fileS[0]=='S'||fileS[0]=='s')&&(fileS[1]=='I'||fileS[1]=='i')&&
      	(fileS[2]=='Z'||fileS[2]=='z')&&(fileS[3]=='E'||fileS[3]=='e'))
      	{
      		for(int i=4;fileS[i]!='\0';i++)
			{
				tests[z]=(char)fileS[i]-'0';
				
    			fileSize= 10 *fileSize + tests[z];
				//cout<<tests[z];
				//cout<<fileS[i];
				//y=i;
				z++;
				//cout<<i<<endl;
			}
      	}
      	//cout<<"k"<<k<<endl;
      	//cout<<y<<endl;
      	for(int i=0;i<z;i++)
		{
			cout<<tests[i];
		}
		cout<<endl;
        char server_response [fileSize]; //buffer
       // recv(network_socket, &tests, sizeof(tests),0);  
       
        recv(network_socket, &server_response, sizeof(server_response),0);  //ssize_t recv(int socket, void *buffer, size_t length, int flags);
       
       
        ofstream oFile;
		oFile.open("o122o.jpg",ios::binary);
        int i=0;
		for(i=0;i<fileSize;i++)
		{
			
			char ch;
			ch=server_response[i];
			
			oFile<<ch;
		}
		//cout<<"dhukinai"<<endl;
    	oFile.close();
	       // printf("%s", server_response);


        
         //int network_socket;
    	//network_socket = socket(AF_INET, SOCK_STREAM, 0); 
		for(int i=0;i<4;i++)
		{
			cout<<fileS[i];
		}
		
		 char weak[4];
		
    	recv(network_socket, &weak, sizeof(weak),0);  
		for(int p=0;p<4;p++)
		{
			cout<<"lol "<<weak[p];
		}
		 cout<<"sadfsdf"<<endl;
		 
        close(network_socket);
		
    return 0;
}
