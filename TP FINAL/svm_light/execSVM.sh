#!/bin/bash

C[1]='10000'
C[2]='0.0001'
C[3]='0.001'
C[4]='0.01'
C[5]='0.1'
C[6]='1'
C[7]='10'
C[8]='100'
C[9]='300'
C[10]='500'
C[11]='800'
C[12]='1000'
C[13]='2000'
C[14]='3000'
C[15]='10000'
C[16]='100000'


D[1]='2'
D[2]='3'
D[3]='5'
D[4]='10'
D[5]='15'
D[6]='30'
D[7]='60'
D[8]='100'
D[9]='300'
D[10]='590'
D[11]='600'


G[1]='5'
G[2]='0.35'
G[3]='0.4'
G[4]='0.45'
G[5]='0.55'
G[6]='0.6'
G[7]='0.65'
G[8]='0.5'
G[9]='1'
G[10]='8'

	echo "Resultados" > resultadosSVM.txt
	: '	
	for i in `seq 1 10`;
	do
		echo "" >> resultadosSVM.txt
		echo "Nuevo C" >> resultadosSVM.txt
		./svm_learn -c 15 heladasSVM/heladasSin$i.data heladasSVM/model$i >> resultadosSVM.txt
		./svm_classify heladasSVM/heladasSin$i.test heladasSVM/model$i heladasSVM/prediction$i >> resultadosSVM.txt	
		#./svm_learn heladasSVM/heladasSin$i.data heladasSVM/model$i >> resultadosSVM.txt
		#./svm_classify heladasSVM/heladasSin$i.test heladasSVM/model$i heladasSVM/prediction$i >> resultadosSVM.txt
	done


	for i in `seq 1 6`;
	do
		echo "" >> resultadosSVM.txt
		echo "Nuevo C" >> resultadosSVM.txt
		./svm_learn -c ${C[$i]} heladasSVM/heladasSin7.data heladasSVM/model7 >> resultadosSVM.txt
		./svm_classify heladasSVM/heladasSin7.test heladasSVM/model7 heladasSVM/prediction7 >> resultadosSVM.txt	
		#./svm_learn heladasSVM/heladasSin$i.data heladasSVM/model$i >> resultadosSVM.txt
		#./svm_classify heladasSVM/heladasSin$i.test heladasSVM/model$i heladasSVM/prediction$i >> resultadosSVM.txt
	done

	echo "Kernel Polinomial" >> resultadosSVM.txt

	for i in `seq 1 1`;
	do
	
		for j in `seq 1 9`;
		do
			echo "" >> resultadosSVM.txt
			echo "Nuevo C" >> resultadosSVM.txt
			./svm_learn -c ${C[$i]} -t 1 -d ${D[$j]} heladasSVM/heladasSin7.data heladasSVM/model7 >> resultadosSVM.txt
			./svm_classify heladasSVM/heladasSin7.test heladasSVM/model7 heladasSVM/prediction7 >> resultadosSVM.txt	
			#./svm_learn heladasSVM/heladasSin$i.data heladasSVM/model$i >> resultadosSVM.txt
			#./svm_classify heladasSVM/heladasSin$i.test heladasSVM/model$i heladasSVM/prediction$i >> resultadosSVM.txt
		done

	done
	' 	
	

	echo "Kernel Polinomial" >> resultadosSVM.txt

	for i in `seq 1 1`;
	do
	
		for j in `seq 10`;
		do
			echo "" >> resultadosSVM.txt
			echo "Nuevo C" >> resultadosSVM.txt
			./svm_learn -c 1 -t 0.1 -d 5 heladasSVM/heladasSin$j.data heladasSVM/model$j >> resultadosSVM.txt
			./svm_classify heladasSVM/heladasSin$j.test heladasSVM/model$j heladasSVM/prediction$j >> resultadosSVM.txt	
			#./svm_learn heladasSVM/heladasSin$i.data heladasSVM/model$i >> resultadosSVM.txt
			#./svm_classify heladasSVM/heladasSin$i.test heladasSVM/model$i heladasSVM/prediction$i >> resultadosSVM.txt
		done

	done	
	
	: '	

	for i in `seq 1 10`;
	do
	
		for j in `seq 1 1`;
		do
			echo "" >> resultadosSVM.txt
			echo "Nuevo Gamma" >> resultadosSVM.txt
			./svm_learn -c 500 -t 2 -g 0.65 heladasSVM/heladasSin$i.data heladasSVM/model$i >> resultadosSVM.txt
			./svm_classify heladasSVM/heladasSin$i.test heladasSVM/model$i heladasSVM/prediction$i >> resultadosSVM.txt	
			#./svm_learn heladasSVM/heladasSin$i.data heladasSVM/model$i >> resultadosSVM.txt
			#./svm_classify heladasSVM/heladasSin$i.test heladasSVM/model$i heladasSVM/prediction$i >> resultadosSVM.txt
		done

	done	
	' 	
	bash filtrar.sh
# ./svm_learn heladasSVM/heladasSin7.data heladasSVM/model7 >> resultadosSVM.txt
