#include <iostream>
#include <vector>
#include "./include/spg.h"

int
main( int argc, char** argv )
{

	spg::Pagina<int>
	teste;

	spg::Pagina<unsigned short int>::Paginacao
	teste1;

	std::cout << teste1.size();
	teste1.resize(64);

	teste1[0] = 0;

	std::cout << teste1.begin()->getDado();

	return 0;
}
