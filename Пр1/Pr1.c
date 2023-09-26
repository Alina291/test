// C program for the implementation of
// menu driven program for student
// management system
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Variable to keep track of
// number of students
int i = 0;

// Structure to store the student
struct sinfo {
 char fname[50];
 char lname[50];
 int roll;
 
} st[55];

// Function to add the student
void add_student()
{

 printf("Add the Students Details\n");
 printf("-------------------------\n");
 printf("Enter the first "
  "name of student\n");
 scanf("%s", st[i].fname);
 printf("Enter the last name"
  " of student\n");
 scanf("%s", st[i].lname);
 printf("Enter the age\n");
 scanf("%d", &st[i].roll);
 
 i = i + 1;
}

// Function to find the student
// by the age
void find_rl()
{
 int x;
 printf("Enter the age"
  " of the student\n");
 scanf("%d", &x);
 int j;
 for (j = 1; j <= i; j++) {
  if (x == st[i].roll) {
   printf(
    "The Students Details are\n");
   printf(
    "The First name is %s\n",
    st[i].fname);
   printf(
    "The Last name is %s\n",
    st[i].lname);
   
  break;
 }
}
}

// Function to find the student
// by the first name
void find_fn()
{
 char a[50];
 printf("Enter the First Name"
  " of the student\n");
 scanf("%s", a);
 int c = 0;
 int j;
 for (j = 1; j <= i; j++) {
  if (!strcmp(st[j].fname, a)) {

   printf(
    "The Students Details are\n");
   printf(
    "The First name is %s\n",
    st[i].fname);
   printf(
    "The Last name is %s\n",
    st[i].lname);
   printf(
    "The age is %d\n ",
    st[i].roll);
  
   c = 1;
  }
  else
   printf(
    "The First Name not Found\n");
 }
}


// Function to print the total
// number of students
void tot_s()
{
 printf("The total number of"
  " Student is %d\n",
  i);
 printf("\n you can have a "
  "max of 50 students\n");
 printf("you can have %d "
  "more students\n",
  50 - i);
}
void printf_s()
{
    printf("First name    Last Name   Age\n");
    int j;
    for(j = 0; j < i; j++){
    printf("%5s %10s %10d \n",st[j].fname, st[j].lname,st[j].roll);
    }
}
// Driver code
int  main()

{
 int choice, count;
 while (1) {
  printf("The Task that you "
   "want to perform\n");
  printf("1. Add the Student Details\n");
  printf("2. Find the Student "
   "Details by Age\n");
  printf("3. Find the Student "
   "Details by First Name\n");
  
  printf("4. Find the Total number"
   " of Students\n");
   printf("5. Check all students\n");
 
  printf("6. To Exit\n");
  printf("Enter your choice to "
   "find the task\n");
  scanf("%d", &choice);
  switch (choice) {
  case 1:
   add_student();
   break;
  case 2:
   find_rl();
   break;
  case 3:
   find_fn();
   break;
  
  case 4:
   tot_s();
   break;
   case 5:
   printf_s();
   break;
  
  case 6:
   exit(0);
   break;
  }
 }
}
