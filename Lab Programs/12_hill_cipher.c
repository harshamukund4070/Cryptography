#include <stdio.h>
#include <string.h>
#include <ctype.h>

int mod26(int x) {
    x %= 26;
    if (x < 0)
        x += 26;
    return x;
}

int modInverse(int a) {
    int x;

    for (x = 1; x < 26; x++)
        if ((a * x) % 26 == 1)
            return x;

    return -1;
}

void cleanText(char input[], char output[]) {
    int i, k = 0;

    for (i = 0; input[i] != '\0'; i++) {
        if (isalpha((unsigned char)input[i]))
            output[k++] = toupper((unsigned char)input[i]);
    }

    if (k % 2 != 0)
        output[k++] = 'X';

    output[k] = '\0';
}

void encrypt(char plain[], char cipher[], int key[2][2]) {
    int i;
    int x, y;
    int c1, c2;

    for (i = 0; plain[i] != '\0'; i += 2) {
        x = plain[i] - 'A';
        y = plain[i + 1] - 'A';

        c1 = mod26(key[0][0] * x + key[0][1] * y);
        c2 = mod26(key[1][0] * x + key[1][1] * y);

        cipher[i] = 'A' + c1;
        cipher[i + 1] = 'A' + c2;
    }

    cipher[i] = '\0';
}

void decrypt(char cipher[], char plain[], int key[2][2]) {
    int det, invDet;
    int inv[2][2];
    int i, x, y;

    det = mod26(key[0][0] * key[1][1] -
                key[0][1] * key[1][0]);

    invDet = modInverse(det);

    if (invDet == -1) {
        printf("Key matrix has no inverse modulo 26.\n");
        plain[0] = '\0';
        return;
    }

    inv[0][0] = mod26(invDet * key[1][1]);
    inv[0][1] = mod26(-invDet * key[0][1]);
    inv[1][0] = mod26(-invDet * key[1][0]);
    inv[1][1] = mod26(invDet * key[0][0]);

    for (i = 0; cipher[i] != '\0'; i += 2) {
        x = cipher[i] - 'A';
        y = cipher[i + 1] - 'A';

        plain[i] =
            'A' + mod26(inv[0][0] * x + inv[0][1] * y);

        plain[i + 1] =
            'A' + mod26(inv[1][0] * x + inv[1][1] * y);
    }

    plain[i] = '\0';
}

int main() {
    char input[1000];
    char plain[1000];
    char cipher[1000];
    char recovered[1000];

    int key[2][2] = {
        {9, 4},
        {5, 7}
    };

    printf("Hill Cipher 2x2\n");
    printf("Key matrix:\n");
    printf("9 4\n");
    printf("5 7\n");

    printf("\nEnter plaintext\n");
    printf("(Default example: meet me at the usual place at ten rather than eight oclock)\n");
    printf("Plaintext: ");

    fgets(input, sizeof(input), stdin);

    cleanText(input, plain);

    printf("\nPrepared plaintext: %s\n", plain);

    printf("\nEncryption calculations:\n");

    int i;
    for (i = 0; plain[i] != '\0'; i += 2) {
        int x = plain[i] - 'A';
        int y = plain[i + 1] - 'A';
        int c1 = mod26(9 * x + 4 * y);
        int c2 = mod26(5 * x + 7 * y);

        printf("(%c,%c) -> (%d,%d) -> (%c,%c)\n",
               plain[i], plain[i + 1],
               x, y,
               'A' + c1, 'A' + c2);
    }

    encrypt(plain, cipher, key);

    printf("\nCiphertext: %s\n", cipher);

    decrypt(cipher, recovered, key);

    printf("\nDecryption:\n");
    printf("Recovered plaintext: %s\n", recovered);

    /*
       For this key:
       determinant = 9*7 - 4*5 = 43
       43 mod 26 = 17
       inverse of 17 mod 26 = 23

       Therefore inverse matrix is:
       23 * [ 7  -4
             -5   9 ] mod 26

       = [ 5  12
           15  25 ]
    */

    printf("\nInverse calculation:\n");
    printf("det(K) = 9*7 - 4*5 = 43 = 17 mod 26\n");
    printf("17^(-1) mod 26 = 23\n");
    printf("K^(-1) mod 26 =\n");
    printf("5  12\n");
    printf("15 25\n");

    return 0;
}
