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



static unsigned char buffer[MAX_PACKET_SIZE];
unsigned char data;
static short receiving = FALSE;
static unsigned short BufferIndex = 0;

static


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

        /*  Start Receiving */
        if(data == STX && receiving == FALSE){
            receiving = TRUE;
            BufferIndex = 0;
        }
        else if(receiving){
            switch(data){
                case DLE:
                /*  get next character  */

                break;

                case ETX:
                /*  Check checksum and send up  */
                break;

                default:
                /*  increment length, keep rolling  */
                break;

            }
        }


    }

    if (UART1_MIS_R & UART_INT_TX)
    {
        /* XMIT done - clear interrupt */
        UART1_ICR_R |= UART_INT_TX;
    }
}
