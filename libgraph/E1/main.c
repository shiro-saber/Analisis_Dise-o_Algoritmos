/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
* File Name : main.c
* Creation Date : 22-10-2015
* Last Modified : Thu 22 Oct 2015 02:25:28 PM CDT
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

int DDALine(int lados)
{
    float lastpoint = 0.0;
    int maxY, i;

    for (int j= 0; j < lados; j++)
    {
        if(lastpoint == 0)
        {
            for(float y = 0; y <= 100.0; ++y)
            {
                putpixel(100, maxY-y, RED);
                i += 2;
            }
        }
    }
    return i;
}

int main()
{
    int gd = DETECT, gm, error;
    int a;
    initgraph(&gd, &gm, "f:\\tc\\bgi");
    printf("Entra el numero de lados ");
    scanf("%d", &a);

    DDALine(1);

    getch();
    closegraph();

    return 0;
}
