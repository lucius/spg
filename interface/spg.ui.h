#include <iostream>
#include "../include/Pagina.h"
#include "../include/Controlador.h"

char*
itoa( int val, int base )
{
	static char
	buf[32] = {0};

	int
	i = 30;

	if( val == 0 )
	{
		return ( char* ) "0";
	}
	
	for( ; val && i ; --i, val /= base )
	{
		buf[ i ] = "0123456789abcdef"[ val % base ];
	}
	
	return &buf[ i+1 ];
}

void
MainWindow::nextStepClicked( )
{
	if( strlen((const char*)caminhoArquivo->text()) )
	{
		resultado->setText( itoa(zim.proximaInstrucao(),10) );
		repaintMemoria( );
		repaintPaginacao( );
		repaintTabelaPaginas( );
	}
}

void
MainWindow::repaintMemoria( )
{
	Pagina<std::string>::Paginacao
	auxImpressao = zim.getMemoriaPrincipal( );

	unsigned int
	count;
	
	std::string
	buffer;
	
	QListViewItem*
	items[16];
	
	if(memoriaList->columns() == 0)
	{
		memoriaList->addColumn( ">", 20 );
		memoriaList->addColumn( "Endereço", 70 );
		memoriaList->addColumn( "Conteudo", 158 );
	}

	memoriaList->clear( );

	for( count=0; count<16; count++ )
	{
		buffer = itoa( count,10 );

		if( buffer.length() == 1 )
		{
			buffer.insert( buffer.begin(), '0');
		}

		if(zim.getInstrucaoCorrespondente() == FIM)
		{
			items[ count ] = new QListViewItem( memoriaList, " ", buffer.c_str(), auxImpressao[count].getDado().c_str() );
		}
		else if(zim.getInstrucaoCorrespondente() == count)
		{
			items[ count ] = new QListViewItem( memoriaList, ">", buffer.c_str(), auxImpressao[count].getDado().c_str() );
		}
		else
		{
			items[ count ] = new QListViewItem( memoriaList, " ", buffer.c_str(), auxImpressao[count].getDado().c_str() );
		}

		if( zim.getProximaPosicao() == count )
		{
			items[ count ]->setSelectable( TRUE );
			items[ count ]->setSelected( TRUE );
		}

		memoriaList->insertItem( (QListViewItem*) items[count] );
	}

	memoriaList->setSorting( 1, TRUE );
}

void
MainWindow::repaintPaginacao( )
{
	Pagina<std::string>::Paginacao
	auxImpressao = zim.getArquivoPaginacao( );

	unsigned
	int
	count;
	
	std::string
	buffer;
	
	QListViewItem*
	items[32];
	
	if(paginacaoList->columns() == 0)
	{
		paginacaoList->addColumn( ">", 20 );
		paginacaoList->addColumn( "Endereço", 70 );
		paginacaoList->addColumn( "Conteudo", 158 );
	}

	paginacaoList->clear( );

	for( count=0; count<32; count++ )
	{
		buffer = itoa( count,10 );

		if( buffer.length() == 1 )
		{
			buffer.insert( buffer.begin(), '0');
		}
		if(zim.getInstrucaoAtual() == count)
		{
			items[ count ] = new QListViewItem( paginacaoList, ">", buffer.c_str(), auxImpressao[count].getDado().c_str() );
		}
		else
		{
			items[ count ] = new QListViewItem( paginacaoList, " ", buffer.c_str(), auxImpressao[count].getDado().c_str() );
		}
		
		paginacaoList->insertItem( (QListViewItem*) items[count] );
	}

	paginacaoList->setSorting( 1, TRUE );

}

void
MainWindow::repaintTabelaPaginas( )
{
	Pagina<std::string>::Paginacao
	auxImpressao = zim.getArquivoPaginacao( );
	
	int
	count;
	
	std::string
	buffer;
	
	std::string
	buffer1;
	
	QListViewItem*
	items[32];
	
	if(tabelaPaginasList->columns() == 0)
	{
		tabelaPaginasList->addColumn( "End. Virtual", 100 );
		tabelaPaginasList->addColumn( "End. Real", 100 );
		tabelaPaginasList->addColumn( "P", 32 );

	}

	tabelaPaginasList->clear( );

	for( count=0; count<32; count++ )
	{
		buffer = itoa( count,10 );

		if( buffer.length() == 1 )
		{
			buffer.insert( buffer.begin(), '0');
		}
		if(zim.getInstrucaoCorrespondente(count) == FIM)
		{
			items[ count ] = new QListViewItem( memoriaList, buffer.c_str(), " ", "0" );
		}
		else
		{
			buffer1 = itoa( zim.getInstrucaoCorrespondente(count),10 );

			if( buffer1.length() == 1 )
			{
				buffer1.insert( buffer1.begin(), '0' );
			}

			items[ count ] = new QListViewItem( memoriaList, buffer.c_str(), buffer1.c_str(), "1"  );
		}

		buffer1.clear( );

		tabelaPaginasList->insertItem( (QListViewItem*) items[count] );
	}

	tabelaPaginasList->setSorting( 0, TRUE );
}


void
MainWindow::openFileClicked( )
{
	QString
	nomeArquivo = QFileDialog::getOpenFileName( QString::null, QString::null, this );

	if( strlen( (const char*)nomeArquivo) != 0 )
	{
		caminhoArquivo->setText( nomeArquivo );
		zim.carregaInstrucoes( (const char*)nomeArquivo );
		
		repaintPaginacao( );
		repaintMemoria( );
		repaintTabelaPaginas( );
	}
}
