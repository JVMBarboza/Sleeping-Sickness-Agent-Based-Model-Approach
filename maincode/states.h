/*##################################################################################*/
/*######################### Change of state related functions ######################*/
/*##################################################################################*/

/*#### FLIES #####*/
void resetIndividualFlies(int coorde){

    TseTse[coorde].age            = 0;
    TseTse[coorde].stage          = 0;
    TseTse[coorde].diseaseReservt = 'n';
    TseTse[coorde].firstMeal      = 'y';
    TseTse[coorde].daysInStage    = 0;
    TseTse[coorde].stageTotalDays = 0;
    TseTse[coorde].daysWithoutEat = 0;
}

int calcDeathByAgeFlies(int coord){
    if(TseTse[coord].age >= fliesMaxAge){
        resetIndividualFlies(coord);
        return 1;
    }
    else{
        return 0;
    }
}

int calcFliesDailyDeath(int coord){

    if(sortRandomNumber(&R) < fliesDeathRate){
        resetIndividualFlies(coord);
        return 1;
    }
    else{
        return 0;
    }
}

void fromSuscpToLatentFlies(int coorde){
    TseTse[coorde].stage          = 1;
    TseTse[coorde].daysInStage    = 0;
    TseTse[coorde].diseaseReservt = 'n';
    TseTse[coorde].stageTotalDays = calculateFliesLatentDurantionDays();
}

void fromLatentToInfectedFlies(int coorde){
    TseTse[coorde].stage          = 2;
    TseTse[coorde].daysInStage    = 0;
    TseTse[coorde].diseaseReservt = 'y';
    TseTse[coorde].stageTotalDays = 0;
}

/*#### HUMANS ####*/
void resetIndividual(int coorde){

    if(Human[coorde].age >= 60*365){ //DEATH BY AGE
        switch(Human[coorde].stage){ 
            case 0://indiv died in susceptible stage
                countHumanDeathByAge++;
                break;
            
            case 1://indiv died in latent stage
                countHumanLatency--;
                countHumanSusceptible++;
                countHumanDeathByAge++;
                break;

            case 2://indiv died in infective stage
                
                if(Human[coorde].stageOfInfection == 1){
                    if(Human[coorde].daysInTreat!=0)
                        countHumanInTreatment--; //died during treatm.

                    countHumanDeathByAge++;
                    countHumanInfectedStageOne--;
                }

                if(Human[coorde].stageOfInfection == 2){
                    if(Human[coorde].daysInTreat!=0)
                        countHumanInTreatment--; //died during treatm.
                        
                    countHumanDeathByAge++;
                    countHumanInfectedStageTwo--;
                }
                countHumanSusceptible++;
                break;
            
            case 3://indiv died in recovered state
                countHumanDeathByAge++;
                countHumanRecovered--;
                countHumanSusceptible++;
                break;
        }
    }
    if(Human[coorde].age < 60*365){ //DEATH BY NATURAL CAUSE OR INFECTION
        switch(Human[coorde].stage){ 
            case 0://indiv died in susceptible stage
                countHumanNaturalDeath++;
                break;
            
            case 1://indiv died in latent stage
                countHumanLatency--;
                countHumanSusceptible++;
                countHumanNaturalDeath++;
                break;

            case 2://indiv died in infective stage
                
                if(Human[coorde].stageOfInfection == 1){
                    
                    if(Human[coorde].daysInTreat!=0) 
                        countHumanInTreatment--; //died during treatm.
                    
                    countHumanDeathInfectStageOne++;
                    countHumanInfectedStageOne--;
                }

                if(Human[coorde].stageOfInfection == 2){
                    if(Human[coorde].daysInTreat!=0)
                        countHumanInTreatment--; //died during treatm.

                    countHumanDeathInfectStageTwo++;
                    countHumanInfectedStageTwo--;
                }

                countHumanSusceptible++;
                break;
            
            case 3://indiv died in recovered state
                countHumanNaturalDeath++;
                countHumanRecovered--;
                countHumanSusceptible++;
                break;
        }    
    }
    
    Human[coorde].age              = calcAgeByDistribution();
    Human[coorde].stage            = 0;
    Human[coorde].stageOfInfection = 0;
    Human[coorde].diseaseReservt   = 'n';
    Human[coorde].daysInStage      = 0;
    Human[coorde].daysInTreat      = 0;
    Human[coorde].individualProbOfTreatSucces = 0.0;
    Human[coorde].treatTotalDays   = 0;
    Human[coorde].stageTotalDays   = 0;
    
}

