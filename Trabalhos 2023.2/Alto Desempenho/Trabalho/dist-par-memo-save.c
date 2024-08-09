// to compile: mpicc dist-par.c -o dist-par -lm -fopenmp
// to run: mpirun -np <number_of_processes> dist-par <matrix_size_per_process> <random_seed> <num_of_threads>

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

void calculaMinMax(const int sending_proc, const int my_rank, const int num_proc, const int total_size, const int num_of_threads,
                   const int* matrix_x, const int* matrix_y, const int* matrix_z,
                   const int* matrix_x_aux, const int* matrix_y_aux, const int* matrix_z_aux,
                   int* matrix_min_manhattan, int* matrix_max_manhattan,
                   double* matrix_min_euclidean, double* matrix_max_euclidean,
                   int* min_manhattan, int* max_manhattan, int* sum_min_manhattan, int* sum_max_manhattan,
                   double* min_euclidean, double* max_euclidean, double* sum_min_euclidean, double* sum_max_euclidean){

    //Calcula a quantidade de pontos recebidos
    const int limit = total_size / num_proc + ((total_size % num_proc != 0) && (sending_proc < total_size % num_proc));

    //Calcula a quantidade dos pontos presentes na matriz do processo
    const int limit2 = total_size / num_proc + ((total_size % num_proc != 0) && (my_rank < total_size % num_proc));

    //Calcula as distâncias entre os pontos recebidos e os pontos de cada processo
    #pragma omp parallel for simd num_threads(num_of_threads) schedule(dynamic, 25)
    for(int i = 0; i < limit; ++i){
        int local_min_manhattan = INT_MAX, local_max_manhattan = 0;
        double local_min_euclidean = DBL_MAX, local_max_euclidean = 0;

        //Salva as coordenadas de ponto selecionado para comparação das distâncias
        int x = matrix_x_aux[i];
        int y = matrix_y_aux[i];
        int z = matrix_z_aux[i];

        //Caso o processo seja o mesmo que enviou os pontos, ele utiliza os pontos de sua própria matriz
        if(my_rank == sending_proc){
            x = matrix_x[i];
            y = matrix_y[i];
            z = matrix_z[i];
        }

        //Calcula as distâncias para o ponto 'i' de todos os pontos que foram gerados posteriormentes a este ponto
        for(int j = (my_rank <= sending_proc) ? i + 1 : i; j < limit2; ++j){
            //Calculas as diferenças entre as coordenadas de cada ponto
            const int dist_x = x - matrix_x[j];
            const int dist_y = y - matrix_y[j];
            const int dist_z = z - matrix_z[j];

            //Calcula as distâncias
            const int dist_manhattan = abs(dist_x) + abs(dist_y) + abs(dist_z);
            const double dist_euclidean = sqrt(dist_x * dist_x + dist_y * dist_y + dist_z * dist_z);

            //Salva as distâncias máximas e mínimas
            if(dist_manhattan < local_min_manhattan) local_min_manhattan = dist_manhattan;
            if(dist_manhattan > local_max_manhattan) local_max_manhattan = dist_manhattan;
            if(dist_euclidean < local_min_euclidean) local_min_euclidean = dist_euclidean;
            if(dist_euclidean > local_max_euclidean) local_max_euclidean = dist_euclidean;
        }

        //Salva as menores e maiores distâncias calculadas para cada ponto
        matrix_min_manhattan[i] = local_min_manhattan;
        matrix_max_manhattan[i] = local_max_manhattan;
        matrix_min_euclidean[i] = local_min_euclidean;
        matrix_max_euclidean[i] = local_max_euclidean;
    }

    int min_manhattan_aux;
    int max_manhattan_aux;
    double min_euclidean_aux;
    double max_euclidean_aux;

    //Para cada ponto
    for(int i = 0; i < limit; ++i){
        //Junta as menores e maiores distâncias calculadas para o ponto 'i' salvando os valores
        MPI_Reduce(matrix_min_manhattan + i, &min_manhattan_aux, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);
        MPI_Reduce(matrix_max_manhattan + i, &max_manhattan_aux, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
        MPI_Reduce(matrix_min_euclidean + i, &min_euclidean_aux, 1, MPI_DOUBLE, MPI_MIN, 0, MPI_COMM_WORLD);
        MPI_Reduce(matrix_max_euclidean + i, &max_euclidean_aux, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);


        //Atualiza os valores para a resposta
        if(my_rank == 0){
            if(min_manhattan_aux < *min_manhattan) *min_manhattan = min_manhattan_aux;
            if(min_euclidean_aux < *min_euclidean) *min_euclidean = min_euclidean_aux;
            if(max_manhattan_aux > *max_manhattan) *max_manhattan = max_manhattan_aux;
            if(max_euclidean_aux > *max_euclidean) *max_euclidean = max_euclidean_aux;

            if(min_manhattan_aux != INT_MAX){
                *sum_min_manhattan += min_manhattan_aux;
                *sum_min_euclidean += min_euclidean_aux;
            }

            *sum_max_manhattan += max_manhattan_aux;
            *sum_max_euclidean += max_euclidean_aux;
        }
    }
}


int main(int argc, char **argv) {
    MPI_Status status;

    int my_rank, num_proc, provided;

    MPI_Init_thread(&argc, &argv, MPI_THREAD_SERIALIZED, &provided);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_proc);

    if (argc != 4){
        printf("Wrong number of arguments. Please try again with mpirun -np <number_of_processes> dist-par <matrix_size> <random_seed> <num_of_threads> \n");
        fflush(0);
        exit(0);
    }

    const int matrix_size = atoi(argv[1]);
    const int rand_seed = atoi(argv[2]);
    const int num_of_threads = atoi(argv[3]);

    omp_set_num_threads(num_of_threads);

    // Calcula o número de pontos totais da matriz
    const int total_size = matrix_size * matrix_size;

    //Determine o range maximo da matriz propria
    const int up_limit = total_size / num_proc + ((total_size % num_proc != 0) && (my_rank < total_size % num_proc));

    const int matrix_size_per_process = total_size / num_proc + (total_size % num_proc != 0);

    // Aloca memória para as matrizes próprias
    int *matrix_x, *matrix_y, *matrix_z;
    matrix_x = (int*) malloc(matrix_size_per_process * sizeof(int));
    matrix_y = (int*) malloc(matrix_size_per_process * sizeof(int));
    matrix_z = (int*) malloc(matrix_size_per_process * sizeof(int));


    //Vetor auxiliar para cálculo de distancias
    int *matrix_x_aux, *matrix_y_aux, *matrix_z_aux;
    matrix_x_aux = (int*) malloc(matrix_size_per_process * sizeof(int));
    matrix_y_aux = (int*) malloc(matrix_size_per_process * sizeof(int));
    matrix_z_aux = (int*) malloc(matrix_size_per_process * sizeof(int));


    //Vetor de mínimos e máximos
    int *matrix_min_manhattan, *matrix_max_manhattan;
    double *matrix_min_euclidean, *matrix_max_euclidean;
    matrix_min_euclidean = (double*) malloc(matrix_size_per_process * sizeof(double));
    matrix_max_euclidean = (double*) malloc(matrix_size_per_process * sizeof(double));
    matrix_min_manhattan = (int*) malloc(matrix_size_per_process * sizeof(int));
    matrix_max_manhattan = (int*) malloc(matrix_size_per_process * sizeof(int));


    //Rotina de divisao dos dados entre os processos
    if (my_rank == 0){
        srand(rand_seed);
        //Gera pontos de x
        for(int i = 0, i_aux = 0; i < total_size; ++i){
            int aux = rand() % (MAX_POINT_DIFFERENCE) + MIN_POINT_VALUE;
            if(i % num_proc == 0){
                matrix_x[i_aux] = aux;
                i_aux++;
            } else{
                MPI_Send(&aux, 1, MPI_INT, i % num_proc, (i_aux-1), MPI_COMM_WORLD);
            }
        }
        //Gera pontos de y
        for(int i = 0, i_aux = 0; i < total_size; ++i){
            int aux = rand() % (MAX_POINT_DIFFERENCE) + MIN_POINT_VALUE;
            if(i % num_proc == 0){
                matrix_y[i_aux] = aux;
                i_aux++;
            } else{
                MPI_Send(&aux, 1, MPI_INT, i % num_proc, (i_aux-1)*2, MPI_COMM_WORLD);
            }
        }
        //Gera pontos de z
        for(int i = 0, i_aux = 0; i < total_size; ++i){
            int aux = rand() % (MAX_POINT_DIFFERENCE) + MIN_POINT_VALUE;
            if(i % num_proc == 0){
                matrix_z[i_aux] = aux;
                i_aux++;
            } else{
                MPI_Send(&aux, 1, MPI_INT, i % num_proc, (i_aux-1)*3, MPI_COMM_WORLD);
            }
        }
    }
    //Recebimento dos dados pelos processos diferentes do 0
    else{
        for(int i = 0; i < up_limit; i++)
            MPI_Recv(&matrix_x[i], 1, MPI_INT, 0, i, MPI_COMM_WORLD, &status);
        for(int i = 0; i < up_limit; i++)
            MPI_Recv(&matrix_y[i], 1, MPI_INT, 0, i*2, MPI_COMM_WORLD, &status);
        for(int i = 0; i < up_limit; i++)
            MPI_Recv(&matrix_z[i], 1, MPI_INT, 0, i*3, MPI_COMM_WORLD, &status);
    }

    //Inicializa as variáveis onde serão salvas as respostas
    int min_manhattan = INT_MAX;
    int max_manhattan = 0;
    double min_euclidean = DBL_MAX;
    double max_euclidean = 0;

    int sum_min_manhattan = 0;
    int sum_max_manhattan = 0;
    double sum_min_euclidean = 0;
    double sum_max_euclidean = 0;

    for(int i = 0; i < num_proc; i++){
        // Envia os pontos armazenados no processo 'i' para serem utilizados pelos demais processos para o cálculo das distâncias
        if(my_rank == i){
            for(int j = 0; j <  num_proc; j++){
                if(my_rank != j){
                    MPI_Send(matrix_x, matrix_size_per_process, MPI_INT, j, 0, MPI_COMM_WORLD);
                    MPI_Send(matrix_y, matrix_size_per_process, MPI_INT, j, 0, MPI_COMM_WORLD);
                    MPI_Send(matrix_z, matrix_size_per_process, MPI_INT, j, 0, MPI_COMM_WORLD);
                }
            }
        }
        //Recebimento dos pontos pelos processos diferentes de 'i'
        else{
            MPI_Recv(matrix_x_aux, matrix_size_per_process, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
            MPI_Recv(matrix_y_aux, matrix_size_per_process, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
            MPI_Recv(matrix_z_aux, matrix_size_per_process, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
        }

        calculaMinMax(i, my_rank, num_proc, total_size, num_of_threads,
                      matrix_x, matrix_y, matrix_z,
                      matrix_x_aux, matrix_y_aux, matrix_z_aux,
                      matrix_min_manhattan, matrix_max_manhattan,
                      matrix_min_euclidean, matrix_max_euclidean,
                      &min_manhattan, &max_manhattan, &sum_min_manhattan, &sum_max_manhattan,
                      &min_euclidean, &max_euclidean, &sum_min_euclidean, &sum_max_euclidean);
    }

    // Libera a memória alocada para as matrizes
    free(matrix_x);
    free(matrix_y);
    free(matrix_z);

    free(matrix_x_aux);
    free(matrix_y_aux);
    free(matrix_z_aux);

    free(matrix_min_euclidean);
    free(matrix_max_euclidean);
    free(matrix_min_manhattan);
    free(matrix_max_manhattan);

    //Imprime minimos/maximos finais
    if(my_rank == 0){
        printf("Distância de Manhattan mínima: %d (soma min: %d) e máxima: %d (soma max: %d).\n", min_manhattan, sum_min_manhattan, max_manhattan, sum_max_manhattan);
        printf("Distância Euclidiana mínima: %.2lf (soma min: %.2lf) e máxima: %.2lf (soma max: %.2lf).\n", min_euclidean, sum_min_euclidean, max_euclidean, sum_max_euclidean);
    }

    MPI_Finalize();
    exit(0);
}