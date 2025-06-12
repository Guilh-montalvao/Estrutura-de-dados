#include <stdio.h>

void atualizaNotas(float *nota1, float *nota2, float *nota3){
    *nota1 = *nota1 + 1;
    *nota2 = *nota2 + 1;
    *nota3 = *nota3 + 1;

}

int main() {
    float n1 = 3.5, n2 = 7.0, n3 = 9.0;
    atualizaNotas(&n1, &n2, &n3);
    printf("%.2f, %.2f, %.2f", n1, n2, n3);

    return 0;
}