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

const char* getNewString() {
	// Open file
	FILE *fp;
	fp = fopen("phrases.txt", "r");
	if (fp == NULL) {
		return NULL;
	}
	char currentString[100];
	char fileContents[10000];
	int counter = 0;

	// Store file in fileContents
	while (fgets(currentString, 100, fp)) {
		strcat(fileContents, currentString);
		++counter;
	}

	int fileLength = counter;
	const char delimiter[2] = "\n";
	char *token;
	int target = rand() % fileLength;
	counter = 0;

	// Find phrases
	token = strtok(fileContents, delimiter);
	while (token) {
		if (counter == target) {
			return token;
		}
		token = strtok(NULL, delimiter);
		++counter;
	}
	return NULL;
}

void reset(int *counter, int *incorrect, char text[], char targetText[], char *strings[], int *size, int *clockStarted, int *stringsSize, int *finished) {
	white();
	int random = rand() % *stringsSize / sizeof(char *);
	int newSize = sizeof(strings[random]);
	strcpy(targetText, getNewString());
	strcpy(text, "");
	*counter = 0;
	*incorrect = -1;
	*size = strlen(targetText);
	*clockStarted = 0;
	*finished = 0;
	system("cls");
		printf("%s", targetText);	
		for (int i = 0; i < *size; ++i) {
			printf("\b");
		}
}

int main(int argc, char *argv[]) {
	char c[2] = {' ', '\0'};
	char targetText1[] = "The quick brown fox jumps over the lazy dog";
	char targetText2[] = "Your mother is a fat whore";
	char targetText3[] = "Your dad is a good boy";
	char *strings[] = {targetText1, targetText2, targetText3};
	int stringsSize = sizeof(strings);
	srand(time(NULL));
	
	int finished = 0;
	int incorrect = -1;
	char text[1000] = "";
	int counter = 0;
	int random = rand() % sizeof(strings) / sizeof(char *);	
	int newSize = sizeof(strings[random]);
	char targetText[1000];
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
			if (c[0] != 13 && finished == 1) {
				continue;
			}
			if (c[0] == 8) {
				backspace(text, &counter, targetText);			
			}
			else if (c[0] == 27) {	
				reset(&counter, &incorrect, text, targetText, strings, &size, &clockStarted, &stringsSize, &finished);
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
					if (c[0] == 13) {
						reset(&counter, &incorrect, text, targetText, strings, &size, &clockStarted, &stringsSize, &finished);
						continue;
					}
					finished = 1;
					end=clock();
					wpm	= size / ((end-start) / 1000.0) * 60;
					white();
					printf("\nWPM: %0.0f", wpm / 5.0);
				}
			}
        }
    }	
	return 0;
}
