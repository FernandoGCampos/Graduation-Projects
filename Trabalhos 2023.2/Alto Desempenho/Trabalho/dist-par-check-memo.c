// to compile: mpicc dist-par-check-memo.c -o dist-par-check-memo -lm -fopenmp -O3 -fopt-info-vec-optimized -ffast-math
// to run: mpirun -np <number_of_processes> dist-par-check-memo <matrix_size> <random_seed> <num_of_threads>

// time mpirun -np 4 ./dist-par-check-memo 100 1000 4
// time mpirun -np 4 ./dist-par-check-memo 200 1 6

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <float.h>
#include <limits.h>

#include <mpi.h>
#include <omp.h>


#include "memory.h"

int get_memory_usage_kb(long* vmrss_kb, long* vmsize_kb)
{
    /* Get the the current process' status file from the proc filesystem */
    FILE* procfile = fopen("/proc/self/status", "r");

    long to_read = 8192;
    char buffer[to_read];
    int read = fread(buffer, sizeof(char), to_read, procfile);
    fclose(procfile);

    short found_vmrss = 0;
    short found_vmsize = 0;
    char* search_result;

    /* Look through proc status contents line by line */
    char delims[] = "\n";
    char* line = strtok(buffer, delims);

    while (line != NULL && (found_vmrss == 0 || found_vmsize == 0) )
    {
        search_result = strstr(line, "VmRSS:");
        if (search_result != NULL)
        {
            sscanf(line, "%*s %ld", vmrss_kb);
            found_vmrss = 1;
        }

        search_result = strstr(line, "VmSize:");
        if (search_result != NULL)
        {
            sscanf(line, "%*s %ld", vmsize_kb);
            found_vmsize = 1;
        }

        line = strtok(NULL, delims);
    }

    return (found_vmrss == 1 && found_vmsize == 1) ? 0 : 1;
}

#define MAX_POINT_VALUE 100
#define MIN_POINT_VALUE 0

#define MAX_POINT_DIFFERENCE MAX_POINT_VALUE - MIN_POINT_VALUE

// Calcula a distância de manhattan entre dois pontos
int manhattan_distance(const int x1, const int y1, const int z1, const int x2, const int y2, const int z2){
    return abs(x1 - x2) + abs(y1 - y2) + abs(z1 - z2);
}

// Calcula a distância Euclidiana entre dois pontos
double euclidean_distance(const int x1, const int y1, const int z1, const int x2, const int y2, const int z2){
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2) + pow(z1 - z2, 2));
}

// Encontra a maior e a menor distância de manhattan entre um ponto e os próximos da matrix
void get_manhattan(const int point, const int* matrix_x, const int* matrix_y, const int* matrix_z,
                   const int last, int* min_distance, int* max_distance){
    int i;
    int min_dist = INT_MAX;
    int max_dist = 0;

    const int x = matrix_x[point];
    const int y = matrix_y[point];
    const int z = matrix_z[point];

    #pragma omp simd reduction(min : min_dist) reduction(max : max_dist)
    for(i = point+1; i < last; ++i){
        const int dist = manhattan_distance(x, y, z, matrix_x[i], matrix_y[i], matrix_z[i]);
        if(dist < min_dist) min_dist = dist;
        if(dist > max_dist) max_dist = dist;
    }

    *min_distance = min_dist;
    *max_distance = max_dist;
}

// Encontra a maior e a menor distância euclidiana entre um ponto e os próximos da matrix
void get_euclidean(const int point, const int* matrix_x, const int* matrix_y, const int* matrix_z,
                   const int last, double* min_distance, double* max_distance){
    int i;
    double min_dist = DBL_MAX;
    double max_dist = 0;

    const int x = matrix_x[point];
    const int y = matrix_y[point];
    const int z = matrix_z[point];

    #pragma omp simd reduction(min : min_dist) reduction(max : max_dist)
    for(i = point+1; i < last; ++i){
        const double dist = euclidean_distance(x, y, z, matrix_x[i], matrix_y[i], matrix_z[i]);
        if(dist < min_dist) min_dist = dist;
        if(dist > max_dist) max_dist = dist;
    }

    *min_distance = min_dist;
    *max_distance = max_dist;
}

