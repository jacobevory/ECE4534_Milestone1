/* ************************************************************************** */
/* Milestone 1 Debug Source */
/* ************************************************************************** */

#include "debug.h"

// Section: Interface Functions                                               */

void dbgOutputVal(uint32_t outVal){
    if (outVal < 0 || outVal > 127) tx = 127;
    else tx = (outVal  + (toggle * 128)) & 0x000000ff;
    writeIntTo1((uint8_t)tx);
    if(!toggle) toggle = true;
    else if (toggle) toggle = false;
}

void dbgUARTVal(unsigned char outVal){
    int track = 0;
    while(track<1){
        if (!DRV_USART0_TransmitBufferIsFull()){
            DRV_USART0_WriteByte(outVal);
            track++;
        }
    }
    DRV_USART0_WriteByte("\n");
}

void dbgOutputLoc(uint32_t outVal){
    if (outVal < 0 || outVal > 127) tx1 = 127;
    else tx1 = (outVal  + (toggle1 * 128)) & 0x000000ff;
    writeIntTo2((uint8_t)tx1);
    if(!toggle1) toggle1 = true;
    else if (toggle1) toggle1 = false;
}

void ohNoh(void){
    dbgOutputLoc(LOC_127);
    writeIntTo1(0);
    writeIntTo2(0);
    dbgUARTVal('E');
    dbgUARTVal('r');
    dbgUARTVal('r');
    dbgUARTVal('o');
    dbgUARTVal('r');
}

void writeIntTo1(uint8_t value){
    bool array[8];
    int i = 0;
    for (i = 0; i < 8; ++i) {
    array[i] = (value >> i) & 1;
    }
    PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_0, array[0]);
    PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_1, array[1]);
    PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_4, array[2]);
    PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_5, array[3]);
    PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_9, array[4]);
    PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_13, array[5]);
    PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_13, array[6]);
    PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_7, array[7]);
}

void writeIntTo2(uint8_t value){
    bool array[8];
    int i = 0;
    for (i = 0; i < 8; ++i) {
    array[i] = (value >> i) & 1;
    }
    PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_1, array[0]);
    PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_0, array[1]);
    PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_6, array[2]);
    PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_7, array[3]);
    PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_14, array[4]);
    PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_12, array[5]);
    PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_13, array[6]);
    PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_9, array[7]);
}
/* *****************************************************************************
 End of File
 */
