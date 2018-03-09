#include "../Comportamientos_Jugador/jugador.hpp"
#include <random>
#include <iostream>
#include <omp.h>

using namespace std;

Action ComportamientoJugador::think(Sensores sensores) {
	//PARALELISMO
	Action accion = actIDLE;

	/*
	// En esta matriz de tamano 100x100 hay que escribir el mapa solucion
	// mapaResultado[fila][columna] = lo que hay en fila columna
	
	cout << "\nTerreno: ";
	for (int i=0; i<sensores.terreno.size(); i++)
		cout << sensores.terreno[i];
	cout << endl;

	cout << "Superficie: ";
	for (int i=0; i<sensores.superficie.size(); i++)
		cout << sensores.superficie[i];
	cout << endl;

	cout << "Colisión: " << sensores.colision << endl;
	cout << "Mochila: " << sensores.mochila << endl;
	cout << "Reset: " << sensores.reset << endl;
	cout << "Vida: " << sensores.vida << endl;
	cout << "objetoActivo: " << sensores.objetoActivo << endl;
	cout << "Situado: " << bien_situado << endl;
	cout << endl;
	*/

/*********************************************ACTUALIZAR ESTADO **********************************************************/	
	ActualizarVariables(sensores);

			if(bien_situado) {
				//if(volcar) {
					//VolcarMemoria();
					//volcar = false;
				//}
				
				ActualizarMapa(sensores);
			}

			//else
				//ActualizarMemoria(sensores);*/
		
	

/***********************************************DECISION******************************************************************/
	
			if(sensores.superficie[2] >= '0' && sensores.superficie[2] <= '3' && sensores.objetoActivo == '_') {
				accion = actPICKUP;
			}

	
			else if(sensores.superficie[2] == 'l' && sensores.objetoActivo == '0') {
				accion = actGIVE;
	
			}

			//PUERTA

			else if((sensores.terreno[2] == 'T' || sensores.terreno[2] =='S' || sensores.terreno[2] =='K')&& sensores.superficie[2] == '_' && seguir_frente) {
				accion = actFORWARD;
			}

			else if (sensores.terreno[2] == 'A' && sensores.objetoActivo == '1' && sensores.superficie[2] == '_' && seguir_frente) {
				accion = actFORWARD;
			}

			else if(sensores.terreno[2] == 'B' && sensores.objetoActivo == '2' && sensores.superficie[2] == '_' && seguir_frente) {
				accion = actFORWARD;
			}

			else {
				accion = (girar_derecha)?actTURN_R:actTURN_L;
			}	

			ultimaAccion = accion;

	return accion;
}

int ComportamientoJugador::interact(Action accion, int valor){
  return false;
}

void ComportamientoJugador::ActualizarVariables(const Sensores &sensores) {
			
			random_device rd;
			mt19937 gen(rd());
			uniform_int_distribution<int> distribucion(0,100);
			int n = distribucion(gen);

			//¿DESCUBIERTO EL FRENTE?
			//bool descubierto;

			seguir_frente = n<PROB_FRENTE; //&& !descubierto;	//DISTRIBUCION UNIFORME PERMITE EL USO DE PROBABILIDAD REAL
			girar_derecha = (n & 1 == 0);


		
			if(sensores.reset) {
				brujula = 0;
				bien_situado = false;
				ultimaAccion = actIDLE;
				//BorrarMemoria();
				col_me = 99;
				col_me = 99;
				volcar = true;
			}
		
			switch (ultimaAccion) {
				case actFORWARD:
					switch(brujula) {
						case 0: --fil_ma;//--fil_me;
						break; //N
						case 1: ++col_ma;// ++col_me;
						break; //E
						case 2: ++fil_ma;// ++fil_me;
						break; //S
						case 3: --col_ma; //--col_me;
						break; //O
					}
					break;

				case actTURN_L:
					brujula = (brujula + 3) & 3; // (brujula+3)%4
					break;

				case actTURN_R:
					brujula = (brujula + 1) & 3; // (brujula+1)%4
					break;
			}
			
			/************************************************POSICIONARSE*************************************************************/
			
			if(sensores.terreno[0] == 'K' && !bien_situado) {
				fil_ma = sensores.mensajeF;
				col_ma = sensores.mensajeC;
				bien_situado = true;
			}

}

void ComportamientoJugador::ActualizarMapa(const Sensores &sensores) {
	int k = 0;
	mapaResultado[fil_ma][col_ma] = sensores.terreno[k++];
		
	switch(brujula) {
			case 0:
				for(int i=1; i <=3; ++i)
					for(int j=-i; j <= i; ++j) 
						mapaResultado[fil_ma-i][col_ma+j] = sensores.terreno[k++];
			break;

			case 1:
				for(int i=1; i <=3; ++i)
					for(int j=-i; j <= i; ++j)
						mapaResultado[fil_ma+j][col_ma+i] = sensores.terreno[k++];
			break;

			case 2:
				for(int i=1; i <=3; ++i)
					for(int j=-i; j <= i; ++j)
						mapaResultado[fil_ma+i][col_ma-j] = sensores.terreno[k++];			
			break;

			case 3:
				for(int i=1; i <=3; ++i)
					for(int j=-i; j <= i; ++j)
						mapaResultado[fil_ma-j][col_ma-i] = sensores.terreno[k++];				
			break;
	}

}

/*
void ComportamientoJugador::ActualizarMemoria(const Sensores &sensores) {
	int k = 0;
	memoria[fil_me][col_me] = sensores.terreno[k++];
		
	//PARALELISMO
	switch(brujula) {
			case 0:
				for(int i=1; i <=3; ++i)
					for(int j=-i; j <= i; ++j) 
						memoria[fil_me-i][col_me+j] = sensores.terreno[k++];
			break;

			case 1:
				for(int i=1; i <=3; ++i)
					for(int j=-i; j <= i; ++j)
						memoria[fil_me+j][col_me+i] = sensores.terreno[k++];			
				break;

			case 2:
				for(int i=1; i <=3; ++i)
					for(int j=-i; j <= i; ++j)
						memoria[fil_me+i][col_me-j] = sensores.terreno[k++];
			break;

			case 3:
				for(int i=1; i <=3; ++i)
					for(int j=-i; j <= i; ++j)
						memoria[fil_ma-j][col_ma-i] = sensores.terreno[k++];
			break;
	}
}

void ComportamientoJugador::VolcarMemoria() {
	short inc_f = fil_ma - fil_me;
	short inc_c = col_ma - col_me;

	for(short i=0; i < 100; ++i)
		for(short j=0; j < 100; ++j)
			if(mapaResultado[i][j] == '?')
				mapaResultado[i][j] = memoria[i-inc_f][j-inc_c];
}

void ComportamientoJugador::BorrarMemoria() {

	for(typename ComportamientoJugador::size_type i=0; i < TAM_MEMORIA; ++i)
		for(typename ComportamientoJugador::size_type j=0; j < TAM_MEMORIA; ++j)
			memoria[i][j] = '?';
}
*/
