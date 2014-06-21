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
   // printf("in memorymake: %p\n", tabel);
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


#if 1
//---------READ DATA----------//
void fileRead(char *pathData, char **dataRewrite, int *length)
{
	char line[MAXLINE];
	//printf("pathdata: %s\n", pathData);
	FILE *f = fopen (pathData, "r");
	/*ce ni mogoce odpreti datoteke*/
	if(f == NULL)
	{
		printf("NAPAKA\n");
	}
	int i = 0;
	while (fgets(line, MAXLINE, f) != NULL)
	{
		strcpy(dataRewrite[i], line);
		(*length)++;
		//printf("%s", dataRewrite[i]);
		i++;
	}
	fclose(f);
}
#endif

void Compare (char **data1, char** data2, char* FO)
{
    //printf("---------data2%c:", data2[0][0]);

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
                //printf("tuki:\n%d", a);
                #if 0
                if(j==i)
                {
                    if(strcmp(data1[i],data2[j]) == 0)
                    data1[i] = 1;
                    data2[j] = 1;
                    printf("TUKILE SM");
                    j++;
                    break;
                }
                #endif // 0

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
            {
                fprintf(fp, "%c", data1[i][0]);
            }
            i++;
        }

        else if(i > j)
        {
            foundSame = 0;
            int b;

            for(b = 0; b < length1; b++)
            {
							if(data2[j][0]==(int)NULL)
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
            {
                fprintf(fp, "%c", data2[j][0]);
            }

            j++;
        }
    }
    fprintf(fp, "%c", '\n');
    fclose(fp);
}


//----------MAIN---------//
int main(int argc, char *argv[])
{

	/*naredimo tabelo za prepis iz prve datoteke*/
	char **data1 = NULL;
	data1 = makeMemory(data1);
	/*naredimo tabelo za prepis iz druge datoteke*/
	char **data2 = NULL;
	data2 = makeMemory(data2);
	/*prepisimo datoteko 1 v tabelo data1*/
	fileRead(argv[1], data1, &length1);
	/*prepisimo datoteko 2 v tabelo data2*/
	fileRead(argv[2], data2, &length2);
	//puts("ble2");
	//sleep(5);
    Compare(data1, data2, argv[3]);

	//----TEST FILES-------//
	#if 0
	int i;
	puts("PRVI");
	for(i = 0; i < strlen(data1); i++)
	{
		printf("Data 1 :%s\n", data1[i]);
	}
	puts("DRUGI");
    for(i = 0; i < strlen(data2); i++)
	{
		printf("Data 2 :%s\n", data2[i]);
	}
    #endif
//    puts ("DELA");
  //  printf("len1: %i    len2: %i",length1, length2);
  //fprintf("\n");
     return 0;
}
