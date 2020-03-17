#!/bin/bash

Int[0]='2'
Int[1]='5'
Int[2]='10'
Int[3]='20'
Int[4]='40'

for i in `seq 1 5`;
do
		
	cp espirales.net espirales$i.net
	cp espirales.data espirales$i.data
	cp espirales.test espirales$i.test
	sed -i -- "s/#intermedias/${Int[$i-1]}/g" espirales$i.net
		
	for k in `seq 1 20`;
	do
		#ejecuto
		./a.out espirales$i >> espirales$i.resultados
	done
		
		: '
		
		#genero en espirales11.mse los datos correspondientes a mse train - valid - test
		sed -r 's/.{27}$//' espirales$i$j.mse > espirales$i$j2.mse #saca de atras
		sed -r 's/.{9}//' espirales$i$j2.mse > espirales$i$j.mse #saca de adelate
		rm espirales$i$j2.mse
		
		
		#creo el archivo
		#echo "Promedios" > promedio$i$j
		
		mkdir Promedio$i$j
				
        for k in `seq 1 100`;
        do
			#calculo promedios
			
			#Epoca k
			
			echo "Train, Validation, Test"  > Promedio$i$j/epoca`expr $k \* 400`
			
			
			# filtro las lineas correspondientes
			sed -n $k~100p espirales$i$j.mse >> Promedio$i$j/epoca`expr $k \* 400`
        done		
	
		#Con comandos R saco los promedios
		Rscript "/home/gabina/Facultad/Machine Learning/TP2/Ejercicio a/calcularPromedios.R"
	
		'
done    
 

