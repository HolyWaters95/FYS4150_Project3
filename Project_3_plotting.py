from numpy import zeros, ones, array, sqrt, linspace, exp, meshgrid, pi
import matplotlib.pyplot as plt
from Py_Functions import readarrays

Exact = pi**2/256.

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

#Tabulating results from Laguerre

'''
Values = open("build-Project_3-Desktop_Qt_5_13_0_MinGW_64_bit-Debug/Results_Laguerre.txt")

lines = Values.readlines()

Values.close()

N_values = []
I_values = []

for i in range(len(lines)):
	line_i = lines[i].split()
	N_values.append(float(line_i[2]))
	I_values.append(float(line_i[5]))

Runtimes = readarrays("build-Project_3-Desktop_Qt_5_13_0_MinGW_64_bit-Debug/Gauss_Laguerre_Runtimes.txt")[0][1]

N_values = array(N_values)
I_values = array(I_values)
Error_Laguerre = abs(I_values-ones(len(I_values))*Exact)

Lag_error = open("Laguerre_Errors.txt","w+")
Lag_error.write("Results of Integral using Gaussian Laguerre \n\n")
Lag_error.write("          |  Computed Value  |   Error   |      Runtime     |\n")
for i in range(len(N_values)):
	Lag_error.write(" N = %3d  |     %8.5f     |  %7.5f  |   %10.5f     |\n" % (N_values[i], I_values[i],Error_Laguerre[i],Runtimes[i]))

Lag_error.close()
'''
#Tabulating results from Legendre


Values = open("build-Project_3-Desktop_Qt_5_13_0_MinGW_64_bit-Debug/Results_Legendre.txt")

lines = Values.readlines()

Values.close()

L_values = []
N_values = []
I_values = []

L_values.append(float(lines[0].split()[4])
N_values.append(float(lines[0].split()[7])
I_values.append(float(lines[0].split()[10])

for i in range(1,len(lines)):
	line_i = lines[i].split()	
	L_values.append(float(line_i[4]))
	N_values.append(float(line_i[7]))
	I_values.append(float(line_i[10]))

Runtimes = readarrays("build-Project_3-Desktop_Qt_5_13_0_MinGW_64_bit-Debug/Gauss_Legendre_Runtimes.txt")[0][1]

N_values = array(N_values)
I_values = array(I_values)
Error_Legendre = abs(I_values-ones(len(I_values))*Exact)

Leg_error = open("Legendre_Errors.txt","w+")
Leg_error.write("Results of Integral using Gaussian Legendre \n\n")
Leg_error.write("          |  Computed Value  |   Error   |      Runtime     |\n")
for l in L_values:
	Leg_error.write(" L = %d  |" % l)
	for i in range(len(N_values)):
		Leg_error.write("        N = %3d  |     %8.5f     |  %7.5f  |\n" % (N_values[i], I_values[i],Error_Legendre[i]))

Leg_error.close()



#2, 4, 7, 10
