t = int(input())
while t != 0:
  t -= 1

  n = int(input())
  a = input()
  a = a.split()
  lista = []
  m1 = 1
  m2 = 1
  sol = False
  for i in a:
    lista.append(int(i))
    m2 *= lista[-1]
  for i in range(len(lista)):
    m2 /= lista[i]
    m1 *= lista[i]
    if m1 == m2:
      print(i + 1)
      sol = True
      break
  if not sol:
    print(-1)