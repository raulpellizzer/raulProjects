#ifndef TRAB1D_H
#define TRAB1D_H

/* IMPLEMENTATION : DINAMIC AND THREADED STACK (Pilha) */

#define StackSize 100

typedef struct {
  char Name[40];
  char Nickname[30];
}Identity;

typedef struct {
  char Text[100];
  Identity I;
}StInfo;

typedef struct nodest {
  StInfo StI;
  struct nodest *Previous;
}Message;

typedef struct {
  Message *Top;
  int Total;
}Stack;

void CreateSt(Stack *);
int IsStEmpty(Stack *);
void PushSt(Stack *, Message *, int *);
void PopSt(Stack *, Message *, int *);
void EmptySt(Stack *);

/* End of stack code */

/* IMPLEMENTATION : DINAMIC AND THREADED LINE (Fila) */

#define LineSize 100

typedef struct nodef {
  Identity I;
  struct nodef *Next;
  struct nodef *Prev;
}NoLn;

typedef struct {
  NoLn *Start;
  NoLn *End;
  int Total;
}Line;  /* Each person has his/her line of requests */

void CreateLn(Line *);
void EmptiesLn(Line *);
int IsLnEmpty(Line *);
void PushLn(Line *, Identity *, int *);
void PopLn(Line *, Identity *, int *);

/* End of line code */

/* IMPLEMENTATION : DINAMIC AND THREADED LIST (Lista) */

#define ListSize 100

typedef struct nodel {
  Identity I;
  struct nodel *Next;
}NoList;

typedef struct { // Each person has his/her list of partners
  NoList *Start;
  NoList *End;
  int Total;
}PList;

void Create(PList *);
void Empties(PList *);
int IsEmpty(PList *);
void Push(PList *, Identity *, int *);
void Pop(PList *, char [], int *);

/* User code */

typedef struct {
  Stack St;
  Line Ln;
  PList Pl;
  Identity Myname;
}User;

typedef struct nodeu {
  User URegistered;
  struct nodeu *Next;
}NoU;

typedef struct { // List with all the users registered
  NoU *Start;
  NoU *End;
  int Total;
}UsersRegistered;

void CreateUR(UsersRegistered *);
void PushUR(UsersRegistered *, Identity *, int *);
int Exist(UsersRegistered u, char []); // Searches for a user
int SearchInPL(PList pl, char []);

#endif

