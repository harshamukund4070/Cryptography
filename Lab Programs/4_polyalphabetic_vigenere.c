#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char plaintext[1000];
    char key[100];
    char ciphertext[1000];
    int i, j = 0, shift;

    printf("Enter plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);

    printf("Enter key: ");
    scanf("%99s", key);

    for (i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha((unsigned char)plaintext[i])) {
            shift = toupper((unsigned char)key[j % strlen(key)]) - 'A';

            if (isupper((unsigned char)plaintext[i]))
                ciphertext[i] =
                    'A' + (plaintext[i] - 'A' + shift) % 26;
            else
                ciphertext[i] =
                    'a' + (plaintext[i] - 'a' + shift) % 26;

            j++;
        } else {
            ciphertext[i] = plaintext[i];
        }
    }

    ciphertext[i] = '\0';

    printf("Ciphertext: %s", ciphertext);

    return 0;
}
