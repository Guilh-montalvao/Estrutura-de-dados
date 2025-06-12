#include <stdio.h> 

void deslocar(int *a, int *b){
    *a = *b; 
    *b = *b - *b; //zerando o valor do ponteiro
}

int main(){

    int a = 10; 
    int b = 7; 

    deslocar(&a, &b); 
    printf("a = %d, b = %d", a, b);
}