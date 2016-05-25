#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include "Global.h"
#include "Moteur.h"

/*
Recap of register : I indicate the timer used (0-2)
	OCRIX -> Duty_cycle Value X mean A or B to select the PWM
	TCCRIA -> PWM Mode (Invert, Non invert, Fast or Phase corrected)
	TCCRIB -> PWM prescaler clock
	
	Here we used 16-Bit Timer1 with output PWM on pin OC1A : (15) and OC1B (16)
	
	Frequency meter on pin 6
*/

/*
--------	Definition for global Parameters	--------
*/
//Correcter K*(1+TAU*s)/s
#define K 5 // 
#define TAU 1 //

//Motor constant
#define KM 100
#define REDUCTION 1
#define RPM_MAX 7000

//Timer acquisition 
#define TIMER2_T 0xA0 //


//Global variable
double counterA = 0, counterB = 0; //Count impulse form motor encoder
double frequencyA = 0, frequencyB = 0;
uint8_t porthistory = 0;

void PWM_Init(uint16_t PWM_top)
{
	//Set the PWM Pin as Output
	SET(DDRB,PORTB1);
	SET(DDRB,PORTB2);
	
	//Init duty_ycle to 0
	OCR1A = 0;
	OCR1B = 0;
	
	//Set TOP Value
	ICR1 = PWM_top; // PWM Frequency = F_CPU/(2*ICR1)
	
	
	//Set the mode of operation
	//COM1X1 -> Non Inverted Mode
	//WGM13 set Phase and Frequency corrected mode, with top value on 16bit register ICR1 (define PWM frequency)
	//CS10 No clock prescaler
	TCCR1A |= (1 << COM1A1) | (1 << COM1B1);
	TCCR1B |= (1 << WGM13) | (1 << CS10);
	
}

void Counter_INIT()
{
	//Setup 4 interrupt pin
	SET(DDRD,PORTD4|PORTD5|PORTD6|PORTD7); //Set as Input the 4 pin
	//SET(PORTD,PORTD4|PORTD5|PORTD6|PORTD7);
	
	SET(PCICR,PCIE2);   //Setup Scan interrupt on pin PORTD [16-23] (PCIE1 PORTC: 8-14 et PCIE2 PORTD 16-23)
	SET(PCMSK2,PCINT21|PCINT22|PCINT20|PCINT23);     // Turns on PCINTx interrupt
	
	//TIMER2 will update frequency value each X ms;
	TCNT2 = TIMER2_T;
	TCCR2B |= (1<<CS22) | (1<<CS21) | (1<<CS20); //Select system clock with 1024 prescaler
	TIMSK2 |= (1<<TOIE2); //Overflow interrupt enable
}

ISR(PCINT2_vect){
	uint8_t changedbits = PIND ^ porthistory;
	porthistory = PIND;
	
	if(changedbits & (1 << PIND5))
	{
		counterA++;
	}
	
	if(changedbits & (1 << PIND6))
	{
		counterA++;
	}
		
	if(changedbits & (1 << PIND4))
	{
		counterB++;
	}

	if(changedbits & (1 << PIND7))
	{
		counterB++;
	}
}

ISR(TIMER2_OVF_vect){
	TOG(PORTC,PORTC1);
	double t_cycle = 1024.0/F_CPU;
	double capture_time = (255.0 - TIMER2_T)*t_cycle;
	
	frequencyA = counterA/capture_time;//Compute frequency
	frequencyB = counterB/capture_time;
	
	TCNT2 = TIMER2_T; //Reset the timer to count from TIMER2_T to 255 ;
	
	//reset counter
	counterA = 0;
	counterB = 0;
}

float GetFrequency(int sel)
{
	if(sel)
		return frequencyA;
	else
		return frequencyB;
}

//wheel_freq is frequency AFTER the gear reduction
void ControlLoop(int wheel_freqA, int wheel_freqB)
{	
	float duty_cycleA = CorrecteurPI(wheel_freqA*REDUCTION, frequencyA)/RPM_MAX;
	float duty_cycleB = CorrecteurPI(wheel_freqB*REDUCTION, frequencyB)/RPM_MAX;
	
	if(duty_cycleA > 1) duty_cycleA = 1;
	if(duty_cycleA < 0) duty_cycleA = 0;
	
	if(duty_cycleB > 1) duty_cycleB = 1;
	if(duty_cycleB < 0) duty_cycleB = 0;
	
	int commandeA = (int) ICR1*duty_cycleA;
	int commandeB = (int) ICR1*duty_cycleB;
	
	PWM_SetDutyCycleA((uint16_t) commandeA);
	PWM_SetDutyCycleB((uint16_t) commandeB);
}

float CorrecteurPI(int commande, double frequency)
{
	float err_ = commande - frequency;
	err_ = err_*K; //Apply the correcter
	return err_;
}

void PWM_SetDutyCycleA(uint16_t duty_cycle)
{
	OCR1A = duty_cycle;
}

void PWM_SetDutyCycleB(uint16_t duty_cycle)
{
	OCR1B = duty_cycle;
}

void PWM_SetTop(uint16_t TOP_val)
{
	ICR1 = TOP_val;
}