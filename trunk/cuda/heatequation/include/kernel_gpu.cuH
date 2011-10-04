#include <stdio.h>
#include <sys/time.h>

// Matrix dimension DIM to array dimension N
#define DIM 10
#define N   DIM*DIM

static void HandleError( cudaError_t err,
                         const char *file,
                         int line ) {
    if (err != cudaSuccess) {
        printf( "%s in %s at line %d\n", cudaGetErrorString( err ),
                file, line );
        exit( EXIT_FAILURE );
    }
}

#define HANDLE_ERROR( err ) (HandleError( err, __FILE__, __LINE__ ))


#define HANDLE_NULL( a ) {if (a == NULL) { \
                            printf( "Host memory failed in %s at line %d\n", \
                                    __FILE__, __LINE__ ); \
                            exit( EXIT_FAILURE );}}


// Functions for add_loop_gpu
__global__ void new_time_blocks(float *u, float *u_new,float c);
__global__ void new_time_threads(float *u, float *u_new,float c);
#define M   100000
#define W   101 // MUST be a odd number (2n+1)
