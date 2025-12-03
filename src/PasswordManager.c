#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Configuration
#define DATA_FILE "../data/passwords.dat"
#define MASTER_PASSWORD "1234" // Change this to your desired password
#define ENCRYPTION_KEY 'X'     // Simple XOR Key

// Data Structure
struct Credential {
    char website[50];
    char username[50];
    char password[50];
};

// --- Helper Functions ---

// Simple XOR encryption/decryption (Symmetric)
void toggleEncryption(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = str[i] ^ ENCRYPTION_KEY;
    }
}

// Clears input buffer to prevent skipping inputs
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Remove newline character from fgets
void stripNewline(char *str) {
    str[strcspn(str, "\n")] = 0;
}

// --- Core Features ---

void addPassword() {
    struct Credential cred;
    FILE *fp = fopen(DATA_FILE, "ab"); // Append binary mode

    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("\n--- Add New Password ---\n");
    
    printf("Website: ");
    fgets(cred.website, 50, stdin);
    stripNewline(cred.website);

    printf("Username: ");
    fgets(cred.username, 50, stdin);
    stripNewline(cred.username);

    printf("Password: ");
    fgets(cred.password, 50, stdin);
    stripNewline(cred.password);

    // Encrypt before writing to file
    toggleEncryption(cred.website);
    toggleEncryption(cred.username);
    toggleEncryption(cred.password);

    fwrite(&cred, sizeof(struct Credential), 1, fp);
    fclose(fp);
    printf("Password saved successfully!\n");
}

void searchPassword() {
    struct Credential cred;
    char searchKey[50];
    int found = 0;
    
    FILE *fp = fopen(DATA_FILE, "rb"); // Read binary mode

    if (fp == NULL) {
        printf("No passwords found. Add one first!\n");
        return;
    }

    printf("\nEnter Website to search (or type 'ALL' to see all): ");
    fgets(searchKey, 50, stdin);
    stripNewline(searchKey);

    printf("\n%-20s %-20s %-20s\n", "Website", "Username", "Password");
    printf("------------------------------------------------------------\n");

    while (fread(&cred, sizeof(struct Credential), 1, fp)) {
        // Decrypt temp variables to check logic
        toggleEncryption(cred.website);
        toggleEncryption(cred.username);
        toggleEncryption(cred.password);

        if (strcmp(searchKey, "ALL") == 0 || strstr(cred.website, searchKey) != NULL) {
            printf("%-20s %-20s %-20s\n", cred.website, cred.username, cred.password);
            found = 1;
        }
    }

    if (!found) {
        printf("No matching records found.\n");
    }

    fclose(fp);
}

// --- Main Execution ---

int main() {
    char inputPass[50];
    int choice;

    printf("=== SECURE PASSWORD MANAGER ===\n");
    printf("Enter Master Password: ");
    scanf("%s", inputPass);
    clearInputBuffer(); // Consume the Enter key

    if (strcmp(inputPass, MASTER_PASSWORD) != 0) {
        printf("Access Denied!\n");
        return 1;
    }

    while (1) {
        printf("\n1. Add Credential\n");
        printf("2. Search/View Credentials\n");
        printf("3. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);
        clearInputBuffer(); 

        switch (choice) {
            case 1:
                addPassword();
                break;
            case 2:
                searchPassword();
                break;
            case 3:
                printf("Exiting... Stay Safe!\n");
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}