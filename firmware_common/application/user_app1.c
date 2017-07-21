/**********************************************************************************************************************
File: user_app1.c                                                                

----------------------------------------------------------------------------------------------------------------------
To start a new task using this user_app1 as a template:
 1. Copy both user_app1.c and user_app1.h to the Application directory
 2. Rename the files yournewtaskname.c and yournewtaskname.h
 3. Add yournewtaskname.c and yournewtaskname.h to the Application Include and Source groups in the IAR project
 4. Use ctrl-h (make sure "Match Case" is checked) to find and replace all instances of "user_app1" with "yournewtaskname"
 5. Use ctrl-h to find and replace all instances of "UserApp1" with "YourNewTaskName"
 6. Use ctrl-h to find and replace all instances of "USER_APP1" with "YOUR_NEW_TASK_NAME"
 7. Add a call to YourNewTaskNameInitialize() in the init section of main
 8. Add a call to YourNewTaskNameRunActiveState() in the Super Loop section of main
 9. Update yournewtaskname.h per the instructions at the top of yournewtaskname.h
10. Delete this text (between the dashed lines) and update the Description below to describe your task
----------------------------------------------------------------------------------------------------------------------

Description:
This is a user_app1.c file template 

------------------------------------------------------------------------------------------------------------------------
API:

Public functions:


Protected System functions:
void UserApp1Initialize(void)
Runs required initialzation for the task.  Should only be called once in main init section.

void UserApp1RunActiveState(void)
Runs current task state.  Should only be called once in main loop.


**********************************************************************************************************************/

#include "configuration.h"

/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_UserApp1"
***********************************************************************************************************************/
/* New variables */
volatile u32 G_u32UserApp1Flags;  /* Global state flags*/
LedCommandType aeDemoList[]=
    {
            {RED,1000,TRUE,LED_PWM_100},
            {RED,6000,FALSE,LED_PWM_0},
            {GREEN,3000,TRUE,LED_PWM_100},
            {GREEN,9000,FALSE,LED_PWM_0},
            {BLUE,2000,TRUE,LED_PWM_100},
            {BLUE,4000,FALSE,LED_PWM_0},
            {YELLOW,4000,TRUE,LED_PWM_100},
            {YELLOW,8000,FALSE,LED_PWM_0},
            {CYAN,6000,TRUE,LED_PWM_100},
            {CYAN,8000,FALSE,LED_PWM_0},
            {ORANGE,5000,TRUE,LED_PWM_100},
            {ORANGE,7000,FALSE,LED_PWM_0},
            {WHITE,7000,TRUE,LED_PWM_100},
            {WHITE,9000,FALSE,LED_PWM_0},
            {PURPLE,5000,TRUE,LED_PWM_100},
            {PURPLE,8000,FALSE,LED_PWM_0}
    };
LedCommandType aeUserList[]=
    {
            {RED,1000,TRUE,LED_PWM_100},
            {RED,6000,FALSE,LED_PWM_0},
            {ORANGE,5000,TRUE,LED_PWM_100},
            {ORANGE,7000,FALSE,LED_PWM_0},
            {WHITE,7000,TRUE,LED_PWM_100},
            {WHITE,9000,FALSE,LED_PWM_0},
            {PURPLE,5000,TRUE,LED_PWM_100},
            {PURPLE,8000,FALSE,LED_PWM_0}
    };








/*--------------------------------------------------------------------------------------------------------------------*/
/* Existing variables (defined in other files -- should all contain the "extern" keyword) */
extern volatile u32 G_u32SystemFlags;                  /* From main.c */
extern volatile u32 G_u32ApplicationFlags;             /* From main.c */

extern volatile u32 G_u32SystemTime1ms;                /* From board-specific source file */
extern volatile u32 G_u32SystemTime1s;                 /* From board-specific source file */


/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "UserApp1_" and be declared as static.
***********************************************************************************************************************/
static fnCode_type UserApp1_StateMachine;            /* The state machine function pointer */
static u32 UserApp1_u32Timeout;                      /* Timeout counter used across states */


/**********************************************************************************************************************
Function Definitions
**********************************************************************************************************************/

/*--------------------------------------------------------------------------------------------------------------------*/
/* Public functions                                                                                                   */
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
/* Protected functions                                                                                                */
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------
Function: UserApp1Initialize

Description:
Initializes the State Machine and its variables.

Requires:
  -

Promises:
  - 
