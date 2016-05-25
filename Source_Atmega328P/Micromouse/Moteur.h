#ifndef MOTEUR_H
#define MOTEUR_H

void PWM_Init(uint16_t PWM_top);
void PWM_SetDutyCycleA(uint16_t duty_cycle);
void PWM_SetDutyCycleB(uint16_t duty_cycle);
void PWM_SetTop(uint16_t TOP_val);

void Counter_INIT();
float GetFrequency(int sel);

void ControlLoop(int wheel_freqA, int wheel_freqB);
float CorrecteurPI(int commande, double frequency);


#endif