#ifndef COMPORTAMIENTOPUERTA_H
#define COMPORTAMIENTOPUERTA_H

#include "comportamientos/comportamiento.hpp"

class ComportamientoPuerta : public Comportamiento{

  public:
    ComportamientoPuerta(unsigned int size = 0) : Comportamiento(size){}
    ComportamientoPuerta(const ComportamientoPuerta & comport) : Comportamiento(comport){}
    ~ComportamientoPuerta(){}

    Action think(const Sensores &sensores);

    int interact(const Action &accion, const int &valor) const;


    ComportamientoPuerta * clone(){return new ComportamientoPuerta(*this);}
};


#endif