//Death related function: returns 1->if indiv passed |0-> still alive
int calcProbNaturalDeath(int coord){ 

    if(sortRandomNumber(&R) < deathNaturalEstim()){
        resetIndividual(coord);
        return 1;
    }
    else{
        return 0;
    }                    

}

int calcDeathByAge(int coord){
    if(Human[coord].age >= 60*365){
        resetIndividual(coord);
        return 1;
    }
    else{
        return 0;
    }
}

void fromSuscpToLatent(int coord){

    Human[coord].stage            = 1;
    Human[coord].stageOfInfection = 0;
    Human[coord].diseaseReservt   = 'n';
    Human[coord].daysInStage      = 0;
    Human[coord].daysInTreat      = 0;
    Human[coord].individualProbOfTreatSucces = 0.0;
    Human[coord].treatTotalDays   = 0;
    Human[coord].stageTotalDays   = calcHumanAndAnimalsLatentDurantionDays();

    countHumanSusceptible--;
    countHumanLatency++;
}
    
void fromLatentToInfected(int coord){
    
    Human[coord].stage            = 2;
    Human[coord].stageOfInfection = 1;
    Human[coord].diseaseReservt   = 'y';
    Human[coord].daysInStage      = 0;
    Human[coord].daysInTreat      = 0;
    Human[coord].individualProbOfTreatSucces = 0.0;
    Human[coord].treatTotalDays   = 0;
    Human[coord].stageTotalDays   = calculateInfectStageOneDuration();
    
    countHumanLatency--;
    countHumanInfectedStageOne++;
}

void fromInfectedStageOneToStageTwo(int coord){
    
    Human[coord].stage            = 2;
    Human[coord].stageOfInfection = 2;
    Human[coord].diseaseReservt   = 'n';
    Human[coord].daysInStage      = calculateInfectStageTwoDuration();
    Human[coord].daysInTreat      = 0;
    Human[coord].individualProbOfTreatSucces = 0.0;
    Human[coord].treatTotalDays   = 0;
    Human[coord].stageTotalDays   = 0;

    countHumanInfectedStageOne--;
    countHumanInfectedStageTwo++;
}

void fromInfectedStageOneToRecovered(int coord){
    
    Human[coord].stage            = 3;
    Human[coord].stageOfInfection = 0;
    Human[coord].diseaseReservt   = 'n';
    Human[coord].daysInStage      = 1;
    Human[coord].daysInTreat      = 0;
    Human[coord].individualProbOfTreatSucces = 0.0;
    Human[coord].treatTotalDays   = 0;
    Human[coord].stageTotalDays   = 0;
    
    countHumanInfectedStageOne--;
    countHumanRecovered++;
    
}

void fromInfectedStageTwoToRecovered(int coord){
    
    Human[coord].stage            = 3;
    Human[coord].stageOfInfection = 0;
    Human[coord].diseaseReservt   = 'n';
    Human[coord].daysInStage      = 1;
    Human[coord].daysInTreat      = 0;
    Human[coord].individualProbOfTreatSucces = 0.0;
    Human[coord].treatTotalDays   = 0;
    Human[coord].stageTotalDays   = 0;
    
    countHumanInfectedStageTwo--;
    countHumanRecovered++;
}

/*#### ANIMALS ####*/
void resetIndividualAnimal(int coord){
    
    Animal[coord].age            = 0;
    Animal[coord].stage          = 0;
    Animal[coord].diseaseReservt = 'n';
    Animal[coord].daysInStage    = 1;
    Animal[coord].stageTotalDays = 0;
}

int calcDeathByAgeAnimals(int coord){
    if(Animal[coord].age >= animalsMaxAge){               // CONFIRMAR
        resetIndividualAnimal(coord);
        return 1;
    }
    else{
        return 0;
    }
}

int calcAnimalsDailyDeath(int coord){

    if(sortRandomNumber(&R) < cattleDeathRate){
        resetIndividualAnimal(coord);
        return 1;
    }
    else{
        return 0;
    }

}

void fromSuscpToLatentAnimals(int coord){

    Animal[coord].stage          = 1;
    Animal[coord].daysInStage    = 0;
    Animal[coord].diseaseReservt = 'n';
    Animal[coord].stageTotalDays = calcHumanAndAnimalsLatentDurantionDays();
}

void fromLatentToInfectedAnimals(int coorde){
    Animal[coorde].stage          = 2;
    Animal[coorde].daysInStage    = 0;
    Animal[coorde].diseaseReservt = 'y';
    Animal[coorde].stageTotalDays  = 0;

}