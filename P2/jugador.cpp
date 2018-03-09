#include "../Comportamientos_Jugador/jugador.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


class OrdenarNodo {
	public:
		bool operator()(const ComportamientoJugador::nodo &n1,const ComportamientoJugador::nodo &n2) {
			return n1 < n2;
		}
};

/***************************************************************AUXILIARES DE ESTADO ***************************************************************/
typename ComportamientoJugador::nodo& ComportamientoJugador::nodo::operator=(const ComportamientoJugador::nodo &n) {
	if(!(*this == n)) {
		costo = n.costo;
		st.fila = n.st.fila;
		st.columna = n.st.columna;
		st.orientacion = n.st.orientacion;
		padre = n.padre;
	
		for(unsigned short i=0;i<3;++i)
			hijos[i] = n.hijos[i];
	}
	
	return *this;
}

ComportamientoJugador::nodo::nodo() {
	costo = 0;
	st.fila = 0;
	st.columna = 0;
	st.orientacion = 0;
	padre = NULL;
	
	for(unsigned short i=0;i<3;++i)
		hijos[i] = NULL;
}
bool ComportamientoJugador::nodo::operator==(const ComportamientoJugador::nodo &n) const {
	return st == n.st;
}

bool ComportamientoJugador::nodo::estado::operator==(const ComportamientoJugador::nodo::estado &st) const {
	return (fila == st.fila && columna == st.columna && orientacion == st.orientacion);
}

bool ComportamientoJugador::nodo::operator<(const ComportamientoJugador::nodo &n1) const{
	return costo < n1.costo;
}

void ComportamientoJugador::nodo::ExpandirNodo(const Action &accion) {
	typename ComportamientoJugador::nodo n1;
		
	n1.costo = costo+1;
	n1.accion = accion;
	n1.padre = this;
	
	n1.st.orientacion = st.orientacion;
	
	switch (accion) {
		case actFORWARD:
				switch(n1.st.orientacion) {
					case 0: --n1.st.fila;
					break; //N

					case 1: ++n1.st.columna;
					break; //E
				
					case 2: ++n1.st.fila;
					break; //S

					case 3: --n1.st.columna;
					break; //O
				}
			hijos[0] = &n1;
			break;

		case actTURN_L:
			n1.st.orientacion = (n1.st.orientacion + 3) & 3; // (1.st.orientacion+3)%4
			hijos[1] = &n1;	
			break;

		case actTURN_R:
			n1.st.orientacion = (n1.st.orientacion + 1) & 3; // (1.st.orientacion+1)%4
			hijos[2] = &n1;	
			break;
	}

}

list<Action> ComportamientoJugador::FormarPlan(ComportamientoJugador::nodo &n) const {
	list<Action> plan;
	
	while(n.padre != NULL) {
		plan.push_back(n.accion);
		n = *n.padre;
	}
	
	return plan;
}
	
