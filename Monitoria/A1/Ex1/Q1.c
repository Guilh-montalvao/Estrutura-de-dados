#include <stdio.h>

void dobra(int *n) {
    *n = *n * 2;
}

int main() {
    int x = 4;
    dobra(&x);
    printf("%d\n", x);
    return 0;
}

// 8 porque o valor de N é passado por referencia para a variavel X que multiplica seu valor por 2 que resulta em 8.