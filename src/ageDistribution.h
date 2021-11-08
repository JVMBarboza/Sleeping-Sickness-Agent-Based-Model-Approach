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