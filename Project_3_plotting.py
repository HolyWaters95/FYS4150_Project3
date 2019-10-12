from numpy import zeros, ones, array, sqrt, linspace, exp, meshgrid, pi, log10, polyfit, polyval
import matplotlib.pyplot as plt
from Py_Functions import readarrays

Exact = (5*pi**2)/256.


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
'''
Values = open("build-Project_3-Desktop_Qt_5_13_0_MinGW_64_bit-Debug/Results_Legendre.txt")

lines = Values.readlines()

Values.close()

L_values = []
N_values = []
I_values = []
Error_Legendre = []

N_values.append([])
I_values.append([])
Error_Legendre.append([])
L_counter = 1
N_counter = 0

L_values.append(float(lines[0].split()[4]))
for i in range(1,len(lines)):
	if L_counter == 1:
		N_counter += 1
	if lines[i].split()[4] != lines[i-1].split()[4]:
		N_values.append([])
		I_values.append([])
		Error_Legendre.append([])

		L_values.append(float(lines[i].split()[4]))
		L_counter += 1

i = 0

for l in range(L_counter):
	for n in range(N_counter):
		N_values[l].append(int(lines[i].split()[7]))
		I_values[l].append(float(lines[i].split()[10]))
		Error_Legendre[l].append(abs(float(lines[i].split()[10])-Exact))
		i += 1

Leg_error = open("Legendre_Errors.txt","w+")
Leg_error.write("Results of Integral using Gaussian Legendre \n\n")
Leg_error.write("                      |  Computed Value  |   Error   |\n")
for l in range(L_counter):
	Leg_error.write(" L = %d  |" % L_values[l])
	for i in range(N_counter):
		if i == 0:
			Leg_error.write("   N = %3d   |     %8.5f     |  %7.5f  |\n" % (N_values[l][i], I_values[l][i],Error_Legendre[l][i]))		
		else:		
			Leg_error.write("        |   N = %3d   |     %8.5f     |  %7.5f  |\n" % (N_values[l][i], I_values[l][i],Error_Legendre[l][i]))

Leg_error.close()
'''
#Plot runtimes for Legendre

N, Runtimes = readarrays("build-Project_3-Desktop_Qt_5_13_0_MinGW_64_bit-Debug/Gauss_Legendre_Runtimes.txt")[0]

N = array(N); Runtimes = array(Runtimes)
lN = log10(N)
lR = log10(Runtimes)

lininterpol = polyfit(lN,lR,1)

print lininterpol[0],lininterpol[1]
N_array = linspace(0,5,2000)
linpolynomial = lininterpol[0]*N_array + lininterpol[1]

plt.figure()
plt.plot(lN,lR,"ro",N_array,linpolynomial,"b")
plt.title("Runtimes for Gaussian Legendre as function \n of number of data points, N")
plt.xlabel("$log_{10}(N)$")
plt.ylabel("$log_{10}(t_R)$")
plt.legend(["Calculated runtimes","%.2f$x$ + %.2f" % (lininterpol[0], lininterpol[1])])

#Plotting runtimes for legendre and laguerre together

plt.figure()
plt.plot(lN,lR,"ro",N_array,linpolynomial,"b")


N, Runtimes = readarrays("build-Project_3-Desktop_Qt_5_13_0_MinGW_64_bit-Debug/Gauss_Laguerre_Runtimes.txt")[0]

N = array(N); Runtimes = array(Runtimes)
lN = log10(N)
lR = log10(Runtimes)

lininterpol = polyfit(lN,lR,1)

N_array = linspace(0,5,2000)
linpolynomial = lininterpol[0]*N_array + lininterpol[1]

plt.plot(lN,lR,"ro",N_array,linpolynomial,"b")
plt.title("Runtimes for Gaussian Legendre as function \n of number of data points, N")
plt.xlabel("$log_{10}(N)$")
plt.ylabel("$log_{10}(t_R)$")
plt.legend(["Calculated runtimes Legendre","Legendre polyfit: %.2f$x$ + %.2f" % (lininterpol[0], lininterpol[1]),"Calculated runtimes Laguerre","--"])



plt.show()




