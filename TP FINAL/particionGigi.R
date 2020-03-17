### Cross Validation ###

### crossvalidation es una funcion que toma como argumento el número de cross validation y genera 10 archivos con las particiones ###

crossvalidation <- function(x)
{
	p<-read.csv("/home/gabina/Facultad/Machine Learning/TP FINAL/heladas/heladasEscaladas.data",header=F)

	# Proporción de cada clase
	cant <- dim(p)[1]
	prop1 <- dim(p[p$V7 == 1,])[1]/ cant
	prop0 <- dim(p[p$V7 == 0,])[1]/ cant
	# Longitud de cada partición. x es el número de cross-validation
	long <- dim(p)[1]/x
	# Mezclo los datos
	p <- p[sample(nrow(p)),]
	p0 <- p[p$V7 == 0,]
	p1 <- p[p$V7 == 1,]
	#Cantidad de cada clase
	c1 <- floor(long * prop1)
	c0 <- floor(long * prop0)
	# Escribo en los archivos


	### Genero archivos para SVM
	for(i in 1:x){
		#Escribo clase 0
		name <- paste('/home/gabina/Facultad/Machine Learning/TP FINAL/svm_light/heladasSVM/',i,'.data',sep="")
		init <- c0 * (i - 1) + 1
		fin <- c0 * i
		for( j in init:fin){	
			vector <- c(-1, p0[j,]$V1, p0[j,]$V2, p0[j,]$V3, p0[j,]$V4, p0[j,]$V5, p0[j,]$V6)
			write(vector,name,append = T,sep=" X:",ncolumns = 7)
		}
		#Escribo clase 1
		init <- c1 * (i - 1) + 1
		fin <- c1 * i
		for( j in init:fin){	
			vector <- c(+1, p1[j,]$V1, p1[j,]$V2, p1[j,]$V3, p1[j,]$V4, p1[j,]$V5, p1[j,]$V6)
			write(vector,name,append = T,sep=" X:",ncolumns = 7)
		}	
		
	}

	#Si no utilicé todos los puntos de clase 1, los reparto entre los archivos
	if (c1 * x != prop1 * cant){
		fin <- prop1 * cant - c1 * x
		for(i in 1:fin){
			name <- paste('/home/gabina/Facultad/Machine Learning/TP FINAL/svm_light/heladasSVM/',i,'.data',sep="")
			vector <- c(+1, p1[i + c1 * x ,]$V1, p1[i + c1 * x ,]$V2, p1[i + c1 * x ,]$V3, p1[i + c1 * x ,]$V4, p1[i + c1 * x ,]$V5, p1[i + c1 * x ,]$V6)
      write(vector,name,append = T,sep=" X:",ncolumns = 7)			
		}
	}

	#Si no utilicé todos los puntos de clase 0, los reparto entre los archivos, empezando por el último
	if (c0 * x != prop0 * cant){
		fin <- prop0 * cant - c0 * x
		for(i in 1:fin){
			name <- paste('/home/gabina/Facultad/Machine Learning/TP FINAL/svm_light/heladasSVM/',x - i + 1,'.data',sep="")
			vector <- c(-1, p0[i + c0 * x ,]$V1, p0[i + c0 * x ,]$V2, p0[i + c0 * x ,]$V3, p0[i + c0 * x ,]$V4, p0[i + c0 * x ,]$V5, p0[i + c0 * x ,]$V6)
			write(vector,name,append = T,sep=" X:",ncolumns = 7)		
		}
	}	
	
	### Genero archivos normales
	
	for(i in 1:x){
		
		name <- paste('heladas/heladas',i,'.data',sep="")
		init <- c0 * (i - 1) + 1
		fin <- c0 * i
		for( j in init:fin){	
			write.table(p0[j,],name,append = T,sep=",",col.names = F, row.names = F)
		}
		init <- c1 * (i - 1) + 1
		fin <- c1 * i
		for( j in init:fin){	
			write.table(p1[j,],name,append = T,sep=",",col.names = F, row.names = F)
		}	
		
	}

	#Si no utilicé todos los puntos de clase 1, los reparto entre los archivos
	if (c1 * x != prop1 * cant){
		fin <- prop1 * cant - c1 * x
		for(i in 1:fin){
			name <- paste('/home/gabina/Facultad/Machine Learning/TP FINAL/heladas/',i,'.data',sep="")
			write.table(p1[i + c1 * x ,],name,append = T,sep=",",col.names = F, row.names = F)
		}
	}

	#Si no utilicé todos los puntos de clase 0, los reparto entre los archivos, empezando por el último VER
	if (c0 * x != prop0 * cant){
		fin <- prop0 * cant - c0 * x
		for(i in 1:fin){
			name <- paste('/home/gabina/Facultad/Machine Learning/TP FINAL/heladas/',x - i + 1,'.data',sep="")
			write.table(p0[i + c0 * x ,],name,append = T,sep=",",col.names = F, row.names = F)
		}
	}
	return ()
	
}

crossvalidation(10)
