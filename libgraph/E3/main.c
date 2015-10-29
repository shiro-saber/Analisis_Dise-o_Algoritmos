/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
* File Name : main.c
* Creation Date : 28-10-2015
* Last Modified : Wed 28 Oct 2015 11:21:17 PM CST
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

#include <stdio.h>
#include <graphics.h>
#define PI 3.14159265

int DDALine(int x0, int y0, int x1, int y1, int puntos[])
{
 int maxY, i, temp;

   float dx, dy, m, x, y;

   i=0;
   dx=x1-x0;
   dy=y1-y0;

   maxY=getmaxy();

   if (dx == 0) /* Es una línea vertical */
   {
     if (y0 > y1)
     {
       temp = y1;
       y1 = y0;
       y0 = temp;
       temp = x1;
       x1 = x0;
       x0 = temp;
   }
   for(y = y0; y <= y1; ++y)
   {
     putpixel(x0, maxY-y, WHITE);
     puntos[i] = x0;
     puntos[i+1] = y;
     i += 2;
   }
 }
 else if (dy == 0) /* Es una línea horizontal */
 {
   if (x0 > x1)
   {
     temp = y1;
     y1 = y0;
     y0 = temp;
     temp = x1;
     x1 = x0;
     x0 = temp;
   }
   for(x = x0; x <= x1; ++x)
   {
     putpixel(x, y0, WHITE);
     puntos[i] = x0;
     puntos[i+1] = y;
     i += 2;
   }
 }
 else if (dy <= dx) /* Es una línea con pendiente < 1 */
 {
   if (x0 > x1)
   {
     temp = y1;
     y1 = y0;
     y0 = temp;
     temp = x1;
     x1 = x0;
     x0 = temp;
   }
   m = dy/dx;
   y = y0;

   for(x = x0; x <= x1; ++x)
   {
     putpixel(x, (int)(maxY-y), WHITE);
     puntos[i] = x;
     puntos[i+1] = (int)y;
     i += 2;
     y = y + m;
   }
 }
 else /* Es una línea con pendiente > 1 */
 {
   if (y0 > y1)
   {
     temp = y1;
     y1 = y0;
     y0 = temp;
     temp = x1;
     x1 = x0;
     x0 = temp;
   }

   m = dx/dy;
   x = x0;

   for(y = y0; y <= y1; ++y)
   {
     putpixel((int)x, maxY-y, WHITE);
     puntos[i] = (int)x;
     puntos[i+1] = y;
     i += 2;
     x = x + m;
   }
 }
 return i;
}

 /* Dibuja los puntos por simetría en los demás cuadrantes */
 int ellipsePoints(int x, int y, int puntos[], int i)
 {
   int maxx = getmaxx()/2;
   int maxy = getmaxy()/2;

   putpixel(maxx+x,maxy+y,WHITE);

   puntos[i]=maxx+x;
   puntos[i+1]=maxy+y;
   i+=2;

   putpixel(maxx-x,maxy+y,WHITE);
   putpixel(maxx+x,maxy-y,WHITE);
   putpixel(maxx-x,maxy-y,WHITE);

   return i;
 }

 /* Algoritmo MidPointElipse */
 int midPointEllipse(int a,int b, int puntos[])
 {
   int i = 0;
   double d2;
   int x=0;
   int y=b;
   double dl=b*b-(a*a*b)+(0.25*a*a);

   putpixel(x,y, WHITE);

   while((a*a*(y-0.5))>(b*b*(x+1)))
   {
     if(dl<0)
       dl+=b*b*(2*x+3);
     else
     {
       dl+=b*b*(2*x+3)+a*a*(-2*y+2);
       y--;
     }
     x++;
     i = ellipsePoints(x, y, puntos, i);
   }

   d2=b*b*(x+0.5)*(x+0.5)+a*a*(y-1)*(y-1)-a*a*b*b;

   while(y>0)
   {
     if(d2<0)
     {
       d2+=b*b*(2*x+2)+a*a*(-2*y+3);
       x++;
     }
     else
       d2+=a*a*(-2*y+3);

     y--;
     i = ellipsePoints(x, y, puntos, i);
   }
   return i;
 }

