#include <stdio.h>

#define A 0
#define X 1
#define Y 2
#define Z 3
#define W 4
#define B 5
#define NA 6

int map[6][2] = {
    {X, Y},
    {NA, Z},
    {X, NA},
    {W, B},
    {B, Y},
    {Y, X}
};

int main(void)
{
    char path[110];
    int i;
    int city;
    
    while (1){
        scanf("%s", path);
        if (path[0] == '#'){
            break;
        }
        
        city = A;
        i = 0;
        while (path[i] != '\0'){
            if (map[city][path[i] - '0'] == NA){
                break;
            }
            city = map[city][path[i] - '0'];
            i++;
        }
        if (city == B){
            printf("Yes\n");
        }
        else {
            printf("No\n");
        }
    }
    return (0);
}