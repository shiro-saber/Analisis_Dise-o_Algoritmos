/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
* File Name : main.c
* Creation Date : 22-10-2015
* Last Modified : Wed 28 Oct 2015 10:35:02 PM CST
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

#include <graphics.h>
#include <stdio.h>
#include <math.h>
#define pi 3.1416

/* lo que nos dio cubells*/
/* Algoritmo DDA */
int DDALine(int x0, int y0, int x1, int y1, int puntos[])
{
	int maxY, i;
	float dx, dy, m, x, y;

	i=0;

	dx=x1-x0;
	dy=y1-y0;
	maxY=getmaxy();

	if (dx == 0) /* Es una línea vertical */
	{
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

/* Guardar los puntos dibujados en un archivo */
void generaArchivo(int puntos[], int count)
{
	FILE *fp;
	int i,np;

	fp=fopen("puntos.txt","w");
	fprintf(fp,"%s","Los puntos dibujados son:\n");
	np=0;
	for(i = 0; i < count; i += 2)
	{
		fprintf(fp,"(%d, %d) ", puntos[i], puntos[i+1]);
		np++;
		if(np==5) { fprintf(fp,"\n"); np=0; }
	}
	fclose(fp);
}

/*Mii funcion*/
int pintaPoligono(int lados, int puntos[])
{
    int x1, x2, y1, y2;
    float i = 0.0;
    int mitadx = getmaxx()/2;
    int mitady = getmaxy()/2;
    x1 = mitadx + 100;
    y1 = mitady;
    
    for(int m = 0; m < lados; ++m)
    {
        i = i + (360/lados);
        x2 = mitadx + (100*cos(i*pi/180.0));
        y2 = mitady + (100*sin(i*pi/180.0)); 
        DDALine(x1, y1, x2, y2, puntos); //dibujamos la línea
       
        x1 = x2;//comenzamos desde el siguiente punto
        y1 = y2;//comenzamos desde el siguiente punto
    }
    return i;
}

int main(int argc, char **argv)
{
	int lados, x1, y1, x2, y2;
	int gd = DETECT, gm = VGAMAX;
	int puntos[1000], count;

	printf("Numero de lados: ");
	scanf("%d", &lados);

	initgraph(&gd, &gm, NULL);
	pintaPoligono(lados, puntos);

	getch();
	closegraph();

	return 0;
}
