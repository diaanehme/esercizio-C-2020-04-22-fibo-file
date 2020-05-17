// Diaa Nehme  IN0500345  esercizio20200422

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <errno.h>

// Fibonacci Function
unsigned long fibonacci(unsigned int n){
	unsigned long result;
	if(n < 0)
		return 0;
	else if(n == 0){
		result = 0;
		return result;
	}
	else if(n == 1){
		result = 1;
		return result;
	}
	else {
		result = fibonacci(n-1) + fibonacci(n-2);
		return result;
		}
	return result;
	}

// Fill Array Function
unsigned long * fibonacci_array(unsigned int n){

	unsigned long * array;
	array = calloc(n + 1, sizeof(unsigned long));

	if (array == NULL)
	{
		perror("Error with calloc!");
		exit(EXIT_FAILURE);
	}

	for(int i = 0; i < n + 1; i++){
		array[i] = fibonacci(i);
	}
	return array;
}

// itoa_printf Function
char * itoa_printf(unsigned long number) {
	char * result;
	result = calloc(12, sizeof(char));

	if (result == NULL)
	{
		perror("Error with calloc!");
		exit(EXIT_FAILURE);
	}

	snprintf(
			result,
			12,
			"%lu\n",
			number);

	return result;
}

int main(int argc, char *argv[]) {

	char * text_to_write;
	char * file_name = "fibonacci.txt";
	int text_to_write_len;

	printf("I write in the file %s\n", file_name);

	int fd = open(file_name,O_CREAT | O_TRUNC | O_WRONLY,S_IRUSR | S_IWUSR);
	if (fd == -1) {

		perror("Eroor with open()!");

		exit(EXIT_FAILURE);
	}


	unsigned long * fibonacci_result;
	unsigned int length = 39;

	fibonacci_result = calloc(length + 1, sizeof(unsigned long));

	if (fibonacci_result == NULL) {
		return NULL;
	}

	fibonacci_result = fibonacci_array(length);

	for (int i = 0; i <= length; i++) {

		text_to_write = itoa_printf(fibonacci_result[i]);
		text_to_write_len = strlen(text_to_write) + 1;

		int result = write(fd, text_to_write, text_to_write_len);

		if (result == -1) {
					perror("Error with write()!");
					exit(EXIT_FAILURE);
				}

	}

	free(text_to_write);

	if (close(fd) == -1) {
		perror("Error with close()!");
		exit(EXIT_FAILURE);
	}

	printf("bye!\n");

	return 0;
}
