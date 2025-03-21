#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define SENTINEL 1000000000000000000

void merge(long long A[], long long left, long long mid, long long right){
  long long n1, n2, i, j, k;
  long long *L,*R;
  
  n1 = mid-left;
  n2 = right-mid;
  
  L = (long long*)malloc(sizeof(long long) *(n1 + 1));
  R = (long long*)malloc(sizeof(long long) *(n2 + 1));
  
  for(i = 0; i <= n1 - 1; i++){
    L[i] = A[left + i];
  }
  for(j = 0; j <= n2 - 1; j++){
    R[j] = A[mid + j];
  }
  
  L[n1] = SENTINEL;
  R[n2] = SENTINEL;
  
  i = 0;
  j = 0;
  
  for(k = left; k <= right - 1; k++){
   if(L[i] <= R[j]){
      A[k] = L[i];
      i++;
    }
    else{
      A[k] = R[j];
      j++;
    }
  }
  free(L);
  free(R);
}

void mergeSort(long long A[], long long left, long long right){
  long long mid;
  
  if(left + 1 < right){
    mid=(left + right)/2;
    mergeSort(A, left, mid);
    mergeSort(A, mid, right);
    merge(A, left, mid, right);
  }
}

int main(void){

    int N;

    scanf("%d", &N);

    long long a[N];

    for(int i = 0; i < N; i ++){
        scanf("%lld", &a[i]);
    }

    mergeSort(a, 0, N);

    long long A = 0, B = 0;

    if(N % 2 == 0){
        for(int i = N-1; i >= 0; i -= 2){
            A += a[i];
            B += a[i-1];
        }
        printf("%lld\n", A - B);
    }else{
        for(int i = N-1; i >= 1; i -= 2){
            A += a[i];
            B += a[i-1];
        }
        A += a[0];
        printf("%lld\n", A - B);
    }

    return 0;
}