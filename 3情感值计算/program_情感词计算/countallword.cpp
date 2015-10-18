//    15206766
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
void findstrch(FILE *fp,int );
void readline(char *tempstr,int num);
int adjdivnum[20];	 //record to div	 **
int appearnum;	 //noun num	 **
typedef struct
{
 int linkcount;	//link adj num
 int hashcode[20];//find adj hash
 float relativedegree[20];//every adj	 **
 char noun[20];	//name
 char adj[20][20];	//adj name
}task_dict;
task_dict tasktemp[2000];
int adjnum;
int allword;
char tempstr[157286400];
int max=0,point=0;
int ntemp[5000];
char adj[1600][30];
int fangzhen[1600][1600],adjcount=0;
int main()
{
 FILE *fdir,*fp;
 char opstr[20],dirpathstr[100];
 char pathstr[]="D:\\assembley\\VC6\\MyProjects\\test2\\MUSIC\\";
 FILE *fdes1,*fdes2,*fdes3;
 if((fdes1=fopen("newadj.txt","r"))==NULL)
  exit(0);
 if((fdes2=fopen("partdata_final.txt","w+b"))==NULL)
  exit(0);
 if((fdes3=fopen("partdata_final_print.txt","w+"))==NULL)
  exit(0);
 int i,filesize,filesizeall=0;
 system("dir D:\\assembley\\VC6\\MyProjects\\test2\\MUSIC\\ /b > dir.txt");
 if((fdir=fopen("dir.txt","a+b"))==NULL)
  exit(0);

 while(!feof(fdes1))
 {
  fscanf(fdes1,"%d %s\n",&i,adj[adjcount++]);
 }
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
  fseek(fp,0,2);
  filesize=ftell(fp);
  rewind(fp);
  fread(tempstr+filesizeall,filesize,1,fp);
  filesizeall+=filesize;
  //
  fclose(fp);
 }i=strlen(tempstr);
 adjnum=adjcount;
 while(point<adjnum)
 {
 
  appearnum=0;
  adjcount=0;
  findstrch(fp,filesizeall);	//查找字符串
  printf("%-20s\t%d\t%d    %d\n",adj[point],adjcount,++max,allword);
  fprintf(fdes3,"%-20s\t%d\t%d\n",adj[point],adjcount,max);
  //i=strlen(tempstr);	 //一个名词的关联已经找完，找出前20个，放入结构体中
  point++;
 }

 fwrite(fangzhen,sizeof(fangzhen),1,fdes2);
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
void findstrch(FILE *fp,int filesize)
{
 int j=0;
 char *pstr=tempstr;
 while(1)
 {
  while(j<filesize)
  {
   if(!(tempstr[j] == '_' && tempstr[j+1] == '.'))
   {
    if(tempstr[j] == '_')
     allword++;
    j++;
   }
   
   else
    break;
  }
 
  if(j>=filesize)
   break;
  readline(pstr,tempstr+j-pstr);
 
  pstr=&tempstr[j];
  j++	;
 }
}
void readline(char *str,int num)	 //一句话中的匹配 若要换寻找匹配的词性则直接修改adj[]数组即可
{
 int i;
 char j;	 //遍历找单词，把link中填充，注意指针的移动并且
 char *newadj;
 j=str[num];
 i=str[num]=0;
 newadj=strstr(str,adj[point]);
 if(!newadj)
 {str[num]=j;return;}
 appearnum++;
 while(i<adjnum)//
 {
  newadj=strstr(str,adj[i]);//
  if((int)newadj)
   if(point !=i)
    fangzhen[point][i]++,adjcount++;//printf("%d %d %d\n",point ,i,adjcount++);
  i++;
 }
 str[num]=j;
}
