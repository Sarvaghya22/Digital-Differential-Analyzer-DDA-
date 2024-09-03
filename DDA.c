#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void main()
{
    float x1,x2;
    float y1,y2;
    int steps;
    float xinc,yinc;
    float deltaX, deltaY;   
    int x,y;

    
    printf("enter x1 and y1\n");
    scanf("%f %f",&x1,&y1);

    printf("x1: %.1f      y1: %.1f\n",x1,y1);

    printf("enter x2 and y2\n");
    scanf("%f %f",&x2,&y2);

    printf("x2: %.1f      y2: %.1f\n",x2,y2);

    deltaX= x2 - x1;
    //deltaX = abs(deltaX);
    deltaY= y2 - y1;
    //deltaY = abs(deltaY);
    


    if(abs(deltaX)>abs(deltaY))
    {
        steps= deltaX;
        printf("deltaX as Steps\n");
    }
    else
    {   
        steps= deltaY;
        printf("deltaY as Steps\n");
    }

    printf("deltaX :%.1f\n",deltaX);
    printf("deltaY :%.1f\n",deltaY);
    printf("steps :%d\n",abs(steps));

    xinc = deltaX/abs(steps);
    yinc = deltaY/abs(steps);

    printf("xinc :%.1f        yinc: %.1f\n\n", xinc,yinc);

    printf("x: %.1f      y: %.1f\n",x1,y1);
    for(int i =1; i<abs(steps); i++)
    {
        x1 = x1+ xinc;
        y1 = y1+ yinc;

        printf("x :%.1f        y: %.1f\n", x1,y1);
    }
    printf("x: %.1f      y: %.1f\n",x2,y2);
    

}