#include <strings.h>
#include <stdlib.h>
#include "STD_Types.h"
#include <stdio.h>

typedef struct nodedef
{
	char *name;
	u8 age;
	u8 gender;
	u32 ID;
	struct nodedef* next;
}node;

typedef enum
{
	male,
	female
}gen;

node* head= NULL;
u8 patients=0;
int reservation[5]={0};
// 0:	2pm to 2:30pm,  
// 1:	2:30pm to 3pm,
// 2:	3pm to 3:30pm, 
// 3:	4pm to 4:30pm
// 4:	4:30pm to 5pm.
void printlist(void);
void addNode(u32 id ,char name[50] ,u8 age,u8 gender);
void edit (void);
u8 isfound(u32 id);
node* search(u32 id);
void intro();
void adminShow();
void patientShow();
void reserve ();
void cancelReserve ();
void viewReserve (); 
void viewAvailable ();
char checkAvailavle(char slot);
char searchReservations(int id);

/*
 * Func Name: printlist
 * Input Par: void
 * Description: N/A
 * Return Value: void
 * Description: N/A
 * Description: func is used to print the patient details
 * */
void printlist(void)
{
	node* n=head;
	int i=0;
	printf("---------------------\n");
	printf("---------------------\n");
	while (n!= NULL)
	{
		i++;
		printf("Patient %d:-\n",i);
		printf("ID    :%d   \n",n->ID);
		printf("name  :%s  \n",n->name);
		printf("age   :%d   \n",n->age);
		if (n->gender==male)
		{printf("gender:male\n");}
		else if (n->gender==female)
		{printf("gender:female\n");}
		n=n->next;
		printf("---------------------\n");
	}
	if(i==0)
	{printf("The list is empty\n");}
	printf("---------------------\n");
}



/*
 * Func Name: addNode
 * Input Par: id
 * Description: the unique id of each patient
 * Input Par: name
 * Description: array of characters that make up the name
 * Input Par: age
 * Description: age of patient between 0-150
 * Input Par: gender
 * Description: gender of patient between 0->male,1->female
 * Return Value: void
 * Description: N/A
 * Description: func is used to add another patient to the linked list
 * */
void addNode(u32 id ,char name[50] ,u8 age,u8 gender)
{
	if(!isfound(id))
	{
		if (patients==0)
		{
			
			head = (node*) malloc(sizeof(node));
			head->ID=id;
			//head->name=(char*) malloc(50);
			head->name=malloc(strlen(name)+1);
			strcpy(head->name,name);
			if (age>=0||age<=150)
			{
				head->age=age;
				
				if (gender==male || gender==female)
				{
					head->gender=gender;
					head->next=NULL;
					patients++;
					printf("Patient added\n");
					return;
				}
				else
				{
				printf("Invalid Gender\n");
				return;
				}
			}
			else
			{
				printf("Invalid Age\n");
				return;
			}
			
			
		}
		else
		{
			node* n=head;
			while (n->next!= NULL)
			{
				n=n->next;
			}
			node* new = (node*) malloc(sizeof(node));
			new->ID=id;
			//new->name=(char*) malloc(50);
			new->name=malloc(strlen(name)+1);
			strcpy(new->name,name);
			new->age=age;
			new->gender=gender;
			new->next=NULL;
			
			n->next=new;
			
			patients++;
			
		}		
		printf("Patient added\n");
	}
	else
	printf("ID already exists.");
	
}

/*
 * Func Name: edit
 * Input Par: void
 * Description: N/A
 * Return Value: void
 * Description: N/A
 * Description: func is used to edit the patient details(age-name-gender)
 * */
