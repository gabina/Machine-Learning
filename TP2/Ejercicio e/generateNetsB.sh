#!/bin/bash

Dim[0]='2'
Dim[1]='4'
Dim[2]='8'
Dim[3]='16'
Dim[4]='32'

for i in `seq 1 5`;
do
		
	: '	
	cp gausianas0A.net gausianas0A$i.net
	cp gausianas0A.data gausianas0A$i.data
	cp gausianas0A.test gausianas0A$i.test
	sed -i -- "s/#entrenamiento/${Dim[$i-1]}/g" gausianas0A$i.net
	' 	
	for k in `seq 1 20`;
	do
		#ejecuto
		./a.out GausianasB/d=${Dim[$i-1]}/gausianasB0 >>  GausianasB/d=${Dim[$i-1]}/gausianasB0.resultados
	done
		
		: '
		
		#genero en gausianas0A11.mse los datos correspondientes a mse Dim - valid - test
		sed -r 's/.{27}$//' gausianas0A$i$j.mse > gausianas0A$i$j2.mse #saca de atras
		sed -r 's/.{9}//' gausianas0A$i$j2.mse > gausianas0A$i$j.mse #saca de adelate
		rm gausianas0A$i$j2.mse
		
		
		#creo el archivo
		#echo "Promedios" > promedio$i$j
		
		mkdir Promedio$i$j
				
        for k in `seq 1 100`;
        do
			#calculo promedios
			
			#Epoca k
			
			echo "Dim, Validation, Test"  > Promedio$i$j/epoca`expr $k \* 400`
			
			
			# filtro las lineas correspondientes
			sed -n $k~100p gausianas0A$i$j.mse >> Promedio$i$j/epoca`expr $k \* 400`
        done		
	
		#Con comandos R saco los promedios
		Rscript "/home/gabina/Facultad/Machine Learning/TP2/Ejercicio a/calcularPromedios.R"
	
		'
done    
 

