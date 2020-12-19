#ifndef ESCUELA_MAGIA_H
#define ESCUELA_MAGIA_H

#include <iostream>
#include <cstdlib>
#include <vector>
#include "../hechizo/hechizo.h"
#include "../mago/mago.h"
#include "../set/set.h"
#include "../map/map.h"
#include "../maxheap/maxheap.h"

using namespace std;

struct EscuelaDeMagiaSt;
typedef EscuelaDeMagiaSt* EscuelaDeMagia;

/// Prop�sito: Devuelve una escuela vac�a.
/// O(1)
EscuelaDeMagia fundarEscuela();

/// Prop�sito: Indica si la escuela est� vac�a.
/// O(1)
bool estaVacia(EscuelaDeMagia m);

/// Prop�sito: Incorpora un mago a la escuela (si ya existe no hace nada).
/// O(log m)
void registrar(string nombre, EscuelaDeMagia m);

/// Prop�sito: Devuelve los nombres de los magos registrados en la escuela.
/// O(m)
vector<string> magos(EscuelaDeMagia m);

/// Prop�sito: Devuelve los hechizos que conoce un mago dado.
/// Precondici�n: Existe un mago con dicho nombre.
/// O(log m)
Set hechizosDe(string nombre, EscuelaDeMagia m);

/// Prop�sito: Dado un mago, indica la cantidad de hechizos que la escuela ha dado y �l no sabe.
/// Precondici�n: Existe un mago con dicho nombre.
/// O(log m)
int leFaltanAprender(string nombre, EscuelaDeMagia m);

/// Prop�sito: Devuelve el mago que m�s hechizos sabe.
/// Precondici�n: La escuela no est� vac�a.
/// O(log m)
Mago unEgresado(EscuelaDeMagia m);

/// Prop�sito: Devuelve la escuela sin el mago que m�s sabe.
/// Precondici�n: La escuela no est� vac�a.
/// O(log m)
void quitarEgresado(EscuelaDeMagia m);

/// Prop�sito: Ense�a un hechizo a un mago existente, y si el hechizo no existe en la escuela es incorporado a la misma.
/// O(m . log m + log h)
void enseniar(Hechizo h, string nombre, EscuelaDeMagia m);

/// Prop�sito: Libera toda la memoria creada por la escuela (incluye magos, pero no hechizos).
void destruirEscuela(EscuelaDeMagia m);

#endif
