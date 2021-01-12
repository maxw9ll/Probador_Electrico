#!/usr/bin/env python3
import tkinter as tk
import tkinter.messagebox as msg
from tkinter import *
import time
from serialToExcel import SerialToExcel
import sys
from tkinter.font import Font
import RPi.GPIO as gpio
import os
import serial
estado = 0




def aceptar(event=None):
    try:
        n = int(var_texto.get())
        estado = n
        estado = var_texto.get()
    except (ValueError, Exception):
        var_lbl.set("Entrada no válida. \nIntente nuevamente.")
        cuadro_texto.delete(0, 'end')
    else:
        if len(str(estado)) == 6:
            var_lbl.set("Realizando prueba. \nEspere un momento por favor.")
            time.sleep(0.1)
            btn_aceptar.focus_set()
            root.after(125, wiw) #1000
        else:
            var_lbl.set("#WO No Válido\nIntente Nuevamente")
            print(len(estado))
            cuadro_texto.delete(0, 'end')
    


root = tk.Tk()
root.geometry("315x150")
root.resizable(0, 0)
root.winfo_toplevel().title("Rapid Manufacturing")


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


def wiw():
    ser = ""
    alo = 0
    i = 0
    j = 0
    coco = 0
    estado = int(var_texto.get())
    gpio.setmode(gpio.BOARD)
    gpio.setwarnings(False)
    gpio.setup(12, gpio.OUT)
    gpio.output(12, True)
    time.sleep(0.5)
    
    
    try:
        ser = serial.Serial("/dev/ttyACM0",19200)
        serialToExcel = SerialToExcel("/dev/ttyACM0",19200, estado)
    except Exception:
        try:
            ser = serial.Serial("/dev/ttyACM1",19200)
            serialToExcel = SerialToExcel("/dev/ttyACM1",19200, estado)
        except Exception:
            var_lbl.set("Error. Intente Nuevamente.")
            print("Error")
            cuadro_texto.focus_set()            
                
            
    finally:
        
    
        def waw():

            columnas = ["#","Instruction Type","From Points", "To Points", "Measured"]

            serialToExcel.setColumns(["#","Instruction Type","From Points", "To Points", "Measured"])
            serialToExcel.setRecordsNumber(5)
            serialToExcel.readPort()

            try:
                reading = ser.readline().decode('utf-8', errors = 'replace')
            except (Exception, UnicodeDecodeError):
                try:
                    reading = ser.readline().decode('utf-8', errors = 'replace')
                except UnicodeDecodeError:
                    print("Ejecutar nuevamente")
                
            if reading.strip() == '3':
                print("PASSED")
                serialToExcel.wow(1)
            else:
                serialToExcel.wow(0)
                print(reading.strip())


            serialToExcel.writeFile("archivo-conexiones.xls")
            gpio.output(12, False)
            #time.sleep(0.05) #0.125
            gpio.cleanup()
            var_lbl.set("Pruebas terminadas. \nDocumento generado.")
            cuadro_texto.delete(0, 'end')
            
        
        reading = "tr"

        os.chdir("/home/pi/Desktop")
        f = open('myfile.txt', 'w')
        time.sleep(1)
        while reading.strip() != 'break':
            
            reading = ser.readline().decode('utf-8', errors = 'replace')
            #print(reading.strip())
            if reading.strip() == "bai":
                print("hola")
                coco = 1
                print(coco)
                break
            elif reading.strip() != 'break':
                print(reading)
                f = open('myfile.txt', 'a')
                f.write(reading)
                # + "\n"   
            else:
                print(reading.strip())
        f.close()
        
        if os.stat("myfile.txt").st_size <= 10:
            alo = 1
            if coco == 0:
                #alo = 1
                var_lbl.set("Intente Nuevamente.")
                cuadro_texto.delete(0, 'end')
                #cuadro_texto.focus_set()
                #gpio.cleanup()
            elif coco == 1:
                #alo = 1
                var_lbl.set("Comprobar Conexión\nRaspberry - Arduino")
                #cuadro_texto.focus_set()
            cuadro_texto.delete(0, 'end')
            cuadro_texto.focus_set()
            gpio.cleanup()
            
        if alo == 0:
            with open('myfile.txt', 'r') as file:
                for line in file:
                    for word in line.split():
                        if word == 'CONECTADO':
                            j = j + 1
            file.close()
            if j == 3:
                var_lbl.set("No Hay Ensamble Conectado.\nIntente Nuevamente.")
                cuadro_texto.delete(0, 'end')
                cuadro_texto.focus_set()
                gpio.cleanup()
            else:
                waw()
                while i < 0:
                    reading = ser.readline().decode('utf-8', errors = 'replace')
                    #time.sleep(0.05) #0.2
                    i=i+1
                    break

                if reading.strip() == '3':
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

def close(event):
    root.withdraw() # if you want to bring it back
    sys.exit() # if you want to exit the entire thing

def gg():
    #cuadro_texto.focus_set()
    time.sleep(2)
    var_lbl.set("Ingrese #WO\nPara Comenzar")
    cuadro_texto.focus_set()
    
root.bind('<Escape>', close)
        
root.mainloop()