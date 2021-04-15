import glob
import pandas as pd 

#LOADING DATA FILES 
filenames = glob.glob("results/simulation01/*.csv")


# SETTING FRAMES
susceptible_frame            = pd.DataFrame() # In matplot -> index = 1
latent_frame                 = pd.DataFrame() # In matplot -> index = 2
infected_stg_one_frame       = pd.DataFrame() # ...
infected_stg_two_frame       = pd.DataFrame()
infected_total_frame         = pd.DataFrame()
recovered_frame              = pd.DataFrame()
in_treatment_frame           = pd.DataFrame()
natural_deaths_frame         = pd.DataFrame()
stage_one_deaths             = pd.DataFrame()
stage_two_deaths             = pd.DataFrame()
total_infected_deaths_frame  = pd.DataFrame()
daily_new_infectives_frame   = pd.DataFrame()
daily_new_deaths_frame       = pd.DataFrame()    


#O MOTIVO DE FAZER ISSO AO INVÉS DE LER DOS ARQUIVOS É QUE EU NÃO IREI PRECISAR FAZER MEDIA DE VARIOS ARQUIVOS SENDO O RESULTADO IGUAL VISTO QUE TODOS OS TEMPOS SAO IGUAIS
time = []
#in the case of simulation of 10 years
for i in range(0,3649):
    time.append(i)

timeFrame = pd.DataFrame({'Time':time})


#MANIPULATING DATA
for file in filenames:
    df=pd.read_csv(file,index_col=0)
    susceptible_frame = pd.concat([susceptible_frame, df['Susceptible']], axis=1)

for file in filenames:
    df=pd.read_csv(file,index_col=0)
    latent_frame = pd.concat([latent_frame, df['Latent']], axis=1)

for file in filenames:
    df=pd.read_csv(file,index_col=0)
    infected_stg_one_frame = pd.concat([infected_stg_one_frame, df['Infection Stage 1']], axis=1)

for file in filenames:
    df=pd.read_csv(file,index_col=0)
    infected_stg_two_frame = pd.concat([infected_stg_two_frame, df['Infection Stage 2']], axis=1)

for file in filenames:
    df=pd.read_csv(file,index_col=0)
    infected_total_frame = pd.concat([infected_total_frame, df['Total Infected']], axis=1)

for file in filenames:
    df=pd.read_csv(file,index_col=0)
    recovered_frame = pd.concat([recovered_frame, df['Recovered']], axis=1)

for file in filenames:
    df=pd.read_csv(file,index_col=0)
    in_treatment_frame = pd.concat([in_treatment_frame, df['In Treatment']], axis=1)
      
for file in filenames:
    df=pd.read_csv(file,index_col=0)
    natural_deaths_frame = pd.concat([natural_deaths_frame, df['Natural Death']], axis=1)
  
for file in filenames:
    df=pd.read_csv(file,index_col=0)
    stage_one_deaths = pd.concat([stage_one_deaths, df['Stage 1 Death']], axis=1)

for file in filenames:
    df=pd.read_csv(file,index_col=0)
    stage_two_deaths = pd.concat([stage_two_deaths, df['Stage 2 Death']], axis=1)
 
for file in filenames:
    df=pd.read_csv(file,index_col=0)
    total_infected_deaths_frame = pd.concat([total_infected_deaths_frame, df['Total Infection Death']], axis=1)
 
for file in filenames:
    df=pd.read_csv(file,index_col=0)
    daily_new_infectives_frame = pd.concat([daily_new_infectives_frame, df['Daily New Infective']], axis=1)

for file in filenames:
    df=pd.read_csv(file,index_col=0)
    daily_new_deaths_frame = pd.concat([daily_new_deaths_frame, df['Daily Deaths']], axis=1)   

