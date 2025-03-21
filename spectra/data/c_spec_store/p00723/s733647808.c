#include <stdio.h>
#include <string.h>

char a[1024][80];
int ap;

void reverse(char *s, int n)
{
    int i;
    for(i=0;i<n/2;++i) {
        char t=s[i];
        s[i]=s[n-1-i];
        s[n-1-i]=t;
    }
}
void swap(char *s1, char *s2)
{
    int i=0;
    char t[80], *p;
    for(p=s2;*p;++p) t[i++]=*p;
    for(p=s1;p!=s2;++p) t[i++]=*p;
    t[i]=0;
    strcpy(s1, t);
}
int contain(char* s)
{
    int i;
    for(i=0;i<ap;++i) if (!strcmp(a[i], s)) return 1;
    return 0;
}

int main(void)
{
    int n;
    scanf("%d", &n);
    while (n--) {
        int i, len;
        char s[80], t[80];
        scanf("%s", s);

        ap=0;
        len=strlen(s);
        strcpy(t, s);
        for(i=1;i<len;++i) {
            if (!contain(s)) strcpy(a[ap++], s);
            reverse(s, i); if (!contain(s)) strcpy(a[ap++], s);
            reverse(s+i, len-i); if (!contain(s)) strcpy(a[ap++], s);
            reverse(s, i); if (!contain(s)) strcpy(a[ap++], s);
            strcpy(s, t);
            swap(s, s+i);
            if (!contain(s)) strcpy(a[ap++], s);
            reverse(s, len-i); if (!contain(s)) strcpy(a[ap++], s);
            reverse(s+len-i, i); if (!contain(s)) strcpy(a[ap++], s);
            reverse(s, len-i); if (!contain(s)) strcpy(a[ap++], s);
            strcpy(s, t);
        }
        printf("%d\n", ap);
    }
    return 0;
}