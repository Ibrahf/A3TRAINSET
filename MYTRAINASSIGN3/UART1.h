/*
 * UART1.h
 *
 *  Created on: Dec 3, 2019
 *      Author: AWhit
 */

#ifndef UART1_H_
#define UART1_H_

#define GPIO_PORTA_AFSEL_R  (*((volatile unsigned long *)0x40058420))   // GPIOA Alternate Function Select Register
#define GPIO_PORTA_DEN_R    (*((volatile unsigned long *)0x4005851C))   // GPIOA Digital Enable Register
#define GPIO_PORTA_PCTL_R   (*((volatile unsigned long *)0x4005852C))   // GPIOA Port Control Register
#define UART1_DR_R          (*((volatile unsigned long *)0x4000D000))   // UART0 Data Register  x
#define UART1_FR_R          (*((volatile unsigned long *)0x4000D018))   // UART0 Flag Register
#define UART1_IBRD_R        (*((volatile unsigned long *)0x4000D024))   // UART0 Integer Baud-Rate Divisor Register
#define UART1_FBRD_R        (*((volatile unsigned long *)0x4000D028))   // UART0 Fractional Baud-Rate Divisor Register
#define UART1_LCRH_R        (*((volatile unsigned long *)0x4000D02C))   // UART0 Line Control Register
#define UART1_CTL_R         (*((volatile unsigned long *)0x4000D030))   // UART0 Control Register
#define UART1_IFLS_R        (*((volatile unsigned long *)0x4000D034))   // UART0 Interrupt FIFO Level Select Register
#define UART1_IM_R          (*((volatile unsigned long *)0x4000D038))   // UART0 Interrupt Mask Register
#define UART1_MIS_R         (*((volatile unsigned long *)0x4000D040))   // UART0 Masked Interrupt Status Register
#define UART1_ICR_R         (*((volatile unsigned long *)0x4000D044))   // UART0 Interrupt Clear Register
#define UART1_CC_R          (*((volatile unsigned long *)0x4000DFC8))   // UART0 Clock Control Register
#define NVIC_EN1_R          (*((volatile unsigned long *)0xE000E104))   // Interrupt 32-54 Set Enable Register

#define MAX_PACKET_SIZE 8

#define STX     0x02
#define ETX     0x03
#define DLE     0x10

#define PHYS_OUT_MAILBOX    3
#define PHYS_IN_MAILBOX     4
/*  For test    */
void setData(unsigned char data);

#endif /* UART1_H_ */
