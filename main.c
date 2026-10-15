#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int rows;
    int cols;
    double **data;
} Matrix;

/* Create a matrix dynamically */
Matrix *createMatrix(int rows, int cols) {
    if (rows <= 0 || cols <= 0)
        return NULL;

    Matrix *m = malloc(sizeof(Matrix));
    if (m == NULL)
        return NULL;

    m->rows = rows;
    m->cols = cols;
    m->data = calloc(rows, sizeof(double *));

    if (m->data == NULL) {
        free(m);
        return NULL;
    }

    for (int i = 0; i < rows; i++) {
        m->data[i] = calloc(cols, sizeof(double));

        if (m->data[i] == NULL) {
            for (int j = 0; j < i; j++)
                free(m->data[j]);

            free(m->data);
            free(m);
            return NULL;
        }
    }

    return m;
}

/* Free matrix memory */
void freeMatrix(Matrix *m) {
    if (m == NULL)
        return;

    for (int i = 0; i < m->rows; i++)
        free(m->data[i]);

    free(m->data);
    free(m);
}

/* Read matrix values */
void inputMatrix(Matrix *m) {
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            printf("Element [%d][%d]: ", i, j);

            while (scanf("%lf", &m->data[i][j]) != 1) {
                printf("Invalid number. Try again: ");

                int ch;
                while ((ch = getchar()) != '\n' && ch != EOF)
                    ;
            }
        }
    }
}

/* Display matrix */
void displayMatrix(const Matrix *m) {
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++)
            printf("%10.2f", m->data[i][j]);

        printf("\n");
    }
}

/* Create and read a matrix */
Matrix *readMatrix(void) {
    int rows, cols;

    printf("Number of rows: ");
    if (scanf("%d", &rows) != 1 || rows <= 0)
        return NULL;

    printf("Number of columns: ");
    if (scanf("%d", &cols) != 1 || cols <= 0)
        return NULL;

    Matrix *m = createMatrix(rows, cols);

    if (m == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    inputMatrix(m);
    return m;
}

/* Addition and subtraction */
Matrix *calculate(const Matrix *a, const Matrix *b, int operation) {
    if (a->rows != b->rows || a->cols != b->cols)
        return NULL;

    Matrix *r = createMatrix(a->rows, a->cols);
    if (r == NULL)
        return NULL;

    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < a->cols; j++) {
            if (operation == 1)
                r->data[i][j] = a->data[i][j] + b->data[i][j];
            else
                r->data[i][j] = a->data[i][j] - b->data[i][j];
        }
    }

    return r;
}

/* Matrix multiplication */
Matrix *multiply(const Matrix *a, const Matrix *b) {
    if (a->cols != b->rows)
        return NULL;

    Matrix *r = createMatrix(a->rows, b->cols);
    if (r == NULL)
        return NULL;

    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < b->cols; j++) {
            for (int k = 0; k < a->cols; k++) {
                r->data[i][j] +=
                    a->data[i][k] * b->data[k][j];
            }
        }
    }

    return r;
}

/* Determinant using Gaussian elimination */
double determinant(const Matrix *m) {
    if (m->rows != m->cols)
        return NAN;

    int n = m->rows;
    Matrix *temp = createMatrix(n, n);

    if (temp == NULL)
        return NAN;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            temp->data[i][j] = m->data[i][j];

    double det = 1.0;
    int sign = 1;

    for (int i = 0; i < n; i++) {
        int pivot = i;

        for (int j = i + 1; j < n; j++) {
            if (fabs(temp->data[j][i]) >
                fabs(temp->data[pivot][i]))
                pivot = j;
        }

        if (fabs(temp->data[pivot][i]) < 1e-12) {
            det = 0.0;
            freeMatrix(temp);
            return det;
        }

        if (pivot != i) {
            double *row = temp->data[i];
            temp->data[i] = temp->data[pivot];
            temp->data[pivot] = row;
            sign = -sign;
        }

        double value = temp->data[i][i];
        det *= value;

        for (int j = i + 1; j < n; j++) {
            double factor = temp->data[j][i] / value;

            for (int k = i + 1; k < n; k++)
                temp->data[j][k] -=
                    factor * temp->data[i][k];

            temp->data[j][i] = 0.0;
        }
    }

    det *= sign;
    freeMatrix(temp);
    return det;
}

