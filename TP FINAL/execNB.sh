#!/bin/bash

for i in `seq 1 10`;
do
	./nb.out heladas/heladasSin$i >> heladas/resultadosNB.txt

done
