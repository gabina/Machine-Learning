#!/bin/bash

grep "Accuracy on test set: " resultadosSVM.txt > resultadosSVM2.txt

sed -r 's/.{38}$//' resultadosSVM2.txt > resultadosSVM3.txt
sed -r 's/.{22}//'  resultadosSVM3.txt > resultadosSVM.txt
rm resultadosSVM2.txt
rm resultadosSVM3.txt
