// AOJ 2613: Unordered Operators
// 2017.10.10 bal4u@uu

#include <stdio.h>
#include <ctype.h>

#define MAX 210

#define VAL   10
#define LEFT  -1
#define RIGHT -2
#define PLUS   0 
#define MINUS  1
#define MUL    2

typedef struct { long long v; char id; } T;
T stack[MAX+3], buf[MAX+3]; int top, end;

char str[MAX], *p;

int tbl[13][3] = {
	{1,2,3},{1,3,2},{2,1,3},{2,3,1},{3,1,2},{3,2,1},
	{1,1,1},{1,1,2},{2,2,1},{1,2,1},{2,1,2},{1,2,2},{2,1,1}}; int rid;

long long getInt(void)
{
	long long n = 0;
	while (isdigit(*p)) n = 10 * n + (*p++ - '0');
	return n;
}

int token(char c)
{
	if (c == '+') return PLUS;
	if (c == '-') return MINUS;
	return MUL;
}

int rank(int op)
{
	if (op == LEFT) return LEFT;
	return tbl[rid][op];
}

int main()
{
	int i, id, f;
	long long v1, v2, ans;

	scanf("%s", str); f = 1;
	for (rid = 0; rid < 13; rid++) {
		p = str, top = 0, end = 0;
		while (*p) {
			if (isdigit(*p)) buf[end].id = VAL, buf[end++].v = getInt();
			else if (*p == ')') {
				while (top > 0 && stack[top-1].id != LEFT) buf[end++] = stack[--top];
				p++, top--;
			} else if (*p == '(') stack[top++].id = LEFT, p++;
			else {
				id = token(*p++);
				while (top > 0) {
					if (rank(id) <= rank(stack[top-1].id))
						buf[end++] = stack[--top];
					else break;
				}
				stack[top++].id = id;
			}
		}
		while (top > 0) buf[end++] = stack[--top];

		for (top = i = 0; i < end; i++) {
			if ((id = buf[i].id) == VAL) stack[top++].v = buf[i].v;
			else {
				v1 = stack[--top].v, v2 = stack[--top].v;
				if      (id == PLUS)  v2 += v1;
				else if (id == MINUS) v2 -= v1;
				else if (id == MUL)   v2 *= v1;
				stack[top++].v = v2;
			}
		}
		if (f) ans = stack[--top].v, f = 0;
		else if (ans < stack[--top].v) ans = stack[top].v;
	}
	printf("%lld\n", ans);
	return 0;
}