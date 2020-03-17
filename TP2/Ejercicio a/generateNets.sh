#!/bin/bash

Mom[0]='0'
Mom[1]='0.5'
Mom[2]='0.9'

Lr[0]='0.1'
Lr[1]='0.01'
Lr[2]='0.001'

for i in `seq 1 3`;
do
	for j in `seq 1 3`;
	do 
	

		: '
		cp dos_elipses.net dos_elipses$i$j.net
		cp dos_elipses.data dos_elipses$i$j.data
		cp dos_elipses.test dos_elipses$i$j.test
		sed -i -- "s/#momentum/${Mom[$i-1]}/g" dos_elipses$i$j.net
		sed -i -- "s/#learning-rate/${Lr[$j-1]}/g" dos_elipses$i$j.net
		
		
		for k in `seq 1 20`;
		do
			#ejecuto
			./a.out dos_elipses$i$j >> dos_elipses$i$j.resultados
		done
		
		'
		
		 
		: '
		
		#creo el archivo
		#echo "Promedios" > promedio$i$j
		
		mkdir Promedio$i$j
				
        for k in `seq 1 100`;
        do
			#calculo promedios
			
			#Epoca k
			
			echo "Train, Validation, Test"  > Promedio$i$j/epoca`expr $k \* 400`
			
			
			# filtro las lineas correspondientes
			sed -n $k~100p dos_elipses$i$j.mse >> Promedio$i$j/epoca`expr $k \* 400`
        done		
	
		#Con comandos R saco los promedios
		Rscript "/home/gabina/Facultad/Machine Learning/TP2/Ejercicio a/calcularPromedios.R"
	
		'
	
	done
done    
 