// Encontra os valores da distância de manhattan para todos os pontos atribuídos ao processo
void get_process_manhattan(const int* matrix_x, const int* matrix_y, const int* matrix_z, const int begin,
                           const int last, const int num_proc, int* local_min_manhattan, int* local_max_manhattan,
                           int* local_sum_min_manhattan, int* local_sum_max_manhattan, const int num_of_threads){
    int i;
    int local_min = INT_MAX;
    int local_max = 0;
    int sum_min = 0;
    int sum_max = 0;

    #pragma omp parallel for simd num_threads(num_of_threads) \
        reduction(min : local_min) reduction(max : local_max) reduction(+: sum_min, sum_max)
    for(i = begin; i < last - 1; i += num_proc){
        int min_dist, max_dist;
        get_manhattan(i, matrix_x, matrix_y, matrix_z, last, &min_dist, &max_dist);

        sum_min += min_dist;
        sum_max += max_dist;

        if(min_dist < local_min) local_min = min_dist;
        if(max_dist > local_max) local_max = max_dist;
    }

    *local_min_manhattan = local_min;
    *local_max_manhattan = local_max;
    *local_sum_min_manhattan = sum_min;
    *local_sum_max_manhattan = sum_max;
}

// Encontra os valores da distância euclidiana para todos os pontos atribuídos ao processo
void get_process_euclidean(const int* matrix_x, const int* matrix_y, const int* matrix_z, const int begin,
                           const int last, const int num_proc, double* local_min_euclidean, double* local_max_euclidean,
                           double* local_sum_min_euclidean, double* local_sum_max_euclidean, const int num_of_threads){
    int i;
    double local_min = DBL_MAX;
    double local_max = 0;
    double sum_min = 0;
    double sum_max = 0;

    #pragma omp parallel for simd num_threads(num_of_threads) \
        reduction(min : local_min) reduction(max : local_max) reduction(+: sum_min, sum_max)
    for(i = begin; i < last - 1; i += num_proc){
        double min_dist, max_dist;
        get_euclidean(i, matrix_x, matrix_y, matrix_z, last, &min_dist, &max_dist);

        sum_min += min_dist;
        sum_max += max_dist;

        if(min_dist < local_min) local_min = min_dist;
        if(max_dist > local_max) local_max = max_dist;
    }

    *local_min_euclidean = local_min;
    *local_max_euclidean = local_max;
    *local_sum_min_euclidean = sum_min;
    *local_sum_max_euclidean = sum_max;
}

