	for(i in 1:3){
			jpeg(paste("/home/gabina/Facultad/Machine Learning/TP2/Ejercicio c/MSE/mse",i,sep="","e.jpeg"))
			p <- read.csv(paste('/home/gabina/Facultad/Machine Learning/TP2/Ejercicio c/MSE/ikeda',i,".mse",sep=""))
			a<-seq(0,9950,50)
			plot(a,p[,1],col=4,xlab="Épocas", ylab="MSE",main="MSE en función de las épocas")
			lines(a,p[,1],col=4)
			points(a,p[,2],col=2)
			lines(a,p[,2],col=2)
			points(a,p[,3],col=3)
			lines(a,p[,3],col=3)
			dev.off()
		}

