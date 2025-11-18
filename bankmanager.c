#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct account {
    int accNo;
    char name[50];
    float balance;
};

// SAARE FUNCTIONS 
void createAccount();
void deposit();
void withdrawMoney();
void checkBalance();
void displayAll();

int main() {
    int choice;

    while (1) {     // INFINTTE LOOP MENU DISPLAY KARNE KE LIYE 
        printf("\n===== BANK ACCOUNT MANAGEMENT SYSTEM =====\n");
        printf("1. Create New Account\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. Check Balance\n");
        printf("5. Display All Accounts\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: createAccount(); break;
            case 2: deposit(); break;
            case 3: withdrawMoney(); break;
            case 4: checkBalance(); break;
            case 5: displayAll(); break;
            case 6: exit(0);
            default: printf("Invalid Choice! Try again.\n");
        }
    }
    return 0;
}


// NAYA ACCOUNT BANANE KE LIYE 

void createAccount() {
    struct account acc;
    FILE *fp = fopen("bank.txt", "a");

    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("\nEnter Account Number: ");
    scanf("%d", &acc.accNo);

    printf("Enter Name: ");
    scanf("%s", acc.name);

    printf("Enter Initial Balance: ");
    scanf("%f", &acc.balance);

    fprintf(fp, "%d %s %.2f\n", acc.accNo, acc.name, acc.balance);

    fclose(fp);
    printf("Account Created Successfully!\n");
}


// DEPOSIT WALA CODE

void deposit() {
    int accNo;
    float amount;
    struct account acc;
    int found = 0;

    FILE *fp = fopen("bank.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (fp == NULL || temp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("\nEnter Account Number: ");
    scanf("%d", &accNo);

    printf("Enter Amount to Deposit: ");
    scanf("%f", &amount);

    while (fscanf(fp, "%d %s %f", &acc.accNo, acc.name, &acc.balance) != EOF) {
        if (acc.accNo == accNo) {
            acc.balance += amount;
            found = 1;
            printf("Amount Deposited Successfully!\n");
        }
        fprintf(temp, "%d %s %.2f\n", acc.accNo, acc.name, acc.balance);
    }

    fclose(fp);
    fclose(temp);

    // FILE UPDATE KIYA 
    remove("bank.txt");
    rename("temp.txt", "bank.txt");

    if (!found) {
        printf("Account Not Found!\n");
    }
}


// WITHDRAW MONEY WALA CODE

void withdrawMoney() {
    int accNo;
    float amount;
    struct account acc;
    int found = 0;

    FILE *fp = fopen("bank.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (fp == NULL || temp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("\nEnter Account Number: ");
    scanf("%d", &accNo);

    printf("Enter Amount to Withdraw: ");
    scanf("%f", &amount);

    while (fscanf(fp, "%d %s %f", &acc.accNo, acc.name, &acc.balance) != EOF) {
        if (acc.accNo == accNo) {
            if (amount > acc.balance) {
                printf("Insufficient Balance!\n");
            } else {
                acc.balance -= amount;
                printf("Withdrawal Successful!\n");
            }
            found = 1;
        }
        fprintf(temp, "%d %s %.2f\n", acc.accNo, acc.name, acc.balance);
    }

    fclose(fp);
    fclose(temp);

    remove("bank.txt");
    rename("temp.txt", "bank.txt");

    if (!found) {
        printf("Account Not Found!\n");
    }
}


// BALANCE CHECK KRNE KE LIYE 

void checkBalance() {
    int accNo;
    struct account acc;
    int found = 0;

    FILE *fp = fopen("bank.txt", "r");

    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("\nEnter Account Number: ");
    scanf("%d", &accNo);

    while (fscanf(fp, "%d %s %f", &acc.accNo, acc.name, &acc.balance) != EOF) {
        if (acc.accNo == accNo) {
            printf("\n----- ACCOUNT DETAILS -----\n");
            printf("Account Number: %d\n", acc.accNo);
            printf("Name: %s\n", acc.name);
            printf("Balance: %.2f\n", acc.balance);
            found = 1;
            break;
        }
    }

    fclose(fp);

    if (!found) {
        printf("Account Not Found!\n");
    }
}


// SAARE ACCOUNTS DIKAHANE KE LIYE 

void displayAll() {
    struct account acc;
    FILE *fp = fopen("bank.txt", "r");

    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    printf("\n===== ALL ACCOUNTS =====\n");

    while (fscanf(fp, "%d %s %f", &acc.accNo, acc.name, &acc.balance) != EOF) {
        printf("\nAccount Number: %d\n", acc.accNo);
        printf("Name: %s\n", acc.name);
        printf("Balance: %.2f\n", acc.balance);
    }

    fclose(fp);


    return 0;


    // END OF PROJECT ......
}
