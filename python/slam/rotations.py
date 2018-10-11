import numpy as np
from math import cos, sin, pi, radians, pow
from pyquaternion import Quaternion

def rot_matrix_z(theta):
    return np.array([[cos(theta), -sin(theta), 0],
                      [sin(theta), cos(theta), 0],
                      [0, 0, 1]])

def rot_matrix_y(beta):
    return np.array([[cos(beta), 0, sin(beta)],
                      [0, 1, 0],
                      [-sin(beta), 0, cos(beta)]])

def rot_matrix_x(gamma):
    return np.array([[1, 0, 0],
                      [0, cos(gamma), -sin(gamma)],
                      [0, sin(gamma), cos(gamma)]])

def rot_matrix_aggregate(roll, pitch, yaw):
    #return (rot_matrix_z(yaw) * (rot_matrix_y(pitch) * rot_matrix_x(roll)))
    return rot_matrix_z(yaw).dot(rot_matrix_y(pitch).dot(rot_matrix_x(roll)))

def rot_matrix(roll, pitch, yaw):
    # gamma is roll
    # beta is pitch
    # alpha is yaw
    ca = cos(yaw)
    cb = cos(pitch)
    sa = sin(yaw)
    sb = sin(pitch)
    sg = sin(roll)
    cg = cos(roll)

    return np.array([[ca*cb, ca*sb*sg - sa*cg, ca*sb*cg + sa*sg],
                      [sa*cb, sa*sb*sg + ca*cg, sa*sb*cg - ca*sg],
                      [-sb, cb*sg, cb*cg]])

def T(roll, pitch, yaw, translate):
    m = np.identity(4, dtype=float)
    m[:3,:3] = rot_matrix(0, 0, 0)
    m[:3,3] = translate
    return m

def skew_sym(w):
    return np.array([[  0,   -w[2], +w[1]],
                     [+w[2],   0,   -w[0]],
                     [-w[1], +w[0],    0]])

def exp_so3(theta, w):
    return np.identity(3) + sin(theta)/theta * skew_sym(w) \
        + (1-cos(theta))/skew_sym(pow(theta,2))

def main():
    roll = radians(10)
    pitch = radians(-20)
    yaw = radians(180)

    R_agg = rot_matrix_aggregate(roll, pitch, yaw)
    print(R_agg)

    R = rot_matrix(roll, pitch, yaw)
    print(R)

    diff = R_agg - R
    print(diff)

    translate = np.array([0, 0, 0])

    my_T = T(roll, pitch, yaw, translate)
    print(my_T)

    Q_rot = Quaternion(axis=[0, 0, 1], angle=yaw) * Quaternion(axis=[0, 1, 0], angle=pitch) * Quaternion(axis=[1, 0, 0], angle=roll)
    print(Q_rot.rotation_matrix)
    print(Q_rot.rotation_matrix - R)

    Q_rot_unit = Q_rot.unit
    print(Q_rot_unit)


if __name__ == '__main__':
    main()
