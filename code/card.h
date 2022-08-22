/******************************************************************************
*
* Module: Card
*
* File Name: card.h
*
* Description: Header file for Card Module
*
* Author: Mohanad K. Saeed
******************************************************************************/

#ifndef CARD_H
#define CARD_H

/* Standard Types */
#include "std_types.h"

/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/

/* Type definition for Card Possible Errors used by the Card Module */
typedef enum EN_cardError_t {
	OK_CARD,WRONG_NAME,WRONG_EXP_DATE,WRONG_PAN
}EN_cardError_t;

/* Type definition for Card Data used by the Card Module */
typedef struct ST_cardData_t {
	uint8_t cardHolderName[25];
	uint8_t primaryAccountNumber[20];
	uint8_t cardExpirationDate[6];
}ST_cardData_t;

/* -----------------------------------------------------------------------------
 *                      Functions Prototypes                                   *
 ------------------------------------------------------------------------------*/

/* Function for getting the Card Holder Name */
EN_cardError_t getCardHolderName(ST_cardData_t* cardData); 

/* Function for getting the Card Expiry Date */
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData);

/* Function for getting the Primary Account Number */
EN_cardError_t getCardPAN(ST_cardData_t* cardData);

#endif