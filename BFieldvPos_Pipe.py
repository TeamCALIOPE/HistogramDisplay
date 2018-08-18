import pylab
import numpy as np
import matplotlib.pyplot as plt
import math

#list_of_files = [('/Users/cbartram/MagneticSimulations/pass_thru','label 1'),
list_of_files = [('/Users/cbartram/MagneticSimulations/pass_thru_pipe','label 2')]

datalist = [ ( pylab.loadtxt(filename), label ) for filename, label in list_of_files ]
colors = ["red","Crimson"]

for data, label in datalist:
#    if label=="label 1":
#        pylab.scatter( data[:,0], data[:,1], label=label, color=colors[0],s=100,edgecolor='none')
 #   else:
        pylab.scatter( data[:,0], data[:,1], label=label, color=colors[1],s=100,edgecolor='none');
	c=[3,3,3,3,3,3];
	pylab.errorbar(data[:,0], data[:,1], yerr=data[:,1/(math.sqrt(1))], linestyle="None");
#pylab.legend()
pylab.title("Magnetic Field v Position (Inside Pipe Within Magnet): 8 mm Wall Thickness")
pylab.xlabel("Inches (from end of ruler placed inside magnet)")
pylab.ylabel("Gauss")
pylab.show()
