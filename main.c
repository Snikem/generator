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
int size_border;
int size_shifts;
int iteration = 1000;
int sizesABCDE;
char alphas_for_matrix[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'E'};

FILE *file;


void fill_matrices_from_file() {
    FILE *file_loc;
    char name[] = "Output_file_k.txt";
    if ((file_loc = fopen(name, "r")) == NULL) {
        printf("file not opened");
        getchar();
    }
    fscanf(file_loc, "%d", &sabc.second);
    fscanf(file_loc, "%d", &sabc.first);
    sizesABCDE = sabc.first;
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

void print_2_matrix(float **a, int fir, int sec) {
    for (int i = 0; i < fir; i++) {
        for (int j = 0; j < sec; j++) {
            printf("%f ", a[i][j]);
        }
        printf("\n");
    }
}

void print_1_matrix(int *a, int fir) {
    for (int i = 0; i < fir; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

void free_2_matrix(float ***a, int fir) {
    for (int i = 0; i < fir; i++) {
        free(a[i]);
    }
    free(a);
}

void open_file() {
    char name[] = "main.c";
    if ((file = fopen(name, "w")) == NULL) {
        printf("file not opened");
        getchar();
    }
}

void generate_begin() {
    fprintf(file, "#include <stdio.h>\n"
                  "#include <malloc.h>\n"
                  "#include <math.h>\n"
                  "float **abc;\n"
                  "float **u;\n"
                  "struct sizes_of_matrix //\n"
                  "{\n"
                  "    int first;\n"
                  "    int second;\n"
                  "};\n"
                  "int number_of_nested_loops;\n"
                  "int *borders;\n"
                  "int *shifts;\n"
                  "struct sizes_of_matrix su;\n"
                  "struct sizes_of_matrix sabc;\n"
                  "struct sizes_of_matrix sx;\n"
                  "int size_border;\n"
                  "int size_shifts;\n"
                  "int iteration = 1000;\n"
                  "int sizesABCDE = %d;"
                  "\n",sabc.second);
}

void generate_init_matrix()
{
    for(int i = 0; i < sabc.first;i++)
    {
        fprintf(file,"float **%c;\n",alphas_for_matrix[i]);
    }
    fprintf(file,"\n");
}
void fill_ABC()
{
    for(int i = 0; i < sabc.first;i++)
    {

        for(int j = 0;j < sabc.second;j++)
        {

        }
    }

}
void generate_fill_ABC()
{
    fprintf(file, "void fill_ABC()\n"
                  "{\n");
    fprintf(file,"int indexABC = 0;\n");
    fprintf(file,"sx.first = borders[1] - 1;\n");
    fprintf(file,"sx.second = borders[3] - 1;\n");
    for(int i = 0; i < sabc.first;i++)
    {
        fprintf(file,"indexABC = 0;\n");
        fprintf(file,  "%c = (float **) malloc(sx.first * sizeof(float * ));\n",alphas_for_matrix[i]);
        fprintf(file,"for(int i = 0; i < sx.first;i++){\n");
        fprintf(file,"%c[i] = (float *) malloc(sx.second * sizeof(float));\n",alphas_for_matrix[i]);
        fprintf(file,"for(int j = 0; j < sx.second;j++){\n");
        fprintf(file,"%c[i][j] = abc[%d][indexABC];\n"
                     "indexABC++;\n",alphas_for_matrix[i],i);
        fprintf(file,"}\n"
                     "}\n");

    }

    fprintf(file,"}\n");
}

void generate_functions() {
    fprintf(file, "void print_2_matrix(float **a, int fir, int sec) {\n"
                  "    for (int i = 0; i < fir; i++) {\n"
                  "        for (int j = 0; j < sec; j++) {\n"
                  "            printf(\"%%f \", a[i][j]);\n"
                  "        }\n"
                  "        printf(\"\\n\");\n"
                  "    }\n"
                  "printf(\"\\n\");\n"
                  "}\n"
                  "\n");
    fprintf(file, "void print_1_matrix(int *a, int fir) {\n"
                  "    for (int i = 0; i < fir; i++) {\n"
                  "        printf(\"%%d \", a[i]);\n"
                  "    }\n"
                  "    printf(\"\\n\");\n"
                  "}\n"
                  "\n"
                  "int compare_1(double a, double b, double eps)\n"
                  "{\n"
                  "    double diff = floor(a/eps + 0.5) - floor(b/eps + 0.5);\n"
                  "    return diff < 0 ? -1 : diff > 0 ? +1 : 0;\n"
                  "}\n"
                  "void new_print_2_matrix(float **a, int fir, int sec) {\n"
                  "    int count = 0;\n"
                  "    for (int i = 0; i < fir; i++) {\n"
                  "        for (int j = 0; j < sec; j++) {\n"
                  "            if(compare_1(a[i][j],0.0000f,0.0000001) != 0)\n"
                  "                //printf(\"%%f \",a[i][j]);\n"
                  "                count++;\n"
                  "        }\n"
                  "    }\n"
                  "    printf(\"ne nol: %%d\\n\",count);\n"
                  "}\n");
}

void generate_fill_var_in_program() {
    fprintf(file, "\n"
                  "void fill_matrices_from_file() {\n"
                  "    FILE *file_loc;\n"
                  "    char name[] = \"Output_file_k.txt\";\n"
                  "    if ((file_loc = fopen(name, \"r\")) == NULL) {\n"
                  "        printf(\"file not opened\");\n"
                  "        getchar();\n"
                  "    }\n"
                  "    fscanf(file_loc, \"%%d\", &sabc.second);\n"
                  "    fscanf(file_loc, \"%%d\", &sabc.first);\n"
                  "    fscanf(file_loc, \"%%d\", &number_of_nested_loops);\n"
                  "    size_border = 2 * number_of_nested_loops;\n"
                  "    borders = (int *) malloc(size_border * sizeof(int));\n"
                  "    for (int i = 0; i < number_of_nested_loops; i++) {\n"
                  "        fscanf(file_loc, \"%%d\", &borders[i * 2]);\n"
                  "        fscanf(file_loc, \"%%d\", &borders[i * 2 + 1]);\n"
                  "\n"
                  "    }\n"
                  "    size_shifts = number_of_nested_loops * sabc.first;\n"
                  "    shifts = (int *) malloc(size_shifts * sizeof(int));\n"
                  "    for (int i = 0; i < size_shifts; i++) {\n"
                  "        fscanf(file_loc, \"%%d\", &shifts[i]);\n"
                  "    }\n"
                  "\n"
                  "    abc = (float **) malloc(sabc.first * sizeof(float *));\n"
                  "    for (int i = 0; i < sabc.first; i++) {\n"
                  "        abc[i] = (float *) malloc(sabc.second * sizeof(float));\n"
                  "        for (int j = 0; j < sabc.second; j++) {\n"
                  "            fscanf(file_loc, \"%%f\", &abc[i][j]);\n"
                  "        }\n"
                  "\n"
                  "    }\n"
                  "    fscanf(file_loc, \"%%d\", &su.first);\n"
                  "    fscanf(file_loc, \"%%d\", &su.second);\n"
                  "    u = (float **) malloc(su.first * sizeof(float *));\n"
                  "    for (int i = 0; i < su.first; i++) {\n"
                  "        u[i] = (float *) malloc(su.second * sizeof(float));\n"
                  "        for (int j = 0; j < su.second; j++) {\n"
                  "            fscanf(file_loc, \"%%f\", &u[i][j]);\n"
                  "        }\n"
                  "\n"
                  "    }\n"
                  "    fclose(file_loc);\n"
                  "}\n"
                  "\n");
}

void generate_main() {
    fprintf(file, "int main() {\n"
                  "fill_matrices_from_file();\n"
                  "    fill_ABC();\n"
                  "    //  print_2_matrix(abc,sabc.first,sabc.second);\n"
                  "    new_print_2_matrix(u,su.first,su.second);\n"
                  "    //print_2_matrix(u,su.first,su.second);\n"
                  "    // print_1_matrix(borders,size_border);\n"
                  "    //  print_1_matrix(shifts,size_shifts);\n"
                  "// print_2_matrix(A,sx.first,sx.second);\n"
                  "    // print_2_matrix(B,sx.first,sx.second);\n"
                  "    // print_2_matrix(C,sx.first,sx.second);\n"
                  "    // print_2_matrix(D,sx.first,sx.second);\n"
                  "    convolution();\n"
                  "   //new_print_2_matrix(u,su.first,su.second);\n"
                  "   print_2_matrix(u,su.first,su.second);\n"
                  "    return 0;\n"
                  "}\n"
                  "\n");
}

void closeFile() {
    fclose(file);
}

void generate_convolution() {
    int shif;
    char alphas[] = {'i', 'j', 'k', 'o', 'a'};
    fprintf(file, "void convolution()\n"
                  "{\n");

    fprintf(file, "for(int it = 0; it < iteration;it++)\n"
                  "    {\n");
    for (int i = 0; i < number_of_nested_loops; i++) {
        fprintf(file, "for(int %c = %d; %c < %d;%c++)\n"
                      "    {\n", alphas[i], borders[2 * i], alphas[i], borders[2 * i + 1], alphas[i]);
    }
    fprintf(file, "u");
    for (int i = 0; i < number_of_nested_loops; i++) {
        fprintf(file,"[%c]",alphas[i]);

    }
    fprintf(file,"=");
    for(int i = 0;i < sabc.first;i++)
    {

        if(i!=0)
        {
            fprintf(file," + ");
        }
        fprintf(file,"%c[i - 1][j - 1] * ",alphas_for_matrix[i]);
        fprintf(file," u");
        for(int j = 0; j < number_of_nested_loops; j++)
        {
            shif = shifts[i * 2 + j];
            if(shif>=0)
            {
                fprintf(file,"[%c + %d]",alphas[j],shif);
            }
            else
            {
                fprintf(file,"[%c %d]",alphas[j],shif);
            }
        }
    }
    fprintf(file,";\n");














    fprintf(file,"\n");
    for (int i = 0; i < number_of_nested_loops; i++) {
        fprintf(file, "}\n");

    }
    fprintf(file, "}\n");
    fprintf(file, "}\n");

}

void convolution() {
    for (int it = 0; it < iteration; it++) {

    }

}

int main() {
    fill_matrices_from_file();
   // print_2_matrix(abc, sabc.first, sabc.second);
   // print_2_matrix(u, su.first, su.second);
    print_1_matrix(borders, size_border);
    print_1_matrix(shifts, size_shifts);
    open_file();
    generate_begin();
    generate_init_matrix();
    generate_functions();
    generate_fill_var_in_program();
    generate_fill_ABC();
    generate_convolution();
    generate_main();
    closeFile();
    return 0;
}
