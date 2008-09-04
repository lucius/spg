#ifndef CONTROLADOR_H_
#define CONTROLADOR_H_

#include <iostream>
#include <map>
#include <queue>

#include "../include/Pagina.h"
#include "../include/StructPresenca.h"
#include "../include/StructAssociacao.h"



class Controlador
{
	public:
		Controlador( );

		void
		carregaInstrucoes( const std::string );

		void
		proximaInstrucao( );
		void
		executaInstrucao( unsigned int );

	protected:


	private:
		unsigned int
		instrucaoAtual;

		Pagina<std::string>::Paginacao
		arquivoPaginacao;

		Pagina<std::string>::Paginacao
		memoriaPrincipal;

		std::map<unsigned int, StructPresenca>
		mapaMemoria;

		std::queue<StructAssociacao>
		filaRemocao;

		void
		atualizaPagina( unsigned int, unsigned int );

		bool
		verificaPresenca( unsigned int );

		const unsigned int
		trocaPagina( const unsigned int );
};

#endif /* CONTROLADOR_H_ */
