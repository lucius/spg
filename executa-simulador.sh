#!/bin/bash

PASTAPROJETO=`pwd`
CAMINHOSIMULADOR=$PASTAPROJETO/interface/interface
MAKE="make all --silent"
MAKECLEAN="make clean --silent"

function compila_simulador
{
	echo -e " \n** Iniciando a compilacao."

	cd $PASTAPROJETO/interface

	exec $MAKE
	wait

	exec $MAKECLEAN
	wait

	if [ ! -e "interface" ]
	then
		echo -e "\n\n ** Ocorreu algum problema na compilacao. Tente novamente por favor";
	else
		echo -e " [OK] \n\n Simulador em Execucao.";
		exec ./interface &

		wait

		echo -e "\n Obrigado por utilizar o SPG =D.";
	fi

}

echo -e "\nTentando executar o SPG..."

if [ ! -e $CAMINHOSIMULADOR ]
then
	echo -e "\nErro: '$CAMINHOSIMULADOR' nao existe."
	compila_simulador
fi

exec ./interface/interface &
echo -e " [OK] \n\n Simulador em Execucao."

wait

echo -e "\n Obrigado por utilizar o SPG =D.";

