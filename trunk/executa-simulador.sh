#!/bin/bash

PATH_PROJETO=`which $0`
DIR_PROJETO=`dirname $PATH_PROJETO`

if [ `pwd` != "$DIR_PROJETO" ];
then
	pushd $DIR_PROJETO >/dev/null 2>&1
	POP_P=1
fi

SIMULADOR=$DIR_PROJETO/interface/spg

if [ ! -e $SIMULADOR ];
then
	echo -e "ATENCAO: O executavel nao existe... \n\nTentando compilar..."

	pushd $DIR_PROJETO/interface >/dev/null 2>&1

	make all --silent
	make clean --silent

	if [ "$?" == "0" ];
	then
		echo -e "Sucesso: Iniciando execucao..."
		$SIMULADOR >/dev/null 2>&1 &
	else
		echo "ERRO: Falha ao compilar. Abortando..."
	fi

	popd >/dev/null 2>&1


else
	$SIMULADOR >/dev/null 2>&1 &

fi

wait

echo -e "\n Obrigado por utilizar o SPG =D.";

if [ "$POP_P" ==  "1" ];
then
	popd >/dev/null 2>&1
fi
