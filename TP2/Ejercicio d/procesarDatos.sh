#!/bin/bash


for i in `seq 1 9`;
do

		echo "Train, Validation, Test" > MSE/ssp$i.mse

		sed -r 's/.{27}$//' ssp$i.mse >> auxiliar2.txt #saca de atras
		sed -r 's/.{9}//' auxiliar2.txt >> auxiliar3.txt #saca de adelate

		#head -n -9500 auxiliar3.txt >> MSE/ssp$i.mse #  saca las ultimas tantas líneas		
		head -n -9000 auxiliar3.txt > auxiliar4.txt #  saca las ultimas tantas líneas
		sed -e '1,500d'  auxiliar4.txt  >>	MSE/ssp$i.mse #saca las primeras tantas lineas

		rm auxiliar3.txt
		rm auxiliar2.txt
		rm auxiliar4.txt

done    
 
