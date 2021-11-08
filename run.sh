#!/bin/bash

############################# VARIABLES ######################################

#NAME OF SIMULATION DIRECTORY
simulationName="simulation01"

#R
ran=89212589

#NUMBER OF SIMULATIONS
NumOfSimulations=50


##############################################################################

for i in $(seq 1 $NumOfSimulations);
do
    root=$((ran+i)) #different R value for generate different pseudo random numbers 
    
    cp src/main.c .  #copy maincode and edit with different R value
    sed -i -e "s/\(R = \).*/\1$root/" main.c
    
    echo "#######################################################"
    echo "############      STEP $i START     ###################" 
    echo "#######################################################"
    
    gcc main.c -o exec 
    ./exec

    mv file.csv $simulationName-Contagem$i.csv 
    
    rm main.c exec 
    echo "########## End of step ##########"
    echo "    "
    
done

#MOVING DATA TO SIMULATION DIRECTORY
mkdir $simulationName
mv *.csv $simulationName/
mv $simulationName/ results/

#MANIPULATING DATA
python src/fileManipulation.py
mv result.csv results/$simulationName/

#PLOTING
python src/plot.py