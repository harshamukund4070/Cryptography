#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char plaintext[1000];
    char key[27];
    int i, j, valid = 1;

    printf("Enter plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);

    printf("Enter 26-letter substitution alphabet: ");
    scanf("%26s", key);

    if (strlen(key) != 26) {
        printf("Error: Key must contain exactly 26 letters.\n");
        return 1;
    }

    /* Check that every key letter is unique */
    for (i = 0; i < 26; i++) {
        if (!isalpha((unsigned char)key[i])) {
            valid = 0;
            break;
        }
        key[i] = toupper((unsigned char)key[i]);

        for (j = i + 1; j < 26; j++) {
            if (toupper((unsigned char)key[i]) ==
                toupper((unsigned char)key[j])) {
                valid = 0;
                break;
            }
        }
        if (!valid)
            break;
    }

    if (!valid) {
        printf("Error: Key must contain 26 unique alphabet letters.\n");
        return 1;
    }

    for (i = 0; plaintext[i] != '\0'; i++) {
        if (isupper((unsigned char)plaintext[i]))
            plaintext[i] = key[plaintext[i] - 'A'];
        else if (islower((unsigned char)plaintext[i]))
            plaintext[i] = tolower(key[plaintext[i] - 'a']);
    }

    printf("Ciphertext: %s", plaintext);

    return 0;
}
