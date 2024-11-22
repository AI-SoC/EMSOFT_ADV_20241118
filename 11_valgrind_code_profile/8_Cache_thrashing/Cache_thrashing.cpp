#include <malloc.h>    
#include <stdio.h>
#include "timer.h"

Timer timer;
const long TEST_SIZE = 500;
const long TEST_COUNT = 4;

double MatrixMultiplication_ijk(int size, int** A, int** B, int** C)
{
	double time_total = 0.0;
	double sum;
	for (long test = 0; test < TEST_COUNT; ++test)
	{
		timer.Start();
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				sum = 0.0;
				for (int k = 0; k < size; k++)
				{
					sum += A[i][k] * B[k][j];
				}
				C[i][j] = sum;
			}
		}
		timer.Stop();
		time_total += timer.Elapsed();
	}

	return time_total;
}

double MatrixMultiplication_jik(int size, int** A, int** B, int** C)
{
	double time_total = 0.0;
	double sum;
	for (long test = 0; test < TEST_COUNT; ++test)
	{
		timer.Start();
		for (int j = 0; j < size; j++)
		{
			for (int i = 0; i < size; i++)
			{
				sum = 0.0;
				for (int k = 0; k < size; k++)
				{
					sum += A[i][k] * B[k][j];
				}
				C[i][j] = sum;
			}
		}
		timer.Stop();
		time_total += timer.Elapsed();
	}

	return time_total;
}

double MatrixMultiplication_jki(int size, int** A, int** B, int** C)
{
	double time_total = 0.0;
	double matrix;
	for (long test = 0; test < TEST_COUNT; ++test)
	{
		timer.Start();
		for (int j = 0; j < size; j++)
		{
			for (int k = 0; k < size; k++)
			{
				matrix = B[k][j];
				for (int i = 0; i < size; i++)
				{
					C[i][j] += A[i][k] * matrix;
				}
			}
		}
		timer.Stop();
		time_total += timer.Elapsed();
	}

	return time_total;
}

double MatrixMultiplication_kji(int size, int** A, int** B, int** C)
{
	double time_total = 0.0;
	double matrix;
	for (long test = 0; test < TEST_COUNT; ++test)
	{
		timer.Start();
		for (int k = 0; k < size; k++)
		{
			for (int j = 0; j < size; j++)
			{
				matrix = B[k][j];
				for (int i = 0; i < size; i++)
				{
					C[i][j] += A[i][k] * matrix;
				}
			}
		}
		timer.Stop();
		time_total += timer.Elapsed();
	}

	return time_total;
}


double MatrixMultiplication_kij(int size, int** A, int** B, int** C)
{
	double time_total = 0.0;
	double matrix;
	for (long test = 0; test < TEST_COUNT; ++test)
	{
		timer.Start();
		for (int k = 0; k < size; k++)
		{
			for (int i = 0; i < size; i++)
			{
				matrix = A[i][k];
				for (int j = 0; j < size; j++)
				{
					C[i][j] += matrix * B[k][j];
				}
			}
		}
		timer.Stop();
		time_total += timer.Elapsed();
	}

	return time_total;
}

double MatrixMultiplication_ikj(int size, int** A, int** B, int** C)
{
	double time_total = 0.0;
	double matrix;
	for (long test = 0; test < TEST_COUNT; ++test)
	{
		timer.Start();
		for (int i = 0; i < size; i++)
		{
			for (int k = 0; k < size; k++)
			{
				matrix = A[i][k];
				for (int j = 0; j < size; j++)
				{
					C[i][j] += matrix * B[k][j];
				}
			}
		}
		timer.Stop();
		time_total += timer.Elapsed();
	}

	return time_total;
}

int main(int argc, char* argv[])
{
	double time_total;
	double time_ijk;
	double time_jik;
	double time_jki;
	double time_kji;

	double time_kij;
	double time_ikj;

	int** A = new int* [TEST_SIZE];
	int** B = new int* [TEST_SIZE];
	int** C = new int* [TEST_SIZE];
	for (int i = 0; i < TEST_SIZE; i++)
	{
		A[i] = new int[TEST_SIZE];
		B[i] = new int[TEST_SIZE];
		C[i] = new int[TEST_SIZE];
	}

	time_total = MatrixMultiplication_ijk(TEST_SIZE, A, B, C);
	time_ijk = time_total / TEST_COUNT;

	time_total = MatrixMultiplication_jik(TEST_SIZE, A, B, C);
	time_jik = time_total / TEST_COUNT;

	time_total = MatrixMultiplication_jki(TEST_SIZE, A, B, C);
	time_jki = time_total / TEST_COUNT;

	time_total = MatrixMultiplication_kji(TEST_SIZE, A, B, C);
	time_kji = time_total / TEST_COUNT;

	time_total = MatrixMultiplication_kij(TEST_SIZE, A, B, C);
	time_kij = time_total / TEST_COUNT;

	time_total = MatrixMultiplication_ikj(TEST_SIZE, A, B, C);
	time_ikj = time_total / TEST_COUNT;

	printf("------------------------------------\n");
	printf("%-12s %10s %10s\n", "Version", "Times(ms)", "Speedup");
	printf("------------------------------------\n");
	printf("%-12s %10.4f %10.4f\n", "ijk",
		time_ijk, 1.0);
	printf("%-12s %10.4f %10.4f\n", "jik",
		time_jik, time_ijk / time_jik);
	printf("%-12s %10.4f %10.4f\n", "jki",
		time_jki, time_ijk / time_jki);
	printf("%-12s %10.4f %10.4f\n", "kji",
		time_kji, time_ijk / time_kji);
	printf("%-12s %10.4f %10.4f\n", "kij",
		time_kij, time_ijk / time_kij);
	printf("%-12s %10.4f %10.4f\n", "ikj",
		time_ikj, time_ijk / time_ikj);
	printf("------------------------------------\n");

	for (int i = 0; i < TEST_SIZE; i++)
	{
		delete[] A[i];
		delete[] B[i];
		delete[] C[i];
	}
	delete[] A;
	delete[] B;
	delete[] C;

	return 0;
}
