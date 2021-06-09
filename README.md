# Sleeping Sickness Agent-Based Model
Agent-based model for the simulation of Sleeping Sickness disease behavior in a fictional population.

## Getting Started

These instructions will help you to get a copy of the project in your local machine for development, testing, and research purposes. 

## Prerequisites

During the implementation of the model,  tools used are listed below. Therefore, we highly recomend the script  as prerequisites to run simulations. Otherwise, you may run it manually and item I is the only prerequisite necessary.

```
    I)   GCC (version 7.5.0)
    II)  Python (3.7.6)
    III) Matplotlib (3.1.3)
    IV)  Pandas (1.0.1)
    V)   Numpy (1.18.1)
```

## Installing

No instalation, just modify and execute run.sh file.

## Running

    i) The authors recommend a change in the "ran" variable value in run.sh for each simulation since a different value of "ran" implies in different pseudo random numbers.
    
    ii) Modify the directory of simulation results in python files(**).

    iii) modify variable values in sed command.

## Built With

* [GCC](https://gcc.gnu.org/) - Compiler 
* [Python](https://www.python.org/) - Used to graphics and output files manipulation
* [Matplotlib](https://matplotlib.org/) - Graphics
* [Pandas](https://pandas.org/) - Data manipulation
* [Numpy](https://numpy.org/) - Data manipulation

## License

    ---*---

## Acknowledgments

*) As mentioned, if the user don't feel confortable using python tools, it is possible to run everything manually using the main.c in the "maincode" directory or inserting "#" in the python line(s) in the run.sh script.

**)pay attention to the name of output files in the script and in the python codes "results/directory", have to be the same to plot work fine. 


Authors: Aquino L. Espíndola, João Victor M. Barboza & Matheus de Moraes Gonçalves Correia

Date: June, 2020 
