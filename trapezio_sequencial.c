#include <math.h>
#include <stdio.h>
#include <time.h>

double f(double x){
    return (x*x);
}

int main(){

time_t inicio;
time_t fim;
time(&inicio);

double n = 1000000000;

double a = 0;
double b = 1;

double h = (b-a)/n;

double integral = (f(a) + f(b))/2;

for (int i = 1; i < n - 1; i++)
{
    integral += f(a + h*i);
}

integral *= h;

printf("\nValor da Integral: %f\n", integral);

time(&fim);

printf("\nTempo passado: %.2ld\n", fim - inicio);


}
