/*
 * final_project.c
 *
 * Created: 3/13/2025 1:21:44 AM
 * Author : Ahmad Abdullatif
 */ 
#include "std_types.h"
#include "smart_home_system_interface.h"


int main(void)
{
	SmartHome_voidInitSystem();
    while (1) 
    {
		SmartHome_voidTerminalLoginMainMenu();
	}
}



