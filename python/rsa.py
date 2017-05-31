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

	def encrypt(self, message):
		i = 0
		for char in message:
			cypher = ord(char) ** self.e
			cypher = cypher % self.publicKey
			self.cypherText += str(cypher)
			i += 1
			if i != len(message):
				self.cypherText += " "
		print(self.cypherText)

	def decrypt(self, message):
		tokens = message.split()
		for tok in tokens:
			cypher = int(tok) ** int(self.privateKey)
			print(cypher)
			cypher = cypher % int(self.publicKey)
