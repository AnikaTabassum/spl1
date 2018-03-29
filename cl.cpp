#include<stdio.h>
#include<stdlib.h>
#include<fstream>
#include<sys/types.h>
#include<iostream>
#include<sys/socket.h>

#include<netinet/in.h>
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
char strings[5000][5000];
void openforwrite(int filecounter) {
	char fileoutputname[15];
	sprintf(fileoutputname, "testf%d", filecounter);
	sprintf(strings[filecounter-1],fileoutputname);
    printf("%s\n",fileoutputname);
    oFile.open(fileoutputname,ios::binary);
}

int openForRead(char server_message[])
{
	ifstream iFile;
	FILE *ptr_writefile;
	iFile.open("jj.jpg",ios::binary);
	char line [128];
	int filecounter=1, byteCounter=1;
	char s[]="jj.jpg";

	int total=totalByte(s);

    int ft=total/10;
    int dt=total%10;

    if(dt>0) {ft=ft+1; cout<<ft<<endl;}
    openforwrite(filecounter);
    if(iFile.is_open())
    {
    	
        while(!iFile.eof())
        {	
        	int x=0;
            if(oFile.is_open())

            {

                for(int i=0;i<totalByte(s);i++)
                {
                    char ch;

                    iFile.get(ch);
					server_message[x]=ch;
                    if(byteCounter==(total/10)||(iFile.eof()))
                    {
                        oFile.close();
                        byteCounter=1;
                        filecounter++;
                        openforwrite(filecounter);
                    }
                    oFile<<ch;
                    byteCounter++;

                }
            }
            iFile.close();
        }
    }
    return filecounter;
}

int main()
{
	char s[128]="jj.jpg";
	int total=totalByte(s);
    char server_message[454546];
	openForRead(server_message);
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
