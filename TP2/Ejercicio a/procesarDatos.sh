#!/bin/bash


for i in `seq 1 3`;
do
	for j in `seq 1 3`;
	do 
	
		echo "Test" >> datosProcesados$i$j.txt
		grep "Test discreto:" dos_elipses$i$j.resultados >> datosProcesados1.txt

		sed -r 's/.{1}$//' datosProcesados1.txt >> datosProcesados2.txt #saca de atras
		sed -r 's/.{14}//' datosProcesados2.txt >> datosProcesados$i$j.txt #saca de adelate

		rm datosProcesados1.txt
		rm datosProcesados2.txt
	
	done
done    
 

