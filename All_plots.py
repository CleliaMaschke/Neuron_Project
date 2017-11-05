import os
import numpy as np
import matplotlib.pyplot as pl

files = ["Param1.csv", "Param2.csv", "Param3.csv", "Param4.csv"]
for f in files:
	data = np.genfromtxt(f)
	select= np.array([d for d in data if d[1] < 30])
	data1= select.transpose()
	
	pl.subplot(211)
	pl.title(f)
	pl.scatter(0.1*data1[0],data1[1],alpha=0.8, edgecolors='none');
	pl.xlabel('time [ms]', color = 'black')
	pl.ylabel('neuron ID', color='black')

	pl.subplots_adjust(hspace=0.3)
	pl.subplot(212)
	n, bins, patches = pl.hist(0.1*data1[0], 50, normed=0, alpha=0.75)
	pl.xlabel('time (ms)', color = 'black')
	pl.ylabel('frequency', color = 'black')
	output_filename = os.path.splitext(f)[0] + '.png'
	pl.savefig(output_filename)
	pl.show(); 
