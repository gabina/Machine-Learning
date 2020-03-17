#!/bin/bash

Dim[1]='2'
Dim[2]='4'
Dim[3]='8'
Dim[4]='16'
Dim[5]='32'

bash acomodar.sh

for i in `seq 1 5`;
do
		
	
 	rm GausianasA/d=${Dim[$i]}/gausianasA.resultados
	rm GausianasB/d=${Dim[$i]}/gausianasB.resultados

	for k in `seq 1 20`;
	do
		#ejecuto
		./a.out GausianasA/d=${Dim[$i]}/gausianasA$k >>  GausianasA/d=${Dim[$i]}/gausianasA.resultados
		./a.out GausianasB/d=${Dim[$i]}/gausianasB$k >> GausianasB/d=${Dim[$i]}/gausianasB.resultados
	done

		
done    
 
bash procesarDatos.sh
