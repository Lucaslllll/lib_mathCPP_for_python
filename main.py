import calculus 
import ordenacao

# a = 7; b = 22

# print("MDC: ")
# print(calculus.mdc(a, b))
# print("MMC: ")
# print(calculus.mmc(a, b))
# print("FATORIAL de a: ")
# print(calculus.fatorial(a))
# p = int(input("Digite um número para saber se é primo: "))

# if calculus.wilson(p) == 0:
# 	print("é primo")
# else:
# 	print("não é primo")
	

# print(calculus.potencia(2, 4))


# print(calculus.teste_de_congruencias(5, -3, 7))



# import utils

# cpf = utils.gerador_cpf()
# print("CPF gerado: ", cpf)
# n = ''
# for c in cpf:
# 	n += str(c)
# print(n)

# print(calculus.potencia(3,7))

a = ordenacao.quick_sort([1,5,-2], 0, 3)
print(a)