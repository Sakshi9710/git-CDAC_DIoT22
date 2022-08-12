numbers = range(-15,15)
less_than_zero = list(filter(lambda x : x<0 , numbers))

print(less_than_zero)

x = lambda a : a +10
print(x(5))

x = lambda a,b : a*b
print(x(5,6))

x = lambda a,b,c : a +b+c
print(x(5,6,+9))