void edit (void)
{
	u8 option;
	u32 id;
	printf("To Edit Age Choose 1\n");
	printf("To Edit Name Choose 2\n");
	printf("To Edit Gender Choose 3\n");
	printf("Enter Option:");
	scanf("%d",&option);
	printf("%d\n",option);

	printf("Enter ID:");
	scanf("%d",&id);
	node* pat=search(id);
	if (pat==NULL)
	{
		printf("Incorrect ID\n");
		return;
	}
	
	switch (option)
	{
		case 1:
		u8 a; /* age */
		printf("Enter Updated Age:");
		scanf("%d",&a);
		if (a>=0||a<=150)
		{
			pat->age=a;
			return;
		}
		else 
		{
			printf("Invalid Age\n");
			return;
		}
		break;

		case 2:
		char nam[50];
		printf("Enter Updated Name:");
		scanf(" %[^\n]%*c", &nam);
		pat->name=malloc(strlen(nam)+1);
		strcpy(pat->name,nam);
		return;
		break;

		case 3:
		u8 g; /* gender */
		printf("Enter Updated Gender(0->male,1->female): ");
		scanf("%d",&g);
		if (g==male || g==female)
		{
			pat->gender=g;
			return;
		}
		else 
		{
			printf("Invalid Gender\n");
			return;
		}
		break;
		default:
		printf("Incorrect Option\n");
	}
	
}


/*
 * Func Name: isfound
 * Input Par: id
 * Description: an id of a patient
 * Return Value: char
 * Description: 0 or 1
 * Description: return 0 if the id doesn't exist and 1 if a patient with the same id exist
 * */
u8 isfound(u32 id)
{
	if (head==0)
		return 0;
	node* n=head;
	for (u8 i=0;i<patients;i++)
	{
		if (n->ID==id)
		{return 1;}
		n=n->next;
	}
	
	return 0;
}

/*
 * Func Name: search
 * Input Par: id
 * Description: an id of a patient
 * Return Value: node 
 * Description: node from the linked list(patient)
 * Description: return null if the id doesn't exist and pointer to a node if a patient with the same id exist
 * */
node* search(u32 id)
{
	if (head==0)
		return NULL;
	node* n=head;
	for (u8 i=0;i<patients;i++)
	{
		if (n->ID==id)
		{return n;}
		n=n->next;
	}
	return NULL;
}

/*
 * Function Name :intro
 * INput Par 	 :void
 * Return VAlue :void
 * Description  : starting the program by welcoming user and offering the login choices
 */
void intro()
{
	s8 	state =0,flag=0;
	s8	userState =0;
	s32	pass=0;
	while (flag==0)
	{	
		printf("**--**--**--*--**--**--*--**--**--*--**--**--*--**--**--*--**--**--**\n");
		printf ("Welcome to our System------------------\n");
		printf ("If you want to log as  an Admin enter 1\n");
		printf ("If you want to log as  an User  enter 2\n");
		printf ("To Exit the program enter 3\n");
		printf ("Your choice :");
		scanf  (" %d",&state);
		printf ("**--**--**--*--**--**--*--**--**--*--**--**--*--**--**--*--**--**--**\n");
		if (state==1)
		{
			for(s32 i=0;i<3;i++)
			{
				printf ("Since you choosed to login as an admin Please enter you PASSWORD:\n");
				scanf("%d",&pass);
				if (pass==1234)
				{
					printf ("welcome back\n");
					printf("**--**--**--*--**\n");
					adminShow();
					i=8;
				}
				else
				{
					printf ("INVALID PASSWORD \n");
				}
				if(i==2)
				{
					printf ("you consumed the 3 avlabile tries ,Sorry you cann't login");	
				}
			}
			printf("**--**--**--*--**--**--*--**--**--*--**--**--*--**--**--*--**--**--**\n");
			flag=0;
		}
		else if (state==2)
		{
			printf ("welcome \n");
			patientShow();	
			flag=0;
		}
		else if (state==3)
		{
			flag=1;
		}
		else printf ("Wrong input");

	}	
}
/*
 * Function Name :Adminshow
 * INput Par 	 :void
 * Return VAlue  :void
 * Description   : called when you succseded to login as andmin it shows the admin options
 */
