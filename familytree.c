#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <ctype.h>

#define SIZE 20

typedef struct node *pnode;

struct node {
	int id;						// Unique id
    char name[SIZE];			// Name
    char lifeStatus;			// 'A' (Alive) or 'D' (Dead)
    int age; 					// Age
    pnode parents[2]; 			// pointers to parents
    pnode partner; 				// pointer to partner
    pnode children[5]; 			// pointers to children
    pnode prev;
    pnode next;
};

pnode head;

pnode get_node(int id, char *name, int age, char lifeStatus);

void insert(int id, char *name, int age, char lifeStatus);

void deleteNode(char *name);

void printList();

void setParent(char *parentName, char *childName);

void setPartner(char *personName, char *partnerName);

void changeProfile(char *name, int age, char lifeStatus);

int printPerson(char *name);

void printParents(char *name);

void printChildren(char *name);

void printSiblings(char *name);

void printPartner(char *name);

void saveTree(char *fileName);

void loadTree(char *fileName);

pnode findNode(int id);

int lastId;

int main(){

    head = NULL;
	lastId = 0;
    int choice;

    do {
		printf(
				"=== Family Tree Menu ===\n\n"
				"Please select from the options below:\n\n"
				"(0) Exit.\n"
				"(1) Add a new person.\n"
				"(2) Set a person as a parent of another person.\n"
				"(3) Set a person as the partner of another person.\n"
				"(4) Print all the relatives of a person.\n"
				"(5) Change the profile of a person.\n"
				"(6) Remove a person.\n"
				"(7) Print all the persons.\n"
				"(8) Save the tree into a file.\n"
				"(9) Load the tree from a file.\n");
		while (1){
			printf("Enter your selection: ");
			scanf("%i", &choice);
			if ((choice < 0) || (choice > 9)){
				printf("Invalid selection!\n");
				continue;
			}
			else
				break;
		}

		char name[21];
		int  age;
		char lifeStatus;
		char parentName[21];
		char childName[21];
		char personName[21];
		char partnerName[21];
		switch (choice) {

		case 1:
			printf( "Enter the name of the person: " );
			scanf( "%20s", name);
			printf( "Enter the age of the person: " );
			scanf( "%d", &age);
			fflush(stdin);
			printf( "Enter the life status of the person (Alive/Dead): " );
			scanf( "%c", &lifeStatus);
			lastId++;
		    insert(lastId, name, age, lifeStatus);
			break;
		case 2:
			printf( "Enter the name of the parent: " );
			scanf( "%20s", parentName);
			printf( "Enter the name of the child: " );
			scanf( "%20s", childName);
			setParent(parentName, childName);
			break;
		case 3:
			printf( "Enter the name of the person: " );
			scanf( "%20s", personName);
			printf( "Enter the name of the partner: " );
			scanf( "%20s", partnerName);
			setPartner(personName, partnerName);
			break;
		case 4:
			printf( "Enter the name of the person: " );
			scanf( "%20s", personName);
			if (printPerson(personName)){
				printParents(personName);
				printChildren(personName);
				printSiblings(personName);
				printPartner(personName);
			}
			break;
		case 5:
			printf( "Enter the name of the person: " );
			scanf( "%20s", name);
			printf( "Enter the age of the person: " );
			scanf( "%d", &age);
			fflush(stdin);
			printf( "Enter the life status of the person (Alive/Dead): " );
			scanf( "%c", &lifeStatus);
		    changeProfile(name, age, lifeStatus);
			break;
		case 6:
			printf( "Enter the name of the person: " );
			scanf( "%20s", name);
			deleteNode(name);
			break;
		case 7:
			printList();
			break;
		case 8:
			printf( "Enter the file name: " );
			scanf( "%20s", name);
		    saveTree(name);
			break;
		case 9:
			printf( "Enter the file name: " );
			scanf( "%20s", name);
		    loadTree(name);
			break;
		}

    } while (choice != 0);

	return 0;
}

pnode get_node(int id, char *name, int age, char lifeStatus){

	pnode new_node = (pnode) malloc(sizeof(struct node));
	new_node->id = id;
	new_node->age = age;
	new_node->lifeStatus = toupper(lifeStatus);
	strcpy(new_node->name, name);
	new_node->prev = NULL;
	new_node->next = NULL;
	return new_node;
}

void insert(int id, char *name, int age, char lifeStatus){

	pnode new_node = get_node(id, name, age, lifeStatus);
	if(head == NULL){
		head = new_node;
		return;
	}

	pnode temp = head;
	pnode temp_prev = NULL;
	while(temp != NULL && strcmp(name, temp->name) > 0){
		temp_prev = temp;
		temp = temp->next;
	}

	if (temp == NULL) {
		new_node->next = NULL;
		new_node->prev = temp_prev;
		temp_prev->next = new_node;
	}
	else {
		if(strcmp(name, temp->name) <= 0){
			new_node->next = temp;
			if(strcmp(name, head->name) <= 0){
				head = new_node;
			} else {
				new_node->prev = temp->prev;
				temp->prev->next = new_node;
			}
			temp->prev = new_node;
		} else {
			new_node->prev = temp;
			temp->next = new_node;
		}
	}
}

