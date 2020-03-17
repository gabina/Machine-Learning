#!/bin/bash

Train[0]='190'
Train[1]='150'
Train[2]='100'

for i in `seq 2 3`;
do
		
	cp ikeda.net ikeda$i.net
	cp ikeda.data ikeda$i.data
	cp ikeda.test ikeda$i.test
	sed -i -- "s/#entrenamiento/${Train[$i-1]}/g" ikeda$i.net
		
	for k in `seq 1 20`;
	do
		#ejecuto
		./a.out ikeda$i >> ikeda$i.resultados
	done
		
		: '
		
		#genero en ikeda11.mse los datos correspondientes a mse train - valid - test
		sed -r 's/.{27}$//' ikeda$i$j.mse > ikeda$i$j2.mse #saca de atras
		sed -r 's/.{9}//' ikeda$i$j2.mse > ikeda$i$j.mse #saca de adelate
		rm ikeda$i$j2.mse
		
		
		#creo el archivo
		#echo "Promedios" > promedio$i$j
		
		mkdir Promedio$i$j
				
        for k in `seq 1 100`;
        do
			#calculo promedios
			
			#Epoca k
			
			echo "Train, Validation, Test"  > Promedio$i$j/epoca`expr $k \* 400`
			
			
			# filtro las lineas correspondientes
			sed -n $k~100p ikeda$i$j.mse >> Promedio$i$j/epoca`expr $k \* 400`
        done		
	
		#Con comandos R saco los promedios
		Rscript "/home/gabina/Facultad/Machine Learning/TP2/Ejercicio a/calcularPromedios.R"
	
		'
done    
 

