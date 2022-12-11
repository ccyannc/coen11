#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
	srand((int)time(NULL));
	int correct = 0;
	int counter;
	int answer, divisor, dividend, guess;
    
	for (counter = 0; counter < 10; counter++) {
		
		divisor = rand() % 12 + 1;
		answer = rand() % 13;
		dividend = divisor * answer;
		
		printf("%i / %i = ? \n", dividend, divisor);
		printf("Input Guess:\n");
		scanf("%i", &guess);

		if (guess == answer) {
			printf("%i is the correct answer. \n", guess);
			correct++;
		} else {
			printf("Incorrect. %i was the correct answer \n", answer);
		}
	}
	printf("Out of 10, you got %i correct.", correct);
}

