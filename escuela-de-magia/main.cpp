#include <iostream>
#include <cstdlib>
#include <vector>
#include "../hechizo/hechizo.h"
#include "../mago/mago.h"
#include "../set/set.h"
#include "../map/map.h"
#include "../maxheap/maxheap.h"
#include "escuela_magia.h"
#include "../common/Common.h"

using namespace std;

/// Proposito: Retorna todos los hechizos aprendidos por los magos.
/// Eficiencia: ? O(log n^2)

Set hechizosAprendidos(EscuelaDeMagia m) {
    Set hechizosADevolver = emptyS();
    for(string nombre: magos(m)){
       hechizosADevolver =  unionS(hechizosDe(nombre,m),hechizosADevolver);
    }
    return hechizosADevolver;
}

/// Proposito: Indica si existe un mago que sabe todos los hechizos enseñados por la escuela.
/// Eficiencia: O(log M)
bool hayUnExperto(EscuelaDeMagia m) {
   return (leFaltanAprender(nombreMago(unEgresado(m)),m)== 0);
}

/// Proposito: Devuelve una maxheap con los magos que saben todos los hechizos dados por la escuela, quitándolos de la escuela.
/// Eficiencia: O(log M^2)
MaxHeap egresarExpertos(EscuelaDeMagia m) {
    MaxHeap egresados = emptyH();
    while(hayUnExperto(m)){
        insertH(unEgresado(m),egresados);
        quitarEgresado(m);
    }
    return egresados;
}