void adminShow()
{
	s8 flag =1;
	s8 state =0;
	while (flag)
	{
		printf ("If you want to add a new patient ,enter 1\n");
		printf ("If you want to edit a patient record ,enter 2\n");
		printf ("If you want to reserve a slot with the doctor ,enter 3\n");
		printf ("If you want to cancel a reservation ,enter 4\n");
		printf ("If you want to exit,enter 5\n");

		printf ("Your choice :");
		scanf  ("%d",&state);

		switch (state)
		{
			case 1:
			{
				char name[50];
				u8 a,gender;
				u32 id;
				
				printf("Enter ID:");
				scanf("%d",&id);
				printf("Enter Name:");
				scanf(" %[^\n]%*c", &name);
				printf("Enter Gender(0->male,1->female):");
				scanf("%d", &gender);
				if(gender==male||gender==female)
				{
					printf("Enter Age:");
					scanf("%d",&a);
					if (a>=0||a<=150)
					{
						addNode(id,name,a,gender);
					}
					else
					{
						printf("Invalid Age\n");
					}
				}
				else
				{
					printf("Invalid Gender\n");
				}
				flag =1;
				break;	
			}
			case 2:
			{
				u32 id;
				edit();
				flag =1;
				break;	
			}
			case 3:
			{
				reserve ();
				flag =1;
				break;	
			}
			case 4:
			{
				cancelReserve ();
				flag =1;
				break;	
			}
			case 5:
			{
				flag =0;
				break;	
			}
			default : 
			{
				printf ("Wrong input");
				flag=1;
			}
		}
	}
	intro();
}
/*
 * Function Name :Patientshow
 * INput Par 	 :void
 * Return VAlue  :void
 * Description   :called when you succsedeed to login as user it shows the user options
 */
void patientShow()
{
	s8 flag =1;
	s8 userState =0;
	while (flag)
	{
		printf ("Enter 1 to view patient records \n");
		printf ("Enter 2 to view reservations    \n");
		printf ("Enter 3 to exit,               \n");
		scanf("%d",&userState);
		printf("**--**--**--*--**--**--*--**--**--*--**--**--*--**--**--*--**--**--**\n");

		if ( userState==1)
		{
			printlist();
			flag=1;
		}
		else if ( userState==2)
		{
			viewReserve ();
			flag=1;
		}
		else if(userState==3)
		{
			printf("Goodbye");
			flag=0;
		}
		printf("**--**--**--*--**--**--*--**--**--*--**--**--*--**--**--*--**--**--**\n");
		
	}
	intro();
}
/*
 * Function Name :viewReserve
 * INput Par 	 :void
 * Return VAlue  :void
 * Description   :Shows if each slot is reserved or not and if it is reserved it shows the patient Id who reserved it
 *				  used in user mode .
 */
void viewReserve ()
{
	printf("--------------------------------------------------------\n");
	for (int i=0;i<5;i++)
	{
		switch(i)
		{
			case 0 :
					printf("reservation ->0 from 2pm to 2:30pm : ");
					if (reservation[0]==0) {printf ("No reservation yet \n");}
					else {printf ("Reserved Patient ID: %d\n",reservation[0]);}
					break;
			case 1 :
					printf("reservation ->1 from 2:30pm to 3pm : ");
					if (reservation[1]==0) {printf ("No reservation yet \n");}
					else {printf ("Reserved Patient ID: %d\n",reservation[1]);}
					break;
			case 2 :
					printf("reservation -2 from 3pm to 3:30pm : ");
					if (reservation[2]==0) {printf ("No reservation yet \n");}
					else {printf ("Reserved Patient ID: %d \n",reservation[2]);}
					break;
			case 3 :
					printf("reservation ->3 from 4pm to 4:30pm : ");
					if (reservation[3]==0) {printf ("No reservation yet \n");}
					else {printf ("Reserved Patient ID: %d \n",reservation[3]);}
					break;
			case 4 :
					printf("reservation ->4 from 4:30pm to 5pm : ");
					if (reservation[4]==0) {printf ("No reservation yet \n");}
					else {printf ("Reserved Patient ID: %d \n",reservation[4]);}
					break;
		}
	}
	printf("--------------------------------------------------------\n\n\n");
}
/*
 * Function Name :viewAvailable
 * INput Par 	 :void
 * Return VAlue  :void
 * Description   :Shows only the avalible (not reserved) slots
 *				  used in Admin mode .
 */
