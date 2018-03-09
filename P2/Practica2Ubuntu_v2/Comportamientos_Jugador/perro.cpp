#include "../Comportamientos_Jugador/perro.hpp"


#include <iostream>
#include <stdlib.h>

int aleatorio4(int tope){
  double a = random(), c = RAND_MAX;
  a = a / (c+1);
  int b = a*(tope+1);
  return b;
}


Action ComportamientoPerro::think(const Sensores &sensores){
// Las unicas acciones que pueden realizar son {actFORWARD, actTURN_L, actTURN_R, actIDLE}
// "sensores.lobos" es un vector de pares que inidica las coordenadas (fil,col) de todos los lobos
// "sensores.fil" y "sensores.col" contiene su fila y su columna actual.


  switch (aleatorio4(3)) {
    case 0:
      return actIDLE;
    break;

    case 1:
      return actFORWARD;
    break;

    case 2:
      return actTURN_L;
    break;

    case 3:
      return actTURN_R;
    break;
  }


}

int ComportamientoPerro::interact(const Action &accion, const int &valor) const {
  if(accion == actGIVE or accion == actTHROW)
      return (valor == '0')?1:0;
  
  else
    return 0;

}
