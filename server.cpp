#include<stdio.h>
#include<stdlib.h>
#include<fstream>
#include<sys/types.h>
#include<iostream>
#include<sys/socket.h>

#include<netinet/in.h>
using namespace std;

int totalByte(char* input)  ////counts the total byte of the splittedfiles
{
    ifstream iFile;
    iFile.open(input,ios::binary);
    int byt=0;
    if(iFile.is_open())
    {
        char ch;

        while(1)
        {
            if(iFile.eof()) break;
            iFile.get(ch);
            byt++;
        }

    }
    iFile.close();
    return byt;

}
int main()
{
	ifstream iFile;
	iFile.open("jj.jpg",ios::binary);
    char server_message[454546];
    int i=0;
  	char s[125]="jj.jpg";
   	char lol[1253];
    int total=totalByte(s);
    cout<<total<<endl;
	if(iFile.is_open())
    {
        while(!iFile.eof())
        {
        	char ch;

        	iFile.get(ch);
        	server_message[i]=ch;
        	i++;
        }
    }
    iFile.close();

    //create the server socket
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    //define the server address

    struct sockaddr_in server_address;
    server_address.sin_family= AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr= INADDR_ANY;

    //bind the socket to our specified IP and port

    bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));

    listen(server_socket, 5);


    int client_socket;
    client_socket=accept(server_socket,NULL,NULL);//int accept(int socket, struct sockaddr *restrict address,socklen_t *restrict address_len);
    send(client_socket, server_message, sizeof(server_message),0);
   // send(client_socket, total, sizeof(total),0);
    //close(server_socket);

    return 0;
}
