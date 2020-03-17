calculateMedidas<-function(i,j){	
	
	#Escribo los titulos
	#write("Test",paste('/home/gabina/Facultad/Machine Learning/TP2/Ejercicio a/datosProcesados',i,j,'.txt',sep=""),append = T)

	#Leo los 20 valores de test
	p <- read.csv(paste('/home/gabina/Facultad/Machine Learning/TP2/Ejercicio a/datosProcesados',i,j,'.txt',sep=""))
		
	#Escribo los promedios en el archivos promedios
	write(median(p$Test),"PROMEDIO",append = T,sep=",")
	write(mean(p$Test),"PROMEDIO",append = T,sep=",")
	write(min(p$Test),"PROMEDIO",append = T,sep=",")

	return ()
}

	for(i in 1:3){
		for(j in 1:3){
			calculateMedidas(i,j)
		}
	}
		

