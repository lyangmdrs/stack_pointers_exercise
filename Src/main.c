/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#include <stdint.h>

/*
 * The goal of this exercise is to get 1 KB of STACK memory space
 * and separate it in two spaces, each one with 512 B. The first
 * space will be pointed by MSP and the second will be pointed by
 * PSP.
 *
 * As such, when the processor is on Handler Mode, the first portion
 * will be used as stack memory.
 *
 * By consequence, when the processor is on Thread Mode, the second
 * portion will be used as stack memory.
 *
 */

__attribute__((naked)) void change_sp_to_psp(void)
{
	// Using Equal Assembler Directives to define macros compliant with assembly statements

	__asm volatile (".equ S_RAM, 0x20000000");				// Initial RAM address
	__asm volatile (".equ RAM_SZ, (128 * 1024)");			// RAM Size = 128 KB
	__asm volatile (".equ E_RAM, ( (S_RAM) + (RAM_SZ) )");	// Final RAM address

	__asm volatile (".equ S_STACK, E_RAM");					// Stack starts at the end of RAM

	__asm volatile (".equ S_MSP_STACK, S_STACK");			// MSP space starts with Stack
	__asm volatile (".equ E_MSP_STACK, ( S_STACK + 512 )");	// MSP occupies the first 512 B of Stack

	__asm volatile (".equ S_PSP_STACK, E_MSP_STACK");		// PSP space starts at the end of MSP space


	__asm volatile ("LDR R0, =S_PSP_STACK"); 	// Loads PSP start address to R0 register
	__asm volatile ("MSR PSP, R0");				// Loads the content of R0 to PSP register
	__asm volatile ("MOV R0, #0X02");			// Writes the value to set SPSEL bit from CONTROL in R0
	__asm volatile ("MSR CONTROL, R0");			// Sets SPSEL to 1
}

void generate_exception(void)
{
	__asm volatile ("SVC #0X5");				// Uses SVC with any value from 0 to 255 to trigger an exception
}

int main(void)
{
    /* Loop forever */
	for(;;);
}

void SVC_Handler(void)
{
	// TODO: Print something here with SWV
}