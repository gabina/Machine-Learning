#!/bin/bash



		echo "Test" > test.txt
		grep "Test:" EspiralesAnidadas/espirales.resultados >> auxiliar1.txt

		sed -r 's/.{1}$//' auxiliar1.txt >> auxiliar2.txt #saca de atras
		sed -r 's/.{5}//' auxiliar2.txt >> test.txt #saca de adelate

		rm auxiliar1.txt
		rm auxiliar2.txt

		echo "Validacion" > validacion.txt
		grep "Validacion:" EspiralesAnidadas/espirales.resultados >> auxiliar1.txt

		sed -r 's/.{1}$//' auxiliar1.txt >> auxiliar2.txt #saca de atras
		sed -r 's/.{11}//' auxiliar2.txt >> validacion.txt #saca de adelate

		rm auxiliar1.txt
		rm auxiliar2.txt

		echo "Entrenamiento" > train.txt
		grep "Entrenamiento:" EspiralesAnidadas/espirales.resultados >> auxiliar1.txt

		sed -r 's/.{1}$//' auxiliar1.txt >> auxiliar2.txt #saca de atras
		sed -r 's/.{14}//' auxiliar2.txt >> train.txt #saca de adelate

		rm auxiliar1.txt
		rm auxiliar2.txt
