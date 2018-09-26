//#include <iostream.h>
#include <stdlib.h>
#include <conio.h>
 
#define maxpila 100
 
struct nodo
{
  int info;
  struct nodo *llink;
  struct nodo *rlink;
}*raiz;
 
struct PILA{
       int tope;
       struct nodo *cont[maxpila];
};
 
void limpiarpila(struct PILA *pila) {
    pila->tope=0;
}
 
bool pilavacia (struct PILA *pila){
     bool valor;
     if (pila->tope==0) valor=true;
     else valor = false;
     return valor;
     }
 
bool pilallena (struct PILA *pila){
     bool valor;
     if (pila->tope==maxpila) valor=true;
     else valor = false;
     return valor;
     }
 
void meterpila(struct PILA *pila, struct nodo *p) {
 
     if (pilallena (pila) == false){
         pila->tope=pila->tope+1;
         pila->cont[pila->tope]=p;
     }
     else cout << "\nERROR: No se puede insertar en la pila, ya que esta llena";
 
 
     }
 
   void sacarpila(struct PILA *pila, struct nodo **q){
 
     if (pilavacia(pila)==false){
        *q=pila->cont[pila->tope];
        pila->tope--;
        }
    else cout << "\nERROR: No se puede sacar de la pila, ya que esta vacia";
 
 
    }
 
void creararbol(){
 
struct nodo *p, *q, *r;
 
int n, i;
cout << "Cuantos nodos va a tener el arbol?";
cin >> n;
raiz =  (struct nodo *)malloc(sizeof(struct nodo));
cout << "Por favor digite la info del nodo raiz del arbol: ";
cin  >> raiz->info;
raiz->llink = NULL;
raiz->rlink = NULL;
 
for (i=2;i<=n;i++){
    p = (struct nodo *) malloc(sizeof(struct nodo));
    cout << "Por favor digite la info del nodo " << i << " del arbol: ";
    cin >> p->info;
    p->llink = NULL;
    p->rlink = NULL;
 
    q=raiz;
 
    while (q!=NULL){
 
          r=q;
 
          if (p->info > q->info) q=q->rlink;
          else q=q->llink;
 
          }
 
          if (p->info > r->info) r->rlink=p;
          else r->llink=p;
 
 
}
 
}
 
void recorrerprofDerecha(){
 struct PILA pila;
 struct nodo *p;
 
 int cont=0;
 
 limpiarpila(&pila);
 meterpila (&pila, raiz);
 
 cout << "\n\nLos datos del arbol recorrido en profundidad son: \n";
 
 while (pilavacia(&pila)==false){
       sacarpila (&pila,&p);
       cout << endl << p->info;
 
       if (p->rlink != NULL) {
 
                   meterpila (&pila, p->rlink);
                   cont++;
 
            }
 
 
 
       }
 
     cout << "\n\nLos datos del arbol insertados a la derecha son: \n"<<cont;
 
}
 
void recorrerprofIzquierda(){
 struct PILA pila;
 struct nodo *p;
 
 int cont=0;
 
 limpiarpila(&pila);
 meterpila (&pila, raiz);
 
 cout << "\n\nLos datos del arbol recorrido en profundidad son: \n";
 
 while (pilavacia(&pila)==false){
       sacarpila (&pila,&p);
       cout << endl << p->info;
 
        if (p->llink != NULL){
 
                  meterpila (&pila, p->llink);
                  cont++;
 
            }
 
       }
 
  cout << "\n\nLos datos del arbol insertados a la izquierda son: \n"<<cont;
 
}
 
int main(void)
{
 
 
     creararbol();
     recorrerprofDerecha();
     recorrerprofIzquierda();
 
 
 
	getch();
 
  return 0;
}

