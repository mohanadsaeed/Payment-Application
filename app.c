/******************************************************************************
*
* Module: Application
*
* File Name: app.c
*
* Description: Source file for Application Module
*
* Author: Mohanad K. Saeed
******************************************************************************/
#include "app.h"
void appStart(void) {
	/*Declaring Card Data*/
	ST_cardData_t cardData;
	EN_cardError_t cardError;
	/*Declaring Terminal Data*/
	ST_terminalData_t terminalData;
	EN_terminalError_t terminalError;
	EN_serverError_t serverError;
	EN_transState_t transactionError;

	do
	{
		cardError = getCardHolderName(&cardData);
		if (cardError == WRONG_NAME) {
			printf("Wrong Card Name \n \n");
		}
	} while (cardError != OK_CARD);

	do
	{
		cardError = getCardExpiryDate(&cardData);
		if (cardError == WRONG_EXP_DATE) {
			printf("Wrong Expiration Date \n \n");
		}
	} while (cardError != OK_CARD);

	do
	{
		cardError = getCardPAN(&cardData);
		if (cardError == WRONG_PAN) {
			printf("Wrong Primary Account Number \n \n");
		}
	} while (cardError != OK_CARD);

	do {
		terminalError = getTransactionDate(&terminalData);
		if (terminalError == WRONG_DATE) {
			printf("Wrong Transaction Date \n \n");
		}
	} while (terminalError != OK);

	terminalError = isCardExpired(&cardData, &terminalData);
	if (terminalError == EXPIRED_CARD) {
		printf("Declined Process (Expired Card)\n");
		return 0;
	}

	do {
		terminalError = getTransactionAmount(&terminalData);
		if (terminalError == INVALID_AMOUNT) {
			printf("Invalid Amount");
		}
	} while (terminalError != OK);

	do {
		terminalError = setMaxAmount(&terminalData);
		if (terminalError == INVALID_MAX_AMOUNT) {
			printf("Invalid Maximum Amount");
		}
	} while (terminalError != OK);

	terminalError = isBelowMaxAmount(&terminalData);
	if (terminalError == EXCEED_MAX_AMOUNT) {
		printf("Declined Process (Amount Exceeding Limit \n)");
		return 0;
	}

	serverError = isValidAccount(&cardData);
	if (serverError == ACCOUNT_NOT_FOUND) {
		printf("Declined Process (Invalid Account)");
		return 0;
	}

	serverError = isAmountAvailable(&terminalData);
	if (serverError == LOW_BALANCE) {
		printf("Declined Process (Insuffecient Funds)");
		return 0;
	}

	ST_transaction_t transactionData = {
		cardData,
		terminalData
	};

	printf("Your Current Balance is: \n%f \n", g_accountsDataBase[index].balance);
	transactionError = recieveTransactionData(&transactionData);
	if (transactionError == APPROVED) {
		printf("Approved Transaction, and your new balance is: \n%f \n", g_accountsDataBase[index].balance);
	}

	return 0;
}

	