/*
	Linear equation solver
	Ország Bence @ BME-VIK
	2017-03-13
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int    *stack, varNum;
double *matrix;

double det(int *source, int *target, int detSize, int depth) {
	if (detSize == 1) return *(matrix + depth + *source);
	int i, j, k;
	double detValue = 0, sign = 1.0;
	for (i = 0; i < detSize; ++i, sign *= -1.0) {
		for (j = k = 0; j < detSize; ++j) if (j - i) target[k++] = source[j];
		detValue += sign * *(matrix + depth + *(source + i)) * det(target, target + detSize - 1, detSize - 1, depth + varNum);
	}
	return detValue;
}

int main(int argc, char **argv) {
	int i, j;
	double *temp, *dets;
	varNum = argc - 1;
	for (j = 0, i = 0; j < varNum; j += 2 * ++i);
	
	if (j != varNum) {
		printf("\n[ERR] > Inappropriate number of parameters.\n");
		return -1;
	}
	varNum = i;
	stack 	= (int*)	malloc(sizeof(int)    * (varNum * (varNum + 1) / 2));
	matrix 	= (double*)	malloc(sizeof(double) * (argc - 1));
	temp 	= (double*)	malloc(sizeof(double) * varNum);
	dets 	= (double*)	malloc(sizeof(double) * (varNum + 1));
	for (i = 0; i < (argc - 1); ++i) matrix[i] = atof(argv[i+1]);
	for (i = 0; i < varNum; ++i) stack[i] = i;
	for (i = 0; i <= varNum; ++i)
	{
		dets[i] = det(stack, stack + varNum, varNum, 0);
		if (i > 0) memcpy(matrix + (i-1) * varNum, temp, varNum * sizeof(double));
		memcpy(temp, matrix + i * varNum, varNum * sizeof(double));
		memcpy(matrix + i * varNum, matrix + varNum * varNum, varNum * sizeof(double));
	}
	printf("\n");
	if (dets[0] == 0.0)
	{
		for (i = 1, j = 1; j == 1 && i <= varNum; j = dets[i] == 0.0, ++i);
		if (j) printf("[ERR] > There are infinite number of solutions.\n");
		else printf("[ERR] > There are no solutions.\n");
	}
	else for (i = 1; i <= varNum; ++i) printf("%2.d. = %16.6Lf\n", i, dets[i]/dets[0]);
	return 0;
}
