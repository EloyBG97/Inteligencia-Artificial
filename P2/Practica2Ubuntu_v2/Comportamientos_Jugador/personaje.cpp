#include "../Comportamientos_Jugador/personaje.hpp"


Action ComportamientoPersonaje::think(const Sensores &sensores){
  Action accion;
  ++paso;

  switch (paso%7){
      case 0: accion = actTURN_R;
              break;
      case 4: accion = actTURN_L;
      		  break;
  }
  return accion;
}

int ComportamientoPersonaje::interact(const Action &accion, const int &valor) const{
  if(accion == actGIVE or accion == actTHROW)
      return (valor == '4')?4:0;

  else
    return 0;
  
}
