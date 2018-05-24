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
using namespace std;

int number_of_threads;
ofstream oFile; 
char file_name[7];
int total=0;

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
	char s[]="t.jpg";
	//char s[]="c.pdf";         /////////////////filename
	iFile.open(s,ios::binary);
	char line [128];
	int filecounter=1, byteCounter=1;

	int total=totalByte(s);

    int ft=total/5;
    int dt=total%5;

    if(dt>0) 
    {
    	ft=ft+1; 
    }
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

                    if(byteCounter==(total/10)||(iFile.eof()))
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

void send_Number_of_Files(int network_socket)
{
	

    char num_of_file[2];
    if(number_of_threads<10)
    {
   		num_of_file[0]='0';
   		num_of_file[1]=(char)number_of_threads+'0';
   		
	}
	else if(number_of_threads>=10)
	{
		
		int n=number_of_threads;
		int x=n/10;	
		
		num_of_file[0]=(char)x+'0';
		x=n%10;
		num_of_file[1]=(char)x+'0';
		
		
	}
	
	send(network_socket, num_of_file, sizeof(num_of_file),0); 
   
}

void send_file_name(int network_socket, long tid)
{
	char fileN[4];
	fileN[0]='N';fileN[1]='A';fileN[2]='M';fileN[3]='E';
	
	send(network_socket,&fileN, sizeof(fileN),0);	//sending filename array
  
	char temp[2];
  
	if(tid<9)
    {
    	temp[0]='0';
    	temp[1]=(char)tid+1+'0';
    }
    else if(tid>=9)
    {
   		int n=tid+1;		
		int x=n/10;
		temp[0]=(char)x+'0';
		x=n%10;
		temp[1]=(char)x+'0';
   	}

  	if(tid>=9)
  	{
  		file_name[0]='t',file_name[1]='.',file_name[2]='j',file_name[3]='p',file_name[4]='g',file_name[5]=temp[0],file_name[6]=temp[1];
  		//file_name[0]='c',file_name[1]='.',file_name[2]='p',file_name[3]='d',file_name[4]='f',file_name[5]=temp[0],file_name[6]=temp[1];
  	}
  	else
  	{
  		file_name[0]='t',file_name[1]='.',file_name[2]='j',file_name[3]='p',file_name[4]='g',file_name[5]=temp[1],file_name[6]='\0';
  		//file_name[0]='c',file_name[1]='.',file_name[2]='p',file_name[3]='d',file_name[4]='f',file_name[5]=temp[1],file_name[6]='\0';  
  	}	
    send(network_socket,&file_name, sizeof(file_name),0);  /////send file names
  	
}

void send_file_size_and_file(int network_socket)
{
	total=totalByte(file_name);
	  	
    char fileSize[9];
	int n=total;
	char test[n];
	int i=0;
	while(n!=0){
		int remainder= n%10;
		char cc='0'+remainder;
		test[i]=cc;
		i++;
		n=n/10;
	}
	
	int x=4;
	for(int j=i-1;j>=0;j--)
	{
		fileSize[x]=test[j];	
		x++;
	}
    	fileSize[0]='S'; fileSize[1]='I';fileSize[2]='Z';fileSize[3]='E';
    	 
     send(network_socket,&fileSize, sizeof(fileSize),0);			///send filesize
   
	char server_message[888888];
    send(network_socket, &server_message, total,0);			///send file
   
}

void *sendSock(void *threadid) 
{
    long tid;
   	tid = (long)threadid;
   
   	int network_socket;
    network_socket = socket(AF_INET, SOCK_STREAM, 0);   

    struct sockaddr_in server_address;
    server_address.sin_family= AF_INET;
    server_address.sin_addr.s_addr= INADDR_ANY;
	//server_address.sin_addr.s_addr=  inet_addr("10.100.106.7");    /////////to other ip
    server_address.sin_port = htons(9002);
    int connection_status= connect(network_socket, (struct sockaddr *)&server_address, sizeof(server_address)); 

    if(connection_status==-1)
        printf("Error\n");
        
    int socket(int domain, int type, int protocol);
   
 	send_Number_of_Files(network_socket);

 	send_file_name(network_socket,tid);

 	send_file_size_and_file(network_socket);
  
    close(network_socket);
    

    return 0;
   	pthread_exit(NULL);
}

int main () {
	number_of_threads=	openForRead();
   	pthread_t threads[number_of_threads];
   	int rc;
   	int i;
   
   	for( i = 0; i < number_of_threads; i++ ) 
   	{
      	cout << "creating thread, " << i+1 << endl;
    	rc = pthread_create(&threads[i], NULL, sendSock, (void *)i);
      
      	if (rc) 
      	{
        	 cout << "Error:unable to create thread," << rc << endl;
        	 exit(-1);
      	}
   }
   pthread_exit(NULL);
}
