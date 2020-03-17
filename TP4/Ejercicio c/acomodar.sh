#!/bin/bash

Dim[1]='2'
Dim[2]='4'
Dim[3]='8'
Dim[4]='16'
Dim[5]='32'

for j in `seq 1 5`;
do
		cp GausianasA/d=${Dim[$j]}/gausianasA0.data GausianasA/d=${Dim[$j]}/gausianasA20.data
		cp GausianasA/d=${Dim[$j]}/gausianasA0.test GausianasA/d=${Dim[$j]}/gausianasA20.test
		rm 	GausianasA/d=${Dim[$j]}/gausianasA0.data
		rm 	GausianasA/d=${Dim[$j]}/gausianasA0.test
		rm 	GausianasA/d=${Dim[$j]}/gausianasA0.nb
		rm 	GausianasA/d=${Dim[$j]}/gausianasA0.predic	
		
		cp GausianasB/d=${Dim[$j]}/gausianasB0.data GausianasB/d=${Dim[$j]}/gausianasB20.data
		cp GausianasB/d=${Dim[$j]}/gausianasB0.test GausianasB/d=${Dim[$j]}/gausianasB20.test
		rm 	GausianasB/d=${Dim[$j]}/gausianasB0.data
		rm 	GausianasB/d=${Dim[$j]}/gausianasB0.test
		rm 	GausianasB/d=${Dim[$j]}/gausianasB0.nb
		rm 	GausianasB/d=${Dim[$j]}/gausianasB0.predic								
done
	


for i in `seq 1 20`;
do
	for j in `seq 1 5`;
	do
	
		: '
		rm GausianasA/d=${Dim[$j-1]}/gausianasA${i-1}.tree
		rm GausianasA/d=${Dim[$j-1]}/gausianasA${i-1}.unpruned		
		rm GausianasA/d=${Dim[$j-1]}/gausianasA${i-1}.names		
		rm GausianasA/d=${Dim[$j-1]}/gausianasA${i-1}a.prediction		

		rm GausianasB/d=${Dim[$j-1]}/gausianasB${i-1}.tree
		rm GausianasB/d=${Dim[$j-1]}/gausianasB${i-1}.unpruned		
		rm GausianasB/d=${Dim[$j-1]}/gausianasB${i-1}.names		
		rm GausianasB/d=${Dim[$j-1]}/gausianasB${i-1}a.prediction		
				
		'

		cp gausianasA0.nb GausianasA/d=${Dim[$j]}/gausianasA${i}.nb
		sed -i -- "s/#dimensiones/${Dim[$j]}/g" GausianasA/d=${Dim[$j]}/gausianasA${i}.nb
		
		cp gausianasA0.nb GausianasB/d=${Dim[$j]}/gausianasB${i}.nb
		sed -i -- "s/#dimensiones/${Dim[$j]}/g" GausianasB/d=${Dim[$j]}/gausianasB${i}.nb		
		
	done
done
