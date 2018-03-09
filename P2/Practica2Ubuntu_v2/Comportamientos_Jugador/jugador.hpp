#ifndef COMPORTAMIENTOJUGADOR_H
#define COMPORTAMIENTOJUGADOR_H
#include <list>
#include "comportamientos/comportamiento.hpp"
using namespace std;

class ComportamientoJugador : public Comportamiento{

    public:
		typedef short size_type;
		ComportamientoJugador(unsigned int size) : Comportamiento(size) {
			// Inicializar Variables de Estado
			fil_ma = col_ma = 99;
			brujula = 0; // 0: Norte, 1:Este, 2:Sur, 3:Oeste
			ultimaAccion = actIDLE;
			girar_derecha = false;
			bien_situado = false;
			tengo_regalo = false;
			seguir_frente = false;

			estoy_ejecutando_plan =false;
			error_plan =false;
		  
			col_me = (TAM_MEMORIA/2)-1;
			fil_me = (TAM_MEMORIA/2)-1;
			volcar = true;

			memoria = new char* [TAM_MEMORIA];
		
			#pragma omp parallel sections
			{
				#pragma omp section
				for(size_type i=0; i < TAM_MEMORIA/2; ++i) {
					memoria[i] = new char [TAM_MEMORIA];
					for(size_type j=0; j < TAM_MEMORIA/2; ++j)
						memoria[i][j] = '?';
				}
				
				#pragma omp section
				for(size_type i=TAM_MEMORIA/2; i < TAM_MEMORIA; ++i) {
					memoria[i] = new char [TAM_MEMORIA];
					for(size_type j=0; j < TAM_MEMORIA/2; ++j)
						memoria[i][j] = '?';
				}
				
				#pragma omp section
				for(size_type i=0; i < TAM_MEMORIA/2; ++i) {
					memoria[i] = new char [TAM_MEMORIA];
					for(size_type j=TAM_MEMORIA/2; j < TAM_MEMORIA; ++j)
						memoria[i][j] = '?';
				}
				
				#pragma omp section
				for(size_type i=TAM_MEMORIA/2; i < TAM_MEMORIA; ++i) {
					memoria[i] = new char [TAM_MEMORIA];
					for(size_type j=TAM_MEMORIA/2; j < TAM_MEMORIA; ++j)
						memoria[i][j] = '?';
				}
			}

			
		}

    ComportamientoJugador(const ComportamientoJugador & comport) : Comportamiento(comport){
		col_ma = comport.col_ma;
		fil_ma = comport.fil_ma;
		brujula = comport.brujula;
		ultimaAccion = comport.ultimaAccion;
		girar_derecha = comport.girar_derecha;
		bien_situado = comport.bien_situado;
		tengo_regalo = comport.tengo_regalo;
		seguir_frente = comport.seguir_frente;

		estoy_ejecutando_plan = comport.estoy_ejecutando_plan;
		error_plan = comport.error_plan;

		col_me = comport.col_me;
		fil_me = comport.fil_me;
		volcar = comport.volcar;

		memoria = new char* [TAM_MEMORIA];
		
			#pragma omp parallel sections
			{
				#pragma omp section
				for(size_type i=0; i < TAM_MEMORIA/2; ++i) {
					memoria[i] = new char [TAM_MEMORIA];
					for(size_type j=0; j < TAM_MEMORIA/2; ++j)
						memoria[i][j] = comport.memoria[i][j];
				}
				
				#pragma omp section
				for(size_type i=TAM_MEMORIA/2; i < TAM_MEMORIA; ++i) {
					memoria[i] = new char [TAM_MEMORIA];
					for(size_type j=0; j < TAM_MEMORIA/2; ++j)
						memoria[i][j] = comport.memoria[i][j];;
				}
				
				#pragma omp section
				for(size_type i=0; i < TAM_MEMORIA/2; ++i) {
					memoria[i] = new char [TAM_MEMORIA];
					for(size_type j=TAM_MEMORIA/2; j < TAM_MEMORIA; ++j)
						memoria[i][j] = comport.memoria[i][j];;
				}
				
				#pragma omp section
				for(size_type i=TAM_MEMORIA/2; i < TAM_MEMORIA; ++i) {
					memoria[i] = new char [TAM_MEMORIA];
					for(size_type j=TAM_MEMORIA/2; j < TAM_MEMORIA; ++j)
						memoria[i][j] = comport.memoria[i][j];;
				}
			}
	}
	
    ~ComportamientoJugador(){
    
    	#pragma omp parallel for
		for(size_type i=0; i < TAM_MEMORIA; ++i)
			delete [] memoria[i];
		delete [] memoria;
	}

    Action think(const Sensores &sensores);

    int interact(const Action &accion, const int &valor) const;


    ComportamientoJugador * clone(){return new ComportamientoJugador(*this);}



  private:
  	friend class OrdenarNodo;
	static const size_type PROB_FRENTE = 122; //95%
	static const size_type TAM_MAPA = 100;
	static const size_type TAM_MEMORIA = 200;


   	bool girar_derecha,bien_situado,seguir_frente, tengo_regalo, volcar;
	size_type brujula,fil_ma,col_ma, fil_me,col_me, giro_anterior;
	Action ultimaAccion;

      // Para el plan
    bool estoy_ejecutando_plan;
    bool error_plan;
    list <Action> plan;
	char **memoria;
	
	struct nodo {
		unsigned int costo;
		Action accion;
		struct estado {
			unsigned int fila;
			unsigned int columna;
			unsigned int orientacion;
			
			bool operator==(const estado &st) const;
		};
		
		estado st;
		nodo *padre;
		nodo *hijos[3];
		
		nodo();
		nodo& operator=(const nodo &n);
		bool operator==(const nodo &st) const;
		bool operator<(const nodo &n1) const;
		void ExpandirNodo(const Action &accion);
	};
	
	void ActualizarVariables(const Sensores &sensores);
	void ActualizarMapa(const Sensores &sensores);
	void VolcarMemoria();
	void ActualizarMemoria(const Sensores &sensores);
	void BorrarMemoria();
    void Reiniciar();
    list<Action> FormarPlan(nodo &n) const;
   // bool pathFinding(const estado &origen, const estado &destino, list<Action> &plan);
   bool CostoUniforme(nodo n, const nodo &destino, list<Action> &plan) const;
    
};


#endif
