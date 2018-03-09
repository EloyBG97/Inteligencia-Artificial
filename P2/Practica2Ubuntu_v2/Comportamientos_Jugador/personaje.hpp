#ifndef COMPORTAMIENTOPERSONAJE_H
#define COMPORTAMIENTOPERSONAJE_H

#include "comportamientos/comportamiento.hpp"

class ComportamientoPersonaje : public Comportamiento{

  public:
    ComportamientoPersonaje(unsigned int size = 0) : Comportamiento(size){
      paso=0;
    }
    ComportamientoPersonaje(const ComportamientoPersonaje & comport) : Comportamiento(comport){}
    ~ComportamientoPersonaje(){}

    Action think(const Sensores &sensores);

    int interact(const Action &accion, const int &valor) const;


    ComportamientoPersonaje * clone(){return new ComportamientoPersonaje(*this);}

  private:
    int paso;

};



#endif
