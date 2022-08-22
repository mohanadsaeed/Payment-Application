/******************************************************************************
*
* Module: Server
*
* File Name: server.c
*
* Description: Source file for Server Module
*
* Author: Mohanad K. Saeed
******************************************************************************/
#include "server.h"
#include "terminal.h"

/* ---------------------------------------------------------------------------
[FUNCTION NAME] : isValidAccount
[DESCRIPTION]   : This function will take card data and validate these data.
				  It checks if the PAN exists or not in the server's database.
				  If the PAN doesn't exist will return DECLINED_STOLEN_CARD, 
				  else will return OK

[Args]		    :
				in  -> pointer to structure:
					This argument is structure with the card data.
[Return]	    :
				out -> EN_serverError_t:
					The possible server errors either OK or specific error
------------------------------------------------------------------------------*/
EN_serverError_t isValidAccount(ST_cardData_t* cardData) {
	uint8_t i,j,matched=0;
	for (j = 0; (j < 20 && matched == 0); j++) {
		for (i = 0; cardData->primaryAccountNumber[i] != '\0'; i++) {
			if (cardData->primaryAccountNumber[i] == g_accountsDataBase[j].primaryAccountNumber[i]) {
				matched = 1;
			}
			else {
				matched = 0;
				break;
			}
		}
	}
	if (matched == 0) {
		return ACCOUNT_NOT_FOUND;
	}
	else {
		index = j-1;
		return OK_SERVER;
	}
}

/* ---------------------------------------------------------------------------
[FUNCTION NAME] : isAmountAvailable
[DESCRIPTION]   : This function will take terminal data and validate these data.
				  It checks if the transaction's amount is available or not. If 
				  the transaction amount is greater than the balance in the 
				  database will return LOW_BALANCE, else will return OK
[Args]		    :
				in  -> pointer to structure:
					This argument is structure with the terminal data.
[Return]	    :
				out -> EN_serverError_t:
					The possible server errors either OK or specific error
------------------------------------------------------------------------------*/
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData) {
	if (termData->transAmount > g_accountsDataBase[index].balance) {
		return LOW_BALANCE;
	}
	else {
		return OK_SERVER;
	}
}

/* ---------------------------------------------------------------------------
[FUNCTION NAME] : saveTransaction
[DESCRIPTION]   : This function will take all transaction data into the transactions 
				  database. It gives a sequence number to a transaction, this number 
				  is incremented once a transaction is processed into the server.
				  If saves any type of transaction, APPROVED or DECLINED, with the 
				  specific reason for declining/transaction state.If transaction 
				  can't be saved will return SAVING_FAILED, else will return OK
[Args]		    :
				in  -> pointer to structure:
					This argument is structure with the transaction data.
[Return]	    :
				out -> EN_serverError_t:
					The possible server errors
------------------------------------------------------------------------------*/
EN_serverError_t saveTransaction(ST_transaction_t* transData) {
	static uint8_t transactionNumber=0;
	transData->transactionSequenceNumber = transactionNumber;
	memcpy(g_transactionDataBase[transactionNumber], transData, sizeof(*transData));
	transactionNumber++;
	return OK_SERVER;
}



/* ---------------------------------------------------------------------------
[FUNCTION NAME] : recieveTransactionData
[DESCRIPTION]   : This function will take all transaction data and validate 
				  its data. It checks the account details and amount availability. 
				  If the account does not exist return DECLINED_STOLEN_CARD, 
				  if the amount is not available will return DECLINED_INSUFFECIENT_FUND, 
				  if a transaction can't be saved will return INTERNAL_SERVER_ERROR 
				  and will not save the transaction, else returns APPROVED. 
				  It will update the database with the new balance.

[Args]		    :
				in  -> pointer to structure:
					This argument is structure with the transaction data.
[Return]	    :
				out -> EN_transState_t:
					The possible transaction states
------------------------------------------------------------------------------*/
EN_transState_t recieveTransactionData(ST_transaction_t* transData) {
	if (isValidAccount(&transData->cardHolderData) == ACCOUNT_NOT_FOUND) {
		transData->transState = DECLINED_STOLEN_CARD;
		return DECLINED_STOLEN_CARD;
	}
	else if (isAmountAvailable(&transData->terminalData) == LOW_BALANCE) {
		transData->transState = DECLINED_INSUFFECIENT_FUND;
		return DECLINED_INSUFFECIENT_FUND;
	}
	else if (saveTransaction(&transData) == SAVING_FAILED) {
		return INTERNAL_SERVER_ERROR;
	}
	else {
		g_accountsDataBase[index].balance -= transData->terminalData.transAmount;
		return APPROVED;
	}
}
