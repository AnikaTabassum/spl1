#include <stdio.h>
#include<string.h>
char strings[5000][5000];
FILE *openforwrite(int filecounter) {
	char fileoutputname[15];

	sprintf(fileoutputname, "file_part%d", filecounter);
	sprintf(strings[filecounter-1],fileoutputname);
   // printf("%s\n",fileoutputname);
	return fopen(fileoutputname, "w");
}

int cbd_merge_files(int n) {

  FILE* fp = fopen("E:/chap1/final.txt", "wb");

  if (fp == NULL) return 1;

  char buffer[4097];
    int i;
  for (i = 0; i < n; ++i) {

    const char* fname = strings[i];
        //printf("%s\n",fname);
    FILE* fp_read = fopen(fname, "rb");

    if (fp_read == NULL) return 1;

    int n;

    while ((n = fread(buffer, sizeof(char), 4096, fp_read))) {

        int k = fwrite(buffer, sizeof(char), n, fp);

        if (!k) return 1;
    }
    fclose(fp_read);

 }

 fclose(fp);

 return 0;
}

int main() {
	FILE *ptr_readfile;
	FILE *ptr_writefile;
	char line [128]; /* or some other suitable maximum line size */
	int filecounter=1, linecounter=1;

	ptr_readfile = fopen("input.txt","r");
	if (!ptr_readfile)
		return 1;

	ptr_writefile = openforwrite(filecounter);

	while (fgets(line, sizeof line, ptr_readfile)!=NULL) {
		if (linecounter == 10) {
			fclose(ptr_writefile);
			linecounter = 1;
			filecounter++;

			ptr_writefile = openforwrite(filecounter);
			if (!ptr_writefile)
			return 1;
		}
		fprintf(ptr_writefile,"%s", line);
		linecounter++;
	}
	fclose(ptr_readfile);
    int i;
    for(i=0;i<filecounter;i++)
        printf("%s\n",strings[i]);
	cbd_merge_files(filecounter);
	return 0;
}
