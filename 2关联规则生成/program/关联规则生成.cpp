/*还应剔除一些垃圾形容词 还有link为0 时候的情况*/
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <direct.h>
#include <string.h>
#define GL 37
int gethash(const char *orstr);
void revstr(char *str,int n);
void findstrch(FILE *fp);
void readline(char *tempstr,int num);
void setnum(void);
typedef struct
{
	int hash;
	char str[15];
	int num;
	int link[20];
	int linknum[20];
	int point;
	char tag;

}hashtab;

hashtab adj[5000]={0},n[5000]={0},v[5000]={0};
char tempstr[10000000];
int max=0,point=0,adjnum=0,nnum=0,vnum=0;
int ntemp[5000];
int guolv[GL]={1578,1572,1523,1512,1428,1369,1319,1286,1282,1273,1255,1216,1162,970,
			937,834,783,782,689,678,621,597,543,499,491,439,237,149,118,3,470,589,938,1215,1333,623,512				};
int main()
{
	FILE *fdir,*fp;
	char opstr[20],dirpathstr[100];
	char pathstr[]="D:\\assembley\\VC6\\MyProjects\\test2\\MUSIC\\";
	FILE *fdes1,*fdes2,*fdes3;
	if((fdes1=fopen("desadj.txt","r+b"))==NULL)
		exit(0);
	if((fdes2=fopen("desn.txt","r+b"))==NULL)
		exit(0);
	if((fdes3=fopen("desv.txt","r+b"))==NULL)
		exit(0);
/*
			if((fp=fopen("wwwwwwn.txt","w+"))==NULL)
				exit(0);*/
		
	while(fread(&adj[adjnum++],sizeof(hashtab),1,fdes1)==1)
		;
	while(fread(&n[nnum++],sizeof(hashtab),1,fdes2)==1)
		;
	while(fread(&v[vnum++],sizeof(hashtab),1,fdes3)==1)
		;
	system("dir MUSIC\\  /b > dir.txt");
	if((fdir=fopen("dir.txt","a+b"))==NULL)
		exit(0);
	while(point++<nnum)
	{
	/*
	
			for(int i=0;i<adjnum;i++)
							{
								printf("%s\n",adj[i].str);
								fprintf(fp,"%d\t",i);
								fputs(adj[i].str,fp);
								fputc('\n',fp);
							}
							fclose(fp);
			*/
	
		
		memset(ntemp,0,sizeof(ntemp));
		rewind(fdir);
		while(1)
		{
			fgets(opstr,20,fdir);
			if(feof(fdir))
				break;
			opstr[strlen(opstr)-2]='\0';
			strcpy(dirpathstr,pathstr);
			strcat(dirpathstr,opstr);
			if((fp=fopen(dirpathstr,"a+b"))==NULL)
				break;
		/*
			if(sum++==6000)
						system("pause");*/
		
			findstrch(fp);//查找字符串
			printf("%s\t%d\n",dirpathstr,++max);
			fclose(fp);	
		}
		setnum();					//一个名词的关联已经找完，找出前20个，放入结构体中




	}
	fclose(fdir);
	fclose(fdes1);
	fclose(fdes2);
	fclose(fdes3);
	return 0;
}

int gethash(const char *orstr)
{
	register int hash = 0;
	while(*orstr)
		hash =hash * 131 + *orstr++;
	return hash;
}
void findstrch(FILE *fp)
{
	int j=0;
	long filesize;
	char *pstr=tempstr;
	fseek(fp,0,2);
	filesize=ftell(fp);
	rewind(fp);
	fread(tempstr,filesize,1,fp);
	while(1)
	{
		while(!(tempstr[j] == '_' && tempstr[j+1] == '.') && j<filesize)
			j++;
	
		if(j>=filesize)
			break;
		readline(pstr,tempstr+j-pstr);
		pstr=&tempstr[j];
	}
}
void readline(char *tempstr,int num)			//一句话中的匹配  若要换寻找匹配的词性则直接修改adj[]数组即可
{
	int i;												//遍历找单词，把link中填充，注意指针的移动并且
	char *newadj;
	i=tempstr[num]=0;
	newadj=strstr(tempstr,n[point].str);
	if(!newadj)
		return;
	while(i<adjnum)//
	{
		newadj=strstr(tempstr,adj[i].str);//
		if((int)newadj)
			ntemp[i]++;
		i++;
	}
	tempstr[num]='.';
}    
void setnum(void)
{
	FILE *fp;
	int i,j,maxnum,k=-1;
	for(i=0;i<GL;i++)
		ntemp[guolv[i]]=0;
	if((fp=fopen("waaaaaaaaaab.txt","a+"))==NULL)
		exit(0);
	for(i=0;i<20;i++)
	{
		k=-1;
		maxnum=0;
		for(j=0;j<adjnum;j++)
		{
			if(maxnum<ntemp[j])
			{
				k=j;
				maxnum=ntemp[j];
			}			
		}
		if(k==-1)
			continue;
		n[point].link[i]=k;
		n[point].linknum[i]=ntemp[k];
		ntemp[k]=0;
	}
	printf("%s\n",n[point].str);
	fprintf(fp,"%s\n",n[point].str);
	for(i=0;i<20;i++)
	{
		if(n[point].link[i]==0)
			fprintf(fp,"%d NULL\n",i);
		else
		{
			printf("%s\n",adj[n[point].link[i]].str);
			fprintf(fp,"%d %s\n",i,adj[n[point].link[i]].str);
		}
	}
	fprintf(fp,"-----------------------\n");
	fclose(fp);
	
}