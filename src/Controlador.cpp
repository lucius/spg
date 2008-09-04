#include <iostream>
#include <sstream>

#include "../include/Controlador.h"



Controlador::Controlador( )
{
	this->arquivoPaginacao.resize( 32 );
	this->memoriaPrincipal.resize( 16 );
	this->instrucaoAtual = 0;
}

void
Controlador::carregaInstrucoes( const std::string _nomeArquivo )
{


}

void
Controlador::proximaInstrucao( )
{
	if( this->verificaPresenca(this->instrucaoAtual) )
	{
		this->executaInstrucao( this->mapaMemoria[this->instrucaoAtual].enderecoPrincipal );
	}
	else
	{
		this->executaInstrucao( this->trocaPagina(this->instrucaoAtual) );
	}

	++this->instrucaoAtual;
}

void
Controlador::atualizaPagina( unsigned int _origem, unsigned int _destino )
{
	this->memoriaPrincipal[_origem].setModificado( false );
	this->arquivoPaginacao[_destino] = this->memoriaPrincipal[_origem];
}

/*
 * SOMA A B
 * SUBT A B
 * MULT A B
 * DIVI A B
 * PULA A
 */
void
Controlador::executaInstrucao( unsigned int _numeroInstrucao )
{
	std::istringstream
	conversor[0];

	int
	primeiro;

	int
	segundo;

	std::string
	_instrucao = this->memoriaPrincipal[_numeroInstrucao].getDado( );

	conversor[0].str( _instrucao.substr(0, 4) );
	conversor[1].str( _instrucao.substr(5, _instrucao.find_first_of(' ')) );
	conversor[2].str( _instrucao.substr(_instrucao.find_first_of(' ',5)+1, _instrucao.size()) );

	conversor[1] >> primeiro;
	conversor[2] >> segundo;

	conversor[0] >> _instrucao;
	if( _instrucao == "SOMA" )
	{
		std::cout << primeiro + segundo;
	}
	else if( _instrucao == "SUBT" )
	{
		std::cout << primeiro - segundo;
	}
	else if( _instrucao == "MULT" )
	{
		std::cout << primeiro * segundo;
	}
	else if( _instrucao == "DIVI" )
	{
		std::cout << primeiro / segundo;
	}
	else if( _instrucao == "PULA" )
	{
		this->instrucaoAtual = primeiro;
		std::cout << "Pulando para Instrucao: " + primeiro;
	}
}


bool
Controlador::verificaPresenca( unsigned int )
{
	if( this->mapaMemoria[this->instrucaoAtual].presente )
	{
		return true;
	}
	else
	{
		return false;
	}
}

const unsigned int
Controlador::trocaPagina( const unsigned int _origem )
{
	unsigned int
	destino;

	StructAssociacao
	tmp;

	if( this->filaRemocao.size() == this->mapaMemoria.size() )
	{
		destino = this->filaRemocao.front().enderecoPrincipal;

		if( this->memoriaPrincipal[destino].getModificado() )
		{
			this->atualizaPagina( destino, this->filaRemocao.front().enderecoPaginacao );
		}

		this->memoriaPrincipal[destino] = this->arquivoPaginacao[_origem];
		this->mapaMemoria[_origem].enderecoPrincipal = destino;
		this->mapaMemoria[_origem].presente = true;
		this->mapaMemoria[this->filaRemocao.front().enderecoPaginacao].presente = false;
	}
	else
	{
		destino = this->filaRemocao.size() -1;

		this->memoriaPrincipal[destino] = this->arquivoPaginacao[_origem];
		this->mapaMemoria[_origem].enderecoPrincipal = destino;
		this->mapaMemoria[_origem].presente = true;

		this->filaRemocao.pop();
		tmp.enderecoPaginacao = _origem;
		tmp.enderecoPrincipal = destino;
		this->filaRemocao.push( tmp );
	}
}
