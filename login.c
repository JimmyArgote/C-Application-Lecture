#include <stdio.h>
#include <time.h>
/* lg = login, ps = password */
/* função de atenticação*/

//#define CLOCKS_PER_SEC 10
int timeout ( int seconds )
{
    clock_t endwait;
    endwait = clock () + seconds * CLOCKS_PER_SEC ;
    while (clock() < endwait) {
    }

    return 1;
}

remaining(int seconds )
{
    int tempo = 0, hora = 0, minuto = 0, segundo = seconds;

   while(tempo < 10)
   {
       printf("CRONOMEOTRP:\n\n");
       printf("%d:%d:%d\n\n", hora, minuto, segundo);
       //sleep(1000);
       system("clear");
       segundo++;

       if(segundo == 60)
       {
           segundo = 0;
           minuto++;
       }
       if(minuto == 60)
       {
           minuto = 0;
           hora++;
       }
       if(hora == 24)
       {
            hora = 0;
       }
   }
}