void changeProfile(char *name, int age, char lifeStatus){

	pnode temp = head;
	while(temp != NULL){
		if(strcmp(name, temp->name) == 0){
			temp->age = age;
			temp->lifeStatus = toupper(lifeStatus);
			return;
		}
		else
			temp = temp->next;
	}
	puts("Person not found!");
}

void deleteNode(char *name){

	pnode temp = head;
	while(temp != NULL){
		if(strcmp(name, temp->name) == 0){
			if (temp == head) {
				if (temp->parents[0] != NULL) {
					for (int i=0; i<5; i++) {
						if (strcmp(temp->parents[0]->children[i]->name, temp->name) == 0) {
							temp->parents[0]->children[i] = NULL;
							break;
						}
					}
				}
				if (temp->parents[1] != NULL) {
					for (int i=0; i<5; i++) {
						if (strcmp(temp->parents[1]->children[i]->name, temp->name) == 0) {
							temp->parents[1]->children[i] = NULL;
							break;
						}
					}
				}
				if (temp->partner != NULL) {
					temp->partner->partner = NULL;
				}
				for (int i=0; i<5; i++) {
					if (temp->children[i] != NULL) {
						for (int j=0; j<2; j++) {
							if (strcmp(temp->children[i]->parents[j]->name, temp->name) == 0) {
								temp->children[i]->parents[j] = NULL;
								break;
							}
						}
					}
				}
				head = head->next;
				free(temp);
				return;
			}
			else {
				pnode del = temp;
				temp->prev->next = temp->next;
				if (temp->next != NULL)
					temp->next->prev = temp->prev;
				free(del);
				return;
			}
		}
		else
			temp = temp->next;
	}
	puts("Person not found!");
}

void setParent(char *parentName, char *childName) {

	pnode child = head;
	while(child != NULL){
		if(strcmp(childName, child->name) == 0){
			break;
		}
		else
			child = child->next;
	}

	if (child != NULL) {
		pnode parent = head;
		while(parent != NULL) {

			if(strcmp(parentName, parent->name) == 0){
				if (child->parents[0] == NULL) {
					child->parents[0] = parent;
					puts("Parent set.");
				}
				else if (child->parents[1] == NULL) {
					child->parents[1] = parent;
					puts("Parent set.");
				}
				else {
					puts("The second person has already two parents.");
					return;
				}
				int i = 0;
				for (; i < 5; i++) {
					if (parent->children[i] == NULL)
						break;
				}
				if (i < 5) {
					parent->children[i] = child;
					puts("Child set.");
				}
				else
					puts("No more children.");
				return;
			}
			else
				parent = parent->next;
		}
		puts("Parent not found!");
	}
	else
		puts("Person not found!");
}

void setPartner(char *personName, char *partnerName){

	pnode person = head;
	while(person != NULL){
		if(strcmp(personName, person->name) == 0){
			break;
		}
		else
			person = person->next;
	}

	if (person != NULL) {
		if (person->partner != NULL) {
			puts("This person already has a partner.");
			return;
		}
		pnode partner = head;
		while(partner != NULL) {
			if(strcmp(partnerName, partner->name) == 0){
				if (partner->partner == NULL) {
					person->partner = partner;
					partner->partner = person;
					puts("Partners are set.");
					return;
				}
				else {
					puts("The second person already has a partner.");
					return;
				}
			}
			else
				partner = partner->next;
		}
		if (partner == NULL)
			puts("Second person not found!");
	}
	else
		puts("Person not found!");
}

int printPerson(char *name){
	pnode temp = head;
	while(temp != NULL){
		if(strcmp(name, temp->name) == 0) {
			puts("====================");
			printf("Name: %s, Age: %d, Life Status: %s\n", temp->name, temp->age, temp->lifeStatus == 'A'?"Alive":"Dead");
			puts("====================");
			return 1;
		}
		temp = temp->next;
	}
	puts("Person not found!");
	return 0;
}

void printList(){
	pnode temp = head;
	puts("List of the persons:");
	puts("====================");
	while(temp != NULL){
		printf("Name: %s, Age: %d, Life Status: %s\n", temp->name, temp->age, temp->lifeStatus == 'A'?"Alive":"Dead");
		temp = temp->next;
	}
	puts("====================");
}

