/******************************************************************************
*
* Module: Terminal
*
* File Name: terminal.h
*
* Description: Header file for Terminal Module
*
* Author: Mohanad K. Saeed
******************************************************************************/

#ifndef TERMINAL_H
#define TERMINAL_H

#include "std_types.h"
#include "card.h"
/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/
 /* Type definition for Terminal Data used by the Card Module */
typedef struct ST_terminalData_t
{
	float32_t transAmount;
	float32_t maxTransAmount;
	uint8_t transactionDate[11];
}ST_terminalData_t;

/* Type definition for terminal Possible Errors used by the Card Module */
typedef enum EN_terminalError_t
{
	OK, WRONG_DATE, EXPIRED_CARD, INVALID_CARD, INVALID_AMOUNT, EXCEED_MAX_AMOUNT, INVALID_MAX_AMOUNT
}EN_terminalError_t;

/* -----------------------------------------------------------------------------
 *                      Functions Prototypes                                   *
 ------------------------------------------------------------------------------*/
/*Function for asking for the transaction data and store it in terminal data*/
EN_terminalError_t getTransactionDate(ST_terminalData_t* termData);
/*Function for comparing the card expiry date with the transaction date*/
EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData);
/*Function for asks for the transaction amount and saves it into terminal data.*/
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData);
/*Function for comparing the transaction amount with the terminal max amount.*/
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData);
/*Function for seting the maximum allowed amount into terminal data.*/
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData);

#endif