#include <stdio.h>
#include <malloc.h>
float **abc;
float **u;
struct sizes_of_matrix //
{
    int first;
    int second;
};
int number_of_nested_loops;
int *borders;
int *shifts;
struct sizes_of_matrix su;
struct sizes_of_matrix sabc;
struct sizes_of_matrix sx;
int size_border;
int size_shifts;
int iteration = 1000;
int sizesABCDE = 12;
float **A;
float **B;
float **C;
float **D;

void print_2_matrix(float **a, int fir, int sec) {
    for (int i = 0; i < fir; i++) {
        for (int j = 0; j < sec; j++) {
            printf("%f ", a[i][j]);
        }
        printf("\n");
    }
printf("\n");
}

void print_1_matrix(int *a, int fir) {
    for (int i = 0; i < fir; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}


void fill_matrices_from_file() {
    FILE *file_loc;
    char name[] = "Output_file_1.txt";
    if ((file_loc = fopen(name, "r")) == NULL) {
        printf("file not opened");
        getchar();
    }
    fscanf(file_loc, "%d", &sabc.second);
    fscanf(file_loc, "%d", &sabc.first);
    fscanf(file_loc, "%d", &number_of_nested_loops);
    size_border = 2 * number_of_nested_loops;
    borders = (int *) malloc(size_border * sizeof(int));
    for (int i = 0; i < number_of_nested_loops; i++) {
        fscanf(file_loc, "%d", &borders[i * 2]);
        fscanf(file_loc, "%d", &borders[i * 2 + 1]);

    }
    size_shifts = number_of_nested_loops * sabc.first;
    shifts = (int *) malloc(size_shifts * sizeof(int));
    for (int i = 0; i < size_shifts; i++) {
        fscanf(file_loc, "%d", &shifts[i]);
    }

    abc = (float **) malloc(sabc.first * sizeof(float *));
    for (int i = 0; i < sabc.first; i++) {
        abc[i] = (float *) malloc(sabc.second * sizeof(float));
        for (int j = 0; j < sabc.second; j++) {
            fscanf(file_loc, "%f", &abc[i][j]);
        }

    }
    fscanf(file_loc, "%d", &su.first);
    fscanf(file_loc, "%d", &su.second);
    u = (float **) malloc(su.first * sizeof(float *));
    for (int i = 0; i < su.first; i++) {
        u[i] = (float *) malloc(su.second * sizeof(float));
        for (int j = 0; j < su.second; j++) {
            fscanf(file_loc, "%f", &u[i][j]);
        }

    }
    fclose(file_loc);
}

void fill_ABC()
{
int indexABC = 0;
sx.first = borders[1] - 1;
sx.second = borders[3] - 1;
indexABC = 0;
A = (float **) malloc(sx.first * sizeof(float * ));
for(int i = 0; i < sx.first;i++){
A[i] = (float *) malloc(sx.second * sizeof(float));
for(int j = 0; j < sx.second;j++){
A[i][j] = abc[0][indexABC];
indexABC++;
}
}
indexABC = 0;
B = (float **) malloc(sx.first * sizeof(float * ));
for(int i = 0; i < sx.first;i++){
B[i] = (float *) malloc(sx.second * sizeof(float));
for(int j = 0; j < sx.second;j++){
B[i][j] = abc[1][indexABC];
indexABC++;
}
}
indexABC = 0;
C = (float **) malloc(sx.first * sizeof(float * ));
for(int i = 0; i < sx.first;i++){
C[i] = (float *) malloc(sx.second * sizeof(float));
for(int j = 0; j < sx.second;j++){
C[i][j] = abc[2][indexABC];
indexABC++;
}
}
indexABC = 0;
D = (float **) malloc(sx.first * sizeof(float * ));
for(int i = 0; i < sx.first;i++){
D[i] = (float *) malloc(sx.second * sizeof(float));
for(int j = 0; j < sx.second;j++){
D[i][j] = abc[3][indexABC];
indexABC++;
}
}
}
void convolution()
{
for(int it = 0; it < iteration;it++)
    {
for(int i = 1; i < 4;i++)
    {
for(int j = 1; j < 5;j++)
    {
u[i][j]=A[i - 1][j - 1] *  u[i + 1][j + 0] + B[i - 1][j - 1] *  u[i -1][j + 0] + C[i - 1][j - 1] *  u[i + 0][j + 1] + D[i - 1][j - 1] *  u[i + 0][j -1];

}
}
}
}
int main() {
    fill_matrices_from_file();
  fill_ABC();
  //  print_2_matrix(abc,sabc.first,sabc.second);
    print_2_matrix(u,su.first,su.second);
   // print_1_matrix(borders,size_border);
  //  print_1_matrix(shifts,size_shifts);
 print_2_matrix(A,sx.first,sx.second);
   // print_2_matrix(B,sx.first,sx.second);
   // print_2_matrix(C,sx.first,sx.second);
   // print_2_matrix(D,sx.first,sx.second);
convolution();
    print_2_matrix(u,su.first,su.second);
    return 0;
}

