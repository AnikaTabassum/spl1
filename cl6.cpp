#include<stdio.h>
#include<bits/stdc++.h>
#include<stdlib.h>
#include<iostream>
#include<sys/types.h>
#include<sys/socket.h>
#include<fstream>
#include<netinet/in.h>
#include <unistd.h>
using namespace std;
ofstream oFile; 
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
	iFile.open("j.jpg6",ios::binary);
    int i=0;
  	char s[7]="j.jpg6";
	int total=totalByte(s);
  	
//    int tot=48257;
    char server_message[888888];
    /*char *server_message;
    server_message= new char[48257];*/
    cout<<total<<endl;

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
	 // send(client_socket, total, sizeof(total),0);
	char fileN[4];
	fileN[0]='N';fileN[1]='A';fileN[2]='M';fileN[3]='E';
	send(network_socket,&fileN, sizeof(fileN),0);
	for(int i=0;i<4;i++)
		{
			cout<<fileN[i];
		}
    send(network_socket,&s, sizeof(s),0);

    char fileS[7];
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
		
     send(network_socket,&fileS, sizeof(fileS),0);
   

    send(network_socket, &server_message, total,0);
   
    close(network_socket);
    

    return 0;
}
 
