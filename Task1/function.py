def legendre(a, p):
    print(a)
    print(p)
    print()
    if a == 0:
        return 0
    if a == 1:
        return 1
    elif a == 2:
        return (-1)**((p**2-1)//8)
    elif a % 2 == 0:
        return legendre(2, p)*legendre(a//2, p)
    else:
        return int(legendre(p % a, a)*(-1)**((p-1)*(a-1)/4))
