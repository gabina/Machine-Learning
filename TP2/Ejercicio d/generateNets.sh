#!/bin/bash

Gamma[0]='0.00000001'
Gamma[1]='0.0000001'
Gamma[2]='0.000001'
Gamma[3]='0.00001'
Gamma[4]='0.0001'
Gamma[5]='0.001'
Gamma[6]='0.01'
Gamma[7]='0.1'
Gamma[8]='1'

for i in `seq 2 8 `;
do
			
	cp ssp.net ssp$i.net
	cp ssp.data ssp$i.data
	cp ssp.test ssp$i.test
	sed -i -- "s/# gamma/${Gamma[$i-1]}/g" ssp$i.net
	
	 	
	for k in `seq 1 1`;
	do
		#ejecuto
		./a.out ssp$i >> ssp$i.resultados
	done
	
		: '
		
		#genero en ssp11.mse los datos correspondientes a mse Gamma - valid - test
		sed -r 's/.{27}$//' ssp$i$j.mse > ssp$i$j2.mse #saca de atras
		sed -r 's/.{9}//' ssp$i$j2.mse > ssp$i$j.mse #saca de adelate
		rm ssp$i$j2.mse
		
		
		#creo el archivo
		#echo "Promedios" > promedio$i$j
		
		mkdir Promedio$i$j
				
        for k in `seq 1 100`;
        do
			#calculo promedios
			
			#Epoca k
			
			echo "Gamma, Validation, Test"  > Promedio$i$j/epoca`expr $k \* 400`
			
			
			# filtro las lineas correspondientes
			sed -n $k~100p ssp$i$j.mse >> Promedio$i$j/epoca`expr $k \* 400`
        done		
	
		#Con comandos R saco los promedios
		Rscript "/home/gabina/Facultad/Machine Learning/TP2/Ejercicio a/calcularPromedios.R"
	
		'
done    
 