/*************************************************PATH FINDING******************************************************************************************/
bool ComportamientoJugador::CostoUniforme(nodo n, const nodo &destino, list<Action> &plan) const {
	cerr << (n < n);

	list<typename ComportamientoJugador::nodo> frontier;
	vector<typename ComportamientoJugador::nodo> explored;
	typename list<typename ComportamientoJugador::nodo>::iterator it;
	
	frontier.push_back(n);
	
	
	while(!frontier.empty()) {
		n = *frontier.begin();;
		frontier.pop_front();
		
		if(n == destino) {
			plan = FormarPlan(n);
			return true;
		}
		
		for(unsigned short i=0;i<3;++i) {
			switch (i) {
				case 0:
					n.ExpandirNodo(actFORWARD);
					break;

				case 1:
					n.ExpandirNodo(actTURN_L);
					break;

				case 2:
					n.ExpandirNodo(actTURN_L);
					break;
			}
		
			if(find(explored.begin(),explored.end(),*n.hijos[i]) == explored.end() && find(frontier.begin(),frontier.end(),*n.hijos[i]) == frontier.end())
				frontier.push_back(*n.hijos[i]);
			else if((*(it=find(frontier.begin(),frontier.end(),*n.hijos[i]))).costo > n.hijos[i]->costo) {
				frontier.erase(it);
				frontier.push_back(*n.hijos[i]);
			}
		}
		
		frontier.sort(OrdenarNodo());
		
	}
	
	
	return false;
}
/*
//SIMULAR ARBOL DE ESTADOS CON FUNCION RECURSIVA (CONVERTIR A ITERATIVA PARA MAS EFICIENCIA)
bool ComportamientoJugador::pathFinding(const estado &origen, const estado &destino, list<Action> &plan){

	//Borro la lista
	plan.clear();
	estado st = origen;

	typename ComportamientoJugador::size_type difF = origen.fila - destino.fila;
	typename ComportamientoJugador::size_type difC = origen.columna - destino.columna;

	// Reduzco la distancia en columnas
	if (difC < 0){
		if (st.orientacion == 0){
			plan.push_back(actTURN_R);
			st.orientacion = 1;
		}
	
		else if (st.orientacion == 3){
			plan.push_back(actTURN_R);
			plan.push_back(actTURN_R);
			st.orientacion = 1;
		}

		else if (st.orientacion == 2){
			plan.push_back(actTURN_L);
			st.orientacion = 1;
		}
	}

	else if (difC > 0){
		if (st.orientacion == 0){
			plan.push_back(actTURN_L);
			st.orientacion = 3;
		}

		else if (st.orientacion == 1){
			plan.push_back(actTURN_R);
			plan.push_back(actTURN_R);
			st.orientacion = 3;
		}

		else if (st.orientacion == 2){
			plan.push_back(actTURN_R);
			st.orientacion = 3;
		}
	}

	// Avanzo la diferencia entre columnas
	if (difC<0)
		difC = -difC;

	for (typename ComportamientoJugador::size_type i=0; i < difC; i++){
		plan.push_back(actFORWARD);
	}

	// Reduzco la distancia en filas
	if (difF < 0){
		if (st.orientacion == 1){
			plan.push_back(actTURN_R);
			st.orientacion = 2;
		}
	
		else if (st.orientacion == 3){
			plan.push_back(actTURN_L);
			st.orientacion = 2;
		}
	}

	else if (difF > 0){
		if (st.orientacion == 1){
			plan.push_back(actTURN_L);
			st.orientacion = 0;
		}

		else if (st.orientacion == 3){
			plan.push_back(actTURN_R);
			st.orientacion = 0;
		}
	}

	// Avanzo la diferencia entre filas
	if (difF<0)
		difF = -difF;

	for (typename ComportamientoJugador::size_type i=0; i < difF; i++){
		plan.push_back(actFORWARD);
	}

	return true;
}
*/

void ComportamientoJugador::Reiniciar(){
	fil_ma = col_ma = 99;
	fil_me = col_me = 99;
	bien_situado = false;
	brujula = 0;
	tengo_regalo = false;
	error_plan =true;
	estoy_ejecutando_plan = false;
	BorrarMemoria();
	volcar = true;
}

inline bool hayObstaculoDelante(const vector<unsigned char> & terreno, const vector<unsigned char> & superficie){
	return !((terreno[2]=='T' || terreno[2]=='S' || terreno[2]=='K') && superficie[2]=='_');

}

void PintaPlan(const list<Action> &plan){
	auto it = plan.begin();
	while (it!=plan.end()){
		switch(*it) {
			case actFORWARD:
				cout << "A ";
				break;
			
			case actTURN_R:
				cout << "D ";
				break;
				
			case actTURN_L:
				cout << "I ";
				break;
			
			default:
				cout << "- ";
				break;
		}
		++it;
	}
	cout << endl;
}


