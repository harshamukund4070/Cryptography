#include <stdio.h>
#include <string.h>
#include <ctype.h>

void createMatrix(char key[], char matrix[5][5]) {
    int used[26] = {0};
    int row = 0, col = 0, i;
    char ch;

    used['J' - 'A'] = 1;   /* I and J are treated as the same */

    for (i = 0; key[i] != '\0'; i++) {
        ch = toupper((unsigned char)key[i]);

        if (ch < 'A' || ch > 'Z')
            continue;

        if (ch == 'J')
            ch = 'I';

        if (!used[ch - 'A']) {
            matrix[row][col++] = ch;
            used[ch - 'A'] = 1;

            if (col == 5) {
                col = 0;
                row++;
            }
        }
    }

    for (ch = 'A'; ch <= 'Z'; ch++) {
        if (!used[ch - 'A']) {
            matrix[row][col++] = ch;

            if (col == 5) {
                col = 0;
                row++;
            }
        }
    }
}

void findPosition(char matrix[5][5], char ch, int *row, int *col) {
    int i, j;

    if (ch == 'J')
        ch = 'I';

    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            if (matrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

void prepareText(char input[], char prepared[]) {
    int i, j = 0;
    char ch;

    for (i = 0; input[i] != '\0'; i++) {
        ch = toupper((unsigned char)input[i]);

        if (ch >= 'A' && ch <= 'Z') {
            if (ch == 'J')
                ch = 'I';

            if (j > 0 && prepared[j - 1] == ch) {
                prepared[j++] = 'X';
            }

            prepared[j++] = ch;
        }
    }

    if (j % 2 != 0)
        prepared[j++] = 'X';

    prepared[j] = '\0';
}

void encryptPlayfair(char prepared[], char matrix[5][5], char cipher[]) {
    int i, r1, c1, r2, c2;
    int n = strlen(prepared);

    for (i = 0; i < n; i += 2) {
        findPosition(matrix, prepared[i], &r1, &c1);
        findPosition(matrix, prepared[i + 1], &r2, &c2);

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
    char key[100];
    char plaintext[1000];
    char prepared[2000];
    char cipher[2000];
    char matrix[5][5];
    int i, j;

    printf("Enter keyword: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0';

    printf("Enter plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);

    createMatrix(key, matrix);

    printf("\nPlayfair Matrix:\n");
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++)
            printf("%c ", matrix[i][j]);
        printf("\n");
    }

    prepareText(plaintext, prepared);
    encryptPlayfair(prepared, matrix, cipher);

    printf("\nPrepared plaintext: %s\n", prepared);
    printf("Ciphertext: %s\n", cipher);

    return 0;
}
