#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct frac{
	int num;
	int den;
};

struct frac* create_frac(int num, int den){
	struct frac *result = malloc(sizeof(struct frac));
	result->num = num;
	result->den = den;
	return result;
}

int find_size(int number){
	if(number < 0)
		return find_size(-number) + 1;
	if(number == 0)
		return 1;
	int size = 1;
	for (int i = 10; 1; i = i * 10){
		if(number < i)
			return size;
		size++;
	}
	return -1;
}

char* convert_number_string(int number){
	int size = find_size(number);
	char *result = malloc(size + 1);
	int counter = 0;
	if(number < 0){
		result[counter++] = '-';
		size -= 1;
		number = -number;	
	}
	for(int i = (int) pow(10, size - 1); i != 0; i = i / 10){
		result[counter++] = '0' + (number / i);
	       	number = number % i;	
	}
	result[counter] = '\0';
	return result;
}

char* to_string(struct frac *f){
	int den_length = find_size(f->den);
	int num_length = find_size(f->num);
	char *result = malloc(den_length + num_length+ 2);
	int index = 0;
	char *num = convert_number_string(f->num);
	for(int i = 0; i < num_length; i++){
		result[index++] = num[i];
	}
	result[index++] = '/';
	char *den = convert_number_string(f->den);
	for(int i = 0; i < den_length; i++){
		result[index++] = den[i];
	}
	result[index] = '\0';
	free(num);
	free(den);
	return result;
}

int main(void){
	printf("%d bytes\n", (int) sizeof(struct frac));
	struct frac *frazione = create_frac(1234, -476);
	char *string = to_string(frazione);
	printf("%s\n", string);
	free(frazione);
	free(string);

	
}

