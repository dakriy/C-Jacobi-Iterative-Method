#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef int bool;

#define true 1
#define false 0

float EPS = 0.01f;

const bool condition_met(const float * ans_row, const int col) {
	if (col == 0) return false;
	// Don't want to be dividing by zero!
	if (fabsf(ans_row[col - 1]) < 0.00001) return false;
	if (fabsf((ans_row[col] - ans_row[col - 1])/ ans_row[col - 1]) >= EPS) return false;
	return true;
}

const bool conditions_met(const float ** ans_matrix, const int current_col, const int rows)
{
	for (int i = 0; i < rows; i++)
		if (!condition_met(ans_matrix[i], current_col)) return false;
	return true;
}

int main() {
	
	int ROWS;
	int COLS;

	printf("ENTER YOUR EPSILON VALUE (The smaller the more accurate):\n");
	scanf("%f", &EPS);

	printf("NUMBER OF ROWS IN THE COEFFICIENT MATRIX.\n");
	scanf("%d", &ROWS);
	printf("NUMBER OF COLS IN THE COEFFICIENT MATRIX.\n");
	scanf("%d", &COLS);


	float ** matrix = (float **)malloc(sizeof(float *) * ROWS);
	float ** inverse = (float **)malloc(sizeof(float *) * ROWS);
	float ** m = (float **)malloc(sizeof(float *) * ROWS);
	float ** negate = (float **) malloc(sizeof(float *) * ROWS);
	float ** ans = (float **) malloc(sizeof(float *)*ROWS);
	float * ans_col = (float *) malloc(sizeof(float) * ROWS);
	for (int i = 0; i < ROWS; i++) {
		matrix[i] = (float *) malloc(sizeof(float) * COLS);
		inverse[i] = (float *) malloc(sizeof(float) * COLS);
		m[i] = (float *) malloc(sizeof(float) * COLS);
		negate[i] = (float *)malloc(sizeof(float) * COLS);
		ans[i] = (float *)malloc(sizeof(float) * 100);
	}
	
	printf("Enter the answer column:\n");
	for (int i = 0; i < ROWS; i++){
		scanf("%f", &ans_col[i]);
		for (int j = 0; j < 100; j++) {
			ans[i][j] = 0.;
		}
	}


	printf("INITIAL GUESSES:\n");
	for (int i = 0; i < ROWS; i++){
		printf("X%d = ", i + 1);
		scanf("%f", &ans[i][0]);
	}
	
	printf("COEFFICIENT MATRIX:\n");
	for (int i = 0; i < ROWS; i++)
		for (int j = 0; j < COLS; j++)
			scanf("%f", &matrix[i][j]);

	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			if (i == j) {
				inverse[i][j] = 1./matrix[i][j];
				negate[i][j] = 0.;
			}
			else {
				inverse[i][j] = 0.;
				negate[i][j] = -1. * matrix[i][j];
			}
		}
	}

	
	for (int c = 0; c < ROWS; c++) { // LOL I'M NOT USIN C++
		for (int d = 0; d < COLS; d++) {
			m[c][d] = 0;
			for (int k = 0; k < ROWS; k++) {
				m[c][d] += inverse[c][k] * negate[k][d];
			}
		}
	}


	printf("\nHere is the matrix D^-1:\n");
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			printf("%f\t", inverse[i][j]);
		}
		printf("\n");
	}

	printf("\nHere is the matrix M:\n");
	
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			printf("%f\t", m[i][j]);
		}
		printf("\n");
	}

	
	int current_col = 0;
	do {
		float * first = (float *) malloc(sizeof(float) * ROWS);
		float * second = (float *) malloc(sizeof(float) * ROWS);
		if (current_col + 1 >= 100) {
			return -1;
		}
		for (int c = 0; c < ROWS; c++) {
			first[c] = 0;
			second[c] = 0;
			for (int k = 0; k < ROWS; k++) {
				first[c] += m[c][k] * ans[k][current_col];
				second[c] += inverse[c][k] * ans_col[k];
			}
		}
		for (int i = 0; i < ROWS; i++) {
			ans[i][current_col + 1] = first[i] + second[i];
		}	
		current_col++;
		free(first);
		free(second);
	} while(!conditions_met(ans, current_col, ROWS));


	printf("\n DONE! Here is the answer matrix.\n");
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < current_col; j++) {
			printf("%f\t", ans[i][j]);
		}
		printf("\n");
	}

	printf("BYE\n");


	for (int i = 0; i < ROWS; i++) {
		free(matrix[i]);
		free(inverse[i]);
		free(m[i]);
		free(negate[i]);
		free(ans[i]);
	}
	free(ans_col);
	free(matrix);
	free(inverse);
	free(m);
	free(ans_col);
	free(ans);
}

