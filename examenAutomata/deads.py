# Bryan Ithan Landín Lara A01636271
# Luis Fernando Cuevas Arroyo A01637254
# Jorge Ivan Sanchez Gonzalez A01761414
# Adolfo Hernández Signoret A01637184
# Cared Nicolle Castaños Manjarrez A01742620

# Ejercicio autómata pushdown que valide un palíndromo

import math

def validar(val):
  print("valores:",val)
  flag = 0
  for x in val:
    if x != "a" and x != "b":
      flag = 1
  if flag == 1:
    print("Esta cadena no es valida de la forma:")
    print("w w^-1")
    
    exit()

def automata_de_pila(val):
  #tenemos que hacer un automata que guarde la pila para comparar si es palindromo o no
  pila = ["#"]
  alfabeto_pila = "a"
  alfabeto_pila2 = "b"
  estado = 0
  for x in val:
    if estado == 0:
      if x == "a":
        pila.append("a")
        estado = 1
      elif x == "b":
        pila.append("b")
        estado = 2
    elif estado == 1:
      if x == "a":
        pila.append("a")
      elif x == "b":
        pila.pop()
    elif estado == 2:
      if x == "b":
        pila.append("b")
      elif x == "a":
        pila.pop()
  if pila == ["#"]:
    print("La cadena es un palindromo")
  else:
    print("La cadena no es un palindromo")

def ejercicio2():
  valores = input("Digita la cadena: ")
  validar(valores)
  automata_de_pila(valores)


ejercicio2()