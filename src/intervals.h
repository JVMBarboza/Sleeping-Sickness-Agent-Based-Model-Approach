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

//sort duration in the interval:15-30 days  
int calculateFliesLatentDurantionDays(){
    return sortRandomNumberInteger(fliesMinDaysInLatent,fliesMaxDaysInLatent+1);
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