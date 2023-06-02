#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>

void white() {
	printf("\033[0;37m");
}

void red() {
	printf("\033[1;31m");
}

void green() {
  printf("\033[32m");
}

void backspace(char text[], int *counter, char targetText[]) {
	if (*counter > 0) {
		text[*counter-1] = '\0';
		*counter = *counter - 1;
		white();	
		printf("\b%c\b", targetText[*counter]);	
	}
}

int main(int argc, char *argv[]) {
	int incorrect = -1;
	char text[1000] = "";
	char c[2] = {' ', '\0'};
	int counter = 0;
	char targetText1[] = "The quick brown fox jumps over the lazy dog";
	char targetText2[] = "Your mother is a fat whore";
	char targetText3[] = "Your dad is a good boy";
	char *strings[] = {targetText1, targetText2, targetText3};

	srand(time(NULL));
	int random = rand() % sizeof(strings) / sizeof(char *);	
	int newSize = sizeof(strings[random]);
	char targetText[newSize];
	strcpy(targetText, strings[random]);
	int size = strlen(targetText);

	system("cls");
	printf("%s", targetText);	
	for (int i = 0; i < size; ++i) {
		printf("\b");
	}

	float wpm;
	clock_t start, end;
	int clockStarted = 0;
	
    while(1) {
        if (kbhit()) {
			if (!clockStarted) {
				start = clock(); 
				clockStarted = 1;
			}
			c[0] = getch();
			if (c[0] == 8) {
				backspace(text, &counter, targetText);			
			}
			else {
				if (counter < size) {	
					strcat(text, c);
					if (incorrect != -1) {	
						if (text[incorrect] == targetText[incorrect] || incorrect > counter) {
							incorrect = -1;
						} 
					}
					if (incorrect == -1 && text[counter] != targetText[counter]) {
						incorrect = counter;
					}
					if (incorrect != -1) {
						red();
						if (targetText[counter] == ' ') {
							printf("_");
						} else {
						printf("%c", targetText[counter]);	
						}
					} else {
						green();
						printf("%s", c);
					}
					counter = counter + 1;
				}
				if (counter >= size && incorrect == -1) {
					end=clock();
					wpm	= size / ((end-start) / 1000.0) * 60;
					white();
					printf("\nWPM: %0.0f", wpm / 5.0);
				}
			}
        }
    }	
}
