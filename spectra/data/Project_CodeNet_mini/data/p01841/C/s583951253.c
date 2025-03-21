/*
A2740
title:Rooted Tree for Misawa-san
@kankichi573
*/
#include <stdio.h>
#include <string.h>
char input_tree[2][100000];
char ans[100000];
char *ap;
char zeros[1]="\0";

typedef struct  {
  char *sptr;
  int  len;
} mystr_;

void display(mystr_ *str)
{
  int i;
  for(i=0;i<str->len;i++)
    printf("%c",str->sptr[i]);
#ifdef DEBUG
  printf("{%d}",str->len);
#endif
  printf("\n");
}

void analyze_tree(mystr_ *in,mystr_ *left,mystr_ *right,int *val)
{
  char *p;
  int lv,i;

  left->sptr = p = in->sptr;

  for(i=0,lv=0;i<in->len;i++)
    {
      if(p[i]=='[')
	{
	if(lv==0)
	  {
	    left->len=i;
	    *val = atoi(p+i+1);
	  }
	
	
	  lv++;
	}
      else if(p[i]==']')
	{
	  if(lv==1)
	    {
	      right->sptr=&p[i+1];
	      right->len =in->len-i-1;
	    }
	  lv--;
	}
      else if(p[i]=='(')
	lv++;
      else if(p[i]==')')
	lv--;
    }
}

int is_empty_tree(mystr_ *in)
{
  if(in->len==2)
    return(1);
  else
    return(0);
}

void remove_paren(mystr_ *in)
{
  in->len  -= 2;
  in->sptr ++;
}


void add_tree(mystr_ *in1,mystr_ *in2,mystr_ *out)
{
  mystr_ stree[2][2],sstree[2];
  int v[2],val,le,i;

  analyze_tree(in1,&stree[0][0],&stree[0][1],&v[0]);
  analyze_tree(in2,&stree[1][0],&stree[1][1],&v[1]);
  val = v[0]+v[1];

  if(is_empty_tree(&stree[0][0]) || is_empty_tree(&stree[1][0]))
    {
      sstree[0].sptr=zeros;
      sstree[0].len =0;
    }
  else
    {
      remove_paren(&stree[0][0]);
      remove_paren(&stree[1][0]);
      add_tree(&stree[0][0],&stree[1][0],&sstree[0]);
    }
  if(is_empty_tree(&stree[0][1]) || is_empty_tree(&stree[1][1]))
    {
      sstree[1].sptr=zeros;
      sstree[1].len =0;
    }
  else
    {
      remove_paren(&stree[0][1]);
      remove_paren(&stree[1][1]);
      add_tree(&stree[0][1],&stree[1][1],&sstree[1]);
    }

  out->sptr=ap;

  sprintf(ap,"(%.*s)[%d](%.*s)",sstree[0].len,sstree[0].sptr,val,
	  sstree[1].len,sstree[1].sptr);

  while(*ap)
    ap++;
  out->len=ap - out->sptr;

}

int main()
{
  char *l,*r;
  int llen,rlen,val;
  mystr_ tree[3],ltree,rtree;
  
  scanf("%s",&(input_tree[0][0]));
  tree[0].sptr=&(input_tree[0][0]);
  tree[0].len =strlen(&(input_tree[0][0]));
  scanf("%s",&(input_tree[1][0]));
  tree[1].sptr=&(input_tree[1][0]);
  tree[1].len =strlen(&(input_tree[1][0]));
  ap=&ans[0];

  add_tree(&tree[0],&tree[1],&tree[2]);
  display(&tree[2]);

  return(0);
}