void printParents(char *name){
	pnode temp = head;
	while(temp != NULL){
		if(strcmp(name, temp->name) == 0){
			if (temp->parents[0] != NULL) {
				printf("First Parent of %s is %s\n", name, temp->parents[0]->name);
				if (temp->parents[1] != NULL)
					printf("Second Parent of %s is %s\n", name, temp->parents[1]->name);
			}
			else
				puts("This person has no parents.");
			return;
		}
		else
			temp = temp->next;
	}
	puts("Person not found!");
}

void printSiblings(char *name){
	pnode temp = head;
	while(temp != NULL){
		if(strcmp(name, temp->name) == 0){
			if (temp->parents[0] != NULL) {
				int i = 0;
				int notYet = 1;
				for (; i < 5; i++) {
					if (temp->parents[0]->children[i] != NULL && strcmp(name, temp->parents[0]->children[i]->name) != 0) {
						if (notYet) {
							printf("Siblings of %s are:\n", name);
							notYet = 0;
						}
						printf("%s\n", temp->parents[0]->children[i]->name);
					}
				}
			}
			else
				puts("This person has no sibling.");
			return;
		}
		else
			temp = temp->next;
	}
	puts("Person not found!");
}

void printPartner(char *name){
	pnode temp = head;
	while(temp != NULL){
		if(strcmp(name, temp->name) == 0){
			if (temp->partner != NULL) {
				printf("Partner of %s is %s\n", name, temp->partner->name);
			}
			else
				puts("This person has no partner.");
			return;
		}
		else
			temp = temp->next;
	}
	puts("Person not found!");
}

void printChildren(char *name){
	pnode temp = head;
	while(temp != NULL){
		if(strcmp(name, temp->name) == 0){
			if (temp->children[0] != NULL) {
				printf("Children of %s are:\n", name);
				int i = 0;
				for (; i < 5; i++) {
					if (temp->children[i] != NULL) {
						printf("%s\n", temp->children[i]->name);
					}
				}
			}
			else
				puts("This person has no children.");
			return;
		}
		else
			temp = temp->next;
	}
	puts("Person not found!");
}

void saveTree(char *fileName) {

	FILE *cfPtr;

	if ((cfPtr = fopen(fileName, "w")) == NULL) {
		puts("File could not be opened.");
	}
	else {
		puts("Data is writing to the file...");
		pnode temp = head;

		while(temp != NULL){
			int parent1 = temp->parents[0] == NULL ? 0 : temp->parents[0]->id;
			int parent2 = temp->parents[1] == NULL ? 0 : temp->parents[1]->id;
			int partner = temp->partner == NULL ? 0 : temp->partner->id;
			int c[5];
			for (int i=0; i<5;i++) {
				c[i] = temp->children[i] == NULL ? 0 : temp->children[i]->id;
			}
			fprintf(cfPtr, "%d %20s %d %c %d %d %d %d %d %d %d %d\n", temp->id, temp->name, temp->age, temp->lifeStatus,
					parent1, parent2, partner, c[0],c[1],c[2],c[3],c[4]);
			temp = temp->next;
		}
		fclose(cfPtr); // fclose closes the file
		puts("Data has been successfully written to the file.");
	}
}

void loadTree(char *fileName) {

	FILE *cfPtr;

	if ((cfPtr = fopen(fileName, "r")) == NULL) {
		puts("File could not be opened.");
	}
	else {
		puts("Data is loading from the file...");
		pnode temp = head;
		while(temp != NULL){
			head = head->next;
			free(temp);
			temp = head;
		}

		int id;
		char name[21];
		int age;
		char lifeStatus;
		char line[100];
		lastId = 0;
		while(fgets(line, sizeof line, cfPtr)){
			sscanf(line,"%d %20s %d %c",&id, name, &age, &lifeStatus);
		    insert(id, name, age, lifeStatus);
		    if (id > lastId)
		    	lastId = id;
		}

		rewind(cfPtr);

		while(fgets(line, sizeof line, cfPtr)){
			int parent1=0;
			int parent2=0;
			int partner=0;
			int c[5]={0};

			sscanf(line,"%d %20s %d %c %d %d %d %d %d %d %d %d\n",&id, name, &age, &lifeStatus,
					&parent1, &parent2, &partner, &c[0],&c[1],&c[2],&c[3],&c[4]);
			pnode n = findNode(id);

			if ((parent1 != 0)) {
				pnode p = findNode(parent1);
				if (p != NULL)

					setParent(p->name,n->name);
			}
			if ((parent2 != 0)) {
				pnode p = findNode(parent2);
				if (p != NULL)
					setParent(p->name,n->name);
			}
			if ((partner != 0)) {
				pnode p = findNode(partner);
				if (p != NULL)
					setPartner(n->name,p->name);
			}
		}

		fclose(cfPtr); // fclose closes the file
		puts("Data has been successfully loaded to the file.");
	}
}

pnode findNode(int id) {

	pnode temp = head;

	while(temp != NULL){
		if (temp->id == id)
			return temp;
		temp = temp->next;
	}

	return NULL;
}