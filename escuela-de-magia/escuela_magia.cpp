#include "escuela_magia.h"
#include "../common/Common.h"

struct EscuelaDeMagiaSt {
   Set hechizosSet;
   Map magosMap;
   MaxHeap magosMaxHeap;
};

/// Prop�sito: Devuelve una escuela vac�a.
/// O(1)
EscuelaDeMagia fundarEscuela() {
    EscuelaDeMagia escuelita = new EscuelaDeMagiaSt;
    escuelita->hechizosSet = emptyS();
    escuelita->magosMap = emptyM();
    escuelita->magosMaxHeap= emptyH();
    return escuelita;
}

/// Prop�sito: Indica si la escuela est� vac�a.
/// O(1)
bool estaVacia(EscuelaDeMagia m) {
   return isEmptyH(m->magosMaxHeap);
}

/// Prop�sito: Incorpora un mago a la escuela (si ya existe no hace nada).
/// O(log m)
void registrar(string nombre, EscuelaDeMagia m) {
        if(lookupM(nombre,m->magosMap) == NULL){
        assocM(nombre,crearMago(nombre),m->magosMap);
        insertH(crearMago(nombre),m->magosMaxHeap);
        }
}

/// Prop�sito: Devuelve los nombres de los magos registrados en la escuela.
/// O(m)
vector<string> magos(EscuelaDeMagia m) {
       return domM(m->magosMap);
}

/// Prop�sito: Devuelve los hechizos que conoce un mago dado.
/// Precondici�n: Existe un mago con dicho nombre.
/// O(log m)
Set hechizosDe(string nombre, EscuelaDeMagia m) {
      return hechizosMago(lookupM(nombre,m->magosMap));
}

/// Prop�sito: Dado un mago, indica la cantidad de hechizos que la escuela ha dado y �l no sabe.
/// Precondici�n: Existe un mago con dicho nombre.
/// O(log m)
int leFaltanAprender(string nombre, EscuelaDeMagia m) {
    return sizeS(m->hechizosSet) -sizeS(hechizosDe(nombre,m));
}

/// Prop�sito: Devuelve el mago que m�s hechizos sabe.
/// Precondici�n: La escuela no est� vac�a.
/// O(log m)
Mago unEgresado(EscuelaDeMagia m) {
    return maxH(m->magosMaxHeap);
}

/// Prop�sito: Devuelve la escuela sin el mago que m�s sabe.
/// Precondici�n: La escuela no est� vac�a.
/// O(log m)
void quitarEgresado(EscuelaDeMagia m) {
    deleteM(nombreMago(unEgresado(m)),m->magosMap);
   deleteMax(m->magosMaxHeap);
}

MaxHeap enseniarBis(Hechizo h, string nombre,MaxHeap mH){
///Eficiencia: O(log N)
///Dado un hechizo, nombre y un maxHeap, agrega el hechizo al mago
   MaxHeap heapActualizada = emptyH();
    while(sizeH(mH)!= 0){
        if(nombreMago(maxH(mH)) != nombre){
            insertH(maxH(mH),heapActualizada);
            deleteMax(mH);
        }
        else {
            aprenderHechizo(h,maxH(mH));
            insertH(maxH(mH),heapActualizada);
            deleteMax(mH);
        }
    }
    return heapActualizada;
}


/// Prop�sito: Ense�a un hechizo a un mago existente, y si el hechizo no existe en la escuela es incorporado a la misma.
/// O(m . log m + log h)
void enseniar(Hechizo h, string nombre, EscuelaDeMagia m) {
    addS(h,m->hechizosSet) ;
    aprenderHechizo(h,lookupM(nombre,m->magosMap)) ;
    m->magosMaxHeap = enseniarBis(h,nombre,m->magosMaxHeap) ;
}


/// Prop�sito: Libera toda la memoria creada por la escuela (incluye magos, pero no hechizos).
void destruirEscuela(EscuelaDeMagia m) {
        destroyS(m->hechizosSet);
        destroyM(m->magosMap);
       while(m->magosMaxHeap!=NULL){
			destroyMago(maxH(m->magosMaxHeap));
			deleteMax(m->magosMaxHeap);
        }
		destroyH(m->magosMaxHeap);
}


