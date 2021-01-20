# Probador_de_Cables
Probador de Cables para Ensamble Aeroespacial de 3 Puntas Utilizando Arduino y Raspberry Pi

El funcionamiento del probador de cables se basa en ver la conductividad para verificar las conexiones según el diagrama.

Para verificar las conexiones se utilizan los pines del Arduino MEGA 2560 como salidas y entradas las cuales son leídas para detectar los HIGH y LOW. Dependiendo de las lecturas se genera como resultado una cadena (String) la cual es enviada via serial al Raspberry Pi 4 el cual la recibe y la almacena en un nuevo archivo en formato XLS.

Para iniciar el proceso de revisión de conexiones se escanea un código de barras que da como resultado un número de 6 dígitos el cual es ingreado en una interfaz elaborada con Tkinter en el Raspberry Pi. Si el número ingresado es válido, el Raspberry Pi manda una señal de voltaje a través de un pin GPIO al Arduino. El Arduino al recibir la señal comienza con las pruebas y genera el String para mandarlo hacía el Raspberry Pi. El Raspberry al recibirlo despliega en la pantalla una ventana diciendo si el ensamble fue aporbado o si hubo alguna falla indica cual fue la falla. Después de algunos segundos la ventana se cierra automáticamente y se genera un archivo en formato XLS con los resultados para su posterior revisión.
