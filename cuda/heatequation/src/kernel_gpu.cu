#include "kernel_gpu.cuH"

/**
Generate the new u in the next time step using blocks
*/
__global__ void new_time_blocks(float *u, float *u_new,float c) {
    // XXX: Because the boundary conditions, this must started in 1
    // u_[1], that is the reason why i added +1
    int tid = blockIdx.x;  // this thread handles the data at its thread id
	// The array is a matrix (N+1)*(N)
	// Just chain the values of u in the interval 1,rowdim

    if (tid < N){
        // If tid belows to the boundary don't make anything(fixed boundary cond)
        if(tid<DIM || tid > N-1-DIM){           // Horizontal boundary
            u_new[tid]=u[tid];
        }else if(tid%DIM==0 || (tid+1)%DIM==0){ //Vertical Boundary
            u_new[tid]=u[tid];
        }else{  // make a time step
            u_new[tid] = u[tid]+c*(u[tid+1]+u[tid-1]+u[tid-DIM]+u[tid+DIM]-4*u[tid]);
        }
        
    }
}

/**
Generate the new u in the next time step using threads
*/

__global__ void new_time_threads(float *u, float *u_new,float c) {
    int tid = blockIdx.x;    // this thread handles the data at its thread id
    if (tid < N)
        u_new[tid] = u[tid+1]+u[tid-1]-4*u[tid] ;
        //u_new[tid] = u[tid+1]+u[tid-1]+u[tid-dim]+u[tid+dim]-4*u[tid] ;
}
