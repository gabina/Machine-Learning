calculatePromedio<-function(i,j){	
	
	#Escribo los titulos
	write("Train,Validation,Test",paste('/home/gabina/Facultad/Machine Learning/TP2/Ejercicio a/Promedio',i,j,'/promedios',i,j,sep=""))
				
	for (k in 1:100){
		
		
		#Calculo la epoca
		epoca <- k * 400
		
		#Leo los 20 valores de entrenamiento, validacion y test de la epoca 400 para Promedioij
		p <- read.csv(paste('/home/gabina/Facultad/Machine Learning/TP2/Ejercicio a/Promedio',i,j,'/epoca',epoca,sep=""))
		
		#Calculo el promedio
		promedio <- colSums(p) / dim(p)[1]
		
		#Escribo los promedios en el archivos promedios
		write(c(promedio[1],promedio[2],promedio[3]),paste("Promedio",i,j,"/promedios",i,j,sep=""),append = T,sep=",")

	}
	
	jpeg(paste("/home/gabina/Facultad/Machine Learning/TP2/Ejercicio a/Promedio",i,j,"/mse",i,j,sep="",".jpeg"))
	p <- read.csv(paste('/home/gabina/Facultad/Machine Learning/TP2/Ejercicio a/Promedio',i,j,'/promedios',i,j,sep=""))
	a<-seq(0,39600,400)
	plot(a,p[,1],col=4,xlab="Épocas", ylab="MSE",main="MSE en función de las épocas",sub="Azul -> entrenamiento, Rojo -> validación, Verde -> test")
	lines(a,p[,1],col=4)
	points(a,p[,2],col=2)
	lines(a,p[,2],col=2)
	points(a,p[,3],col=3)
	lines(a,p[,3],col=3)
	dev.off()
	
	return ()
}

	for(i in 1:1){
		for(j in 1:1){
			calculatePromedio(i,j)
		}
	}
		

