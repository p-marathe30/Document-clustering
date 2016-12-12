#include <stdio.h>
#include <string.h>
#include <math.h>
#include<malloc.h>
#include<ctype.h>
#include<time.h>
#include <sys/types.h>
#include <dirent.h>
#define PI 3.14159265
char file_name[100][30];
int count_file[100][240000];
int depth=0;
int place=1;
int space=0;
int done=0;
struct trie
{
    int val;
    struct trie *alpha[26];
}*root=NULL;
struct trie* newnode()
{
    space++;
    int i;
   struct trie *n= malloc(sizeof(struct trie));
        n->val=0;
    for(i=0;i<26;i++)
            n->alpha[i]=NULL;
    return n;
}
void insertin(char a[],int ctr[])
{

    int i=0,l=strlen(a);
    if(root==NULL)
    {
        root=newnode();
    }
struct trie* n=root;
    while(i<l)
        {

            while(n->alpha[a[i]-'a']!=NULL && i<l)
            {
                n=n->alpha[a[i]-'a'];
                i++;
                if(i==l)break;
            }
            if(i==l)break;
            if(i!=l)
            {
            n->alpha[a[i]-'a']=newnode();

            }
        }
        if(n->val==0)
        {n->val=place++;}
        ctr[n->val]++;
}
int search(char a[])
{
    int i=0,l=strlen(a);
    struct trie* n=root;
    while(i<l)
        {

            while(n->alpha[a[i]-'a']!=NULL && i<l)
            {
                n=n->alpha[a[i]-'a'];
                i++;
            }
            if(i==l)
            {
                if(n->val!=0)
                printf("FOUND!");
                else
                    printf("NOT FOUND!");
                return 1;
            }
            else
            {
                printf("NOT FOUND!");
                return 0;
            }
            }
    printf("NOT FOUND");
    return 0;
}
char k[10];
char *conv(int i)
{
    int j=0;
    while(i!=0)
    {
        k[j++]=i%10 +'0';
        i/=10;
    }
    k[j]='\0';
    return strrev(k);
}
float similarity(int ctr1[],int ctr2[])
{
    int i;
    float sum=0;
    float mod1=0,mod2=0;
    for(i=0;i<place;i++)
    {
        sum=sum+ctr1[i]*ctr2[i];
        mod1+=(pow(ctr1[i],2));
        mod2+=(pow(ctr2[i],2));
    }
    mod1=sqrt(mod1);
    mod2=sqrt(mod2);
    float ans=sum/(mod1*mod2);
    return ans;
}
int istxt(char name[])
{
    int l=strlen(name);
    int i=l-4,j=0;
    char  txt[5];
    for(i=l-4;i<=l-1;i++)
    {
        txt[j++]=name[i];
    }
    txt[j]='\0';
    if(strcmp(txt,".txt")==0)
        {
            return 1;
        }
    return 0;
}

int main()
{
  printf("The files are:\n");
    FILE *f1;
    int i=0,j;
    for(i=0;i<60;i++)
        for(j=0;j<240000;j++)
           {
               count_file[i][j]=0;
           }
    char ins[50];
    char c;
    int file_no=0;
    DIR *dp;
    struct dirent *ep;
    dp = opendir ("C:");
    if (dp != NULL)
    {
      while (ep=readdir(dp))
        {
            if(istxt(ep->d_name)==1)
                strcpy(file_name[file_no++],ep->d_name);
        }
      (void) closedir (dp);
    }
    else
        perror("no such directory!");
    int index;
    clock_t tstart=clock();
    for(index=0;index<file_no;index++)
    {
        printf("%s\n",file_name[index]);
        f1=fopen(file_name[index],"r");
        if(f1==NULL){printf("no such file");break;}
        c=fgetc(f1);
    while(c!=EOF)
    {
        i=0;
        while(!isalpha(c) && c!=EOF)c=fgetc(f1);
        if(c==EOF)break;
        while(isalpha(c))
        {
            c=tolower(c);
            ins[i++]=c;
            c=fgetc(f1);
        }
        ins[i]='\0';
        insertin(ins,count_file[index]);
        c=fgetc(f1);
    }
    fclose(f1);
    }
    printf("\n\n");
    float mean=0;
    float stde=0;
    int N=0;
    float sim[100][100];
    for(i=0;i<file_no;i++)
    {
        for(j=i+1;j<file_no;j++)
            {
                N++;
                sim[i][j]=similarity(count_file[i],count_file[j]);
                mean+=sim[i][j];
            }
    }
    mean=mean/N;
    for(i=0;i<file_no;i++)
    {
        for(j=i+1;j<file_no;j++)
        {
            stde+=pow((sim[i][j]-mean),2);
        }
    }
    stde/=N;
    stde=sqrt(stde);
    int no_suspects=1;
    char grade[100][100];
    printf("\nthe grading result is:\n");
    for(i=0;i<file_no;i++)
    {
        for(j=i+1;j<file_no;j++)
        {
            if(sim[i][j]>=(mean+1.5*stde))
                {
                    if((acos(sim[i][j])*180/PI)>10)grade[i][j]='A';
                    else
                    {
                        no_suspects=0;
                        grade[i][j]='S';
                        printf("(%s and %s) are the suspects!\n\n",file_name[i],file_name[j]);
                    }
                }
            else if(sim[i][j]<mean+1.5*stde && sim[i][j]>=mean+0.5*stde)
                grade[i][j]='A';
            else if(sim[i][j]<mean+0.5*stde && sim[i][j]>=mean)
                grade[i][j]='B';
            else
                grade[i][j]='N';
        }
    }
    if(no_suspects==1)
        printf("\nEveryone is honest");
    printf("\nthe mean is:%f and the standard deviation is:%f",mean,stde);
    printf("\ntime taken by the algorithm=%0.2f",(double)(clock()-tstart)/CLOCKS_PER_SEC);
    printf("\namount of memory used:%f mb\n",1.0*space*108/(1024*1024));
    return 0;
}
