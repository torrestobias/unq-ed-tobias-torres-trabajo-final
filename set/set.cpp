#include "set.h"
#include "../common/Common.h"

struct Node {
   Hechizo elem; // el elemento que este nodo almacena
   Node* next; // siguiente nodo de la cadena de punteros
};

struct SetSt {
   int size; // cantidad de elementos del conjunto
   Node* first; // puntero al primer elemento
};

/**
  Invariantes de representacion:
    - size es la cantidad de nodos
    - no hay nodos con hechizos repetidos
**/

/// Proposito: retorna un conjunto de hechizos vacio
/// Costo: O(1)
Set emptyS() {
   Set s = new SetSt;
   s ->size = 0;
   s ->first = NULL;
   return s;
}

/// Proposito: retorna la cantidad de hechizos
/// Costo: O(1)
int sizeS(Set s) {
   return s->size;
}

/// Proposito: indica si el hechizo pertenece al conjunto
/// Costo: O(h), h = cantidad de hechizos
bool belongsS(Hechizo h, Set s) {
       Node* n = s->first;

        while ((n != NULL) && (!mismoHechizo(n->elem,h))){
            n = n->next;
        }
        //cout<<"salio del while"<<endl;
        return (n != NULL);
}

/// Proposito: agrega un hechizo al conjunto
/// Costo: O(h), h = cantidad de hechizos
void addS(Hechizo h, Set s) {
    Node* nodo = new Node;
    nodo->elem = h;
    nodo->next = NULL;
        if(s->first == NULL){
            s->size++;
            s->first= nodo;
        }
        if(!belongsS(h,s)){   ///PREGUNTAR!!!
        Node* tmp = s->first;
            s->size ++;
            s->first = nodo;
            s->first->next = tmp;
    }

}

/// Proposito: borra un hechizo del conjunto (si no existe no hace nada)
/// Costo: O(h), h = cantidad de hechizos
void removeS(Hechizo h, Set s) {
    if(belongsS(h,s)){
        Node* previo = NULL;
        Node* actual = s->first;

        if(s->size == 1 && actual->elem ==h){
            s->first = NULL;

        }

        while(actual != NULL && actual->elem != h){
            previo = actual;
            actual = actual->next;
        }

        if (previo == NULL){
            Node* tmp = actual;
            actual = tmp->next;
            delete tmp;
            s->size--;

        }
        else {
            Node* tmp = actual;
            previo->next= tmp->next;
            delete tmp;
            s->size--;

        }

    }


}
/// Proposito: borra toda la memoria consumida por el conjunto (pero no la de los hechizos)
/// Costo: O(n)
void destroyS(Set s) {
    Node* nodo = s->first;

    while(nodo != NULL){
    Node* tmp = nodo ->next;
    nodo = tmp;
    delete nodo;
    }
    delete s;
}

/// Proposito: retorna un nuevo conjunto que es la union entre ambos (no modifica estos conjuntos)
/// Costo: O(h^2), h = cantidad de hechizos
Set unionS(Set s1,Set s2){
   Set setADevolver = emptyS();
   Node* n1 = s1->first;
   Node* n2 = s2->first;
        while(n1 != NULL){
            addS(n1->elem,setADevolver);
            n1 = n1->next;
        }

        while(n2 != NULL){
            addS(n2->elem,setADevolver);
            n2 = n2->next;
        }

        return setADevolver;
   }

