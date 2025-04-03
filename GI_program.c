/*
 * GI_program.c
 *
 * Created: 2/15/2025 12:54:54 PM
 *  Author: Ahmad abdullatif
 */
#include "std_types.h"
#include "bit_math.h"
#include "GI_interface.h"
#include "GI_registers.h"


void GI_voidEnableGeneralInterrupt (void){
	SET_BIT(SREG_REGISTER,GI_I_BIT);
}
void GI_voidDisableGeneralInterrupt(void){
	CLEAR_BIT(SREG_REGISTER,GI_I_BIT);
}