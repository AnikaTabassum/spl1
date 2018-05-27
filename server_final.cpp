#include<stdio.h>
#include<bits/stdc++.h>
#include<stdlib.h>
#include<fstream>
#include<sys/types.h>
#include<iostream>
#include<sys/socket.h>
#include <unistd.h>
#include<netinet/in.h>
using namespace std;
char **strings=new char*[5000];
int number_of_file=0;
int cnt=0;
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
        //cout<<byt;
    }
    iFile.close();
    return byt;

}
int mergeFiles(int n)          //merges the splitted files
{

    ofstream oFile2;
    oFile2.open("final.jpg",ios::binary);
	//oFile2.open("received.pdf",ios::binary);
    char buffer[4097];

    for (int i = 1; i <=n; ++i)
    {

        const char* fname = strings[i];
        printf("merging %s\n",fname);

        ifstream iFile2;
        iFile2.open(fname,ios::binary);

        if(iFile2.is_open())
        {
            while(!iFile2.eof())
            {
                if(oFile2.is_open()||(iFile2.eof()))
                {

                    for(int j=0;j<totalByte2(fname);j++)
                    {
                        char ch;
                        iFile2.get(ch);
                        if(!iFile2.eof())
                            oFile2<<ch;

                    }
                }
            iFile2.close();
            }
        }


    }
    oFile2.close();
	return 0;
}
int convert(char tem[])
{
	int x=tem[0]-'0';
	x=x*10+(tem[1]-'0');
	
	return x;
}
void receive_number_of_files(int client_socket)
{	
	char num[2];
	recv(client_socket, &num, sizeof(num),0);  /////receive number of files
	number_of_file=convert(num);
	
}

void receive_file_name(int client_socket)
{
 	char *name=new char[80];
	char fileN[4];
	recv(client_socket, &fileN, sizeof(fileN),0);  ///////receive fileName array
	char arr[2];
	recv(client_socket, &arr, sizeof(arr),0); 
	int sz=convert(arr);
	sz=sz+2;
	char s[sz];
    recv(client_socket, &s, sz,0);  //receive file name
    	
	int p=0;
		
	if((fileN[0]=='N'||fileN[0]=='n')&&(fileN[1]=='A'||fileN[1]=='a')&&
    (fileN[2]=='M'||fileN[2]=='m')&&(fileN[3]=='E'||fileN[3]=='e'))
    {
		int a=0;
   		cnt++;
   		int idx,idxx;
		for(int i=0;i<sz;i++)
		{
			name[i]=s[i];
			
		}
		if(s[sz-1]=='\0')
		{
			a=s[sz-2]-'0';		
		}
		else
		{
			a=s[sz-2]-'0';
			a=a*10+(s[sz-1]-'0');
			
    	}	
   		strings[a]=name;
    }
}

void receive_file_size_and_file(int client_socket)
{
	char fileS[9];
	int tests[12];
	recv(client_socket, &fileS, sizeof(fileS),0);  //receive filesize array
   	int fileSize=0;
    int z=0;
      	
	if((fileS[0]=='S'||fileS[0]=='s')&&(fileS[1]=='I'||fileS[1]=='i')&&
    (fileS[2]=='Z'||fileS[2]=='z')&&(fileS[3]=='E'||fileS[3]=='e'))
    {	
      	for(int i=4;fileS[i]!='\0';i++)
		{
			tests[z]=(char)fileS[i]-'0';				
    		fileSize= 10 *fileSize + tests[z];	
			z++;	
		}
     }

     char server_response [fileSize]; 

	 recv(client_socket, &server_response, sizeof(server_response),0);  // receive file
}
	
int main()
{
 
    for(int i=0;i<5000;i++)
	{
		char *strings=new char[5000];
	}
   
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_address;
    server_address.sin_family= AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr= INADDR_ANY;

    bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));
	
	while(1)
	{
    	listen(server_socket, 5);
		int client_socket;
    	client_socket=accept(server_socket,NULL,NULL);
    	
		receive_number_of_files(client_socket);
		
      	receive_file_name(client_socket);
      	
      	receive_file_size_and_file(client_socket);
       
       	if(cnt==number_of_file)
       	{
       		mergeFiles(number_of_file);
       		cnt=0;
       		cout<<"Successfully merged"<<endl;
       	}

        close(client_socket);
	}
		
    return 0;
}
