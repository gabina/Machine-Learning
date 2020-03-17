jpeg("espirales150.jpeg")
p <- read.csv('/home/gabina/Facultad/Machine Learning/R8/Data/espirales150a.prediction')
plot(p[,1], p[,2],col=p[,3]+3)
dev.off()