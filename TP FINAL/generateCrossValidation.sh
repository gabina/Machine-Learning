#!/bin/bash

for i in `seq 1 10`;
do
	echo > heladas/heladasSin$i.data
	cp heladas/heladasEscaladas.names heladas/heladasSin$i.names
	for j in `seq 1 10`;
	do
		if [ $i -eq $j ];then
			cp heladas/heladasEscaladas$i.data heladas/heladasSin$i.test
			continue
		fi
		
		cat heladas/heladasEscaladas$j.data  >> heladas/heladasSin$i.data 
		
	done

done
