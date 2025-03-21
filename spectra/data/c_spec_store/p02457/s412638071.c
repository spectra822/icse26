#include <stdio.h>

int search(int s[],int key,int head,int tail){
    if(head>tail)return -1;
    
    int mid=(head+tail)/2;
    
    if(s[mid]==key)return mid;
    else if(s[mid]>key)tail=mid-1;
    else if(s[mid]<key)head=mid+1;
    
    return search(s,key,head,tail);
}
int getLB(int s[],int key,int head,int tail){
    if(s[0]>key||tail<0)return 0;
    if(s[tail]<key||head>tail)return tail+1;
    
    int mid=(head+tail)/2;
    
    if(s[mid]<key)head=mid+1;
    else if(s[mid]>=key){
        if(s[mid-1]<key)return mid;
        else tail=mid-1;
    }
        
    return getLB(s,key,head,tail);
}
int insert(int s[],int key,int cnt){
    int d;
    if(cnt==0)d=0;
    else d=getLB(s,key,0,cnt-1);
    
    int i;
    for(i=cnt;i>d;i--)s[i]=s[i-1];
    s[i]=key;
    return 1;
}
int delete(int s[],int key,int cnt){
    int d;
    d=search(s,key,0,cnt-1);
    if(d<0)return -1;
    
    int i;
    for(i=d;i<cnt-1;i++)s[i]=s[i+1];
    return 1;
}
void dump(int s[],int l,int r,int cnt){
    int i;
    i=getLB(s,l,0,cnt-1);

    while(s[i]<=r&&i<cnt)printf("%d\n",s[i++]);
    return;
}
void print(int s[],int cnt){
    printf("cnt=%d,s:",cnt);
    for(int i=0;i<cnt;i++)printf("%d ",s[i]);
    printf("\n");
    return;
}
int main(void){
    int q;
    scanf("%d\n",&q);
    
    int s[q];
    int cnt=0;
    
    int com,x,y;
    while(q--){
        scanf("%d ",&com);
        switch(com){
            case 0:
                //insert
                scanf("%d\n",&x);
//    printf("insert:%d\n",x);
                if(search(s,x,0,cnt-1)==-1){
                    if(insert(s,x,cnt)==1)cnt++;
                }
                printf("%d\n",cnt);
                break;
            case 1:
                //find
                scanf("%d\n",&x);
//    printf("find:%d\n",x);
                if(search(s,x,0,cnt-1)==-1)printf("0\n");
                else printf("1\n");
                break;
            case 2:
                //delete
                scanf("%d\n",&x);
//    printf("delete:%d\n",x);
                if(delete(s,x,cnt)==1)cnt--;
                break;
            case 3:
                //dump
                scanf("%d %d\n",&x,&y);
//    printf("dump:%d %d\n",x,y);
                dump(s,x,y,cnt);
                break;
        }
//        print(s,cnt);
    }
    
    return 0;
}

