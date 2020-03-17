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

rm DosElipses/dos_elipses.resultados

for i in `seq 1 16`;
do
		
	cp DosElipses/dos_elipses.nb DosElipses/dos_elipses$i.nb
	cp DosElipses/dos_elipses.data DosElipses/dos_elipses$i.data
	cp DosElipses/dos_elipses.test DosElipses/dos_elipses$i.test
	sed -i -- "s/#bins/${Bins[$i]}/g" DosElipses/dos_elipses$i.nb
			
	#ejecuto
	./a.out DosElipses/dos_elipses$i >>  DosElipses/dos_elipses.resultados

		'	
done    
 

