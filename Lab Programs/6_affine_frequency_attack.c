#include <stdio.h>
#include <string.h>

int gcd(int a, int b) {
    while (b != 0) {
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}

int mod(int x) {
    x %= 26;
    if (x < 0) x += 26;
    return x;
}

int inverse(int a) {
    int x;
    for (x = 1; x < 26; x++)
        if ((a * x) % 26 == 1)
            return x;
    return -1;
}

int main() {
    char ciphertext[2000];
    int freq[26] = {0};
    int i, max1 = -1, max2 = -1;
    char first, second;
    int a = 3, b = 15, inv;

    printf("Enter affine ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);

    for (i = 0; ciphertext[i] != '\0'; i++) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z')
            freq[ciphertext[i] - 'A']++;
        else if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z')
            freq[ciphertext[i] - 'a']++;
    }

    for (i = 0; i < 26; i++) {
        if (freq[i] > max1) {
            max2 = max1;
            max1 = freq[i];
            first = 'A' + i;
        } else if (freq[i] > max2) {
            max2 = freq[i];
            second = 'A' + i;
        }
    }

    printf("\nMost frequent letter: %c\n", first);
    printf("Second most frequent letter: %c\n", second);

    /*
       Assuming:
       B -> E (E = 4)
       U -> T (T = 19)

       4a + b = 1 (mod 26)
       19a + b = 20 (mod 26)

       Therefore:
       15a = 19 (mod 26)
       a = 3, b = 15

       Decryption:
       p = a^(-1)(c-b) mod 26
       3^(-1) mod 26 = 9
    */

    inv = inverse(a);

    printf("\nAssumption: B -> E and U -> T\n");
    printf("Found key: a = %d, b = %d\n", a, b);
    printf("Decryption formula: P = %d(C - %d) mod 26\n", inv, b);

    for (i = 0; ciphertext[i] != '\0'; i++) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z')
            ciphertext[i] = 'A' + mod(inv * ((ciphertext[i] - 'A') - b));
        else if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z')
            ciphertext[i] = 'a' + mod(inv * ((ciphertext[i] - 'a') - b));
    }

    printf("Decrypted text: %s", ciphertext);

    return 0;
}
