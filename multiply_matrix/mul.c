#include<stdio.h>
#include<stdint.h>
#include<time.h>
#define N 1024



#ifdef DEBUG
    #define N 8
#else
    #define N 2048
    // How much is my L1 cache?
    // What is aligned bits?
    //
#endif



/*
 * Matrix multiply
 * 1. Tiling
 * 
 * 2. Cache coherence
 * 3. The fundamental thing about machine learing is matrix multiply
 * 4. 
 *
 *  Memory order row and column major
 */

float a[N][N];
float b[N][N];
float c[N][N];


uint64_t nanos(){
    struct timespec start;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    return (uint64_t)start.tv_sec*1000000000 + (uint64_t)start.tv_nsec;
}

void get_tflops(uint64_t start, uint64_t end, char *message){
    printf("%s", message);
    double tflops = (2.0*N*N*N)*1e-12;
    double s = (end-start)*1e-9;
    printf("%f TFLOPS/S\n", tflops/s);
}

/*
void get_tflops(uint64_t start, uint64_t end){
    double tflops = (2.0*N*N*N)*1e-12;
    double s = (end-start)*1e-9;
    printf("%f TFLOPS/S\n", tflops/s);
}
*/

BLOCK_SIZE = 16

void tiling_multiply(){

}

void basic_multiply(){
    uint64_t start = nanos();
    // float a[][2] = {
    //     { 1, 2 },
    //     { 3, 4 },
    // };
    // float b[][2] = {
    //     { 1, 2 },
    //     { 3, 4 },
    // };
    // Sometimes this matrix is not set to 0,0
    // Ig that only happens when this is in bss and not when in the
    // data segment.
    // float c[2][2];
    for(int i =0;i<N;i++){
        for(int j=0;j<N;j++){
            float acc = 0;
            for(int k=0;k<N;k++){
                //c[i][j] = c[i][j] + (a[i][k] * b[k][j]);
                acc += a[i][k] * b[k][j];
            }
            c[i][j] = acc;
            // printf("c[%d][%d] = %f\n", i, j, c[i][j]);
        }
    }
    uint64_t end = nanos();
    get_tflops(start, end, (char *)"Basic mutiplication:");
}

int main(){
    basic_multiply();
    return 0;
}
