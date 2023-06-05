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

const char* getNewString(char *fileContents, char *tempContents, int fileLength) {
	const char delimiter[2] = "\n";
	int target = rand() % fileLength;
	int counter = 0;
	strcpy(tempContents, fileContents);
	// Find phrases
	char *token = strtok(tempContents, delimiter);	
	while (token) {
		if (counter == target) {
			return token;
		}
		token = strtok(NULL, delimiter);
		++counter;
	}	
}

void reset(char text[], char targetText[], int *counter, int *incorrect, int *size, int *finished, int *clockStarted, char *fileContents, char *tempContents, int fileLength) {
	white();
	char previousText[1000];
	strcpy(previousText, targetText);	
	while (strcmp(previousText, targetText) == 0) {
		strcpy(targetText, getNewString(fileContents, tempContents, fileLength));
	}
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
	printf ( "\033[1;H");
}

int main(int argc, char *argv[]) {
	SetConsoleOutputCP( 65001 );
	// Open file
	FILE *fp;
	fp = fopen("phrases.txt", "r");
	if (fp == NULL) {
		return -1;
	}
	char currentString[1000] = "";	
	char *fileContents = (char *) malloc(1580000);
	char *tempContents = (char *) malloc(1580000);
	int fileCounter = 0;
	while (fgets(currentString, 1000, fp)) {
		strcat(fileContents, currentString);
		++fileCounter;
	}
	int fileLength = fileCounter;
	fread(file_buffer, 1024*1024*4, 1, fp);
	printf("strlen %zu\n", strlen(file_buffer));
	char text[1000];
	char targetText[1000];
	int counter;
	int incorrect;
	int size;
	int finished;

	char c[2] = {' ', '\0'};
	float wpm;
	clock_t start, end;
	int clockStarted = 0;
	
	// Start this shit	
	srand(time(NULL)); 
	reset(text, targetText, &counter, &incorrect, &size, &finished, &clockStarted, fileContents, tempContents, fileLength);
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
				reset(text, targetText, &counter, &incorrect, &size, &finished, &clockStarted, fileContents, tempContents, fileLength);
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
						reset(text, targetText, &counter, &incorrect, &size, &finished, &clockStarted, fileContents, tempContents, fileLength);
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
