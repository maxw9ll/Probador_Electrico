// Se definen los pines de un extremo del cable. Estos pines serán de entrada.
int j24[] = {22, 24, 26, 28, 30, 32, 34, 36, 38, 40}; //Se definen los pines de salida
int p4[] = {11, 10, 9, 8, 7, 6, 5, 4, 3, 2}; // Se definen los pines de entrada
int p9[] = {23, 25, 27, 29, A14, A15, 31, 33, 35, 37}; //Se definen los pines de entrada/salida

//Linea 1223

//int contador = 0;
int x = 0;
int y = 0;
int ensamble = 0;
int w =0;
int conectado = 0;
int fallo = 0;

// Se definen los pines de componentes de salida: buzzer, led verde y led rojo
#define buz 47
#define greenLed 49
#define redLed 51


// Se declara una constante de un botón de sólo lectura 
const int buttonPin = 50; 

// Se declara un valor que será el estado del botón
int buttonState = 0;
int coco = 0;

int nada = 0; //Variable que indica si todos los pines de entrada están en HIGH
int sumador = 0;
int suma = 0;
int misi = 0;
int simi = 0;
int misito = 0 ;
int mini = 0;
int miniCont = 0;
int bu = 0;
int ncEstado = 0;
int k = 0;
int n = 0;
int o = 0;
int p = 0;
int q = 0;
int s = 0;
String bs = "BS";
int op[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int misO[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int misI[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int opj24p9[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int misOj24p9[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int misIj24p9[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int opp9p4[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int misOp9p4[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int misIp9p4[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

String arr[] = {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "};

String sta2[] = {"1,WIRE,P4-001,J24-001,", "2,WIRE,J24-001,P9-001,", "3,WIRE,P4-002,J24-002,", "4,WIRE,J24-002,P9-002,", "5,WIRE,P4-007,P4-BS,", "6,WIRE,P4-BS,J24-007,", 
"7,WIRE,J24-007,J24-BS,", "8,WIRE,J24-BS,P9-007,", "9,WIRE,P9-007,P9-BS,", "10,WIRE,P4-008,P9-008,", "11,WIRE,J24-005,P9-005,", "12,WIRE,J24-006,P9-006,", "13,RESISTOR,P9-005,P9-006,"};

int vs = 0;
int vsM = 0;


// Setup

void setup() {

  Serial.begin(19200);
    
  // Se declaran los pines de entrada 
  for(int i = 0; i < 10; i++){
    pinMode(p4[i], INPUT);
    pinMode(p9[i], INPUT);
  }

  // Se declaran los pines de salida
  for(int j = 0; j < 10; j++){
    pinMode(j24[j], OUTPUT);
  }
  
  // Se declaran el buzzer y el botón
  pinMode(greenLed, OUTPUT);
  digitalWrite(greenLed,LOW);
  
  pinMode(redLed, OUTPUT);
  digitalWrite(redLed,LOW);
  
  pinMode(buz, OUTPUT);
  digitalWrite(buz,LOW);
  
  pinMode(buttonPin, INPUT);


}

void variables(){
  int nada = 0; //Variable que indica si todos los pines de entrada están en HIGH
  int sumador = 0;
  int suma = 0;
  int misi = 0;
  int simi = 0;
  int misito = 0 ;
  int mini = 0;
  int miniCont = 0;
  int bu = 0;
  int ncEstado = 0;
  int k = 0;
  int n = 0;
  int o = 0;
  int p = 0;
  int q = 0;
  int s = 0;
  int vs = 0;
  int vsM = 0;
}

void continuidad(){
  
  //nada = 0;
  for(int i = 0; i < 10; i++){
    digitalWrite(j24[i], HIGH);
  }
  for(int j = 0; j < 10; j++){
    if (digitalRead(p4[j]) == HIGH){
        nada = nada + 1;
      
    }
  }
  for(int a = 0; a < 10; a++){
        digitalWrite(j24[a], LOW);
      }
      
  

  
  if (nada == 0){
    Serial.println(F("NO HAY ENSAMBLE CONECTADO J24-P4"));
    delay(750);
    conectado = conectado + 1;
    fallo = fallo + 1;
  }
  
  else{
    openIndividual();
    miniO();
    llamarMiswire();
    misto();
    aprobado();
  }
  nada = 0;
}



void llamarMiswire(){
  for(int j = 0; j < 10; j++){
        misWire(j);
      }
}

void salidasLCD(int p){
  //delay(750);
  op[p-1] = op[p-1] + 1;
  if(p!=10){
    Serial.print(F("OPEN P4 EN POSICION ")); Serial.println(p);
  }
  else{
    Serial.println(F("OPEN P4 EN BS"));
  }
  y = y + 1;
  delay(125);
}

void salidaMiswire(int x, int z){
  
  
  if(z==5 or z==6 or z==3 or z==4 or z==8 or z==9 or x==3 or x==4 or x==8 or x==9){
    misO[x-1] = 1;
    misI[z-1] = 1;
    Serial.print(F("CONEXION J24 "));
    
    if(x!=10){
      Serial.print(x);
    }
    
    else{
      Serial.print(bs);
    }
      
    Serial.print(F(" - P4 "));
    
    if(z!=10){
      Serial.print(z);
    }
    else{
      Serial.print(bs);
    }
     
    Serial.println(F(" NO DEBE CONECTARSE"));
    y = y + 1;
    delay(125);
  }
  else if(x == z){
    
  }
  else if(x==7 and z ==10){
    
  }
  else if(x==10 and z==7){  
  
  }
  else{
  misO[x-1] = 1;
  misI[z-1] = 1;
  Serial.print(F("MISWIRE: "));
  if(x!=10){
    Serial.print(x);
  }
  else{
    Serial.print(bs);
  }
  Serial.print(F(" Y "));
  
  if(z!=10){
    Serial.print(z);
  }
  else{
    Serial.print(bs);
  }
  Serial.println(F(" J24 -- P4 :("));
  y=y+1;
  delay(125);
  }
}


void openIndividual(){
  
  for(int j =0; j < 10; j++){
    digitalWrite(j24[j], HIGH);
  }
  for(int i = 0; i < 10; i++){
    //contador = 0; 
    switch(i){
      case 0:
        //verifica = lecturaEntrada(0);
        if (digitalRead(p4[0]) == LOW){
          salidasLCD(1); 
          //y = y + 1;                                         
        }
        break;
      case 1:
        if (digitalRead(p4[1]) == LOW){
          salidasLCD(2);   
          //y = y + 1;                                           
        }
        break; 
      case 6:
        if (digitalRead(p4[6]) == LOW){
          salidasLCD(7);   
          //y = y + 1;                                           
        }
        break;
      case 9:
        if (digitalRead(p4[9]) == LOW and i!=6){
          salidasLCD(10);   
          //y = y + 1;                                           
        }
        break;           
     }
   }
   for(int a = 0; a < 10; a++){
        digitalWrite(j24[a], LOW);
      }
}



void misWire(int x){


  for(int i = 0; i < 10; i++){
    if(i==x){
      pinMode(j24[x], OUTPUT);
      digitalWrite(j24[x], HIGH);
    }
    else{
      digitalWrite(j24[i], LOW);
      pinMode(j24[i], INPUT);
    }
  }

  for(int j = 0; j < 10; j++){

    if(digitalRead(p4[j]) == HIGH and j==2 and j==x){
      salidaMiswire(x+1, j+1);
      y=y+1;
    }
    if(digitalRead(p4[j]) == HIGH and j==3 and j==x){
      salidaMiswire(x+1, j+1);
      y=y+1;
    }
    if(digitalRead(p4[j]) == HIGH and j==4 and j==x){
      salidaMiswire(x+1, j+1);
      y=y+1;
    }
    if(digitalRead(p4[j]) == HIGH and j==5 and j==x){
      salidaMiswire(x+1, j+1);
      y=y+1;
    }
    if(digitalRead(p4[j]) == HIGH and j==7 and j==x){
      salidaMiswire(x+1, j+1);
      y=y+1;
    }
    if(digitalRead(p4[j]) == HIGH and j==8 and j==x){
      salidaMiswire(x+1, j+1);
      y=y+1;
    }
    
    if(digitalRead(p4[j]) == HIGH and j!=x){
      k=j;
      if(x == 6 or x == 9){
        switch(x){
            case 6:
            for(int i = 0; i < 10; i++){
              digitalWrite(j24[i], LOW);
            }
            pinMode(j24[9], INPUT);
            digitalWrite(j24[6], HIGH);
            break;
            case 9:
            for(int i = 0; i < 10; i++){
              digitalWrite(j24[i], LOW);
            }
            pinMode(j24[6], INPUT);
            pinMode(j24[9], OUTPUT);
            digitalWrite(j24[3], HIGH);
            break;
          }
          
    }
 
          //if(k!=6 and k!=9){
            salidaMiswire(x+1, k+1);
           // y = y + 1;
        //digitalWrite(j24[x], LOW);
        //}
    }
    
   /* for(int k = 0; k < 6; k++){
      pinMode(j24[k], OUTPUT);
    }*/
    
  }

  
  
 
   
    
    for(int k = 0; k < 10; k++){
      pinMode(j24[k], OUTPUT);
      digitalWrite(j24[k], LOW);
    }
    misi = 0;
    misito = 0;
    k=0;
    x=0;
}

void misto(){
  for(int i = o; i < 10; i++){
    pinMode(j24[i], OUTPUT);
    digitalWrite(j24[i], LOW);
    pinMode(j24[i], INPUT);
    }
        
    pinMode(j24[9], OUTPUT);
    digitalWrite(j24[9], HIGH);
    
    if(digitalRead(p4[6]) == HIGH or digitalRead(p4[9]) == HIGH){
      misi = misi + 1;
       }
    
    digitalWrite(j24[9], LOW);
    pinMode(j24[9], INPUT);
    pinMode(j24[6], OUTPUT);
    digitalWrite(j24[6], HIGH);
          
    if(digitalRead(p4[6]) == HIGH or digitalRead(p4[9]) == HIGH){
      misito = misito + 1;
       }
       
     digitalWrite(j24[6], LOW);
          
    if(misi == 1 and misito == 0){
      for(int i = 0; i < 10; i++){
        if(i!= 6 and i!=9){
          
          pinMode(j24[i], OUTPUT);
          digitalWrite(j24[i], HIGH);
         }
              
       
          if(digitalRead(p4[6]) == HIGH or digitalRead(p4[9]) == HIGH){
             Serial.print(F("MISWIRE J24 ")); Serial.print(i+1);
             Serial.println(F(" - 7"));
             y=y+1; 
             delay(125);
          }
          
          digitalWrite(j24[i], LOW);
          digitalWrite(j24[i], INPUT);
        
        }
        
        misi = 0;
        misito = 0;
      }
          
      else if(misi == 0 and misito == 1){
        pinMode(j24[6], INPUT);
        for(int i = 0; i < 9; i++){
          if(i!= 6 and i!=9){
            pinMode(j24[i], OUTPUT);
            digitalWrite(j24[i], HIGH);
           }
              
           if(digitalRead(p4[6]) == HIGH or digitalRead(p4[7]) == HIGH){
             Serial.print(F("MISWIRE J24 ")); Serial.print(i+1);
             Serial.println(F(" - BS"));
             y=y+1;
             delay(125); 
            }
            
           digitalWrite(j24[i], LOW);
           digitalWrite(j24[i], INPUT);
            
         }
         
         misi = 0;
         misito = 0;
       
       }

       else if(misi ==0 and misito == 0){
        for(int i = 0; i < 10; i++){
          if(i!= 6 and i!=9){
            pinMode(j24[i], OUTPUT);
            digitalWrite(j24[i], HIGH);
           }
              
          if(digitalRead(p4[6]) == HIGH or digitalRead(p4[9]) == HIGH){
             Serial.print(F("MISWIRE J24 ")); Serial.print(i+1);
             Serial.println(F(" CON P4: 7 y BS"));
             y=y+1;
             delay(125);  
           }
           
           digitalWrite(j24[i], LOW);
           pinMode(j24[i], INPUT);
        }
        
        
        
       }
       misi = 0;
       misito = 0;
       
       for(int k = 0; k < 10; k++){
        pinMode(j24[k], OUTPUT);
        digitalWrite(j24[k], LOW);
        }   
}




void aprobado(){
  for(int i = 0; i < 10; i++){
    digitalWrite(j24[i], LOW);
  }
  x=0;
    for(int j = 0; j < 10; j++){
      digitalWrite(j24[j],HIGH);
      if(digitalRead(p4[j] == HIGH)){
        if(y==0){
          if(j != 4 && j != 5 and j!=2 and j!=3 and j!=7 and j!=8){
          x = x + 1;
          }
          
        }
      digitalWrite(j24[j],LOW);
    }
   }
 
  if(x == 4){
    Serial.println(F("CONEXION J24-P4 APROBADA :)"));
    delay(125);  
    Serial.println();
    ensamble = ensamble + 1;
    delay(125);
  }
  else{     
    Serial.println(F("CONEXION J24-P4 DEFECTUOSA :("));
    delay(125);  
    Serial.println();
    delay(125);
    fallo = fallo + 1;
  }
  x = 0;
  y = 0;
}



void salidasMini(int o){
  op[o-1] = op[o-1] + 2;
  if(o!=10){
    Serial.print(F("OPEN J24 POSICION ")); Serial.println(o);
  }
  else{
    Serial.println(F("OPEN J24 EN BS"));
  }
  y=y+1;
  delay(125);
}



void miniO(){
  mini = 0;
 for(int i = 0; i < 10; i++){
  digitalWrite(j24[i], LOW);
  pinMode(j24[i], INPUT);
 }
 mini = 0;
      p = 0;
  for(int k =0; k < 10; k++){
    pinMode(j24[k], OUTPUT);
    digitalWrite(j24[k], HIGH);
   // pinMode(j24[1], INPUT);
    for(int j = 0; j < 10; j++){
      if(digitalRead(p4[j]) == LOW){
        mini = mini + 1;
      }
    }
    
      switch(k){
        
      case 0:
        if(mini==10){
          salidasMini(1);
        }
        break;
      case 1:
        if(mini==10){
          salidasMini(2);
        }
        break;
      case 6:
        if(mini==10){
          salidasMini(7);
        }
        break;
      case 9:
        if(mini==10){
          salidasMini(10);
        }
        break;
      }
       
      mini = 0;
      p = 0;
      digitalWrite(j24[k], LOW);
      pinMode(j24[k], INPUT);
  }
  for(int i = 0; i < 10; i++){
  pinMode(j24[i], OUTPUT);
 }

}


//

/*segundo programaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa*/


void continuidadj24p9(){ // Función que verifia si hay un ensamble conectado o no
  
  for(int i = 0; i < 10; i++){ // Se ponen en HIGH todas las salidas de j24
    digitalWrite(j24[i], HIGH);
  }
  for(int j = 0; j < 10; j++){  // Se leen las entradas en p9
    if (digitalRead(p9[j]) == HIGH){
          nada = nada + 1;
        
    }
  }
  for(int a = 0; a < 10; a++){ // Se ponen en LOW todas las salidas de j24
    digitalWrite(j24[a], LOW);
  }
  
  
  if (nada == 0){ // Si no se detecta nada en las entardas entonces no hay nada conectado
  
    Serial.println(F("NO HAY ENSAMBLE CONECTADO J24-P9"));
    delay(125); //Tiempo de muestreo
    conectado = conectado + 1; //Para saber cuantos no están conectados
    fallo = fallo + 1; //Fallos
  }
  else{ //Si se detecta por lo menos 1 pin entonces se llaman a las siguienres funciones 
    openIndividualj24p9(); //Función para detectar si una entrada no lee nada lo que se interpreta como open en p9
    
    miniOj24p9(); // Lo mismo que la anterior solo que es si una salida no es detectada de j24
    
    llamarMiswirej24p9(); // Función que detecta los miswires si es que hay excepto para los pines 7 y 10
    
    mistoj24p9(); // Función que detecta los miswires con relación a los pines 7 y 10
    
    resistenciaj24p9(); // Función para detectar si se encuentra conectada o no la rsistencia en los 5 y 6
    
    aprobadoj24p9(); // Si no se detecta ningun error se aprobará el ensamble
  }
  nada = 0; // Se reinicia el contador para detectar pines
}


void llamarMiswirej24p9(){ // Llama a una salida para compararla con las entrada y ver si se conectó donde no corresponde
  for(int j = 0; j < 10; j++){
        misWirej24p9(j);
      }
}

void salidasLCDj24p9(int p){ // Si hay un open en p9 esta función es llamada para imprimirlo en la pantalla LCD
  opj24p9[p-1] = opj24p9[p-1] + 1;
  
  if(p!=10){
    Serial.print(F("OPEN P9 POSICION ")); Serial.println(p);
  }
  
  else{
    Serial.println(F("OPEN P9 EN BS"));
  }
  y = y + 1;
  delay(125);
}

void salidaMiswirej24p9(int x, int z){ // Si un miswire es detectado esta función es llamada para imprimirlo en la pantalla LCD
  
  if(z==3 or z==4 or z==8 or z==9 or x==3 or x==4 or x==8 or x==9){  
    misOj24p9[x-1] = 1;
    misIj24p9[z-1] = 1;
    Serial.print(F("CONEXION J24 "));
    
    if(x!=10){
      Serial.print(x);
    }
    else{
      Serial.print(bs);
    }
    
    Serial.print(F(" - P9 "));
    
    if(z!=10){
      Serial.print(z);
    }
    else{
      Serial.print(bs);
    }
    Serial.println(F(" NO DEBE CONECTARSE"));
    y = y + 1;
    delay(125);
  }
  
  else if(x == z){
    
  }
  
  else if(x==7 and z ==10){
    
  }
  
  else if(x==10 and z==7){  
  
  }
  
  else{
  misOj24p9[x-1] = 1;
  misIj24p9[z-1] = 1;
  Serial.print(F("MISWIRE: "));
  
  if(x!=10){
    Serial.print(x);
  }
  else{
    Serial.print(bs);
  }
  
  Serial.print(F(" Y "));
  
  if(z!=10){
    Serial.print(z);
  }
  else{
    Serial.print(bs);
  }
  Serial.println(F(" J24 - P9 :(!"));
  y=y+1;
  delay(125);
  }
}


void openIndividualj24p9(){ // Función que detecta si hay alguna posición open de p9
  
  for(int j =0; j < 10; j++){ // Todas las salidas se ponen en HIGH
    digitalWrite(j24[j], HIGH);
  }
  
  for(int i = 0; i < 10; i++){
    switch(i){
      case 0:
        if (digitalRead(p9[0]) == LOW){
          salidasLCDj24p9(1); 
          //y = y + 1;                                         
        }
        break;
      case 1:
        if (digitalRead(p9[1]) == LOW){
          salidasLCDj24p9(2);   
          //y = y + 1;                                           
        }
        break; 
      case 4:
        if (digitalRead(p9[4]) == LOW){
          salidasLCDj24p9(5); 
          //y = y + 1; 
        }
        break;  
      case 5:
        if (digitalRead(p9[5]) == LOW){
          salidasLCDj24p9(6); 
          //y = y + 1;                                            
        }
        break; 
      case 6:
        if (digitalRead(p9[6]) == LOW){
          salidasLCDj24p9(7);   
          //y = y + 1;                                           
        }
        break;
      case 9:
        if (digitalRead(p9[9]) == LOW and i!=6){
          salidasLCDj24p9(10);   
          //y = y + 1;                                           
        }
        break;          
     }
   }
   for(int a = 0; a < 10; a++){
    digitalWrite(j24[a], LOW); 
   }
}



void misWirej24p9(int x){


  for(int i = 0; i < 10; i++){
    if(i==x){
      pinMode(j24[x], OUTPUT);
      digitalWrite(j24[x], HIGH);
    }
    else{
      digitalWrite(j24[i], LOW);
      pinMode(j24[i], INPUT);
    }
  }

  for(int j = 0; j < 10; j++){

    if(digitalRead(p9[j]) == HIGH and j==2 and j==x){
      salidaMiswirej24p9(x+1, j+1);
      y=y+1;
    }
    if(digitalRead(p9[j]) == HIGH and j==3 and j==x){
      salidaMiswirej24p9(x+1, j+1);
      y=y+1;
    }
    if(digitalRead(p9[j]) == HIGH and j==7 and j==x){
      salidaMiswirej24p9(x+1, j+1);
      y=y+1;
    }
    if(digitalRead(p9[j]) == HIGH and j==8 and j==x){
      salidaMiswirej24p9(x+1, j+1);
      y=y+1;
    }
    
    if(digitalRead(p9[j]) == HIGH and j!=x){
      k=j;

      
           if(x!=4 and x!=5 and k==4 or k==5){
              switch(k){
                case 4:
                  if(analogRead(p9[4]) > 995){
                    salidaMiswirej24p9(x+1, 5);
                  }
                  break;
                case 5:
                if(analogRead(p9[5]) > 995){
                  salidaMiswirej24p9(x+1, 6);
                }
                break;
              }
            }

            else if(x==4 and k==5 or x==5 and k==4){
              switch(x){
                case 4:
                  if(analogRead(p9[5]) > 995){
                    salidaMiswirej24p9(x+1, 6);
                  }
                  break;
                case 5:
                if(analogRead(p9[4]) > 995){
                  salidaMiswirej24p9(x+1, 5);
                }
                break;
              }
            }
            else{
              salidaMiswirej24p9(x+1, k+1);
            }
            
    }
    
  }

  
  
 
   
    
    for(int k = 0; k < 10; k++){
      pinMode(j24[k], OUTPUT);
      digitalWrite(j24[k], LOW);
    }
    misi = 0;
    misito = 0;
    k=0;
    x=0;
}


void mistoj24p9(){
  for(int i = o; i < 10; i++){
    pinMode(j24[i], OUTPUT);
    digitalWrite(j24[i], LOW);
    pinMode(j24[i], INPUT);
    }
        
    pinMode(j24[9], OUTPUT);
    digitalWrite(j24[9], HIGH);
    
    if(digitalRead(p9[6]) == HIGH or digitalRead(p9[9]) == HIGH){
      misi = misi + 1;
       }
    
    digitalWrite(j24[9], LOW);
    pinMode(j24[9], INPUT);
    pinMode(j24[6], OUTPUT);
    digitalWrite(j24[6], HIGH);
          
    if(digitalRead(p9[6]) == HIGH or digitalRead(p9[9]) == HIGH){
      misito = misito + 1;
       }
       
     digitalWrite(j24[6], LOW);
          
    if(misi == 1 and misito == 0){
      for(int i = 0; i < 10; i++){
        if(i!= 6 and i!=9){
          
          pinMode(j24[i], OUTPUT);
          digitalWrite(j24[i], HIGH);
         }
              
       
          if(digitalRead(p9[6]) == HIGH or digitalRead(p9[9]) == HIGH){
             Serial.print(F("MISWIRE J24 ")); Serial.print(i+1);
             Serial.println(F(" - 7 ")); 
             y=y+1;
             delay(125); 
          }
          
          digitalWrite(j24[i], LOW);
          digitalWrite(j24[i], INPUT);
        
        }
        
        misi = 0;
        misito = 0;
      }
          
      else if(misi == 0 and misito == 1){
        pinMode(j24[6], INPUT);
        for(int i = 0; i < 9; i++){
          if(i!= 6 and i!=9){
            pinMode(j24[i], OUTPUT);
            digitalWrite(j24[i], HIGH);
           }
              
           if(digitalRead(p9[6]) == HIGH or digitalRead(p9[7]) == HIGH){
             Serial.print(F("MISWIRE J24 ")); Serial.print(i+1);
             Serial.println(F(" - BS ")); 
             y=y+1;
             delay(125);
            }
            
           digitalWrite(j24[i], LOW);
           digitalWrite(j24[i], INPUT);
            
         }
         
         misi = 0;
         misito = 0;
       
       }

       else if(misi ==0 and misito == 0){
        for(int i = 0; i < 10; i++){
          if(i!= 6 and i!=9){
            pinMode(j24[i], OUTPUT);
            digitalWrite(j24[i], HIGH);
           }
              
          if(digitalRead(p9[6]) == HIGH or digitalRead(p9[9]) == HIGH){
             Serial.print(F("MISWIRE J24 ")); Serial.print(i+1);
             Serial.println(F(" CON P4: 7 Y BS ")); 
             y=y+1;
             delay(125);
           }
           
           digitalWrite(j24[i], LOW);
           pinMode(j24[i], INPUT);
        }
        
        
        
       }
       misi = 0;
       misito = 0;
       
       for(int k = 0; k < 10; k++){
        pinMode(j24[k], OUTPUT);
        digitalWrite(j24[k], LOW);
        }   
}



void aprobadoj24p9(){ //Función que dice si aprueba o no el esnamblaje
  for(int i = 0; i < 10; i++){
    digitalWrite(j24[i], LOW);
  }
  
  x=0;
  
  for(int j = 0; j < 10; j++){
    digitalWrite(j24[j],HIGH);
    if(digitalRead(p9[j] == HIGH)){
      if(y==0){
        if(j!= 2 and j!= 3 and j!= 7 and j!= 8){
          x = x + 1;
        }
       }
      digitalWrite(j24[j],LOW);
    }
   }
 
  if(x == 6){
    Serial.println(F("CONEXION J24 - P9 APROBADA :)"));
    delay(125);  
    Serial.println();
    ensamble = ensamble + 1;
    delay(125);
  }
  else{
    Serial.println(F("CONEXION J24 - P9 DEFECTUOSA :("));
    delay(125);  
    Serial.println();
    fallo = fallo + 1;  
    delay(125);  
  }
  x = 0;
  y = 0;
}


void salidasMinij24p9(int o){
  opj24p9[o-1] = opj24p9[o-1] + 2;
  if(o!=10){
    Serial.print(F("OPEN J24: POSICION ")); Serial.println(o);
  }
  else{
    Serial.println(F("OPEN J24 EN BS"));
  }
  y=y+1;
  delay(125);
}


void miniOj24p9(){
  mini = 0;
  for(int i = 0; i < 10; i++){
    digitalWrite(j24[i], LOW);
    pinMode(j24[i], INPUT);
 }
    mini = 0;
      p = 0;
 
  for(int k =0; k < 10; k++){
    pinMode(j24[k], OUTPUT);
    digitalWrite(j24[k], HIGH);
    for(int j = 0; j < 10; j++){
      if(digitalRead(p9[j]) == LOW){
        mini = mini + 1;
      }
    }
    
      switch(k){
        
      case 0:
        if(mini==10){
          salidasMinij24p9(1);
        }
        break;
      case 1:
        if(mini==10){
          salidasMinij24p9(2);
        }
        break;
      case 4:
        if(mini==10){
          salidasMinij24p9(5);
        }
        break;
      case 5:
        if(mini==10){ //p==5
          salidasMinij24p9(6);
        }
        break;
      case 6:
        if(mini==10){
          salidasMinij24p9(7);
        }
        break;
      case 9:
        if(mini==10){
          salidasMinij24p9(10);
        }
        break;
      }
       
      mini = 0;
      p = 0;
      digitalWrite(j24[k], LOW);
      pinMode(j24[k], INPUT);
  }
  for(int i = 0; i < 10; i++){
  pinMode(j24[i], OUTPUT);
 }

}


void resistenciaj24p9(){
  for(int k = 0; k < 10; k++){
    digitalWrite(j24[k], LOW);
    pinMode(j24[k], INPUT);
    
    pinMode(p9[k], INPUT);
  }

  pinMode(p9[4], OUTPUT);
  digitalWrite(p9[4], HIGH);
  
    if(analogRead(p9[5]) > 95 and analogRead(p9[5]) < 1024){
     q = q + 1;
    }

    /*lcd.clear();
    delay(750);
    lcd.print(analogRead(p9[5]));
    delay(750);*/

   digitalWrite(p9[4], LOW);
   pinMode(p9[4], INPUT);  
   pinMode(p9[5], OUTPUT);
   digitalWrite(p9[5], HIGH);

  
    if(analogRead(p9[4]) > 95 and analogRead(p9[4]) < 1024){
     q = q + 1;
     arr[12] = "DETECTED";
    }

    /*lcd.clear();
    delay(750);
    lcd.print(analogRead(p9[4]));
    delay(750);*/
    
    digitalWrite(p9[5], LOW);
    pinMode(p9[5], INPUT);
 


  if(q < 2){
    arr[12] = "NOT DETECTED";
    Serial.println(F("RESISTENCIA NO DETECTADA EN P9: 5 - 6"));
    y=y+1;
    delay(125);
    //arr[11] = "NOT DETECTED";
  }
  /*else if(q == 2){
    arr[11] = "DETECTED";
  }*/
  
  q=0;
  for(int k = 0; k < 10; k++){
    pinMode(j24[k], OUTPUT);
  }
      
}

/*Otro programaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
*/

void continuidadp9p4(){
  
  //nada = 0;
  for(int i = 0; i < 10; i++){
    digitalWrite(p9[i], HIGH);
  }
  for(int j = 0; j < 10; j++){
    if (digitalRead(p4[j]) == HIGH){
        nada = nada + 1;
      
    }
  }
  for(int a = 0; a < 10; a++){
        digitalWrite(p9[a], LOW);
      }
  

  /*lcd.clear();
  delay(500);
  lcd.setCursor(0,0);
  lcd.print(nada);
  delay(2000);*/

  
  if (nada == 0){
    Serial.println(F("NO HAY ENSAMBLE CONECTADO P9 - P4"));
    delay(125); //Tiempo de muestreo
    conectado = conectado + 1;
    fallo = fallo + 1;
  }
  else{
    openIndividualp9p4();
    miniOp9p4();
    llamarMiswirep9p4();
    mistop9p4();
    for(int k = 0; k < 6; k++){
    pinMode(j24[k], INPUT);
    pinMode(p9[k], OUTPUT);
  }
    resistenciaj24p9();
    for(int k = 0; k < 6; k++){
    pinMode(j24[k], INPUT);
    pinMode(p9[k], OUTPUT);
  }
    
    aprobadop9p4();
  }
  nada = 0;
}


void llamarMiswirep9p4(){
  for(int j = 0; j < 10; j++){
        misWirep9p4(j);
      }
}
void salidasLCDp9p4(int p){
  //delay(750);
  opp9p4[p-1] = opp9p4[p-1] + 1;
 
  if(p!=10){
    Serial.print(F("OPEN P4: POSICION ")); Serial.println(p);
  }
  else{
    Serial.println(F("OPEN P4 EN BS"));
  }
  y = y + 1;
  delay(125);
}

void salidaMiswirep9p4(int x, int z){
  
  if(z==5 or z==6 or z==3 or z==4 or z==9 or x==3 or x==4 or x==9){ //Dependiendo el GAP aquí es donde se cambia z==5 or z==6 or z ==3 or z==4 or z==8 or z==9
    misOp9p4[x-1] = 1;
    misIp9p4[z-1] = 1;
    
    Serial.print(F("CONEXION P9 "));
      
    if(x!=10){
      Serial.print(x);
    }
    else{
      Serial.print(bs);
    }
    
    Serial.print(F(" - P4 "));
    if(z!=10){
      Serial.print(z);
    }
    else{
      Serial.print(bs);
    }
    Serial.println(F(" NO DEBE CONECTARSE")); 
    y=y+1;
    delay(125);
  }
  else if(x == z){
    
  }
  else if(x==7 and z ==10){
    
  }
  else if(x==10 and z==7){  
  
  }
  else{
  misOp9p4[x-1] = 1;
  misIp9p4[z-1] = 1;  
  Serial.print("MISWIRE: ");
  
  if(x!=10){
    Serial.print(x);
  }
  else{
    Serial.print(bs);
  }
  
  Serial.print(F(" Y "));
  
  if(z!=10){
    Serial.print(z);
  }
  else{
    Serial.print(bs);
  }
  Serial.println(F(" P9 -- P4 :("));
  y=y+1;
  delay(125);
  }
}

void salidasp9p4(){
  for(int i = 0; i < 10; i++){
    digitalWrite(p9[i], LOW);
  }
}


void openIndividualp9p4(){
  for(int j =0; j < 10; j++){
    digitalWrite(p9[j], HIGH);
  }
  for(int i = 0; i < 10; i++){
    //contador = 0; 
    switch(i){
      case 0:
        //verifica = lecturaEntrada(0);
        if (digitalRead(p4[0]) == LOW){
          salidasLCDp9p4(1); 
          //y = y + 1;                
        }
        break;
      case 1:
        if (digitalRead(p4[1]) == LOW){
          salidasLCDp9p4(2);   
          //y = y + 1;                                           
        }
        break; 
      case 6:
        if (digitalRead(p4[6]) == LOW){
          salidasLCDp9p4(7);   
          //y = y + 1;                                           
        }
        break;
      case 7:
        if (digitalRead(p4[7]) == LOW){
          salidasLCD(8);   
          //y = y + 1;                                           
        }
        break;
      case 9:
        if (digitalRead(p4[9]) == LOW and i!=6){
          salidasLCDp9p4(10);   
          //y = y + 1;                                           
        }
        break;           
     }
   }
   for(int a = 0; a < 10; a++){
        digitalWrite(p9[a], LOW);
      }
}



void misWirep9p4(int x){


  for(int i = 0; i < 10; i++){
    if(i==x){
      pinMode(p9[x], OUTPUT);
      digitalWrite(p9[x], HIGH);
    }
    else{
      digitalWrite(p9[i], LOW);
      pinMode(p9[i], INPUT);
    }
  }

  for(int j = 0; j < 10; j++){

    if(digitalRead(p4[j]) == HIGH and j==2 and j==x){
      salidaMiswirep9p4(x+1, j+1);
      y=y+1;
    }
    if(digitalRead(p4[j]) == HIGH and j==3 and j==x){
      salidaMiswirep9p4(x+1, j+1);
      y=y+1;
    }
    if(digitalRead(p4[j]) == HIGH and j==4 and j==x){
      salidaMiswirep9p4(x+1, j+1);
      y=y+1;
    }
    if(digitalRead(p4[j]) == HIGH and j==5 and j==x){
      salidaMiswirep9p4(x+1, j+1);
      y=y+1;
    }
    /*if(digitalRead(p4[j]) == HIGH and j==7 and j==x){
      salidaMiswirep9p4(x+1, j+1);
      y=y+1;
    }*/
    if(digitalRead(p4[j]) == HIGH and j==8 and j==x){
      salidaMiswirep9p4(x+1, j+1);
      y=y+1;
    }
    
    if(digitalRead(p4[j]) == HIGH and j!=x){
      k=j;


 
          //if(k!=6 and k!=9){
            salidaMiswirep9p4(x+1, k+1);
            //y = y + 1;
        //digitalWrite(j24[x], LOW);
        //}
    }
    
   /* for(int k = 0; k < 6; k++){
      pinMode(j24[k], OUTPUT);
    }*/
    
  }

  
  
 
   
    
    for(int k = 0; k < 10; k++){
      pinMode(p9[k], OUTPUT);
      digitalWrite(p9[k], LOW);
    }
    misi = 0;
    misito = 0;
    k=0;
    x=0;
}

void mistop9p4(){
  for(int i = 0; i < 10; i++){
    pinMode(p9[i], OUTPUT);
    digitalWrite(p9[i], LOW);
    pinMode(p9[i], INPUT);
    }
        
    pinMode(p9[9], OUTPUT);
    digitalWrite(p9[9], HIGH);
    
    if(digitalRead(p4[6]) == HIGH or digitalRead(p4[9]) == HIGH){
      misi = misi + 1;
       }
    
    digitalWrite(p9[9], LOW);
    pinMode(p9[9], INPUT);
    pinMode(p9[6], OUTPUT);
    digitalWrite(p9[6], HIGH);
          
    if(digitalRead(p4[6]) == HIGH or digitalRead(p4[9]) == HIGH){
      misito = misito + 1;
       }
       
     digitalWrite(p9[6], LOW);
          
    if(misi == 1 and misito == 0){
      for(int i = 0; i < 10; i++){
        if(i!= 6 and i!=9){
          pinMode(p9[i], OUTPUT);
          digitalWrite(p9[i], HIGH);
         }
              
         if(digitalRead(p4[6]) == HIGH or digitalRead(p4[9]) == HIGH){ 
           Serial.print(F("MISWIRE P9 ")); Serial.print(i+1);
           Serial.println(F(" - 7"));
           y=y+1;
           delay(125);
         }
          
          digitalWrite(p9[i], LOW);
        
        }
        
        misi = 0;
        misito = 0;
      }
          
      else if(misi == 0 and misito == 1){
        pinMode(p9[6], INPUT);
        for(int i = 0; i < 10; i++){
          if(i!= 6 and i!=9){
            pinMode(p9[i], OUTPUT);
            digitalWrite(p9[i], HIGH);
           }
              
          if(digitalRead(p4[6]) == HIGH or digitalRead(p4[9]) == HIGH){ 
           Serial.print(F("MISWIRE P9 ")); Serial.print(i+1);
           Serial.println(F(" - BS"));
           y=y+1;
           delay(125);
          }
            
           digitalWrite(p9[i], LOW);
            
         }
         
         misi = 0;
         misito = 0;
       
       }

       else if(misi ==0 and misito == 0){
        for(int i = 0; i < 10; i++){
          if(i!= 6 and i!=9){
            pinMode(p9[i], OUTPUT);
            digitalWrite(p9[i], HIGH);
           }
              
          if(digitalRead(p4[6]) == HIGH or digitalRead(p4[9]) == HIGH){
           Serial.print(F("MISWIRE DE P9 ")); Serial.print(i+1);
           Serial.println(F(" CON P4: 7 Y BS"));
           y=y+1; 
           delay(125);  
          }
           
           digitalWrite(p9[i], LOW);
           pinMode(p9[i], INPUT);
        }
        
        
        
       }
       misi = 0;
       misito = 0;
       
       for(int k = 0; k < 10; k++){
        pinMode(p9[k], OUTPUT);
        digitalWrite(p9[k], LOW);
        }   
}




void aprobadop9p4(){
  for(int i = 0; i < 10; i++){
    digitalWrite(p9[i], LOW);
  }
  x=0;
    for(int j = 0; j < 10; j++){
      digitalWrite(p9[j],HIGH);
      if(digitalRead(p9[j] == HIGH)){
        if(y==0){
          if(j != 4 && j != 5 and j!=2 and j!=3 and j!=8){
          x = x + 1;
          }
          
        }
      digitalWrite(p9[j],LOW);
    }
   }
  
  if(x == 5){
    Serial.println(F("CONEXION P9 - P4 APROBADA :)"));
    delay(125);
    Serial.println();
    delay(125);
    ensamble = ensamble + 1;
  }
  else{
    Serial.println(F("CONEXION P9 - P4 DEFECTUOSA :("));
    delay(125);
    Serial.println();
    delay(125);
    fallo = fallo + 1;

  }
  x = 0;
  y = 0;
}



void salidasMinip9p4(int o){
  opp9p4[o-1] = opp9p4[o-1] + 2;
  
  if(o!=10){
    Serial.print(F("OPEN P9: POSICION ")); Serial.println(o);
  }
  else{
    Serial.println(F("OPEN P9 EN BS"));
  }
  y=y+1;
  delay(125);
}



void miniOp9p4(){
  mini = 0;
 for(int i = 0; i < 10; i++){
  digitalWrite(p9[i], LOW);
  pinMode(p9[i], INPUT);
 }
  for(int k =0; k < 10; k++){
    pinMode(p9[k], OUTPUT);
    digitalWrite(p9[k], HIGH);
   // pinMode(j24[1], INPUT);
    for(int j = 0; j < 10; j++){
      if(digitalRead(p4[j]) == LOW){
        mini = mini + 1;
      }
    }
    for(int j = 0; j < 10; j++){
      if(j!=k and digitalRead(p9[j]) == LOW and j!=4 and j!=5){
        p = p + 1;
      }
      else if(j==4 and analogRead(p9[j]) < 95){
        p=p+1;
      }
      else if(j==5 and analogRead(p9[j]) < 95){
        p=p+1;
      }
       
    }
    
      switch(k){
        
      case 0:
        if(mini==10 and p == 9){
          salidasMinip9p4(1);
        }
        break;
      case 1:
        if(mini==10 and p == 9){
          salidasMinip9p4(2);
        }
        break;
      case 6:
        if(mini==10){
          salidasMinip9p4(7);
        }
        break;
      case 7:
        if(mini==10 and p==9){
          salidasMinip9p4(7);
        }
        break;
      case 9:
        if(mini==10){
          salidasMinip9p4(10);
        }
        break;
      }
       
      mini = 0;
      p = 0;
      digitalWrite(p9[k], LOW);
      pinMode(p9[k], INPUT);
  }
  for(int i = 0; i < 10; i++){
  pinMode(p9[i], OUTPUT);
 }

}





/*Loooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
*/

void rasp(){
  //CONEXION #1 ------------------------------------------------------------------------------------------------------------------------
  if(op[0] == 0 and misO[0] == 0 and misI[0] == 0){
    arr[0] = "PASSED";
  }
  else if(op[0] > 0 and misO[0] == 0 and misI[0] == 0){
    arr[0] = "OPEN";
  }
  else if(op[0] == 0 and misO[0] == 1 or misI[0] == 1){
    arr[0] = "MISWIRE";
  }
  else if(op[0] > 0 and (misO[0] == 1 or misI[0] == 1)){
    arr[0] = "OPEN & MISWIRE";
  }

  //CONEXION #2 ------------------------------------------------------------------------------------------------------------------------
  if(opj24p9[0] == 0 and misOj24p9[0] == 0 and misIj24p9[0] == 0){
    arr[1] = "PASSED";
  }
  else if(opj24p9[0] > 0 and misOj24p9[0] == 0 and misIj24p9[0] == 0){
    arr[1] = "OPEN";
  }
  else if(opj24p9[0] == 0 and misOj24p9[0] == 1 or misIj24p9[0] == 1){
    arr[1] = "MISWIRE";
  }
  else if(opj24p9[0] > 0 and (misOj24p9[0] == 1 or misIj24p9[0] == 1)){
    arr[1] = "OPEN & MISWIRE";
  }

  //CONEXION #3 ------------------------------------------------------------------------------------------------------------------------
  if(op[1] == 0 and misO[1] == 0 and misI[1] == 0){
    arr[2] = "PASSED";
  }
  else if(op[1] > 0 and misO[1] == 0 and misI[1] == 0){
    arr[2] = "OPEN";
  }
  else if(op[1] == 0 and misO[1] == 1 or misI[1] == 1){
    arr[2] = "MISWIRE";
  }
  else if(op[1] > 0 and (misO[1] == 1 or misI[1] == 1)){
    arr[2] = "OPEN & MISWIRE";
  }

  //CONEXION #4 ------------------------------------------------------------------------------------------------------------------------
  if(opj24p9[1] == 0 and misOj24p9[1] == 0 and misIj24p9[1] == 0){
    arr[3] = "PASSED";
  }
  else if(opj24p9[1] > 0 and misOj24p9[1] == 0 and misIj24p9[1] == 0){
    arr[3] = "OPEN";
  }
  else if(opj24p9[1] == 0 and misOj24p9[1] == 1 or misIj24p9[1] == 1){
    arr[3] = "MISWIRE";
  }
  else if(opj24p9[1] > 0 and (misOj24p9[1] == 1 or misIj24p9[1] == 1)){
    arr[3] = "OPEN & MISWIRE";
  }

  //CONEXION #5 ------------------------------------------------------------------------------------------------------------------------
  for(int r = 0; r < 10; r++){
    pinMode(j24[r], INPUT);
    pinMode(p9[r], INPUT);
    pinMode(p4[r], INPUT);
  }
  pinMode(p4[6], OUTPUT);
  digitalWrite(p4[6], HIGH);

  for(int r = 0; r < 10; r++){
    if(r!=6){
      if(digitalRead(p4[r]) == HIGH and r==9){
    
      vs = vs + 100;
    }
    else if(digitalRead(p4[r]) == HIGH and r!=9){
      vs = vs + 1;
    }
  }
  }
  digitalWrite(p4[6], LOW);
  pinMode(p4[6], INPUT);
  
  for(int r = 0; r < 10; r++){
   if(r!= 9){
    pinMode(p4[r], OUTPUT);
    digitalWrite(p4[6], HIGH);
   }
    

    if(digitalRead(p4[9]) == HIGH and r!=6){
      vsM = vsM + 1;
    }
    digitalWrite(p4[r], LOW);
    pinMode(p4[r], INPUT);
  }
  if(vs == 100){
    arr[4] = "PASSED";
  }
  else if(vs == 0){
    arr[4] = "OPEN";
  }
  else if(vs != 0 and vs != 100){
    arr[4] = "MISWIRE";
  }
  else if(vs == 0 and vsM != 0){
    arr[4] = "OPEN & MISWIRE";
  }
  /*Serial.println();
  Serial.println(vs);
  Serial.println(vsM);*/
  vs = 0;
  vsM = 0;

  //CONEXION #6 ------------------------------------------------------------------------------------------------------------------------

  if(op[9] == 0 and misO[9] ==0 and misI[9] == 0 and misO[6] == 0 and misI[6] == 0){
    arr[5] = "PASSED";
  }
  else if(op[9] != 0 and misO[9] == 0 and misI[6] == 0 and misO[6] == 0 and misI[6] == 0){
    arr[5] = "OPEN";
  }
  else if(op[9] == 0 and misO[9] == 1 or misI[9] == 1 or misO[6] == 1 or misI[6] == 1){
    arr[5] = "MISWIRE";
  }
  else if(op[9] != 0 and (misO[9] == 1 or misI[9] == 1 or misO[6] == 1 or misI[6] == 1)){
    arr[5] = "OPEN & MISWIRE";
  }

  //CONEXION #7 ------------------------------------------------------------------------------------------------------------------------
  for(int r = 0; r < 10; r++){
    pinMode(j24[r], INPUT);
    pinMode(p9[r], INPUT);
    pinMode(p4[r], INPUT);
  }
  pinMode(j24[6], OUTPUT);
  digitalWrite(j24[6], HIGH);


      if(digitalRead(j24[9]) == HIGH){
    
      vs = vs + 100;
      }
    

  digitalWrite(j24[6], LOW);
  pinMode(j24[6], INPUT);
  
  if(vs == 100 and op[6]== 0 and op[9] == 0 and misI[6] == 0 and misO[6] ==0 and misI[9] == 0 and misO[9] == 0){
    arr[6] = "PASSED";
  }
  else if((op[6] != 0 or op[9] !=0) and misI[6] == 0 and misO[6] ==0 and misI[9] == 0 and misO[9] == 0){
    arr[6] = "OPEN";
  }
  else if(op[6] == 0 and op[9] ==0 and (misI[6] == 1 or misO[6] == 1 or misI[9] == 1 or misO[9] == 1)){
    arr[6] = "MISWIRE";
  }
  else if(op[6] != 0 or op[9] !=0 and (misI[6] == 1 or misO[6] == 1 or misI[9] == 1 or misO[9] == 1)){
    arr[6] = "OPEN & MISWIRE";
  }
  else{
    arr[6] = "REVISAR";
  }

  vs = 0;
  vsM = 0;
  
  //CONEXION #8 ------------------------------------------------------------------------------------------------------------------------

  if(opj24p9[9] == 0 and misOj24p9[9] ==0 and misIj24p9[9] == 0 and misOj24p9[6] == 0 and misIj24p9[6] == 0){
    arr[7] = "PASSED";
  }
  else if(opj24p9[9] != 0 and misOj24p9[9] == 0 and misIj24p9[9] == 0 and misOj24p9[6] == 0 and misIj24p9[6] == 0){
    arr[7] = "OPEN";
  }
  else if(opj24p9[9] == 0 and misOj24p9[9] == 1 or misIj24p9[9] == 1 or misOj24p9[6] == 1 or misIj24p9[6] == 1){
    arr[7] = "MISWIRE";
  }
  else if(opj24p9[9] != 0 and (misOj24p9[9] == 1 or misIj24p9[9] == 1 or misOj24p9[6] == 1 or misIj24p9[6] == 1)){
    arr[7] = "OPEN & MISWIRE";
  }

  //CONEXION #9 ------------------------------------------------------------------------------------------------------------------------
  for(int r = 0; r < 10; r++){
    pinMode(j24[r], INPUT);
    pinMode(p9[r], INPUT);
    pinMode(p4[r], INPUT);
  }
  pinMode(p9[6], OUTPUT);
  digitalWrite(p9[6], HIGH);

  for(int r = 0; r < 10; r++){
    if(r!=6){
      if(digitalRead(p9[r]) == HIGH and r==9){
    
      vs = vs + 100;
    }
    else if(digitalRead(p9[r]) == HIGH and r!=9){
      vs = vs + 1;
    }
  }
  }
  digitalWrite(p9[6], LOW);
  pinMode(p9[6], INPUT);
  
  for(int r = 0; r < 10; r++){
   if(r!= 9){
    pinMode(p9[r], OUTPUT);
    digitalWrite(p9[6], HIGH);
   }
    

    if(digitalRead(p9[9]) == HIGH and r!=6){
      vsM = vsM + 1;
    }
    digitalWrite(p9[r], LOW);
    pinMode(p9[r], INPUT);
  }
  if(vs == 100){
    arr[8] = "PASSED";
  }
  else if(vs == 0){
    arr[8] = "OPEN";
  }
  else if(vs != 0 and vs != 100){
    arr[8] = "MISWIRE";
  }
  else if(vs == 0 and vsM != 0){
    arr[8] = "OPEN & MISWIRE";
  }

  vs = 0;
  vsM = 0;

  //CONEXION #10 ------------------------------------------------------------------------------------------------------------------------*******************************
  if(opp9p4[7] == 0 and misOp9p4[7] == 0 and misIp9p4[7] == 0){
    arr[9] = "PASSED";
  }
  else if(opp9p4[7] > 0 and misOp9p4[7] == 0 and misIp9p4[7] == 0){
    arr[9] = "OPEN";
  }
  else if(opp9p4[7] == 0 and misOp9p4[7] == 1 or misIp9p4[7] == 1){
    arr[9] = "MISWIRE";
  }
  else if(opp9p4[7] > 0 and (misOp9p4[7] == 1 or misIp9p4[7] == 1)){
    arr[9] = "OPEN & MISWIRE";
  }

  //CONEXION #11 ------------------------------------------------------------------------------------------------------------------------
  if(opj24p9[4] == 0 and misOj24p9[4] == 0 and misIj24p9[4] == 0){
    arr[10] = "PASSED";
  }
  else if(opj24p9[4] > 0 and misOj24p9[4] == 0 and misIj24p9[4] == 0){
    arr[10] = "OPEN";
  }
  else if(opj24p9[4] == 0 and misOj24p9[4] == 1 or misIj24p9[4] == 1){
    arr[10] = "MISWIRE";
  }
  else if(opj24p9[4] > 0 and (misOj24p9[4] == 1 or misIj24p9[4] == 1)){
    arr[10] = "OPEN & MISWIRE";
  }

  //CONEXION #12 ------------------------------------------------------------------------------------------------------------------------
  if(opj24p9[5] == 0 and misOj24p9[5] == 0 and misIj24p9[5] == 0){
    arr[11] = "PASSED";
  }
  else if(opj24p9[5] > 0 and misOj24p9[5] == 0 and misIj24p9[5] == 0){
    arr[11] = "OPEN";
  }
  else if(opj24p9[5] == 0 and misOj24p9[5] == 1 or misIj24p9[5] == 1){
    arr[11] = "MISWIRE";
  }
  else if(opj24p9[5] > 0 and (misOj24p9[5] == 1 or misIj24p9[5] == 1)){
    arr[11] = "OPEN & MISWIRE";
  }

  //CONEXION #12 ------------------------------------------------------------------------------------------------------------------------
  //resistenciaj24p9()

  //SERIAL PRINT ------------------------------------------------------------------------------------------------------------------------
  while(w<13){
    Serial.println(sta2[w] + arr[w]);
    
    w = w + 1;
    delay(100);
  }
  w = 0;

  while(w<10){
    op[w] = 0;
    misO[w] = 0;
    misI[w] = 0;
    opj24p9[w] = 0;
    misOj24p9[w] = 0;
    misIj24p9[w] = 0;
    opp9p4[w] = 0;
    misOp9p4[w] = 0;
    misIp9p4[w] = 0;

    w = w + 1;
  }
  
  w = 0;



    
}
void loop() {
  buttonState = digitalRead(buttonPin);
  //Serial.println(buttonState);
    

  //buttonState = digitalRead(buttonPin);
  if (buttonState == LOW){
    while(coco < 1){
    //Serial.println("VUELVA A INTENTARLO");
    //delay(1000);
    //Serial.println("break");
    Serial.println(F("bai"));
    coco = coco + 1;
    }
    
    }
  else if (buttonState == HIGH){
  
    delay(1125); //1250
    coco = 0;

     for(int i = 0; i < 10; i++){
        pinMode(j24[i], OUTPUT);
        pinMode(p9[i], INPUT);
        pinMode(p4[i], INPUT);
        digitalWrite(j24[i], LOW);
      }
      continuidad();
     delay(50);
     variables();
      for(int i = 0; i < 10; i++){
        pinMode(j24[i], OUTPUT);
        pinMode(p9[i], INPUT);
        pinMode(p4[i], INPUT);
        digitalWrite(j24[i], LOW);
      }
      continuidadj24p9();
      delay(50);
      variables();
      for(int i = 0; i < 10; i++){
        pinMode(j24[i], INPUT);
        pinMode(p9[i], OUTPUT);
        pinMode(p4[i], INPUT);
        digitalWrite(p9[i], LOW);
      }
      continuidadp9p4();
      delay(50);
      variables();


      delay(125);
      Serial.println(F("break"));
      
      if(conectado == 3){
        digitalWrite(redLed, HIGH);
        delay(4000);
        digitalWrite(redLed, LOW);
      }
      
      delay(125);
      rasp();
      delay(125);
      Serial.println(ensamble);
      delay(250);
      //delay(50);
      
      if(ensamble == 3){
        digitalWrite(greenLed, HIGH);
        delay(4000);
        digitalWrite(greenLed, LOW);
      }
      else if(fallo >0 and conectado != 3 and ensamble!=3){ //if(ensamble >0 and ensamble!=3)
        digitalWrite(redLed, HIGH);
        digitalWrite(buz, HIGH);
        delay(4000);
        digitalWrite(redLed, LOW);
        digitalWrite(buz, LOW);
      }
      
      
      ensamble = 0;
      conectado = 0;
      fallo = 0;
      
  
  }
}
