int j24[] = {22, 24, 26, 28, 30, 32, 34, 36, 38, 40}; //Pines del Conector 3 (J24)
int p4[] = {11, 10, 9, 8, 7, 6, 5, 4, 3, 2}; // Pines del Conector 1 (P4)
int p9[] = {23, 25, 27, 29, A14, A15, 31, 33, 35, 37}; //Pines del COnector 2 (P9)
int buz = 47; //Pin donde se conecta el positivo del buzzer
int greenLed = 49; //Pin donde se conecta el positivo del Led verde
int redLed = 51; //Pin donde se conecta el positivo del Led rojo


//1141


int conexionesCorrectas = 0;//Variable que se utiliza para contar las conexiones correctas en las funciones Aprobado(), Aprobadoj24p9() errores Aprobadop9p4()
int errores = 0; //Variable que se utiliza para contar el # de errores detectados
int ensambleAprobado = 0; //Variable que se utiliza para verificar si un ensamble aprobó o no
int resultados = 0; //Variable que se utiliza para imprimir los resultados de las conexiones en un ciclo While
int noConectado = 0; //Variable que se utiliza para contar cuantas puntas no están conectadas
int fallo = 0; //Variable que se utiliza para contar cuantas puntas fallaron en sus conexiones 



int pines = 0; //Variable que indica si todos los pines de una punta son detectados o si no hay punta detectada
int misi = 0; //Variable que detecta si se lee un HIGH en las posiciones 7 y 10 al mandar la señal desde la posición 10
int misito = 0; //Variable que detecta si se lee un HIGH en las posiciones 7 y 10 al mandar la señal desde la posición 7
int openS = 0; //Variable que se utiliza para detectar si hay alguna pin open de la punta que manda la señal
int openR = 0; //Variable que se utiliza para detectar si hay alguna pin open de la punta que manda la señal cuando la punta posee una resistencia en sus conexiones
int resistenciaD = 0; //Variable que se utiliza para detectar si se encuentra la resistencia conectada
String bs = "BS"; //Variable que se utiliza para sustituir la posición 10 por BackShell



