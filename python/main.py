import rsa
import sys

if len(sys.argv) != 3:
	print("Argumentos inválidos")
	sys.exit()

#Cria objeto RSA
alg = rsa.RSA(13, 17, 2, 2)

alg.findPublicKey()

alg.findPrivateKey()

#Leitura de arquivo de entrada
inpString = ""
inp = open(sys.argv[2], 'r')
for line in inp:
	inpString += line

#Limpa fim da string
inpString = inpString.rstrip()

#Determina modo de operação
if sys.argv[1] == 'e':
	alg.encrypt(inpString)
elif sys.argv[1] == 'd':
	alg.decrypt(inpString)
else:
	print("Argumento inválido -- [e|d]")
