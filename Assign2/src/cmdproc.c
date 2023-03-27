/** @file cmdproc.c
 * @brief Implementation of all functions related to the command processor.
 *
 * @author Gonçalo Soares & Gonçalo Rodrigues
 * @date 27 March 2022
 * @bug No known bugs.
 */

/* ***************************************************** */
/* SETR 22/23, Paulo Pedreiras                           */
/* Base code for Unit Testing                            */
/*    Simple example of command processor                */
/*    Note that there are several simplifications        */
/*    E.g. Kp, Ti and Td usually are not integer values  */
/*    Code can (and should) be improved. E.g. error      */ 
/*        codes are "magic numbers" in the middle of the */
/*        code instead of being (defined) text literals  */
/* ***************************************************** */

#include <stdio.h>

#include "cmdproc.h"

/* PID parameters */
/* Note that in a real application these vars would be extern */
char Kp, Ti, Td;

/* Checksum Parameter */
char Cs;

/* Process variables */ 
/* Note that in a real application these vars would be extern */
int setpoint, output, error; 

/* Internal variables */
static char cmdString[MAX_CMDSTRING_SIZE];
static unsigned char cmdStringLen = 0; 

/* ************************************************************ */
/* Processes the chars received so far looking for commands */
/* Returns:                                                     */
/*  	 0: if a valid command was found and executed           */
/* 	-1: if empty string or incomplete command found             */
/* 	-2: if an invalid command was found                         */
/* 	-3: if a CS error is detected (command not executed)        */
/* 	-4: if string format is wrong                               */
/* ************************************************************ */
int cmdProcessor(void)
{
	int i;
	
	/* Detect empty cmd string */
	if(cmdStringLen == 0)
		return CMD_ERROR_STRING; 
	
	/* Find index of SOF */
	for(i=0; i < cmdStringLen; i++) {
		if(cmdString[i] == SOF_SYM) {
			break;
		}
	}
	
	/* If a SOF was found look for commands */
	if(i < cmdStringLen) {
		if(cmdString[i+1] == 'P') { /* P command detected */
			Kp = cmdString[i+2];
			Ti = cmdString[i+3];
			Td = cmdString[i+4];
			if(Kp < '0' || Kp > '9' || Ti < '0' || Ti > '9' || Td < '0' || Td > '9') {
				return STR_WRONG_FORMAT;
			}

			Cs = (unsigned char)('P' + Kp + Ti + Td);
			if(Cs != cmdString[i+5]){
				return CS_ERROR;
			}
			
			if(cmdString[i+6] != EOF_SYM){
				return CMD_ERROR_STRING;
			}

			resetCmdString();
			return CMD_SUCCESS;
		}
		
		if(cmdString[i+1] == 'S') { /* S command detected */
			Cs = (unsigned char)('S');
			if(Cs != cmdString[i+2]){
				return CS_E	RROR;
			}

			if(cmdString[i+3] != EOF_SYM){
				return CMD_ERROR_STRING;
			}

			printf("Setpoint = %d, Output = %d, Error = %d", setpoint, output, error);
			resetCmdString();
			return CMD_SUCCESS;
		}	
		return CMD_INVALID;	/* No valid command found */
	}
	
	/* cmd string not null and SOF not found */
	return STR_WRONG_FORMAT;

}

/* ******************************** */
/* Adds a char to the cmd string 	*/
/* Returns: 				        */
/*  	 0: if success 		        */
/* 		-1: if cmd string full 	    */
/* ******************************** */
int newCmdChar(unsigned char newChar)
{
	/* If cmd string not full add char to it */
	if (cmdStringLen < MAX_CMDSTRING_SIZE) {
		cmdString[cmdStringLen] = newChar;
		cmdStringLen +=1;
		return CMD_SUCCESS;		
	}
	
	/* If cmd string full return error */
	return CMD_ERROR_STRING;
}

/* ************************** */
/* Resets the command string  */  
/* ************************** */
void resetCmdString(void)
{
	cmdStringLen = 0;		
	return;
}
