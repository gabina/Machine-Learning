#!/bin/bash

for i in `seq 1 1`;
do
		
	: '	
	cp ikeda.net iris.net
	cp ikeda.data iris.data
	cp ikeda.test iris.test
	sed -i -- "s/#entrenamiento/${Train[$i-1]}/g" iris.net

		'
	
		
	for k in `seq 1 1`;
	do
		#ejecuto
		./a.out iris >> iris.resultados
	done
		

		: '		
		#genero en ikeda11.mse los datos correspondientes a mse train - valid - test
		sed -r 's/.{27}$//' iris.mse > iris2.mse #saca de atras
		sed -r 's/.{9}//' iris2.mse > iris.mse #saca de adelate
		rm iris2.mse

		
		#creo el archivo
		#echo "Promedios" > promedio$i
		
		mkdir Promedio$i
				
        for k in `seq 1 100`;
        do
			#calculo promedios
			
			#Epoca k
			
			echo "Train, Validation, Test"  > Promedio$i/epoca`expr $k \* 400`
			
			
			# filtro las lineas correspondientes
			sed -n $k~100p iris.mse >> Promedio$i/epoca`expr $k \* 400`
        done		
	
		#Con comandos R saco los promedios
		Rscript "/home/gabina/Facultad/Machine Learning/TP2/Ejercicio a/calcularPromedios.R"
	
		'
done    
 

