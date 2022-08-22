/******************************************************************************
*
* Module: Terminal
*
* File Name: terminal.c
*
* Description: Source file for Terminal Module
*
* Author: Mohanad K. Saeed
******************************************************************************/
#include "terminal.h"
#include <stdio.h>
#include<time.h>

/* ---------------------------------------------------------------------------
[FUNCTION NAME] : getTransactionDate
[DESCRIPTION]   : Function is responsible for asking for the transaction data
				  and store it in terminal data. Transaction date is 10 characters 
				  string in the format DD/MM/YYYY, e.g 25/06/2022. If the transaction 
				  date is NULL, less than 10 characters or wrong format will return 
				  WRONG_DATE error, else return OK.
[Args]		    :
				in  -> pointer to structure:
					This argument is empty structure to store the terminal data.
[Return]	    :
				out -> EN_terminalError_t:
					The possible terminal errors either OK or specific error
------------------------------------------------------------------------------*/
EN_terminalError_t getTransactionDate(ST_terminalData_t* termData) {
	/*Temporary array to save the transaction date to make some checks before
	store it into card data*/
	uint8_t tempDate[20] = { 0 }, dateSize, i;
	printf("Please, Enter the transaction date in the format DD/MM/YYYY: \n");
	gets(tempDate);
	/*Loop to get the number of transaction date characters entered by the user and
	make sure that the transaction date format is correct*/
	for (i = 0; tempDate[i] != '\0'; i++) {
		if (!((tempDate[i] >= '0' && tempDate[i] <= '9') || tempDate[i] == '/')) {
			return WRONG_DATE;
		}
	}
	dateSize = i;
	if (dateSize != 10 || tempDate[2] != '/' || tempDate[5] != '/') {
		return WRONG_DATE;
	}
	else {
		/*Copy the transaction date from the temporary array to the terminal data
		and return OK*/
		for (i = 0; tempDate[i] != '\0'; i++) {
			termData->transactionDate[i] = tempDate[i];
		}
		termData->transactionDate[i] = '\0';
		return OK;
	}
}

/* ---------------------------------------------------------------------------
[FUNCTION NAME] : isCardExpired
[DESCRIPTION]   : Function is responsible for comparing the card expiry date 
				  with the transaction date. If the card expiration date is 
				  before the transaction date will return EXPIRED_CARD, 
				  else return OK. 
[Args]		    :
				in  -> pointer to structure:
					This argument is structure contains the card data.

				in  -> pointer to structure:
					This argument is structure contains the terminal data.
[Return]	    :
				out -> EN_terminalError_t:
					The possible terminal errors either OK or specific error
------------------------------------------------------------------------------*/
EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData) {
	/*To compare the transaction date and the card expiration date we need to compare first
	the second digit of the year the compare the first digit of the year then compare the
	second digit of month then compare the first digit of month to decide if the card is
	expired or not*/
	/*Transaction Date: DD/MM/YYYY -> 01/34/6789
	  Card Expiration Date: MM/YY -> 01/34 */
	if (cardData->cardExpirationDate[3] < termData->transactionDate[8]) {
		return EXPIRED_CARD;
	}
	else if (cardData->cardExpirationDate[3] == termData->transactionDate[8]) {
		if (cardData->cardExpirationDate[4] < termData->transactionDate[9]) {
			return EXPIRED_CARD;
		}
		else if (cardData->cardExpirationDate[4] == termData->transactionDate[9]) {
			if (cardData->cardExpirationDate[0] < termData->transactionDate[3]) {
				return EXPIRED_CARD;
			}
			else if (cardData->cardExpirationDate[0] == termData->transactionDate[3]) {
				if (cardData->cardExpirationDate[1] < termData->transactionDate[4]) {
					return EXPIRED_CARD;
				}
				else {
					return OK;
				}
			}
			else {
				return OK;
			}
		}
		else {
			return OK;
		}
	}
	else {
		return OK;
	}
}

/* ---------------------------------------------------------------------------
[FUNCTION NAME] : getTransactionAmount
[DESCRIPTION]   : Function is responsible for asking for the transaction amount 
				  and saves it into terminal data. If the transaction amount is 
				  less than or equal to 0 will return INVALID_AMOUNT, else 
				  return OK.
[Args]		    :
				in  -> pointer to structure:
					This argument is structure contains the terminal data.
[Return]	    :
				out -> EN_terminalError_t:
					The possible terminal errors either OK or specific error
------------------------------------------------------------------------------*/
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData) {
	float32_t tempAmount;
	printf("Please, Enter the transaction amount: \n");
	scanf("%f", &tempAmount);
	if (!(tempAmount > 0)) {
		return INVALID_AMOUNT;
	}
	else {
		termData->transAmount = tempAmount;
		return OK;
	}
}

/* ---------------------------------------------------------------------------
[FUNCTION NAME] : setMaxAmount
[DESCRIPTION]   : Function is responsible for setting the maximum allowed amount 
				  into terminal data. Transaction max amount is a float number.
				  If transaction max amount less than or equal to 0 will return 
				  INVALID_MAX_AMOUNT error, else return OK.
[Args]		    :
				in  -> pointer to structure:
					This argument is structure contains the terminal data.
[Return]	    :
				out -> EN_terminalError_t:
					The possible terminal errors either OK or specific error
------------------------------------------------------------------------------*/
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData) {
	float32_t tempMaxAmount;
	printf("Please, Enter the maximum transaction amount: \n");
	scanf("%f", &tempMaxAmount);
	if (!(tempMaxAmount > 0)) {
		return INVALID_MAX_AMOUNT;
	}
	else {
		termData->maxTransAmount = tempMaxAmount;
		return OK;
	}
}

/* ---------------------------------------------------------------------------
[FUNCTION NAME] : isBelowMaxAmount
[DESCRIPTION]   : Function is responsible for comparing the transaction amount 
				  with the terminal max amount. If the transaction amount is 
				  larger than the terminal max amount will return 
				  EXCEED_MAX_AMOUNT, else return OK.
[Args]		    :
				in  -> pointer to structure:
					This argument is structure contains the terminal data.
[Return]	    :
				out -> EN_terminalError_t:
					The possible terminal errors either OK or specific error
------------------------------------------------------------------------------*/
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData) {
	if (termData->transAmount > termData->maxTransAmount) {
		return EXCEED_MAX_AMOUNT;
	}
	else {
		return OK;
	}
}

