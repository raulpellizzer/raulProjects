#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trab1D.h"

int main () {
  UsersRegistered U;
  NoU *aux1 = NULL, *aux4 = NULL;
  NoList *aux2 = NULL;
  NoLn *aux3 = NULL;
  Identity temp1, temp2;
  Message m;
  int error, op, i, j, count = 0;
  char choice, garbage;

  CreateUR(&U);

  printf("        Welcome!\n\n");

  printf("           Here are your options. Choose an action :\n");
  printf("1 - Register new user\n");
  printf("2 - Show all users and their information\n");
  printf("3 - Ask for partnership\n");
  printf("4 - See list of requests for partnerships\n");
  printf("5 - Send a message to a partner\n");
  printf("6 - See incoming messages\n");
  printf("7 - Suggest new partnerships\n");
  printf("8 - Reset system\n");
  printf("9 - Exit\n\n");

  do{
    scanf("%d", &op);

    switch(op) {
    case 1:
      printf("Enter your name and nickname : ");
      scanf("%s %s", temp1.Name, temp1.Nickname);
      printf("\n");
      PushUR(&U,&temp1,&error);

      aux1 = U.Start;
      for(i=0;i<U.Total-1;i++)
	aux1 = aux1->Next;
      CreateSt(&(aux1->URegistered.St));
      CreateLn(&(aux1->URegistered.Ln));
      Create(&(aux1->URegistered.Pl));
      printf("Welcome, %s!\n", temp1.Nickname);
      break;

      
    case 2:
      printf("Showing users information : Users and their partners \n\n");
      aux1 = U.Start;
      
      for(i=0;i<U.Total;i++) { 
	if(aux1->URegistered.Pl.Total > 0) {
	  printf("%s works with : ", aux1->URegistered.Myname.Nickname); 
	  count = aux1->URegistered.Pl.Total;
	  aux2 = aux1->URegistered.Pl.Start; 
	  for(j=0;j<count;j++) {
	    printf("%s; ", aux2->I.Nickname);
	    aux2 = aux2->Next;
	  }
	} 
	else
	   printf("%s has no partners.", aux1->URegistered.Myname.Nickname);
	printf("\n");
	aux1 = aux1->Next;
      }
      break;
      

    case 3:
      printf("Enter your name and nickname : ");
      scanf("%s %s", temp1.Name, temp1.Nickname);
      printf("Enter the nickname of who you want to work with : ");
      scanf("%s", temp2.Nickname);

      if(Exist(U,temp2.Nickname)) {
	aux1 = U.Start;
		
	while(strcmp(temp2.Nickname,aux1->URegistered.Myname.Nickname) != 0) {
	  aux1 = aux1->Next;
        }

	PushLn(&(aux1->URegistered.Ln),&temp1,&error);
	printf("Request submitted successfully!\n");
      } else 
	printf("User does not exist!\n");
      break;

      
    case 4:
      printf("Enter your nickname : ");
      scanf("%s", temp1.Nickname);
      
      aux1 = U.Start; 
      while(strcmp(temp1.Nickname,aux1->URegistered.Myname.Nickname) != 0) {
	aux1 = aux1->Next;
      }
      
      if(aux1->URegistered.Ln.Total > 0) { 
	aux3 = aux1->URegistered.Ln.Start; 
	for(i=0;i<aux1->URegistered.Ln.Total;i++) {
	  aux4 = U.Start; 
	  printf("%s wants to work with you. Accept? (y/n) : ", aux3->I.Nickname);
	  scanf("%c %c", &garbage, &choice);
	  if(choice == 'y') {
	    while(strcmp(aux3->I.Nickname,aux4->URegistered.Myname.Nickname) != 0) {
	      aux4 = aux1->Next;
	    }

	    Push(&(aux1->URegistered.Pl),&(aux3->I),&error);
	    Push(&(aux4->URegistered.Pl),&(aux1->URegistered.Myname),&error);
	    printf("Operation was successful!\n");
	  }
	  aux3 = aux3->Prev;
	}
	
	EmptiesLn(&(aux1->URegistered.Ln));
	
      } else printf("You dont have any requests at the moment.\n");
      break;

    case 5:
      printf("Enter your nickname : ");
      scanf("%s", m.StI.I.Nickname);
      printf("Enter your partners nickname : ");
      scanf("%s", temp2.Nickname);

      aux1 = U.Start;
      while(strcmp(temp2.Nickname,aux1->URegistered.Myname.Nickname) != 0) {
	aux1 = aux1->Next;
      }
      if(SearchInPL(aux1->URegistered.Pl,m.StI.I.Nickname)) {
	printf("Type your message : ");
	scanf("%c", &garbage);
	scanf("%[^\n]", m.StI.Text);

	PushSt(&(aux1->URegistered.St),&m,&error);
	printf("Your message has been sent!\n");
      } else
	printf("%s is not your partner.\n", temp2.Nickname);
      break;


    case 6:
      printf("Enter your nickname : ");
      scanf("%s", temp1.Nickname);
      aux1 = U.Start;
      while(strcmp(temp1.Nickname,aux1->URegistered.Myname.Nickname) != 0) {
	aux1 = aux1->Next;
      }
      
      printf("Here are your messages :\n");
      if(aux1->URegistered.St.Total == 0)
	printf("You have no messages.\n");
      while(aux1->URegistered.St.Total > 0) {
	PopSt(&(aux1->URegistered.St),&m,&error);
	printf("[%s] : %s\n", m.StI.I.Nickname, m.StI.Text);
      }
      break;


    case 7:
      printf("Suggested partnerships :\n");
      aux1 = U.Start;
      for(i=0;i<U.Total-1;i++) {
	printf("%s, ", aux1->URegistered.Myname.Nickname);
	aux1 = aux1->Next;
      }
      printf("%s.\n", aux1->URegistered.Myname.Nickname);
      break;


    case 8:
      aux1 = U.Start;
      for(i=0;i<U.Total;i++) {
	EmptySt(&(aux1->URegistered.St));
	//EmptiesLn(&(aux1->URegistered.Ln));
	//Empties(&(aux1->URegistered.Pl));
	aux1 = aux1->Next;
      }
      U.Total = 0;
      break;


    case 9:
      printf("Thank you !!\n\n");
      return 0;


    default:
      printf("Type again\n");
    }
    printf("So, whats next?\n\n");
  }while(op!=10);
}
