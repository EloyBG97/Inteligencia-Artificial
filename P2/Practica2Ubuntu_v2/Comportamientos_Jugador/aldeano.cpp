#include "../Comportamientos_Jugador/aldeano.hpp"


Action ComportamientoAldeano::think(const Sensores &sensores){
  paso = (paso+1) & 1;
  
  return (paso==1)?actFORWARD:actTURN_R;
}

int ComportamientoAldeano::interact(const Action &accion, const int &valor) const{
    return 0;
}
