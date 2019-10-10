from numpy import zeros, array, sqrt, linspace, exp, meshgrid
import matplotlib.pyplot as plt



# Plotting integrand as function of r1 and r2
'''
def integrand(r1,r2):
	f = exp(-4*(r1+r2))
	return f

r1 = linspace(0,0.5,1000)
r2 = linspace(0,0.5,1000)

X,Y = meshgrid(r1,r2)

I = integrand(X,Y) 

plt.contourf(X,Y,I)
plt.colorbar()
plt.show()
'''
