/** @file cmdproc.h
 * @brief Definition of the return values and the function prototypes.
 *  
 * In order to avoid unwated exceptions and errors during all reading operations,
 * the functions in this file are defined in order to return the correct values and the associated
 * error codes if they were to fail. All of this having in Unit Testing.
 * 
 * @author Paulo Pedreiras
 * @authors Gonçalo Soares & Gonçalo Rodrigues
 * @date 27 March 2023
 * @bug No known bugs.
 */

#ifndef __CMD_PROC_H_
#define __CMD_PROC_H_

/* Some defines */
/* Other defines should be return codes of the functions */
#define CMD_SUCCESS       0     /**<Return value when a correct command is read.*/
#define CMD_ERROR_STRING -1     /**<Return value when an empty string or incomplete command was found.*/
#define CMD_INVALID      -2     /**<Return value when an invalid command was found.*/
#define CS_ERROR         -3     /**<Return value when a CS error is detected.*/
#define STR_WRONG_FORMAT -4     /**<Return value when the string format is wrong.*/             

#define MAX_CMDSTRING_SIZE 10   /**<Maximum size of the command string.*/ 
#define SOF_SYM '#'	            /**<Start of Frame Symbol.*/
#define EOF_SYM '!'             /**<End of Frame Symbol.*/

/* Function prototypes */

/**
 * @brief This function processes commands received via UART.
 * 
 * @return int Returns a value to indicate whether the command was valid or not.
 */
int cmdProcessor(void);

/**
 * @brief This function adds a new character to the command string.
 * 
 * @param newChar The new character to be added to the command string.  
 * @return int Returns a value to indicate whether the command was valid or not.
 */
int newCmdChar(unsigned char newChar);

/**
 * @brief This function resets the command string.
 * 
 */
void resetCmdString(void);

#endif
