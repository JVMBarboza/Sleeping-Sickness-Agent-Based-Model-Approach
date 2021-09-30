/*##################################################################################*/
/*########################  Pseudo Random Number Generator #########################*/
/*##################################################################################*/

/***** Pseudo Random Number Generator (0-1) *****/
double sortRandomNumber(unsigned *R){
    *R=*R*s;
    return (*R/max);
}

//sort int number between minNumber maxNumber-1 
//call: SortRandomNumberInteger(10,15); -> sort in the interval 0-14
int sortRandomNumberInteger(int minNum, int maxNum){
    return ( sortRandomNumber(&R)*(maxNum-minNum)+minNum );
}