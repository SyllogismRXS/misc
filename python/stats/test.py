# http://www.randalolson.com/2012/08/06/statistical-analysis-made-easy-in-python/

import numpy as np
from pandas import *
from scipy import stats  

experimentDF = read_csv('parasite_data.csv', na_values=[" "])

#print experimentDF
#print experimentDF["Virulence"]
#print experimentDF["Virulence"][12]
#print experimentDF[experimentDF["ShannonDiversity"] > 2.0]
#print experimentDF[np.isnan(experimentDF["Virulence"])]
#print("Virulence Mean: %f" % experimentDF["Virulence"].mean())

treatment1 = experimentDF[experimentDF["Virulence"] == 0.5]["ShannonDiversity"]  
treatment2 = experimentDF[experimentDF["Virulence"] == 0.8]["ShannonDiversity"]  

z_stat, p_val = stats.ranksums(treatment1, treatment2)  
print "MWW RankSum P for treatments 1 and 2 =", p_val  
