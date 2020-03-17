graficar<-function(i){	
	
	jpeg(paste("prediccion",i,".jpeg",sep=""))
	p <- read.csv(paste('/home/gabina/Facultad/Machine Learning/TP3/Ejercicio 4/DosElipses/dos_elipses',i,'.predic',sep=""))
	plot(p[,1], p[,2],col=p[,3]+2)
	dev.off()

	return ()
}

	for(i in 1:16){
			graficar(i)
		}
		




