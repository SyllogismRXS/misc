#!/usr/bin/env python

from mpl_toolkits.mplot3d import Axes3D
import argparse
import numpy
import matplotlib.pyplot as plt

def plot_6dof(path_file):
    data = numpy.loadtxt(path_file)
    fig = plt.figure()
    ax = fig.gca(projection='3d')
    ax.plot(data[:,1],data[:,2],data[:,3],'.-')
    plt.show()

def plot_car(path_file):
    data = numpy.loadtxt(path_file)
    #print(data[:,0])
    #print(data)
    plt.plot(data[:,0], data[:,1])
    plt.xlabel('x')
    plt.ylabel('y')
    plt.grid(True)
    plt.show()


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("path_file")
    parser.add_argument("--car", action='store_true')
    args = parser.parse_args()

    if args.car:
        plot_car(args.path_file)
    else:
        plot_6dof(args.path_file)
    
            
