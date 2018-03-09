#ifndef COMPORTAMIENTOJUGADOR_H
#define COMPORTAMIENTOJUGADOR_H

#include "comportamientos/comportamiento.hpp"


using namespace std;

class ComportamientoJugador : public Comportamiento{

  public:
	typedef unsigned short size_type;
	
    ComportamientoJugador(unsigned int size) :Comportamiento(size) {

		col_ma = 99;
		fil_ma = 99;
		brujula = 0;
		ultimaAccion = actIDLE;
		girar_derecha = false;
		bien_situado = false;
		seguir_frente = false;
	
		col_me = (TAM_MEMORIA/2)-1;
		fil_me = (TAM_MEMORIA/2)-1;
		volcar = true;

		memoria = new char* [TAM_MEMORIA];
		for(size_type i=0; i < TAM_MEMORIA; ++i) {
			memoria[i] = new char [TAM_MEMORIA];
			for(size_type j=0; j < TAM_MEMORIA; ++j)
				memoria[i][j] = '?';
		}
	}

    ComportamientoJugador(const ComportamientoJugador & comport) : Comportamiento(comport){
		col_ma = comport.col_ma;
		fil_ma = comport.fil_ma;
		brujula = comport.brujula;
		ultimaAccion = comport.ultimaAccion;
		girar_derecha = comport.girar_derecha;
		bien_situado = comport.bien_situado;
		seguir_frente = comport.seguir_frente;

		col_me = comport.col_me;
		fil_me = comport.fil_me;
		volcar = comport.volcar;

		memoria = new char* [TAM_MEMORIA];
		for(size_type i=0; i < TAM_MEMORIA; ++i) {
			memoria[i] = new char [TAM_MEMORIA];
			for(size_type j=0; j < TAM_MEMORIA; ++j)
				memoria[i][j] = comport.memoria[i][j];
		}
		
	}

    ~ComportamientoJugador() {
		for(size_type i=0; i < TAM_MEMORIA; ++i)
			delete [] memoria[i];
		delete [] memoria;
	}

    Action think(Sensores sensores);

    int interact(Action accion, int valor);


    ComportamientoJugador * clone(){return new ComportamientoJugador(*this);}


  private:
		static const size_type PROB_FRENTE = 95;
		static const size_type TAM_MEMORIA = 200;
		
		bool girar_derecha,bien_situado,seguir_frente, volcar;

		size_type brujula,fil_ma,col_ma, fil_me,col_me;

		Action ultimaAccion;

		char **memoria;

		void ActualizarVariables(const Sensores &sensores);
		void ActualizarMapa(const Sensores &sensores);
		void VolcarMemoria();
		void ActualizarMemoria(const Sensores &sensores);
		void BorrarMemoria();
};


#endif
