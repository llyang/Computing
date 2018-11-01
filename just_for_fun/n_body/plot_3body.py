#! /usr/bin/env python3

import sys
import numpy as np
from matplotlib import pyplot as plt
from matplotlib import animation


def do_plot(fn):
    fig = plt.figure()
    ax = plt.axes(xlim=(-2, 2), ylim=(-2, 2))
    line, = ax.plot([], [], linewidth=2, color='blue')
    ball, = ax.plot([], [], marker='o', markersize=12, color='black')

    def init():
        line.set_data([], [])
        ball.set_data([], [])
        return line, ball

    def animate(i):
        line.set_data(data[:i, 0], data[:i, 1])
        ball.set_data(data[i - 1, 0], data[i - 1, 1])
        return line, ball

    data = np.loadtxt(fn)

    anim = animation.FuncAnimation(
        fig,
        animate,
        init_func=init,
        frames=len(data),
        interval=1,
        repeat=False,
        blit=True)

    plt.show()


if __name__ == '__main__':

    if len(sys.argv) > 1:
        do_plot(sys.argv[1])
    else:
        print('require a filename')
