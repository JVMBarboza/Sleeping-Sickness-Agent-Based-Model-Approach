#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "define.h"

/*######################## SIMULATION PARAMETERS ######################*/

int  totalOfYears                         = 10;
char anyTreatment                         = 'y'; //any treatment in simulation? y(yes) or n(no)
int treatmProgramTimeDuration             = 365;
int yearOfTreatmentStart[4]               = {2,4,6,8}; 
double diseasedPorcentageToGetInTreatm[4] = {0.50,0.20,0.20,0.20};

#define max 4294967295.0 
unsigned s = 88912125;
unsigned 
R = 8932924
;

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
    char firstMeal;  
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


#include "randomNumberGen.h"
#include "intervals.h"
#include "ageDistribution.h"
#include "states.h"
#include "agentsInteractions.h"
#include "treatment.h"

/*##################################################################################*/
/*############################### Lattice functions ################################*/
/*##################################################################################*/

void generateInitialLattice(){
    
    int indiv;
    
    for (indiv = 0; indiv < (int)(LenTseTsePop); indiv++){ //Generating Flies pop
        TseTse[indiv].age            = sortRandomNumberInteger(0,60);
        TseTse[indiv].stage          = 0;
        TseTse[indiv].firstMeal      = 'y';
        TseTse[indiv].daysWithoutEat = sortRandomNumberInteger(0,4); 
        TseTse[indiv].daysInStage    = 1;
        TseTse[indiv].stageTotalDays = 0;
        TseTse[indiv].diseaseReservt = 'n';
    }

    for (indiv = 0; indiv < (int)(LenHumanPop); indiv++){  //Generating human population
        Human[indiv].age              = calcAgeByDistribution();
        Human[indiv].stage            = 0;
        Human[indiv].stageOfInfection = 0;
        Human[indiv].diseaseReservt   = 'n';
        Human[indiv].daysInStage      = 1;
        Human[indiv].daysInTreat      = 0;
        Human[indiv].individualProbOfTreatSucces = 0.0;
        Human[indiv].treatTotalDays   = 0;
        Human[indiv].stageTotalDays   = 0;
        countHumanSusceptible++;
    }

    for (indiv = 0; indiv < (int)(LenAnimalsPop); indiv++){ //Generating Animals pop
        Animal[indiv].age            = sortRandomNumberInteger(0,366); 
        Animal[indiv].stage          = 0;
        Animal[indiv].diseaseReservt = 'n';
        Animal[indiv].daysInStage    = 1;
        Animal[indiv].stageTotalDays = 0;
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