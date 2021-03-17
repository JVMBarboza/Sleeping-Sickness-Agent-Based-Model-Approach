#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*######################## SIMULATION PARAMETERS ######################*/

int  totalOfYears                         = 10;
char anyTreatment                         = 'y'; //any treatment in simulation? y(yes) or n(no)
int treatmProgramTimeDuration             = 365;
int yearOfTreatmentStart[4]               = {2,4,6,8}; 
double diseasedPorcentageToGetInTreatm[4] = {0.50,0.2,0.2,0.2};


/*############################ CONSTANTS #############################*/

#define max 4294967295.0 
unsigned s = 88912125;
unsigned 
R = 8932924
;

//POPULATIONS && TREATMENT
#define LenTseTsePop  50000
#define LenHumanPop   5000
#define LenAnimalsPop 1000

#define initialInfectedHumanPorcetg     0.006  //H:0.6% (SMITH, 2016) 
#define initialInfectedFliesPorcetg     0.024  //F:2.4% (SMITH, 2016) 
#define initialInfectedAnimalsPorcetg   0.18   //A:18%  (SMITH, 2016)

//FLIES CONSTANTS
#define fliesDeathRate 0.021976910177 // (days⁻¹) (ARTZROUNI, M.; GOUTEUX, J.-P. 1996)

#define ProbBiteMax 0.25  //(ARTZROUNI, M.; GOUTEUX, J.-P. 1996)   
#define ProbBiteMin 0.05                 

#define fliesMaxDaysInLatent 30 //(MULLER, G.; GRÉBAUT, P.; GOUTEUX, J.-P. 2004)
#define fliesMinDaysInLatent 15

#define ProbInfectHumanAndAnimals 0.62 //(ROGERS, 1988) 

//HUMANS/ANIMALS             
#define naturalDeathMaxEstim 0.000068490805 // 1/14600 = 1/(365*40) days⁻¹ (SMITH, 2016)
#define naturalDeathMinEstim 0.000045661058 // 1/21900 = 1/(365*60) days⁻¹

#define bloodMealOnHumans 0.333 //(SIMO, 2012) //0.667 //(GREBAUT, 2009) 

#define probInfectFliesMax 0.05 //(SIMARRO,2014) //0.14 //(ARTZROUNI, M.; GOUTEUX, J.-P. 2016)
#define probInfectFliesMin 0.02                  //0.05 

#define cattleDeathRate 0.002735976376 // 1/365 days⁻¹

#define animalsMaxDaysInLatent 14 //(ARTZROUNI, M.; GOUTEUX, J.-P. 1996)
#define animalsMinDaysInLatent 10

#define humansMaxDaysInStgOne 833 //(CHECCHI, F. et al. 2008)
#define humansMinDaysInStgOne 357

#define humansMaxDaysInStgTwo 769 //(CHECCHI, F. et al. 2008)
#define humansMinDaysInStgTwo 345



/*############################# COUNTS AND VARIABLES #########################*/

double countHumanSusceptible         = 0.0,
       countHumanLatency             = 0.0,
       countHumanInfectedStageOne    = 0.0,
       countHumanInfectedStageTwo    = 0.0,
       countHumanRecovered           = 0.0,
       countHumanInTreatment         = 0.0,
       countHumanNaturalDeath        = 0.0,
       countHumanDeathByAge          = 0.0,
       countHumanDeathInfectStageOne = 0.0,
       countHumanDeathInfectStageTwo = 0.0;


int  j         = 0;
char treatment = 'F'; //variable for switch treatment ON/OFF=T/F 

/*########################### Agents Structs ################################*/

/*********** Human Struct and Parameters **********/
struct Human{
    int  age;              
    int  stage;            
    int  stageOfInfection;  
    char diseaseReservt;   
    int  daysInStage;      
    int  daysInTreat;
    double individualProbOfTreatSucces;
    int  treatTotalDays;
    int  stageTotalDays; 
} Human[LenHumanPop];
 
/*********** Flies Struct **********/
struct Fly{
    int  age;
    int  stage;           
    char diseaseReservt;  
    int  daysWithoutEat;  
    int  daysInStage; 
    int  stageTotalDays;  
} TseTse[LenTseTsePop];

