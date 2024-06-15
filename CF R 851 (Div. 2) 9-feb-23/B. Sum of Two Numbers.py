t = int(input())
while t != 0:
  t -= 1

  n = int(input())

  for i in range(n):
    x = str(n - i)
    sx = 0
    for j in x:
      sx += int(j)

    y = str(i)
    sy = 0
    for j in y:
      sy += int(j)

    if (abs(sx - sy) <= 1):
      print(x, y)
      break
