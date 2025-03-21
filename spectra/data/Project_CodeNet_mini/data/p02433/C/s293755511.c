#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INSERT '0'
#define MOVE '1'
#define ERASE '2'
#define END 1000000001

typedef struct Cell {
	int data;
	struct Cell* prev;
	struct Cell* next;
} Cell;

Cell* newCell(int data) {
    Cell* cell = malloc(sizeof(Cell));
    cell->data = data;
    cell->prev = NULL;
    cell->next = NULL;
    return cell;
}

void print(Cell *cell) {
    // 先頭まで移動する
	while (cell->prev != NULL) {
		cell = cell->prev;
	}

	do {
	    if (cell->data != END) {
			printf("%d\n", cell->data);
			cell = cell->next;
		}
	} while (cell->next != NULL);
}

int isEnd(Cell *cursor) {
	return (cursor != NULL && cursor->data == END);
}

int isFront(Cell *cursor) {
	return (cursor != NULL && cursor->prev == NULL);
}

Cell* insert(Cell *cursor, int data) {
	if (isFront(cursor)) {
		Cell *new = newCell(data);
		new->next = cursor;
		cursor->prev = new;
		return new;
	}

	Cell *new = newCell(data);
	Cell *prev = cursor->prev;
	new->prev = prev;
	new->next = cursor;
	prev->next = new;
	cursor->prev = new;
	return new;
}

Cell* move(Cell *cursor, int d) {
	if (d == 0) {
		return cursor;
	}

	if (d < 0) {
		for (;d < 0; d++) {
			if (isFront(cursor)) {
				printf("Cursor is already front.\n");
				exit(1);
			}

			cursor = cursor->prev;
		}
		return cursor;
	}

	for (;d > 0; d--) {
		if (cursor->next == NULL) {
			printf("Cursor has no next.\n");
			exit(2);
		}

		cursor = cursor->next;
	}
	
	return cursor;
}

Cell* erase(Cell *cursor) {
	if (isEnd(cursor)) {
		return cursor;
	}
	
	if (isFront(cursor)) {
	    Cell *next = cursor->next;
	    next->prev = NULL;
	    free(cursor);
	    return next;
	}

	Cell *prev = cursor->prev;
	Cell *next = cursor->next;
	prev->next = next;
	next->prev = prev;
	free(cursor);
	return next;
}


void answer() {
	Cell *cursor;
	int q = 0;
	char a[15];

	fgets(a, 15, stdin);
	q = atoi(a);
	cursor = newCell(END);

	while (q--) {
	    fgets(a, 15, stdin);
		if (a[0] == INSERT) {
            cursor = insert(cursor, atoi(a+2));
		} else if (a[0] == MOVE) {
		    cursor = move(cursor, atoi(a+2));
		} else if (a[0] == ERASE) {
		    cursor = erase(cursor);
		}

	}

	print(cursor);
}

int test() {
	Cell *cur = newCell(END);
	cur = insert(cur, 1);
	cur = insert(cur, 2);
	cur = insert(cur, 3);
	cur = move(cur, 1);
	cur = erase(cur);
	print(cur);
	return 0;
}

int main(void){
	answer();
}


