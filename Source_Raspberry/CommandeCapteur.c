#include <stdio.h>
#include <wiringPi.h>

//Paramétre du programme
#define N_SENSOR = 3

//definission des pins
#define SEL0 
#define SEL1 //Selection de l'output du demux
#define SEL2

#define OSC //Commande reset de l'oscillateur

//Pin pour la mesure analogique, a voir comment on fait
#define PINRD

int main (void)
{
  wiringPiSetup () ;
  init();

  for (;;)
  {
    digitalWrite (0, HIGH) ; delay (500) ;
    digitalWrite (0,  LOW) ; delay (500) ;
  }
  return 0 ;
}

int init()
{
	//Output
	pinMode (SEL0, OUTPUT);
	pinMode (SEL1, OUTPUT);
	pinMode (SEL2, OUTPUT);
	pinMode (OSC, OUTPUT);

	//Input
}

void GetSensorCapture(int* Result)
{
	int i;
	for(i = 0; i < N_SENSOR; i++)
	{
		digitalWrite(SEL0, (i & 1)); //Recupere le bit 0 
		digitalWrite(SEL1, (i & 2)); // 1
		digitalWrite(SEL2, (i & 4)); // et 2
		
	}
}