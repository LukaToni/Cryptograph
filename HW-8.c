#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define MAXLINE 100

static int length1 = 0;
static int length2 = 0;

//-------MEMORY----------//
char **makeMemory(char **tabel)
{
	tabel = malloc(sizeof(char*)*1000);
	int i = 0;
	while(i < 1000)
	{
		tabel[i] = malloc(sizeof(char)*100);
		tabel[i][0] = '\0';
		i++;
	}
	return tabel;
}



//---------READ DATA----------//
void fileRead(char *pathData, char **dataRewrite, int *length)
{
	char line[MAXLINE];
	
	FILE *f = fopen (pathData, "r");
	
	if(f == NULL)
	{
		printf("ERROR\n"); //canot open file
	}
	int i = 0;
	while (fgets(line, MAXLINE, f) != NULL)
	{
		strcpy(dataRewrite[i], line);
		(*length)++;
		i++;
	}
	fclose(f);
}


void Compare (char **data1, char** data2, char* FO)
{
    FILE *fp = fopen(FO, "w");

    int i = 0;
    int j = 0;
    int foundSame;
    while( i <= length1 || j <= length2)
    {
        if(i == j)
        {
            foundSame = 0;
            int a;

            for(a = 0; a < length2; a++)
            {
	            if(data1[i][0] == '\0') //isto kot (int)EOF -redeferenciranje
	            {
			foundSame = 1;
			break;
	            }
	            else if(strcmp(data1[i], data2[a]) == 0)
	            {
			foundSame = 1;
			break;
	            }
            }

            if(foundSame == 0)
                fprintf(fp, "%c", data1[i][0]);
            
            i++;
        }

        else if(i > j)
        {
            foundSame = 0;
            int b;

            for(b = 0; b < length1; b++)
            {
		if(data2[j][0] == (int)NULL)
		{
			foundSame = 1;
			break;
		}
                if(strcmp(data1[b], data2[j]) == 0)
                {
			foundSame = 1;
			break;
                }
            }
            if(foundSame == 0)
                fprintf(fp, "%c", data2[j][0]);
   
            j++;
        }
    }
    fprintf(fp, "%c", '\n');
    fclose(fp);
}


//----------MAIN---------//
int main(int argc, char *argv[])
{
	/*create table for rewriting from first data*/
	char **data1 = NULL;
	data1 = makeMemory(data1);
	/*create table for rewriting from second data*/
	char **data2 = NULL;
	data2 = makeMemory(data2);
	/*rewrite from data1 in table data1*/
	fileRead(argv[1], data1, &length1);
	/*rewrite from data2 in table data2*/
	fileRead(argv[2], data2, &length2);

    	Compare(data1, data2, argv[3]);

	//----TEST FILES-------//
	/*
	int i;
	puts("PRVI");
	for(i = 0; i < strlen(data1); i++)
		printf("Data 1 :%s\n", data1[i]);
	
	puts("DRUGI");
	for(i = 0; i < strlen(data2); i++)
		printf("Data 2 :%s\n", data2[i]);
	
	*/

     return 0;
}
