#include <stdio.h>
#include <stdlib.h>


int is_natural_string(const char *str) {
    if (str[0] == '\0' || str[0] == '0' || str[0] == '-') {
	return 0;
    }
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] < '0' || str[i] > '9') {
            return 0;
        }
    }
    return 1;
}

int is_integer_string(const char *str) {
    int start = 0;
    if (str[0] == '-' || str[0] == '+') {
    	start += 1;
    }

    if (str[start] == '\0') {
	return 0;
    }

    for (int i = start; str[i] != '\0'; i++) {
        if (str[i] < '0' || str[i] > '9') {
            return 0;
        }
    }
    return 1;
}

int is_float_string(const char *str) {
    int start = 0;
    if (str[0] == '-' || str[0] == '+') {
    	start += 1;
    }
    
    if (str[start] == '\0') {
	return 0;
    }
    
    int dot_count = 0;
    int digit_count = 0;
    
    for (int i = start; str[i] != '\0'; i++) {
        if (str[i] == '.') {
            dot_count++;
            if (dot_count > 1) {
                return 0;
            }
        } 
        else if (str[i] >= '0' && str[i] <= '9') {
            digit_count++;
        } 
        else {
            return 0;
        }
    }

    if (digit_count == 0) {
        return 0;
    }

    return 1;
}


int main() {
    char *N_str = NULL;
    char *M_str = NULL;
    int M, N;

    while (1) {
        printf("Введите N: ");
        if (scanf("%ms", &N_str) != 1) {
            printf("Ошибка чтения.\n");
            free(N_str);
	    continue;
        }
        if (is_natural_string(N_str)) {
    	    N = atoi(N_str);
	    free(N_str);
	    break;
        } else {
	    free(N_str); 
	    printf("Число должно быть натуральным!\n");
        }
    }

    while (1) {
        printf("Введите M: ");
        if (scanf("%ms", &M_str) != 1) {
            printf("Ошибка чтения.\n");
            free(M_str); 
            continue;
        }
        if (is_natural_string(M_str)) {
            M = atoi(M_str);
	    free(M_str);
            break;
        } else {
	    printf("Чичло должно быть натуральным!\n");
	    free(M_str); 
	}
    }
    
    float *Matrix = malloc(M * N * sizeof(*Matrix));
    
    for (int i = 0; i < N; i++) {
    	 for (int j = 0; j < M; j++) {
   	     char *element = NULL;
   	     float value;
   	     
   	     while (1) {
        	 printf("Введите элемент [%i][%i]: ", i, j);
        	 if (scanf("%ms", &element) != 1) {
            	     printf("Ошибка чтения.\n");
            	     free(element);
	    	     continue;
        	 }
        	 if (is_float_string(element)) {
    	    	     value = atof(element);
	    	     free(element);
	    	     break;
        	 } else {
	    	     free(element); 
	    	     printf("Некорректный ввод!\n");
        	 }
	    }
   	    Matrix[i*M + j] = value;
   	}
    }
   
    for (int i = 0; i < N; i++) {
    	 for (int j = 0; j < M; j++) {
   	     printf("| %f |", Matrix[i*M + j]);
     	 }
     	 printf("\n");
    }

double *b = malloc(N * sizeof(double));
if (b == NULL) {
    printf("Ошибка\n");
    free(Matrix);
    return 1;
}
for ( int i = 0; i < N; i++) {
 float sum = 0;
 
    for (int j = 0; j < M; j++) {
        sum += Matrix[i * M + j];
    }
    b[i] = sum / M;
}
printf("Среднее арифметические строк:\n ");
for (int i = 0; i < N; i++) {
    printf("b[%d] = %f\n", i, b[i]);
}
int minRow = 0;
float min = Matrix[2];

for (int i = 1; i < N; i++) {
    if (Matrix[i * M + 2] < min) {
        min = Matrix[i * M + 2];
	minRow = i;
    }
}
printf("Минимальный элемент третьего столбца: %f\n", min);

float temp = Matrix[minRow * M + 2];

Matrix[minRow * M + 2] = Matrix[1 * M + 2];

Matrix[1 * M + 2] = temp;

printf("Матрица после обмена:\n");

for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
        printf("| %f |", Matrix[i * M + j]);
    }
    printf("\n");
}
free(b);
free(Matrix);
return 0;
}

