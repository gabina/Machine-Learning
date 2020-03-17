graficar<-function(i){	
	
	jpeg(paste("prediccion",i,".jpeg",sep=""))
	p <- read.csv(paste('/home/gabina/Facultad/Machine Learning/TP3/Ejercicio 4/Espirales Anidadas/EspiralesAnidadas/espirales',i,'.predic',sep=""))
	plot(p[,1], p[,2],col=p[,3]+2)
	dev.off()

	return ()
}

	for(i in 1:16){
			graficar(i)
		}
		
	jpeg("espirales.jpeg")
	p <- read.csv("/home/gabina/Facultad/Machine Learning/TP3/Ejercicio 4/Espirales Anidadas/EspiralesAnidadas/espirales.data")
	plot(p[,1], p[,2],col=p[,3]+2)
	dev.off()

	jpeg("xor1.jpeg")
	p <- read.csv("/home/gabina/Facultad/Machine Learning/TP3/Ejercicio 4/xor/xor.predic")
	plot(p[,1], p[,2],col=p[,3]+2)
	dev.off()

	jpeg("xor2.jpeg")
	p <- read.csv("/home/gabina/Facultad/Machine Learning/TP3/Ejercicio 4/xor/xor.predic")
	plot(p[,1], p[,2],col=p[,3]+2)
	dev.off()

	jpeg("esp.jpeg")
	p <- read.csv("/home/gabina/Facultad/Machine Learning/TP3/Ejercicio 5/espirales1.predic")
	plot(p[,1], p[,2],col=p[,3]+2)
	dev.off()
