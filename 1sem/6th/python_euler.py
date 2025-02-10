import numpy
import math
import time


if __name__ == "__main__":
    start_time = time.time()
    X = list()
    V = list()
    X.append(10)
    V.append(0)
    h = 1
    N = 100000000
    W = 10
    for i in range(N):
        X.append(X[-1] + h*V[-1])
        V.append(V[-1] - h*pow(W, 2) * math.sin(X[-2]))

    end_time = time.time()
    print(end_time - start_time)
    
    