/*********** Animals Struct **********/
struct Cattle{
    int  age;
    int  stage;         
    char diseaseReservt;
    int  daysInStage;
    int  stageTotalDays; 
} Animal[LenAnimalsPop];




/*##################################################################################*/
/*####################### Pseudo Random Gen Functions ##############################*/
/*##################################################################################*/

/***** Pseudo Random Number Generator (0-1) *****/
double sortRandomNumber(unsigned *R){
    *R=*R*s;
    return (*R/max);
}

//hint: sort int number between 10 14 -> SortRandomNumberInteger(10,15)
int sortRandomNumberInteger(int minNum, int maxNum){
    return ( sortRandomNumber(&R)*(maxNum-minNum)+minNum );
}




/*##################################################################################*/
/*##########################  Sort Intervals Functions   ###########################*/
/*##################################################################################*/

//Calculate probability of human natural death from interval: 4.56621e-5 - 6.849315e-5
double deathNaturalEstim(){
    return ( sortRandomNumber(&R)*(naturalDeathMaxEstim-naturalDeathMinEstim) + naturalDeathMinEstim );
}

//Calculate probability of fly bite human/cattle from interval: 0.25-0.05
double ProbBite(){
    return ( sortRandomNumber(&R)*(ProbBiteMax - ProbBiteMin) + ProbBiteMin );
}

//Calculate probability of fly get infected from interval: 0.02-0.05
double ProbFlyGetInfect(){
    return ( sortRandomNumber(&R)*(probInfectFliesMax - probInfectFliesMin) + probInfectFliesMin );
    //return probInfectFly;
}

//Calculate probability of fly transmit infection from fixed value 0.62
double ProbFlyInfect(){
    return ProbInfectHumanAndAnimals;
    //return (sortRandomNumber(&R)*(ProbInfectHumanAndAnimalsMax-ProbInfectHumanAndAnimalsMin) + ProbInfectHumanAndAnimalsMin);
}

//Sort duration in the interval:10-14 days  
int calcHumanAndAnimalsLatentDurantionDays(){
    return sortRandomNumberInteger(animalsMinDaysInLatent,animalsMaxDaysInLatent+1);
}

//Sort duration in the interval:357-833 days
int calculateInfectStageOneDuration(){
    return sortRandomNumberInteger(humansMinDaysInStgOne,humansMaxDaysInStgOne+1);
}

//Sort duration in the interval:345-769 days
int calculateInfectStageTwoDuration(){
    return sortRandomNumberInteger(humansMinDaysInStgTwo,humansMaxDaysInStgTwo+1);
}

