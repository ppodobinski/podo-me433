# Use this code to generate a figure with a subplot of the signal vs time and a subplot of the FFT of each CSV

import matplotlib.pyplot as plt
import numpy as np
import csv

t = [] # column 0
data1 = [] # column 1
data2 = [] # column 2

with open('sigA.csv') as f:
    # open the csv file
    reader = csv.reader(f)
    for row in reader:
        # read the rows 1 one by one
        t.append(float(row[0])) # leftmost column
        data1.append(float(row[1])) # second column

s = data1

Fs = 10000 # sample rate
Ts = 1.0/Fs; # sampling interval
ts = np.arange(0,t[-1],Ts) # time vector
y = s # the data to make the fft from
n = len(y) # length of the signal
k = np.arange(n)
T = n/Fs
frq = k/T # two sides frequency range
frq = frq[range(int(n/2))] # one side frequency range
Y = np.fft.fft(y)/n # fft computing and normalization
Y = Y[range(int(n/2))]

## PART 1

fig1, (ax1, ax2) = plt.subplots(2, 1)
ax1.plot(t,y,'b')
ax1.set_xlabel('Time')
ax1.set_ylabel('Amplitude')
ax2.loglog(frq,abs(Y),'b') # plotting the fft
ax2.set_xlabel('Freq (Hz)')
ax2.set_ylabel('|Y(freq)|')
#plt.show()

## PART 2

fig2, (ax1) = plt.subplots(1,1)
# modified FFT
modified = []
last_x = 4
current_arr = []
print(len(Y))
for i in range(len(t)):
    current_arr.append(y[i])

    if last_x < len(current_arr):
        current_arr.pop(0)
    
    average = sum(current_arr) / len(current_arr)
    modified.append(average)

s = modified
y = s # the data to make the fft from
n = len(y) # length of the signal
k = np.arange(n)
T = n/Fs
frq = k/T # two sides frequency range
frq = frq[range(int(n/2))] # one side frequency range
Y_new = np.fft.fft(y)/n # fft computing and normalization
Y_new = Y_new[range(int(n/2))]

# original FFT
ax1.loglog(frq,abs(Y),'k') # plotting the fft
ax1.set_xlabel('Freq (Hz)')
ax1.set_ylabel('|Y(freq)|')
ax1.set_title(f"number of data points: {last_x}")

# modified FFT
ax1.loglog(frq,abs(Y_new),'r') # plotting the fft
ax1.set_xlabel('Freq (Hz)')
ax1.set_ylabel('|Y(freq)|')

## PART 3

fig3, (ax1) = plt.subplots(1,1)
# modified FFT
A = 0.35
B = np.round(1 - A,2)

average_arr = []
new_average = []
for i in range(len(t)):
    if i == 0:
        continue
    # elif i == 1:
    #     current_average = 1/2 * (y[i] + y[i-1])
    #     average_arr.append(current_average)
    else: 
        current_average = 1/2 * (y[i] + y[i-1])
        average_arr.append(current_average)

for i in range(len(average_arr)):
    if i == 0:
        continue
    else:
        average_arr[i] = A*average_arr[i-1] + B*y[i]


s = average_arr
y = s # the data to make the fft from
n = len(y) # length of the signal
k = np.arange(n)
T = n/Fs
frq_3 = k/T # two sides frequency range
frq_3 = frq_3[range(int(n/2))] # one side frequency range
Y_new = np.fft.fft(y)/n # fft computing and normalization
Y_new = Y_new[range(int(n/2))]

print(len(frq))
print(len(Y))
# original FFT
ax1.loglog(frq,abs(Y),'k') # plotting the fft
ax1.set_xlabel('Freq (Hz)')
ax1.set_ylabel('|Y(freq)|')
ax1.set_title(f"A={A}, B={B}")

# modified FFT
ax1.loglog(frq_3,abs(Y_new),'r') # plotting the fft
ax1.set_xlabel('Freq (Hz)')
ax1.set_ylabel('|Y(freq)|')

# fig3.savefig("hw14_sigD_graph3")

## PART 4

fig4, (ax1) = plt.subplots(1,1)
# modified FFT

placeholder = []
fir = []
sum = 0
# vary the h_arr based on whether it's for A, B, C, or D
h = [
    -0.035589032215048791,
    0.005180814357701674,
    0.041398047206842613,
    -0.042466906900357898,
    -0.020437799433749022,
    0.082509499786556875,
    -0.046933728146852392,
    -0.113186626533460871,
    0.307468289490628932,
    0.644114884775477514,
    0.307468289490628932,
    -0.113186626533460871,
    -0.046933728146852392,
    0.082509499786556875,
    -0.020437799433749022,
    -0.042466906900357898,
    0.041398047206842613,
    0.005180814357701674,
    -0.035589032215048791,
]

window_size = len(h)
h_len_minus_1 = len(h) - 1

for val in y:
    placeholder.append(val)
    if len(placeholder) > window_size:
        placeholder.pop(0)
    if len(placeholder) == window_size:
        current = 0
        sum = 0
        for i in range(len(placeholder)):
            current = placeholder[i] * h[i]
            sum += current
        fir.append(sum)

s = fir
y = s # the data to make the fft from
n = len(y) # length of the signal
k = np.arange(n)
T = n/Fs
frq_4 = k/T # two sides frequency range
frq_4 = frq_4[range(int(n/2))] # one side frequency range
Y_new = np.fft.fft(y)/n # fft computing and normalization
Y_new = Y_new[range(int(n/2))]

# original FFT
ax1.loglog(frq,abs(Y),'k') # plotting the fft
ax1.set_xlabel('Freq (Hz)')
ax1.set_ylabel('|Y(freq)|')
ax1.set_title(f"low pass filter, 19 coefficients, sampling rate = 15 Hz, cutoff freq = 4.65 Hz, transition bandwidth = 0.75 Hz, rectangular window type")

# modified FFT
ax1.loglog(frq_4,abs(Y_new),'r') # plotting the fft
ax1.set_xlabel('Freq (Hz)')
ax1.set_ylabel('|Y(freq)|')

fig4.savefig("hw14_sigA_graph4")

# plt.show()