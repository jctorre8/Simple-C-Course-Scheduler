////////////////////////////////////////////////////////////////////////////////
//INCLUDES
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

////////////////////////////////////////////////////////////////////////////////
//MACROS: CONSTANTS

//Enum to denominate the subject of the classes
typedef enum {SER=0, EGR=1, CSE=2, EEE=3} Subject;


////////////////////////////////////////////////////////////////////////////////
//DATA STRUCTURES

//Course structure
typedef struct {
   Subject  subject;
   int 		creditHours;
   int 		number;
   char  	teacher[1024];
} Course;


////////////////////////////////////////////////////////////////////////////////
//GLOBAL VARIABLES

//place to store course information
Course* CourseCollection = NULL;

//number of courses in the collection. also the index of the next empty element.
int courseCount = 0;

//Number of credit hours a student is currently taking
int creditHours = 0;

////////////////////////////////////////////////////////////////////////////////
//FORWARD DECLARATIONS
void add_class();
void drop_class();
void schedule_print();
void branching(char option);

//main entry point. Starts the program by displaying a welcome and beginning an 
//input loop that displays a menu and processes user input. Pressing q quits.      
int main() {
	char input_buffer;

	printf("\n\nWelcome to ASU Class Schedule\n");

	//menu and input loop
	do {
		printf("\nMenu Options\n");
		printf("------------------------------------------------------\n");
		printf("a: Add a class\n");
		printf("d: Drop a class\n");
		printf("s: Show your classes\n");
		printf("q: Quit\n");
		printf("\nTotal Credits: %d\n\n", creditHours);
		printf("Please enter a choice ---> ");

		scanf(" %c", &input_buffer);

		branching(input_buffer);
	} while (input_buffer != 'q');

	return 0;
}

void add_class(){
	//Variable declaration
	int subject, number, credits;
	char name[1024];

	//User input
	printf("\nWhat is the subject (SER=0, EGR=1, CSE=2, EEE=3)?\n");
	scanf(" %d", &subject);
	printf("\nWhat is the number (e.g. 240)?\n");
	scanf(" %d", &number);
	printf("\nHow many credits is the class (e.g. 3)?\n");
	scanf(" %d", &credits);
	printf("\nWhat is the name of the teacher?\n");
	scanf(" %s", &name);

	//Add new course to the array
	CourseCollection = realloc(CourseCollection, sizeof(Course)*(courseCount+1));
	CourseCollection[courseCount].subject = subject;
	CourseCollection[courseCount].number = number;
	CourseCollection[courseCount].creditHours = credits;
	strcpy(CourseCollection[courseCount].teacher, name);

	courseCount++;
	creditHours += credits;
}

void drop_class(){
	//Variable declaration
	int number, found = 0, i, j=0;

	//User input
	printf("What is the number of the class(e.g. 240)?\n");
	scanf(" %d", &number);

	//Create a temporary memory allocation to transfer data
	Course * temp = (Course *) malloc(sizeof(Course)*(courseCount-1));

	//Copy each class structure to the new space
	for(i = 0; i < courseCount; i++){

		//If there is a course that needs to be removed then skip the copy
		if(CourseCollection[i].number == number && found == 0){
			creditHours -= CourseCollection[i].creditHours;
			found = 1;
			continue;
		}

		//User entered course not in course list
		if(i == j  && i == (courseCount-1)){
			printf("\nCourse not found!!!\n");
			return;
		}
		memcpy((temp+j), (CourseCollection+i), sizeof(Course));
		j++;
	}
	//Free previous course allocation and copy the pointer
	free(CourseCollection);
	CourseCollection = temp;
	courseCount--;
}


void schedule_print(){

	int i;
	printf("\nClass Schedule:\n");
	printf("------------------------------------------------------\n");
		for(i = 0; i < courseCount; i++){
		switch (CourseCollection[i].subject) {
			case 0:
				printf("SER");
				break;

			case 1:
				printf("EGR");
				break;

			case 2:
				printf("CSE");
				break;

			case 3:
				printf("EEE");
				break;
		}

		printf("%d ", CourseCollection[i].number);
		printf("%d ", CourseCollection[i].creditHours);
		printf("%s \n", CourseCollection[i].teacher);
	}
}

//takes a character representing an inputs menu choice and calls the appropriate
//function to fulfill that choice. display an error message if the character is
//not recognized.
void branching(char option) {
	switch (option) {
	case 'a':
		add_class();
		break;

	case 'd':
		drop_class();
		break;

	case 's':
		schedule_print();
		break;

	case 'q':
		free(CourseCollection);
		break;

	default:
		printf("\nError: Invalid Input.  Please try again...");
		break;
	}
}
