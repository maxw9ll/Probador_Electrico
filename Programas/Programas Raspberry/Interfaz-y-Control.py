#!/usr/bin/env python3
import tkinter as tk
import tkinter.messagebox as msg
from tkinter import *
import time
from serialToExcel import SerialToExcel
import sys
from tkinter.font import Font
import os
import serial
import requests




def aceptar(event=None): # Función para verificar si la WO ingresada tiene la longitud deseada.
    try:
        n = int(var_texto.get())
        entrada = n
        entrada = var_texto.get()
    except (ValueError, Exception):
        var_lbl.set("Entrada no válida. \nIntente nuevamente.")
        cuadro_texto.delete(0, 'end')
    else:
        if len(str(entrada)) == 6:
            var_lbl.set("Realizando prueba. \nEspere un momento por favor.")
            time.sleep(0.1)
            btn_aceptar.focus_set()
            root.after(125, wiw) #1000
        else:
            var_lbl.set("#WO No Válido\nIntente Nuevamente")
            cuadro_texto.delete(0, 'end')
    


root = tk.Tk() # Se crea la ventana de la interfáz
root.geometry("315x150") # Se ajusta el tamaño de la ventana
root.resizable(0, 0) # Se declara que la ventana no sea ajustable mas que por programación
root.winfo_toplevel().title("Rapid Manufacturing") #Título de la ventana


var_texto = tk.StringVar()
var_lbl = tk.StringVar()

mi_label = tk.Label(root, textvariable = var_lbl)

var_lbl.set("Ingrese #WO\nPara Comenzar")

mi_label.grid(row = 0, column = 0, columnspan = 3)
mi_label.place(relx=0.5, rely=0.15, anchor=CENTER)


cuadro_texto = tk.Entry(root, justify='center',
                        textvariable = var_texto, width = 20)
cuadro_texto.focus_set()
cuadro_texto.bind('<Return>', aceptar)
cuadro_texto.bind('<KP_Enter>', aceptar)


cuadro_texto.place(relx=0.5, rely=0.40, anchor=CENTER)

btn_aceptar = tk.Button(root, text = "Aceptar", relief = 'raised', command = aceptar)
btn_aceptar.configure(font=("", 10,))

btn_aceptar.bind('<Return>', aceptar)
btn_aceptar.grid(row = 2, column = 2)
btn_aceptar.place(relx=0.5, rely=0.75, anchor=CENTER)

photo = PhotoImage(file = r"/home/pi/Downloads/wiring.png")
photoimage = photo.subsample(10, 10)

poto = PhotoImage(file = r"/home/pi/Downloads/rot.png")
potoi = poto.subsample(2, 2)

w = Label(root, image=photoimage)
w.place(relx=0.8, rely=0.55)

y = Label(root, image = potoi)
y.place(relx=0, rely=0.1)


