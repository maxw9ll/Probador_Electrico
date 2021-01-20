import serial
import xlwt
import os
from datetime import datetime

class SerialToExcel:
    

    def __init__(self,port,speed,rm):
        
        self.port = port
        self.speed = speed
        self.rm = rm

        self.wb = xlwt.Workbook()
        self.ws = self.wb.add_sheet("Conexiones Serial",cell_overwrite_ok=True)
        self.ws.col(0).width = 256*21
        self.ws.col(1).width = 256*15
        self.ws.col(2).width = 256*15
        self.ws.col(3).width = 256*18
        self.ws.col(5).width = 256*15
        
        self.ws.row(0).height = 256*2
        #self.ws.write(0, 0, "Data from Serial")
        
        self.style = xlwt.XFStyle()
        self.font = xlwt.Font()
        self.font.bold = True
        self.font.height = 240
        self.style.font = self.font
        
        self.ws.write(0, 1, f"WO {rm}", style = self.style)
        self.columns = ["Date Time"]
        self.number = 100
        

    def setColumns(self,col):
        self.columns.extend(col)
        
    def setRecordsNumber(self,number):
        self.number = number
        
    def readPort(self):
        
        
        ser = serial.Serial(self.port, self.speed, timeout=1)
        c = 0
        for col in self.columns:
            self.ws.write(2, c, col, style = xlwt.easyxf('font: bold 1'))
            c = c + 1
        self.fila = 3

        i = 0
        while(i<self.number):
            lin = str(ser.readline())
            line = lin[2:][:-5]
            if(len(line) > 0):
                now = datetime.now()
                date_time = now.strftime("%m/%d/%Y, %H:%M:%S")
                print(date_time,line)
                if(line.find(",")):
                    c = 1
                    self.ws.write(self.fila, 0, date_time)
                    columnas = line.split(",")
                    for col in columnas:
                        self.ws.write(self.fila, c, col)
                        c = c + 1

                i = i + 1
                self.fila = self.fila + 1
    
    def writeFile(self,archivo):
        try:
            os.chdir("/home/pi/Desktop")
            self.wb.save(archivo)
        except OSError:
            print("Can't change the Current Working Directory")
    
    def wow(self, estado, rm, parte):
        if estado == 1:
            self.ws.write(0, 0, "PASSED", style = self.style)
        else:
            self.ws.write(0, 0, "REJECTED", style = self.style)
        
        self.ws.write(0, 2, rm, style = self.style)
        self.ws.write(0, 3, parte, style = self.style)
