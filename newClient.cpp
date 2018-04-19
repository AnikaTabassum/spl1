#include<stdio.h>
#include<stdlib.h>
#include<fstream>
#include<sys/types.h>
#include<iostream>
#include<sys/socket.h>
#include <unistd.h>
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
	//khub kosto khub kosto;
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
	//amake mair dao;
    listen(server_socket, 5);


    int client_socket;
    client_socket=accept(server_socket,NULL,NULL);//int accept(int socket, struct sockaddr *restrict address,socklen_t *restrict address_len);
   // send(client_socket, total, sizeof(total),0);
    char fileS[12];
   /* char tests[12];
    for(int i=0;i<12;i++)
	{
		tests[i]='A';
	}
	*/
	int n=total;
	char test[n];
	i=0;
	while(n!=0){
		int remainder= n%10;
		char cc='0'+remainder;
		test[i]=cc;
		i++;
		n=n/10;
	}
	//cout<<i<<endl;
	int x=4;
	for(int j=i-1;j>=0;j--)
	{
		fileS[x]=test[j];
		//cout<<fileS[x];
		x++;
	}
    	fileS[0]='S'; fileS[1]='I';fileS[2]='Z';fileS[3]='E';
    	 for(int i=0;fileS[i]!='\0';i++)
		{
			cout<<fileS[i];
		}
		char weak[4];
		for(int i=0;i<4;i++)
		{
			weak[i]='W';
		}
		
		for(int i=0;i<4;i++)
		{
			cout<<weak[i];
		}
     send(client_socket,&fileS, sizeof(fileS),0);
    //send(client_socket,&tests, sizeof(tests),0);
    send(client_socket, &server_message, sizeof(server_message),0);
    send(client_socket,&weak, sizeof(weak),0);
   
		 //client_socket=accept(server_socket,NULL,NULL);
    //server_socket = socket(AF_INET, SOCK_STREAM, 0);
   // cout<<"check"<<endl;
   // int server_socket;
    close(server_socket);
    

    return 0;
}
