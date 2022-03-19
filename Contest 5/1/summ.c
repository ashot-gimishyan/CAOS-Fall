extern void summ(int N, const int *A, const int *B, int *R){
	for (int i = 0; i < N; ++i){
		R[i] = A[i] + B[i];
	}
}
