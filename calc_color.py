import sys

r = float(sys.argv[1])
g = float(sys.argv[2])
b = float(sys.argv[3])

if(r > 1 and g > 1 and b > 1):
  print("r: " + str( r / 255))
  print("g: " + str( g / 255))
  print("b: " + str( b / 255))
else:
  print("r: " + str( r * 255))
  print("g: " + str( g * 255))
  print("b: " + str( b * 255))
