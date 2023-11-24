#include <stdio.h>
#include <stdlib.h>

// Структура для представлення матриці
struct Matrix {
    int rows;
    int cols;
    int** data;
};

// Функція для створення матриці з заданим розміром
struct Matrix* createMatrix(int rows, int cols) {
    struct Matrix* mat = (struct Matrix*)malloc(sizeof(struct Matrix));
    if (mat == NULL) {
        fprintf(stderr, "Memory allocation error for matrix.\n");
        exit(1);
    }

    mat->rows = rows;
    mat->cols = cols;

    mat->data = (int**)malloc(sizeof(int*) * rows);
    if (mat->data == NULL) {
        fprintf(stderr, "Memory allocation error for matrix data.\n");
        exit(1);
    }

    for (int i = 0; i < rows; i++) {
        mat->data[i] = (int*)malloc(sizeof(int) * cols);
        if (mat->data[i] == NULL) {
            fprintf(stderr, "Memory allocation error for matrix row data.\n");
            exit(1);
        }
    }

    return mat;
}

// Функція для видалення матриці та звільнення пам'яті
void deleteMatrix(struct Matrix* mat) {
    for (int i = 0; i < mat->rows; i++) {
        free(mat->data[i]);
    }
    free(mat->data);
    free(mat);
}

// Функція для зміни розмірів матриці зі збереженням вмісту
void resizeMatrix(struct Matrix* mat, int newRows, int newCols) {
    int** newData = (int**)malloc(sizeof(int*) * newRows);
    if (newData == NULL) {
        fprintf(stderr, "Memory allocation error for new matrix data.\n");
        exit(1);
    }

    for (int i = 0; i < newRows; i++) {
        newData[i] = (int*)malloc(sizeof(int) * newCols);
        if (newData[i] == NULL) {
            fprintf(stderr, "Memory allocation error for new matrix row data.\n");
            exit(1);
        }
    }

    int minRows = (mat->rows < newRows) ? mat->rows : newRows;
    int minCols = (mat->cols < newCols) ? mat->cols : newCols;

    for (int i = 0; i < minRows; i++) {
        for (int j = 0; j < minCols; j++) {
            newData[i][j] = mat->data[i][j];
        }
        free(mat->data[i]);
    }
    free(mat->data);

    mat->data = newData;
    mat->rows = newRows;
    mat->cols = newCols;
}

// Функція для отримання кількості рядків матриці
int numRows(struct Matrix* mat) {
    return mat->rows;
}

// Функція для отримання кількості стовбців матриці
int numCols(struct Matrix* mat) {
    return mat->cols;
}

// Функція для встановлення значення елемента матриці
void setElement(struct Matrix* mat, int row, int col, int value) {
    if (row >= 0 && row < mat->rows && col >= 0 && col < mat->cols) {
        mat->data[row][col] = value;
    } else {
        fprintf(stderr, "Invalid matrix indices.\n");
    }
}

// Функція для отримання значення елемента матриці
int getElement(struct Matrix* mat, int row, int col) {
    if (row >= 0 && row < mat->rows && col >= 0 && col < mat->cols) {
        return mat->data[row][col];
    } else {
        fprintf(stderr, "Invalid matrix indices.\n");
        return 0; // Повернення значення за замовчуванням у випадку помилки
    }
}

// Функція для виведення матриці на екран
void printMatrix(struct Matrix* mat) {
    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            printf("%d ", mat->data[i][j]);
        }
        printf("\n");
    }
}

// Функція для збереження матриці у файлі
void saveMatrixToFile(struct Matrix* mat, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Error opening file for writing.\n");
        return;
    }

    fprintf(file, "%d %d\n", mat->rows, mat->cols);

    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            fprintf(file, "%d ", mat->data[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

// Функція для читання матриці з файлу
struct Matrix* readMatrixFromFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file for reading.\n");
        return NULL;
    }

    int rows, cols;
    fscanf(file, "%d %d", &rows, &cols);

    struct Matrix* mat = createMatrix(rows, cols);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fscanf(file, "%d", &mat->data[i][j]);
        }
    }

    fclose(file);

    return mat;
}

