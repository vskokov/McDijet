#!/usr/bin/python
import math   # This will import math module


E_e = 25.0
E_p = 100.0
root_s = math.sqrt( 1.0 + 2 * E_e * ( E_p + math.sqrt(E_p**2 - 1.0)))
print ("root s = ",root_s)
s = root_s**2

with open('data.txt') as f:
    for line in f:
        Pt,qt,z,phi,phiT,xS,W,Q,Pol,k1x,k1y,k1z,k1E,\
            k2x,k2y,k2z,k2E = [float(i) for i in line.split()]
        y1 = math.atanh(k1z/k1E)
        y2 = math.atanh(k2z/k2E)
        kT1 = math.sqrt(k1x*k1x+k1y*k1y)
        kT2 = math.sqrt(k2x*k2x+k2y*k2y)
        xgamma = (kT1*math.exp(y1) + kT2*math.exp(y2)) / (2*E_e)
        W2sub = W*W + Q*Q - 1.0
        s_m2 = s-1.0
        yprime = W2sub/2.0/s_m2 * (1.+math.sqrt(1.+4.*Q*Q/W2sub**2))
        print (yprime/xgamma, yprime, xgamma, kT1*math.exp(y1)/(kT1*math.exp(y1) + kT2*math.exp(y2))/z)
