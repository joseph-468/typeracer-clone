#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <windows.h>

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
	char targetText[] = "The quick brown fox jumps over the lazy dog";

	system("cls");
	printf("%s", targetText);	
	for (int i = 0; i < sizeof(targetText); ++i) {
		printf("\b");
	}

    while(1) {
        if (kbhit()) {
			c[0] = getch();
			if (c[0] == 8) {
				backspace(text, &counter, targetText);			
			}
			else {
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
        }
    }	
}
