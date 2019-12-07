/*
 * UART1.c
 *
 *  Created on: Dec 3, 2019
 *      Author: AWhit
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "UART1.h"
#include "UART0.h"


static char buffer[MAX_PACKET_SIZE];
static unsigned char data;
static short receiving = FALSE;
static unsigned short BufferIndex = 0;
static short DLE_flg = FALSE;
int checksum;

void setData(unsigned char in){
    data = in;
}

/*
 * Sends a Char to UART1 output port
 */
void writeCharToTrain(unsigned char data){
    /*  Checks if UART FIFO Full    */
    while(UART1_FR_R & UART_FR_TXFF);
    UART1_DR_R = data;
}

/*
 * Prepares and sends a frame to the Train
 * [ STX | Packets | Chksum | ETX ]
 */

void writeStringToTrain(char *index, short length){
    unsigned short i;
    unsigned char checksum = 0;
    /*  Start Transmission  */
    writeCharToTrain(STX);

    for(i = 0 ; i < length ; i++){
        if(*index == DLE || *index == STX || *index == ETX){
            writeCharToTrain(DLE);
        }
        writeCharToTrain(*index);
        checksum += *index;
        index++;
    }
    writeCharToTrain(~checksum);
    writeCharToTrain(ETX);
}


void UART1_Init(void)
{
    volatile int wait;

    /* Initialize UART0 */
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCUART_GPIOA;   // Enable Clock Gating for UART0
    SYSCTL_RCGCUART_R |= SYSCTL_RCGCGPIO_UART0;   // Enable Clock Gating for PORTA
    wait = 0; // give time for the clocks to activate

    UART1_CTL_R &= ~UART_CTL_UARTEN;        // Disable the UART
    wait = 0;   // wait required before accessing the UART config regs

    // Setup the BAUD rate
    UART1_IBRD_R = 8;   // IBRD = int(16,000,000 / (16 * 115,200)) = 8.680555555555556
    UART1_FBRD_R = 44;  // FBRD = int(.680555555555556 * 64 + 0.5) = 44.05555555555556

    UART1_LCRH_R = (UART_LCRH_WLEN_8);  // WLEN: 8, no parity, one stop bit, without FIFOs)

    GPIO_PORTA_AFSEL_R = 0x3;        // Enable Receive and Transmit on PA1-0
    GPIO_PORTA_PCTL_R = (0x01) | ((0x01) << 4);         // Enable UART RX/TX pins on PA1-0
    GPIO_PORTA_DEN_R = EN_DIG_PA0 | EN_DIG_PA1;        // Enable Digital I/O on PA1-0

    UART1_CTL_R = UART_CTL_UARTEN;        // Enable the UART
    wait = 0; // wait; give UART time to enable itself.
}


void UART1_IntEnable(unsigned long flags)
{
    /* Set specified bits for interrupt */
    UART1_IM_R |= flags;
}




/*  Adds the UART1 receiving data to the buffer */
unsigned short enqueueData(){
    if(BufferIndex < MAX_PACKET_SIZE){
        buffer[BufferIndex] = data;
        BufferIndex++;
        checksum +=data;
        return TRUE;
    }
    return FALSE;
}

void data_in(){
    /*  Start Receiving */
    if(data == STX && receiving == FALSE){
        receiving = TRUE;
        BufferIndex = 0;
        checksum = 0;
    }
    else if(receiving && DLE_flg == FALSE){
        switch(data){
            case DLE:
            /*  get next character  */
                DLE_flg = TRUE;
                break;
            case ETX:
                /*  Check checksum and send up  */
                receiving = FALSE;
                if(checksum == -1){
                    /*  Send up Packet  */
                    BufferIndex--;

                }
                break;
            default:
                /*  add the data to the buffer  */
                if(enqueueData() == FALSE){
                    /*  Something broke, discard   */
                    receiving = FALSE;
                }
                break;
        }
    }
    else if(DLE_flg == TRUE && receiving){
        /*  DLE flag is true, enqueue next data regardless  */
        if(enqueueData() == FALSE){
            /*  Something broke, discard   */
            receiving = FALSE;
        }
    }
}

void UART1_IntHandler(void)
{
/*
 * Simplified UART ISR - handles receive and xmit interrupts
 * Application signaled when data received
 */
    if (UART1_MIS_R & UART_INT_RX)
    {
        /* RECV done - clear interrupt and make char available to application */
        UART1_ICR_R |= UART_INT_RX;
        data = UART1_DR_R;
        data_in();
    }

    if (UART1_MIS_R & UART_INT_TX)
    {
        /* XMIT done - clear interrupt */
        UART1_ICR_R |= UART_INT_TX;
        /*  Here we write to the train  */

    }
}
