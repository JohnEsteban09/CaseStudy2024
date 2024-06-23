// CASE STUDY - GROUP 2 - DEBUG AND OPTIMIZE THEN FINALIZE - NUMBER_2_LINKED_LIST

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <stdbool.h>


/* NOTES: 
    - Code's Latest Update: [06-23-2024, 3:13 PM] 
*/


// Define the Node structure for the linked list
typedef struct Node {
    int data;           // Data stored in the node
    struct Node* next;  // Pointer to the next node in the list
} Node;

// Initialize the head of the linked list to NULL
Node* head = NULL;      // Head pointer to the first node in the list


// Function Prototyping
char mainMenu();
void createLinkedList();
void displayLinkedList();
void insertNum();
void deleteNum();
void searchNum();
void clearBuffer();
void pause();

int main(){
    char choice; // Display the main menu and get the user's choice
    
    do {
        choice = mainMenu();

        switch (choice) {
            case 'A':
                if (head != NULL) {
                    printf("Linked List already exists.\n");
                } else {
                    createLinkedList();
                }
                break;
            case 'B':
                displayLinkedList();
                break;
            case 'C':
                insertNum();
                break;
            case 'D':
                deleteNum();
                break;
            case 'E':
                searchNum();
                break;
            case 'F':
                printf("[PROGRAM TERMINATED]\n");
                break;
        }
        pause(); // Pause the program until the user presses a key
        printf("\n----------------------------------------------\n");
    } while (choice != 'F'); // Repeat until the user chooses to exit

    return 0;
}

void clearBuffer() { // Function to clear the input buffer
    while (getchar() != '\n'); 
}

void pause() { // Function to pause the program until the user presses a key
    printf("\n[Press any key to continue...]");
    getch();
}

char mainMenu() {
    char choice;
    bool validChoice;

    do {
        system("cls");  // Clears the console
        printf("----------------------------------------------\n");
        printf("MAIN MENU\n");
        printf("----------------------------------------------\n");
        printf("A. Create a Linear Linked List\n");
        printf("B. Display a Linear Linked List\n");
        printf("C. Insert a number in the Linear Linked List\n");
        printf("D. Delete a number from the Linear Linked List\n");
        printf("E. Search a number\n");
        printf("F. Exit\n");
        printf("----------------------------------------------\n");

        printf("Enter choice:\t");
        scanf(" %c", &choice);  // the space before %c consumes any leftover whitespace characters
        clearBuffer();
        choice = toupper(choice); // Convert the choice to uppercase

        printf("----------------------------------------------\n");

        // Check if the choice is between 'A' and 'F'
        if (head == NULL && choice > 'A' && choice < 'F') {
            validChoice = false;
            printf("No linked list exists. Please create a linked list first.\n");
            pause();
        } else if (choice < 'A' || choice > 'F') {
            validChoice = false;
            printf("Invalid choice. (Enter a letter from A to F)\n");
            pause();
        } else {
            validChoice = true;
        }
    } while (!validChoice); // Repeat until a valid choice is entered

    return choice;
}


void createLinkedList() {
    int num;
    bool validInput;
    Node *current = NULL;

    system("cls");
    printf("----------------------------------------------------------------------\n");
    printf("CREATION - LINEAR LINKED LIST\n");
    printf("----------------------------------------------------------------------\n");
    printf("[Note]: Input any letter or symbol to stop inputting numbers.\n\n");
    printf("Enter number:\n");
    
    do {
        printf("> ");
        if (scanf(" %d", &num) == 1) { // Check if the input is a valid integer
            clearBuffer();
            validInput = true;

            Node *newNode = malloc(sizeof(Node)); // Allocate memory for a new node
            if (newNode == NULL) {
                printf("[Error]: Memory allocation failed!\n");
                exit(1);
            }
            newNode->data = num;
            newNode->next = NULL;

            if (head == NULL) {
                head = newNode;
            } else {
                Node *current = head, *prev = NULL;
                while (current != NULL && current->data < num) {
                    prev = current;
                    current = current->next;
                }
                if (prev == NULL) { // Insert at the beginning
                    newNode->next = head;
                    head = newNode;
                } else {
                    prev->next = newNode;
                    newNode->next = current;
                }
            }
        } else {
            clearBuffer();
            validInput = false;
            printf("\nInvalid choice. (Enter an integer)\n");
        }
    } while (validInput);

    printf("----------------------------------------------------------------------\n");
}