//Calculate initial ages in the population by distribution(britannica.com/place/Republic-of-the-Congo/Demographic-trends)
int calcAgeByDistribution(){
    
    double rn = sortRandomNumber(&R);

    //SORT VALUES AROUND 7 YEARS: 7 +/- 1 (Fexinidazole only applies in children >= 6 years old)
    if(rn<0.20)  
        return ( 7*365+sortRandomNumberInteger( (1*365)*(-1), 2*365) );

    //SORT VALUES AROUND 12 YEARS: +/- 2
    if(rn>=0.20 && rn<(0.20+0.169) ) 
        return ( 12*365+sortRandomNumberInteger( (2*365)*(-1), 2*365) );
    
    //SORT VALUES AROUND 17 YEARS: +/- 2
    if(rn>=(0.20+0.169) && rn<(0.20+0.169+0.103))
        return ( 17*365+sortRandomNumberInteger( (2*365)*(-1), 2*365) );

    //SORT VALUES AROUND 22 YEARS: +/- 2)
    if(rn>=(0.20+0.169+0.103) && rn<(0.20+0.169+0.103+0.09))
        return ( 22*365+sortRandomNumberInteger( (2*365)*(-1), 2*365) );

    //SORT VALUES AROUND 27 YEARS: +/- 2)
    if(rn>=(0.20+0.169+0.103+0.09) && rn<(0.20+0.169+0.103+0.09+0.088))
        return ( 27*365+sortRandomNumberInteger( (2*365)*(-1), 2*365) );

    //SORT VALUES AROUND 32 YEARS: +/- 2)
    if(rn>=(0.20+0.169+0.103+0.09+0.088) && rn<(0.20+0.169+0.103+0.09+0.088+0.073))
        return ( 32*365+sortRandomNumberInteger( (2*365)*(-1), 2*365) );

    //SORT VALUES AROUND 37 YEARS: +/- 2)
    if(rn>=(0.20+0.169+0.103+0.09+0.088+0.073) && rn<(0.20+0.169+0.103+0.09+0.088+0.073+0.066))
        return ( 37*365+sortRandomNumberInteger( (2*365)*(-1), 2*365) );

    //SORT VALUES AROUND 42 YEARS: +/- 2)
    if(rn>=(0.20+0.169+0.103+0.09+0.088+0.073+0.066) && rn<(0.20+0.169+0.103+0.09+0.088+0.073+0.066+0.059))
        return ( 42*365+sortRandomNumberInteger( (2*365)*(-1), 2*365) );

    //SORT VALUES AROUND 47 YEARS: +/- 2)
    if(rn>=(0.20+0.169+0.103+0.09+0.088+0.073+0.066+0.059) && rn<(0.20+0.169+0.103+0.09+0.088+0.073+0.066+0.059+0.051))
        return ( 47*365+sortRandomNumberInteger( (2*365)*(-1), 2*365) );

    //SORT VALUES AROUND 52 YEARS: +/- 2)
    if(rn>=(0.20+0.169+0.103+0.09+0.088+0.073+0.066+0.059+0.051) && rn<(0.20+0.169+0.103+0.09+0.088+0.073+0.066+0.059+0.051+0.053))
        return ( 52*365+sortRandomNumberInteger( (2*365)*(-1), 2*365) );

    //SORT VALUES AROUND 57 YEARS: +/- 2)
    if(rn>=(0.20+0.169+0.103+0.09+0.088+0.073+0.066+0.059+0.051+0.053) && rn<(1.0)) //0.20+0.169+0.103+0.09+0.088+0.073+0.066+0.059+0.051+0.053+0.045
        return ( 57*365+sortRandomNumberInteger( (2*365)*(-1), 2*365) );

}

//sort duration in the interval:15-30 days  
int calculateFliesLatentDurantionDays(){
    return sortRandomNumberInteger(fliesMinDaysInLatent,fliesMaxDaysInLatent+1);
}



/*##################################################################################*/
/*######################### Change of state related functions ######################*/
/*##################################################################################*/

/*#### FLIES #####*/
void resetIndividualFlies(int coorde){

    TseTse[coorde].age            = 0;
    TseTse[coorde].stage          = 0;
    TseTse[coorde].diseaseReservt = 'n';
    TseTse[coorde].daysInStage    = 0;
    TseTse[coorde].stageTotalDays = 0;
    TseTse[coorde].daysWithoutEat = 0;
}

