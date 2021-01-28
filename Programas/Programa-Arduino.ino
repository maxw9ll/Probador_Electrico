// Los conectores se cuentan de arriba hacia abajo 
int conector1[] = {11, 10, 9, 8, 7, 6, 5, 4, 3, 2}; // Pines Conector 1 = P4 = P15
int conector2[] = {23, 25, 27, 29, A14, A15, 31, 33, 35, 37}; // Pines Conector 2 = P9
int conector3[] = {22, 24, 26, 28, 30, 32, 34, 36, 38, 40}; // Pines Conector 3 = J24 = J15

int buz = 47; // Pin de salida de buzzer
int greenLed = 49; // Pin de salida de LED verde
int redLed = 51; // Pin de salida de LED rojo

String bs = "BS";// Variable que sustituye la posición 10 por la tapadera

int resist = 0; // Variable utilizada para detectar una resistencia 

int erroresOpen[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // Arreglo donde se alamcenan los errores tipo Open
int erroresMiswire[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // Arreglo donde se almacenan los errores tipo Miswire

int conexionesIncorrectas = 0; // Varieble que almacena el numero de conexiones incorrectas entre conectore y conector
int conexionesCorrectas = 0; // Varieble que almacena el numero de conexiones correctas entre conectore y conector

String conexiones3Puntas[] = {"1,WIRE,P4-001,J24-001,", "2,WIRE,J24-001,P9-001,", "3,WIRE,P4-002,J24-002,", "4,WIRE,J24-002,P9-002,", "5,WIRE,P4-007,P4-BS,", "6,WIRE,P4-BS,J24-007,", 
"7,WIRE,J24-007,J24-BS,", "8,WIRE,J24-BS,P9-007,", "9,WIRE,P9-007,P9-BS,", "10,WIRE,P4-008,P9-008,", "11,WIRE,J24-005,P9-005,", 
"12,WIRE,J24-006,P9-006,", "13,RESISTOR,P9-005,P9-006,"}; // Arreglo de conexiones a analizar en un ensamble de 3 puntas con RM80983

String conexiones2Puntas[] = {"1,WIRE,P15-001,J15-001,", "2,WIRE,P15-002,J15-002,", "3,WIRE,P15-007,P15-BS,", 
"4,WIRE,P15-BS,J15-007,", "5,WIRE,J15-007,J15-BS,"}; // Arreglo de conexiones a analizar en un ensamble de 2 puntas con RM81418

String estados[] = {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "}; // Arreglo donde se alamcena si la conexión pasó o indica que error tuvo


void setup() {

  Serial.begin(19200); //Baud rate

  for(int i = 0; i < 10; i++){  
    pinMode(conector1[i], INPUT); 
    pinMode(conector2, INPUT); 
    pinMode(conector3, INPUT); 
  }
    
  pinMode(greenLed, OUTPUT); 
  pinMode(redLed, OUTPUT); 
  pinMode(buz, OUTPUT); 

  delay(50);
}

void entradas(int conector[]){ // Función para declarar como entrada los pines de un conector
  for(int i = 0; i < 10; i++){
    pinMode(conector[i], INPUT);
  }      
}

void salidas(int conector[]){ // Función para declarar como salida los pines de un conector
  for(int i = 0; i < 10; i++){
    pinMode(conector[i], OUTPUT);
  }      
}

void high(int conector[]){ // Función para poner en HIGH los pines de un conector
  for(int i = 0; i < 10; i++){
    digitalWrite(conector[i], HIGH);
  }      
}

void low(int conector[]){ // Función para poner en LOW los pines de un conector
  for(int i = 0; i < 10; i++){
    digitalWrite(conector[i], LOW);
  }      
}

//*****************************************************************************************************

void continuidad(int conectorSalida[], int conectorEntrada[], int conexiones){ // Función que detecta si hay ensamble conectado y llama a las funciones para realizar las pruebas
  entradas(conectorEntrada);
  salidas(conectorSalida);
  high(conectorSalida);
  
  int pinesDetectados = 0;

  for(int i = 0; i < 10; i++){
    if(digitalRead(conectorEntrada[i]) == HIGH){
      pinesDetectados = pinesDetectados + 1;
    }
  }
  if(pinesDetectados > 0){
    //Serial.println(F("AHI VA WUWU"));
    low(conectorSalida);
    entradas(conectorSalida);
    
    openEntrada(conectorSalida, conectorEntrada, conexiones);
    misWire(conectorSalida, conectorEntrada, conexiones);
    switch(conexiones){
      case 2:
        resistencia(conector2, 5, 6, "P9");
      break;
      case 3:
        resistencia(conector2, 5, 6, "P9");
      break;
    }
    entradas(conectorEntrada);
    entradas(conectorSalida);
    if(conexiones==4){
      rasp2Puntas();
    }
    else{
      rasp3Puntas(conexiones);
    }
    aprobado(erroresOpen, erroresMiswire, conexiones);
    
  }
  
  else{
    switch(conexiones){
      case 1:
        Serial.println(F("NO HAY ENSAMBLE CONECTADO J24-P4"));
        break;
      case 2:
        Serial.println(F("NO HAY ENSAMBLE CONECTADO J24-P9"));
        break;
      case 3:
        Serial.println(F("NO HAY ENSAMBLE CONECTADO P9-P4"));
        break;
      case 4:
        Serial.println(F("NO HAY ENSAMBLE CONECTADO J15-P15"));
        break;
    }
    Serial.println();
    delay(125);
  }
}

    
//*****************************************************************************************************

void openEntrada(int conectorSalida[],int conectorEntrada[], int conexiones){ // Función para detectar los errores tipo Open
  
  entradas(conectorEntrada);
  salidas(conectorSalida);
  high(conectorSalida);
  
  for(int j = 0; j < 10; j++){
    
    if (digitalRead(conectorEntrada[j]) == LOW ){
      salidasOpen(j+1, conexiones);     
    }
  }
  low(conectorSalida);
  entradas(conectorSalida);
}

void salidasOpen(int posicion, int conexiones){ // Función para imprimir los errores tipo Open
  switch(conexiones){
    case 1:
      if(posicion == 1 or posicion == 2 or posicion == 7){
        Serial.print(F("OPEN J24-P4 EN POSICION ")); Serial.println(posicion);
      }
      else if(posicion == 10){
        Serial.println(F("OPEN J24-P4 EN BS "));
      }
      break;
    case 2:
      if(posicion != 3 and posicion != 4 and posicion != 8 and posicion != 9 and posicion != 10){
        Serial.print(F("OPEN J24-P9 EN POSICION ")); Serial.println(posicion);
      }
      else if(posicion == 10){
        Serial.println(F("OPEN J24-P9 EN BS ")); 
      }
      break;
    case 3:
      if(posicion == 1 or posicion == 2 or posicion == 7 or posicion == 8){
        Serial.print(F("OPEN P9-P4 EN POSICION ")); Serial.println(posicion);
      }
      else if(posicion == 10){
        Serial.println(F("OPEN P9-P4 EN BS "));
      }
      break;
    case 4:
      if(posicion == 1 or posicion == 2 or posicion == 7){
        Serial.print(F("OPEN J15-P15 EN POSICION ")); Serial.println(posicion);
      }
      else if(posicion == 10){
        Serial.println(F("OPEN J15-P15 EN BS "));
      }
      break;
  }
  erroresOpen[posicion-1] = erroresOpen[posicion-1]+1;
  delay(125);
}


//*****************************************************************************************************

void misWire(int conectorSalida[],int conectorEntrada[], int conexiones){ // Función para detectar los errores tipo Miswire
 entradas(conectorEntrada);
 salidas(conectorSalida);
 low(conectorSalida);
 
 for(int i = 0; i < 10; i++){
   digitalWrite(conectorSalida[i], HIGH);

   for(int j = 0; j < 10; j++){
     if(digitalRead(conectorEntrada[j])==HIGH and j!=i){
       salidasMiswire(i+1, j+1, conexiones);
       noConectar(i+1, j+1, conexiones);
     }
     else if(digitalRead(conectorEntrada[j])==HIGH and i==j){
      noConectar(i+1, j+1, conexiones);
     }
     
   }
   digitalWrite(conectorSalida[i], LOW);
 }
 entradas(conectorSalida);
}

void salidasMiswire(int pinSalida,int pinEntrada, int conexiones){ // Función para imprimir los errores tipo Miswire
  
  if (not((pinSalida==10 and pinEntrada==7) or (pinSalida==7 and pinEntrada==10))) {  //and
      switch(conexiones){
      
      case 1:
        Serial.print(F("MISWIRE J24-")); if(pinSalida != 10){Serial.print(pinSalida);} else{Serial.print(bs);}
        Serial.print(F(" CON P4-")); if(pinEntrada != 10){Serial.println(pinEntrada);} else{Serial.println(bs);}
        delay(125);
        break;
      case 2:
        Serial.print(F("MISWIRE J24-")); if(pinSalida != 10){Serial.print(pinSalida);} else{Serial.print(bs);}
        Serial.print(F(" CON P9-")); if(pinEntrada != 10){Serial.println(pinEntrada);} else{Serial.println(bs);}
        delay(125);
        break;
      case 3:
        Serial.print(F("MISWIRE P9-")); if(pinSalida != 10){Serial.print(pinSalida);} else{Serial.print(bs);}
        Serial.print(F(" CON P4-")); if(pinEntrada != 10){Serial.println(pinEntrada);} else{Serial.println(bs);}
        delay(125);
        break;
      case 4:
        Serial.print(F("MISWIRE J15-")); if(pinSalida != 10){Serial.print(pinSalida);} else{Serial.print(bs);}
        Serial.print(F(" CON P15-")); if(pinEntrada != 10){Serial.println(pinEntrada);} else{Serial.println(bs);}
        delay(125);
        break;
    }
    erroresMiswire[pinSalida-1] = erroresMiswire[pinSalida-1] + 1;
    erroresMiswire[pinEntrada-1] = erroresMiswire[pinEntrada-1] + 1;
  }
}
//*****************************************************************************************************
void erroresNoConectar(int pinSalida, int pinEntrada){ // Función para almacenar los errores de coenxiones no deseadas
  erroresMiswire[pinSalida-1] = erroresMiswire[pinSalida-1] + 1;
  erroresMiswire[pinEntrada-1] = erroresMiswire[pinEntrada-1] + 1;
}
//*****************************************************************************************************

void noConectar(int pinSalida, int pinEntrada, int conexiones){ // Función que detecta e imprime las conexiones no deseadas

  switch(conexiones){
    
    case 1:
      if((pinSalida != 1 and pinSalida != 2 and pinSalida != 7 and pinSalida != 10) or
        (pinEntrada != 1 and pinEntrada != 2 and pinEntrada != 7 and pinEntrada != 10)){
        Serial.print(F("NO DEBE CONECTARSE "));Serial.print(F("J24-P4 "));
        if(pinSalida != 10){Serial.print(pinSalida);} else{Serial.print(bs);} 
        Serial.print("-");
        if(pinEntrada != 10){Serial.println(pinEntrada);} else{Serial.println(bs);}
        erroresNoConectar(pinSalida-1, pinEntrada-1);
        delay(125);
      }
      break;
    case 2:
      if((pinSalida == 3 or pinSalida == 4 or pinSalida == 8 or pinSalida == 9) or
        (pinEntrada == 3 or pinEntrada == 4 or pinEntrada == 8 or pinEntrada == 9)){
        Serial.print(F("NO DEBE CONECTARSE "));Serial.print(F("J24-P9 "));
        if(pinSalida != 10){Serial.print(pinSalida);} else{Serial.print(bs);} 
        Serial.print("-");
        if(pinEntrada != 10){Serial.println(pinEntrada);} else{Serial.println(bs);}
        erroresNoConectar(pinSalida-1, pinEntrada-1);
        delay(125);
      }
      break;
    case 3:
      if((pinSalida == 3 or pinSalida == 4 or pinSalida == 5 or pinSalida == 6 or pinSalida == 9) or
        pinEntrada == 3 or pinEntrada == 4 or pinEntrada == 5 or pinEntrada == 6 or pinEntrada == 9){
        Serial.print(F("NO DEBE CONECTARSE "));Serial.print(F("P9-P4 "));
        if(pinSalida != 10){Serial.print(pinSalida);} else{Serial.print(bs);} 
        Serial.print("-");
        if(pinEntrada != 10){Serial.println(pinEntrada);} else{Serial.println(bs);}
        erroresNoConectar(pinSalida-1, pinEntrada-1);
        delay(125);
      }
      break;
    case 4:
      if((pinSalida != 1 and pinSalida != 2 and pinSalida != 7 and pinSalida != 10) or
        (pinEntrada != 1 and pinEntrada != 2 and pinEntrada != 7 and pinEntrada != 10)){
        Serial.print(F("NO DEBE CONECTARSE "));Serial.print(F("J15-P15 "));
        if(pinSalida != 10){Serial.print(pinSalida);} else{Serial.print(bs);} 
        Serial.print("-");
        if(pinEntrada != 10){Serial.println(pinEntrada);} else{Serial.println(bs);}
        erroresNoConectar(pinSalida-1, pinEntrada-1);
        delay(125);
      }
      break;
  }
}

//*****************************************************************************************************

void resistencia(int conector[], int pin1, int pin2, String designador){ // Función para detectar una resistencia
  entradas(conector);
  int detectada = 0;

  pinMode(conector[pin1-1], OUTPUT);
  digitalWrite(conector[pin1-1], HIGH);
  
    if(analogRead(conector[pin2-1]) > 95 and analogRead(conector[pin2-1]) < 1024){
     detectada = detectada + 1;
    }


   digitalWrite(conector[pin1-1], LOW);
   pinMode(conector[pin1-1], INPUT);  
   pinMode(conector[pin2-1], OUTPUT);
   digitalWrite(conector[pin2-1], HIGH);

  
   if(analogRead(conector[pin1-1]) > 95 and analogRead(conector[pin1-1]) < 1024){
    detectada = detectada + 1;
    if(detectada ==2){
      estados[12] = "DETECTED";
    }
   }
    
   digitalWrite(conector[pin2-1], LOW);
   pinMode(conector[pin2-1], INPUT);
 


  if(detectada < 2){
    Serial.print(F("RESISTENCIA NO DETECTADA EN "));Serial.print(designador); Serial.print(": "); Serial.print(pin1);Serial.print(F("-"));Serial.println(pin2);
    resist = resist + 1;
    estados[12] = "NOT DETECTED";
    delay(500);
  }
  
  detectada=0;
  
}

//*****************************************************************************************************

void aprobado(int erroresOp[], int erroresMis[], int conexiones){ // Función que imprime si las conexiones entre dos conectores han sido aprobadas o no
  

  
  for(int i = 0; i < 10; i++){
    switch(conexiones){
      case 1:
        if((erroresOp[i] != 0 or erroresMis[i] != 0) and (i==0 or i==1 or i==6 or i==9)){
          conexionesIncorrectas = conexionesIncorrectas + 1;
        }
        break;
      case 2:
        if((erroresOp[i] != 0 or erroresMis[i] != 0) and (i!=2 and i!=3 and i!=7 and i!=8)){
          conexionesIncorrectas = conexionesIncorrectas + 1;
        }
        break;
      case 3:
        if((erroresOp[i] != 0 or erroresMis[i] != 0) and (i==0 or i==1 or i==6 or i==7 or i==9)){
          conexionesIncorrectas = conexionesIncorrectas + 1;
        }
        break;
      case 4:
        if((erroresOp[i] != 0 or erroresMis[i] != 0) and (i==0 or i==1 or i==6 or i==9)){
          conexionesIncorrectas = conexionesIncorrectas + 1;
        }
      break;
 
    }
  }
  
  
  
  if(conexionesIncorrectas == 0 and resist == 0){
    conexionesCorrectas = conexionesCorrectas + 1;
    switch(conexiones){
      case 1:
        Serial.println(F("CONEXION J24-P4 APROBADA :)"));
        break;
      case 2:
        Serial.println(F("CONEXION J24-P9 APROBADA :)"));
        break;
      case 3:
        Serial.println(F("CONEXION P9-P4 APROBADA :)"));
        break;
      case 4:
        Serial.println(F("CONEXION J15-15 APROBADA :)"));
        break;
    }
    Serial.println();
    delay(25);
  }
  else{
    switch(conexiones){
      case 1:
        Serial.println(F("CONEXION J24-P4 DEFECTUOSA :("));
        break;
      case 2:
        Serial.println(F("CONEXION J24-P9 DEFECTUOSA :("));
        break;
      case 3:
        Serial.println(F("CONEXION P9-P4 DEFECTUOSA :("));
        break;
      case 4:
        Serial.println(F("CONEXION J15-15 DEFECTUOSA :("));
        break;
    }
    Serial.println();
    delay(25);
  }

  //Serial.println(conexionesIncorrectas);
  //delay(125);
  
  for(int i = 0; i < 10; i++){
    erroresOp[i] = 0;
    erroresMis[i] = 0;
  }
  resist = 0;
  conexionesIncorrectas = 0;
}

//*****************************************************************************************************

void conexionBS(int conector[], int posicion){ // Función para comprobar la conexion entre 7-BS de un conector
  
  int vs = 0;
  int vsM = 0;
  entradas(conector);
  
  
  pinMode(conector[6], OUTPUT);
  digitalWrite(conector[6], HIGH);
  delay(50);

  if(digitalRead(conector[9]) == HIGH){
    vs = vs + 1;
  }

  
    if(vs == 1 and erroresMiswire[6] == 0 and erroresMiswire[9] == 0){
      estados[posicion-1] = "PASSED";
    }
    else if((vs==0) and (erroresMiswire[6] == 0 and erroresMiswire[9] == 0)){
      estados[posicion-1] = "OPEN";
    }
    else if((erroresOpen[6] == 0 and erroresOpen[9] == 0) and (erroresMiswire[6] != 0 or erroresMiswire[9] != 0)){
      estados[posicion-1] = "MISWIRE";
    }
    else if((erroresOpen[6] != 0 or erroresOpen[9] != 0) and (erroresMiswire[6] != 0 and erroresMiswire[9] != 0)){
      estados[posicion-1] = "OPEN & MISWIRE";
    }
 
}
//*****************************************************************************************************

void conexiones7(int conectorSalida[], int conectorEntrada[], int posicion){ // Función para comprobar la conexión entre Bs-7 entre 2 conectores
  
  int vs = 0;
  int vsM = 0;
  entradas(conectorEntrada);
  salidas(conectorSalida);
  
  digitalWrite(conectorSalida[6], HIGH);

  for(int r = 0; r < 10; r++){
    if(r!=6){
      if(digitalRead(conectorEntrada[r]) == HIGH and r==9){
    
      vs = vs + 100;
    }
    else if(digitalRead(conectorEntrada[r]) == HIGH and r!=9 and r!=6){
      vs = vs + 1;
    }
  }
  }
  digitalWrite(conectorSalida[6], LOW);
  entradas(conectorSalida);
  
  for(int r = 0; r < 10; r++){
   if(r!= 9){
    pinMode(conectorEntrada[r], OUTPUT);
    if(r==6){
      digitalWrite(conectorEntrada[6], HIGH);
    }
   }
    

    if(digitalRead(conectorSalida[r]) == HIGH and r!=9 and r!=6){
      vsM = vsM + 1;
    }
    digitalWrite(conectorEntrada[r], LOW);
    pinMode(conectorEntrada[r], INPUT);
  }
  
    if(vs == 100){ //sin vsM
      estados[posicion-1] = "PASSED";
    }
    else if(vs == 0 and vsM == 0){ //Sin vsM
      estados[posicion-1] = "OPEN";
    }
    else if(vs != 0 and vs != 100){
      estados[posicion-1] = "MISWIRE";
    }
    else if(vs == 0 and vsM != 0){
      estados[posicion-1] = "OPEN & MISWIRE";
    }
 
}

//*****************************************************************************************************




void rasp3Puntas(int conexiones){ // Función donde se almacenan los estados de las conexiones del ensamble de 3 puntas que es mandada la Raspberry Pi

  switch(conexiones){

    case 1:
      //CONEXION #1 ------------------------------------------------------------------------------------------------------------------------
      if(erroresOpen[0] == 0 and erroresMiswire[0] == 0){
        estados[0] = "PASSED";
      }
      else if(erroresOpen[0] > 0 and erroresMiswire[0] == 0){
        estados[0] = "OPEN";
      }
      else if(erroresOpen[0] == 0 and erroresMiswire[0] > 0){
        estados[0] = "MISWIRE";
      }
      else if(erroresOpen[0] > 0 and erroresMiswire[0] > 0){
        estados[0] = "OPEN & MISWIRE";
      }

      //CONEXION #3 ------------------------------------------------------------------------------------------------------------------------
      if(erroresOpen[1] == 0 and erroresMiswire[1] == 0){
        estados[2] = "PASSED";
      }
      else if(erroresOpen[1] > 0 and erroresMiswire[1] == 0){
        estados[2] = "OPEN";
      }
      else if(erroresOpen[1] == 0 and erroresMiswire[1] > 0){
        estados[2] = "MISWIRE";
      }
      else if(erroresOpen[1] > 0 and erroresMiswire[1] > 0){
        estados[2] = "OPEN & MISWIRE";
      }

      //CONEXION #5 ------------------------------------------------------------------------------------------------------------------------

      conexionBS(conector1, 5);
      

      //CONEXION #6 ------------------------------------------------------------------------------------------------------------------------
      conexiones7(conector3, conector1, 6);

      //CONEXION #7 ------------------------------------------------------------------------------------------------------------------------

      conexionBS(conector3, 7);

      break;
    case 2:
      //CONEXION #2 ------------------------------------------------------------------------------------------------------------------------
      if(erroresOpen[0] == 0 and erroresMiswire[0] == 0){
        estados[1] = "PASSED";
      }
      else if(erroresOpen[0] > 0 and erroresMiswire[0] == 0){
        estados[1] = "OPEN";
      }
      else if(erroresOpen[0] == 0 and erroresMiswire[0] > 0){
        estados[1] = "MISWIRE";
      }
      else if(erroresOpen[0] > 0 and erroresMiswire[0] > 0){
        estados[1] = "OPEN & MISWIRE";
      }

      //CONEXION #4 ------------------------------------------------------------------------------------------------------------------------
      if(erroresOpen[1] == 0 and erroresMiswire[1] == 0){
        estados[3] = "PASSED";
      }
      else if(erroresOpen[1] > 0 and erroresMiswire[1] == 0){
        estados[3] = "OPEN";
      }
      else if(erroresOpen[1] == 0 and erroresMiswire[1] > 0){
        estados[3] = "MISWIRE";
      }
      else if(erroresOpen[1] > 0 and erroresMiswire[1] > 0){
        estados[3] = "OPEN & MISWIRE";
      }

      //CONEXION #7 ------------------------------------------------------------------------------------------------------------------------

      conexionBS(conector3, 7);

      //CONEXION #8 ------------------------------------------------------------------------------------------------------------------------
      conexiones7(conector3, conector2, 8);

      //CONEXION #9 ------------------------------------------------------------------------------------------------------------------------

      conexionBS(conector2, 9);

      //CONEXION #11 ------------------------------------------------------------------------------------------------------------------------
      if(erroresOpen[4] == 0 and erroresMiswire[4] == 0){
        estados[10] = "PASSED";
      }
      else if(erroresOpen[4] > 0 and erroresMiswire[4] == 0){
        estados[10] = "OPEN";
      }
      else if(erroresOpen[4] == 0 and erroresMiswire[4] > 0){
        estados[10] = "MISWIRE";
      }
      else if(erroresOpen[4] > 0 and erroresMiswire[4] > 0){
        estados[10] = "OPEN & MISWIRE";
      }

      //CONEXION #12 ------------------------------------------------------------------------------------------------------------------------
      if(erroresOpen[5] == 0 and erroresMiswire[5] == 0){
        estados[11] = "PASSED";
      }
      else if(erroresOpen[5] > 0 and erroresMiswire[5] == 0){
        estados[11] = "OPEN";
      }
      else if(erroresOpen[5] == 0 and erroresMiswire[5] > 0){
        estados[11] = "MISWIRE";
      }
      else if(erroresOpen[5] > 0 and erroresMiswire[5] > 0){
        estados[11] = "OPEN & MISWIRE";
      }
      break;
    case 3:

      //CONEXION #5 ------------------------------------------------------------------------------------------------------------------------

      conexionBS(conector1, 5);

      //CONEXION #9 ------------------------------------------------------------------------------------------------------------------------

      conexionBS(conector2, 9);

      
      //CONEXION #10 ------------------------------------------------------------------------------------------------------------------------
      if(erroresOpen[7] == 0 and erroresMiswire[7] == 0){
        estados[9] = "PASSED";
      }
      else if(erroresOpen[7] > 0 and erroresMiswire[7] == 0){
        estados[9] = "OPEN";
      }
      else if(erroresOpen[7] == 0 and erroresMiswire[7] > 0){
        estados[9] = "MISWIRE";
      }
      else if(erroresOpen[7] > 0 and erroresMiswire[7] > 0){
        estados[9] = "OPEN & MISWIRE";
      }
      break;
     
  }
  
}

//*****************************************************************************************************

void rasp2Puntas(){ // Función donde se almacenan los estados de las conexiones del ensamble de 2 puntas que es mandada la Raspberry Pi
  //CONEXION #1 ------------------------------------------------------------------------------------------------------------------------
      if(erroresOpen[0] == 0 and erroresMiswire[0] == 0){
        estados[0] = "PASSED";
      }
      else if(erroresOpen[0] > 0 and erroresMiswire[0] == 0){
        estados[0] = "OPEN";
      }
      else if(erroresOpen[0] == 0 and erroresMiswire[0] > 0){
        estados[0] = "MISWIRE";
      }
      else if(erroresOpen[0] > 0 and erroresMiswire[0] > 0){
        estados[0] = "OPEN & MISWIRE";
      }
      
      //CONEXION #2 ------------------------------------------------------------------------------------------------------------------------
      if(erroresOpen[1] == 0 and erroresMiswire[1] == 0){
        estados[1] = "PASSED";
      }
      else if(erroresOpen[1] > 0 and erroresMiswire[1] == 0){
        estados[1] = "OPEN";
      }
      else if(erroresOpen[1] == 0 and erroresMiswire[1] > 0){
        estados[1] = "MISWIRE";
      }
      else if(erroresOpen[1] > 0 and erroresMiswire[1] > 0){
        estados[1] = "OPEN & MISWIRE";
      }
      
      //CONEXION #3 ------------------------------------------------------------------------------------------------------------------------
      conexionBS(conector1, 3);

      
      //CONEXION #4 ------------------------------------------------------------------------------------------------------------------------
      
      conexiones7(conector3, conector1, 4);

      //CONEXION #5 ------------------------------------------------------------------------------------------------------------------------
      conexionBS(conector3, 5);
}

//*****************************************************************************************************

void mandarDatos(int puntas, String conexionesEvaluadas[]){ // Función para mandar los datos e la Raspberry Pi
  int resultados = 0;
  int ciclo = 0;
  switch(puntas){
    case 2:
      ciclo = 5;
      break;
    case 3:
      ciclo = 13;
      break;      
  }
  while(resultados<ciclo){
    Serial.println(conexionesEvaluadas[resultados] + estados[resultados]);
    
    resultados = resultados + 1;
    delay(100);
  }

//  Serial.println();
//  Serial.println(conexionesCorrectas);
//  Serial.println();
//  delay(375);
  
  resultados = 0;
  //conexionesCorrectas = 0;
  //conexionesIncorrectas = 0;

  }


//*****************************************************************************************************
void cable3Puntas(){ // Función para hacer pruebas en un ensamble de 3 puntas con RM80983
  delay(375); //1250
  continuidad(conector3, conector1, 1);
  delay(50);
  continuidad(conector3, conector2, 2);
  delay(50);
  continuidad(conector2, conector1, 3);
  delay(50);
  //Serial.println();
  Serial.println(F("break"));
  delay(250);
  mandarDatos(3, conexiones3Puntas);
  delay(50);
  //Serial.println(conexionesCorrectas);
  
  if(conexionesCorrectas == 3){
    Serial.println(conexionesCorrectas);
    digitalWrite(greenLed, HIGH);
    delay(4000);
    digitalWrite(greenLed, LOW);
  }
  else{
    Serial.println(conexionesCorrectas);
    digitalWrite(redLed, HIGH);
    for(int b = 0; b < 4; b++){
      digitalWrite(buz, HIGH);
      delay(500);
      digitalWrite(buz, LOW);
      delay(500);
    }
    digitalWrite(redLed, LOW);
  }
  
  conexionesCorrectas = 0;
  conexionesIncorrectas = 0;
}
//*****************************************************************************************************

void cable2Puntas(){ // Función para hacer pruebas en un ensamble de 2 puntas con RM81418
  delay(750); //1250
  continuidad(conector3, conector1, 4);
  delay(50);
  //Serial.println();
  Serial.println(F("break"));
  delay(250);
  mandarDatos(2, conexiones2Puntas);
  delay(50);
  //Serial.println()
  
  if(conexionesCorrectas == 1){
    Serial.println(conexionesCorrectas);
    digitalWrite(greenLed, HIGH);
    delay(4000);
    digitalWrite(greenLed, LOW);
  }
  else{
    Serial.println(conexionesCorrectas);
    digitalWrite(redLed, HIGH);
    for(int b = 0; b < 4; b++){
      digitalWrite(buz, HIGH);
      delay(500);
      digitalWrite(buz, LOW);
      delay(500);
    }
    digitalWrite(redLed, LOW);
  }
  conexionesCorrectas = 0;
  conexionesIncorrectas = 0;
}
//*****************************************************************************************************


//*****************************************************************************************************

void loop(){
  
  if (Serial.available() > 0) { // Si el puerto serial esta disponible
    String numeroPuntas = Serial.readStringUntil('\n');
    if(numeroPuntas=="3"){
      //delay(250);
      cable3Puntas();
    }
    else if(numeroPuntas=="2"){
      cable2Puntas();
    }
  }

}
