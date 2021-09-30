/*############################ CONSTANTS #############################*/



//POPULATIONS && TREATMENT
#define LenTseTsePop  50000 //(SMITH, 2016)
#define LenHumanPop   5000  //(SMITH, 2016)
#define LenAnimalsPop 1000  //(SMITH, 2016)

#define initialInfectedHumanPorcetg     0.006  //H:0.6% (SMITH, 2016) 
#define initialInfectedFliesPorcetg     0.024  //F:2.4% (SMITH, 2016) 
#define initialInfectedAnimalsPorcetg   0.18   //A:18%  (SMITH, 2016)

//FLIES CONSTANTS
#define fliesDeathRate 0.021976910177 // (days⁻¹) (ARTZROUNI, M.; GOUTEUX, J.-P. 1996)

#define fliesMaxAge 60 //VERIFICAR

#define ProbBiteMax 0.25  //(ARTZROUNI, M.; GOUTEUX, J.-P. 1996)   
#define ProbBiteMin 0.05                 

#define fliesMaxDaysInLatent 30 //(MULLER, G.; GRÉBAUT, P.; GOUTEUX, J.-P. 2004)
#define fliesMinDaysInLatent 15

#define ProbInfectHumanAndAnimals 0.62 //(ROGERS, 1988) 

//HUMANS/ANIMALS             
#define naturalDeathMaxEstim 0.000068490805 // 1/14600 = 1/(365*40) days⁻¹ (SMITH, 2016)
#define naturalDeathMinEstim 0.000045661058 // 1/21900 = 1/(365*60) days⁻¹

#define animalsMaxAge 365 //DUE TO ANIMALS SLAUTHER

#define bloodMealOnHumans          0.333 //(SIMO, 2012)    //0.667 //(GREBAUT, 2009) 
#define bloodMealOnDomesticAnimals 0.583 //(SIMO, 2012)

#define probInfectFliesMax 0.05 //(SIMARRO,2014) //0.14 //(ARTZROUNI, M.; GOUTEUX, J.-P. 2016)
#define probInfectFliesMin 0.02                  //0.05 

#define cattleDeathRate 0.002735976376 // 1/365 days⁻¹

#define animalsMaxDaysInLatent 14 //(ARTZROUNI, M.; GOUTEUX, J.-P. 1996)
#define animalsMinDaysInLatent 10

#define humansMaxDaysInStgOne 833 //(CHECCHI, F. et al. 2008)
#define humansMinDaysInStgOne 357

#define humansMaxDaysInStgTwo 769 //(CHECCHI, F. et al. 2008)
#define humansMinDaysInStgTwo 345
