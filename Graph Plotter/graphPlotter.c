#include <stdio.h>
#include <math.h>

int main() {
    int a, b, c;
    char graph[30][60];
    
    printf("Graph Plotter\n");
    printf("Enter quadratic equation's coefficients\n");
    printf("Equation is of the form y = ax^2 + bx + c\n");
    scanf("%d %d %d", &a, &b, &c);
    
    for (int i = 0; i < 30; i++) {
        for (int j = 0; j < 60; j++) {
            int x = j - 30;
            int y = a * x * x + b * x + c;
            if (i == 15 - y / 2) {
                graph[i][j] = '*';
            } else {
                graph[i][j] = ' ';
            }
        }
    }
    for (int j = 0; j < 60; j++) {
        graph[15][j] = '-';
    }
    for (int i = 0; i < 30; i++) {
        graph[i][30] = '|';
    }
    printf("Printing the graph..\n");
    for (int i = 0; i < 30; i++) {
        for (int j = 0; j < 60; j++) {
            printf("%c", graph[i][j]);
        }
        printf("\n");
    }
    return 0;
}
