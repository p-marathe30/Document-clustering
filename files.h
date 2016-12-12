#include<iostream>
#include<string.h>
#include<math.h>
#include "tries.h"
#include <fstream>
using namespace std;
class files
{
public:
    char file_name[260];
    int min_index,max_index;
    int word_freq[100001];
    double mod_file=0;
    static tries g_trie;
    files(char file_n[])
    {
        strcpy(file_name,file_n);
        min_index=100001;
        max_index=1;
        int index;
        for(int i=0;i<100000;i++)
            word_freq[i]=0;
        FILE *f1;
        char ins[30],c;
        f1=fopen(file_name,"r");
        c=fgetc(f1);
        int i;
        while(c!=EOF)
        {
            i=0;
            while(!isalpha(c) && c!=EOF)c=fgetc(f1);
            if(c==EOF)break;
            while(isalpha(c))
            {
                c=tolower(c);
     //         printf("%c",c);
                ins[i++]=c;
                c=fgetc(f1);
            }
            ins[i]='\0';
        //printf("\n%s",ins);
            index=g_trie.insertin(ins);
            if(index>max_index)
                max_index=index;
            if(index<min_index)
                min_index=index;
            word_freq[index]++;

            c=fgetc(f1);
        }
    fclose(f1);


        for(int i=min_index;i<=max_index;i++)
        {
            mod_file+=pow(word_freq[i],2);
        }
        mod_file=sqrt(mod_file);
    }
    float operator*(const files &f)
    {
    double similarity=0;
    float sum=0;
    int i;
    cout<<" *";
    int from=max(min_index,f.min_index),to=min(max_index,f.max_index);
    for (i=from;i<=to;i++)
        {
            sum=sum+(word_freq[i]*f.word_freq[i]);
        }
    similarity=sum/(mod_file*f.mod_file);
    //cout<<similarity;
    return acos(similarity);
    }


    int file_word_freq(char search_word[])
    {
        int index;
        index=g_trie.insertin(search_word);
        return word_freq[index];
    }

};
tries files::g_trie;

