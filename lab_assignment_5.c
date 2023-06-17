#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	char letter;
	struct node* next;
} node;

// Returns number of nodes in the linkedList.
int length(node* head)
{
	int count = 0;
	node* current = head;
	while (current != NULL) {
		count++;
		current = current->next;
	}
	return count;
}

// parses the string in the linkedList
//  if the linked list is head -> |a|->|b|->|c|
//  then toCString function wil return "abc"
char* toCString(node* head)
{
	int len = length(head);
	char* str = (char*)malloc((len + 1) * sizeof(char)); // Adds 1 for NULL
	int i = 0;
	node* current = head;
	while (current != NULL) {
		str[i] = current->letter;
		current = current->next;
		i++;
	}
	str[i] = '\0'; //Terminates NULL
	return str;
}

// inserts character to the linkedlist
// f the linked list is head -> |a|->|b|->|c|
// then insertChar(&head, 'x') will update the linked list as foolows:
// head -> |a|->|b|->|c|->|x|
void insertChar(node** pHead, char c)
{
	node* newNode = (node*)malloc(sizeof(node));
	newNode->letter = c;
	newNode->next = NULL;

	if (*pHead == NULL) {
		*pHead = newNode; //If list is empty then make newNode head.
	} else {
		node* current = *pHead;
		while (current->next != NULL) {
			current = current->next; //Goes through list until last node
		}
		current->next = newNode; //Appends newNode at the end
	}
}

// deletes all nodes in the linkedList.
void deleteList(node** pHead)
{
	node* current = *pHead;
	node* next;
	while (current != NULL) { //Goes through each node to free memory allocated
		next = current->next;
		free(current);
		current = next;
	}
	*pHead = NULL;
}

int main(void)
{
	int i, strLen, numInputs;
	node* head = NULL;
	char* str;
	char c;
	FILE* inFile = fopen("input.txt","r");

	fscanf(inFile, " %d\n", &numInputs);
	
	while (numInputs-- > 0)
	{
		fscanf(inFile, " %d\n", &strLen);
		for (i = 0; i < strLen; i++)
		{
			fscanf(inFile," %c", &c);
			insertChar(&head, c);
		}

		str = toCString(head);
		printf("String is : %s\n", str);

		free(str);
		deleteList(&head);

		if (head != NULL)
		{
			printf("deleteList is not correct!");
			break;
		}
	}

	fclose(inFile);
}