# Probador de Cables
Probador de Cables para Ensamble Aeroespacial de 3 Puntas Utilizando Arduino y Raspberry Pi

El funcionamiento del probador de cables se basa en ver la conductividad para verificar las conexiones según el diagrama.

Para verificar las conexiones se utilizan los pines del Arduino Mega 2560 como salidas y entradas las cuales son leídas para detectar las señales eléctricas. Dependiendo de las lecturas se genera como resultado una cadena de datos con las conexiones analizadas verificando si el cable fue aprobado o si fue rechazado se especificando que tipo de error se detectó (open, miswire o short) y en donde fue que se detectó. Ficha cadena de datos es enviada via serial al Raspberry Pi 4 el cual la recibe y la almacena en un nuevo archivo en formato Excel.

Para iniciar el proceso de revisión de conexiones se escanea un código de barras que da como resultado un número de 6 dígitos el cual es ingreado en una interfaz. Si el número ingresado es válido, se envía el número a un sistema para extraer de ahí datos como RM y No. de parte. Al validarse los datos la Raspberry Pi manda un mensaje via serial al Arduino. El Arduino al recibir el mensaje comienza con las pruebas y genera la cadena de datos para mandarlo de regreso hacía la Raspberry Pi. El Raspberry Pi al recibirla despliega en la pantalla una ventana diciendo si el ensamble fue aporbado o si hubo alguna falla indica cual fue la falla. Después de algunos segundos la ventana se cierra automáticamente y se genera un archivo en formato Excel con los resultados para su posterior revisión.
