/**
Necesito las siguientes matrices u_new, u_old, m
*/

#include "kernel_gpu.cuH"
#include <stdio.h>
#include <stdlib.h>

int main( int argc, char *argv ) {

    if(argc!=2){
       printf("usage: heatequation <number_of_steps*2>\n");
       return 1;
    }
    int steps_2=atoi(argv[1]);  // time 2 time steps
    int steps=1000;
    float u[N], u_new[N];   // N must be a perfect square number
    float *dev_u, *dev_u_new;
    float c=0.001;

    struct timeval tempo1, tempo2;
    
    long elapsed_utime;    /* elapsed time in microseconds */
    long elapsed_mtime;    /* elapsed time in milliseconds */
    long elapsed_seconds;  /* diff between seconds counter */
    long elapsed_useconds; /* diff between microseconds counter */



    // allocate the memory on the GPU
    HANDLE_ERROR( cudaMalloc( (void**)&dev_u, N * sizeof(float) ) );
    HANDLE_ERROR( cudaMalloc( (void**)&dev_u_new, N * sizeof(float) ) );

    // fill the array 'u' on the CPU
    // initial condition
    for (int i=0; i<N; i++){
        u[i]=0;
    }
    for (int i=0; i<DIM; i++) {
    // Horizontal boundary conditions
        u[i]       = i;
        u[i*DIM]   = i;
        u[N-1-i]     = i;
        u[N-1-i*DIM] = i;
    }

/*
//    printf("****Print u_old matrix****\n");
//    // display the results
//    for (int i=0; i<DIM; i++) {
//        for (int j=0; j<DIM; j++) {
//            printf( "%f\t", u[i*DIM+j] );
//        }
//        printf("----\n");
//    }
*/
    // copy the array 'u' to the GPU
    HANDLE_ERROR( cudaMemcpy( dev_u, u, N * sizeof(float),
                              cudaMemcpyHostToDevice ) );

//    printf("Press 'Enter' to show the elapsed time: ");
    gettimeofday(&tempo1, NULL);
    for (int i=0;i<steps;i++){
        if (i%2==0)
            new_time_blocks<<<N,1>>>( dev_u, dev_u_new, c);
        else
            new_time_blocks<<<N,1>>>( dev_u_new, dev_u, c);
    }

//
//    gettimeofday(&tempo2, NULL);
//    printf("tempo2.tv_sec = %ld, tempo2_tv_usec = %ld\n",
//            tempo2.tv_sec, tempo2.tv_usec);
//    printf("tempo1.tv_sec = %ld, tempo1_tv_usec = %ld\n",
//            tempo1.tv_sec, tempo1.tv_usec);
//    elapsed_seconds  = tempo2.tv_sec  - tempo1.tv_sec;
//    elapsed_useconds = tempo2.tv_usec - tempo1.tv_usec;
//
//    printf("Elapsed time = %ld seconds + %ld microseconds\n",
//            elapsed_seconds, elapsed_useconds);
//
//    elapsed_utime = (elapsed_seconds) * 1000000 + elapsed_useconds;
//    elapsed_mtime = ((elapsed_seconds) * 1000 + elapsed_useconds/1000.0) + 0.5;
//
//    printf("Elapsed time = %ld microseconds\n", elapsed_utime);
//    printf("Elapsed time = %ld milliseconds\n", elapsed_mtime);
//



    // copy the array 'c' back from the GPU to the CPU
    HANDLE_ERROR( cudaMemcpy( u_new, dev_u_new, N * sizeof(float),
                              cudaMemcpyDeviceToHost ) );
    
//    printf("****Print u_new matrix****\n");
    // display the results
    for (int i=0; i<DIM; i++) {
        for (int j=0; j<DIM; j++) {
            printf( "%f\t", u_new[i*DIM+j] );
        }
        printf("\n");
    }

    // free the memory allocated on the GPU
    HANDLE_ERROR( cudaFree( dev_u ) );
    HANDLE_ERROR( cudaFree( dev_u_new ) );

    return 0;
}