Action ComportamientoJugador::think(const Sensores &sensores){
	Action accion;

	// Actualización de la información del mundo
	ActualizarVariables(sensores);

	if(bien_situado) {
		if(volcar) {
			VolcarMemoria();
			volcar = false;
		}
		
		ActualizarMapa(sensores);
	}

	else
		ActualizarMemoria(sensores);

	if (sensores.terreno[0]=='K' && !bien_situado){
		fil_ma = sensores.mensajeF;
		col_ma = sensores.mensajeC;
		bien_situado = true;
	}

	if (bien_situado && tengo_regalo && !estoy_ejecutando_plan && sensores.regalos.size()>0){
		typename ComportamientoJugador::nodo origen;
		origen.st.fila = fil_ma;
		origen.st.columna = col_ma;
		origen.st.orientacion = brujula;

		typename ComportamientoJugador::nodo destino;
		destino.st.fila = sensores.regalos[0].first;
		destino.st.columna = sensores.regalos[0].second;
		destino.st.orientacion = 0;

		estoy_ejecutando_plan = CostoUniforme(origen, destino, plan);
	}



	// Decidir acciones de no movimiento
	if(sensores.superficie[2] >= '0' && sensores.superficie[2] <= '4' && sensores.objetoActivo == '_') {
		accion = actPICKUP;
	}

	else if(sensores.superficie[2] == 'l' && sensores.objetoActivo == '0') {
		accion = actGIVE;
	}

	else if (sensores.superficie[2] == 'r'  && sensores.objetoActivo == '4'){
		accion = actGIVE;
	}

	// Decidir la nueva acción de movimiento

	else if (estoy_ejecutando_plan && !error_plan ){
		accion = plan.front();
		plan.erase(plan.begin());
		PintaPlan(plan);

		if (plan.size()==0){
			estoy_ejecutando_plan = false;
		}
	}
	

	else if(!hayObstaculoDelante(sensores.terreno,sensores.superficie) && seguir_frente) {
		accion = actFORWARD;
	}
	
	else if (sensores.terreno[2] == 'A' && sensores.objetoActivo == '1' && sensores.superficie[2] == '_' && seguir_frente) {
		accion = actFORWARD;
	}

	else if(sensores.terreno[2] == 'B' && sensores.objetoActivo == '2' && sensores.superficie[2] == '_' && seguir_frente) {
		accion = actFORWARD;
	}

	else if (girar_derecha)
		accion = actTURN_R;
		
	else
		accion = actTURN_L;
	

	// Recordar la ultima accion
	ultimaAccion = accion;
	return accion;
}

int ComportamientoJugador::interact(const Action &accion, const int &valor) const {
  return false;
}