def wiw(): # Función donde comprueba si la WO ingresada es válida y si existe algún fallo de conexiones o comunicación
    ser = ""
    i = 0
    j = 0
    workOrder = int(var_texto.get()) # Variable donde se almacena la WO ingresada
    
    
    
    try: # Se define el puerto y el baud de comunicación con Arduino
        ser = serial.Serial("/dev/ttyACM0",19200)
        serialToExcel = SerialToExcel("/dev/ttyACM0",19200, workOrder)
        
    except Exception: # Se define el puerto y el baud de comunicación con Arduino si no está disponible el otro puerto
        try:
            ser = serial.Serial("/dev/ttyACM1",19200)
            serialToExcel = SerialToExcel("/dev/ttyACM1",19200, estado)
            
        except Exception:
            var_lbl.set("Error. Intente Nuevamente.")
            print("Error")
            cuadro_texto.focus_set()            
                
            
    finally: # Una vez establecido el puerto de comunicación se procede a mandar la WO para obtener la RM y el No. de parte
        url = *********************************************************************
        myobj = {
        "apiUser": "*********",
        "apiKey": "**********************************",
        "workOrder":workOrder
        } # Por cuestiones de seguridad no se publica "apiUser" y "apiKey"
            
        try: # Aquí se verifica que la WO sea válida
            response = requests.post(url, json = myobj)
            rm = response.json()['rm']
            parte = response.json()['partNumber']
        except Exception: # Si la WO no es válida se imprime una Error
            var_lbl.set("Error con WO\nIntente Nuevamente")
            cuadro_texto.delete(0, 'end')
            cuadro_texto.focus_set()
        else: # Si la WO es válida se manda un número al Arduino para indicar que programa correr dependiendo de la RM obtenida
            time.sleep(0.5)
            if rm == 'RM80983':
                ser.write("3\n".encode('utf-8'))
            elif rm == 'RM81418':
                ser.write("2\n".encode('utf-8'))
                #print("aqui")
            else: # Si no se encuentra la RM reustrada se deberá notificar
                ser.write("Revisar".encode('utf-8'))
            time.sleep(0.5)
            
            def waw(rm): # Función para almacenar los datos obtenidos de Arduino a un archivo .xls

                columnas = ["#","Instruction Type","From Points", "To Points", "Measured"]

                serialToExcel.setColumns(["#","Instruction Type","From Points", "To Points", "Measured"])
                if rm == 'RM80983':
                    serialToExcel.setRecordsNumber(13) #Recibe
                elif rm == 'RM81418':
                    serialToExcel.setRecordsNumber(5) #Recibe
                serialToExcel.readPort()

                try:
                    reading = ser.readline().decode('utf-8', errors = 'replace')
                except (Exception, UnicodeDecodeError):
                    try:
                        reading = ser.readline().decode('utf-8', errors = 'replace')
                    except UnicodeDecodeError:
                        print("Ejecutar nuevamente")
                    
                if reading.strip() == '3' and rm == 'RM80983':
                    print("PASSED")
                    serialToExcel.wow(1, rm, parte)
                elif reading.strip() == '1' and rm == 'RM81418':
                    print("PASSED")
                    serialToExcel.wow(1, rm, parte)
                else:
                    serialToExcel.wow(0, rm, parte)
                    print(reading.strip())


                serialToExcel.writeFile("archivo-conexiones.xls")
                
                #time.sleep(0.05) #0.125
                var_lbl.set("Pruebas terminadas. \nDocumento generado.")
                cuadro_texto.delete(0, 'end')
                
            
            reading = "tr"

            os.chdir("/home/pi/Desktop")
            f = open('myfile.txt', 'w')
            time.sleep(1)
            while reading.strip() != 'break':
                
                reading = ser.readline().decode('utf-8', errors = 'replace')
                #print(reading.strip())
                if reading.strip() != 'break':
                    print(reading)
                    f = open('myfile.txt', 'a')
                    f.write(reading)
                    # + "\n"   
                else:
                    print(reading.strip())
            f.close()
            
            if os.stat("myfile.txt").st_size <= 10:
                alo = 1
                
                cuadro_texto.delete(0, 'end')
                cuadro_texto.focus_set()
                
            if alo == 0:
                with open('myfile.txt', 'r') as file:
                    for line in file:
                        for word in line.split():
                            if word == 'CONECTADO':
                                j = j + 1
                file.close()
                if j == 3 or j == 1: ##Conectado
                    var_lbl.set("No Hay Ensamble Conectado.\nIntente Nuevamente.")
                    cuadro_texto.delete(0, 'end')
                    cuadro_texto.focus_set()
                    time.sleep(0.25)
                else:
                    waw(rm)
                    while i < 0:
                        reading = ser.readline().decode('utf-8', errors = 'replace')
                        #time.sleep(0.05) #0.2
                        i=i+1
                        break

                    if reading.strip() == '3' and rm == 'RM80983':
                        print("PASSED")
                    elif reading.strip() == '1' and rm == 'RM81418':
                        print("PASSED")
                    else:
                        print(reading.strip())

                    osCommandString = "xdg-open myfile.txt"
                    os.system(osCommandString)
                    time.sleep(5)
                    osCommandString = "killall mousepad"
                    os.system(osCommandString)
                    time.sleep(0.01)
                    root.focus_set()
                    time.sleep(0.01)
                    #cuadro_texto.focus_set()
                    root.after(50, gg)

def close(event): # Función para cerrar la ventana de interfáz con la tecla "esc"
    root.withdraw() # if you want to bring it back
    sys.exit() # if you want to exit the entire thing

def gg(): # Función para repetir el programa y reiniciar el mensaja de la ventana de interfáz
    #cuadro_texto.focus_set()
    time.sleep(2)
    var_lbl.set("Ingrese #WO\nPara Comenzar")
    cuadro_texto.focus_set()
    
root.bind('<Escape>', close)
        
root.mainloop()
