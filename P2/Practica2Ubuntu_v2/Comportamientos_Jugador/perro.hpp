#ifndef COMPORTAMIENTOPERRO_H
#define COMPORTAMIENTOPERRO_H

#include "comportamientos/comportamiento.hpp"

class ComportamientoPerro : public Comportamiento{

  public:
    ComportamientoPerro(unsigned int size = 0) : Comportamiento(size){}
    ComportamientoPerro(const ComportamientoPerro & comport) : Comportamiento(comport){}
    ~ComportamientoPerro(){}

    Action think(const Sensores &sensores);

    int interact(const Action &accion, const int &valor) const;


    ComportamientoPerro * clone(){return new ComportamientoPerro(*this);}

  private:
    // Esta es la unica variable static que se puede declarar
    static unsigned char ladrido;

    // El resto de variables de Estado
    
};



#endif
