import rsa

alg = rsa.RSA(3, 7, 2, 2)

alg.findPublicKey()
print(getattr(alg, 'publicKey'))

alg.findPrivateKey()
print(getattr(alg, 'privateKey'))

print("Encrypting")
alg.encrypt("hello")
print("Decrypting")
alg.decrypt("20 5 12 12 6")
