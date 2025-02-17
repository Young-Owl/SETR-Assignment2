/** @file cmdproc.h
 * @brief Base code for Unit Testing.
 * 
 * @author Paulo Pedreiras
 * @date 27 March 2023
 * @bug No known bugs.
 */

/* ***************************************************** */
/* SETR 22/23, Paulo Pedreiras                           */
/* Base code for Unit Testing                            */
/*   A few tests to the cmdProcessor                     */
/*      just to illustrate how it works                  */
/*   Shoud be improved (e.g. test more cases)            */
/*                                                       */
/* Compile with: gcc cmdproc.c main.c -o main            */
/*                                                       */
/* ***************************************************** */
#include <stdio.h>
#include "cmdproc.h"

extern char Kp, Ti, Td;

int main(void) 
{
	int res;
	
	printf("Command processor test app\n\r");
	resetCmdString();
	newCmdChar('#');
	newCmdChar('P');
	newCmdChar('1');
	newCmdChar('2');
	newCmdChar('3');
	newCmdChar((unsigned char)('P'+'1'+'2'+'3'));
	newCmdChar('!');
	res=cmdProcessor();
	printf("cmdProcessor output to P 1 2 3: %d, Kp=%c,Ti=%c,Td=%c \n\r", res, Kp, Ti, Td);
	
	newCmdChar('#');
	newCmdChar('D');
	newCmdChar('!');
	res=cmdProcessor();
	printf("cmdProcessor output to D (typo, should be S): % d\n\r", res);
	
	newCmdChar('+');
	newCmdChar('S');
	newCmdChar('!');
	res=cmdProcessor();
	printf("cmdProcessor output to S with wrong SOF: % d\n\r", res);
	
}
