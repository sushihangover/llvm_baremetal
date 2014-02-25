/**
 ******************************************************************************
 * @file      semihost_cmd.s
 * @author    Coocox
 * @version   V1.0
 * @date      09/10/2011
 * @brief     Semihost command support.
 *
 *******************************************************************************
 */


.text
.global SH_DoCommand
.global HardFault_Handler
.code 16
.syntax unified
.type SH_DoCommand, function
.type HardFault_Handler, function


/**************************************************************************//**
  * @brief  prototype: int SH_DoCommand(int n32In_R0, int n32In_R1, int *pn32Out_R0)
  *
  * @param  n32In_R0	R0
  * @param  n32In_R1    R1
  * @param  pn32Out_R0  R2
  *
  * @retval None
  *****************************************************************************/
SH_DoCommand:
    BKPT 0xAB                 		/* Wait ICE or HardFault */
                              		/* ICE will step over BKPT directly */
                              		/* HardFault will step BKPT and the next line */

    B SH_ICE

SH_HardFault:                 		/* Captured by HardFault */
    MOVS   R0, #0             		/* Set return value to 0 */
    BX LR                         	/* Return */

SH_ICE:                           	/* Captured by ICE */
                                  	/* Save return value */
    CMP R2, #0
    BEQ SH_End
    STR R0, [R2]                  	/* Save the return value to *pn32Out_R0 */
SH_End:
    MOVS R0, #1                   	/* Set return value to 1 */
	BX LR                         	/* Return */

/**************************************************************************//**
  * @brief  HardFault Handler
  *
  * @param  None.
  *
  * Skip the semihost command in free run mode.
  *
  * @retval None
  *****************************************************************************/
HardFault_Handler:
	LDR    R0, [R13, #24]         	/* Get previous PC */
	LDRH   R1, [R0]               	/* Get instruction */
	LDR    R2, =0xBEAB            	/* The sepcial BKPT instruction */
	CMP    R1, R2                 	/* Test if the instruction at previous PC is BKPT */
	BNE    HardFault_Handler_Ret  	/* Not BKPT */

	ADDS   R0, #4                 	/* Skip BKPT and next line */
	STR    R0, [R13, #24]         	/* Save previous PC */

	BX     LR

HardFault_Handler_Ret:
	B      .


.end

