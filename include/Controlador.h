#ifndef CONTROLADOR_H_
#define CONTROLADOR_H_

#include <iostream>
#include <map>
#include <queue>
#include <sstream>
#include <fstream>
#include <string>

#include "../include/Pagina.h"
#include "../include/StructPresenca.h"
#include "../include/StructAssociacao.h"

#define FIM 100

class Controlador
{
	public:
		Controlador( )
		{

		}

		void
		carregaInstrucoes( const std::string _nomeArquivo )
		{
			this->arquivoPaginacao.clear( );
			this->memoriaPrincipal.clear( );

			this->arquivoPaginacao.resize( 32 );
			this->memoriaPrincipal.resize( 16 );
			this->instrucaoAtual = 0;

			std::ifstream
			file( _nomeArquivo.c_str(), std::ifstream::in );

			char
			buffer[256];

			std::string
			strBuffer;

			int
			i;
			if( file.good() )
			{
				for( i = 0; i<32; i++ )
				{
					file.getline( buffer, 256 );
					strBuffer = buffer;
					this->arquivoPaginacao[i] = strBuffer;
					if( file.eof() )
					{
						break;
					}
				}
			}
			this->instrucaoAtual = 0;
			file.close();
		}

		int
		proximaInstrucao( )
		{
			int
			retorno;

			if( this->verificaPresenca(this->instrucaoAtual) )
			{
				retorno = this->executaInstrucao( this->mapaMemoria[this->instrucaoAtual].enderecoPrincipal );
			}
			else
			{
				retorno = this->executaInstrucao( this->trocaPagina() );
			}

			++this->instrucaoAtual;

			return retorno;
		}

		Pagina<std::string>::Paginacao
		getArquivoPaginacao( )
		{
			return this->arquivoPaginacao;
		}

		Pagina<std::string>::Paginacao
		getMemoriaPrincipal( )
		{
			return this->memoriaPrincipal;
		}

		const unsigned int
		getInstrucaoAtual( )
		{
			return this->instrucaoAtual;
		}

		const unsigned int
		getInstrucaoCorrespondente( )
		{
			if( this->verificaPresenca(this->instrucaoAtual) )
			{
				return this->mapaMemoria[this->instrucaoAtual].enderecoPrincipal;
			}
			else
			{
				return FIM;
			}
		}

		const unsigned int
		getInstrucaoCorrespondente( unsigned int _instrucao )
		{
			if( this->verificaPresenca(_instrucao) )
			{
				return this->mapaMemoria[_instrucao].enderecoPrincipal;
			}
			else
			{
				return FIM;
			}
		}

		const unsigned int
		getProximaPosicao( )
		{
			if( this->filaRemocao.size() == this->memoriaPrincipal.size() )
			{
				return this->filaRemocao.front().enderecoPrincipal;
			}
			else
			{
				return this->filaRemocao.size();
			}
		}

	protected:

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
		atualizaPagina( unsigned int _origem, unsigned int _destino )
		{
			this->memoriaPrincipal[_origem].setModificado( false );
			this->arquivoPaginacao[_destino] = this->memoriaPrincipal[_origem];
		}

		bool
		verificaPresenca( unsigned int _instrucao)
		{
			return this->mapaMemoria[_instrucao].presente;
		}

		const unsigned int
		trocaPagina( )
		{
			unsigned int
			destino = 0;

			StructAssociacao
			tmp;

			if( this->filaRemocao.size() == this->memoriaPrincipal.size() )
			{
				destino = this->filaRemocao.front().enderecoPrincipal;

				if( this->memoriaPrincipal[destino].getModificado() )
				{
					this->atualizaPagina( destino, this->filaRemocao.front().enderecoPaginacao );
				}

				this->memoriaPrincipal[destino] = this->arquivoPaginacao[this->instrucaoAtual];
				this->mapaMemoria[this->instrucaoAtual].enderecoPrincipal = destino;
				this->mapaMemoria[this->instrucaoAtual].presente = true;
				this->mapaMemoria[this->filaRemocao.front().enderecoPaginacao].presente = false;

				this->filaRemocao.pop();
			}
			else
			{
				destino = this->filaRemocao.size();

				this->memoriaPrincipal[destino] = this->arquivoPaginacao[this->instrucaoAtual];
				this->mapaMemoria[this->instrucaoAtual].enderecoPrincipal = destino;
				this->mapaMemoria[this->instrucaoAtual].presente = true;
			}
			tmp.enderecoPaginacao = this->instrucaoAtual;
			tmp.enderecoPrincipal = destino;
			this->filaRemocao.push( tmp );

			return destino;
		}

		int
		executaInstrucao( unsigned int _numeroInstrucao )
		{
			std::istringstream
			conversor[3];

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
				return primeiro + segundo;
			}
			else if( _instrucao == "SUBT" )
			{
				return primeiro - segundo;
			}
			else if( _instrucao == "MULT" )
			{
				return primeiro * segundo;
			}
			else if( _instrucao == "DIVI" )
			{
				return primeiro / segundo;
			}
			else if( _instrucao == "PULA" )
			{
				this->instrucaoAtual = primeiro - 1;
				return primeiro;
			}
			else
			{
				return false;
			}
		}
};

#endif /* CONTROLADOR_H_ */
