#include<stdio.h>
#include<sys/time.h>

#define N 1024
#define LOOP 100

int A[N][N];
int B[N][N];
int C[N][N];


void add_matrix_aligned(int A[][N], int B[][N], int C[][N]);
void add_matrix_bad(int A[][N], int B[][N], int C[][N]);
void add_matrix_comp(int A[][N], int B[][N], int C[][N]);

void show(int A[][N]){
    
    int i, j;
    for(i=0; i<N; i++){
        for(j=0; j<N; j++){
            printf("%d ", A[i][j]);
        }
        puts("");
    }
    puts("");
}

int main(){
    
    struct timeval s, e;
    double time;

    int i, j;

/*
    for(i=0; i<N; i++){
        for(j=0; j<N; j++){
            a[i][j] = j+1;
            b[i][j] = j+1;
        }
    }

*/

    // compressed code
    add_matrix_comp(A, B, C);
    gettimeofday(&s, NULL);
    for(i=0; i<LOOP; i++) add_matrix_comp(A, B, C);
    gettimeofday(&e, NULL);

    time = (e.tv_sec - s.tv_sec) + (e.tv_usec - s.tv_usec)*1.0E-6;
    printf("add_matrix_comp :\t %lf [s]\n", time);

    
    // normal aligned code
    add_matrix_aligned(A, B, C);
    gettimeofday(&s, NULL);
    for(i=0; i<LOOP; i++) add_matrix_aligned(A, B, C);
    gettimeofday(&e, NULL);

    time = (e.tv_sec - s.tv_sec) + (e.tv_usec - s.tv_usec)*1.0E-6;
    printf("add_matrix_aligned :\t %lf [s]\n", time);

    
    // normal non-aligned code
    add_matrix_bad(A, B, C);
    gettimeofday(&s, NULL);
    for(i=0; i<LOOP; i++) add_matrix_bad(A, B, C);
    gettimeofday(&e, NULL);

    time = (e.tv_sec - s.tv_sec) + (e.tv_usec - s.tv_usec)*1.0E-6;
    printf("add_matrix_bad :\t %lf [s]\n", time);

    
    //show(C);

    return 0;

}
