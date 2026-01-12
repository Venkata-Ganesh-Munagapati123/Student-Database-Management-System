#include<stdio.h>
#include<stdlib.h>
#include<string.h>
// for linked list
struct Student {
int roll;
char name[50];
float marks;
struct Student *next;
};
// for file storage
struct StudentFile {
int roll;
char name[50];
float marks;
};
struct Student *head=NULL;
void saveToFile(struct Student *);
void deleteFromFile(int roll);
void insertStudent()
{
struct Student *newNode;
newNode=(struct Student *)malloc(sizeof(struct Student));
if(newNode==NULL)
{
printf("Memory allocation failed\n");
return;
}
printf("Enter student roll nummber:");
scanf("%d",&newNode->roll);
printf("Enter student name:");
scanf("%s",newNode->name);
printf("Enter the marks:");
scanf("%f",&newNode->marks);
newNode->next=head;
head=newNode;
// for saving 
saveToFile(newNode);
printf("\n student data inserted sucessfully\n");
}
void displayStudents()
{
struct Student *temp;
if(head==NULL)
{
printf("No student recors found\n");
return;
}
temp=head;
printf("student Records:\n");
while(temp!=NULL)
{
printf("Roll:%d\n",temp->roll);
printf("Name:%s\n",temp->name);
printf("Marks:%f\n",temp->marks);
temp=temp->next;
}
}
void searchStudent()
{
struct Student *temp;
int roll,found=0;
if(temp->roll==roll)
{
printf("Database is empty");
return;
}
printf("enter the roll number to serach:");
scanf("%d",&roll);
temp=head;
while(temp!=NULL)
{
if(temp->roll==roll)
{
printf("Student found:\n");
printf("Roll:%d\n",temp->roll);
printf("Name:%s\n",temp->name);
printf("Marks:%.2f",temp->marks);
found=1;
break;
}
temp=temp->next;
}
if(!found)
{
printf("\nStudent data not found\n");
}
}
void deleteStudent()
{
struct Student *temp,*prev;
int roll;
if(head==NULL)
{
printf("Database is Empty\n");
return;
}
printf("Enter roll number to be deleted:");
scanf("%d",&roll);
if(head->roll==roll)
{
temp=head;
head=head->next;
free(temp);

deleteFromFile(roll);

printf("student deleted sucessfully\n");
return;
}
// delete middile nodes
prev=head;
temp=head->next;
while(temp!=NULL)
{
if(temp->roll==roll)
{
prev->next=temp->next;
free(temp);
printf("student deleted sucessfully\n");
return;
}
prev=temp;
temp=temp->next;
}
printf("student not found\n");
}
void updateStudent()
{
struct Student *temp;
int roll,found=0;
if(head==NULL)
{
printf("Database is empty\n");
return;
}
printf("Enter the roll number to update:");
scanf("%d",&roll);
temp=head;
while(temp!=NULL)
{
if(temp->roll==roll)
{
printf("Enter new name:");
scanf("%s",temp->name);
printf("Enter new marks:");
scanf("%f",&temp->marks);
printf("Student data updated sucessfully\n");
found=1;
return;
}
temp=temp->next;
}
if(!found)
{
printf("student not found\n");
}
}
void countStudents()
{
struct Student *temp=head;
int count=0;
while(temp!=NULL)
{
count++;
temp=temp->next;
}
printf("Total Students=%d\n",count);
}
void sortStudents()
{
struct Student *i,*j;
int tempRoll;
char tempName[50];
float tempMarks;
if(head==NULL)
{
printf("Database is empty\n");
return;
}
for(i=head;i!=NULL;i=i->next)
{
for(j=i->next;j!=NULL;j=j->next)
{
if(i->roll>j->roll)
{

// swap roll
tempRoll=i->roll;
i->roll=j->roll;
j->roll=tempRoll;
 
// swap name
strcpy(tempName,i->name);
strcpy(i->name,j->name);
strcpy(j->name,tempName);

// swap marks
tempMarks=i->marks;
i->marks=j->marks;
j->marks=tempMarks;
}
}
}
printf("Students sorted by roll number\n");
}
void saveToFile(struct Student *s)
{
FILE *fp;
struct StudentFile sf;
fp=fopen("student.dat","ab");
if(fp==NULL)
{
printf("file open error\n");
return;
}
sf.roll=s->roll;
strcpy(sf.name,s->name);
sf.marks=s->marks;

fwrite(&sf,sizeof(struct Student),1,fp);
fclose(fp);
}
void loadFromFile()
{
FILE *fp;
struct Student *newNode;
struct StudentFile sf;
fp=fopen("student.dat","rb");
if(fp==NULL)
{
printf("File load error\n");
return;
}
while(fread(&sf,sizeof(struct StudentFile),1,fp))
{
newNode=(struct Student *)malloc(sizeof(struct Student));
newNode->roll=sf.roll;
strcpy(newNode->name,sf.name);
newNode->marks=sf.marks;
newNode->next=head;
head=newNode;
}
fclose(fp);
}
void deleteFromFile(int roll)
{
FILE *fp,*temp;
struct Student s;
int found=0;
fp=fopen("students.dat","rb");
temp=fopen("temp.dat","wb");

if(fp==NULL || temp==NULL)
{
printf("File error\n");
return;
}
while(fread(&s,sizeof(struct Student),1,fp))
{
if(s.roll!=roll)
{
fwrite(&s,sizeof(struct Student),1,temp);
}
else
{
found=1;
}
}
fclose(fp);
fclose(temp);

remove("student.dat");
rename("temp.dat","student.dat");

if(found)
printf("Student deleted permanently from file\n");
else
printf("Student not found in file\n");
}

// main program

int main()
{
int choice;
loadFromFile();
while(1)
{
printf("\n========Student Database Management System===========\n");
printf("1. Insert Student\n");
printf("2. Display Student\n");
printf("3. Search Student\n");
printf("4. Update Student\n");
printf("5. Delete Student\n");
printf("6. Count  Students\n");
printf("7. Sort   students\n");
printf("8. Exit\n");

printf("enter your choice:");
scanf("%d",&choice);

switch(choice)
{
case 1:insertStudent();
       break;
case 2:displayStudents();
       break;
case 3:searchStudent();
       break;
case 4:updateStudent();
       break;
case 5:deleteStudent();
       break;
case 6:countStudents();
       break;
case 7:sortStudents();
       break;
case 8:printf("Existing program\n");
       exit(0);
default:
   printf("Invalid choice! Please try again.\n");
}
}
return 0;
}