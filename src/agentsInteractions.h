/*##################################################################################*/
/*########################## Inter Species(BITE) Funtions ######################*/
/*##################################################################################*/

int sortHumanOrAnimalToBeBited(){
    
    double rn = sortRandomNumber(&R);
    
    if(rn < bloodMealOnHumans)
        return 1; //HUMAN
    else{
        if( (rn >= bloodMealOnHumans) && (rn < (bloodMealOnHumans+bloodMealOnDomesticAnimals)) )
        return 2; //DOMESTIC ANIMAL 
    }

}

//Simulate fly biting indiv infected(sort individual to be bited) 
void verifiesSusceptbFlyGetInfection(int coorde){
    
    double rn  = sortRandomNumber(&R);
    int    key = sortHumanOrAnimalToBeBited();
    
    int individualSelected;
        
    if(key==1){//Human bited      
        individualSelected = sortRandomNumberInteger(0,5000);
        if((Human[individualSelected].diseaseReservt=='y' && rn<ProbFlyGetInfect()) && (TseTse[coorde].firstMeal=='y' && TseTse[coorde].age <= 5)){//infection takes place
            fromSuscpToLatentFlies(coorde); //change the state of selected fly
        }
    }
    
    if(key==2){//Animal bited
        individualSelected = sortRandomNumberInteger(0,1000);
        if((Animal[individualSelected].diseaseReservt=='y' && rn<ProbFlyGetInfect()) && (TseTse[coorde].firstMeal=='y' && TseTse[coorde].age <= 5)){//infection takes place
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
        TseTse[coord].daysWithoutEat = 0;
        TseTse[coord].firstMeal      = 'n'; 
    }
    else{ //didnt bite
        TseTse[coord].daysWithoutEat++;
    }

}
