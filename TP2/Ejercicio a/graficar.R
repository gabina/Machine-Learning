	for(i in 1:3){
		for(j in 1:3){
			jpeg(paste("/home/gabina/Facultad/Machine Learning/TP2/Ejercicio a/MSE/mse",i,j,sep="","e.jpeg"))
			p <- read.csv(paste('/home/gabina/Facultad/Machine Learning/TP2/Ejercicio a/MSE/dos_elipses',i,j,".mse",sep=""))
			a<-seq(0,39600,400)
			plot(a,p[,1],col=4,xlab="Épocas", ylab="MSE",main="MSE en función de las épocas",  ylim=c(0, max(p)))
			lines(a,p[,1],col=4)
			points(a,p[,2],col=2)
			lines(a,p[,2],col=2)
			points(a,p[,3],col=3)
			lines(a,p[,3],col=3)
			dev.off()
		}
	}
