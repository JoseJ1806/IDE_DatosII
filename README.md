# IDE_DatosII

### Cosas a tener en consideracion a la hora de correr el codigo:
1) Para correr el programa se recomienda hacerlo desde el IDE de Qt-Creator ya que fue donde se desarrollo el codigo
2) Si a la hora de correr el codigo no reconoce un kit se recomienda seguir los siguientes pasos: 
  * Ejecutar en la terminal el comando **sudo apt-get install qt5-default**
  * Verifique la versión del Qt instalado y la ubicación del archivo qmake. Puede obtener un resultado similar a esta línea. **QMake versión 3.1 Usando Qt versión 5.9.5 en / usr     /lib / x86_64-linux-gnu.** Lo importante aquí es la ubicación **/usr/lib/x86_64-linux-gnu.**
  * En Qt-Creator, ir a **"Herramientas>Opciones".**
  * Seleccione el cuadro combinado de versiones de Qt y haga clic en **"Agregar"**
  * Encuentre el archivo de qmake en la ubicación antes mencionada, abralo y dele click en **"Aplicar"**
  * En el cuadro combinado de **"Kits"** seleccione Escritorio(por defecto).Luego, desplácese hacia abajo hasta el botón para seleccionar la versión Qt y enumere hacia abajo para   seleccionar la versión que acaba de agregar.
3) Si a la hora de correr el codigo tira muchos errores vaya a **"Ayuda>Acerca de los plugins..."** y desactive el **Clang Base Model**, reinicie Qt-Creator.
4) En caso de que a la hora de descargar el codigo y probarlo le tire una alerta sobre incompatibilidad borre los archivos que contengan **.pro.user.xxxx** dentro del nombre e intente de nuevo

### Funcionalidad del Codigo
Se utiliza el boton **"Run"** para correr el codigo linea por linea y el boton **"Go Back"** se utiliza para devolverse hasta la primera linea y empezar desde nuevo, para cerrar la aplicacion se debe de dar primero al **"Go Back"** y luego se puede salir del IDE.
