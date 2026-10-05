#include <stdio.h>
#include <string.h>
#include <ctype.h>

void makeMatrix(char key[], char matrix[5][5]) {
    int used[26] = {0};
    int r = 0, c = 0, i;
    char ch;

    used['J' - 'A'] = 1;

    for (i = 0; key[i] != '\0'; i++) {
        ch = toupper((unsigned char)key[i]);

        if (ch < 'A' || ch > 'Z')
            continue;

        if (ch == 'J')
            ch = 'I';

        if (!used[ch - 'A']) {
            matrix[r][c++] = ch;
            used[ch - 'A'] = 1;

            if (c == 5) {
                c = 0;
                r++;
            }
        }
    }

    for (ch = 'A'; ch <= 'Z'; ch++) {
        if (!used[ch - 'A']) {
            matrix[r][c++] = ch;

            if (c == 5) {
                c = 0;
                r++;
            }
        }
    }
}

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

void decrypt(char cipher[], char matrix[5][5], char plain[]) {
    int i, r1, c1, r2, c2;
    int n = strlen(cipher);
    int k = 0;

    for (i = 0; i < n; i += 2) {
        findPos(matrix, cipher[i], &r1, &c1);
        findPos(matrix, cipher[i + 1], &r2, &c2);

        if (r1 == r2) {
            plain[k++] = matrix[r1][(c1 + 4) % 5];
            plain[k++] = matrix[r2][(c2 + 4) % 5];
        } else if (c1 == c2) {
            plain[k++] = matrix[(r1 + 4) % 5][c1];
            plain[k++] = matrix[(r2 + 4) % 5][c2];
        } else {
            plain[k++] = matrix[r1][c2];
            plain[k++] = matrix[r2][c1];
        }
    }

    plain[k] = '\0';
}

int main() {
    char key[100];
    char cipher[2000];
    char clean[2000];
    char plain[2000];
    char matrix[5][5];
    int i, j, k = 0;

    printf("Enter key: ");
    fgets(key, sizeof(key), stdin);

    printf("Enter Playfair ciphertext: ");
    fgets(cipher, sizeof(cipher), stdin);

    /* Remove spaces and convert to uppercase */
    for (i = 0; cipher[i] != '\0'; i++) {
        if (isalpha((unsigned char)cipher[i]))
            clean[k++] = toupper((unsigned char)cipher[i]);
    }
    clean[k] = '\0';

    makeMatrix(key, matrix);

    printf("\nPlayfair Matrix:\n");
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++)
            printf("%c ", matrix[i][j]);
        printf("\n");
    }

    decrypt(clean, matrix, plain);

    printf("\nDecrypted message: %s\n", plain);
    printf("\nFor the textbook message, translate the artificial TT pair as 'tt'\n");
    printf("and remove filler X characters where appropriate.\n");

    return 0;
}
