""" Una empresa manufacturera te ha asignado la tarea de desarrollar un programa de control para supervlsar las concnclones ae operaaon ae ¯
una måquina en su linea de produccién. La måquina cuenta con sensores que monitorean la temperatura, presiån y humedad. Tu objetivo es
implementar un programa en Python que evalüe estas condiciones y tome decisiones adecuadas para garantizar un funcionamiento seguro y
eficiente de la måquina.
A continuaci6n, se detallan las especificaciones del programa:
Temperatura:
Si Ia temperatura supera los 75 grados Celsius, imprimir "Advertencia: Temperatura elevada. Verificar sistema de enfriamiento."
• Si la temperatura es superior a 75 grados Celsius y la presi6n es superior a 40 psi, imprimir "iALERTA! Temperatura y presi6n elevadas.
Detener Ia rnåquina de inmediato."
• Si la temperatura es superior a 75 grados Celsius pero la presién es igual o inferior a 40 psi, imprimir "Presiön dentro del rango
aceptable."
Si Ia temperatura es de 75 grados Celsius o inferior, imprimir "Temperatura en rango seguro."
Presi6n:
I a presiön supera los 50 psi, imprimir "Advertencia: Presiön elevada. Verificar sistema de control de presiön."
Si la presiån es de 50 psi o inferior, imprimir "Presiån en rango aceptable."
Humedad:
Si la humedad supera el 50%, imprimir '"Advertencia: Humedad elevada. Verificar sistema de control ambiental.'i
Si Ia humedad es del 50% o inferior, imprimir "Humedad en rango aceptable."
• Al final del programa, imprimir "Programa de control de la måquina completado."""

# Inicio del programa
# ayudame a hacer el programa

temp = float(input("Ingrese la temperatura: "))
presion = float(input("Ingrese la presion: "))
humedad = float(input("Ingrese la humedad: "))
# temp = 75
# presion = 40
# humedad = 50
if temp > 75:
    print("Advertencia: Temperatura elevada. Verificar sistema de enfriamiento.")
    if presion > 40:
        print("¡ALERTA! Temperatura y presión elevadas. Detener la máquina de inmediato.")
    else:
        print("Presión dentro del rango aceptable.")
else:
    print("Temperatura en rango seguro.")
if presion > 50:
    print("Advertencia: Presión elevada. Verificar sistema de control de presión.")
else:
    print("Presión en rango aceptable.")
if humedad > 50:
    print("Advertencia: Humedad elevada. Verificar sistema de control ambiental.")
else:
    print("Humedad en rango aceptable.")
print("Programa de control de la máquina completado.")
# Fin del programa