int op[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; //Array que si detecta un open coloca un "1" en la posición donde fue detectado. Conexión J24(Output) -- P4(Input)
int misO[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; //Array que si detecta un Miswire en la punta que se utilizó como salida coloca un "1" en la posición donde fue detectado. Conexión J24(Output) -- P4(Input)
int misI[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; //Array que si detecta un Miswire en la punta que se utilizó como entrada coloca un "1" en la posición donde fue detectado. Conexión J24(Output) -- P4(Input)

int opj24p9[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; //Array que si detecta un open coloca un "1" en la posición donde fue detectado. Conexión J24(Output) -- P9(Input)
int misOj24p9[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; //Array que si detecta un Miswire en la punta que se utilizó como salida coloca un "1" en la posición donde fue detectado. Conexión J24(Output) -- P9(Input)
int misIj24p9[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; //Array que si detecta un Miswire en la punta que se utilizó como entrada coloca un "1" en la posición donde fue detectado. Conexión J24(Output) -- P9(Input)

int opp9p4[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; //Array que si detecta un open coloca un "1" en la posición donde fue detectado. Conexión P9(Output) -- P4(Input)
int misOp9p4[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; //Array que si detecta un Miswire en la punta que se utilizó como salida coloca un "1" en la posición donde fue detectado. Conexión P9(Output) -- P4(Input)
int misIp9p4[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; //Array que si detecta un Miswire en la punta que se utilizó como entrada coloca un "1" en la posición donde fue detectado. Conexión P9(Output) -- P4(Input)

String arr[] = {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "}; //Array donde se coloca el estado de la conexión. Si pasó o cual fue la falla de la conexión probada

String sta2[] = {"1,WIRE,P4-001,J24-001,", "2,WIRE,J24-001,P9-001,", "3,WIRE,P4-002,J24-002,", "4,WIRE,J24-002,P9-002,", "5,WIRE,P4-007,P4-BS,", "6,WIRE,P4-BS,J24-007,", 
"7,WIRE,J24-007,J24-BS,", "8,WIRE,J24-BS,P9-007,", "9,WIRE,P9-007,P9-BS,", "10,WIRE,P4-008,P9-008,", "11,WIRE,J24-005,P9-005,", 
"12,WIRE,J24-006,P9-006,", "13,RESISTOR,P9-005,P9-006,"}; //Array que indica las conexiones a probar el cual será mandado al raspberry junto con el Arrya "arr"

String sta3[] = {"1,WIRE,P15-001,J15-001,", "2,WIRE,P15-002,J15-002,", "3,WIRE,P15-007,P15-BS,", 
"4,WIRE,P15-BS,J15-007,", "5,WIRE,J15-007,J15-BS,"}; //Array que indica las conexiones a probar el cual será mandado al raspberry junto con el Arrya "arr"

int vs = 0; //Variable que indica si la conexión de la posición 7 con BS es correcta o si existe algún error indica cual es
int vsM = 0; //Variable que indica si la conexión de la posición 10 con 7 es correcta o si existe algún error indica cual es



void setup() {

  Serial.begin(19200); //Baud rate
    
  for(int i = 0; i < 10; i++){ //Se declaran los pines de entrada y salida de los conectores 
    pinMode(p4[i], INPUT); //Conector 1
    pinMode(p9[i], INPUT); //Conector 2
    pinMode(j24[i], OUTPUT); //Conector 3
  }


  pinMode(greenLed, OUTPUT); //Se declara el pin del LED verde como salida
  pinMode(redLed, OUTPUT); //Se declara el pin del LED rojo como salida
  pinMode(buz, OUTPUT); //Se declara el pin del buzzer como salida
  


}

void variables(){ //Función que resetea el valor de las variables utilizadas
  pines = 0; 
  misi = 0;
  misito = 0 ;
  openS = 0;
  openR = 0;
  resistenciaD = 0;
}

void continuidad(){ //Función que detecta si existe la conexión de las puntas J24 -- P4
  
  for(int i = 0; i < 10; i++){
    digitalWrite(j24[i], HIGH);
  }
  
  for(int j = 0; j < 10; j++){
    if (digitalRead(p4[j]) == HIGH){
        pines = pines + 1;
    }
  }
  
  for(int a = 0; a < 10; a++){
        digitalWrite(j24[a], LOW);
  }
      
  
  if (pines == 0){
    Serial.println(F("NO HAY ENSAMBLE CONECTADO J24-P4"));
    Serial.println();
    delay(750);
    noConectado = noConectado + 1;
    fallo = fallo + 1;
  }
  
  else{
    openEntrada();
    openSalida();
    llamarMiswire();
    misBS();
    aprobado();
  }
  pines = 0;
}



void llamarMiswire(){ //Función que manda posición por posición y detecta si existe algún Miswire a través de la función "misWire"
  for(int j = 0; j < 10; j++){
        misWire(j);
      }
}

void salidasOpenEntrada(int p){ //Función que imprime los open detectados del Conector 1 (P4) en J24--P4
  op[p-1] = op[p-1] + 1;
  
  if(p!=10){
    Serial.print(F("OPEN P4 EN POSICION ")); Serial.println(p);
  }
  else{
    Serial.println(F("OPEN P4 EN BS"));
  }
  errores = errores + 1;
  delay(125);
}

void salidaMiswire(int x, int z){ //Función que imprime los miswire detectados de la conexión J24 -- P4. "X" corresponde a J24(Conector 3) y "Z" a P4(Conector 1)
  
  
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
    errores = errores + 1;
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
  errores = errores + 1;
  delay(125);
  }
}


void openEntrada(){ //Función que detecta los open del Conector 1 (P4) en la conexión J24--P4
  
  for(int j =0; j < 10; j++){
    digitalWrite(j24[j], HIGH);
  }
  for(int i = 0; i < 10; i++){
    
    switch(i){
      
      case 0:
        if (digitalRead(p4[0]) == LOW){
          salidasOpenEntrada(1);                                        
        }
        break;
      case 1:
        if (digitalRead(p4[1]) == LOW){
          salidasOpenEntrada(2);                                        
        }
        break; 
      case 6:
        if (digitalRead(p4[6]) == LOW){
          salidasOpenEntrada(7);                                          
        }
        break;
      case 9:
        if (digitalRead(p4[9]) == LOW and i!=6){
          salidasOpenEntrada(10);                                        
        }
        break;           
     }
   }
   
   for(int a = 0; a < 10; a++){
        digitalWrite(j24[a], LOW);
      }
}



void misWire(int x){ //Función que detecta los miswire en la conexión J24--P4. "X" es la posición en J24


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
      errores=errores+1;
    }
    if(digitalRead(p4[j]) == HIGH and j==3 and j==x){
      salidaMiswire(x+1, j+1);
      errores=errores+1;
    }
    if(digitalRead(p4[j]) == HIGH and j==4 and j==x){
      salidaMiswire(x+1, j+1);
      errores=errores+1;
    }
    if(digitalRead(p4[j]) == HIGH and j==5 and j==x){
      salidaMiswire(x+1, j+1);
      errores=errores+1;
    }
    if(digitalRead(p4[j]) == HIGH and j==7 and j==x){
      salidaMiswire(x+1, j+1);
      errores=errores+1;
    }
    if(digitalRead(p4[j]) == HIGH and j==8 and j==x){
      salidaMiswire(x+1, j+1);
      errores=errores+1;
    }
    
    if(digitalRead(p4[j]) == HIGH and j!=x){
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
            salidaMiswire(x+1, j+1);        
    }
  }
    
    for(int k = 0; k < 10; k++){
      pinMode(j24[k], OUTPUT);
      digitalWrite(j24[k], LOW);
    }
}

void misBS(){ //Función que detecta los posibles miswire de las posiciones 7 y BS que no fueron detectados anteriormente
  
  for(int i = 0; i < 10; i++){
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
        errores=errores+1; 
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
        errores=errores+1;
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
        Serial.println(F(" CON P4: 7 Y BS"));
        errores=errores+1;
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




void aprobado(){ //Función que evalua si la conexión J24--P4 pasó o no pasó
  
  for(int i = 0; i < 10; i++){
    digitalWrite(j24[i], LOW);
  }
  
  conexionesCorrectas=0;
  
  for(int j = 0; j < 10; j++){
    digitalWrite(j24[j],HIGH);
    if(digitalRead(p4[j] == HIGH)){
      if(errores==0){
        if(j != 4 && j != 5 and j!=2 and j!=3 and j!=7 and j!=8){
          conexionesCorrectas = conexionesCorrectas + 1;
        } 
       }
    digitalWrite(j24[j],LOW);
    }
  }
  
  if(conexionesCorrectas == 4){
    Serial.println(F("CONEXION J24-P4 APROBADA :)"));
    delay(125);  
    Serial.println();
    ensambleAprobado = ensambleAprobado + 1;
    delay(125);
  }
  else{     
    Serial.println(F("CONEXION J24-P4 DEFECTUOSA :("));
    delay(125);  
    Serial.println();
    delay(125);
    fallo = fallo + 1;
  }
  conexionesCorrectas = 0;
  errores = 0;
}



void salidasMini(int o){ //Función que imprime los open detectados del Conector 3 (J24) en J24--P4
  op[o-1] = op[o-1] + 2;
  if(o!=10){
    Serial.print(F("OPEN J24 POSICION ")); Serial.println(o);
  }
  else{
    Serial.println(F("OPEN J24 EN BS"));
  }
  errores=errores+1;
  delay(125);
}



void openSalida(){ //Función que detecta los open del Conector 3 (J24) en la conexión J24--P4
  openS = 0;
 for(int i = 0; i < 10; i++){
  digitalWrite(j24[i], LOW);
  pinMode(j24[i], INPUT);
 }
 openS = 0;

  for(int k =0; k < 10; k++){
    pinMode(j24[k], OUTPUT);
    digitalWrite(j24[k], HIGH);
   // pinMode(j24[1], INPUT);
    for(int j = 0; j < 10; j++){
      if(digitalRead(p4[j]) == LOW){
        openS = openS + 1;
      }
    }
    
      if(openS == 10){
        switch(k){
      
        
        case 0:
            salidasMini(1);
          break;
        case 1:
            salidasMini(2);
          break;
        case 6:
            salidasMini(7);
          break;
        case 9:
            salidasMini(10);
          break;
        }
      }
       
      openS = 0;
      digitalWrite(j24[k], LOW);
      pinMode(j24[k], INPUT);
  }
  for(int i = 0; i < 10; i++){
  pinMode(j24[i], OUTPUT);
 }

}


//

/**
 * 
 * 
 * 
 * 
 * BLOQUE DE CÓDIGO PARA CONEXIÓN J24--P9 (CONECTOR 3 Y CONECTOR 2)
 * 
 * 
 * 
 * 
 */


void continuidadj24p9(int puntas){ //Función que detecta si existe la conexión de las puntas J24 -- P9
  
  for(int i = 0; i < 10; i++){ // Se ponen en HIGH todas los pines de salida (J24)
    digitalWrite(j24[i], HIGH);
  }
  for(int j = 0; j < 10; j++){  // Se leen las entradas (P9)
    if (digitalRead(p9[j]) == HIGH){
          pines = pines + 1;
        
    }
  }
  for(int a = 0; a < 10; a++){ // Se ponen en LOW todas los pines de salida (J24)
    digitalWrite(j24[a], LOW);
  }
  
  
  if (pines == 0){ // Si no se detecta HIGH en los pines de entrada entonces no hay ensamble J24--P9 conectado
    if (puntas == 3){
      Serial.println(F("NO HAY ENSAMBLE CONECTADO J24-P9"));
    }
    else if (puntas == 2){
      Serial.println(F("NO HAY ENSAMBLE CONECTADO J15-P15"));
    }
    Serial.println(); //Espacio al imprimir para no confundir 
    delay(125); //Tiempo de espera
    noConectado = noConectado + 1; //Para saber cuantos no están noConectados
    fallo = fallo + 1; //Fallos
  }
  else{ //Si se detecta por lo menos 1 pin entonces se llaman a las siguientes funciones 
    openEntradaj24p9(puntas); //Función que detecta los open del Conector 2 (P9) en la conexión J24--P9
    
    openSalidaj24p9(puntas); //Función que detecta los open del Conector 3 (J24) en la conexión J24--P9
    
    llamarMiswirej24p9(puntas); //Función que manda posición por posición y detecta si existe algún Miswire a través de la función "misWirej24p9"
    
    misBSj24p9(puntas); //Función que detecta los posibles miswire de las posiciones 7 y BS que no fueron detectados anteriormente
    
    if (puntas == 3){
      resistenciaj24p9(); // Función para detectar la resistencia entre 5--6 de P9
    }
    
    aprobadoj24p9(puntas); //Función que evalua si la conexión J24--P9 pasó o no pasó
  }
  pines = 0; // Se reinicia el contador para detectar pines
}


void llamarMiswirej24p9(int puntas){ // Llama a una salida para compararla con las entrada y ver si se conectó donde no corresponde
  for(int j = 0; j < 10; j++){
        misWirej24p9(j, puntas);
      }
}

void salidasOpenEntradaj24p9(int p, int puntas){ // Si hay un open en P9 esta función es llamada para imprimirlo
  opj24p9[p-1] = opj24p9[p-1] + 1;
  
  if(p!=10 and puntas == 3){
    Serial.print(F("OPEN P9 POSICION ")); Serial.println(p);
  }
  
  else if (p==10 and puntas == 3){
    Serial.println(F("OPEN P9 EN BS"));
  }
  else if(p!=10 and puntas == 2){
    Serial.print(F("OPEN P15 POSICION ")); Serial.println(p);
  }
  
  else if (p==10 and puntas == 2){
    Serial.println(F("OPEN P15 EN BS"));
  }
  errores = errores + 1;
  delay(125);
}

void salidaMiswirej24p9(int x, int z, int puntas){ // Si un miswire es detectado esta función es llamada para imprimirlo
  
  if(z==3 or z==4 or z==8 or z==9 or x==3 or x==4 or x==8 or x==9){  
    misOj24p9[x-1] = 1;
    misIj24p9[z-1] = 1;
    if (puntas==3){
      Serial.print(F("CONEXION J24 "));
    }
    else if (puntas==2){
      Serial.print(F("CONEXION J15 "));
    }
    
    if(x!=10){
      Serial.print(x);
    }
    else{
      Serial.print(bs);
    }
    
    if(puntas ==3){
      Serial.print(F(" - P9 "));
    }
    else if(puntas==2){
      Serial.print(F(" - P15 "));
    }
    
    if(z!=10){
      Serial.print(z);
    }
    else{
      Serial.print(bs);
    }
    Serial.println(F(" NO DEBE CONECTARSE"));
    errores = errores + 1;
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
  if(puntas==3){
    Serial.println(F(" J24 - P9 :(!"));
  }
  else if(puntas==2){
    Serial.println(F(" J15 - P15 :(!"));
  }
  errores=errores+1;
  delay(125);
  }
}


void openEntradaj24p9(int puntas){ // Función que detecta si hay alguna posición open de P9
  
  for(int j =0; j < 10; j++){ // Todas las salidas se ponen en HIGH
    digitalWrite(j24[j], HIGH);
  }
  
  for(int i = 0; i < 10; i++){
    switch(i){
      case 0:
        if (digitalRead(p9[0]) == LOW){
          salidasOpenEntradaj24p9(1, puntas);                                          
        }
        break;
      case 1:
        if (digitalRead(p9[1]) == LOW){
          salidasOpenEntradaj24p9(2, puntas);                                         
        }
        break; 
      case 4:
        if (digitalRead(p9[4]) == LOW){
          salidasOpenEntradaj24p9(5, puntas); 
        }
        break;  
      case 5:
        if (digitalRead(p9[5]) == LOW){
          salidasOpenEntradaj24p9(6, puntas);                                           
        }
        break; 
      case 6:
        if (digitalRead(p9[6]) == LOW){
          salidasOpenEntradaj24p9(7, puntas);                                           
        }
        break;
      case 9:
        if (digitalRead(p9[9]) == LOW and i!=6){
          salidasOpenEntradaj24p9(10, puntas);                                             
        }
        break;          
     }
   }
   for(int a = 0; a < 10; a++){
    digitalWrite(j24[a], LOW); 
   }
}



void misWirej24p9(int x, int puntas){


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
      salidaMiswirej24p9(x+1, j+1, puntas);
      errores=errores+1;
    }
    if(digitalRead(p9[j]) == HIGH and j==3 and j==x){
      salidaMiswirej24p9(x+1, j+1, puntas);
      errores=errores+1;
    }
    if(digitalRead(p9[j]) == HIGH and j==7 and j==x){
      salidaMiswirej24p9(x+1, j+1, puntas);
      errores=errores+1;
    }
    if(digitalRead(p9[j]) == HIGH and j==8 and j==x){
      salidaMiswirej24p9(x+1, j+1, puntas);
      errores=errores+1;
    }
    
    if(digitalRead(p9[j]) == HIGH and j!=x){
      
           if(x!=4 and x!=5 and j==4 or j==5){
              switch(j){
                case 4:
                  if(analogRead(p9[4]) > 995){
                    salidaMiswirej24p9(x+1, 5, puntas);
                  }
                  break;
                case 5:
                if(analogRead(p9[5]) > 995){
                  salidaMiswirej24p9(x+1, 6, puntas);
                }
                break;
              }
            }

            else if(x==4 and j==5 or x==5 and j==4){
              switch(x){
                case 4:
                  if(analogRead(p9[5]) > 995){
                    salidaMiswirej24p9(x+1, 6, puntas);
                  }
                  break;
                case 5:
                if(analogRead(p9[4]) > 995){
                  salidaMiswirej24p9(x+1, 5, puntas);
                }
                break;
              }
            }
            else{
              salidaMiswirej24p9(x+1, j+1, puntas);
            }
            
    }
    
  }

  
  
 
   
    
    for(int k = 0; k < 10; k++){
      pinMode(j24[k], OUTPUT);
      digitalWrite(j24[k], LOW);
    }
}


void misBSj24p9(int puntas){
  for(int i = 0; i < 10; i++){
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
             if(puntas==3){
              Serial.print(F("MISWIRE J24 ")); Serial.print(i+1);
             }
             else if(puntas==2){
              Serial.print(F("MISWIRE J15 ")); Serial.print(i+1);
             }
             Serial.println(F(" - 7 ")); 
             errores=errores+1;
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
             if(puntas==3){
              Serial.print(F("MISWIRE J24 ")); Serial.print(i+1);
             }
             else if(puntas==2){
              Serial.print(F("MISWIRE J15 ")); Serial.print(i+1);
             }
             Serial.println(F(" - BS ")); 
             errores=errores+1;
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
             if(puntas==3){
              Serial.print(F("MISWIRE J24 ")); Serial.print(i+1);
              Serial.println(F(" CON P4: 7 errores BS ")); 
             }
             else if(puntas==2){
              Serial.print(F("MISWIRE J15 ")); Serial.print(i+1);
              Serial.println(F(" CON P15: 7 errores BS ")); 
             }
             errores=errores+1;
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



void aprobadoj24p9(int puntas){ //Función que dice si aprueba o no el esnamblaje
  for(int i = 0; i < 10; i++){
    digitalWrite(j24[i], LOW);
  }
  
  conexionesCorrectas=0;
  
  for(int j = 0; j < 10; j++){
    digitalWrite(j24[j],HIGH);
    if(digitalRead(p9[j] == HIGH)){
      if(errores==0){
        if(j!= 2 and j!= 3 and j!= 7 and j!= 8){
          conexionesCorrectas = conexionesCorrectas + 1;
        }
       }
      digitalWrite(j24[j],LOW);
    }
   }
 
  if(conexionesCorrectas == 6){
    if(puntas==3){
      Serial.println(F("CONEXION J24 - P9 APROBADA :)"));
    }
    else if(puntas==2){
      Serial.println(F("CONEXION J15 - P15 APROBADA :)"));
    }
    delay(125);  
    Serial.println();
    ensambleAprobado = ensambleAprobado + 1;
    delay(125);
  }
  else{
    if(puntas==3){
      Serial.println(F("CONEXION J24 - P9 DEFECTUOSA :("));
    }
    else if(puntas==2){
      Serial.println(F("CONEXION J15 - P15 DEFECTUOSA :("));
    }
    delay(125);  
    Serial.println();
    fallo = fallo + 1;  
    delay(125);  
  }
  conexionesCorrectas = 0;
  errores = 0;
}


void salidasMinij24p9(int o, int puntas){
  opj24p9[o-1] = opj24p9[o-1] + 2;
  if(o!=10){
    if(puntas==3){
      Serial.print(F("OPEN J24: POSICION ")); Serial.println(o);
    }
    else if(puntas==2){
      Serial.print(F("OPEN J15: POSICION ")); Serial.println(o);
    }
  }
  else{
    if(puntas==3){
      Serial.println(F("OPEN J24 EN BS"));
    }
    else if(puntas==2){
      Serial.println(F("OPEN J15 EN BS"));
    }
  }
  errores=errores+1;
  delay(125);
}


void openSalidaj24p9(int puntas){
  openS = 0;
  for(int i = 0; i < 10; i++){
    digitalWrite(j24[i], LOW);
    pinMode(j24[i], INPUT);
 }
    openS = 0;
 
  for(int k =0; k < 10; k++){
    pinMode(j24[k], OUTPUT);
    digitalWrite(j24[k], HIGH);
    for(int j = 0; j < 10; j++){
      if(digitalRead(p9[j]) == LOW){
        openS = openS + 1;
      }
    }
    
      if(openS == 10){
        switch(k){
      
        
        case 0:
            salidasMinij24p9(1, puntas);
          break;
        case 1:
            salidasMinij24p9(2, puntas);
          break;
        case 4:
            salidasMinij24p9(5, puntas);
          break;
        case 5:
            salidasMinij24p9(6, puntas);
          break;
        case 6:
            salidasMinij24p9(7, puntas);
          break;
        case 9:
            salidasMinij24p9(10, puntas);
          break;
        }
      }
       
      openS = 0;
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
     resistenciaD = resistenciaD + 1;
    }


   digitalWrite(p9[4], LOW);
   pinMode(p9[4], INPUT);  
   pinMode(p9[5], OUTPUT);
   digitalWrite(p9[5], HIGH);

  
    if(analogRead(p9[4]) > 95 and analogRead(p9[4]) < 1024){
     resistenciaD = resistenciaD + 1;
     arr[12] = "DETECTED";
    }
    
    digitalWrite(p9[5], LOW);
    pinMode(p9[5], INPUT);
 


  if(resistenciaD < 2){
    arr[12] = "NOT DETECTED";
    Serial.println(F("RESISTENCIA NO DETECTADA EN P9: 5 - 6"));
    errores=errores+1;
    delay(125);
  }
  
  resistenciaD=0;
  for(int k = 0; k < 10; k++){
    pinMode(j24[k], OUTPUT);
  }
      
}

/**
 * 
 * 
 * 
 * 
 * BLOQUE DE CÓDIGO PARA CONEXIÓN P9--P4 (CONECTOR 2 Y CONECTOR 1)
 * 
 * 
 * 
 * 
 */

void continuidadp9p4(){ //Función que detecta si existe la conexión de las puntas P9 -- P4
  
  //pines = 0;
  for(int i = 0; i < 10; i++){
    digitalWrite(p9[i], HIGH);
  }
  for(int j = 0; j < 10; j++){
    if (digitalRead(p4[j]) == HIGH){
        pines = pines + 1;
      
    }
  }
  for(int a = 0; a < 10; a++){
        digitalWrite(p9[a], LOW);
      }


  
  if (pines == 0){
    Serial.println(F("NO HAY ENSAMBLE CONECTADO P9 - P4"));
    Serial.println();
    delay(125); //Tiempo de muestreo
    noConectado = noConectado + 1;
    fallo = fallo + 1;
  }
  else{
    openEntradap9p4();
    openSalidap9p4();
    llamarMiswirep9p4();
    misBSp9p4();
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
  pines = 0;
}


void llamarMiswirep9p4(){ //Función que manda posición por posición y detecta si existe algún Miswire a través de la función "misWire"
  for(int j = 0; j < 10; j++){
        misWirep9p4(j);
      }
}
void salidasOpenEntradap9p4(int p){ //Función que imprime los open detectados del Conector 1 (P4) en P9--P4
  //delay(750);
  opp9p4[p-1] = opp9p4[p-1] + 1;
 
  if(p!=10){
    Serial.print(F("OPEN P4: POSICION ")); Serial.println(p);
  }
  else{
    Serial.println(F("OPEN P4 EN BS"));
  }
  errores = errores + 1;
  delay(125);
}

void salidaMiswirep9p4(int x, int z){ //Función que imprime los miswire detectados de la conexión P9 -- P4. "X" corresponde a P9(Conector 2) y "Z" a P4(Conector 1)
  
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
    errores=errores+1;
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
  errores=errores+1;
  delay(125);
  }
}


void openEntradap9p4(){ //Función que detecta los open del Conector 1 (P4) en la conexión P9--P4
  for(int j =0; j < 10; j++){
    digitalWrite(p9[j], HIGH);
  }
  for(int i = 0; i < 10; i++){
    //contador = 0; 
    switch(i){
      case 0:
        //verifica = lecturaEntrada(0);
        if (digitalRead(p4[0]) == LOW){
          salidasOpenEntradap9p4(1); 
          //errores = errores + 1;                
        }
        break;
      case 1:
        if (digitalRead(p4[1]) == LOW){
          salidasOpenEntradap9p4(2);   
          //errores = errores + 1;                                           
        }
        break; 
      case 6:
        if (digitalRead(p4[6]) == LOW){
          salidasOpenEntradap9p4(7);   
          //errores = errores + 1;                                           
        }
        break;
      case 7:
        if (digitalRead(p4[7]) == LOW){
          salidasOpenEntrada(8);   
          //errores = errores + 1;                                           
        }
        break;
      case 9:
        if (digitalRead(p4[9]) == LOW and i!=6){
          salidasOpenEntradap9p4(10);   
          //errores = errores + 1;                                           
        }
        break;           
     }
   }
   for(int a = 0; a < 10; a++){
        digitalWrite(p9[a], LOW);
      }
}



void misWirep9p4(int x){ //Función que detecta los miswire en la conexión P9--P4. "X" es la posición en P9


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
      errores=errores+1;
    }
    if(digitalRead(p4[j]) == HIGH and j==3 and j==x){
      salidaMiswirep9p4(x+1, j+1);
      errores=errores+1;
    }
    if(digitalRead(p4[j]) == HIGH and j==4 and j==x){
      salidaMiswirep9p4(x+1, j+1);
      errores=errores+1;
    }
    if(digitalRead(p4[j]) == HIGH and j==5 and j==x){
      salidaMiswirep9p4(x+1, j+1);
      errores=errores+1;
    }

    if(digitalRead(p4[j]) == HIGH and j==8 and j==x){
      salidaMiswirep9p4(x+1, j+1);
      errores=errores+1;
    }
    
    if(digitalRead(p4[j]) == HIGH and j!=x){
        salidaMiswirep9p4(x+1, j+1);
    }
    
   
  }

    
    for(int k = 0; k < 10; k++){
      pinMode(p9[k], OUTPUT);
      digitalWrite(p9[k], LOW);
    }
}

void misBSp9p4(){ //Función que detecta los posibles miswire de las posiciones 7 y BS que no fueron detectados anteriormente
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
           errores=errores+1;
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
           errores=errores+1;
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
           errores=errores+1; 
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




void aprobadop9p4(){ //Función que evalua si la conexión P9--P4 pasó o no pasó
  for(int i = 0; i < 10; i++){
    digitalWrite(p9[i], LOW);
  }
  conexionesCorrectas=0;
    for(int j = 0; j < 10; j++){
      digitalWrite(p9[j],HIGH);
      if(digitalRead(p9[j] == HIGH)){
        if(errores==0){
          if(j != 4 && j != 5 and j!=2 and j!=3 and j!=8){
          conexionesCorrectas = conexionesCorrectas + 1;
          }
          
        }
      digitalWrite(p9[j],LOW);
    }
   }
  
  if(conexionesCorrectas == 5){
    Serial.println(F("CONEXION P9 - P4 APROBADA :)"));
    delay(125);
    Serial.println();
    delay(125);
    ensambleAprobado = ensambleAprobado + 1;
  }
  else{
    Serial.println(F("CONEXION P9 - P4 DEFECTUOSA :("));
    delay(125);
    Serial.println();
    delay(125);
    fallo = fallo + 1;

  }
  conexionesCorrectas = 0;
  errores = 0;
}



void salidasMinip9p4(int o){ //Función que imprime los open detectados del Conector 2 (P9) en P9--P4
  opp9p4[o-1] = opp9p4[o-1] + 2;
  
  if(o!=10){
    Serial.print(F("OPEN P9: POSICION ")); Serial.println(o);
  }
  else{
    Serial.println(F("OPEN P9 EN BS"));
  }
  errores=errores+1;
  delay(125);
}



void openSalidap9p4(){ //Función que detecta los open del Conector 2 (P9) en la conexión P9--P4
  openS = 0;
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
        openS = openS + 1;
      }
    }
    openR=0; //*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-**-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
    for(int j = 0; j < 10; j++){
      if(j!=k and digitalRead(p9[j]) == LOW and j!=4 and j!=5){
        openR = openR + 1;
      }
      else if(j==4 and analogRead(p9[j]) < 95){
        openR = openR + 1;
      }
      else if(j==5 and analogRead(p9[j]) < 95){
        openR = openR + 1;
      }
       
    }
    
      switch(k){
        
      case 0:
        if(openS==10 and openR == 9){
          salidasMinip9p4(1);
        }
        break;
      case 1:
        if(openS==10 and openR == 9){
          salidasMinip9p4(2);
        }
        break;
      case 6:
        if(openS==10){
          salidasMinip9p4(7);
        }
        break;
      case 7:
        if(openS==10 and openR==9){
          salidasMinip9p4(7);
        }
        break;
      case 9:
        if(openS==10){
          salidasMinip9p4(10);
        }
        break;
      }
       
      openS = 0;
      openR = 0;
      digitalWrite(p9[k], LOW);
      pinMode(p9[k], INPUT);
  }
  for(int i = 0; i < 10; i++){
  pinMode(p9[i], OUTPUT);
 }

}





/**
 * 
 * 
 * 
 * 
 * BLOQUE DE CÓDIGO PARA DETERMINAR EL ESTADO DE LAS CONEXIONES A ANALIZAR.CONEXIONES DEFINIDAS EN "sta2[]"
 * 
 * 
 * 
 * 
 */

void rasp3(){
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
  while(resultados<13){
    Serial.println(sta2[resultados] + arr[resultados]);
    
    resultados = resultados + 1;
    delay(100);
  }
  resultados = 0;

  while(resultados<10){
    op[resultados] = 0;
    misO[resultados] = 0;
    misI[resultados] = 0;
    opj24p9[resultados] = 0;
    misOj24p9[resultados] = 0;
    misIj24p9[resultados] = 0;
    opp9p4[resultados] = 0;
    misOp9p4[resultados] = 0;
    misIp9p4[resultados] = 0;

    resultados = resultados + 1;
  }
  
  resultados = 0;
  }

  /**
 * 
 * 
 * 
 * 
 * BLOQUE DE CÓDIGO PARA DETERMINAR EL ESTADO DE LAS CONEXIONES A ANALIZAR.CONEXIONES DEFINIDAS EN "sta3[]"
 * 
 * 
 * 
 * 
 */

void rasp2(){

  //CONEXION #1 ------------------------------------------------------------------------------------------------------------------------
  if(opj24p9[0] == 0 and misOj24p9[0] == 0 and misIj24p9[0] == 0){
    arr[0] = "PASSED";
  }
  else if(opj24p9[0] > 0 and misOj24p9[0] == 0 and misIj24p9[0] == 0){
    arr[0] = "OPEN";
  }
  else if(opj24p9[0] == 0 and misOj24p9[0] == 1 or misIj24p9[0] == 1){
    arr[0] = "MISWIRE";
  }
  else if(opj24p9[0] > 0 and (misOj24p9[0] == 1 or misIj24p9[0] == 1)){
    arr[0] = "OPEN & MISWIRE";
  }

  //CONEXION #2 ------------------------------------------------------------------------------------------------------------------------|||||||||||||||||||||||||||||
  if(opj24p9[1] == 0 and misOj24p9[1] == 0 and misIj24p9[1] == 0){
    arr[1] = "PASSED";
  }
  else if(opj24p9[1] > 0 and misOj24p9[1] == 0 and misIj24p9[1] == 0){
    arr[1] = "OPEN";
  }
  else if(opj24p9[1] == 0 and misOj24p9[1] == 1 or misIj24p9[1] == 1){
    arr[1] = "MISWIRE";
  }
  else if(opj24p9[1] > 0 and (misOj24p9[1] == 1 or misIj24p9[1] == 1)){
    arr[1] = "OPEN & MISWIRE";
  }

  //CONEXION #3 ------------------------------------------------------------------------------------------------------------------------
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
    arr[2] = "PASSED";
  }
  else if(vs == 0){
    arr[2] = "OPEN";
  }
  else if(vs != 0 and vs != 100){
    arr[2] = "MISWIRE";
  }
  else if(vs == 0 and vsM != 0){
    arr[2] = "OPEN & MISWIRE";
  }
  /*Serial.println();
  Serial.println(vs);
  Serial.println(vsM);*/
  vs = 0;
  vsM = 0;

  //CONEXION #4 ------------------------------------------------------------------------------------------------------------------------
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
    arr[3] = "PASSED";
  }
  else if((op[6] != 0 or op[9] !=0) and misI[6] == 0 and misO[6] ==0 and misI[9] == 0 and misO[9] == 0){
    arr[3] = "OPEN";
  }
  else if(op[6] == 0 and op[9] ==0 and (misI[6] == 1 or misO[6] == 1 or misI[9] == 1 or misO[9] == 1)){
    arr[3] = "MISWIRE";
  }
  else if(op[6] != 0 or op[9] !=0 and (misI[6] == 1 or misO[6] == 1 or misI[9] == 1 or misO[9] == 1)){
    arr[3] = "OPEN & MISWIRE";
  }
  else{
    arr[3] = "REVISAR";
  }

  vs = 0;
  vsM = 0;
  
  //CONEXION #5 ------------------------------------------------------------------------------------------------------------------------

  if(opj24p9[9] == 0 and misOj24p9[9] ==0 and misIj24p9[9] == 0 and misOj24p9[6] == 0 and misIj24p9[6] == 0){
    arr[4] = "PASSED";
  }
  else if(opj24p9[9] != 0 and misOj24p9[9] == 0 and misIj24p9[9] == 0 and misOj24p9[6] == 0 and misIj24p9[6] == 0){
    arr[4] = "OPEN";
  }
  else if(opj24p9[9] == 0 and misOj24p9[9] == 1 or misIj24p9[9] == 1 or misOj24p9[6] == 1 or misIj24p9[6] == 1){
    arr[4] = "MISWIRE";
  }
  else if(opj24p9[9] != 0 and (misOj24p9[9] == 1 or misIj24p9[9] == 1 or misOj24p9[6] == 1 or misIj24p9[6] == 1)){
    arr[4] = "OPEN & MISWIRE";
  }


  //SERIAL PRINT ------------------------------------------------------------------------------------------------------------------------
  while(resultados<5){
    Serial.println(sta3[resultados] + arr[resultados]);

    resultados = resultados + 1;
    delay(100);
  }
  resultados = 0;

  while(resultados<10){
    op[resultados] = 0;
    misO[resultados] = 0;
    misI[resultados] = 0;
    opj24p9[resultados] = 0;
    misOj24p9[resultados] = 0;
    misIj24p9[resultados] = 0;
    opp9p4[resultados] = 0;
    misOp9p4[resultados] = 0;
    misIp9p4[resultados] = 0;

    resultados = resultados + 1;
  }
  
  resultados = 0;   

}

void tresPuntas(){ //Función que es llamada para analizar las conexiones entre 3 puntas
  
    delay(1125); //1250
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
      continuidadj24p9(3);
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
      
      if(noConectado == 3){
        digitalWrite(redLed, HIGH);
        delay(4000);
        digitalWrite(redLed, LOW);
      }
      
      delay(125);
      rasp3();
      delay(125);
      //Serial.println(ensambleAprobado);
      delay(250);
      //delay(50);
      
      if(ensambleAprobado == 3){
        Serial.println(ensambleAprobado);
        digitalWrite(greenLed, HIGH);
        delay(4000);
        digitalWrite(greenLed, LOW);
      }
      else if(fallo >0 and noConectado != 3 and ensambleAprobado!=3){ //if(ensambleAprobado >0 and ensambleAprobado!=3)
        Serial.println(ensambleAprobado);
        digitalWrite(redLed, HIGH);
        digitalWrite(buz, HIGH);
        delay(4000);
        digitalWrite(redLed, LOW);
        digitalWrite(buz, LOW);
      }
      
      
      ensambleAprobado = 0;
      noConectado = 0;
      fallo = 0;
}

void dosPuntas(){ //Función que es llamada para analizar las conexiones entre 2 puntas
  delay(1125); //1250
    
      for(int i = 0; i < 10; i++){
        pinMode(j24[i], OUTPUT);
        pinMode(p9[i], INPUT);
        pinMode(p4[i], INPUT);
        digitalWrite(j24[i], LOW);
      }
      continuidadj24p9(2);
      delay(50);
      variables();


      delay(250);
      Serial.println(F("break"));
      delay(125);
      if(noConectado == 1){
        digitalWrite(redLed, HIGH);
        delay(4000);
        digitalWrite(redLed, LOW);
      }
      
      delay(250);
      rasp2();
      delay(125);
      
      if(ensambleAprobado == 1){
        Serial.println(ensambleAprobado);
        digitalWrite(greenLed, HIGH);
        delay(4000);
        digitalWrite(greenLed, LOW);
      }
      else if(fallo >0 and noConectado != 1 and ensambleAprobado!=1){ //if(ensambleAprobado >0 and ensambleAprobado!=3)
        Serial.println(ensambleAprobado);
        digitalWrite(redLed, HIGH);
        digitalWrite(buz, HIGH);
        delay(4000);
        digitalWrite(redLed, LOW);
        digitalWrite(buz, LOW);
      }
      
      
      ensambleAprobado = 0;
      noConectado = 0;
      fallo = 0;
}

    

void loop() {
 if (Serial.available() > 0) {
    String numeroPuntas = Serial.readStringUntil('\n');
    if(numeroPuntas=="3"){
      //delay(250);
      tresPuntas();
    }
    else if(numeroPuntas=="2"){
      dosPuntas();
    }
  }
 
}
