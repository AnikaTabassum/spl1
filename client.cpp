#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<sys/types.h>
#include<sys/socket.h>
#include<fstream>
#include<netinet/in.h>

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

        char server_response [416415]; //buffer

        recv(network_socket, &server_response, sizeof(server_response),0);  //ssize_t recv(int socket, void *buffer, size_t length, int flags);

          ofstream oFile;
		oFile.open("too.jpg",ios::binary);
        int i=0;
		for(i=0;i<48258;i++)
		{

			char ch;
			ch=server_response[i];

			oFile<<ch;
		}
		//cout<<"dhukinai"<<endl;
    	oFile.close();
	    //    printf("%s", server_response);


        //close(network_socket);

    return 0;
}
