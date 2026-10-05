#include <stdio.h>
#include <ctype.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

int main() {
    char plaintext[1000];
    int a, b, i;

    printf("Affine Caesar Cipher\n");
    printf("Formula: C = (a*p + b) mod 26\n\n");

    printf("Enter plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);

    printf("Enter value of a: ");
    scanf("%d", &a);

    printf("Enter value of b (0-25): ");
    scanf("%d", &b);

    b = ((b % 26) + 26) % 26;

    /*
       For the affine cipher to be one-to-one:
       gcd(a, 26) must be 1.

       Valid a values modulo 26:
       1, 3, 5, 7, 9, 11, 15, 17, 19, 21, 23, 25

       b has no coprimality restriction.
       Any value of b is allowed modulo 26 (0 to 25).
    */

    if (gcd(a, 26) != 1) {
        printf("\nInvalid value of a.\n");
        printf("a must be relatively prime to 26.\n");
        printf("Allowed values of a: ");
        printf("1 3 5 7 9 11 15 17 19 21 23 25\n");
        return 1;
    }

    for (i = 0; plaintext[i] != '\0'; i++) {
        if (isupper((unsigned char)plaintext[i])) {
            plaintext[i] =
                'A' + (a * (plaintext[i] - 'A') + b) % 26;
        } else if (islower((unsigned char)plaintext[i])) {
            plaintext[i] =
                'a' + (a * (plaintext[i] - 'a') + b) % 26;
        }
    }

    printf("Ciphertext: %s", plaintext);

    printf("\n\nAnswers:\n");
    printf("a) Limitation on b: No restriction except modulo 26; b can be 0 to 25.\n");
    printf("b) Allowed a values: 1, 3, 5, 7, 9, 11, 15, 17, 19, 21, 23, 25.\n");

    return 0;
}
