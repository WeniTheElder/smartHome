/*
 * Timer0_config.h
 *
 * Created: 2/17/2025 1:34:26 PM
 *  Author: Ahmad abdullatif
 */


#ifndef TIMER0_CONFIG_H_
#define TIMER0_CONFIG_H_
/*
prescaler_value      = 64
tick_time            = prescaller_value/F_CPU
Normal mode:
overflow_time        = (prescaler_value/F_CPU) * 256
number_of_over_flows = desierd_time/overflow_time
preload_value        = (1-fraction)*256

CTC mode:
--you try to set OCR to a value that makes the number of overflows(interrupts) integer value--

number_of_overflows  = desired_time/((OCR0+1)*tick_time)
*/
#define TIMER0_NUMBER_OF_OVERFLOWS 250   //for 100 ms in CTC mode    
#define TIMER0_PRELOAD_VALUE       0      
#define TIMER0_OCR0_VALUE          249




#endif /* TIMER0_CONFIG_H_ */
