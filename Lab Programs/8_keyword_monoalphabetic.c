#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char keyword[100];
    char sequence[27];
    char plaintext[1000];
    int used[26] = {0};
    int i, j = 0;
    char ch;

    printf("Enter keyword: ");
    scanf("%99s", keyword);

    /* Add unique keyword letters */
    for (i = 0; keyword[i] != '\0'; i++) {
        ch = toupper((unsigned char)keyword[i]);

        if (ch >= 'A' && ch <= 'Z' && !used[ch - 'A']) {
            sequence[j++] = ch;
            used[ch - 'A'] = 1;
        }
    }

    /* Add remaining alphabet letters */
    for (ch = 'A'; ch <= 'Z'; ch++) {
        if (!used[ch - 'A'])
            sequence[j++] = ch;
    }

    sequence[26] = '\0';

    printf("\nPlain : ABCDEFGHIJKLMNOPQRSTUVWXYZ\n");
    printf("Cipher: %s\n", sequence);

    getchar(); /* consume newline */
    printf("\nEnter plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);

    for (i = 0; plaintext[i] != '\0'; i++) {
        if (isupper((unsigned char)plaintext[i]))
            plaintext[i] = sequence[plaintext[i] - 'A'];
        else if (islower((unsigned char)plaintext[i]))
            plaintext[i] = tolower(sequence[plaintext[i] - 'a']);
    }

    printf("Ciphertext: %s", plaintext);

    return 0;
}