void viewAvailable ()
{	
	char slot=-1;
	char flag =0;
	printf("\nAvailable Slots---------------------------------------------\n");
	for (int i=0;i<5;i++)
	{	
		if (reservation[i]==0)
		{
			switch(i)
			{
				case 0 :
						printf("reservation ->0 from 2pm to 2:30pm : ");
						printf ("No reservation yet \n");
						flag++;
						break;
				case 1 :
						printf("reservation ->1 from 2:30pm to 3pm : ");
						printf ("No reservation yet \n");
						flag++;
						break;
				case 2 :
						printf("reservation ->2 from 3pm to 3:30pm : ");
						printf ("No reservation yet \n");
						flag++;
						break;
				case 3 :
						printf("reservation ->3 from 4pm to 4:30pm : ");
						printf ("No reservation yet \n");
						flag++;
						break;
				case 4 :
						printf("reservation ->4 from 4:30pm to 5pm : ");
						printf ("No reservation yet \n");
						flag++;
						break;
			}
		}
	}
	printf("Slots numbered 0,1,2,3,4\n");
	printf("%d Available slots \n",flag);
	printf("--------------------------------------------------------\n\n");
	
}
/*
 * Function Name :reserve
 * INput Par 	 :void
 * Return VAlue  :void
 * Description   :add a reservation to the desired slot .
 */
void reserve ()
{	
	int id=0,id2=0;
	char slot=0;
	char flag=0;
	
	viewAvailable();
	printf ("Please choose the desired slot for reservation: ");
	scanf ("%d",&slot);
	flag= checkAvailavle (slot);
	if (flag==1)
	{
		flag=0;
		printf("Please enter the patient ID :");
		scanf ("%d",&id);
		flag=searchReservations(id);
		
		id2=id;
		if (flag==1)
		{
			printf ("You have already booked a reservation\n");
		}
		else
		{	
			flag=0;
			flag = isfound (id);
			
			if (flag==0)
			{ 
				u8 a,gender;
				
				char name[250];
				printf ("New Patient Data:\n");
				printf("patient ID:%d\n",id);
				printf("Enter Name:");
				scanf(" %[^\n]%*c", &name);
				printf("Enter Gender:");
				scanf("%d", &gender);	
				printf("Enter Age:");
				scanf("%d",&a);
				
				addNode(id,name,a,gender);
				printf ("id %d\n",id);
			}
			
			reservation [slot]=id2;
			
			printf ("reservation successfully added\n");
			printf("--------------------------------------------------------\n");
		}
	}	
}
/*
 * Function Name :cancelReserve
 * INput Par 	 :void
 * Return VAlue  :void
 * Description   :cancel a reservation and empty the slot  .
 */
void cancelReserve () 
{
	int id=0;
	char flag =0;
	printf("Please enter the patient ID to be canceled:\n");
	scanf ("%d",&id);
	for (int i=0;i<5;i++)
	{
		if (reservation[i]==id)
		{
			flag ++;	
			reservation[i]=0;
		}
	}
	if (flag==0)
	{
		printf ("Id NOT Found");
	}
	else 
	{
		printf ("Id Found  and canceled\n");
	}
	viewReserve();

}
/*
 * Function Name :checkAvailavle
 * INput Par 	 :char slot
 * INPUT Description   :number of slot to be checked
 * Return VAlue  :char
 * RETURN Description   :if it could be reserved or not
 * Description   :checks the desired slot before reservation if its alredy reserved or not in the time sechdule .
 */
char checkAvailavle(char slot)
{ 	
	if((slot<0)||(slot>4)) 
	{
		printf ("Sorry,Out of Schedule\n");
		return 0;	
	}
	else if (reservation[slot]==0) 
	{	
		printf ("Accepted\n");
		return 1;
	}
	else 
	{	
		printf ("Sorry,Already reserved\n");
		return 0;
	}
}
/*
 * Function Name :searchReservations
 * INput Par 	 :int id
 * INPUT Description   :id to be checked
 * Return VAlue  :char
 * RETURN Description   :if it is found or not
 * Description   :search if this id has already make a reservation  .
 */
char searchReservations(int id)
{
	for (int i=0;i<5;i++)
	{	
		if (reservation[i]==id) return 1;
	}
	
	 return 0;
}


