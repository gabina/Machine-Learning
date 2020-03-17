calculateMedidas<-function(i){	
	
	#Leo los 20 valores de test
	p <- read.csv(paste('/home/gabina/Facultad/Machine Learning/TP2/Ejercicio e/datosProcesadosA',i,'.txt',sep=""))
		
	#Escribo los promedios en el archivos promedios

	write(mean(p$Test),"PROMEDIO",append = T,sep=",")

	return ()
}

	for(i in 1:5){
			calculateMedidas(i)
		}
		

