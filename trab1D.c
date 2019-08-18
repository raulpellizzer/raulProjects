#include <stdio.h>
#include <stdlib.h>
#include "trab1D.h"

                     /* Stack functions  */

void CreateSt(Stack *st) {
  st->Top = NULL;
  st->Total = 0;
}

int IsStEmpty(Stack *st) {
  if(st->Top == NULL) 
    return 1;
  else return 0;
}

void PushSt(Stack *st, Message *m, int *error) {
  Message *x= (Message*) malloc (sizeof(Message));
  if(x!=NULL) {
    *error = 0;
    x->Previous = st->Top;
    st->Top = x;
    st->Top->StI = m->StI;
    st->Total++;
  } else *error = 1;
}

void PopSt(Stack *st, Message *m, int *error) {
  Message *aux;
  if(!IsStEmpty(st)) {
    *error = 0;
    m->StI = st->Top->StI;
    aux = st->Top;
    st->Top = st->Top->Previous;
    aux->Previous = NULL;
    free(aux);
    aux = NULL;
    st->Total--;
  } else *error = 1;
}

void EmptySt(Stack *st) {
  Message *aux;
  int i;
  for(i=0;i<st->Total;i++) {
    aux = st->Top;
    st->Top = st->Top->Previous;
    aux->Previous = NULL;
    free(aux);
    st->Total--;
  }
}
                     /* Line functions */

void CreateLn(Line *ln) {
  ln->Start = NULL;
  ln->End = NULL;
  ln->Total = 0;
}

void EmptiesLn(Line *ln) {
  NoLn *aux1 = NULL, *aux2 = NULL;
  aux1 = ln->Start;
  aux2 = aux1->Next;
  while(aux2!=NULL) {
    aux1->Next= NULL;
    free(aux1);
    aux1 = aux2;
    aux2 = aux1->Next;
  }
  free(aux1);
  ln->Start = NULL;
  ln->End = NULL;
  ln->Total = 0;
}

int IsLnEmpty(Line *ln) {
  if(ln->Start == NULL && ln->End == NULL)
    return 1;
  else return 0;
}

void PushLn(Line *ln, Identity *i, int *error) {
  NoLn *n = (NoLn*) malloc (sizeof(NoLn));
  if(n!=NULL) {
    *error = 0;
    n->I = *i;
    n->Prev = NULL;
    if(ln->Total == 0) {
      n->Next = NULL;
      ln->Start = n;
      ln->End = n;
    } else {
      n->Next = ln->End;
      ln->End->Prev = n;
      ln->End = n;
    }
    ln->Total++;
  } else *error = 1;
}

void PopLn(Line *ln, Identity *i, int *error) {
  NoLn *aux;
  aux = ln->End;
  while(aux->Next!=ln->Start) {
    aux = aux->Next;
  }
  *i = ln->Start->I;
  free(ln->Start);
  ln->Start = aux;
  ln->Start->Next = NULL;
}

                     /* List functions */

void Create(PList *pl) {
  pl->Start = NULL;
  pl->End = NULL;
  pl->Total = 0;
}

void Empties(PList *pl) {
  NoList *aux1, *aux2;
  aux1 = pl->Start;
  aux2 = aux1->Next;
  while(aux2!=NULL) {
    aux1->Next = NULL;
    free(aux1);
    aux1 = aux2;
    aux2 = aux1->Next;
    pl->Total--;
  }
  free(aux1);
  pl->Start = NULL;
  pl->End = NULL;
}

int IsEmpty(PList *pl) {
  if(pl->Total == 0)
    return 1;
  else return 0;
}

void Push(PList *pl, Identity *i, int *error) {
  NoList *n = (NoList*) malloc (sizeof(NoList));
  if(n!=NULL) {
    *error = 0;
    n->I = *i;
    n->Next = NULL;
    if(pl->Total == 0) {
      pl->Start = n;
      pl->End = n;
    } else {
      pl->End->Next = n;
      pl->End = n;
    }
    pl->Total++;
  } else *error = 1;
}

void Pop(PList *pl, char nickname[30], int *error) {
  NoList *aux1, *aux2 = NULL;
  int flag = 0;
  *error = 1;
  aux1 = pl->Start;
  while(aux1!=NULL && flag == 0) {
    if(strcmp(nickname, aux1->I.Nickname) == 0) {
      aux2 = aux1->Next;
      aux1->Next = NULL;
      free(aux1);
      pl->Start = aux2;
      pl->Total--;
      *error = 0;
      flag = 1;
    } else
      aux1 = aux1->Next;
  }
}

void CreateUR(UsersRegistered *u) {
  u->Start = NULL;
  u->End = NULL;
  u->Total = 0;
}

void PushUR(UsersRegistered *u, Identity *i, int *error) {
  NoU *n = (NoU*) malloc (sizeof(NoU));
  if(n!=NULL) {
    *error = 0;
    n->URegistered.Myname = *i;
    n->Next = NULL;
    if(u->Total == 0) {
      u->Start = n;
      u->End = n;
    }
    else {
      u->End->Next = n;
      u->End = n;
    }
    u->Total++;
  } else *error = 1;
}

int Exist(UsersRegistered u, char nickname [30]) {
  int found = 0;
  NoU *aux = u.Start;
  while(aux!=NULL && found == 0) {
    if(strcmp(nickname, aux->URegistered.Myname.Nickname) == 0)
      found = 1;
    else aux = aux->Next;
  }
  return found;
}

int SearchInPL(PList pl, char nickname[30]) {
  int found = 0;
  NoList *aux = pl.Start;
  while(aux!=NULL && found == 0) {
    if(strcmp(nickname, aux->I.Nickname) == 0)
      found = 1;
    else aux = aux->Next;
  }
  return found;
}

  
  
      
    
  
