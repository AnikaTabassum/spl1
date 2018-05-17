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
    oFile2.open("fin.jpg",ios::binary);

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
int main()
{
	
   	char lol[1253];
    
    for(int i=0;i<5000;i++)
{
	char *strings=new char[5000];
}
    //create the server socket
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    //define the server address

    struct sockaddr_in server_address;
    server_address.sin_family= AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr= INADDR_ANY;

    //bind the socket to our specified IP and port
	int cnt=0;
    bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));
	
	while(1){
    listen(server_socket, 5);


    int client_socket;
    client_socket=accept(server_socket,NULL,NULL);//int accept(int socket, struct sockaddr *restrict address,socklen_t *restrict address_len);
       //while(1){
		 char fileS[7];
		 int tests[12];
		
		/*for(int i=0;fileS[i]!='\0';i++)
		{
			cout<<fileS[i];
		}*/
		char *name=new char[80];
		char fileN[4];
		char num[1];
		recv(client_socket, &num, sizeof(num),0);  /////receive number of files
		int number_of_file=num[0]-'0';
		recv(client_socket, &fileN, sizeof(fileN),0);  ///////receive fileName array
		char s[6];
    	recv(client_socket, &s, sizeof(s),0);  //receive file name
		int p=0;
		int a=0;
		
		if((fileN[0]=='N'||fileN[0]=='n')&&(fileN[1]=='A'||fileN[1]=='a')&&
      	(fileN[2]=='M'||fileN[2]=='m')&&(fileN[3]=='E'||fileN[3]=='e'))
      	{
      	cnt++;
      		for(p=0;s[p]!='\0';p++)
      			name[p]=s[p];
      		
      		cout<<name[p]<<endl;
      		//const char* fname = name;
      		a=name[p-1]-'0';
      		//cout<<"oiij0"<<a<<endl;
//      		cout<<a<<endl;
      		strings[a]=name;
      		printf("%s",strings[a]);
      	}
		recv(client_socket, &fileS, sizeof(fileS),0);  //receive filesize array
      		int fileSize=0;
      		int z=0;
      	
		if((fileS[0]=='S'||fileS[0]=='s')&&(fileS[1]=='I'||fileS[1]=='i')&&
      	(fileS[2]=='Z'||fileS[2]=='z')&&(fileS[3]=='E'||fileS[3]=='e'))
      	{
      	cout<<"gh"<<endl;
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
      	
		cout<<fileSize<<endl;
        char server_response [fileSize]; 
        
        
        recv(client_socket, &server_response, sizeof(server_response),0);  // receive file
       
       if(cnt==number_of_file)mergeFiles(cnt);
		
		
		 
        close(client_socket);
		}
		
    return 0;
}
