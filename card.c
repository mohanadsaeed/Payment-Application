/******************************************************************************
*
* Module: Card
*
* File Name: card.c
*
* Description: Source file for Card Module
*
* Author: Mohanad K. Saeed
******************************************************************************/
#include "card.h"
#include <stdio.h>

/* ---------------------------------------------------------------------------
[FUNCTION NAME] : getCardExpiryDate
[DESCRIPTION]   : Function is responsible for asking for the card expiry date
				  and store it into card data. Card holder name is 24 character
				  string maximum and 20 minimum. If the card holer name is NULL,
				  less than 20 characters or more than 24 will return WRONG_NAME
				  error, else return OK
[Args]		    :
				in  -> pointer to structure:
					This argument is empty structure to store the card data.
[Return]	    :
				out -> EN_cardError_t:
					The possible card errors either OK or specific error
------------------------------------------------------------------------------*/
EN_cardError_t getCardHolderName(ST_cardData_t* cardData) {
	/*Temporary array to save the card holder's name to make some checks before 
	store it into card data*/
	uint8_t tempName[40] = {0}, cardNameSize, i;
	printf("Please, Enter the card holder's name: \n");
	gets(tempName);
	/*Loop to get the number of card name characters entered by the user and make
	sure that the card name is alphabets*/
	for (i = 0; tempName[i] != '\0'; i++){
		if (!((tempName[i] >= 'A' && tempName[i] <= 'Z') ||
			(tempName[i] >= 'a' && tempName[i] <= 'z') || (tempName[i]==' '))) {
			return WRONG_NAME;
		}
	}
	cardNameSize = i;
	//Check if the number of card name characters in the allowed limit
	if (cardNameSize < 20 || cardNameSize > 24) {
		return WRONG_NAME;
	}
	else {
		/*Copy the card holder's name from the temporary array to the card data
		and return OK*/
		for (i = 0; tempName[i] != '\0'; i++) {
			cardData->cardHolderName[i] = tempName[i];
		}
		cardData->cardHolderName[i] = '\0';
		return OK_CARD;
	}
};

/* ---------------------------------------------------------------------------
[FUNCTION NAME] : getCardExpiryDate
[DESCRIPTION]   : Function is responsible for asking for the card expiry date
				  and store it into card data. Card expiry date is 5 characters
				  string in the format "MM/YY", e.g "05/25"
[Args]		    :
				in  -> pointer to structure:
					This argument is empty structure to store the card data.
[Return]	    :
				out -> EN_cardError_t:
					The possible card errors either OK or specific error
------------------------------------------------------------------------------*/
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData) {
	/*Temporary array to save the card expiry date to make some checks before
	store it into card data*/
	uint8_t tempDate[10] = { 0 }, dateSize, i;
	printf("Please, Enter the card expiry date in the format MM/YY: \n");
	gets(tempDate);
	/*Loop to get the number of card expiry date characters entered by the user and 
	make sure that the card expiry date format is correct*/
	for (i = 0; tempDate[i] != '\0'; i++) {
		if (!((tempDate[i] >= '0' && tempDate[i] <= '9') || tempDate[i]=='/')) {
			return WRONG_EXP_DATE;
		}
	}
	dateSize = i;
	if (dateSize != 5 || tempDate[2] != '/') {
		return WRONG_EXP_DATE;
	}
	else {
		/*Copy the card expiry date from the temporary array to the card data
		and return OK*/
		for (i = 0; tempDate[i] != '\0'; i++) {
			cardData->cardExpirationDate[i] = tempDate[i];
		}
		cardData->cardExpirationDate[i] = '\0';
		return OK_CARD;
	}
};

/* ---------------------------------------------------------------------------
[FUNCTION NAME] : getCardPAN
[DESCRIPTION]   : Function is responsible for asking for the card's Primary 
				  Account Number and store it into card data. PAN is 20 characters
				  alphanumeric only string 19 maximum and 16 minimum. If the 
				  PAN is NULL, less than 16 or more than 19 characters, will 
				  return WRONG_PAN error, else return OK.
[Args]		    :
				in  -> pointer to structure:
					This argument is empty structure to store the card data.
[Return]	    :
				out -> EN_cardError_t:
					The possible card errors either OK or specific error
------------------------------------------------------------------------------*/
EN_cardError_t getCardPAN(ST_cardData_t* cardData) {
	/*Temporary array to save the card primary account number to make some 
	checks before store it into card data*/
	uint8_t tempPan[25] = { 0 }, panSize, i;
	printf("Please, Enter the card Primary Account Number: \n");
	gets(tempPan);
	/*Loop to get the number of card PAN alphanumerics entered by the user and
	make sure that the PAN is 20 characters alphanumeric only string 19 maximum 
	and 16 minimum. */
	for (i = 0; tempPan[i] != '\0'; i++) {};
	panSize = i;
	//Check if the number of card PAN characters in the allowed limit
	if (panSize < 16 || panSize > 19) {
		return WRONG_PAN;
	}
	else {
		/*Copy the card PAN from the temporary array to the card data
		and return OK*/
		for (i = 0; tempPan[i] != '\0'; i++) {
			cardData->primaryAccountNumber[i] = tempPan[i];
		}
		cardData->primaryAccountNumber[i] = '\0';
		return OK_CARD;
	}
};