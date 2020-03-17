#!/bin/bash

for i in `seq 1 10`;
do

	for j in `seq 1 10`;
	do
		if [ $i -eq $j ];then
			cp svm_light/heladasSVM/heladasEscaladas$i.data svm_light/heladasSVM/heladasSin$i.test
			continue
		fi
		
		cat svm_light/heladasSVM/heladasEscaladas$j.data  >> svm_light/heladasSVM/heladasSin$i.data 
		
	done

done
