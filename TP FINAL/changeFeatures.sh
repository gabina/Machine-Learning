#!/bin/bash

Rep[1]='X'
Rep[2]='1'
Rep[3]='2'
Rep[4]='3'
Rep[5]='4'
Rep[6]='5'

Feat[1]='1'
Feat[2]='2'
Feat[3]='3'
Feat[4]='4'
Feat[5]='5'
Feat[6]='6'


for i in `seq 1 10`;
do
		sed "s/X/1/"	svm_light/heladasSVM/heladasEscaladas$i.data >> svm_light/heladasSVM/hel2adas$i.data
		sed "s/X/2/"	svm_light/heladasSVM/hel2adas$i.data >> svm_light/heladasSVM/hel3adas$i.data
		sed "s/X/3/"	svm_light/heladasSVM/hel3adas$i.data >> svm_light/heladasSVM/hel4adas$i.data
		sed "s/X/4/"	svm_light/heladasSVM/hel4adas$i.data >> svm_light/heladasSVM/hel5adas$i.data
		sed "s/X/5/"	svm_light/heladasSVM/hel5adas$i.data >> svm_light/heladasSVM/hel6adas$i.data
		sed "s/X/6/"	svm_light/heladasSVM/hel6adas$i.data > svm_light/heladasSVM/heladasEscaladas$i.data
		rm svm_light/heladasSVM/hel2adas$i.data
		rm svm_light/heladasSVM/hel3adas$i.data
		rm svm_light/heladasSVM/hel4adas$i.data		
		rm svm_light/heladasSVM/hel5adas$i.data
		rm svm_light/heladasSVM/hel6adas$i.data		
done
