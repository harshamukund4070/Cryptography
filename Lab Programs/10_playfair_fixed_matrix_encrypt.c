#include <stdio.h>
#include <string.h>
#include <ctype.h>

void findPos(char matrix[5][5], char ch, int *r, int *c) {
    int i, j;

    if (ch == 'J')
        ch = 'I';

    for (i = 0; i < 5; i++)
        for (j = 0; j < 5; j++)
            if (matrix[i][j] == ch) {
                *r = i;
                *c = j;
                return;
            }
}

void prepareText(char input[], char output[]) {
    int i, k = 0;
    char ch;

    for (i = 0; input[i] != '\0'; i++) {
        ch = toupper((unsigned char)input[i]);

        if (ch >= 'A' && ch <= 'Z') {
            if (ch == 'J')
                ch = 'I';

            if (k > 0 && output[k - 1] == ch)
                output[k++] = 'X';

            output[k++] = ch;
        }
    }

    if (k % 2 != 0)
        output[k++] = 'X';

    output[k] = '\0';
}

void encrypt(char text[], char matrix[5][5], char cipher[]) {
    int i, r1, c1, r2, c2;
    int n = strlen(text);

    for (i = 0; i < n; i += 2) {
        findPos(matrix, text[i], &r1, &c1);
        findPos(matrix, text[i + 1], &r2, &c2);

        if (r1 == r2) {
            cipher[i] = matrix[r1][(c1 + 1) % 5];
            cipher[i + 1] = matrix[r2][(c2 + 1) % 5];
        } else if (c1 == c2) {
            cipher[i] = matrix[(r1 + 1) % 5][c1];
            cipher[i + 1] = matrix[(r2 + 1) % 5][c2];
        } else {
            cipher[i] = matrix[r1][c2];
            cipher[i + 1] = matrix[r2][c1];
        }
    }

    cipher[n] = '\0';
}

int main() {
    char matrix[5][5] = {
        {'M','F','H','I','K'},
        {'U','N','O','P','Q'},
        {'Z','V','W','X','Y'},
        {'E','L','A','R','G'},
        {'D','S','T','B','C'}
    };

    char plaintext[1000];
    char prepared[2000];
    char ciphertext[2000];
    int i, j;

    printf("Playfair Matrix:\n");
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++)
            printf("%c ", matrix[i][j]);
        printf("\n");
    }

    printf("\nEnter plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);

    prepareText(plaintext, prepared);
    encrypt(prepared, matrix, ciphertext);

    printf("\nPrepared plaintext: %s\n", prepared);
    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}
