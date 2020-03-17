		echo "Train, Validation, Test" >  MSE/dos_elipses33.mse
		

		sed -r 's/.{27}$//' dos_elipses33.mse > dos_elipses332.mse #saca de atras
		sed -r 's/.{9}//' dos_elipses332.mse > dos_elipses333.mse #saca de adelate
		
		
		head -n -1900 dos_elipses333.mse >>	MSE/dos_elipses33.mse 
		rm dos_elipses332.mse
		rm dos_elipses333.mse		 
