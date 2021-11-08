/*#######################################################################*/
/*#################### Treatment related functions ######################*/
/*#######################################################################*/

//value depends on individual age and stage of disease 
int calculateTreatmDuration(int ageInDays, int currentStageOfDisease){
    if(ageInDays<15*365) //independent of stage
        return (365+10); //return 12 months treatm + 10 oral medicine
    else{
        if(ageInDays>=15*365 && currentStageOfDisease==1)
            return (365+10); //return 12 months treatm + 10 oral medicine
        if(ageInDays>=15*365 && currentStageOfDisease==2)
            return (547+10); //return 18 months treatm + 10 oral medicine
    }
}

//value depends on individual age and stage of disease
double calculateTreatmProbSucess(int ageInDays, int currentStageOfDisease){
    if(ageInDays<15*365)
        return 0.976;
    else{
        if(ageInDays>=15*365 && currentStageOfDisease==1)
            return 0.987;
        if(ageInDays>=15*365 && currentStageOfDisease==2)
            return 0.912; 
    }
}

void startTreatmOnIndiv(int coord){
        
    Human[coord].diseaseReservt   = 'n';
    Human[coord].daysInTreat      = 1;
    Human[coord].individualProbOfTreatSucces = calculateTreatmProbSucess(Human[coord].age,Human[coord].stageOfInfection);
    Human[coord].treatTotalDays              = calculateTreatmDuration(Human[coord].age, Human[coord].stageOfInfection);
    
    countHumanInTreatment++;
}

void startTreatmInLattice(){

    int indiv;

    for(indiv=0; indiv<(int)(LenHumanPop); indiv++){

        if(Human[indiv].stage==2 && Human[indiv].daysInTreat==0){
            if(sortRandomNumber(&R) < diseasedPorcentageToGetInTreatm[j]){
                startTreatmOnIndiv(indiv);
            }
        }
    }

    treatment = 'T'; //for updating purposes, notifies main function that the treatment has began
    j++; //notifies system that the next treatm will begin in a different year with different porcentage
}

void updateTreatm(){

    if(treatment == 'T'){
        
        treatmProgramTimeDuration--;
        
        if(treatmProgramTimeDuration==0){
            treatment = 'F';
        }
    }
 
}

void verifyTreatmSucessOnIndiv(int coord){
    
    if(Human[coord].stageOfInfection == 1){
        if(sortRandomNumber(&R) <= Human[coord].individualProbOfTreatSucces){
            fromInfectedStageOneToRecovered(coord); //treatm. SUCCESS
            countHumanInTreatment--;
        }
        else{
            resetIndividual(coord);
        }
    }

    if(Human[coord].stageOfInfection == 2){
        if(sortRandomNumber(&R) <= Human[coord].individualProbOfTreatSucces){
            fromInfectedStageTwoToRecovered(coord);
            countHumanInTreatment--;
        }
        else{
            resetIndividual(coord);
        }
    }

}