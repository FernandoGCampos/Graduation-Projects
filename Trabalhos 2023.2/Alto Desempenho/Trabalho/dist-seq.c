// to compile: gcc dist-seq.c -o dist-seq -lm -O3 -fopt-info-vec-optimized -ffast-math
// to run: ./dist-seq <matrix_size> <random_seed>

// time ./dist-seq 100 1000
// time ./dist-seq 200 1
// 102612
// 10529222544
// 3976185249

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <float.h>
#include <limits.h>

#define MAX_POINT_VALUE 100
#define MIN_POINT_VALUE 0

#define MAX_POINT_DIFFERENCE MAX_POINT_VALUE - MIN_POINT_VALUE

int main(int argc, char **argv){
    if (argc != 3){
        printf("Wrong number of arguments. Please try again with dist-par <matrix_size> <random_seed>\n");
        fflush(0);
        exit(0);
    }

    const int mat_size = atoi(argv[1]);
    const int rand_seed = atoi(argv[2]);

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

    for(int i = 0; i < total_size-1; ++i){
        int local_min_manhattan = INT_MAX;
        int local_max_manhattan = 0;
        double local_min_euclidean = DBL_MAX;
        double local_max_euclidean = 0;

        for(int j = i+1; j < total_size; ++j){
            const int dist_x = matrix_x[i] - matrix_x[j];
            const int dist_y = matrix_y[i] - matrix_y[j];
            const int dist_z = matrix_z[i] - matrix_z[j];

            const int manhattan = abs(dist_x) + abs(dist_y) + abs(dist_z);
            const double euclidean = sqrt(dist_x * dist_x + dist_y * dist_y + dist_z * dist_z);

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
