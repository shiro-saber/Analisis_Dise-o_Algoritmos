/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
* File Name : main.c
* Creation Date : 28-10-2015
* Last Modified : Wed 28 Oct 2015 10:44:50 PM CST
* Created By : root

KNOW LEARN        .==.
C LANGUAGE       ()''()-.
      .---.       ;--; /
    .'_:___". _..'.  __'.
    |__ --==|'-''' \'...;
   [  ]  :[|       |---\
    |__| I=[|     .'    '.
    / / ____|     :       '._
   |-/.____.'      | :       :
  /___\ /___\      '-'._----'
_._._._._._._._._._._._._._._._._._._._._.*/

/* Algoritmo MidPointCircle */
#include <graphics.h>
#include <stdio.h>

/* Dibuja por simetría en todos los octantes */
int circlePoints(int x, int y, int puntos[], int i)
{
 int maxx = getmaxx()/2;
 int maxy = getmaxy()/2;

 puntos[i]=maxx+x;
 puntos[i+1]=maxy+y;
 i+=2;

 putpixel(maxx+x,maxy+y,WHITE);
 putpixel(maxx+y,maxy+x,WHITE);
 putpixel(maxx-x,maxy+y,WHITE);
 putpixel(maxx-y,maxy+x,WHITE);

 return i;
}

/* Algoritmo MidPointCircle */
int midPointCircle(int radius, int puntos[])
{
 int x = 0, y = radius;
 double p = 5.0/4.0-radius;
 int i = 0;

 i = circlePoints(x, y, puntos, i);

 while(y>x)
 {
   if(p < 0)
     p += 2.0 * x + 1.0;
   else
   {
     p += 2.0 * (x - y) + 1.0;
     y--;
   }
   x++;
   i = circlePoints(x, y, puntos, i);
 }
 return i;
}

int main()
{
 int gd=DETECT, gm;
 int radius;

 int puntos[10000];
 int count=0;

 printf("Radio del arco: ");
 scanf("%d",&radius);

 initgraph(&gd, &gm, NULL);

 count = midPointCircle(radius, puntos);

 getch();
 closegraph();

 return 0;
}
