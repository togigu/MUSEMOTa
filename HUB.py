## Reader of the data from portX
import serial # import Serial Library
import matplotlib.pyplot as plt #import matplotlib library
from matplotlib.animation import FuncAnimation
from mpl_toolkits.mplot3d import Axes3D
import numpy as np

## PUERTOS DE ENTRADA  Y DEMAS

bad= 115200 ##Symbol rate
com='COM3'  ##Puerto de entrada
ser = serial.Serial(com, baudrate=bad) ## ristra de datos que entran


## DEFINICION DE PARAMETROS
t_v = []    #Vector de tiempos
T_v=[]      #Vector de temperaturas
H_v = []    #Vector de humedades
P_v=[]      #Vector de presiones
D_v =[]     #Vector de distancias

#Creacion de la figura
fig = plt.figure()
ax_T = fig.add_subplot(4,2,1)
ax_P = fig.add_subplot(4,2,3)
ax_H = fig.add_subplot(4,2,5)
ax_D = fig.add_subplot(4,2,7)
ax_3D = fig.add_subplot(122,projection='3d')
plt.subplots_adjust(hspace=0.8 )

#Condiciones iniciales
Vx = 100
Vy = 0
Vz = 100
X=[0]
Y=[0]
Z=[0]

#Funcion que va leyendo los datos
def update(i):
    global A, Vx,Vy,Vz, X,Y,Z
    #Lectura y estructuracion de datos
    dat=ser.readline().decode()
    [T, P, alt , H ,Ax, Ay, Az, D]=dat.split()
    t_v.append(i)
    T_v.append(float(T))
    P_v.append(float(P))
    H_v.append(float(H))
    D_v.append(float(D))
    
    #Limpieza de gráficas
    ax_T.clear()
    ax_P.clear()
    ax_H.clear()
    ax_D.clear()
    ax_3D.clear()

    #Integracion por Euler de la posicion
    dt = float(t_v[i]-t_v[i-1])
    Vx0 = Vx
    Vy0 = Vy
    Vz0 = Vz

    Vx = Vx0 + dt * float(Ax)
    Vy = Vy0 + dt * float(Ay)
    Vz = Vz0 + dt * (float(Az)-1)

    X0 = float(X[i-1])
    Y0 = float(Y[i-1])
    Z0 = float(Z[i-1])

    X.append(X0 + Vx*dt)
    Y.append(Y0 + Vy*dt)
    Z.append(Z0 + Vz*dt)

    #Representacion de funciones
    ax_T.plot(t_v, T_v)
    ax_T.set_title('Temperatura')
    ax_P.plot(t_v, P_v)
    ax_P.set_title('Presion')
    ax_H.plot(t_v, H_v)
    ax_H.set_title('Humedad')
    ax_D.plot(t_v,D_v)
    ax_D.set_title('Distancia Ultrasonidos')
    ax_3D.plot(X,Y,Z)
    ax_3D.set_title('Trayectoria')
    ax_P.grid()
    ax_T.grid()
    ax_H.grid()
    ax_D.grid()
    ax_P.set_ylabel('Pa')
    ax_T.set_ylabel('ºC')
    ax_D.set_ylabel('mm')
    ax_D.set_xlabel('time [s]')
    ax_H.set_ylabel('%')
    
a = FuncAnimation(fig, update, frames=10000, repeat=False)
plt.show()






        
    


    
    