void cubo(int* puntos)
{
 int x1, y1, x2, y2;
 int n = 4;
 int r = 360;
 int mitadx = getmaxx()/2;
 int mitady = getmaxy()/2;

 x1 = mitadx + 100;
 y1 = mitady;

 float i = 0;
 int m = 0;

 for (m = 0; m < n; ++m)
 {
   i = i + (360/n);
   x2 = mitadx + (100*cos(i*PI/180.0));
   y2 = mitady + (100*sin(i*PI/180.0));

   DDALine(x1, y1, x2, y2, puntos);
   DDALine(x1 + 20, y1 +10, x2 +20, y2 +10, puntos);
   DDALine(x1, y1, x1+20, y1+10, puntos);

   x1 = x2;
   y1 = y2;
 }
}

void prismas(int* puntos)
{
   int x1, y1, x2, y2;
   int n = 2;
   int r = 360;
   int xa, ya;
   int mitadx = getmaxx()/2;
   int mitady = getmaxy()/2;

   xa = mitadx;
   ya = mitady + 150;
   x1 = mitadx - 100;
   y1 = mitady;

   float i = 0;
   int m = 0;

   x2 = mitadx +100;
   y2 = mitady;

   DDALine(x1, y1, x2, y2, puntos);
   DDALine(x1 + 20, y1 -10, x2 +20, y2 -10, puntos);
   DDALine(x1, y1, x1+20, y1+10, puntos);
   DDALine(x2, y2, x2+20, y2+10, puntos);
   DDALine(x1, y1, xa, ya, puntos);
   DDALine(x1 +20, y1 +10, xa, ya, puntos);
   DDALine(xa, ya, x2, y2, puntos);
   DDALine(xa, ya, x2 +20, y2+10, puntos);
}

void prismat(int* puntos){
 int x1, y1, x2, y2;
 int n = 2;
 int r = 360;
 int xa, ya;
 int mitadx = getmaxx()/2;
 int mitady = getmaxy()/2;
 xa = mitadx;
 ya = mitady + 150;
 x1 = mitadx + 100;
 y1 = mitady;
 float i = 0;
 int m = 0;
   x2 = mitadx - 100;
   y2 = mitady;
   DDALine(x1, y1, x2, y2, puntos);
   DDALine(x1, y1, xa, ya, puntos);
   DDALine(xa, ya, x2, y2, puntos);
   DDALine(x1, y1, (x1 + x2) / 2, ((y1 + y2)/2) +15, puntos);
   DDALine((x1 + x2) / 2, ((y1 + y2)/2) +15,x2, y2,  puntos);
   DDALine(xa, ya, (x1 + x2) / 2, ((y1 + y2)/2) +15, puntos);
}


void cono(int* puntos){
 int x = 100;
 int y = 40;
 int xa = getmaxx()/2;
 int ya = (getmaxy()/2) + 150;
 midPointEllipse(x, y, puntos);
 int x2 = (getmaxx()/2)-100;
 int y2 = getmaxy()/2;
 DDALine(xa, ya, x2, y2, puntos);
 x2 = x2 +200;
 DDALine(xa, ya, x2, y2, puntos);
}

int main(int argc, char **argv)
{
 	int x1, y1, x2, y2;
 	int gd = DETECT, gm = VGAMAX;
 	int puntos[1000], count;

 	initgraph(&gd, &gm, NULL);
  cubo(puntos);
  sleep(1);
  closegraph();
  initgraph(&gd, &gm, NULL);
  prismas(puntos);
  sleep(1);
  closegraph();
  initgraph(&gd, &gm, NULL);
  prismat(puntos);
  sleep(1);
  closegraph();
  initgraph(&gd, &gm, NULL);
  cono(puntos);

 	getch();

 	closegraph();

 	return 0;
}
