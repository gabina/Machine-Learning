#!/bin/bash

Bins[0]='0'
Bins[1]='1'
Bins[2]='2'
Bins[3]='5'
Bins[4]='8'
Bins[5]='10'
Bins[6]='12'
Bins[7]='15'
Bins[8]='20'
Bins[9]='25'
Bins[10]='30'
Bins[11]='50'
Bins[12]='70'
Bins[13]='100'
Bins[14]='200'
Bins[15]='300'
Bins[16]='1000'

rm EspiralesAnidadas/espirales.resultados

for i in `seq 1 16`;
do
		
	cp EspiralesAnidadas/espirales.nb EspiralesAnidadas/espirales$i.nb
	cp EspiralesAnidadas/espirales.data EspiralesAnidadas/espirales$i.data
	cp EspiralesAnidadas/espirales.test EspiralesAnidadas/espirales$i.test
	sed -i -- "s/#bins/${Bins[$i]}/g" EspiralesAnidadas/espirales$i.nb
			
	#ejecuto
	./a.out EspiralesAnidadas/espirales$i >>  EspiralesAnidadas/espirales.resultados

		
done    
 

