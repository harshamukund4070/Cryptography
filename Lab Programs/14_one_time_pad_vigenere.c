#include <stdio.h>
#include <string.h>
#include <ctype.h>

void cleanText(char input[], char output[]) {
    int i, k = 0;

    for (i = 0; input[i] != '\0'; i++) {
        if (isalpha((unsigned char)input[i]))
            output[k++] = tolower((unsigned char)input[i]);
    }

    output[k] = '\0';
}

void encrypt(char plain[], int key[], int n, char cipher[]) {
    int i;

    for (i = 0; plain[i] != '\0'; i++) {
        cipher[i] =
            'a' + ((plain[i] - 'a') + key[i % n]) % 26;
    }

    cipher[i] = '\0';
}

void decrypt(char cipher[], int key[], int n, char plain[]) {
    int i;

    for (i = 0; cipher[i] != '\0'; i++) {
        plain[i] =
            'a' + ((cipher[i] - 'a') - key[i % n] + 26) % 26;
    }

    plain[i] = '\0';
}

int main() {
    char input[1000];
    char plain[1000];
    char cipher[1000];
    char recovered[1000];

    int key[1000];
    int n, i;

    printf("One-Time Pad Vigenere Cipher\n");

    printf("Enter plaintext: ");
    fgets(input, sizeof(input), stdin);
    cleanText(input, plain);

    printf("Enter number of key values: ");
    scanf("%d", &n);

    printf("Enter key stream values (0-25):\n");
    for (i = 0; i < n; i++)
        scanf("%d", &key[i]);

    encrypt(plain, key, n, cipher);

    printf("\nPlaintext : %s\n", plain);
    printf("Ciphertext: %s\n", cipher);

    decrypt(cipher, key, n, recovered);
    printf("Decrypted : %s\n", recovered);

    printf("\nFor part (a), use:\n");
    printf("Plaintext = send more money\n");
    printf("Key       = 9 0 1 7 23 15 21 14 11 11 2 8 9\n");

    printf("\nFor part (b), using the same ciphertext and desired plaintext\n");
    printf("\"cash not needed\", calculate each key value as:\n");
    printf("K = (C - P) mod 26\n");

    return 0;
}
