import numpy as np
import matplotlib.pyplot as plt 

plt.rcParams['figure.figsize'] = 13, 7

plt.rc('xtick', labelsize=13.5)
plt.rc('ytick', labelsize=13.5)

fig_name="simulation01.png"

##################### LOADING DATA FROM CSV FILE ########################################## 
data    = np.genfromtxt('results/simulation01/result.csv', delimiter=',')
dataStd = np.genfromtxt('results/simulation01/result_standar_deviation.csv', delimiter=',')

#FORMAT X in DAYS to YEARS
x = data[:,0]
time = [(lambda day: day/365.0)(day) for day in x]


#STORE NECESSARY DATA TO PLOT
susceptible    = data[:,1]
latent         = data[:,2]
stg1           = data[:,3]
stg2           = data[:,4]
total          = data[:,5]
recov          = data[:,6]
in_treatm      = data[:,7]
natural_deaths = data[:,8]
stg1_deaths    = data[:,9]
stg2_deaths    = data[:,10]
total_deaths   = data[:,11]
new_infectives = data[:,12]
daily_deaths   = data[:,13]

#STORE STANDARD DEVIATIONS
susceptible_Std    = dataStd[:,1]
latent_Std         = dataStd[:,2]
stg1_Std           = dataStd[:,3]
stg2_Std           = dataStd[:,4]
total_Std          = dataStd[:,5]
recov_Std          = dataStd[:,6]
in_treatm_Std      = dataStd[:,7]
natural_deaths_Std = dataStd[:,8]
stg1_deaths_Std    = dataStd[:,9]
stg2_deaths_Std    = dataStd[:,10]
total_deaths_Std   = dataStd[:,11]
new_infectives_Std = dataStd[:,12]
daily_deaths_Std   = dataStd[:,13]


########################### PLOT CONFIGURATION ###############################

f, (mainPlot, stdPlot) = plt.subplots(2,1,sharex=True, gridspec_kw={'height_ratios': [4.8, 1]})


########################### MAIN CURVE SETTINGS ##################################
 
mainPlot.plot(time, susceptible, color='#19f56a', lw=1.5, label="Susceptible")
#mainPlot.plot(time, latent, color='#fafe06', lw=1.5, label="Latent")
#mainPlot.plot(time, stg1, color='#feaf06', lw=1.5, label="Stage 1 Infectives")
#mainPlot.plot(time, stg2, color='#59109e', lw=1.5, label="Stage 2 Infectives")
mainPlot.plot(time, total, color='#bf1303', lw=1.5, label="Total Infectives")
#mainPlot.plot(time, recov, color='#07b404', lw=1.5, label="Recovered")
#mainPlot.plot(time, in_treatm, color='#c516b7', lw=1.5, label="Treatment in Progress")

#mainPlot.set_title('Figure 1')
mainPlot.legend(fontsize=13)
mainPlot.grid(True,axis='both',alpha=0.35)
mainPlot.tick_params(axis='both',direction='in',bottom=1, top=0, left=1, right=0)

#X-AXIS
#mainPlot.set_xlim([0,10])
#mainPlot.set_xticks(np.arange(0, 10.2, step=1))
#mainPlot.set_xlabel('Time(Years)', fontsize=15)

#Y-AXIS
mainPlot.set_ylim([0,1.0])
mainPlot.set_yticks(np.arange(0,1.0001,step=0.1))
mainPlot.set_ylabel('Density in Population', fontsize=15)


####################### STANDARD DEVIATION CURVE SETTINGS ###############################

stdPlot.plot(time, susceptible_Std , color='#19f56a', lw=1.30, ls='dashed', label="Susceptible Standard Deviation")
#stdPlot.plot(time, latent_Std      , color='#fafe06', lw=1.30, label="Latent")
#stdPlot.plot(time, stg1_Std        , color='#feaf06', lw=1.30, label="Stage 1 Infectives")
#stdPlot.plot(time, stg2_Std        , color='#59109e', lw=1.30, label="Stage 2 Infectives")
stdPlot.plot(time, total_Std       , color='#bf1303', lw=1.30, ls='dashed', label="Total Infectives")
#stdPlot.plot(time, recov_Std       , color='#07b404', lw=1.30, label="Recovered")
#stdPlot.plot(time, in_treatm_Std   , color='#c516b7', lw=1.30, label="Treatment in Progress")

#stdPlot.legend(fontsize=13)
stdPlot.grid(True,axis='both',alpha=0.35)
stdPlot.tick_params(axis='both',direction='in',bottom=1, top=0, left=1, right=0)

#X-AXIS
stdPlot.set_xlim([0,10])
stdPlot.set_xticks(np.arange(0, 10.2, step=1))
stdPlot.set_xlabel('Time(Years)', fontsize=15)

#Y-AXIS
stdPlot.set_ylim([0,0.021])
stdPlot.set_yticks(np.arange(0,0.021,step=0.01))
stdPlot.set_ylabel('σ', fontsize=15)



############################ OUTPUT SETTINGS ########################################

plt.tight_layout() 
plt.savefig(fig_name, dpi=600, facecolor='w', edgecolor='w',
    orientation='portrait', papertype=None, format=None,
    transparent=False, bbox_inches=None, pad_inches=0.1,
    frameon=None)

#plt.show()