/******************************************************************ACTUALIZAR VARIABLES*****************************************************************/
void ComportamientoJugador::ActualizarVariables(const Sensores &sensores) {

	int n = rand() & 127;


	//PLANNING
	if (error_plan){
		estoy_ejecutando_plan = false;
	}

	if (estoy_ejecutando_plan && plan.front() == actFORWARD && hayObstaculoDelante(sensores.terreno, sensores.superficie)){
		if (sensores.superficie[2] == 'a'  || sensores.superficie[2] == 'l'){
			plan.push_front(actIDLE);
			error_plan = false;
		}
		else {
			error_plan=true;
		}
	}
	else {
		error_plan = false;
	}

	switch (ultimaAccion) {
		case actFORWARD:
			if(!sensores.colision)
				switch(brujula) {
					case 0: --fil_ma;--fil_me;
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
			girar_derecha = n & 1;	
			break;

		case actTURN_R:
			brujula = (brujula + 1) & 3; // (brujula+1)%4
			girar_derecha = n & 1;	
			break;

		case actPICKUP:
			if (sensores.objetoActivo == '4'){
				tengo_regalo = true;
				estoy_ejecutando_plan = false;
			}
			break;

		case actGIVE:
				tengo_regalo = false;
			break;
	}
		
	if(sensores.reset)
		Reiniciar();
		
	seguir_frente = n<PROB_FRENTE;
}

/*************************************************************MAPA RESULTADO****************************************************************************/
void ComportamientoJugador::ActualizarMapa(const Sensores &sensores) {
	typename ComportamientoJugador::size_type k = 0;
	mapaResultado[fil_ma][col_ma] = sensores.terreno[k++];
		
	switch(brujula) {
			case 0:
				for(typename ComportamientoJugador::size_type i=1; i <=3; ++i)
					for(typename ComportamientoJugador::size_type j=-i; j <= i; ++j) 
						mapaResultado[fil_ma-i][col_ma+j] = sensores.terreno[k++];
			break;

			case 1:
				for(typename ComportamientoJugador::size_type i=1; i <=3; ++i)
					for(typename ComportamientoJugador::size_type j=-i; j <= i; ++j)
						mapaResultado[fil_ma+j][col_ma+i] = sensores.terreno[k++];
			break;

			case 2:
				for(typename ComportamientoJugador::size_type i=1; i <=3; ++i)
					for(typename ComportamientoJugador::size_type j=-i; j <= i; ++j)
						mapaResultado[fil_ma+i][col_ma-j] = sensores.terreno[k++];			
			break;

			case 3:
				for(typename ComportamientoJugador::size_type i=1; i <=3; ++i)
					for(typename ComportamientoJugador::size_type j=-i; j <= i; ++j)
						mapaResultado[fil_ma-j][col_ma-i] = sensores.terreno[k++];				
			break;
	}

}

/*****************************************************MEMORIA*******************************************************************************************/
void ComportamientoJugador::ActualizarMemoria(const Sensores &sensores) {
	typename ComportamientoJugador::size_type k = 0;
	memoria[fil_me][col_me] = sensores.terreno[k++];
		
	switch(brujula) {
			case 0:
				for(typename ComportamientoJugador::size_type i=1; i <=3; ++i)
					for(typename ComportamientoJugador::size_type j=-i; j <= i; ++j) 
						memoria[fil_me-i][col_me+j] = sensores.terreno[k++];
			break;

			case 1:
				for(typename ComportamientoJugador::size_type i=1; i <=3; ++i)
					for(typename ComportamientoJugador::size_type j=-i; j <= i; ++j)
						memoria[fil_me+j][col_me+i] = sensores.terreno[k++];			
				break;

			case 2:
				for(typename ComportamientoJugador::size_type i=1; i <=3; ++i)
					for(typename ComportamientoJugador::size_type j=-i; j <= i; ++j)
						memoria[fil_me+i][col_me-j] = sensores.terreno[k++];
			break;

			case 3:
				for(typename ComportamientoJugador::size_type i=1; i <=3; ++i)
					for(typename ComportamientoJugador::size_type j=-i; j <= i; ++j)
						memoria[fil_ma-j][col_ma-i] = sensores.terreno[k++];
			break;
	}
}

void ComportamientoJugador::VolcarMemoria() {
	typename ComportamientoJugador::size_type inc_f = fil_ma - fil_me;
	typename ComportamientoJugador::size_type inc_c = col_ma - col_me;

	for(typename ComportamientoJugador::size_type i=0; i < TAM_MAPA; ++i)
		for(typename ComportamientoJugador::size_type j=0; j < TAM_MAPA; ++j)
			if(mapaResultado[i][j] == '?')
				mapaResultado[i][j] = memoria[i-inc_f][j-inc_c];

}

void ComportamientoJugador::BorrarMemoria() {
	for(typename ComportamientoJugador::size_type i=0; i < TAM_MEMORIA; ++i)
		for(typename ComportamientoJugador::size_type j=0; j < TAM_MEMORIA; ++j)
			memoria[i][j] = '?';

}
