	for(i in 1:9){
			jpeg(paste("/home/gabina/Facultad/Machine Learning/TP2/Ejercicio d/penalizacion",i,sep="",".jpeg"))
			p <- read.csv(paste('/home/gabina/Facultad/Machine Learning/TP2/Ejercicio d/penalizacion',i,".txt",sep=""))
			a<-seq(0,99800,200)
			plot(a,p[,1])
			dev.off()
		}
		
		plot(a,p[,1],col=4,xlab="Épocas", ylab="MSE",main="MSE en función de las épocas", ylim=c(0, 0.01))

			jpeg(paste("/home/gabina/Facultad/Machine Learning/TP2/Ejercicio d/penalizacion4",sep="",".jpeg"))
			p <- read.csv(paste('/home/gabina/Facultad/Machine Learning/TP2/Ejercicio d/penalizacion4',".txt",sep=""))
			a<-seq(0,99800,200)
			plot(a,p[,1],col="orange",xlab="Épocas", ylab="Término de penalización",main="Término de penalización en función de las épocas")
			abline(v=23000,col="black")
			dev.off()

			jpeg(paste("/home/gabina/Facultad/Machine Learning/TP2/Ejercicio d/errorTest1",sep="",".jpeg"))
			p <- read.csv(paste('/home/gabina/Facultad/Machine Learning/TP2/Ejercicio d/ssp1.mse',"",sep=""))
			a<-seq(0,99800,200)
			plot(a,p[,8],col="orange",xlab="Épocas", ylab="Error en test",main="Error en test en función de las épocas")
			#lines(a,p[,8],col="orange")
			dev.off()

			jpeg(paste("/home/gabina/Facultad/Machine Learning/TP2/Ejercicio d/errorTest4",sep="",".jpeg"))
			p <- read.csv(paste('/home/gabina/Facultad/Machine Learning/TP2/Ejercicio d/ssp4.mse',"",sep=""))
			a<-seq(0,99800,200)
			plot(a,p[,8],col="orange",xlab="Épocas", ylab="Error en test",main="Error en test en función de las épocas")
			#lines(a,p[,8],col="orange")
			dev.off()