int main()
{
    /// Escribir algunas pruebas para las funciones de la interfaz
    /// de escuela de magia, y también las de usuario.

/***************************** Tests de Escuela De Magia *****************************/

    ///Se crea una escuela vacia
    EscuelaDeMagia escuelaVacia = fundarEscuela();

    if(estaVacia(escuelaVacia)){
    cout<<"testEscuelaEstaVacia = TEST OK"<<endl;
    }
    else{
    cout<<"testEscuelaEstaVacia = TEST FALLO"<<endl;
    }

    ///Se agregan tres alumnos a la escuela
   EscuelaDeMagia school1 = fundarEscuela();

    registrar("Jaco",school1);
    registrar("Report",school1);
    registrar("Town",school1);

    if(!estaVacia(school1)){
    cout<<"testEscuelaNOEstaVacia = TEST OK"<<endl;
    }
    else{
    cout<<"testEscuelaEstaVacia = TEST FALLO"<<endl;
    }




    ///La cantidad de hechizos del mago "Jaco" son (3)
    EscuelaDeMagia school2 = fundarEscuela();

    Hechizo h1 = crearHechizo("Q",80);
    Hechizo h2 = crearHechizo("W",70);
    Hechizo h3 = crearHechizo("E",60);

    registrar("Jaco",school2);

    enseniar(h1,"Jaco",school2);
    enseniar(h2,"Jaco",school2);
    enseniar(h3,"Jaco",school2);

    if(sizeS(hechizosDe("Jaco",school2))== 3){
    cout<<"testCantidadDeHechizosDeJaco = TEST OK"<<endl;
    }
    else{
    cout<<"testCantidadDeHechizosDeJaco = TEST FALLO"<<endl;
    }

    ///La cantidad de hechizos que le faltan aprender a Report es (1)
    EscuelaDeMagia school3 = fundarEscuela();

    Hechizo h11 = crearHechizo("Q",80);
    Hechizo h22 = crearHechizo("W",70);
    Hechizo h33 = crearHechizo("E",60);
    Hechizo h44 = crearHechizo("R",40);

    registrar("Jaco",school3);
    registrar("Report",school3);
    registrar("Town",school3);

    enseniar(h11,"Jaco",school3);
    enseniar(h11,"Report",school3);
    enseniar(h22,"Report",school3);
    enseniar(h33,"Report",school3);
    enseniar(h44,"Town",school3);

    if(leFaltanAprender("Report",school3)==1){
    cout<<"testCantidadDeHechizosQueLeFaltanAprender = TEST OK"<<endl;
    }
    else{
    cout<<"testCantidadDeHechizosQueLeFaltanAprender = TEST FALLO"<<endl;
    }

    ///El egresado es Report

    EscuelaDeMagia school4 = fundarEscuela();

    Hechizo h111 = crearHechizo("Q",80);
    Hechizo h222 = crearHechizo("W",70);
    Hechizo h333 = crearHechizo("E",60);
    Hechizo h444 = crearHechizo("R",40);

    registrar("Jaco",school4);
    registrar("Report",school4);
    registrar("Town",school4);

    enseniar(h111,"Jaco",school4);
    enseniar(h111,"Report",school4);
    enseniar(h222,"Report",school4);
    enseniar(h333,"Report",school4);
    enseniar(h444,"Town",school4);

    if(nombreMago(unEgresado(school4))== "Report"){
    cout<<"testElEgresadoEsReport = TEST OK"<<endl;
    }
    else{
    cout<<"testElEgresadoEsReport = TEST FALLO"<<endl;
    }


    ///La cantidad de hechizos aprendidos por los magos es 3
    EscuelaDeMagia school5 = fundarEscuela();

    Hechizo h123 = crearHechizo("Q",80);
    Hechizo h234 = crearHechizo("W",70);
    Hechizo h345 = crearHechizo("E",60);

    registrar("Jaco",school5);
    registrar("Hola",school5);
    registrar("Chau",school5);

    enseniar(h123,"Hola",school5);
    enseniar(h234,"Jaco",school5);
    enseniar(h345,"Chau",school5);

    if(sizeS(hechizosAprendidos(school5))==3){
    cout<<"testLaCantidadDeHechizosAprendidosEsTres = TEST OK"<<endl;
    }
    else{
    cout<<"testLaCantidadDeHechizosAprendidosEsTres = TEST FALLO"<<endl;
    }



    ///Test se quita al mago que mas sabe
   EscuelaDeMagia escuela6 = fundarEscuela();

    Hechizo h109 = crearHechizo("h1",2);
    Hechizo h110 = crearHechizo("h2",4);

    registrar("pepe",escuela6);
    registrar("lenny",escuela6);

    enseniar(h109,"pepe",escuela6);
    enseniar(h110,"pepe",escuela6);
    enseniar(h109,"lenny",escuela6);

    quitarEgresado(escuela6);

    if(magos(escuela6).size()==1){
    cout<<"testSeSacaAlMagoQueMasSabe = TEST OK"<<endl;
    }
    else{
    cout<<"testSeSacaAlMagoQueMasSabe = TEST FALLO"<<endl;
    }

    ///Test hay un experto en la escuela
   EscuelaDeMagia school7 = fundarEscuela();

    Hechizo h50 = crearHechizo("Q",80);
    Hechizo h51 = crearHechizo("W",70);
    Hechizo h52 = crearHechizo("E",60);

    registrar("Jaco",school7);
    registrar("Hola",school7);
    registrar("Chau",school7);

    enseniar(h50,"Hola",school7);
    enseniar(h50,"Jaco",school7);
    enseniar(h51,"Jaco",school7);
    enseniar(h52,"Jaco",school7);
    enseniar(h52,"Chau",school7);

    if(hayUnExperto(school7)){
   cout<<"testHayUnExpertoEnLaEscuela = TEST OK"<<endl;
    }
    else{
    cout<<"testHayUnExpertoEnLaEscuela = TEST FALLO"<<endl;
    }

    ///La escuela tiene a 2 egresados
    EscuelaDeMagia school8 = fundarEscuela();

    Hechizo hA = crearHechizo("Q",80);
    Hechizo hB = crearHechizo("W",70);
    Hechizo hC = crearHechizo("E",60);

    registrar("Jaco",school8);
    registrar("Hola",school8);
    registrar("Chau",school8);

    enseniar(hA,"Hola",school8);

    enseniar(hA,"Jaco",school8);
    enseniar(hB,"Jaco",school8);
    enseniar(hC,"Jaco",school8);

    enseniar(hC,"Chau",school8);
    enseniar(hA,"Chau",school8);
    enseniar(hB,"Chau",school8);


    if(sizeH(egresarExpertos(school8))){
   cout<<"testCantidadDeExpertosEnLaEscuela = TEST OK"<<endl;
    }
    else{
    cout<<"testCantidadDeExpertosEnLaEscuela = TEST FALLO"<<endl;
    }


    return 0;
}
