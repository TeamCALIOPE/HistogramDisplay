import pylab
import numpy as np
import matplotlib.pyplot as plt
import math

#list_of_files = [('/Users/cbartram/MagneticSimulations/pass_thru','label 1'),
list_of_files = [('/Users/cbartram/HistogramDisplay/HGHGZPos_Rescale.txt','label 2')]

datalist = [ ( pylab.loadtxt(filename), label ) for filename, label in list_of_files ]
colors = ["red","Crimson"]

for bar in range(1, 24):

        bar = bar-1

        for data, label in datalist:
#    if label=="label 1":
#        pylab.scatter( data[:,0], data[:,1], label=label, color=colors[0],s=100,edgecolor='none')
 #   else:
#        pylab.scatter( data[:,0], data[:,1], label=label, color=colors[1],s=100,edgecolor='none');
                pylab.scatter( -20, data[bar,1], label=label, color=colors[1],s=100,edgecolor='none');
                pylab.scatter( -10, data[bar,2], label=label, color=colors[1],s=100,edgecolor='none');
                pylab.scatter( 0, data[bar,3], label=label, color=colors[1],s=100,edgecolor='none');
                pylab.scatter( 10, data[bar,4], label=label, color=colors[1],s=100,edgecolor='none');
                pylab.scatter( 20, data[bar,5], label=label, color=colors[1],s=100,edgecolor='none');
                #	c=[3,3,3,3,3,3];
                #	pylab.errorbar(data[:,0], data[:,1], yerr=data[:,1/(math.sqrt(1))], linestyle="None");
                #pylab.legend()
                pylab.xlabel("Actual Z Position (cm)")
                pylab.ylabel("Reconstructed Z Position")
                realBar = bar+1
                mystring = 'bar_'+str(realBar)
                pylab.title(mystring)
                pylab.savefig(mystring)
                pylab.clf()
#pylab.show()