void displayLinkedList() {
    system("cls");
    printf("----------------------------------------------------------------------\n");
    printf("DISPLAY - LINEAR LINKED LIST\n");
    printf("----------------------------------------------------------------------\n");

    Node *temp = head;
    while (temp != NULL) {
        printf(">  %d", temp->data);
        temp = temp->next;
        if (temp != NULL)
            printf("\n");
    }

    printf("\n----------------------------------------------------------------------\n");
}


void insertNum() {
    int num;
    Node *newNode = NULL;
    char choice;

    system("cls");
    printf("----------------------------------------------------------------------\n");
    printf("NUMBER INSERTION - LINEAR LINKED LIST\n");
    printf("----------------------------------------------------------------------\n");

    do {
        printf("Enter a number to insert:  ");
        if (scanf(" %d", &num) == 1) {
            clearBuffer();

            newNode = malloc(sizeof(Node));
            if (newNode == NULL) {
                printf("[Error]: Memory allocation failed!\n");
                exit(1);
            }
            newNode->data = num;
            newNode->next = NULL;

            if (head == NULL) {
                head = newNode;
            } else {
                Node *current = head, *prev = NULL;
                while (current != NULL && current->data < num) {
                    prev = current;
                    current = current->next;
                }
                if (prev == NULL) { // Insert at the beginning
                    newNode->next = head;
                    head = newNode;
                } else {
                    prev->next = newNode;
                    newNode->next = current;
                }
            }
            printf("\nNumber inserted successfully.\n");
        } else {
            clearBuffer();
            printf("Wrong input!\n\n");
        }

        printf("Do you want to insert another number? (Y/N): ");
        scanf(" %c", &choice);
        clearBuffer();
        choice = toupper(choice);

        printf("----------------------------------------------------------------------\n");
    } while (choice == 'Y');
}


void deleteNum() {
    int num;
    Node *current;
    Node *previous;
    Node *temp;
    char choice;

    system("cls");
    printf("----------------------------------------------------------------------\n");
    printf("NUMBER DELETION - LINEAR LINKED LIST\n");
    printf("----------------------------------------------------------------------\n");

    if (head == NULL) {
        printf("Linked List is empty.\n");
        return;
    }

    do {
        printf("Enter the number to delete: ");
        if (scanf(" %d", &num) != 1) {
            clearBuffer();
            printf("Invalid input!\n");
            printf("\n----------------------------------------------------------------------\n");
            return;
        }
        clearBuffer();

        current = head;
        previous = NULL;
        bool found = false;

        while (current != NULL) {
            if (current->data == num) {
                found = true;
                if (previous == NULL) {
                    // Deleting the head node
                    temp = current;
                    head = head->next;
                    current = head;
                    free(temp);
                } else {
                    // Deleting a non-head node
                    temp = current;
                    previous->next = current->next;
                    current = current->next;
                    free(temp);
                }
            } else {
                previous = current;
                current = current->next;
            }
        }

        if (!found) {
            printf("\nNumber not found in the list.\n");
        } else {
            printf("\nAll occurrences of number %d deleted successfully.\n", num);
        }

        printf("Do you want to delete another number? (Y/N): ");
        scanf(" %c", &choice);
        clearBuffer();
        choice = toupper(choice);

        printf("----------------------------------------------------------------------\n");
    } while (choice == 'Y');
}


void searchNum() {
    int num;
    Node *current;
    bool found;
    char choice;
    
    system("cls");
    printf("----------------------------------------------------------------------\n");
    printf("NUMBER SEARCHER - LINEAR LINKED LIST\n");
    printf("----------------------------------------------------------------------\n");

    if (head == NULL) {
        printf("Linked List is empty.\n");
        printf("\n----------------------------------------------------------------------\n");
        return;
    }

    do {
        current = head;
        found = false;

        printf("Enter the number to search: ");
        if (scanf(" %d", &num) != 1) {
            clearBuffer();
            printf("\nInvalid input!\n");
            printf("\n----------------------------------------------------------------------\n");
            return;
        }
        clearBuffer();

        while (current != NULL) {
            if (current->data == num) {
                found = true;
                break;
            }
            current = current->next;
        }

        if (found) {
            printf("\nNumber %d found in the list.\n", num);
        } else {
            printf("\nNumber %d not found in the list.\n", num);
        }

        printf("Do you want to search for another number? (Y/N): ");
        scanf(" %c", &choice);
        clearBuffer();
        choice = toupper(choice);

        printf("----------------------------------------------------------------------\n");
    } while (choice == 'Y');
}