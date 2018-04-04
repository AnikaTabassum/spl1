#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<sys/types.h>
#include<sys/socket.h>
#include<fstream>
#include<netinet/in.h>

using namespace std;
char strings[5000][5000];
ofstream oFile;
int filecounter=1, byteCounter=1; 
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
void openforwrite(int filecounter) {
	char fileoutputname[15];
	sprintf(fileoutputname, "testf%d", filecounter);
	sprintf(strings[filecounter-1],fileoutputname);
    printf("%s\n",fileoutputname);
    oFile.open(fileoutputname,ios::binary);
}

int mergeFiles(int n)          //merges the splitted files
{

    ofstream oFile2;
    oFile2.open("now.jpg",ios::binary);

    char buffer[4097];

    for (int i = 0; i < n; ++i)
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
void writeInFile(char server_response[], int filecounter, int byteCounter)
{
	int x=0;
	 openforwrite(filecounter);
	while(server_response[x]!='\0')
	{
		if(oFile.is_open())
        {

			char ch= server_response[x];
			oFile<<ch;
			 byteCounter++;
		}
		x++;
	}
	oFile.close();
    byteCounter=1;
    filecounter++;
    openforwrite(filecounter);
      
}
int merging(int sss, char server_response[])          //merges the splitted files
{

    ofstream oFile2;
    oFile2.open("now.jpg",ios::app);

    char buffer[4097];

    for (int i = 0; i < sss; ++i)
    {
         char ch=server_response[i];                      
         oFile2<<ch;
     }
                
    oFile2.close();
return 0;
}

void receiveing()
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
      	
        recv(network_socket, &server_response, sizeof(server_response),0);  
        //int sss=sizeCheck(server_response);
        writeInFile(server_response,filecounter,byteCounter);
        //cout<<sss<<endl;
        //merging(sss,server_response);
}

int convertion(char server_response[])
{
	/*for(int i=0;server_response[i]!='\0';i++)
	{
		//cout<<server_response[i];
		int h=server_response[i]-'0';
		cout<<h<<endl;
	}*/
	return atoi(server_response);
}

int receiveFileNumbers()
{
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
      
        recv(network_socket, &server_response, sizeof(server_response),0); 
        /*for(int i=0;server_response[i]!='\0';i++)
        	cout<<server_response[i];*/
        int numberOfFiles=convertion(server_response) ;
        //cout<<numberOfFiles<<endl;
        
        return numberOfFiles;
        	
}

int receiveFileSize()
{
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
      
        recv(network_socket, &server_response, sizeof(server_response),0); 
        for(int i=0;server_response[i]!='\0';i++)
        	cout<<"x"<<server_response[i];
        int fileSize=convertion(server_response) ;
        cout<<fileSize<<endl;
        
        return fileSize;
        	
}

int main()
{
    
    int n=receiveFileNumbers();
   // for(int i=0;i<n;i++){
    int size=receiveFileSize();
    cout<<size<<endl;
    //}
    //receiveing();
                 //close(network_socket);

    return 0;
}
