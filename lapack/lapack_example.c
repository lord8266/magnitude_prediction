#include <stdio.h>
#include <stdlib.h>
#include "lapack_wrapper.h"

int main(void) {

	// First a little something on the different matrix storage methods.
	
	int i,j; // Every program needs an i and a j ;)
	
	// We shall use 3*3 matrices for this part
	int N = 3;
	
	// Define the matrix pointers.
	double **matrix, *fmatrix, *cmatrix;
	
	// Dynamically allocate memory for these matrices.
	// At this point we can do everything static of course, but this is a general example
	// Don't forget to free this memory when we are finished with these variables
	
	fmatrix=malloc(N*N*sizeof(double));  // Fortran matrix
	cmatrix=malloc(N*N*sizeof(double));  // C matrix, no difference with Fortran matrix so far
	matrix=malloc(N*sizeof(double*));  // "matrix" is actually a vector of vectors
	for (i=0; i<N; i++) matrix[i]=malloc(N*sizeof(double)); // We can now use the notation matrix[][]
	
	// Let's put some stuff in "matrix" and display it
	matrix[0][0] = 1; matrix[0][1] = 3; matrix[0][2] = 2;
	matrix[1][0] = 6; matrix[1][1] = 4; matrix[1][2] = 1;
	matrix[2][0] = 2; matrix[2][1] = 8; matrix[2][2] = 7;
	
	printf("matrix is: \n");
	for (i=0; i<N; i++) {
		for (j=0; j<N; j++) printf("%5.1f ", matrix[i][j]);
		printf("\n");
	}
	
	// Now create the C matrix version and the Fortran matrix version of this N*N matrix
	mat2cvec(N, N, matrix, cmatrix);
	mat2fvec(N, N, matrix, fmatrix);
	printf("\nIn C vector notation this becomes: (rowwise)\n");
	for (i=0; i<N*N; i++) printf("%5.1f ", cmatrix[i]);
	printf("\nIn Fortran vector notation this becomes: (columnwise)\n");
	for (i=0; i<N*N; i++) printf("%5.1f ", fmatrix[i]);
	
	// Of course we can invert this procedure using cvec2mat() and fvec2mat(), 
	// or turn one format into the other with cvec2fvec() or fvec2cvec()
	
	
	
	// Demonstration of all the different functions 
	printf("\n\nNow some Matrix algebra:\n\n");

	// Create some auxiliary variables, with proper memoryblocks attached.
	double **matrix2, *fmatrix2, *vec, *vec2;
	fmatrix2=malloc(N*N*sizeof(double));
	vec=malloc(N*sizeof(double));
	vec2=malloc(N*sizeof(double));
	matrix2=malloc(N*sizeof(double*)); for (i=0; i<N; i++) matrix2[i]=malloc(N*sizeof(double)); 
	
	// Almost all functions require the Fortran vector format for their matrices
	
	printf("The transpose of the matrix: \n");
	matrix_transpose(N, N, fmatrix, fmatrix2); // fmatrix2 contains the transpose of fmatrix
	fvec2mat(N, N, fmatrix2, matrix2); // Turn it into a proper matrix
	for (i=0; i<N; i++) {for (j=0; j<N; j++) printf("%5.1f ", matrix2[i][j]); printf("\n");} // And display
	
	printf("\nDefine a vector vec = (1, 2, 3)\n");
	vec[0]=1; vec[1]=2; vec[2]=3; 
	printf("\nAnd solve the linear equation matrix*x = vec for x:\n");
	linsolve(N, fmatrix, vec, vec2); // Solve the linear equation fmatrix*vec2 = vec for vec2.
	printf("x = "); for (i=0; i<N; i++) printf("%5.4f ", vec2[i]);
	printf("\n");
	
	// Matrix vector and matrix matrix multiplication is also possible
	
	printf("\n\n\n\nRedefine the matrix as a symmetric matrix: \n");
	matrix[0][0] = 3; matrix[0][1] = 2; matrix[0][2] = 1;
	matrix[1][0] = 2; matrix[1][1] = 2; matrix[1][2] = 1;
	matrix[2][0] = 1; matrix[2][1] = 1; matrix[2][2] = 1;
	for (i=0; i<N; i++) {for (j=0; j<N; j++) printf("%5.1f ", matrix[i][j]); printf("\n");}
	
	mat2fvec(N, N, matrix, fmatrix); // Again we need to work with the Fortran version of this matrix
	
	printf("\nIts eigenvalues are: \n");
	eigen_decomposition(N, fmatrix, fmatrix2, vec); // vec contains the eigenvalues, fmatrix2 the eigenvectors
	for (i=0; i<N; i++) printf("%5.4f ", vec[i]);
	
	printf("\n\nwith eigenvectors (columnwise): \n");
	fvec2mat(N, N, fmatrix2, matrix2);
	for (i=0; i<N; i++) {for (j=0; j<N; j++) printf("%5.4f ", matrix2[i][j]); printf("\n");}
	
	printf("\nSince the matrix is positive definite the square root exists.\n");
	printf("The unique semi-positive definite inverse is:\n");
	matrix_square_root(N, fmatrix, fmatrix2); // Use "simple" square root method
	fvec2mat(N, N, fmatrix2, matrix2);
	for (i=0; i<N; i++) {for (j=0; j<N; j++) printf("%5.4f ", matrix2[i][j]); printf("\n");}
	
	printf("\nA non positive definite square root is given by:\n");
	vec[0]=1; vec[1]=-1; vec[2]=1; 
	matrix_square_root_n(N, fmatrix, vec, fmatrix2);
	fvec2mat(N, N, fmatrix2, matrix2);
	for (i=0; i<N; i++) {for (j=0; j<N; j++) printf("%5.4f ", matrix2[i][j]); printf("\n");}
	
	// Cleaning up and exiting
	free(matrix);
	free(fmatrix);
	free(cmatrix);
	free(matrix2);
	free(fmatrix2);
	free(vec);
	free(vec2);
	return 0;
}
