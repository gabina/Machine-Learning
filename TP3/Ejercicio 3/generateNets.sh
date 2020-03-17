#!/bin/bash

for k in `seq 1 20`;
do
		#ejecuto
		./a.out DosElipses/dos_elipses$k >>  DosElipses/dos_elipses.resultados
		./a.out DosElipses/dos_elipses$k >> DosElipses/dos_elipses.resultados
done

 