int main(int argc, char **argv) {
    int my_rank, num_proc;
    int mat_size, rand_seed, num_of_threads, total_size, size_per_processor, memory_shift, i, provided;
    int *matrix_x, *matrix_y, *matrix_z;

    int local_min_manhattan, local_max_manhattan;
    double local_min_euclidean, local_max_euclidean;

    int local_sum_min_manhattan, local_sum_max_manhattan;
    double local_sum_min_euclidean, local_sum_max_euclidean;

    int min_manhattan, max_manhattan;
    double min_euclidean, max_euclidean;

    int sum_min_manhattan, sum_max_manhattan;
    double sum_min_euclidean, sum_max_euclidean;

    MPI_Status status;

    MPI_Op min_point_op, max_point_op;

    MPI_Init_thread(&argc, &argv, MPI_THREAD_SERIALIZED, &provided);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_proc);

    if (argc != 4){
        printf("Wrong number of arguments. Please try again with mpirun -np <number_of_processes> dist-par <matrix_size> <random_seed> <num_of_threads> \n");
        fflush(0);
        exit(0);
    }

    mat_size = atoi(argv[1]);
    rand_seed = atoi(argv[2]);
    num_of_threads = atoi(argv[3]);

    omp_set_num_threads(num_of_threads);
    omp_set_nested(1);

    // Calcula o número de pontos totais da matriz
    total_size = mat_size * mat_size;

    // Calcula quantos pontos serão alocados em cada processo
    size_per_processor = total_size / num_proc + (total_size % num_proc != 0);

    // Determina qual o deslocamento necessário para chegar ao primeiro ponto da matriz (Utilizado por causa do MPI_Win_allocate_men)
    memory_shift = -(size_per_processor * my_rank);

    long vmrss, vmsize;
    get_memory_usage_kb(&vmrss, &vmsize);
    printf("Begin: %2d: Current memory usage: VmRSS = %6ld KB, VmSize = %6ld KB\n", my_rank, vmrss, vmsize);

    // Aloca memória para as matrizes
    MPI_Win window_x;
    MPI_Win_allocate_shared(size_per_processor * sizeof(int), sizeof(int), MPI_INFO_NULL, MPI_COMM_WORLD, &matrix_x, &window_x);
    MPI_Win window_y;
    MPI_Win_allocate_shared(size_per_processor * sizeof(int), sizeof(int), MPI_INFO_NULL, MPI_COMM_WORLD, &matrix_y, &window_y);
    MPI_Win window_z;
    MPI_Win_allocate_shared(size_per_processor * sizeof(int), sizeof(int), MPI_INFO_NULL, MPI_COMM_WORLD, &matrix_z, &window_z);

    get_memory_usage_kb(&vmrss, &vmsize);
    printf("Middle: %2d: Current memory usage: VmRSS = %6ld KB, VmSize = %6ld KB\n", my_rank, vmrss, vmsize);

    if (my_rank == 0)
    {
        //Cria a matriz
        srand(rand_seed);
        for(int i = 0; i < total_size; ++i){
            matrix_x[i] = rand() % (MAX_POINT_DIFFERENCE) + MIN_POINT_VALUE;
        }
        for(int i = 0; i < total_size; ++i){
            matrix_y[i] = rand() % (MAX_POINT_DIFFERENCE) + MIN_POINT_VALUE;
        }
        for(int i = 0; i < total_size; ++i){
            matrix_z[i] = rand() % (MAX_POINT_DIFFERENCE) + MIN_POINT_VALUE;
        }

        min_manhattan = INT_MAX;
        max_manhattan = 0;
        min_euclidean = DBL_MAX;
        max_euclidean = 0;

        sum_min_manhattan = 0;
        sum_max_manhattan = 0;
        sum_min_euclidean = 0;
        sum_max_euclidean = 0;
    }

    MPI_Barrier(MPI_COMM_WORLD);

    get_memory_usage_kb(&vmrss, &vmsize);
    printf("End: %2d: Current memory usage: VmRSS = %6ld KB, VmSize = %6ld KB\n", my_rank, vmrss, vmsize);

    get_process_manhattan(matrix_x, matrix_y, matrix_z, my_rank + memory_shift, total_size + memory_shift,
                          num_proc, &local_min_manhattan, &local_max_manhattan,
                          &local_sum_min_manhattan, &local_sum_max_manhattan, num_of_threads);

    get_process_euclidean(matrix_x, matrix_y, matrix_z, my_rank + memory_shift, total_size + memory_shift,
                          num_proc, &local_min_euclidean, &local_max_euclidean,
                          &local_sum_min_euclidean, &local_sum_max_euclidean, num_of_threads);

    // Junta os valores encontrados por cada processo
    MPI_Reduce(&local_min_manhattan, &min_manhattan, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);
    MPI_Reduce(&local_max_manhattan, &max_manhattan, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
    MPI_Reduce(&local_min_euclidean, &min_euclidean, 1, MPI_DOUBLE, MPI_MIN, 0, MPI_COMM_WORLD);
    MPI_Reduce(&local_max_euclidean, &max_euclidean, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

    MPI_Reduce(&local_sum_min_manhattan, &sum_min_manhattan, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&local_sum_max_manhattan, &sum_max_manhattan, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&local_sum_min_euclidean, &sum_min_euclidean, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&local_sum_max_euclidean, &sum_max_euclidean, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    get_memory_usage_kb(&vmrss, &vmsize);
    printf("last: %2d: Current memory usage: VmRSS = %6ld KB, VmSize = %6ld KB\n", my_rank, vmrss, vmsize);

    // Libera a memória alocada para as matrizes
    MPI_Win_free(&window_x);
    MPI_Win_free(&window_y);
    MPI_Win_free(&window_z);

    if(my_rank == 0){
        printf("Distância de Manhattan mínima: %d (soma min: %d) e máxima: %d (soma max: %d).\n", min_manhattan, sum_min_manhattan, max_manhattan, sum_max_manhattan);
        printf("Distância Euclidiana mínima: %.2lf (soma min: %.2lf) e máxima: %.2lf (soma max: %.2lf).\n", min_euclidean, sum_min_euclidean, max_euclidean, sum_max_euclidean);
    }

    MPI_Finalize();
    exit(0);
}