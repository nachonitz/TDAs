def reemplazar():
	archivo = input ("Ingrese el archivo: ")
	texto=[]
	palabra_mal = input ("Ingrese la palabra que desea reemplazar: ")
	palabra_bien = input ("Ingrese la palabra correcta: ")
	contador = 0
	with open (archivo, 'r') as f:
		linea = f.readline()
		while linea:
			indice = buscar_palabra(linea,palabra_mal)
			while indice:
				linea = reemplazar_palabra(linea,indice,palabra_mal,palabra_bien)
				indice = buscar_palabra(linea,palabra_mal)
				contador += 1
			texto.append(linea)
			linea = f.readline()
	with open (archivo, 'w') as f:
		cantidad_de_renglones = len(texto)
		for i in range (cantidad_de_renglones):
			f.write(texto[i])
	if not contador:
		print("No se ha corregido ninguna palabra")
	if contador == 1:
		print("Se ha corregido 1 palabra")
	if contador > 1:
		print("Se han corregido {} palabras".format(contador))
def buscar_palabra(texto, palabra):
	largo_texto = len(texto)
	largo_palabra = len(palabra)
	for i in range (largo_texto):
		if texto[i] == palabra[0]:
			if texto[i:i+largo_palabra] == palabra:
				return i
	return False

def reemplazar_palabra(texto,indice,palabra_mal,palabra_bien):
	nuevo_texto = ""
	nuevo_texto += texto[:indice] + palabra_bien + texto[indice + len(palabra_mal)::]
	return nuevo_texto

reemplazar()