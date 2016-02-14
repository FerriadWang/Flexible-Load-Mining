#include<stdlib.h>
#include<stdio.h>
#include<iostream.h>
#include<string.h>
#include<math.h>
#include<vector>
#include<time.h>
using namespace std;
FILE *fin,*fout;
#define col 25
#define line 226
#define MaxK 12
int ColK[col-1];
float means[MaxK][col-1];
void PrintMeans(float means[MaxK][col-1]);
struct Tuple
{
	float arr[col];
	int label[col-1];
};
struct ClusterType
{
	int label;
};
float GetIDisXY(float x,float y)
{
	 return sqrt((x-y)*(x-y));
}
int IClustOfTuple(float means[MaxK][col-1],float tuple,int i)
{
	float dis=GetIDisXY(means[0][i],tuple);
	float temp;
	int label=0;
	int j;
	for(j=1;j<ColK[i];j++)
	{
		temp=GetIDisXY(means[j][i],tuple);
		if(temp<dis)
		{
			dis=temp;
			 label=j;
		}
	}
	return label;
}
//获得平方误差
float GetVar(vector<ClusterType> type[],vector<Tuple> clusters,float means[MaxK][col-1],int i)
{
	float var=0;
	int j;
	 for( j=0;j<ColK[i];j++)
	 {
		vector<ClusterType> temp=type[j];
		 for(int n=0;n<temp.size();n++)
		 {
			 var+=GetIDisXY(means[j][i],clusters[temp[n].label].arr[i]);
		 }
	 }
	 return var;
}
float GetMeans(vector<ClusterType> type,vector<Tuple> clusters,int i)
{
	float num =type.size();
	int j;
	float sum=0;
	for(j=0;j<num;j++)
	{
		int label=type[j].label;
		sum+=clusters[label].arr[i];
	}
	return sum/num;
}
void DisplayMeans(float means[MaxK][col-1])
{
	int i,j;
	for(i=0;i<MaxK;i++)
	{
		for(j=0;j<col-1;j++)
			printf("%f ",means[i][j]);
		printf("\n");
	}
}
void KMeans(vector<Tuple> tuples,float means[MaxK][col-1])
{
	int i;
	/*
	float **means;
	means=new float *[MaxK];
	for(i=0;i<MaxK;i++)
		*means=new float [col-1];*/
	//float means[MaxK][col-1];
	for(i=0;i<col-1;i++)
		ColK[i]=8;
	vector<ClusterType> clusterlabel[MaxK];
	for(i=0;i<col-1;i++)
	{
		if(i==0)
		{
			i=0;
		}
		int j;
		 for(j=0;j<ColK[i];j++)
		 {
			 int tempj=rand()%(line);
			 means[j][i]=tuples[tempj].arr[i];
		 }
		 DisplayMeans(means);
			int templabel=0;
			 for(j=ColK[i];j<tuples.size();j++)
			 {
				templabel=IClustOfTuple(means,tuples[j].arr[i],i);
				ClusterType temp;
				temp.label=j;
				clusterlabel[templabel].push_back(temp);
			 }
			 float oldvar=-0.1;
			  float newvar=GetVar(clusterlabel,tuples,means,i);
			  while(fabs(oldvar-newvar)>=0.1)
			  {
				for(j=0;j<ColK[i];j++)
				{
					if(clusterlabel[j].size()>0)
					means[j][i]=GetMeans(clusterlabel[j],tuples,i);
				}

				oldvar=newvar;
				 newvar=GetVar(clusterlabel,tuples,means,i);
				 
				  for(j=0;j<ColK[i];j++)
					  clusterlabel[j].clear();
				  
				  for(j=0;j<tuples.size();j++)
				  {
					    templabel=IClustOfTuple(means,tuples[j].arr[i],i);
						ClusterType temp;
						temp.label=j;
						clusterlabel[templabel].push_back(temp);
						tuples[j].label[i]=templabel;
				  }
			  }
			  for(j=0;j<ColK[i];j++)
				  clusterlabel[j].clear();
		
	}

	fout=fopen("ClusterData.txt","w");
	
	for(i=0;i<line;i++)
	{//rintf(fout,"%.f ",tuples[i].arr[col-1]);
	for(int j=0;j<col-1;j++)
	{
		fprintf(fout,"%d ",tuples[i].label[j]);
	}
	fprintf(fout,"\n");
	
  }
	fout=fopen("Means.txt","w");
	PrintMeans(means);
}
void PrintMeans(float means[MaxK][col-1])
{
	int i,j;
	for(i=0;i<MaxK;i++)
	{
 		for(j=0;j<col-1;j++)
		{	
			fprintf(fout,"%f ",means[i][j]);
		}
		fprintf(fout,"\n");
	}
}
void main()
{
  int i,j;
  memset(means,0,sizeof(means));
  printf("Hello\n");
  fin=fopen("handandata1.txt","r");
  vector<Tuple> tuples;
  Tuple tuple;
  float temp;
  for(i=0;i<line;i++)
  {
	  for(j=0;j<col-1;j++)
	  {
		fscanf(fin,"%f ",&temp);
		tuple.arr[j]=temp;
	  }
	 tuples.push_back(tuple);
  }
  KMeans(tuples,means);
  system("pause");
}