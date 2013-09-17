#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double f_x(double x1, double x2) {
  return pow(x2, 2.0) - pow(x1, 2.0) + pow(x2-1, 2.0);
}

double df_x1(double x1, double x2) {
  return 2*x1 - 2*pow(x2, 2.0);
}

double df_x2(double x1, double x2) {
  return 4*pow(x2, 3.0) - 4*x1*x2 + 2*x2 - 2;
}

double d2f_x12(double x1) {
  return 2.0;
}

double d2f_x22(double x2, double x1) {
  return 12*pow(x2, 2.0) - 4*x1 + 2;
}

double d2f_x1x2(double x1, double x2) {
  return -4*x2;
}

int main(int argc, char *argv[])
{
  double fxk = 1, fxkp1 = 0, xkp11, xkp12;
  double xk1 = 2, xk2 = 2;
  double delta;
  
  while(fxk-fxkp1 > 0.01) {
    delta = d2f_x12(xk2)*d2f_x22(xk1, xk2)-pow(d2f_x1x2(xk1, xk2), 2.0);
    xkp11 = xk1 - (d2f_x22(xk1,xk2)*df_x1(xk1, xk2)-d2f_x1x2(xk1, xk2)*df_x2(xk1, xk2))/delta;
    xkp12 = xk2 - (-d2f_x1x2(xk1, xk2)*df_x1(xk1, xk2)+d2f_x12(xk2)*df_x2(xk1, xk2))/delta;
    fxk = f_x(xk1, xk2);
    fxkp1 = f_x(xkp11, xkp12);
    //--------------------------------------------
    printf("       /   %f   \\\n", df_x1(xk1, xk2));
    printf("f'(x)=|                |\n");
    printf("       \\   %f   /\n", df_x2(xk1, xk2));
    //--------------------------------------------
    //printf("df_x1: %f\n", df_x1(xk1, xk2));
    //printf("df_x2: %f\n", df_x2(xk1, xk2));
    //--------------------------------------------
    printf("      /   %f   %f   \\\n", d2f_x12(xk2), d2f_x1x2(xk1, xk2));
    printf("J(x)=|                           |\n");
    printf("      \\   %f   %f   /\n", d2f_x1x2(xk1, xk2), d2f_x22(xk1, xk2));
    //--------------------------------------------
    //printf("d2f_x12: %f\n", d2f_x12(xk2));
    //printf("d2f_x22: %f\n", d2f_x22(xk1));
    //printf("d2f_x1x2: %f\n", d2f_x1x2(xk1, xk2));
    //printf("delta: %f\n", delta);
    //--------------------------------------------
    printf("           1       /  %f   %f  \\\n", d2f_x22(xk1, xk2), -d2f_x1x2(xk1, xk2));
    printf("J(x)^-1=-------   |                            |\n");
    printf("       %f \\  %f   %f  /\n", delta, -d2f_x1x2(xk1, xk2), d2f_x12(xk2));
    //--------------------------------------------
    xk1 = xkp11;
    xk2 = xkp12;
    //printf("xkp11: %f\n", xk1);
    //printf("xkp12: %f\n", xk2);
    //--------------------------------------------
    printf("   /  %f  \\\n", xk1);
    printf("X=|              |\n");
    printf("   \\  %f  /\n", xk2);
    //--------------------------------------------
    //printf("fxk: %f\n", fxk);
    //printf("fxkp1: %f\n", fxkp1);
    //printf("|fxk-fxkp1|: %f\n", fxk-fxkp1);
    //--------------------------------------------
    printf("|fxk-fxkp1|=|%f-%f|=%f", fxk, fxkp1, fxk-fxkp1);
    if(fxk-fxkp1 > 0.01) printf("> 0.01   => Next step\n");
    else printf("< 0.01   => Stop\n");
    //--------------------------------------------
    printf("---------------------------------------------------------------\n");
  }
  return 0;
}