#CALCULATING MEAN VALUES
susceptible_frame['Susceptible Mean']                     = susceptible_frame.mean(axis=1)
latent_frame['Latent Mean']                               = latent_frame.mean(axis=1)
infected_stg_one_frame['Infection Stage 1 Mean']          = infected_stg_one_frame.mean(axis=1)
infected_stg_two_frame['Infection Stage 2 Mean']          = infected_stg_two_frame.mean(axis=1)
infected_total_frame['Total Infected Mean']               = infected_total_frame.mean(axis=1)
recovered_frame['Recovered Mean']                         = recovered_frame.mean(axis=1)
in_treatment_frame['In Treatment Mean']                   = in_treatment_frame.mean(axis=1)
natural_deaths_frame['Natural Death Mean']                = natural_deaths_frame.mean(axis=1)
stage_one_deaths['Stage 1 Death Mean']                    = stage_one_deaths.mean(axis=1)
stage_two_deaths['Stage 2 Death Mean']                    = stage_two_deaths.mean(axis=1)
total_infected_deaths_frame['Total Infection Death Mean'] = total_infected_deaths_frame.mean(axis=1)
daily_new_infectives_frame['Daily New Infective Mean']    = daily_new_infectives_frame.mean(axis=1)
daily_new_deaths_frame['Daily Deaths Mean']               = daily_new_deaths_frame.mean(axis=1)

#CALCULATING STD VALUES
susceptible_frame['Susceptible std']                     = susceptible_frame.std(axis=1)
latent_frame['Latent std']                               = latent_frame.std(axis=1)
infected_stg_one_frame['Infection Stage 1 std']          = infected_stg_one_frame.std(axis=1)
infected_stg_two_frame['Infection Stage 2 std']          = infected_stg_two_frame.std(axis=1)
infected_total_frame['Total Infected std']               = infected_total_frame.std(axis=1)
recovered_frame['Recovered std']                         = recovered_frame.std(axis=1)
in_treatment_frame['In Treatment std']                   = in_treatment_frame.std(axis=1)
natural_deaths_frame['Natural Death std']                = natural_deaths_frame.std(axis=1)
stage_one_deaths['Stage 1 Death std']                    = stage_one_deaths.std(axis=1)
stage_two_deaths['Stage 2 Death std']                    = stage_two_deaths.std(axis=1)
total_infected_deaths_frame['Total Infection Death std'] = total_infected_deaths_frame.std(axis=1)
daily_new_infectives_frame['Daily New Infective std']    = daily_new_infectives_frame.std(axis=1)
daily_new_deaths_frame['Daily Deaths std']               = daily_new_deaths_frame.std(axis=1)

#OUTPUT

outputFrame = pd.concat([timeFrame, susceptible_frame['Susceptible Mean'], latent_frame['Latent Mean'], infected_stg_one_frame['Infection Stage 1 Mean'], infected_stg_two_frame['Infection Stage 2 Mean'], infected_total_frame['Total Infected Mean'], recovered_frame['Recovered Mean'], in_treatment_frame['In Treatment Mean'], natural_deaths_frame['Natural Death Mean'], stage_one_deaths['Stage 1 Death Mean'], stage_two_deaths['Stage 2 Death Mean'], total_infected_deaths_frame['Total Infection Death Mean'], daily_new_infectives_frame['Daily New Infective Mean'], daily_new_deaths_frame['Daily Deaths Mean']], axis=1)
outputFrame.to_csv('result.csv', index=False)

outputFrame = pd.concat([timeFrame, susceptible_frame['Susceptible std'], latent_frame['Latent std'], infected_stg_one_frame['Infection Stage 1 std'], infected_stg_two_frame['Infection Stage 2 std'], infected_total_frame['Total Infected std'], recovered_frame['Recovered std'], in_treatment_frame['In Treatment std'], natural_deaths_frame['Natural Death std'], stage_one_deaths['Stage 1 Death std'], stage_two_deaths['Stage 2 Death std'], total_infected_deaths_frame['Total Infection Death std'], daily_new_infectives_frame['Daily New Infective std'], daily_new_deaths_frame['Daily Deaths std']], axis=1)
outputFrame.to_csv('result_standard_deviation.csv', index=False)
