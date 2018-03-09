#include "../Comportamientos_Jugador/jugador.hpp"
#include <iostream>
#include <random>

using namespace std;

Action ComportamientoJugador::think(Sensores sensores) {
	Action accion = actIDLE;

	
	static unsigned int a = 0;
	if(a % 100 == 0)
		cerr << a << endl;
	a++;
	
	// En esta matriz de tamano 100x100 hay que escribir el mapa solucion
	// mapaResultado[fila][columna] = lo que hay en fila columna
	
	/*
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
		//ActualizarMemoria(sensores);

/************************************************POSICIONARSE*************************************************************/
	if(sensores.terreno[0] == 'K' && !bien_situado) {
		fil_ma = sensores.mensajeF;
		col_ma = sensores.mensajeC;
		bien_situado = true;
	}

/***********************************************DECISION******************************************************************/
	if(sensores.superficie[2] >= '0' && sensores.superficie[2] <= '3' && sensores.objetoActivo == '_') {
		accion = actPICKUP;
	}

	
	else if(sensores.superficie[2] == 'l' && sensores.objetoActivo == '0') {
		accion = actGIVE;
	}
/*
	else if(sensores.terreno[2] == 'D' && sensores.objetoActivo == '3' && !abierta) {
		accion = actGIVE;
		abierta = true;
	}


	else if(sensores.terreno[2] == 'D' && sensores.objetoActivo == '3' && abierta) {
		accion = actFORWARD;
		abierta = false;
	}
		
	else if((sensores.terreno[1] == 'D' || sensores.terreno[3] == 'D') && sensores.objetoActivo == '3'  && sensores.superficie[2] == '_' ) {
		accion = actFORWARD;
	}

	else if(puerta_encontrada_l) {
		puerta_encontrada_l=false;
		accion = actTURN_L;
	}

	else if(puerta_encontrada_r) {
		puerta_encontrada_r=false;
		accion = actTURN_R;
	}	

*/

	else if((sensores.terreno[2] == 'T' || sensores.terreno[2] =='S' || sensores.terreno[2] =='K') && sensores.superficie[2] == '_' && seguir_frente) {
		accion = actFORWARD;
	}

	else if (sensores.terreno[2] == 'A' && sensores.objetoActivo == '1' && sensores.superficie[2] == '_' && seguir_frente) {
		accion = actFORWARD;
	}

	else if(sensores.terreno[2] == 'B' && sensores.objetoActivo == '2' && sensores.superficie[2] == '_' && seguir_frente) {
		accion = actFORWARD;
	}

	else {
		accion =(girar_derecha)?actTURN_L:actTURN_R;
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

	if(sensores.reset) {
		brujula = 0;
		bien_situado = false;
		ultimaAccion = actIDLE;
		//BorrarMemoria();
		col_me = 99;
		col_me = 99;
		volcar = true;
	}

	puerta_encontrada_l=(sensores.terreno[1] == 'D') && sensores.objetoActivo == '3';
	puerta_encontrada_r=(sensores.terreno[3] == 'D') && sensores.objetoActivo == '3';

	switch (ultimaAccion) {
		case actFORWARD:
			switch(brujula) {
				case 0: --fil_ma; --fil_me;
				break; //N
				case 1: ++col_ma; ++col_me;
				break; //E
				case 2: ++fil_ma; ++fil_me;
				break; //S
				case 3: --col_ma; --col_me;
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

	seguir_frente = n<PROB_FRENTE;	//DISTRIBUCION UNIFORME PERMITE EL USO DE PROBABILIDAD REAL
	girar_derecha = (n%2 == 0);
}

void ComportamientoJugador::ActualizarMapa(const Sensores &sensores) {
	mapaResultado[fil_ma][col_ma] = sensores.terreno[0];
		
	switch(brujula) {
			case 0:
				mapaResultado[fil_ma-1][col_ma-1] = sensores.terreno[1];
				mapaResultado[fil_ma-1][col_ma] = sensores.terreno[2];
				mapaResultado[fil_ma-1][col_ma+1] = sensores.terreno[3];
				mapaResultado[fil_ma-2][col_ma-2] = sensores.terreno[4];
				mapaResultado[fil_ma-2][col_ma-1] = sensores.terreno[5];
				mapaResultado[fil_ma-2][col_ma] = sensores.terreno[6];
				mapaResultado[fil_ma-2][col_ma+1] = sensores.terreno[7];
				mapaResultado[fil_ma-2][col_ma+2] = sensores.terreno[8];
				mapaResultado[fil_ma-3][col_ma-3] = sensores.terreno[9];
				mapaResultado[fil_ma-3][col_ma-2] = sensores.terreno[10];
				mapaResultado[fil_ma-3][col_ma-1] = sensores.terreno[11];
				mapaResultado[fil_ma-3][col_ma] = sensores.terreno[12];
				mapaResultado[fil_ma-3][col_ma+1] = sensores.terreno[13];
				mapaResultado[fil_ma-3][col_ma+2] = sensores.terreno[14];
				mapaResultado[fil_ma-3][col_ma+3] = sensores.terreno[15];
				break;

			case 1:
				mapaResultado[fil_ma-1][col_ma+1] = sensores.terreno[1];
				mapaResultado[fil_ma][col_ma+1] = sensores.terreno[2];
				mapaResultado[fil_ma+1][col_ma+1] = sensores.terreno[3];
				mapaResultado[fil_ma-2][col_ma+2] = sensores.terreno[4];
				mapaResultado[fil_ma-1][col_ma+2] = sensores.terreno[5];
				mapaResultado[fil_ma][col_ma+2] = sensores.terreno[6];
				mapaResultado[fil_ma+1][col_ma+2] = sensores.terreno[7];
				mapaResultado[fil_ma+2][col_ma+2] = sensores.terreno[8];
				mapaResultado[fil_ma-3][col_ma+3] = sensores.terreno[9];
				mapaResultado[fil_ma-2][col_ma+3] = sensores.terreno[10];
				mapaResultado[fil_ma-1][col_ma+3] = sensores.terreno[11];
				mapaResultado[fil_ma][col_ma+3] = sensores.terreno[12];
				mapaResultado[fil_ma+1][col_ma+3] = sensores.terreno[13];
				mapaResultado[fil_ma+2][col_ma+3] = sensores.terreno[14];
				mapaResultado[fil_ma+3][col_ma+3] = sensores.terreno[15];
				break;

			case 2:
				mapaResultado[fil_ma+1][col_ma+1] = sensores.terreno[1];
				mapaResultado[fil_ma+1][col_ma] = sensores.terreno[2];
				mapaResultado[fil_ma+1][col_ma-1] = sensores.terreno[3];
				mapaResultado[fil_ma+2][col_ma+2] = sensores.terreno[4];
				mapaResultado[fil_ma+2][col_ma+1] = sensores.terreno[5];
				mapaResultado[fil_ma+2][col_ma] = sensores.terreno[6];
				mapaResultado[fil_ma+2][col_ma-1] = sensores.terreno[7];
				mapaResultado[fil_ma+2][col_ma-2] = sensores.terreno[8];
				mapaResultado[fil_ma+3][col_ma+3] = sensores.terreno[9];
				mapaResultado[fil_ma+3][col_ma+2] = sensores.terreno[10];
				mapaResultado[fil_ma+3][col_ma+1] = sensores.terreno[11];
				mapaResultado[fil_ma+3][col_ma] = sensores.terreno[12];
				mapaResultado[fil_ma+3][col_ma-1] = sensores.terreno[13];
				mapaResultado[fil_ma+3][col_ma-2] = sensores.terreno[14];
				mapaResultado[fil_ma+3][col_ma-3] = sensores.terreno[15];
				break;

			case 3:
				mapaResultado[fil_ma+1][col_ma-1] = sensores.terreno[1];
				mapaResultado[fil_ma][col_ma-1] = sensores.terreno[2];
				mapaResultado[fil_ma-1][col_ma-1] = sensores.terreno[3];
				mapaResultado[fil_ma+2][col_ma-2] = sensores.terreno[4];
				mapaResultado[fil_ma+1][col_ma-2] = sensores.terreno[5];
				mapaResultado[fil_ma][col_ma-2] = sensores.terreno[6];
				mapaResultado[fil_ma-1][col_ma-2] = sensores.terreno[7];
				mapaResultado[fil_ma-2][col_ma-2] = sensores.terreno[8];
				mapaResultado[fil_ma+3][col_ma-3] = sensores.terreno[9];
				mapaResultado[fil_ma+2][col_ma-3] = sensores.terreno[10];
				mapaResultado[fil_ma+1][col_ma-3] = sensores.terreno[11];
				mapaResultado[fil_ma][col_ma-3] = sensores.terreno[12];
				mapaResultado[fil_ma-1][col_ma-3] = sensores.terreno[13];
				mapaResultado[fil_ma-2][col_ma-3] = sensores.terreno[14];
				mapaResultado[fil_ma-3][col_ma-3] = sensores.terreno[15];
				break;
	}
}

void ComportamientoJugador::ActualizarMemoria(const Sensores &sensores) {
	memoria[fil_me][col_me] = sensores.terreno[0];
		
	switch(brujula) {
			case 0:
				memoria[fil_me-1][col_me-1] = sensores.terreno[1];
				memoria[fil_me-1][col_me] = sensores.terreno[2];
				memoria[fil_me-1][col_me+1] = sensores.terreno[3];
				memoria[fil_me-2][col_me-2] = sensores.terreno[4];
				memoria[fil_me-2][col_me-1] = sensores.terreno[5];
				memoria[fil_me-2][col_me] = sensores.terreno[6];
				memoria[fil_me-2][col_me+1] = sensores.terreno[7];
				memoria[fil_me-2][col_me+2] = sensores.terreno[8];
				memoria[fil_me-3][col_me-3] = sensores.terreno[9];
				memoria[fil_me-3][col_me-2] = sensores.terreno[10];
				memoria[fil_me-3][col_me-1] = sensores.terreno[11];
				memoria[fil_me-3][col_me] = sensores.terreno[12];
				memoria[fil_me-3][col_me+1] = sensores.terreno[13];
				memoria[fil_me-3][col_me+2] = sensores.terreno[14];
				memoria[fil_me-3][col_me+3] = sensores.terreno[15];
				break;

			case 1:
				memoria[fil_ma-1][col_me+1] = sensores.terreno[1];
				memoria[fil_me][col_me+1] = sensores.terreno[2];
				memoria[fil_me+1][col_me+1] = sensores.terreno[3];
				memoria[fil_me-2][col_me+2] = sensores.terreno[4];
				memoria[fil_me-1][col_me+2] = sensores.terreno[5];
				memoria[fil_me][col_me+2] = sensores.terreno[6];
				memoria[fil_me+1][col_me+2] = sensores.terreno[7];
				memoria[fil_me+2][col_me+2] = sensores.terreno[8];
				memoria[fil_me-3][col_me+3] = sensores.terreno[9];
				memoria[fil_me-2][col_me+3] = sensores.terreno[10];
				memoria[fil_me-1][col_me+3] = sensores.terreno[11];
				memoria[fil_me][col_me+3] = sensores.terreno[12];
				memoria[fil_me+1][col_me+3] = sensores.terreno[13];
				memoria[fil_me+2][col_me+3] = sensores.terreno[14];
				memoria[fil_me+3][col_me+3] = sensores.terreno[15];
				break;

			case 2:
				memoria[fil_me+1][col_me+1] = sensores.terreno[1];
				memoria[fil_me+1][col_me] = sensores.terreno[2];
				memoria[fil_me+1][col_me-1] = sensores.terreno[3];
				memoria[fil_me+2][col_me+2] = sensores.terreno[4];
				memoria[fil_me+2][col_me+1] = sensores.terreno[5];
				memoria[fil_me+2][col_me] = sensores.terreno[6];
				memoria[fil_me+2][col_me-1] = sensores.terreno[7];
				memoria[fil_me+2][col_me-2] = sensores.terreno[8];
				memoria[fil_me+3][col_me+3] = sensores.terreno[9];
				memoria[fil_me+3][col_me+2] = sensores.terreno[10];
				memoria[fil_me+3][col_me+1] = sensores.terreno[11];
				memoria[fil_me+3][col_me] = sensores.terreno[12];
				memoria[fil_me+3][col_me-1] = sensores.terreno[13];
				memoria[fil_me+3][col_me-2] = sensores.terreno[14];
				memoria[fil_me+3][col_me-3] = sensores.terreno[15];
				break;

			case 3:
				memoria[fil_me+1][col_me-1] = sensores.terreno[1];
				memoria[fil_me][col_me-1] = sensores.terreno[2];
				memoria[fil_me-1][col_me-1] = sensores.terreno[3];
				memoria[fil_me+2][col_me-2] = sensores.terreno[4];
				memoria[fil_me+1][col_me-2] = sensores.terreno[5];
				memoria[fil_me][col_me-2] = sensores.terreno[6];
				memoria[fil_me-1][col_me-2] = sensores.terreno[7];
				memoria[fil_me-2][col_me-2] = sensores.terreno[8];
				memoria[fil_me+3][col_me-3] = sensores.terreno[9];
				memoria[fil_me+2][col_me-3] = sensores.terreno[10];
				memoria[fil_me+1][col_me-3] = sensores.terreno[11];
				memoria[fil_me][col_me-3] = sensores.terreno[12];
				memoria[fil_me-1][col_me-3] = sensores.terreno[13];
				memoria[fil_me-2][col_me-3] = sensores.terreno[14];
				memoria[fil_me-3][col_me-3] = sensores.terreno[15];
				break;
	}
}

void ComportamientoJugador::VolcarMemoria() {
	unsigned int inc_f = fil_ma - fil_me;
	unsigned int inc_c = col_ma - col_me;
	
	for(unsigned int i=0; i < 100; ++i)
		for(unsigned int j=0; j < 100; ++j)
			if(mapaResultado[i][j] == '?')
				mapaResultado[i][j] = memoria[i-inc_f][j-inc_c];

}

void ComportamientoJugador::BorrarMemoria() {
	for(unsigned short i=0; i < TAM_MEMORIA; ++i)
		for(unsigned short j=0; j < TAM_MEMORIA; ++j)
			memoria[i][j] = '?';
}

