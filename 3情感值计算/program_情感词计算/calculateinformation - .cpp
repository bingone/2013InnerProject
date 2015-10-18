#include <stdio.h>
#include<string.h>
#include <math.h>
#include <stdlib.h>
#define allwordnum 15206766
#define total 863
#define sbegin 0
#define sends 60//
#define wbegin 60//
#define wends 863
#define poadj 30//
#define neadj 30//
#define ubegin 60//
#define uend 863
#define vbegin 60  //
#define C 0.2
#define CIRCLENUM 50

double B1[6]={0,0.2,0.4,0.6,0.8,1};   //betra
 int K1[9]={50,100,200,300,400,500,600,700,860} ;     //k
 double B;
 int K;
void indirectnumber(double (*sou)[total],double (*des)[total],int route);
void initarr();
void unionarr();
double unionfunc(int i,int flag);
void pagerank();
void lan_sim_calc();
void Matrix(double (*matrix)[total],double *onematrix,int begin,int end,int col);
void unionpagerank(double *ranknumber);
double d_sim(int x,int y);
double id_sim(int x,int y);
/*add more function*/
int fangzhentemp[1600][1600];//接收数据文件
double finalfangzhen[total][total];//pagerank计算用的方阵
double finalfangzhentest[total];
double fangzhen[total][total];
double indrectfangzhen[total][total];//暂时未用
double ranknumber[total]; 
double indrectranknumber[total];
char str[total][50];
double pword[total];	 //每个词的概率
double pfangzhen[total][total];//每个词互现的概率
int cmpfun(const void *a,const void *b)
{
	double i=*(double *)a,j=*(double *)b;
	if(i>j)
		return -1;
	else if(i<j)
		return 1;
	else
		return 0;
}
void main()
{

 FILE *fp,*fdir,*fpfangzhen;
 if((fp=fopen("partdata_final_30.txt","rb"))==NULL)  //partdata_final.txt
  return ;
 if((fdir=fopen("newadj_30.txt","rb"))==NULL) //part_emotion_all_57_109_910
  return ;
 fread(fangzhentemp,sizeof(fangzhentemp),1,fp);
 int i,j=0;
 while( !feof(fdir) )
  fscanf(fdir,"%d %s\n",&i,str[j++] );

 initarr();
 lan_sim_calc();
 memcpy(indrectfangzhen,finalfangzhen,sizeof(indrectfangzhen));
 memcpy(indrectranknumber,ranknumber,sizeof(indrectranknumber));
 for(i=0;i<6;i++)
	 for(B=B1[i],j=0;j<9;j++)
	 {
		 K=K1[j];
		 memcpy(finalfangzhen,indrectfangzhen,sizeof(indrectfangzhen));
		 memcpy(ranknumber,indrectranknumber,sizeof(indrectranknumber));
		 unionarr();
		 pagerank();
	 }
 
 
 //printf("%d\n",sum);
}
void initarr()
{
 int i,j;
 double countnum;
 for(i=0;i<total;i++)
  for(j=0;j<total;j++)
   if(fangzhentemp[i][j])
    fangzhen[i][j]=fangzhentemp[i][j];
 //printf("%f",sum);
 for(i=0;i<poadj;i++)
 
   ranknumber[i]=1;
 for(i=poadj;i<neadj+poadj;i++)
  ranknumber[i]=-1;
/************************************************************************/
/* 计算每个词出现的概率，共现的次数 */
/************************************************************************/
 for(i=0;i<total;i++)
 {
  for(countnum=0,j=0;j<total;j++)
  {
   countnum+=fangzhen[i][j];
   pfangzhen[i][j]=pfangzhen[j][i]=fangzhen[i][j]/allwordnum;
  }
  pword[i]=countnum/allwordnum;
 
 }
 
 
}
void unionarr()
{
 int i,j;
 double temp1,temp2;
 for(i=wbegin;i<wends;i++)
 {
	 temp1=unionfunc(i,1);
	 temp2=unionfunc(i,0);
	 memcpy(finalfangzhentest,finalfangzhen[i],sizeof(finalfangzhentest));
	 qsort((void *)finalfangzhentest,total,sizeof(double), cmpfun    );
	 for(j=sbegin;j<wends;j++)
		 if(finalfangzhen[i][j]<finalfangzhentest[K])
			 finalfangzhen[i][j]=0;
  for(j=sbegin;j<wends;j++)
  {
   if(temp1 == 0 )
    {finalfangzhen[j][i]=finalfangzhen[i][j]=0;}
   else
   {
	   if(finalfangzhen[i][j]>0)
		   if(temp1 == 0)
			   {finalfangzhen[j][i]=finalfangzhen[i][j]=0;}
		   else
		        finalfangzhen[j][i]=finalfangzhen[i][j]=finalfangzhen[i][j]/temp1;
	   else
		   if(temp2 == 0)
			   {finalfangzhen[j][i]=finalfangzhen[i][j]=0;}
		   else
		   finalfangzhen[j][i]=finalfangzhen[i][j]=finalfangzhen[i][j]/temp2;
   }
   if(i==110||finalfangzhen[i][j]>1 ||finalfangzhen[i][j]<-1)
	   i=i;
  }
 }
 
}
double unionfunc(int i,int flag)
{
 int j;
 double u,v,po,ne;
 u=v=po=ne=0;
 for(j=sbegin;j<sends;j++)
  if(finalfangzhen[i][j]>0)
	  po+=finalfangzhen[i][j];
  else
	  ne+=finalfangzhen[i][j];
 for(j=wbegin;j<wends;j++)
 {
 
   if(finalfangzhen[i][j]>0)
	  po+=finalfangzhen[i][j];
  else
	  ne+=finalfangzhen[i][j];
 }
 if(flag==1)
 return po;
 else
	 return ne;
}
void pagerank()
{
 int i,j=CIRCLENUM;
 FILE *fp;
 char str1[100];
 sprintf(str1,"d:\\Users\\Administrator\\Desktop\\Seed30\\result_Seed30_K%d_betra_%lf.txt",K,B);
 if((fp=fopen(str1,"w"))==NULL)
  return;
 double ys[wends-wbegin],*yw=ranknumber+wbegin,temp1,temp2;
 Matrix(finalfangzhen,ys,sbegin,sends,wbegin);
 while(j--)
 {
 
  Matrix(finalfangzhen,yw,wbegin,wends,wbegin);
  temp1=temp2=0;
	for(i=0;i<wends-wbegin;i++)
		printf("%lf %lf\n",ys[i],yw[i]),temp1+=ys[i],temp2+=yw[i];
	printf("%lf %lf\n",temp1,temp2);
  for(i=0;i<wends-wbegin;i++)
	  yw[i]=(1-B)*ys[i]+B*yw[i];
  unionpagerank(ranknumber);
  for(i=0;i<wends-wbegin;i++)printf(" %lf %s\n",yw[i],str[i+wbegin]);

 }
 for(i=0;i<wends;i++)
  fprintf(fp,"%03d. %20s %lf\n",i+1,str[i],ranknumber[i]);

  fclose(fp);
}
void Matrix(double (*matrix)[total],double *onematrix,int begin,int end,int col)
{
 int i,j=0;
 double sum=0;
 for(i=col;i<total;i++)
 {
	 sum=0;
  for(j=begin;j<end;j++)
  {
	  if(matrix[i][j]>1 || ranknumber[j]>1)
	  i=i;
   sum+=matrix[i][j]*ranknumber[j];
  }
  onematrix[i-col]=sum;
 }
}
void unionpagerank(double *ranknumber)
{
 double sum1=0,sum2=0;
 int i,po,ne;
 for(po=ne=0,i=wbegin;i<wends;i++)
 {
  if(ranknumber[i]>0)
   sum1+=ranknumber[i],po++;
  else if(ranknumber[i]<0)
   sum2+=ranknumber[i],ne++;
 }
 for(i=wbegin;i<wends;i++)
 {
  if(ranknumber[i]>0)
   ranknumber[i]/=sum1;
  if(i==143)
	  i=i;
  else if(ranknumber[i]<0)
   ranknumber[i]/=-sum2;
  if(ranknumber[i]>1)
	  i=i;
 }
 sum2=sum2;
}
void lan_sim_calc()
{
 int i,j;
 double temp;
 for(i=0;i<total;i++)
  for(j=i+1;j<total;j++)
  {
   if(fangzhen[i][j] ==0)
    temp=id_sim(i,j);
   else
    temp=d_sim(i,j);
   if(temp>1)
	   i=i;
   finalfangzhen[j][i]=finalfangzhen[i][j]=temp;
  }
   
}
double id_sim(int x,int y)
{
 int i,k,Ii=0,Ij=0;
 double m,n;
 double totalnum=0;
 for(i=0;i<total;i++)
 {
  if(fangzhen[x][i])
   Ii++;
  if(fangzhen[y][i])
   Ij++;
 }
 if(Ii==0 || Ij==0)
  return 0;
 for(totalnum=k=0;k<total;k++)
 {
  if( fangzhen[x][k] && fangzhen[y][k] )
  {
   m=d_sim(x,k);
   n=d_sim(y,k);
   totalnum+=m>n?m:n;
  }
 }
 
 return C*totalnum/Ii/Ij;
}
double d_sim(int x,int y)
{
 if(x==y)
  return 1;
 if(pfangzhen[x][y] == 0 || (pword[x]==0 || pword[y])==0)
  return 0;
 return (pfangzhen[x][y]*log10(pfangzhen[x][y]/(pword[x]*pword[y])));
}
