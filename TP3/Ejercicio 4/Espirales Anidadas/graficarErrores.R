	for(i in 1:3){
			jpeg("errorea.jpeg")
			test <- read.csv("/home/gabina/Facultad/Machine Learning/TP3/Ejercicio 4/Espirales Anidadas/test.txt")
			train <- read.csv("/home/gabina/Facultad/Machine Learning/TP3/Ejercicio 4/Espirales Anidadas/train.txt")
			valid <- read.csv("/home/gabina/Facultad/Machine Learning/TP3/Ejercicio 4/Espirales Anidadas/validacion.txt")
			a<-c(1,2,5,8,10,12,15,20,25,30,50,70,100,200,300,1000)
			plot(a,test[,1],col=3,xlab="Cantidad de bins", ylab="Error porcentual",ylim=c(min(train),max(test)))
			lines(a,test[,1],col=3)
			points(a,train[,1],col=4)
			lines(a,train[,1],col=4)
			points(a,valid[,1],col=2)
			lines(a,valid[,1],col=2)
			dev.off()
			
			
			jpeg("errorea2.jpeg")
			test <- read.csv("/home/gabina/Facultad/Machine Learning/TP3/Ejercicio 4/Espirales Anidadas/test.txt")
			train <- read.csv("/home/gabina/Facultad/Machine Learning/TP3/Ejercicio 4/Espirales Anidadas/train.txt")
			valid <- read.csv("/home/gabina/Facultad/Machine Learning/TP3/Ejercicio 4/Espirales Anidadas/validacion.txt")
			a<-c(1,2,5,8,10,12,15,20,25,30,50,70,100)
			plot(a,test[,1],col=3,xlab="Cantidad de bins", ylab="Error porcentual",ylim=c(min(train),max(test)))
			lines(a,test[,1],col=3)
			points(a,train[,1],col=4)
			lines(a,train[,1],col=4)
			points(a,valid[,1],col=2)
			lines(a,valid[,1],col=2)
			dev.off()			
		}

Bins[1]='1'
Bins[2]='2'
Bins[3]='5'
Bins[4]='8'
Bins[5]='10'
Bins[6]='12'
Bins[7]='15'
Bins[8]='20'
Bins[9]='25'
Bins[10]='30'
Bins[11]='50'
Bins[12]='70'
Bins[13]='100'
Bins[14]='200'
Bins[15]='300'
Bins[16]='1000'
