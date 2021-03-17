import numpy as np
import matplotlib.pyplot as plt 

plt.rcParams['figure.figsize'] = 13, 7

plt.rc('xtick', labelsize=13.5)
plt.rc('ytick', labelsize=13.5)

fig_name="simulation01.png"

#LOAD DATA FROM CSV FILE 
data = np.genfromtxt('results/simulation01/result.csv', delimiter=',')

#FORMAT X in DAYS To YEARS
x = data[:,0]
time = [(lambda day: day/365.0)(day) for day in x]


#Store necessary data to plot
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

#Plot Configuration

main_fig  = plt.figure()
mainPlot            = main_fig.add_axes([0.1, 0.1, 0.8, 0.8])

#count_fig = plt.figure()
#countPlot           = count_fig.add_axes([0.1, 0.1, 0.8, 0.8])
 

########################### CURVES SETTINGS ##################################
 
#mainPlot.plot(time, susceptible,    color='#19f56a', lw=1.5, label="Susceptible")
#mainPlot.plot(time, latent,         color='#fafe06', lw=1.5, label="Latent")
mainPlot.plot(time, stg1,           color='#feaf06', lw=1.5, label="Stage 1 Infectives")
mainPlot.plot(time, stg2,           color='#59109e', lw=1.5, label="Stage 2 Infectives")
mainPlot.plot(time, total,          color='#bf1303', lw=1.5, label="Total Infectives")
#mainPlot.plot(time, recov,          color='#07b404', lw=1.5, label="Recovered")
#mainPlot.plot(time, in_treatm,      color='#c516b7', lw=1.5, label="Treatment in Progress")

#GENERAL
#mainPlot.set_title('Figure 1')
mainPlot.legend(fontsize=13)
mainPlot.grid(True,axis='both',alpha=0.35)
mainPlot.tick_params(axis='both',direction='in',bottom=1, top=0, left=1, right=0)

#X-AXIS
mainPlot.set_xlim([0,10])
mainPlot.set_xticks(np.arange(0, 10.2, step=1))
mainPlot.set_xlabel('Time(Years)', fontsize=15)

#Y-AXIS
mainPlot.set_ylim([0,1.0])
mainPlot.set_yticks(np.arange(0,1.0001,step=0.1))
mainPlot.set_ylabel('Density in Population', fontsize=15)

#COUNT PLOT
#countPlot.plot(time, natural_deaths, color='#86be04', lw=1.5, label="Natural Deaths")
#countPlot.plot(time, stg1_deaths,    color='#e78c04', lw=1.5, label="Stage One Deaths")
#countPlot.plot(time, stg2_deaths,    color='#1a168d', lw=1.5, label="Stage Two Deaths")
#countPlot.plot(time, total_deaths,   color='#bc0808ff', lw=1.5, label="Total Infectives Deaths")
#countPlot.plot(time, new_infectives, color='#e9520c', lw=1.5, label="Daily Infectives")
#countPlot.plot(time, daily_deaths,   color='#cf0707', lw=1.5, label="Daily Deaths by Infection")

#countPlot.set_title('Figure 2')
#countPlot.legend(fontsize=13)
#countPlot.grid(True,axis='both',alpha=0.35)
#countPlot.tick_params(axis='both',direction='in',bottom=1, top=0, left=1, right=0)

#countPlot.set_xlim([0,10])
#countPlot.set_xticks(np.arange(0, 10.2, step=1))
#countPlot.set_xlabel('Time(Years)', fontsize=14.6)

#countPlot.set_ylim([0,1000])
#countPlot.set_yticks(np.arange(0,1000,step=100))
#countPlot.set_ylabel('Count', fontsize=14.6)

#OUTPUT
plt.tight_layout() 
plt.savefig(fig_name, dpi=600, facecolor='w', edgecolor='w',
    orientation='portrait', papertype=None, format=None,
    transparent=False, bbox_inches=None, pad_inches=0.1,
    frameon=None)

#plt.show()