#!/usr/bin/python
#
# Copyright (c) 2018 [n/a] info@embeddora.com All rights reserved
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#        * Redistributions of source code must retain the above copyright
#          notice, this list of conditions and the following disclaimer.
#        * Redistributions in binary form must reproduce the above copyright
#          notice, this list of conditions and the following disclaimer in the
#          documentation and/or other materials provided with the distribution.
#        * Neither the name of The Linux Foundation nor
#          the names of its contributors may be used to endorse or promote
#          products derived from this software without specific prior written
#          permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NON-INFRINGEMENT ARE DISCLAIMED.    IN NO EVENT SHALL THE COPYRIGHT OWNER OR
# CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
# EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
# PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
# OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
# WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
# OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
# ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
# Abstract: 

import usbtmc
import numpy
import matplotlib.pyplot as plot
import sys
 
scope =  usbtmc.Instrument(0x1ab1, 0x0588) # Rigol DS1102E

scope.write(":STOP")
 
timescale = float(scope.ask_raw(":TIM:SCAL?"))

timeoffset = float(scope.ask_raw(":TIM:OFFS?"))

voltscale1 = float(scope.ask_raw(':CHAN1:SCAL?'))
voltscale2 = float(scope.ask_raw(':CHAN2:SCAL?'))

voltoffset1 = float(scope.ask_raw(":CHAN1:OFFS?"))
voltoffset2 = float(scope.ask_raw(":CHAN2:OFFS?"))

scope.write(":WAV:POIN:MODE RAW")
rawdata1 = scope.ask_raw(":WAV:DATA? CHAN1")[10:]
rawdata2 = scope.ask_raw(":WAV:DATA? CHAN2")[10:]

data_size = len(rawdata1)
sample_rate = float(scope.ask_raw(':ACQ:SAMP?'))

print 'Data size:', data_size, "Sample rate:", sample_rate

scope.write(":KEY:FORCE")
scope.close()

data1 = numpy.frombuffer(rawdata1, 'B')
data2 = numpy.frombuffer(rawdata2, 'B')

data1 = data1 * -1 + 255
data2 = data2 * -1 + 255
 
data1 = (data1 - 130.0 - voltoffset1/voltscale1*25) / 25 * voltscale1
data2 = (data2 - 130.0 - voltoffset2/voltscale2*25) / 25 * voltscale2

time = numpy.linspace(timeoffset - 6 * timescale, timeoffset + 6 * timescale, num=len(data1))
#time = numpy.linspace(0, 6 * timescale, num=len(data1))
 
if (time[-1] < 1e-3):
    time = time * 1e6
    tUnit = "uS"
elif (time[-1] < 1):
    time = time * 1e3
    tUnit = "mS"
else:
    tUnit = "S"
 
plot.plot(time, data1)
plot.plot(time, data2)
plot.title("Oscilloscope Channel 1")
plot.ylabel("Voltage (V)")
plot.xlabel("Time (" + tUnit + ")")
plot.xlim(time[0], time[-1])
##plot.show()

#for x in range(1,data_size):
#	print "(", x, " of ", data_size-1, " )  Probe1: (", data1[x], ")  Probe2 : (", data2[x], ")"

print "<num elements: ", data_size-1, ", time in ", tUnit, ">"
print "Time X(CH1) X(CH2)"
print "Second Volt Volt"

for x in range(1,data_size):
	print ("%2.6f,%2.5f,%2.5f" % (  time[x],data1[x],data2[x] ) ) ;

print "<end>"

