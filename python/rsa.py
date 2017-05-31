import math

class RSA(object):
	publicKey = None
	privateKey = None
	cypherText = ""
	plainText = ""

	def __init__(self, p, q, e, k):
		self.p = p
		self.q = q
		self.e = e
		self.k = k

	def findPublicKey(self):
		self.publicKey = self.p*self.q

	def gcd(self, a, b):
		if a == 0:
			return b
		else:
			return self.gcd(b%a, a)

	def findPrivateKey(self):
		phi = (self.p-1)*(self.q-1)
		while (self.e < phi):
			if (self.gcd(self.e, phi) == 1):
				break
			else:
				self.e = self.e + 1

		self.privateKey = (1+(self.k*phi))/self.e

	#Criptografa a mensagem
	def encrypt(self, message):
		i = 0
		for char in message:
			#Converte valor de char para ascii
			cypher = ord(char) ** self.e
			cypher = cypher % self.publicKey
			self.cypherText += str(cypher)
			i += 1
			#Verifica se chegou ao fim da string, se não adiciona separador
			if i != len(message):
				self.cypherText += " "

		#Salva texto criptografado em arquivo
		out = open('encrypted.txt', 'w')
		out.write(self.cypherText)

	#Decriptografa a mensage
	def decrypt(self, message):
		#Quebra em tokens para leitura
		tokens = message.split()
		for tok in tokens:
			cypher = int(tok) ** int(self.privateKey)
			cypher = cypher % int(self.publicKey)
			self.plainText += chr(cypher)
		#Salva texto decriptografado em arquivo
		out = open('decrypted.txt', 'w')
		out.write(self.plainText)
