def reemplazar(texto,palabra_mal,palabra_bien):
	contador = 0
	for i in range (len(texto)):
		indice = buscar_palabra(texto[i],palabra_mal)
		while indice:
			texto[i] = reemplazar_palabra(texto[i],indice,palabra_mal,palabra_bien)
			indice = buscar_palabra(texto[i],palabra_mal)
			contador += 1
	return contador	
def buscar_palabra(texto, palabra):
	largo_texto = len(texto)
	largo_palabra = len(palabra)
	for i in range (largo_texto):
		if texto[i] == palabra[0]:
			if texto[i:i+largo_palabra] == palabra:
				return i
	return False

def buscar_comparador(texto,comparador):
	operadores = ("!","=","<",">","/","*","-","+")
	espacio = " "
	largo_texto = len(texto)
	largo_comparador = len(comparador)
	if largo_comparador > 1:
		indice = buscar_palabra(texto,comparador)
		if (indice == False):
			return False
		while texto[indice-1] == espacio and texto[indice+largo_comparador] == espacio:
			indice = buscar_palabra(texto[indice+largo_comparador:],comparador)
			if indice == False:
				return False
		return indice
	for i in range (largo_texto):
		if texto[i] == comparador:
			if texto[i-1] in operadores or texto[i+1] in operadores:
				continue
			if texto[i-1] != espacio or texto[i+1] != espacio:
				return i
	return False

def reemplazar_palabra(texto,indice,palabra_mal,palabra_bien):
	nuevo_texto = ""
	nuevo_texto += texto[:indice] + palabra_bien + texto[indice + len(palabra_mal)::]
	return nuevo_texto

def agregar_espacios_comparador(texto,indice,comparador):
	espacio = " "
	nuevo_texto = ""
	largo_comparador = len(comparador)
	if largo_comparador > 1:
		if texto[indice-1] != espacio and texto[indice+largo_comparador] == espacio:
			nuevo_texto = reemplazar_palabra(texto,indice,comparador," {}".format(comparador))
		if texto[indice-1] != espacio and texto[indice+largo_comparador] != espacio:
			nuevo_texto = reemplazar_palabra(texto,indice,comparador," {} ".format(comparador))
		if texto[indice-1] == espacio and texto[indice+largo_comparador] != espacio:
			nuevo_texto = reemplazar_palabra(texto,indice,comparador,"{} ".format(comparador))
		return nuevo_texto
	if texto[indice-1] != espacio and texto[indice+1] == espacio:
		nuevo_texto = reemplazar_palabra(texto,indice,comparador," {}".format(comparador))
	if texto[indice-1] != espacio and texto[indice+1] != espacio:
		nuevo_texto = reemplazar_palabra(texto,indice,comparador," {} ".format(comparador))
	if texto[indice-1] == espacio and texto[indice+1] != espacio:
		nuevo_texto = reemplazar_palabra(texto,indice,comparador,"{} ".format(comparador))
	return nuevo_texto

def quitar_problema_de_un_comparador(lista,largo,comparador):
	contador = 0
	largo_comparador = len(comparador)
	for i in range (largo):
		indice = buscar_comparador(lista[i],comparador)
		while indice:
			lista[i] = agregar_espacios_comparador(lista[i],indice,comparador)
			contador += 1
			indice = buscar_comparador(lista[i],comparador)
	return contador

def lista_a_archivo(archivo,lista):
	with open (archivo, 'w') as f:
		cantidad_de_renglones = len(lista)
		for i in range (cantidad_de_renglones):
			f.write(texto[i])
def quitar_problema_de_comparadores(lista,comparadores):
	cantidad_de_renglones = len(lista)
	cantidad_de_errores = []
	for i in range (len(comparadores)):
		errores = quitar_problema_de_un_comparador(lista,cantidad_de_renglones,comparadores[i])
		cantidad_de_errores.append(errores)
		errores = 0
	return cantidad_de_errores

def archivo_a_lista(archivo):
	lista = []
	with open (archivo,'r') as f:
		linea = f.readline()
		while linea:
			lista.append(linea)
			linea = f.readline()
	return lista

def lista_a_archivo(lista,archivo):
	with open (archivo, 'w') as f:
		cantidad_de_renglones = len(lista)
		for i in range (cantidad_de_renglones):
			largo_renglon = len(lista[i])
			for j in range (largo_renglon):
			
				f.write(lista[i][j])
def main():
	archivo = input ("Ingrese el nombre del archivo al que quiere corregir errores comunes: ")
	lista = archivo_a_lista(archivo)
	palabra_mal = "{)"
	palabra_bien = "{ )"
	comparadores = ("=","==",">","<","!=")
	cantidad_de_comparadores = len(comparadores)
	primer_error = reemplazar(lista,"){",") {")
	segundos_errores = quitar_problema_de_comparadores(lista,comparadores)
	lista_a_archivo(lista,archivo)
	print("Se han corregido:\n{} errores de {}".format(primer_error,"){"))
	for i in range (cantidad_de_comparadores):
		print("{} errores de {}".format(segundos_errores[i],comparadores[i]))
main()