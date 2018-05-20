#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include<stdio.h>
#include<bits/stdc++.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<fstream>
#include<netinet/in.h>
#include <unistd.h>
#define NUM_THREADS 7
using namespace std;
int number_of_threads;
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
void openforwrite(int filecounter,char *s) {
	char fileoutputname[15];
	cout<<filecounter<<endl;
	sprintf(fileoutputname, "%s%d", s,filecounter);
	sprintf(strings[filecounter-1],fileoutputname);
    printf("%s\n",fileoutputname);
    oFile.open(fileoutputname,ios::binary);
}
int openForRead()
{
	ifstream iFile;
	FILE *ptr_writefile;
	char s[]="j.jpg";
	iFile.open(s,ios::binary);
	char line [128];
	int filecounter=1, byteCounter=1;

	int total=totalByte(s);

    int ft=total/5;
    int dt=total%5;

    if(dt>0) {ft=ft+1; cout<<ft<<endl;}
    openforwrite(filecounter,s);
    if(iFile.is_open())
    {
        while(!iFile.eof())
        {
            if(oFile.is_open())

            {

                for(int i=0;i<totalByte(s);i++)
                {
                    char ch;

                    iFile.get(ch);

                    if(byteCounter==(total/5)||(iFile.eof()))
                    {
                        oFile.close();
                        byteCounter=1;
                        filecounter++;
                        openforwrite(filecounter,s);
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



void *sendSock(void *threadid) {
   long tid;
   tid = (long)threadid;
   cout << "ID, " << tid << endl;
   char temo=(char)tid+1+'0';
  // cout<<temo<<endl;
   ifstream iFile;
  	char s[6];
  	s[0]='j',s[1]='.',s[2]='j',s[3]='p',s[4]='g',s[5]=temo;
  	
	iFile.open(s,ios::binary);
  	
    int i=0;
  	char num[2];
  	num[0]=s[5];
  	
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
	///////////inet_pton(AF_INET, "127.0.0.1", &remote_addr.sin_addr); /********************************************************************
    int connection_status= connect(network_socket, (struct sockaddr *)&server_address, sizeof(server_address)); //

    if(connection_status==-1)
        printf("Error\n");
        int socket(int domain, int type, int protocol);
    char num_of_file[1];
   	num_of_file[0]=(char)number_of_threads+'0';
	send(network_socket, num_of_file, sizeof(num_of_file),0); ///////send nuber of splitted files
	char fileN[4];
	fileN[0]='N';fileN[1]='A';fileN[2]='M';fileN[3]='E';
	//send(network_socket,&num, sizeof(num),0);
	send(network_socket,&fileN, sizeof(fileN),0);		////send fileName array
	for(int i=0;i<4;i++)
		{
			cout<<fileN[i];
		}
    send(network_socket,&s, sizeof(s),0);    /////send file names

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
		
     send(network_socket,&fileS, sizeof(fileS),0);			///send filesize
   

	cout<<tid<<endl;
    send(network_socket, &server_message, total,0);			///send file
   
    close(network_socket);
    

    return 0;
   pthread_exit(NULL);
}

int main () {
	number_of_threads=	openForRead();
   pthread_t threads[number_of_threads];
   int rc;
   int i;
   
   for( i = 0; i < number_of_threads; i++ ) {
      cout << "main() : creating thread, " << i << endl;
      rc = pthread_create(&threads[i], NULL, sendSock, (void *)i);
      
      if (rc) {
         cout << "Error:unable to create thread," << rc << endl;
         exit(-1);
      }
   }
   pthread_exit(NULL);
}
