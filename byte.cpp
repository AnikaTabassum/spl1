#include<iostream>
#include<fstream>
#include <stdio.h>
#include<string.h>

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
        //cout<<byt;
    }
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

int mergefiles(int n)          //merges the splitted files
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

int main() {
	ifstream iFile;
	FILE *ptr_writefile;
	iFile.open("j.jpg",ios::binary);
	char line [128];
	int filecounter=1, byteCounter=1;
	char s[]="j.jpg";

	int total=totalByte(s);

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

                for(int i=0;i<totalByte(s);i++)
                {
                    char ch;

                    iFile.get(ch);

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

    mergeFiles(filecounter);
	return 0;
}
