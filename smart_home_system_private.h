/*
 * smart_home_system_private.h
 *
 * Created: 3/13/2025 1:55:15 AM
 *  Author: Ahmad abdullatif
 */


#ifndef FINAL_PROJECT_PRIVATE_H_
#define FINAL_PROJECT_PRIVATE_H_

#define USER_ID_SIZE                 3   
#define USER_COUNTER_ADDRESSS        255
#define MAX_NUMBER_OF_USERS          50


void priv_voidAdminLogin           ();
void priv_voidAdminPage            ();
void priv_voidUserLogin            ();
void priv_voidAddUser              ();
void priv_voidCheckPassword        (u8* copy_u8UserId);
void priv_voidUserPage             ();
void priv_voidLockSystem           ();
void priv_voidDoorControl          ();
void priv_voidLightSystem          ();
void priv_voidInitLightSystem      ();
void priv_voidTempSensorSystem     ();
void priv_LCDcontrolMainTerminal   ();
void priv_voidLCDLightSystemControl();



#endif /* FINAL_PROJECT_PRIVATE_H_ */
