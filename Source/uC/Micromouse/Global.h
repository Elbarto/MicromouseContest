/*
 * Global.h
 *
 * Created: 12/03/2016 16:34:40
 *  Author: jolanbarbancon
 */ 


#ifndef GLOBAL_H_
#define GLOBAL_H_

	#ifndef F_CPU
	#define F_CPU 20000000UL // 20 MHz clock speed
	#endif

	//Select a file with a main to compile
	#define TEST_MOTEUR


	//Simple command that we can use in every file
	#define SET(x,y) (x|=(1<<y))
	#define CLR(x,y) (x&=(~(1<<y)))
	#define CHK(x,y) (x&(1<<y))
	#define TOG(x,y) (x^=(1<<y))



#endif /* GLOBAL_H_ */