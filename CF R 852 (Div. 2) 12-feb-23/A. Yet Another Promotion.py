t = int(input())
while (t != 0):
  t -= 1

  txt = input()
  txt = txt.split()
  a = int(txt[0])
  b = int(txt[1])

  txt = input()
  txt = txt.split()
  n = int(txt[0])
  m = int(txt[1])

  q = int(n / (m + 1))
  r = n - (q * (m + 1))

  print(min(q * min(a * m, b * (m + 1)) + (r * min(a, b)), n * min(a, b)))