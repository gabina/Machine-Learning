#!/bin/bash


for i in `seq 1 3`;
do
	for j in `seq 1 3`;
	do

		echo "Train, Validation, Test" > MSE/dos_elipses$i$j.mse

		sed -r 's/.{27}$//' Resultados/dos_elipses$i$j.mse >> auxiliar2.txt #saca de atras
		sed -r 's/.{9}//' auxiliar2.txt >> auxiliar3.txt #saca de adelate

		head -n -1400 auxiliar3.txt > auxiliar4.txt # Saco las ultimas tantas lineas
		sed -e '1,500d'  auxiliar4.txt  >>	MSE/dos_elipses$i$j.mse #Saco las primeras tantas lineas

		rm auxiliar3.txt
		rm auxiliar2.txt
		rm auxiliar4.txt

	done
done    
 
