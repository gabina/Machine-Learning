getDistance<-function(vector, mu){
	dist <- 0
	dim <- 5	
	for(i in 1:dim){
		dist <- dist + (vector[i] - mu[i]) ** 2		
	}	
	return (dist ** 0.5)
}

getClass<-function(vector, mu0,mu1){
	dist0 <- getDistance(vector, mu0)
	dist1 <- getDistance(vector, mu1)
	if (dist0 < dist1){
		return (0)
	}
	else {if (dist1 < dist0){
			return (1)
		}
		else{
			return (floor(runif(1,0,2)))
		}	
	}

}

calculateError<-function(p,mu0,mu1,v,name){
	error <- 0
	for(i in 1:9999){
		v[i] <- getClass(p[i,],mu0,mu1)
		if( v[i] != p[i,6]){
			error <- error + 1
		}
	}
	return (error / 999)
}


mu0 <- rep(-1,5)
mu1 <- rep(1,5)
v <- rep(0,99999)

p <- read.csv('/home/gabina/Facultad/Machine Learning/TP1/Ejercicio 6/6.1/gausianasA0.data')
e <- calculateError(p,mu0,mu1,v,"clasificacionIdealA1")
write(e,"data1")

p <- read.csv('/home/gabina/Facultad/Machine Learning/TP1/Ejercicio 6/6.1/gausianasA1.data')
e <- calculateError(p,mu0,mu1,v,"clasificacionIdealA2")
write(e,"data2")

p <- read.csv('/home/gabina/Facultad/Machine Learning/TP1/Ejercicio 6/6.1/gausianasA2.data')
e <- calculateError(p,mu0,mu1,v,"clasificacionIdealA3")
write(e,"data3")

p <- read.csv('/home/gabina/Facultad/Machine Learning/TP1/Ejercicio 6/6.1/gausianasA3.data')
e <- calculateError(p,mu0,mu1,v,"clasificacionIdealA4")
write(e,"data4")

p <- read.csv('/home/gabina/Facultad/Machine Learning/TP1/Ejercicio 6/6.1/gausianasA4.data')
e <- calculateError(p,mu0,mu1,v,"clasificacionIdealA5")
write(e,"data5")