/* Resize a matrix using realloc */
int resizeMatrix(Matrix *m, int newRows, int newCols) {
    if (m == NULL || newRows <= 0 || newCols <= 0)
        return 0;

    Matrix *temp = createMatrix(newRows, newCols);
    if (temp == NULL)
        return 0;

    int rows = (m->rows < newRows) ? m->rows : newRows;
    int cols = (m->cols < newCols) ? m->cols : newCols;

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            temp->data[i][j] = m->data[i][j];

    freeMatrix(m);

    /* Copy the new structure back into the original structure */
    m->rows = temp->rows;
    m->cols = temp->cols;
    m->data = temp->data;

    free(temp);
    return 1;
}

int main(void) {
    int choice;

    do {
        printf("\n================================\n");
        printf("   ADVANCED MATRIX CALCULATOR\n");
        printf("================================\n");
        printf("1. Addition\n");
        printf("2. Subtraction\n");
        printf("3. Multiplication\n");
        printf("4. Determinant\n");
        printf("5. Resize Matrix\n");
        printf("0. Exit\n");
        printf("Choose: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");

            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF)
                ;

            choice = -1;
            continue;
        }

        Matrix *a = NULL;
        Matrix *b = NULL;
        Matrix *result = NULL;

        switch (choice) {
            case 1:
            case 2:
            case 3:
                printf("\nEnter Matrix A:\n");
                a = readMatrix();

                if (a == NULL) {
                    printf("Invalid matrix A!\n");
                    break;
                }

                printf("\nEnter Matrix B:\n");
                b = readMatrix();

                if (b == NULL) {
                    printf("Invalid matrix B!\n");
                    freeMatrix(a);
                    break;
                }

                if (choice == 1 && choice == 2)
                    result = calculate(a, b, choice);
                else
                    result = multiply(a, b);

                if (result == NULL) {
                    printf("Operation impossible!\n");
                } else {
                    printf("\nResult:\n");
                    displayMatrix(result);
                }

                freeMatrix(a);
                freeMatrix(b);
                freeMatrix(result);
                break;

            case 4:
                printf("\nEnter a square matrix:\n");
                a = readMatrix();

                if (a == NULL) {
                    printf("Invalid matrix!\n");
                    break;
                }

                if (a->rows != a->cols) {
                    printf("Matrix must be square!\n");
                } else {
                    double det = determinant(a);

                    if (isnan(det))
                        printf("Could not calculate determinant.\n");
                    else
                        printf("Determinant = %.4f\n", det);
                }

                freeMatrix(a);
                break;

            case 5: {
                printf("\nEnter a matrix:\n");
                a = readMatrix();

                if (a == NULL) {
                    printf("Invalid matrix!\n");
                    break;
                }

                int rows, cols;

                printf("New number of rows: ");
                if (scanf("%d", &rows) != 1 || rows <= 0) {
                    printf("Invalid size!\n");
                    freeMatrix(a);
                    break;
                }

                printf("New number of columns: ");
                if (scanf("%d", &cols) != 1 || cols <= 0) {
                    printf("Invalid size!\n");
                    freeMatrix(a);
                    break;
                }

                if (resizeMatrix(a, rows, cols)) {
                    printf("\nResized matrix:\n");
                    displayMatrix(a);
                } else {
                    printf("Resize failed!\n");
                }

                freeMatrix(a);
                break;
            }

            case 0:
                printf("Goodbye!\n");
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while (choice != 0);

    return 0;
