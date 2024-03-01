from function import *


def test_legendre_quad_res():
    assert legendre(24, 43) == 1

def test_legendre_quad_non_res():
    assert legendre(11, 17) == -1

def test_legendre_div():
    assert legendre(4, 16) == 0
