#!/bin/bash


for i in `seq 1 3`;
do

		echo "Train, Validation, Test" > MSE/ikeda$i.mse

		sed -r 's/.{27}$//' ikeda$i.mse >> auxiliar2.txt #saca de atras
		sed -r 's/.{9}//' auxiliar2.txt >> auxiliar3.txt #saca de adelate

		head -n -3000 auxiliar3.txt > auxiliar4.txt 
		sed -e '1,800d'  auxiliar4.txt  >>	MSE/ikeda$i.mse 

		rm auxiliar3.txt
		rm auxiliar2.txt
		rm auxiliar4.txt

done    
 
