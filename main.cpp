//Напишите программу, в которой создается квадратная матрица (реализуется через
//двумерный массив). Матрицу необходимо заполнить числовыми значениями (способ
//заполнения выбрать самостоятельно), а затем выполнить транспонирование матрицы: матрица
//симметрично «отражается» относительно главной диагонали, в результате чего элемент
//матрицы а ij становится элементом а ji и наоборот.

#include <iostream>

using namespace std;

void print_matrix(int** matrix, int size) {
	for (int i = 0; i < size; ++i){
		for (int j = 0; j < size; ++j)
			cout << matrix[i][j] << ' ';
		cout << endl;
	}

	for (int i = 0; i < size; ++i)
		cout << "--";
	cout << endl;
}


void transpose_matrix(int** matrix, int size) {
	asm(".intel_syntax noprefix\n\t");
	asm(
		"	mov	rax, 0\n\t"  				// i = 0
		".OUTER_LOOP:\n\t"
		"	cmp	rax, rcx\n\t"
		"	jge	.EXIT\n\t"
		"	mov	rbx, rax\n\t"
		"	add	rbx, 1\n\t"  				// j = i + 1
		".INNER_LOOP:\n\t"
		"	cmp	rbx, rcx\n\t"
		"	jge	INCREMENT_OUTER_LOOP\n\t"
		"	mov r9, [rsi + rax * 8]\n\t"  	// *(matrix + i)
		"	mov r8d, [r9 + rbx * 4]\n\t"   	// t = *(*(matrix + i) + j)
		
		"	mov r10, [rsi + rbx * 8]\n\t" 	// *(matrix + j)
		"	mov r11d, [r10 + rax * 4]\n\t" 	// *(*(matrix + j) + i)
		"	mov r12, [rsi + rax * 8]\n\t" 	// *(matrix + i)
		"	mov [r12 + rbx * 4], r11d\n\t" 	// *(*(matrix + i) + j)
		
		"	mov r13, [rsi + rbx * 8]\n\t" 	// *(matrix + j)
		"	mov [r13 + rax * 4], r8d\n\t"  	// *(*(matrix + j) + i) = t
		"	add	rbx, 1\n\t"					// ++j
		"	jmp	.INNER_LOOP\n\t"
		"INCREMENT_OUTER_LOOP:\n\t"
		"	add	rax, 1\n\t" 				// ++i
		"	jmp	.OUTER_LOOP\n\t"
		".EXIT:\n\t"
		:
		: "S" (matrix), "c" (size)
		:
	);

	/*
	for (int i = 0; i < size; ++i){
		for (int j = i + 1; j < size; ++j){
			int t = *(*(matrix + i) + j);
			*(*(matrix + i) + j) = *(*(matrix + j) + i);
			*(*(matrix + j) + i) = t;
		}
	}
	*/
}



int main(int argc, char const *argv[])
{
	int size;

	cout << "Input matrix size: ";
	cin >> size;
	//size = 5; cout << endl;

	int **matrix = new int*[size];
	for (int i = 0; i < size; ++i){
		matrix[i] = new int[size];
		for (int j = 0; j < size; ++j)
			matrix[i][j] = i * size + j;
	}

	print_matrix(matrix, size);

	transpose_matrix(matrix, size);

	print_matrix(matrix, size);


	for (int i = 0; i < size; ++i)
		delete matrix[i];
	delete matrix;

	return 0;
}