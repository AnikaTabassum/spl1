#include<iostream>
#include<fstream>
#include <stdio.h>
#include<string.h>

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
void openforwrite(int filecounter,char *s) {
	char fileoutputname[15];
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

int main() {
	
	int filecounter=openForRead();
	
	return 0;
}
