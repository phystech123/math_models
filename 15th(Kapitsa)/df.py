import pandas as pd
import matplotlib.pyplot as plt
import mpl_toolkits
from mpl_toolkits.mplot3d import Axes3D
import seaborn as sns
import numpy as np
import math
import os
import matplotlib.animation as animation

N = 100000
h = 0.001*1000
nu=1000
l=10
a=0.1
g=9.81
m=2
df1 = pd.read_csv("datas/data_phi.csv", sep=";")
df2 = pd.read_csv("datas/data_omega.csv", sep=";")
X = l*np.sin(df1[" x"])
Y = l*np.cos(df1[" x"]) + a*np.cos(nu*df1['t'])


fig, ax = plt.subplots()



line2 = ax.plot(X[0], Y[0])[0]
ax.set(xlim=[min(X), max(X)], ylim=[min(Y), max(Y)], xlabel='Time [s]', ylabel='Z [m]')
ax.legend()


def update(frame):
    # for each frame, update the data stored on each artist.
    x = X[:frame]
    y = Y[:frame]
    # update the line plot:
    line2.set_xdata(X[:frame])
    line2.set_ydata(Y[:frame])
    return (line2)


ani = animation.FuncAnimation(fig=fig, func=update, frames=N, interval=h)
plt.show()