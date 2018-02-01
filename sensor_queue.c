

#include "sensor_queue.h"
#include "debug.h"


#define QUEUE_SEND_FREQUENCY_MS         ( 200 / portTICK_PERIOD_MS )
#define QUEUE_LENGTH                    ( 1 )

QueueHandle_t xQueue;


void sensorq_create ( void ){
	 xQueue = xQueueCreate( 16, sizeof(uint32_t));
     if( xQueue == NULL )
    {
     dbgOutputVal(3);
    }
     val = -1;
}

void sensorq_send(uint32_t inVal){
	//sends data
   
     val = inVal;
     //dbgOutputVal(1);
	 xQueueSendToBackFromISR( xQueue, ( void * ) &val, (BaseType_t) 0);	
     
     //xQueueSendFromISR(xQueue, &val, true);
     //dbgOutputVal(2);


	
}

uint32_t sensorq_receive( void){
	
	if(xQueueReceive( xQueue, &rval, portMAX_DELAY )){
        return rval;
    }
    else{
        return -1;
    }
    return 1;
	
}

/*******************************************************************************
 End of File
 */
