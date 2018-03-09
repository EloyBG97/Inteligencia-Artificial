#ifndef COMPORTAMIENTOALDEANO_H
#define COMPORTAMIENTOALDEANO_H

#include "comportamientos/comportamiento.hpp"

class ComportamientoAldeano : public Comportamiento{

  public:
    ComportamientoAldeano(unsigned int size = 0) : Comportamiento(size){
      paso=0;
    }
    ComportamientoAldeano(const ComportamientoAldeano & comport) : Comportamiento(comport){}
    ~ComportamientoAldeano(){}

    Action think(const Sensores &sensores);

    int interact(const Action &accion, const int &valor) const;


    ComportamientoAldeano * clone(){return new ComportamientoAldeano(*this);}

  private:
    int paso;

};



#endif