// Функція для додавання двох матриць
struct Matrix* addMatrices(struct Matrix* mat1, struct Matrix* mat2) {
    if (mat1->rows != mat2->rows || mat1->cols != mat2->cols) {
        fprintf(stderr, "Matrix dimensions do not match for addition.\n");
        return NULL;
    }

    struct Matrix* result = createMatrix(mat1->rows, mat1->cols);

    for (int i = 0; i < mat1->rows; i++) {
        for (int j = 0; j < mat1->cols; j++) {
            result->data[i][j] = mat1->data[i][j] + mat2->data[i][j];
        }
    }

    return result;
}

// Функція для віднімання двох матриць
struct Matrix* subtractMatrices(struct Matrix* mat1, struct Matrix* mat2) {
    if (mat1->rows != mat2->rows || mat1->cols != mat2->cols) {
        fprintf(stderr, "Matrix dimensions do not match for subtraction.\n");
        return NULL;
    }

    struct Matrix* result = createMatrix(mat1->rows, mat1->cols);

    for (int i = 0; i < mat1->rows; i++) {
        for (int j = 0; j < mat1->cols; j++) {
            result->data[i][j] = mat1->data[i][j] - mat2->data[i][j];
        }
    }

    return result;
}

// Функція для множення матриці на число
struct Matrix* multiplyMatrixByScalar(struct Matrix* mat, int scalar) {
    struct Matrix* result = createMatrix(mat->rows, mat->cols);

    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            result->data[i][j] = mat->data[i][j] * scalar;
        }
    }

    return result;
}

// Функція для множення двох матриць
struct Matrix* multiplyMatrices(struct Matrix* mat1, struct Matrix* mat2) {
    if (mat1->cols != mat2->rows) {
        fprintf(stderr, "Matrix dimensions do not match for multiplication.\n");
        return NULL;
    }

    struct Matrix* result = createMatrix(mat1->rows, mat2->cols);

    for (int i = 0; i < mat1->rows; i++) {
        for (int j = 0; j < mat2->cols; j++) {
            result->data[i][j] = 0;
            for (int k = 0; k < mat1->cols; k++) {
                result->data[i][j] += mat1->data[i][k] * mat2->data[k][j];
            }
        }
    }

    return result;
}

int main() {
    struct Matrix* mat1 = createMatrix(3, 3);
    struct Matrix* mat2 = createMatrix(3, 3);

    // Заповнюємо матриці
    for (int i = 0; i < mat1->rows; i++) {
        for (int j = 0; j < mat1->cols; j++) {
            setElement(mat1, i, j, i * mat1->cols + j);
            setElement(mat2, i, j, i * mat2->cols + j);
        }
    }

    // Виведення матриць на екран
    printf("Matrix 1:\n");
    printMatrix(mat1);

    printf("\nMatrix 2:\n");
    printMatrix(mat2);

    // Додавання матриць
    struct Matrix* sum = addMatrices(mat1, mat2);
    if (sum != NULL) {
        printf("\nMatrix Sum:\n");
        printMatrix(sum);
        deleteMatrix(sum);
    }

    // Віднімання матриць
    struct Matrix* difference = subtractMatrices(mat1, mat2);
    if (difference != NULL) {
        printf("\nMatrix Difference:\n");
        printMatrix(difference);
        deleteMatrix(difference);
    }

    // Множення матриці на число
    struct Matrix* scaledMatrix = multiplyMatrixByScalar(mat1, 2);
    if (scaledMatrix != NULL) {
        printf("\nMatrix Scaled by 2:\n");
        printMatrix(scaledMatrix);
        deleteMatrix(scaledMatrix);
    }

    // Множення матриць
    struct Matrix* product = multiplyMatrices(mat1, mat2);
    if (product != NULL) {
        printf("\nMatrix Product:\n");
        printMatrix(product);
        deleteMatrix(product);
    }

    // Збереження матриці у файл і читання її з файлу
    saveMatrixToFile(mat1, "matrix.txt");
    struct Matrix* loadedMatrix = readMatrixFromFile("matrix.txt");
    if (loadedMatrix != NULL) {
        printf("\nLoaded Matrix:\n");
        printMatrix(loadedMatrix);
        deleteMatrix(loadedMatrix);
    }

    // Звільнення пам'яті
    deleteMatrix(mat1);
    deleteMatrix(mat2);

    return 0;
}
