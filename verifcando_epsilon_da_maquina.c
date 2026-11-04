#include <stdio.h>

int main() {
    double epsilon = 1.0;
    
    while ((1.0 + epsilon) > 1.0) {
        epsilon = epsilon / 2.0;
    }
    
    epsilon = epsilon * 2.0;
    printf("\n\n");
    printf("Épsilon calculado (C): %1.50e\n", epsilon);
    printf("\n\n");
    return 0;
}