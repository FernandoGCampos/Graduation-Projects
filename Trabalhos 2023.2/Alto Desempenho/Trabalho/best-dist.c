// to compile: mpicc best-dist.c -o best-dist -lm -fopenmp -O3 -fopt-info-vec-optimized -ffast-math
// to run: mpirun -np <number_of_processes> best-dist <matrix_size> <random_seed> <num_of_threads>

// time mpirun -np 4 ./best-dist 100 1000 4
// time mpirun -np 4 ./best-dist 200 1 6

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <float.h>
#include <limits.h>

#include <mpi.h>
#include <omp.h>

#define MAX_POINT_VALUE 100
#define MIN_POINT_VALUE 0

#define MAX_POINT_DIFFERENCE MAX_POINT_VALUE - MIN_POINT_VALUE

int main(int argc, char **argv) {
    int my_rank, num_proc;
    int mat_size, rand_seed, num_of_threads, total_size, size_per_processor, memory_shift, i, j, provided;
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
        printf("Wrong number of arguments. Please try again with mpirun -np <number_of_processes> best-dist <matrix_size> <random_seed> <num_of_threads> \n");
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

    // Aloca memória para as matrizes
    MPI_Win window_x;
    MPI_Win_allocate_shared(size_per_processor * sizeof(int), sizeof(int), MPI_INFO_NULL, MPI_COMM_WORLD, &matrix_x, &window_x);
    MPI_Win window_y;
    MPI_Win_allocate_shared(size_per_processor * sizeof(int), sizeof(int), MPI_INFO_NULL, MPI_COMM_WORLD, &matrix_y, &window_y);
    MPI_Win window_z;
    MPI_Win_allocate_shared(size_per_processor * sizeof(int), sizeof(int), MPI_INFO_NULL, MPI_COMM_WORLD, &matrix_z, &window_z);

    if (my_rank == 0){
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

    local_min_manhattan = INT_MAX;
    local_max_manhattan = 0;
    local_min_euclidean = DBL_MAX;
    local_max_euclidean = 0;

    local_sum_min_manhattan = 0;
    local_sum_max_manhattan = 0;
    local_sum_min_euclidean = 0;
    local_sum_max_euclidean = 0;

    #pragma omp parallel for num_threads(num_of_threads) schedule(dynamic, 25) private(j) \
        reduction(min : local_min_manhattan) reduction(max : local_max_manhattan) reduction(+: local_sum_min_manhattan, local_sum_max_manhattan) \
        reduction(min : local_min_euclidean) reduction(max : local_max_euclidean) reduction(+: local_sum_min_euclidean, local_sum_max_euclidean)
    for(i = my_rank + memory_shift; i < total_size + memory_shift - 1; i += num_proc){
        int min_dist_manhattan = INT_MAX, max_dist_manhattan = 0;
        double min_dist_euclidean = DBL_MAX, max_dist_euclidean = 0;

        const int x = matrix_x[i];
        const int y = matrix_y[i];
        const int z = matrix_z[i];

        #pragma omp simd
        for(j = i+1; j < total_size + memory_shift; ++j){
            const int dist_x = x - matrix_x[j];
            const int dist_y = y - matrix_y[j];
            const int dist_z = z - matrix_z[j];

            const int dist_manhattan = abs(dist_x) + abs(dist_y) + abs(dist_z);
            const double dist_euclidean = sqrt(dist_x * dist_x + dist_y * dist_y + dist_z * dist_z);

            if(dist_manhattan < min_dist_manhattan) min_dist_manhattan = dist_manhattan;
            if(dist_manhattan > max_dist_manhattan) max_dist_manhattan = dist_manhattan;
            if(dist_euclidean < min_dist_euclidean) min_dist_euclidean = dist_euclidean;
            if(dist_euclidean > max_dist_euclidean) max_dist_euclidean = dist_euclidean;
        }

        local_sum_min_manhattan += min_dist_manhattan;
        local_sum_max_manhattan += max_dist_manhattan;
        local_sum_min_euclidean += min_dist_euclidean;
        local_sum_max_euclidean += max_dist_euclidean;

        if(min_dist_manhattan < local_min_manhattan) local_min_manhattan = min_dist_manhattan;
        if(max_dist_manhattan > local_max_manhattan) local_max_manhattan = max_dist_manhattan;
        if(min_dist_euclidean < local_min_euclidean) local_min_euclidean = min_dist_euclidean;
        if(max_dist_euclidean > local_max_euclidean) local_max_euclidean = max_dist_euclidean;
    }

    // Junta os valores encontrados por cada processo
    MPI_Reduce(&local_min_manhattan, &min_manhattan, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);
    MPI_Reduce(&local_max_manhattan, &max_manhattan, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
    MPI_Reduce(&local_min_euclidean, &min_euclidean, 1, MPI_DOUBLE, MPI_MIN, 0, MPI_COMM_WORLD);
    MPI_Reduce(&local_max_euclidean, &max_euclidean, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

    MPI_Reduce(&local_sum_min_manhattan, &sum_min_manhattan, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&local_sum_max_manhattan, &sum_max_manhattan, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&local_sum_min_euclidean, &sum_min_euclidean, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&local_sum_max_euclidean, &sum_max_euclidean, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

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