#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

#define ITERATIONS 1000000000

int main(int argc, char** argv) {
    int rank, size, i;
    double x, y, sum, pi, result;

    // Inicializar MPI
    MPI_Init(&argc, &argv);

    // Obtener el número de procesos y el rango del proceso actual
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Semilla aleatoria común para todos los procesos
    srand(123);

    // Número de iteraciones para cada proceso
    int n = ITERATIONS / size;

    sum = 0.0;
    for (i = 0; i < n; i++) {
        // Generar coordenadas aleatorias en el rango [0, 1]
        x = (double) rand() / RAND_MAX;
        y = (double) rand() / RAND_MAX;

        // Verificar si el punto está dentro del círculo unitario
        if (x * x + y * y <= 1.0) {
            sum += 1.0;
        }
    }

    // Reducción de la suma de todos los procesos
    MPI_Reduce(&sum, &result, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    // El proceso 0 calcula el valor final de PI y lo imprime
    if (rank == 0) {
        pi = 4.0 * result / ITERATIONS;
        printf("Valor aproximado de PI: %.15f\n", pi);
    }

    // Finalizar MPI
    MPI_Finalize();

    return 0;
}