int calcDeathByAgeFlies(int coord){
    if(TseTse[coord].age >= 60){
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
    if(Animal[coord].age >= 365){
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



/*##################################################################################*/
/*########################## Inter Species(BITE) Funtions ######################*/
/*##################################################################################*/

int sortHumanOrAnimalToBeBited(){
    double rn = sortRandomNumber(&R);
    if(rn < bloodMealOnHumans)
        return 1; //HUMAN
    else
        return 2; //ANIMAL
    
}

//Simulate fly biting indiv infected(sort individual to be bited) 
void verifiesSusceptbFlyGetInfection(int coorde){
    
    double rn  = sortRandomNumber(&R);
    int    key = sortHumanOrAnimalToBeBited();
    
    int individualSelected;
        
    if(key==1){//Human bited      
        individualSelected = sortRandomNumberInteger(0,5000);
        if(Human[individualSelected].diseaseReservt=='y' && rn<ProbFlyGetInfect()){//infection takes place
            fromSuscpToLatentFlies(coorde); //change the state of selected fly
        }
    }
    
    if(key==2){//Animal bited
        individualSelected = sortRandomNumberInteger(0,1000);
        if(Animal[individualSelected].diseaseReservt=='y' && rn<ProbFlyGetInfect()){//infection takes place
            fromSuscpToLatentFlies(coorde); //change the state of selected fly
        }
    }
        
}

//Simulate infected fly biting indiv(sort healthy human or animal to be infected)
void verifiesInfectedFlyTransmitInfection(){

    double rn = sortRandomNumber(&R);
    int   key = sortHumanOrAnimalToBeBited();
    
    int individualSelected;

    if(key==1){//Bite on Human 
        individualSelected = sortRandomNumberInteger(0,5000);
        if(Human[individualSelected].stage==0 && rn<ProbFlyInfect()){//infection takes place    
            fromSuscpToLatent(individualSelected); //change state of selected SUSCEPTIBLE HUMAN
        }
    }

    if(key==2){//Bite on Animal 
        individualSelected = sortRandomNumberInteger(0,1000);
        if(Animal[individualSelected].stage==0 && rn<ProbFlyInfect()){//infection takes place
            fromSuscpToLatentAnimals(individualSelected); //change the state of selected SUSCEPTIBLE ANIMAL
        }
    }

}

//Simulate bite
void verifiesBite(int coord){
    
    double rn = sortRandomNumber(&R);

    //bite 
    if(rn<ProbBite() && TseTse[coord].daysWithoutEat>=3){        
        
        if(TseTse[coord].stage == 0){
            verifiesSusceptbFlyGetInfection(coord);
        }
        if(TseTse[coord].stage == 2){
            verifiesInfectedFlyTransmitInfection();
        }
        TseTse[coord].daysWithoutEat=0;
    }
    else{ //didnt bite
        TseTse[coord].daysWithoutEat++;
    }

}




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




/*##################################################################################*/
/*############################### Lattice functions ################################*/
/*##################################################################################*/

void generateInitialLattice(){
    
    int i;
    
    for (i = 0; i < (int)(LenTseTsePop); i++){ //Generating Flies pop
        TseTse[i].age            = sortRandomNumberInteger(0,60);
        TseTse[i].stage          = 0;
        TseTse[i].daysWithoutEat = sortRandomNumberInteger(0,4); 
        TseTse[i].daysInStage    = 1;
        TseTse[i].stageTotalDays = 0;
        TseTse[i].diseaseReservt = 'n';
    }

    for (i = 0; i < (int)(LenHumanPop); i++){  //Generating human population
        Human[i].age              = calcAgeByDistribution();
        Human[i].stage            = 0;
        Human[i].stageOfInfection = 0;
        Human[i].diseaseReservt   = 'n';
        Human[i].daysInStage      = 1;
        Human[i].daysInTreat      = 0;
        Human[i].individualProbOfTreatSucces = 0.0;
        Human[i].treatTotalDays   = 0;
        Human[i].stageTotalDays   = 0;
        countHumanSusceptible++;
    }

    for (i = 0; i < (int)(LenAnimalsPop); i++){ //Generating Animals pop
        Animal[i].age            = sortRandomNumberInteger(0,366); 
        Animal[i].stage          = 0;
        Animal[i].diseaseReservt = 'n';
        Animal[i].daysInStage    = 1;
        Animal[i].stageTotalDays = 0;
    }
}

void generateInitialInfectedPopulation(){
    
    int indiv;

    for(indiv=0; indiv<(int)(LenTseTsePop); indiv++){
        if (sortRandomNumber(&R)<initialInfectedFliesPorcetg){
            TseTse[indiv].stage          = 2;
            TseTse[indiv].daysInStage    = 1;
            TseTse[indiv].stageTotalDays = 0;
            TseTse[indiv].diseaseReservt = 'y';
        }
    }

    for(indiv=0; indiv<(int)(LenHumanPop); indiv++){
        if (sortRandomNumber(&R)<initialInfectedHumanPorcetg){
            Human[indiv].stage            = 2;
            Human[indiv].stageOfInfection = 1;
            Human[indiv].diseaseReservt   = 'y';
            Human[indiv].daysInStage      = 1;
            Human[indiv].daysInTreat      = 0;
            Human[indiv].individualProbOfTreatSucces = 0.0;
            Human[indiv].treatTotalDays   = 0;
            Human[indiv].stageTotalDays   = calculateInfectStageOneDuration();

            countHumanSusceptible--;
            countHumanInfectedStageOne++;
        }
    }
    
    for(indiv=0; indiv<(int)(LenAnimalsPop); indiv++){
        if (sortRandomNumber(&R)<initialInfectedAnimalsPorcetg){
            Animal[indiv].stage          = 2;
            Animal[indiv].diseaseReservt = 'y';
            Animal[indiv].daysInStage    = 1;
            Animal[indiv].stageTotalDays = 0;
        }
    }
}

void updateIndiv(int coord){
    
    Human[coord].age++;
    Human[coord].daysInStage++;
    if(Human[coord].daysInTreat!=0){
        Human[coord].daysInTreat++;
    }
}

void updateIndivTimeFlies(int coord){
    TseTse[coord].age++;
    TseTse[coord].daysInStage++;
}

void updateIndivTimeAnimals(int coord){
    Animal[coord].age++;
    Animal[coord].daysInStage++;
}





/* ################################################################################## */
/* ############################### MAIN FUNCTION #################################### */
/* ################################################################################## */

int main(){
    
    //LOCAL CONSTANTS TO BE USED
    int time,
        indiv;

    int yesterdayTotalInfective=0, yesterdayTotalDeath=0;

    //FILE MANAGEMENT
    FILE *of; //output file
    of = fopen("file.csv","w");
    fprintf(of,"Time,Susceptible,Latent,Infection Stage 1,Infection Stage 2,Total Infected,Recovered,In Treatment,Natural Death,Stage 1 Death,Stage 2 Death,Total Infection Death,Daily New Infective,Daily Deaths\n");



    //STARTING UP 
    generateInitialLattice();            //generate lattice
    generateInitialInfectedPopulation(); //generate infectives
    printf("INITIAL:\tS:%g\tL:%g\tI:%g\n",countHumanSusceptible,countHumanLatency,countHumanInfectedStageOne);

    //SYSTEM DYNAMICS
    for (time = 1; time <= 365*totalOfYears; time++){

        //Study Treatment Implementation in the step
        if( time == 365*yearOfTreatmentStart[j] ){
            if(anyTreatment=='y'){
                startTreatmInLattice();
            }
        }
    
        //FLIES
        for(indiv = 0; indiv < (int)(LenTseTsePop); indiv++){
            
            if(calcDeathByAgeFlies(indiv)==0 && calcFliesDailyDeath(indiv)==0){//indiv not dead
                
                switch(TseTse[indiv].stage){
                    case 0: //susceptible
                        verifiesBite(indiv);
                        updateIndivTimeFlies(indiv);
                        break;

                    case 1: //latent
                        if(TseTse[indiv].daysInStage == TseTse[indiv].stageTotalDays)
                            fromLatentToInfectedFlies(indiv);

                        verifiesBite(indiv);
                        updateIndivTimeFlies(indiv);
                        break;

                    case 2: //infective
                        verifiesBite(indiv);
                        updateIndivTimeFlies(indiv);
                        break;
                }
            }//FLIES SWITCH END
        }//FLIES POPULATOIN FOR END
               
        //HUMANS
        for(indiv = 0; indiv < (int)(LenHumanPop);  indiv++){

            if(calcProbNaturalDeath(indiv)==0 && calcDeathByAge(indiv)==0){ //VERIFIES INDIV DIDNT DIE FROM NATURAL CAUSES NOR BY AGE
                switch(Human[indiv].stage){
                    case 0: //Susceptible
                        updateIndiv(indiv);//susceptible
                        break;

                    case 1: //Latent
                        if(Human[indiv].daysInStage == Human[indiv].stageTotalDays){
                            fromLatentToInfected(indiv);//max days reached
                        }
                        updateIndiv(indiv);
                        break;

                    case 2: //Infected 
                        //if(calcProbInfectDeath(indiv)==0){//VERIFIES INDIV. DIDNT DIE BY INFECTION
                            
                        if(Human[indiv].stageOfInfection == 1){ //stg 1 of disease
                            if(Human[indiv].daysInTreat==0 && Human[indiv].daysInStage==Human[indiv].stageTotalDays){ //not in treatm
                                fromInfectedStageOneToStageTwo(indiv);
                            }
                            if(Human[indiv].daysInTreat!=0 && Human[indiv].daysInTreat==Human[indiv].treatTotalDays){ //in treatm
                                verifyTreatmSucessOnIndiv(indiv);
                            }
                            updateIndiv(indiv);
                        }
                        
                        if(Human[indiv].stageOfInfection == 2){ //stg 2 of disease
                            
                            //reached end of therapy
                            if(Human[indiv].daysInTreat!=0 && Human[indiv].daysInTreat==Human[indiv].treatTotalDays){
                                verifyTreatmSucessOnIndiv(indiv);
                            }
                            //reached max days in stage 2
                            if(Human[indiv].daysInStage==Human[indiv].stageTotalDays){
                                resetIndividual(indiv);
                            }
                            
                            updateIndiv(indiv);
                        }    
                        //}
                        
                        break;

                    case 3: //recovered
                        updateIndiv(indiv);
                        break;

                }//HUMAN SWITCH END
            }
        }//HUMAN POPULATION FOR END

        //ANIMALS
        for(indiv = 0; indiv < (int)(LenAnimalsPop); indiv++){
            
            if(calcDeathByAgeAnimals(indiv)==0 && calcAnimalsDailyDeath(indiv)==0){
                switch(Animal[indiv].stage){
                    case 0: //susceptible
                        updateIndivTimeAnimals(indiv);
                        break;

                    case 1: //latent
                        if(Animal[indiv].daysInStage >= Animal[indiv].stageTotalDays)
                            fromLatentToInfectedAnimals(indiv);
                        
                        updateIndivTimeAnimals(indiv);
                        break;

                    case 2: //infected
                        updateIndivTimeAnimals(indiv);
                        break;
                }
            }
        }
                
                
        //UPDATES
        updateTreatm();


        //PRINTING DATA ON THE SCREEN
        printf("Done:%i%%  t:%i  S:%i  L:%i  I-stg1:%i  I-stg2:%i  R:%i  In treatm:%i  ND:%i AD:%i  D-sg1:%i D-sg2:%i  Sum:%i\n",(100*time)/(10*365),
                                                                                                                           (int)(time),
                                                                                                                           (int)(countHumanSusceptible),
                                                                                                                           (int)(countHumanLatency),
                                                                                                                           (int)(countHumanInfectedStageOne),
                                                                                                                           (int)(countHumanInfectedStageTwo),
                                                                                                                           (int)(countHumanRecovered),
                                                                                                                           (int)(countHumanInTreatment),
                                                                                                                           (int)(countHumanNaturalDeath),
                                                                                                                           (int)(countHumanDeathByAge),
                                                                                                                           (int)(countHumanDeathInfectStageOne),
                                                                                                                           (int)(countHumanDeathInfectStageTwo),
                                                                                                                           (int)(countHumanDeathInfectStageOne+countHumanDeathInfectStageTwo));
        
        //WRITING DATA IN OUTPUT FILE
        fprintf(of,"%i,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g\n",time,
                                                           (countHumanSusceptible)/5000.0,
                                                           (countHumanLatency)/5000.0,
                                                           (countHumanInfectedStageOne)/5000.0,
                                                           (countHumanInfectedStageTwo)/5000.0,
                                                           (countHumanInfectedStageOne+countHumanInfectedStageTwo-countHumanInTreatment)/5000.0,
                                                           (countHumanRecovered)/5000.0,
                                                           (countHumanInTreatment)/5000.0,
                                                           (countHumanNaturalDeath),
                                                           (countHumanDeathInfectStageOne),
                                                           (countHumanDeathInfectStageTwo),
                                                           (countHumanDeathInfectStageOne+countHumanDeathInfectStageTwo),
                                                           (countHumanInfectedStageOne+countHumanInfectedStageTwo)-yesterdayTotalInfective,
                                                           (countHumanDeathInfectStageOne+countHumanDeathInfectStageTwo)-yesterdayTotalDeath);
    
        yesterdayTotalInfective = countHumanInfectedStageOne+countHumanInfectedStageTwo;
        yesterdayTotalDeath     = countHumanDeathInfectStageOne+countHumanDeathInfectStageTwo;
    
    }//END MAIN FOR
    

    //CLOSING FILE
    fclose(of);

    return 0;
}