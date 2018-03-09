#ifndef COMPORTAMIENTOOBJETO_H
#define COMPORTAMIENTOOBJETO_H

#include "comportamientos/comportamiento.hpp"

class ComportamientoObjeto : public Comportamiento{

  public:
    ComportamientoObjeto(unsigned int size = 0) : Comportamiento(size){}
    ComportamientoObjeto(const ComportamientoObjeto & comport) : Comportamiento(comport){}
    ~ComportamientoObjeto(){}

    Action think(const Sensores &sensores);

    int interact(const Action &accion, const int &valor) const;


    ComportamientoObjeto * clone(){return new ComportamientoObjeto(*this);}
};


#endif
