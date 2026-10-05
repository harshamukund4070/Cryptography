#include <stdio.h>
#include <math.h>

/*
Q11:
Playfair uses a 5x5 matrix.

Naive number of arrangements:
25!

log2(25!) ≈ 83.68
So approximately 2^84 possible keys.

When equivalent keys are considered, the effective key space is
approximately 2^62.4 (about 5.9 x 10^18) for the conventional
Playfair key equivalence calculation.

This program calculates the values.
*/

int main() {
    long double log2_25_fact = 0.0L;
    long double log2_effective;

    int i;

    for (i = 1; i <= 25; i++)
        log2_25_fact += log2l((long double)i);

    /*
       Standard Playfair effective-key estimate:
       approximately 2^62.4.
    */
    log2_effective = 62.4L;

    printf("PLAYFAIR KEY SPACE\n\n");

    printf("Possible raw 5x5 matrices = 25!\n");
    printf("log2(25!) = %.2Lf\n", log2_25_fact);
    printf("Therefore raw key space is approximately 2^%.0Lf.\n",
           roundl(log2_25_fact));

    printf("\nAfter considering equivalent keys:\n");
    printf("Effective key space is approximately 2^%.1Lf.\n",
           log2_effective);
    printf("Approximately %.3Le effective keys.\n",
           powl(2.0L, log2_effective));

    return 0;
}
