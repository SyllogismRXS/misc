#!/usr/bin/env python

import sympy as syp
import matplotlib.pyplot as plt
import numpy as np

x, y = syp.symbols('x y')

fxy = x**2 + y**2
plane = 4*(x-2) + 4*(y-2)

syp.plotting.plot3d(fxy,plane)

#expr_1 = x**2 + y**2
#x_range_1 = (x, -5, 5)
#y_range_1 = (y, -5, 5)
#
#expr_2 = -x**2 + -y**2
#x_range_2 = (x, -5, 5)
#y_range_2 = (y, -5, 5)
#
#p1 = syp.plotting.plot3d(
#    (expr_1, x_range_1, y_range_1),
#    (expr_2, x_range_2, y_range_2)
#)

# x, y, z = syp.symbols('x y z')
#
# curve_1 = x
# curve_2 = x**2
# curve_3 = x**3
#
# x_range = (x, -10, 10)
#
# syp.plot(curve_1, curve_2, curve_3, x_range, show = False)

#my_function = x**2 + y**2 - 50

#curve_1 = syp.plot3d(my_function)

#plot3d(my_function)

# x = symbols('x')
# p1 = plot(x*x)
# p2 = plot(x)
# p1.extend(p2)


#  ########################
#  # Straight matplot lib
#  ########################
#  from mpl_toolkits.mplot3d import Axes3D
#  import matplotlib.pyplot as plt
#  from matplotlib import cm
#  from matplotlib.ticker import LinearLocator, FormatStrFormatter
#  import numpy as np
#
#  fig = plt.figure()
#  ax = fig.gca(projection='3d')
#
#  # Make data.
#  X = np.arange(-5, 5, 0.05)
#  Y = np.arange(-5, 5, 0.05)
#
#  X, Y = np.meshgrid(X, Y)
#  f = X**2 + Y**2
#
#  # Plot the surface.
#  surf = ax.plot_surface(X, Y, f, cmap=cm.coolwarm,
#                         linewidth=0, antialiased=False)
#
#  plane = 4*(X-2) + 4*(Y-2)
#  surf = ax.plot_surface(X, Y, plane, cmap=cm.coolwarm,
#                         linewidth=0, antialiased=False)
#
#  # Customize the z axis.
#  #ax.set_zlim(-1.01, 1.01)
#  #ax.zaxis.set_major_locator(LinearLocator(10))
#  #ax.zaxis.set_major_formatter(FormatStrFormatter('%.02f'))
#
#  ## Add a color bar which maps values to colors.
#  fig.colorbar(surf, shrink=0.5, aspect=5)
#
#  plt.show()
