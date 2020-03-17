#!/bin/bash

Dim[0]='2'
Dim[1]='4'
Dim[2]='8'
Dim[3]='16'
Dim[4]='32'


for i in `seq 1 5`;
do
		
	
 	rm GausianasA/d=${Dim[$i-1]}/gausianasA.resultados
	rm GausianasB/d=${Dim[$i-1]}/gausianasB.resultados

	./a.out GausianasA/d=${Dim[$i-1]}/gausianasA0 >>  GausianasA/d=${Dim[$i-1]}/gausianasA.resultados
	./a.out GausianasB/d=${Dim[$i-1]}/gausianasB0 >> GausianasB/d=${Dim[$i-1]}/gausianasB.resultados


		
	for k in `seq 1 19`;
	do
		#ejecuto
		./a.out GausianasA/d=${Dim[$i-1]}/gausianasA$k >>  GausianasA/d=${Dim[$i-1]}/gausianasA.resultados
		./a.out GausianasB/d=${Dim[$i-1]}/gausianasB$k >> GausianasB/d=${Dim[$i-1]}/gausianasB.resultados
	done

		
done    
 

