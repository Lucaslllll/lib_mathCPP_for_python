import calculus 

a = 7; b = 22

print("MDC: ")
print(calculus.mdc(a, b))
print("MMC: ")
print(calculus.mmc(a, b))
print("FATORIAL de a: ")
print(calculus.fatorial(a))
p = int(input("Digite um número para saber se é primo: "))

if calculus.wilson(p) == 0:
	print("é primo")
else:
	print("não é primo")
	