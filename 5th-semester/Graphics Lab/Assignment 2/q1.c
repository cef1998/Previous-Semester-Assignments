/*
NAME - ANKIT MISHRA
REG NO - 20168047
PROGRAM - DDA LINE GENERATION ALGORITHM
*/

#include<stdio.h>
#include<graphics.h>
//Function for finding absolute value
int abs (int n)
{
    return ( (n>0) ? n : ( n * (-1)));
}
 
//DDA Function for line generation
void DDA(int X0, int Y0, int X1, int Y1)
{
    // calculate dx & dy
    int dx = X1 - X0;
    int dy = Y1 - Y0;
 
    // calculate steps required for generating pixels
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
 
    // calculate increment in x & y for each steps
    float Xinc = dx / (float) steps;
    float Yinc = dy / (float) steps;
 
    // Put pixel for each step
    float X = X0;
    float Y = Y0;
    int i;
    for (  i = 0; i <= steps; i++)
    {
        putpixel (X,Y,YELLOW);  // put pixel at (X,Y)
        X += Xinc;           // increment in x at each step
        Y += Yinc;           // increment in y at each step
        delay(100);          // for visualization of line-
                             // generation step by step
    }
}
int main()
{
    int gd = DETECT, gm;
    int X0 , Y0 , X1 , Y1 ;
    printf("Enter co-ordinates of first point: ");
    scanf("%d%d", &X0, &Y0);
    printf("Enter co-ordinates of second point: ");
    scanf("%d%d", &X1, &Y1);
    // Initialize graphics function
    initgraph (&gd, &gm, "");  
    DDA(X0, Y0, X1, Y1);
    getch();
    closegraph();
    return 0;
} 
