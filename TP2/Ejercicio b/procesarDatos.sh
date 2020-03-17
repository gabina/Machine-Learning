#!/bin/bash


for i in `seq 1 5`;
do

		echo "Test" >> datosProcesados$i.txt
		grep "Test discreto:" espirales$i.resultados >> auxiliar1.txt

		sed -r 's/.{1}$//' auxiliar1.txt >> auxiliar2.txt #saca de atras
		sed -r 's/.{14}//' auxiliar2.txt >> datosProcesados$i.txt #saca de adelate

		rm auxiliar1.txt
		rm auxiliar2.txt

done    
 