*/
void UserApp1Initialize(void)
{
 LedOff(WHITE);
 LedOff(RED);
 LedOff(PURPLE);
 LedOff(ORANGE);
 LedOff(BLUE);
 LedOff(GREEN);
 LedOff(CYAN);
 LedOff(YELLOW);
 LCDCommand(LCD_CLEAR_CMD);   //Clear all the things on LCD.
 
 static u8 au8Message[]={'0'};  //The characters are empty in the middle.
 
 for(u8 i=0;i<16;i+=2)
 {
   LCDMessage(LINE1_START_ADDR+i,au8Message);
 }
 
   
 
 
    
 
 

  /* If good initialization, set state to Idle */
  if( 1 )
  {
    UserApp1_StateMachine = UserApp1SM_Idle;
  }
  else
  {
    /* The task isn't properly initialized, so shut it down and don't run */
    UserApp1_StateMachine = UserApp1SM_Error;
  }

} /* end UserApp1Initialize() */

  
/*----------------------------------------------------------------------------------------------------------------------
Function UserApp1RunActiveState()

Description:
Selects and runs one iteration of the current state in the state machine.
All state machines have a TOTAL of 1ms to execute, so on average n state machines
may take 1ms / n to execute.

Requires:
  - State machine function pointer points at current state

Promises:
  - Calls the function to pointed by the state machine function pointer
*/
void UserApp1RunActiveState(void)
{
  UserApp1_StateMachine();

} /* end UserApp1RunActiveState */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Private functions                                                                                                  */
/*--------------------------------------------------------------------------------------------------------------------*/


/**********************************************************************************************************************
State Machine Function Definitions
**********************************************************************************************************************/

/*-------------------------------------------------------------------------------------------------------------------*/
/* Wait for ??? */
static void UserApp1SM_Idle(void)
{   
   static u32 u32Time=0;
   static u16 u16Count=0;
   static u8 u8Counter[]={'0','0','0','0'};
   static u8 au8LedAddr[]={0,2,4,6,8,10,12,14};
   static u8 au8Input[]={1,2};
   static u8 u8CharNum;
   static u8 u8Index=0;
   
   //u8CharNum=DebugScanf(au8Input);
   
   if(WasButtonPressed(BUTTON0))
   {
     ButtonAcknowledge(BUTTON0);
     u8CharNum=1;
   }
   
   if(WasButtonPressed(BUTTON1))
   {
     ButtonAcknowledge(BUTTON1);
     u8CharNum=2;
   }
   

   u32Time++;
   u16Count++;
  
   if(u32Time==10000)       //When u32Time=10000, u32Time=0.
    {
        u32Time=0;
    }
   
   u8Counter[0]=0x30+u32Time/1000;
   u8Counter[1]=0x30+u32Time%1000/100; 
   u8Counter[2]=0x30+u32Time%100/10; 
   u8Counter[3]=0x30+u32Time%10; 
   
   if(u32Time%100 == 0)    //Display once every 100ms.
	{
        LCDMessage(LINE2_START_ADDR,u8Counter);
	}


   
   for(u8 j=0;j<16;j++)  //The LEDS are in prople order.
    {
        if(u32Time==aeDemoList[j].u32Time&&u8CharNum==1)
        {
            LedPWM(aeDemoList[j].eLed, aeDemoList[j].eCurrentRate);
            
            if(aeDemoList[j].bOn==TRUE)
            {
              LCDMessage(LINE1_START_ADDR+au8LedAddr[aeDemoList[j].eLed],"1");
            }
            
            if(aeDemoList[j].bOn==FALSE)
	  {
              LCDMessage(LINE1_START_ADDR+au8LedAddr[aeDemoList[j].eLed],"0");
	  }

        }
        
    }
   
   for(u8 k=0;k<200;k++)
   {
      if(u8Index<16)
   {
     u8Index++;
   }
   
     if(u32Time==aeUserList[u8Index].u32Time&&u8CharNum==2)
     {
       LedPWM(aeUserList[u8Index].eLed,aeUserList[u8Index].eCurrentRate);
       
       if(aeUserList[u8Index].bOn==TRUE)
       {
         LCDMessage(LINE1_START_ADDR+au8LedAddr[aeUserList[u8Index].eLed],"1");
       }
       
       if(aeUserList[u8Index].bOn==FALSE)
       {
         LCDMessage(LINE1_START_ADDR+au8LedAddr[aeUserList[u8Index].eLed],"0");
       }
     }
     u8Index=0; 
   }
   
 
   
    

   

}/* end Us*/

/*-------------------------------------------------------------------------------------------------------------------*/
/* Handle an error */
static void UserApp1SM_Error(void)          
{
  
} /* end UserApp1SM_Error() */



/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
