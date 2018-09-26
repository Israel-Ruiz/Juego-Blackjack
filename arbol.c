#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>


struct nodoarbol{
struct nodoarbol *izqnodo;
int info;
char letra;
struct nodoarbol *dernodo;
};
typedef struct nodoarbol NODO;
typedef NODO *ARBOL;

void insertanodonuevo(ARBOL *, int,char);
void inorden (ARBOL);
void preorden (ARBOL);
void postorden (ARBOL);
void treefree (ARBOL);

main()
{
int i, n, elementos;
char newnod, chain;
ARBOL raiz=NULL;

printf("\n\nCuantos nodos desea agregar: ");
scanf("%d",&n);
for (i=0;i<n;i++)
{
fflush(stdin);
printf("\nIntroduce numero: ");
scanf("%d",&elementos);
fflush(stdin);
printf("Introduce letra: ");
scanf("%c",&chain);
insertanodonuevo(&raiz,elementos,chain);
}
system("cls");
printf("\n\nPreorden: ");
preorden(raiz);
printf("\n\nInorden: ");
inorden(raiz);
printf("\n\nPostOrden: ");
postorden(raiz);
getch();
treefree(raiz);
raiz=NULL;
return 0;
}


void insertanodonuevo(ARBOL *rarbol, int nuevo,char l)
{
if (*rarbol==NULL)
{
*rarbol=(NODO *)malloc(sizeof(NODO));
if(*rarbol!=NULL)
{
(*rarbol)->info=nuevo;
(*rarbol)->letra=l;
(*rarbol)->izqnodo=NULL;
(*rarbol)->dernodo=NULL;
}
else {printf("\nMEMORIA NO DISPONIBLE\n");}
}
else
if(nuevo<(*rarbol)->info)
insertanodonuevo(&((*rarbol)->izqnodo),nuevo,l);
else
if(nuevo>(*rarbol)->info)
insertanodonuevo(&((*rarbol)->dernodo),nuevo,l);
}
void preorden (ARBOL rarbol)
{
if(rarbol!=NULL)
{

printf("[%d]",rarbol->info);
printf("[%c]",rarbol->letra);
preorden(rarbol->izqnodo);
preorden(rarbol->dernodo);
}
}

void inorden(ARBOL rarbol)
{
if(rarbol!=NULL)
{
inorden(rarbol->izqnodo);
printf("[%d]", rarbol->info);
printf("[%c]",rarbol->letra);
inorden(rarbol->dernodo);
}
}

void postorden(ARBOL rarbol)
{
if(rarbol!=NULL)
{

postorden(rarbol->izqnodo);
postorden(rarbol->dernodo);
printf("[%d]", rarbol->info);
printf("[%c]",rarbol->letra);
}
}

void treefree(ARBOL rarbol)
{
if(rarbol!=NULL)
{
treefree (rarbol->izqnodo);
treefree(rarbol->dernodo);
treefree (rarbol);
}
}
