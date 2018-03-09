#include "comportamientos/objeto.hpp"

#include <random>


#include <iostream>



Action ComportamientoObjeto::think(const Sensores &sensores){
  return actIDLE;
}


int ComportamientoObjeto::interact(const Action &accion, const int &valor) const{

  if(accion == actPICKUP){
    return 2;
  }
  else{
    if(accion == actPUTDOWN){
      return 3;
    }
    else{
          return 0;
    }
  }
}
