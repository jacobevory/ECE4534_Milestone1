#include "FreeRTOS.h"
#include "queue.h"

typedef enum
{
	/* Application's state machine's initial state. */
	SENSOR_QUEUE_STATE_INIT=0,

	/* TODO: Define states used by the application state machine. */

} SENSOR_QUEUE_STATES;

typedef struct
{
    /* The application's current state */
    SENSOR_QUEUE_STATES state;

    /* TODO: Define any additional data used by the application. */


} SENSOR_QUEUE_DATA;

uint32_t val;
uint32_t rval;

void sensorq_create( void );
void sensorq_send(uint32_t inVal); 
uint32_t sensorq_receive( void );
