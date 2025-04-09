#include <stdio.h>

void media(float n1, float n2, float *resultado) {
    *resultado = (n1 + n2) / 2;
}

int main() {
    float n1 = 5.5;
    float n2 = 7.5;
    float resultado;

    media(n1, n2, &resultado);
    printf("Media: %.2f\n", resultado);

    return 0;
}
