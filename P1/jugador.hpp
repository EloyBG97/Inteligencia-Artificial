#ifndef COMPORTAMIENTOJUGADOR_H
#define COMPORTAMIENTOJUGADOR_H

#include "comportamientos/comportamiento.hpp"


using namespace std;

class ComportamientoJugador : public Comportamiento{

  public:
    ComportamientoJugador(unsigned int size) :Comportamiento(size) {

		col_ma = 99;
		fil_ma = 99;
		col_me = 99;
		fil_me = 99;
		brujula = 0;
		ultimaAccion = actIDLE;
		girar_derecha = false;
		bien_situado = false;
		puerta_encontrada_l = false;
		puerta_encontrada_r = false;
		seguir_frente = false;
		volcar = true;
		abierta = false;

		memoria = new char* [TAM_MEMORIA];
		for(unsigned short i=0; i < TAM_MEMORIA; ++i) {
			memoria[i] = new char [TAM_MEMORIA];
			for(unsigned short j=0; j < TAM_MEMORIA; ++j)
				memoria[i][j] = '?';
		}
	}

    ComportamientoJugador(const ComportamientoJugador & comport) : Comportamiento(comport){
		col_ma = comport.col_ma;
		fil_ma = comport.fil_ma;
		col_me = comport.col_me;
		fil_me = comport.fil_me;
		brujula = comport.brujula;
		ultimaAccion = comport.ultimaAccion;
		girar_derecha = comport.girar_derecha;
		bien_situado = comport.bien_situado;
		puerta_encontrada_l = comport.puerta_encontrada_l;
		puerta_encontrada_r = comport.puerta_encontrada_r;
		seguir_frente = comport.seguir_frente;
		volcar = comport.volcar;
		abierta = comport.abierta;

		memoria = new char* [TAM_MEMORIA];
		for(unsigned short i=0; i < TAM_MEMORIA; ++i) {
			memoria[i] = new char [TAM_MEMORIA];
			for(unsigned short j=0; j < TAM_MEMORIA; ++j)
				memoria[i][j] = comport.memoria[i][j];
		}
	}

    ~ComportamientoJugador() {
		for(unsigned short i=0; i < TAM_MEMORIA; ++i)
			delete [] memoria[i];
		delete [] memoria;
	}

    Action think(Sensores sensores);

    int interact(Action accion, int valor);


    ComportamientoJugador * clone(){return new ComportamientoJugador(*this);}


  private:
		static const unsigned short PROB_FRENTE = 95;
		static const unsigned short TAM_MEMORIA = 200;
	
		int fil_ma,col_ma,fil_me,col_me;
		unsigned int brujula;
		Action ultimaAccion;
		bool girar_derecha,bien_situado,seguir_frente,puerta_encontrada_l,puerta_encontrada_r,volcar,abierta;
		char **memoria;

		void ActualizarVariables(const Sensores &sensores);
		void ActualizarMapa(const Sensores &sensores);
		void VolcarMemoria();
		void ActualizarMemoria(const Sensores &sensores);
		void BorrarMemoria();
};


#endif
