// to compile: gcc dist-omp.c -o dist-omp -lm -fopenmp -O3 -fopt-info-vec-optimized -ffast-math
// to run: ./dist-omp <matrix_size> <random_seed> <num_of_threads>

// time ./dist-omp 100 1000 4
//

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <float.h>
#include <limits.h>

#include <omp.h>

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

int main(int argc, char **argv){
    if (argc != 4){
        printf("Wrong number of arguments. Please try again with dist-omp <matrix_size> <random_seed> <num_of_threads> \n");
        fflush(0);
        exit(0);
    }


    const int mat_size = atoi(argv[1]);
    const int rand_seed = atoi(argv[2]);
    const int num_of_threads = atoi(argv[3]);

    const int total_size = mat_size * mat_size;

    int* matrix_x = (int*) calloc(total_size, sizeof(int));
    int* matrix_y = (int*) calloc(total_size, sizeof(int));
    int* matrix_z = (int*) calloc(total_size, sizeof(int));

    //Matrix creation
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

    int min_manhattan = INT_MAX;
    int max_manhattan = 0;
    double min_euclidean = DBL_MAX;
    double max_euclidean = 0;
    int sum_min_manhattan = 0;
    int sum_max_manhattan = 0;
    double sum_min_euclidean = 0;
    double sum_max_euclidean = 0;

    int i;
    #pragma omp parallel for simd \
        reduction(+: sum_min_manhattan, sum_max_manhattan, sum_min_euclidean, sum_max_euclidean) \
        reduction(min: min_manhattan, min_euclidean) \
        reduction(max: max_manhattan, max_euclidean) \
        num_threads(num_of_threads)
    for(i = 0; i < total_size-1; ++i){
        int local_min_manhattan = INT_MAX;
        int local_max_manhattan = 0;
        double local_min_euclidean = DBL_MAX;
        double local_max_euclidean = 0;

        for(int j = i+1; j < total_size; ++j){
            const int manhattan = manhattan_distance(matrix_x[i], matrix_y[i], matrix_z[i], matrix_x[j], matrix_y[j], matrix_z[j]);
            const double euclidean = euclidean_distance(matrix_x[i], matrix_y[i], matrix_z[i], matrix_x[j], matrix_y[j], matrix_z[j]);

            if(manhattan < local_min_manhattan) local_min_manhattan = manhattan;
            if(manhattan > local_max_manhattan) local_max_manhattan = manhattan;
            if(euclidean < local_min_euclidean) local_min_euclidean = euclidean;
            if(euclidean > local_max_euclidean) local_max_euclidean = euclidean;
        }

        sum_min_manhattan += local_min_manhattan;
        sum_max_manhattan += local_max_manhattan;
        sum_min_euclidean += local_min_euclidean;
        sum_max_euclidean += local_max_euclidean;

        if(local_min_manhattan < min_manhattan) min_manhattan = local_min_manhattan;
        if(local_max_manhattan > max_manhattan) max_manhattan = local_max_manhattan;
        if(local_min_euclidean < min_euclidean) min_euclidean = local_min_euclidean;
        if(local_max_euclidean > max_euclidean) max_euclidean = local_max_euclidean;
    }

    printf("Distância de Manhattan mínima: %d (soma min: %d) e máxima: %d (soma max: %d).\n", min_manhattan, sum_min_manhattan, max_manhattan, sum_max_manhattan);
    printf("Distância Euclidiana mínima: %.2lf (soma min: %.2lf) e máxima: %.2lf (soma max: %.2lf).\n", min_euclidean, sum_min_euclidean, max_euclidean, sum_max_euclidean);

    return 0;
}
