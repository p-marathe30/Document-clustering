#include<stdio.h>
#include<string.h>
struct trie
{
    int val;
    struct trie *alpha[26];
};
trie* newnode()
{

    int i;
   trie *n= new trie;
        n->val=0;
    for(i=0;i<26;i++)
            n->alpha[i]=NULL;
    return n;
}


class tries
{
    public:
        unsigned int place;
        trie* root;

        tries()
        {
            root=NULL;
            place=1;
        }
        void unload_trie(trie *temp);
        ~tries()
        {
            if(root!=NULL)
            {
                unload_trie(root);
            }

        }
        int insertin(char input[]);

};
void tries::unload_trie(trie *temp)
{
    trie *t=temp;
    int i=0;
    for(i=0;i<26;i++)
    {
        if(t->alpha[i]!=NULL)
            unload_trie(t->alpha[i]);
    }
    delete(t);
}
int tries::insertin(char a[])
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
             //   printf("%c*",a[i]);
                n=n->alpha[a[i]-'a'];
                i++;
                if(i==l)break;
            }
            if(i==l)break;
            //printf("%d",i);
            if(i!=l)
            {
            //printf("%c*",a[i]);
            n->alpha[a[i]-'a']=newnode();

            }

        }
        if(n->val==0)
        {n->val=place++;}
        return n->val;
}

