calculateMedidas<-function(i){	
	
	#Leo los 20 valores de test
	p <- read.csv(paste('/home/gabina/Facultad/Machine Learning/TP4/Ejercicio c/datosProcesadosA',i,'.txt',sep=""))
		
	#Escribo los promedios en el archivos promedios

	write(mean(p$Test),"PROMEDIOA",append = T,sep=",")
	#write(mean(p$Validación),"PROMEDIOA",append = T,sep=",")
	
	#Leo los 20 valores de test
	p <- read.csv(paste('/home/gabina/Facultad/Machine Learning/TP4/Ejercicio c/datosProcesadosB',i,'.txt',sep=""))
		
	#Escribo los promedios en el archivos promedios

	write(mean(p$Test),"PROMEDIOB",append = T,sep=",")	
	#write(mean(p$Validación),"PROMEDIOB",append = T,sep=",")	
	
	return ()
}

	for(i in 1:5){
			calculateMedidas(i)
		}
		

