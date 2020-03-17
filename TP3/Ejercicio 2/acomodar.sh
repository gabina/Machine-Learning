#!/bin/bash

Dim[0]='2'
Dim[1]='4'
Dim[2]='8'
Dim[3]='16'
Dim[4]='32'


for i in `seq 1 20`;
do
	for j in `seq 1 5`;
	do
	
		: '
		rm GausianasA/d=${Dim[$j-1]}/gausianasA${i-1}.tree
		rm GausianasA/d=${Dim[$j-1]}/gausianasA${i-1}.unpruned		
		rm GausianasA/d=${Dim[$j-1]}/gausianasA${i-1}.names		
		rm GausianasA/d=${Dim[$j-1]}/gausianasA${i-1}a.prediction		
		
		
		cp gausianasA0.nb GausianasA/d=${Dim[$j-1]}/gausianasA${i-1}.nb
		sed -i -- "s/#dimensiones/${Dim[$j-1]}/g" GausianasA/d=${Dim[$j-1]}/gausianasA${i-1}.nb
		'
		rm GausianasB/d=${Dim[$j-1]}/gausianasB${i-1}.tree
		rm GausianasB/d=${Dim[$j-1]}/gausianasB${i-1}.unpruned		
		rm GausianasB/d=${Dim[$j-1]}/gausianasB${i-1}.names		
		rm GausianasB/d=${Dim[$j-1]}/gausianasB${i-1}a.prediction		
		
		
		cp gausianasA0.nb GausianasB/d=${Dim[$j-1]}/gausianasB${i-1}.nb
		sed -i -- "s/#dimensiones/${Dim[$j-1]}/g" GausianasB/d=${Dim[$j-1]}/gausianasB${i-1}.nb		
		
	done
done
