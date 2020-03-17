#!/bin/bash

Dim[0]='2'
Dim[1]='4'
Dim[2]='8'
Dim[3]='16'
Dim[4]='32'


for i in `seq 1 5`;
do



		echo "Test" > datosProcesadosA$i.txt
		grep "Test:" GausianasA/d=${Dim[$i-1]}/gausianasA.resultados >> auxiliar1.txt

		sed -r 's/.{1}$//' auxiliar1.txt >> auxiliar2.txt #saca de atras
		sed -r 's/.{5}//' auxiliar2.txt >> datosProcesadosA$i.txt #saca de adelate

		rm auxiliar1.txt
		rm auxiliar2.txt
		
		echo "Test" > datosProcesadosB$i.txt
		grep "Test:" GausianasB/d=${Dim[$i-1]}/gausianasB.resultados >> auxiliar1.txt

		sed -r 's/.{1}$//' auxiliar1.txt >> auxiliar2.txt #saca de atras
		sed -r 's/.{5}//' auxiliar2.txt >> datosProcesadosB$i.txt #saca de adelate

		rm auxiliar1.txt
		rm auxiliar2.txt		
		
done    
 

