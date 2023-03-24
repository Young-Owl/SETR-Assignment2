#ifndef __CMD_PROC_H_
#define __CMD_PROC_H_

/* Some defines */
/* Other defines should be return codes of the functions */
#define CMD_FOUND         0
#define CMD_ERROR_STRING -1
#define CMD_INVALID      -2
#define CS_ERROR         -3
#define STR_WRONG_FORMAT -4                  

#define MAX_CMDSTRING_SIZE 10 /* Maximum size of the command string */ 
#define SOF_SYM '#'	          /* Start of Frame Symbol */
#define EOF_SYM '!'           /* End of Frame Symbol */

/* Function prototypes */
int cmdProcessor(void);
int newCmdChar(unsigned char newChar);
void resetCmdString(void);

#endif
