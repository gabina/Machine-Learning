#!/bin/bash


for i in `seq 1 20`;
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
				
		
		sed -i -- "s/#dimensiones/${Dim[$j-1]}/g" GausianasA/d=${Dim[$j-1]}/gausianasA${i-1}.nb
		sed -i -- "s/#dimensiones/${Dim[$j-1]}/g" GausianasB/d=${Dim[$j-1]}/gausianasB${i-1}.nb				
		'


		cp DosElipses/dos_elipses.nb Dos\Elipses/dos_elipses$i.nb
		cp DosElipses/dos_elipses.data Dos\Elipses/dos_elipses$i.data
		cp DosElipses/dos_elipses.test Dos\Elipses/dos_elipses$i.test
		
done
