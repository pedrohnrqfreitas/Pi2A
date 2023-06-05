cpfsls = list()
filename = 'cpfs.txt'
with open (filename) as fin:
   for line in fin:
      cpfsls.append(line.strip())

cpfsls.sort()
print(cpfsls)

filename = 'CPF.txt'
with open(filename, 'w') as fout:
   for cpf in cpfsls:
      fout.write(cpf +'\n')



