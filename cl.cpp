#include<stdio.h>
#include<stdlib.h>
#include<fstream>
#include<sys/types.h>
#include<iostream>
#include<sys/socket.h>

#include<netinet/in.h>
#include<stdlib.h>
using namespace std;
ofstream oFile;
int totalByte2(const char* input)      //counts the total byte of the splittedfiles
{
    ifstream iFile;
    iFile.open(input,ios::binary);
    int byt=0;
    if(iFile.is_open())
    {
        char ch;

        while(!iFile.eof())
        {
            iFile.get(ch);
            byt++;
        }
    }
       // cout<<byt;
    iFile.close();
    return byt;

}
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

void sendingFile(char server_message[]){
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
    }
int openForRead()
{
	ifstream iFile;
	FILE *ptr_writefile;
	iFile.open("jj.jpg",ios::binary);
	char line [128];
	int filecounter=1, byteCounter=1;
	char s[]="jj.jpg";

	int total=totalByte(s);
	char server_message[total];

    int ft=total/10;
    int dt=total%10;

    if(dt>0) {ft=ft+1; cout<<ft<<endl;}
    openforwrite(filecounter);
    if(iFile.is_open())
    {
        while(!iFile.eof())
        {
            if(oFile.is_open())

            {
				int x=0;
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
                        //sendingFile(server_message);
                        x=0;
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
int countTheFiles()
{
	ifstream iFile;
	FILE *ptr_writefile;
	iFile.open("jj.jpg",ios::binary);
	char line [128];
	int filecounter=1, byteCounter=1;
	char s[]="jj.jpg";

	int total=totalByte(s);
	char server_message[total];

    int ft=total/10;
    int dt=total%10;

    if(dt>0) {ft=ft+1; cout<<ft<<endl;}
    openforwrite(filecounter);
    if(iFile.is_open())
    {
        while(!iFile.eof())
        {
            if(oFile.is_open())

            {
				int x=0;
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
                        x=0;
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
char fileSIZE[100];
char *convert(int n, char server_message[])
{
	
	int i=0;
	char test[n];
	while(n!=0){
		int remainder= n%10;
		char cc='0'+remainder;
		test[i]=cc;
		i++;
		n=n/10;
	}
	int x=0;
	for(int j=i-1;j>=0;j--)
	{
		server_message[x]=test[j];
		
		x++;
	}
	

return server_message;	
}
char server_message2[454546];
char *convert2(int n)
{
	cout<<n<<endl;
	int i=0;
	char test[n];
	while(n!=0){
		int remainder= n%10;
		char cc='0'+remainder;
		test[i]=cc;
		i++;
		n=n/10;
	}
	int x=0;
	for(int j=i-1;j>=0;j--)
	{
		server_message2[x]=test[j];
		//cout<<server_message2[x]<<endl;
		x++;
	}
	

return server_message2;	
}

/*
void sendFileNumbers()
{
	char fileoutputname[15];
	sprintf(fileoutputname, "testf%d", filecounter);
	sprintf(strings[filecounter-1],fileoutputname);
    printf("%s\n",fileoutputname);
    oFile.open(fileoutputname,ios::binary);
}*/



void sendingFileNumbers(int n){
    int server_socket;
    cout<<n<<endl;
    char server_message[454546];
    convert(n,server_message);
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
    }
    
void sendingFileSize(int n){
    int server_socket;
    
   // cout<<n<<endl;
    convert2(n);
    for(int i=0;server_message2[i]!='\0';i++)
        	cout<<"xs"<<server_message2[i];
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
    
    send(client_socket, server_message2, sizeof(server_message2),0);
    
    }

int main()
{
	ifstream iFile;
	iFile.open("jj.jpg",ios::binary);
    char server_message[454546];
    int filecounter=countTheFiles();
    sendingFileNumbers(filecounter);
    //cout<<filecounter<<endl;
    for(int i=0;i<filecounter;i++)
    {
    	//char fileoutputname[15];
    	//sprintf(fileoutputname, "testf%d", filecounter);
    	cout<<strings[i]<<endl;
		//sprintf(strings[i],fileoutputname);
		int size=totalByte2(strings[i]);
		cout<<size<<endl;
    	sendingFileSize(size);
    	
    }
   // openForRead();
     
    //close(server_socket);

    return 0;
}
