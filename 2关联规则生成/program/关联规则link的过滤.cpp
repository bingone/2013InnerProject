#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <direct.h>
#include <string.h>
/************************************************************************/
/*
aim 去除NULL与重复adj
1. read part.txt in line
2. plus allnoun
3. NULL same jump
4. 
                                                                     
*/
/************************************************************************/
int gethash(const char *orstr)
{
	register int hash = 0;
	while(*orstr)
		hash =hash * 131 + *orstr++;
	return hash;
}
	int num[20];		//record to div				**
	int appearnum;		//noun num					**

typedef struct  
{
	int linkcount;	//link adj num
	int hashcode[20];//find adj hash
	float relativedegree[20];//every adj			**
	char noun[20];	//name
	char adj[20][20];	//adj name
}task_dict;

task_dict tasktemp[2000];
int nounum;

int main()
{
	FILE *fpsou,*fpdes;
	int i,j,k,n,flag=0;
	char buff[100];
	char *buffer;
	if((fpdes=fopen("partdata_link.txt","w"))==NULL)
		exit(0);
	if((fpsou=fopen("part.txt","r"))==NULL)
		exit(0);	
	while(fgets(buff,25,fpsou))
	{
		
		flag=i=0;							//flag用于去除中间包含NULL
		if(*buff=='-' ||strstr(buff,"NULL"))
				continue;
		buff[strlen(buff)-1]=0;
		strcpy(tasktemp[nounum].noun,buff);	
		do
		{
			fgets(buff,25,fpsou);
			buff[strlen(buff)-1]=0;
			buffer=strstr(buff," ");
			buffer++;
			if(*buff=='-')
				break;
			if(strstr(buff,"NULL")|| i&&strstr(buff,tasktemp[nounum].adj[i-1]))
			{flag++;continue;}
			strcpy(tasktemp[nounum].adj[i],buffer);
			tasktemp[nounum].hashcode[i]=gethash(buff);
			if(i==19-flag)
				break;
			i++;
		}while(1);
		if(i)
			tasktemp[nounum].linkcount=i,nounum++,printf("%s %d %d\n",tasktemp[nounum-1].noun,tasktemp[nounum-1].linkcount,nounum-1);
		
	}
	for(i=0;i<nounum;i++)
	{
		fprintf(fpdes,"%s\n",tasktemp[i].noun);
		for(j=0;j<tasktemp[i].linkcount;j++)
			fprintf(fpdes,"%d %s\n",j+1,tasktemp[i].adj[j]);
		fprintf(fpdes,"\n\n\n");
	}
	
	fclose(fpdes);
	fclose(fpsou);
	return 0;
}