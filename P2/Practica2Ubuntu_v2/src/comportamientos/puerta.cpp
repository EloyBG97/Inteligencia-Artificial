#include "comportamientos/puerta.hpp"

#include <random>


#include <iostream>



Action ComportamientoPuerta::think(const Sensores &sensores){
  return actIDLE;
}


int ComportamientoPuerta::interact(const Action &accion, const int &valor) const{
  if(accion == actGIVE){
    if(valor == '3'){

      return 1;
    }
    else{
      return 0;
    }
  }
  else{
    return 0;
  }
}
