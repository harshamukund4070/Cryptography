#include <stdio.h>

int mod26(int x) {
    x %= 26;
    if (x < 0)
        x += 26;
    return x;
}

int inverseMod26(int a) {
    int i;

    for (i = 1; i < 26; i++)
        if ((a * i) % 26 == 1)
            return i;

    return -1;
}

int main() {
    int p[2][2];
    int c[2][2];

    int det, invDet;
    int invP[2][2];
    int key[2][2];
    int i, j;

    printf("HILL CIPHER - KNOWN PLAINTEXT ATTACK\n");
    printf("Enter two known plaintext blocks as numbers.\n");
    printf("Use A=0, B=1, ..., Z=25.\n\n");

    printf("Plaintext matrix P:\n");
    for (i = 0; i < 2; i++)
        for (j = 0; j < 2; j++)
            scanf("%d", &p[i][j]);

    printf("\nCorresponding ciphertext matrix C:\n");
    for (i = 0; i < 2; i++)
        for (j = 0; j < 2; j++)
            scanf("%d", &c[i][j]);

    /*
       Hill cipher:
       C = K P

       Therefore:
       K = C P^(-1) mod 26
    */

    det = mod26(p[0][0] * p[1][1] -
                p[0][1] * p[1][0]);

    invDet = inverseMod26(det);

    if (invDet == -1) {
        printf("\nP is not invertible modulo 26.\n");
        printf("Choose known plaintext blocks whose matrix determinant\n");
        printf("is relatively prime to 26.\n");
        return 1;
    }

    invP[0][0] = mod26(invDet * p[1][1]);
    invP[0][1] = mod26(-invDet * p[0][1]);
    invP[1][0] = mod26(-invDet * p[1][0]);
    invP[1][1] = mod26(invDet * p[0][0]);

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            key[i][j] =
                mod26(c[i][0] * invP[0][j] +
                      c[i][1] * invP[1][j]);
        }
    }

    printf("\nP determinant = %d\n", det);
    printf("Inverse of determinant = %d\n", invDet);

    printf("\nP inverse modulo 26:\n");
    printf("%d %d\n", invP[0][0], invP[0][1]);
    printf("%d %d\n", invP[1][0], invP[1][1]);

    printf("\nRecovered Hill key matrix K:\n");
    printf("%d %d\n", key[0][0], key[0][1]);
    printf("%d %d\n", key[1][0], key[1][1]);

    printf("\nFormula used: K = C * P^(-1) mod 26\n");

    return 0;
}
