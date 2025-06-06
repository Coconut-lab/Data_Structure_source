#ifndef MYHEADER_H
#define MYHEADER_H

#include <stdio.h>

extern double num1, num2, result;
extern char operator;

void myInput(void);
void myOutput(void);
double calculate(double a, double b, char op);

#endif
