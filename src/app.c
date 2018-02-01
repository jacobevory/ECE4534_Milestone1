/*******************************************************************************
  MPLAB Harmony Application Source File
  
  Company:
    Microchip Technology Inc.
  
  File Name:
    app.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It 
    implements the logic of the application's state machine and it may call 
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2014 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *******************************************************************************/
// DOM-IGNORE-END


// *****************************************************************************
// *****************************************************************************
// Section: Included Files 
// *****************************************************************************
// *****************************************************************************

#include "app.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_Initialize function.
    
    Application strings and buffers are be defined outside this structure.
*/

//APP_DATA appData;

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

/* TODO:  Add any necessary callback functions.
*/

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************


/* TODO:  Add any necessary local functions.
*/


// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
 
    appData.state = APP_STATE_INIT;
    
    
    /* TODO: Initialize your application's state machine and other
     * parameters.
     */
}


/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */int i = 0;
void APP_Tasks ( void ){
    while(1){
        switch (appData.state) {
            case APP_STATE_INIT:
            {
                DRV_TMR0_Start();
                PLIB_USART_Enable(USART_ID_1);
                appData.ADCRdy = false;
                DRV_ADC_Open();
                sensorq_create();
                dbgOutputVal(appData.sensorRead);
                appData.adcIndex = 0;
                PLIB_ADC_SampleAutoStartEnable(ADC_ID_1);
                appData.state = APP_STATE_FIRST;
                break;
            }
            case APP_STATE_FIRST:
            {
                i++;
                if(i > 127) i = 0;
                appData.sensorVal = 0;
                appData.sensorRead = sensorq_receive()*128/1024;
                dbgOutputLoc(i);
                appData.sensorVal += appData.sensorRead;
                dbgOutputVal(appData.sensorRead);
                appData.state = APP_STATE_SECOND;
                break;
            }
            case APP_STATE_SECOND:
            {
                appData.sensorRead = sensorq_receive()*128/1024;
                //dbgOutputLoc(LOC_2);
                appData.sensorVal += appData.sensorRead;
                dbgOutputVal(appData.sensorRead);
                appData.state = APP_STATE_THIRD; 
                break;
            }
            case APP_STATE_THIRD:
            {
                appData.sensorRead = sensorq_receive()*128/1024;
                //dbgOutputLoc(LOC_3);
                appData.sensorVal += appData.sensorRead;
                dbgOutputVal(appData.sensorRead);
                appData.state = APP_STATE_FOURTH; 
                break;
            }
            case APP_STATE_FOURTH:
            {
                appData.sensorRead = sensorq_receive()*128/1024;
                //dbgOutputLoc(LOC_4);
                appData.sensorVal += appData.sensorRead;
                dbgOutputVal(appData.sensorRead);
                appData.sensorVal = appData.sensorVal / ADC_NUM_SAMPLE_PER_AVERAGE;
                dbgUARTVal(appData.sensorVal);
                dbgUARTVal('c');
                dbgUARTVal('m');
                appData.adcIndex = 0;
                PLIB_ADC_SampleAutoStartEnable(ADC_ID_1);
                appData.state = APP_STATE_FIRST;
                break;
            }
            default:
            {
                ohNoh();
                break;
            }
        }
    }
}

 
void APP_ADC_Average ( void )
{
    int i;
 
    appData.ADCRdy = true;
    appData.sensorVal = 0;
    /* Must read results before clearing persistent interrupt flag. */
    for (i=0; i < ADC_NUM_SAMPLE_PER_AVERAGE; i++)
    {
        appData.sensorVal += PLIB_ADC_ResultGetByIndex(ADC_ID_1, i);
    }
 
    appData.sensorVal = appData.sensorVal / ADC_NUM_SAMPLE_PER_AVERAGE ;
    dbgOutputVal(appData.sensorVal/1024*128);
    /* If the "Stop Conversion on the First ADC Interrupt?" box in MHC is checked,
       the Hardware will disable auto-sampling when the interrupt condition
       occurs (after obtaining the 16th result). Auto-sampling needs to be
       re-enabled every ADC interrupt. */
    PLIB_ADC_SampleAutoStartEnable(ADC_ID_1); 
}


/*******************************************************************************
 End of File
 */
