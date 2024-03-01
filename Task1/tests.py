from function import *


def legendre_quad_res_test():
    assert legendre(24, 43) == 1

def legendre_quad_non_res_test():
    assert legendre(11, 17) == -1

def legendre_div_test():
    assert legendre(4, 16) == 0
