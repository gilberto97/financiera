#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>

#define MAX_ARCHIVO 100   //La longitud maxima del nombre de archivo es de 100
#define MAX_NOMBRE 50     //El largo maximo del nombre es de 50
#define MAX_CREDITOS 100  //El credito maximo es de 100
#define MAX_MESS 4

/*
ADVERTENCIA!
Antes de usar el programa por favor utilice la terminal en pantalla completa, si no se realiza esta acción la lista y las tablas se mostrarán desconfiguradas debido a la longitud de los campos.
Esto dificulta mucho la lectura y le visualización de lo realizado. Muchas gracias.

*/

typedef struct {  //Estructura de la informacion de la base de datos que se va a ir manipulando durante su funcionamiento
    int orden;
    char nombre[MAX_NOMBRE];
    char apellido[MAX_NOMBRE];
    float importe;
    char importeStr[MAX_NOMBRE]; // Agregar importeStr como miembro de la estructura
    char tipoCredito[MAX_NOMBRE];
    int dia;
    int mes;
    char mess[MAX_MESS];
    int anio;
    int numCuotas;
    float importeCuota;
    char importeCuotaStr[MAX_NOMBRE];
    float iva;
    char ivaStr[MAX_NOMBRE];
    float totalCuota;
    char totalCuotaStr[MAX_NOMBRE];
    int activo;
} Credito;


void controlarError(const char* mensaje);
void validarIngresoEntero(int* numero);
void validarIngresoFlotante(float* numero);
void ingresarTexto(char* texto, int maxLength);
void validarIngresoFecha(int* dia, int* mes, int* anio);
bool fechaEsMayorOIgual(int dia1, int mes1, int anio1, int dia2, int mes2, int anio2);
bool fechaEsMenorOIgual(int dia1, int mes1, int anio1, int dia2, int mes2, int anio2);
void listarTxt();
void crearArchivoBinario();
void migrarDatos();
void listarDat();
void altaCliente();  //Hay 12 en total por ahora son 20
void mostrarCredito(Credito credito);
void cambiarMes(int mes, char* mesNombre);
int mesNum(const char* mesNombre);


void controlarError(const char* mensaje) {  // Realizar acciones adicionales para controlar el error según corresponda
    printf("Error: %s\n", mensaje);

}

void validarIngresoEntero(int* numero) {   // Solicitud al usuario que ingrese un numero valido, si no lo hace se le va a solicitar que ingrese uno valido.
    char buffer[100];                       // La funcion usa un bulce while para repetir la solicitud de entras hasta que se ingrese un numero valido.
    fgets(buffer, sizeof(buffer), stdin);   // Si el sscanf devuelve 1 (osea que la conversion es valida), el blucle se interrumple.
    if (sscanf(buffer, "%d", numero) != 1) {// Esta funcion se utiliza en el codigo proporcionado para validar las entradas del usuario al solicitar el numero de orden, el dia, el mes, el año, el numero de cuotas, etc.
        controlarError("Debe ingresar un numero entero válido.");
        validarIngresoEntero(numero);
    }
}

void validarIngresoFlotante(float* numero) {   // Funcion que se repite en bucle que repite la solicitud de entrada de un numero valido.
    char buffer[100];                          // Esta funcion se utiliza en el codigo proporcionado para validar las entradas del usuario al solicitar la tasa de interes, el monto del prestamo y el monto de las cuotas.
    fgets(buffer, sizeof(buffer), stdin);
    if (sscanf(buffer, "%f", numero) != 1) {
        controlarError("Debe ingresar un numero flotante.");
        validarIngresoFlotante(numero);
    }
}

void ingresarTexto(char* texto, int maxLength) {
    fgets(texto, maxLength, stdin);
    size_t len = strlen(texto);
    if (len > 0 && texto[len - 1] == '\n') {
        texto[len - 1] = '\0';
    }
}

void validarIngresoFecha(int* dia, int* mes, int* anio) {  // Función para validar el ingreso de una fecha
    validarIngresoEntero(dia);
    validarIngresoEntero(mes);
    validarIngresoEntero(anio);
}


bool fechaEsMayorOIgual(int dia1, int mes1, int anio1, int dia2, int mes2, int anio2) {
    if (anio1 > anio2)
        return true;
    else if (anio1 == anio2 && mes1 > mes2)
        return true;
    else if (anio1 == anio2 && mes1 == mes2 && dia1 >= dia2)
        return true;
    else
        return false;
}

bool fechaEsMenorOIgual(int dia1, int mes1, int anio1, int dia2, int mes2, int anio2) { // Función para verificar si una fecha es menor o igual a otra fecha
    if (anio1 < anio2)
        return true;
    else if (anio1 == anio2 && mes1 < mes2)
        return true;
    else if (anio1 == anio2 && mes1 == mes2 && dia1 <= dia2)
        return true;
    else
        return false;
}

void reemplazarComasPorPuntos(char* cadena) {
    int i;
    for (i = 0; cadena[i] != '\0'; i++) {
        if (cadena[i] == ',') {
            cadena[i] = '.';
        }
    }
}

void cambiarMes (int mes, char * mesNombre){
    switch (mes) {
        case 1:
            strcpy(mesNombre, "ene");
            break;
        case 2:
            strcpy(mesNombre, "feb");
            break;
        case 3:
            strcpy(mesNombre, "mar");
            break;
        case 4:
            strcpy(mesNombre, "abr");
            break;
        case 5:
            strcpy(mesNombre, "may");
            break;
        case 6:
            strcpy(mesNombre, "jun");
            break;
        case 7:
            strcpy(mesNombre, "jul");
            break;
        case 8:
            strcpy(mesNombre, "ago");
            break;
        case 9:
            strcpy(mesNombre, "sep");
            break;
        case 10:
            strcpy(mesNombre, "oct");
            break;
        case 11:
            strcpy(mesNombre, "nov");
            break;
        case 12:
            strcpy(mesNombre, "dic");
            break;
        default:
            return 0;  // Mes inválido
    }
}

int mesNum(const char* mesNombre) {

    if (strcmp(mesNombre, "ene") == 0)
        return 1;
    else if (strcmp(mesNombre, "feb") == 0)
        return 2;
    else if (strcmp(mesNombre, "mar") == 0)
        return 3;
    else if (strcmp(mesNombre, "abr") == 0)
        return 4;
    else if (strcmp(mesNombre, "may") == 0)
        return 5;
    else if (strcmp(mesNombre, "jun") == 0)
        return 6;
    else if (strcmp(mesNombre, "jul") == 0)
        return 7;
    else if (strcmp(mesNombre, "ago") == 0)
        return 8;
    else if (strcmp(mesNombre, "sep") == 0)
        return 9;
    else if (strcmp(mesNombre, "oct") == 0)
        return 10;
    else if (strcmp(mesNombre, "nov") == 0)
        return 11;
    else if (strcmp(mesNombre, "dic") == 0)
        return 12;

    return 0; // Mes inválido
}

void listarTxt() {                              // 4) Emitir por pantalla el archivo de texto.
    Credito vf[MAX_ARCHIVO];                    //Funcion que se encarga de mostrar en forma de tabla los valores del archivo 'prestamos.csv'.
    int j = 0;                                  //La tabla se emite pero los falores flotantes todavia no de forma decimal.
    FILE* pArchivo = fopen("prestamos.csv", "r");

    if (pArchivo != NULL) {
        char linea[100];

        fgets(linea, sizeof(linea), pArchivo); // Salta la primera línea

        printf("------------------------------------------------------------------------------------------------------------------------------------------\n");
        printf("|  Orden |        Cliente         |  Importe  | Tipo de crédito | Dia | Mes | Anio | Cuotas | Importe Cuota |    IVA   |   Total Cuota   |\n");
        printf("------------------------------------------------------------------------------------------------------------------------------------------\n");

        while (fgets(linea, sizeof(linea), pArchivo) != NULL && j < MAX_ARCHIVO) {
            sscanf(linea, "%d;%[^;];%[^;];%[^;];%d;%d;%d;%d;%[^;];%[^;];%[^;]",
                   &vf[j].orden,
                   vf[j].nombre,
                   vf[j].importeStr,
                   vf[j].tipoCredito,
                   &vf[j].dia,
                   &vf[j].mes,
                   &vf[j].anio,
                   &vf[j].numCuotas,
                   vf[j].importeCuotaStr,
                   vf[j].ivaStr,
                   vf[j].totalCuotaStr);

            reemplazarComasPorPuntos(&vf[j].importeStr);
            reemplazarComasPorPuntos(&vf[j].importeCuotaStr);
            reemplazarComasPorPuntos(&vf[j].ivaStr);
            reemplazarComasPorPuntos(&vf[j].totalCuotaStr);

            sscanf(vf[j].importeStr, "%f", &vf[j].importe);
            sscanf(vf[j].importeCuotaStr, "%f", &vf[j].importeCuota);
            sscanf(vf[j].ivaStr, "%f", &vf[j].iva);
            sscanf(vf[j].totalCuotaStr, "%f", &vf[j].totalCuota);

            printf("| %2d     | %22s | %9.2f | %15s | %02d |  %02d  | %04d | %6d | %13.2f |  %6.2f  | %15.2f |\n",
                   vf[j].orden,
                   vf[j].nombre,
                   vf[j].importe,
                   vf[j].tipoCredito,
                   vf[j].dia,
                   vf[j].mes,
                   vf[j].anio,
                   vf[j].numCuotas,
                   vf[j].importeCuota,
                   vf[j].iva,
                   vf[j].totalCuota);

            j++;
        }

        printf("------------------------------------------------------------------------------------------------------------------------------------------\n");

        fclose(pArchivo);
    } else {
        controlarError("No se pudo abrir el archivo 'prestamos.csv'.");
    }
}

void crearArchivoBinario() {  // 5) Crear un nuevo archivo binario
    int i;                    // Crea un nuevo archivo binario el cual se va a pisar si ya habia uno existente.
    FILE* pArchivo = fopen("creditos.dat", "wb");
    if (pArchivo != NULL) {
        fclose(pArchivo);
        printf("Se ha creado el archivo 'creditos.dat'.\n");
    } else {
        controlarError("No se pudo crear el archivo 'creditos.dat'.");
    }
    fclose(pArchivo);
    return;
}

void migrarDatos() {       // 6) Migrar los archivos de texto
    FILE* pArchivoTxt = fopen("prestamos.csv", "r");    // Migra los datos del archivo 'prestamos.csv' al archivo binario 'creditos.bat'.
    FILE* pArchivoBin = fopen("creditos.dat", "ab");

    if (pArchivoTxt != NULL && pArchivoBin != NULL) {
        char linea[100];
        fgets(linea, sizeof(linea), pArchivoTxt); // Salta la primera linea

        while (fgets(linea, sizeof(linea), pArchivoTxt) != NULL) {
            Credito credito;

            sscanf(linea, "%d;%[^;];%[^;];%[^;];%d;%d;%d;%d;%[^;];%[^;];%[^;]",
                   //"%d;%[^;];%f;%[^;];%d;%d;%d;%d;%f;%f;%f"
                   &credito.orden,
                   credito.nombre,
                   //credito.apellido,
                   credito.importeStr,
                   credito.tipoCredito,
                   &credito.dia,
                   &credito.mes,
                   //credito.mess,
                   &credito.anio,
                   &credito.numCuotas,
                   credito.importeCuotaStr,
                   credito.ivaStr,
                   credito.totalCuotaStr);
                   //&credito.activo);

            reemplazarComasPorPuntos(&credito.importeStr);
            reemplazarComasPorPuntos(&credito.importeCuotaStr);
            reemplazarComasPorPuntos(&credito.ivaStr);
            reemplazarComasPorPuntos(&credito.totalCuotaStr);

            sscanf(credito.importeStr, "%f", &credito.importe);
            fflush(stdin);
            sscanf(credito.importeCuotaStr, "%f", &credito.importeCuota);
            fflush(stdin);
            sscanf(credito.ivaStr, "%f", &credito.iva);
            fflush(stdin);
            sscanf(credito.totalCuotaStr, "%f", &credito.totalCuota);


    // Separar el nombre en nombre y apellido
char nombre[MAX_NOMBRE];
char apellido[MAX_NOMBRE];

char* token = strtok(credito.nombre, " ");
if (token != NULL) {
    strncpy(nombre, token, sizeof(nombre) - 1);
    nombre[sizeof(nombre) - 1] = '\0';
    token = strtok(NULL, " ");
    if (token != NULL) {
        strncpy(apellido, token, sizeof(apellido) - 1);
        apellido[sizeof(apellido) - 1] = '\0';
    } else {
        strncpy(apellido, "", sizeof(apellido));
    }
} else {
    strncpy(nombre, "", sizeof(nombre));
    strncpy(apellido, "", sizeof(apellido));
}

// Copiar el nombre y apellido en la estructura 'credito'
strcpy(credito.nombre, nombre);
strcpy(credito.apellido, apellido);

//La transformacion de numero a texto no se pudo llegar a emitir

// Convertir el mes de número a texto
//char mesTexto[MAX_MESS];
//cambiarMes(credito.mes, mesTexto);

// Copiar el mes convertido al campo 'mes' de la estructura 'credito'
//strcpy(credito.mes, mesTexto);

// Convertir el mes de texto a número
//int mesNumero = mesNum(credito.mes);

// Asignar el número de mes convertido al campo 'mess' de la estructura 'credito'
//credito.mess = mesNumero;



    // Setea el campo 'activo' en 1.
    credito.activo = 1;

            fwrite(&credito, sizeof(Credito), 1, pArchivoBin);
        }

        fclose(pArchivoTxt);
        fclose(pArchivoBin);

        printf("Datos migrados exitosamente.\n");
    } else {
        controlarError("No se pudo abrir uno o ambos archivos de origen o destino.");
    }
}

void listarDat() {   // 7) Emitir por pantalla el contenido del archivo binario
    FILE* pArchivo = fopen("creditos.dat", "rb");

    if (pArchivo != NULL) {
        Credito credito;
        int j = 0;
        int opcion;


        int inicioDia, inicioMes, inicioAnio;
        int finDia, finMes, finAnio;


        printf("\nSeleccione una opcion:\n");
        printf("1. Listar todos (activos e inactivos)\n");
        printf("2. Listar solo activos\n");
        printf("3. Filtrar por tipo de credito\n");
        printf("4. Filtrar por rango de tiempo\n");
        printf("Ingrese el numero de opcion: ");
        validarIngresoEntero(&opcion);

    // Implementa la lógica basada en la opción seleccionada
    switch (opcion) {
        case 1:
                printf("------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
                printf("|  Orden |     Nombre      |   Apellido      | Importe   |Tipo de crédito  |Dia | Mes | Anio | Cuotas | Importe Cuota |   IVA   |   Total Cuota   | Activo |\n");
                printf("------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

                // Leer y imprime todos los registros del archivo binario
                while (fread(&credito, sizeof(Credito), 1, pArchivo) == 1 && j < MAX_ARCHIVO) {
                        printf("| %2d     | %15s | %15s | %9.2f | %15s | %02d | %02d | %04d | %6d | %13.2f |  %6.2f  | %15.2f | %6d |\n",
                               credito.orden,
                               credito.nombre,
                               credito.apellido,
                               credito.importe,
                               credito.tipoCredito,
                               credito.dia,
                               credito.mes,
                               credito.anio,
                               credito.numCuotas,
                               credito.importeCuota,
                               credito.iva,
                               credito.totalCuota,
                               credito.activo);
                    j++;
                }

                printf("------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
                break;
        case 2:
    // Leer y imprimir solo registros activos del archivo binario
               printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
                printf("|  Orden |     Nombre      |   Apellido      | Importe   |Tipo de crédito  |Dia | Mes | Anio | Cuotas | Importe Cuota |   IVA   |   Total Cuota   | Activo |\n");
                printf("------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

    // Leer y imprimir registros activos del archivo binario
    while (fread(&credito, sizeof(Credito), 1, pArchivo) == 1 && j < MAX_ARCHIVO) {
        if (credito.activo == 1) {
            printf("| %2d     | %15s | %15s | %9.2f | %15s | %02d | %02d | %04d | %6d | %13.2f |  %6.2f  | %15.2f | %6d |\n",
                   credito.orden,
                   credito.nombre,
                   credito.apellido,
                   credito.importe,
                   credito.tipoCredito,
                   credito.dia,
                   credito.mes,
                   credito.anio,
                   credito.numCuotas,
                   credito.importeCuota,
                   credito.iva,
                   credito.totalCuota,
                   credito.activo);

            j++;
        }
    }

    printf("------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    break;
        case 3:
                printf("\nSeleccione una opcion: \n");
                printf("1. Con Garantia\n");
                printf("2. A solo firma\n");
                printf("Ingrese el numero de opcion: ");
                int tipo; // Declare the 'tipo' variable as an integer
                validarIngresoEntero(&tipo);
                fflush(stdin);

    // Lea y imprima registros con el tipo de crédito coincidente del archivo binario
                printf("------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
                printf("|  Orden |     Nombre      |   Apellido      | Importe   |Tipo de crédito  |Dia | Mes | Anio | Cuotas | Importe Cuota |   IVA   |   Total Cuota   | Activo |\n");
                printf("------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

    // Lea y imprima registros con el tipo de crédito correspondiente
    while (fread(&credito, sizeof(Credito), 1, pArchivo) == 1 && j < MAX_ARCHIVO) {
        if ((tipo == 1 && strcmp(credito.tipoCredito, "Con Garantia") == 0) ||
            (tipo == 2 && strcmp(credito.tipoCredito, "A sola firma") == 0)) {
            printf("| %2d     | %15s | %15s | %9.2f | %15s | %02d | %02d | %04d | %6d | %13.2f |  %6.2f  | %15.2f | %6d |\n",
                   credito.orden,
                   credito.nombre,
                   credito.apellido,
                   credito.importe,
                   credito.tipoCredito,
                   credito.dia,
                   credito.mes,
                   credito.anio,
                   credito.numCuotas,
                   credito.importeCuota,
                   credito.iva,
                   credito.totalCuota,
                   credito.activo);
            j++;
        }
    }

    printf("------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    break;
        case 4:    //El ingreso de la fecha es bastante robusto o solo emite con los valores en ese orden ingresando exactamente 7 numeros
            // Read the range of time from the user
            //int inicioDia,inicioMes,inicioAnio;
            //int finDia,finMes,finAnio;

            printf("Ingrese la fecha de inicio (DD/MM/AAAA): ");  //El ingreso de fecha funciona aunque salen errores termina emitiendo
            validarIngresoFecha(&inicioDia, &inicioMes, &inicioAnio);

            printf("Ingrese la fecha de fin (DD/MM/AAAA): ");
            validarIngresoFecha(&finDia, &finMes, &finAnio);

            // Imprima los registros filtrados dentro del rango de tiempo dado
                printf("------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
                printf("|  Orden |     Nombre      |   Apellido      | Importe   |Tipo de crédito  |Dia | Mes | Anio | Cuotas | Importe Cuota |   IVA   |   Total Cuota   | Activo |\n");
                printf("------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

            while (fread(&credito, sizeof(Credito), 1, pArchivo) == 1 && j < MAX_ARCHIVO){
            // Compara la fecha de cada registro con el rango de tiempo dado
                if (fechaEsMayorOIgual(credito.dia, credito.mes, credito.anio, inicioDia, inicioMes, inicioAnio)
                    &&fechaEsMenorOIgual(credito.dia, credito.mes, credito.anio, finDia, finMes, finAnio)) {
                        //mostrarCredito(credito); //duda
                        printf("| %2d     | %15s | %15s | %9.2f | %15s | %02d | %02d | %04d | %6d | %13.2f |  %6.2f  | %15.2f | %6d |\n",
                               credito.orden,
                               credito.nombre,
                               credito.importe,
                               credito.tipoCredito,
                               credito.dia,
                               credito.mes,
                               credito.anio,
                               credito.numCuotas,
                               credito.importeCuota,
                               credito.iva,
                               credito.totalCuota,
                               credito.activo);
                     j++;
                 }

             }

    printf("------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    break;

             default:
                controlarError("Opcion invalida.");
                break;
        }

    fclose(pArchivo);
    } else {
        controlarError("No se pudo abrir el archivo 'creditos.dat'.");
    }
}

void altaCliente() {   //El alta emite de cliente agrega al cliente al final de la tabla sin superponer los valores anteriores
    FILE* pArchivo = fopen("creditos.dat", "ab");

    if (pArchivo != NULL) {
        Credito credito;
        credito.orden = 1; // Asignamos el primer número de orden
        int ultimoOrden = 0;

        // Buscamos el último número de orden en el archivo
        fseek(pArchivo, -sizeof(Credito), SEEK_END);
        fread(&credito, sizeof(Credito), 1, pArchivo);
        ultimoOrden = credito.orden;

        int numeroOrden;
        printf("Ingrese el numero de orden: ");
        validarIngresoEntero(&numeroOrden);

        printf("Ingrese el nombre del cliente: ");
        ingresarTexto(credito.nombre, MAX_NOMBRE);

        printf("Ingrese el apellido del cliente: ");
        ingresarTexto(credito.apellido, MAX_NOMBRE);

        printf("Ingrese el importe del crédito: ");
        validarIngresoFlotante(&credito.importe);

        int tipo;
        printf("Seleccione el tipo de credito \n");
        printf("1. Con Garantia\n");
        printf("2. A solo firma\n");
        printf("Ingrese una opcion: ");
        validarIngresoEntero(&tipo);
        fflush(stdin);

        //printf("Ingrese el tipo de crédito: "); //hacer q elija entre dos opciones 1 o 2
        //ingresarTexto(credito.tipoCredito, MAX_NOMBRE);

        //El ingreso de la fecha es todo junto y en total tienen que ser 7 numeros en total
        printf("Ingrese la fecha de otorgamiento del crédito (dia mes anio): "); //ser mas claro con el orden de ingreso
        validarIngresoFecha(&credito.dia, &credito.mes, &credito.anio); //hace falta que ponga numero y se emita como texto

        printf("Ingrese la cantidad de cuotas: ");
        validarIngresoEntero(&credito.numCuotas);

        printf("Ingrese el importe de cada cuota: ");
        validarIngresoFlotante(&credito.importeCuota);

        printf("Ingrese el IVA: ");    //falta emitir el total de cuota cuando lo vaya a imprimir tiene que hacer el calculo
        validarIngresoFlotante(&credito.iva);

        credito.totalCuota = credito.importeCuota + credito.iva;
        credito.activo = 1;

        credito.orden = ultimoOrden + 1; // Asignamos el siguiente número de orden

        fwrite(&credito, sizeof(Credito), 1, pArchivo);
        fclose(pArchivo);

        printf("El crédito se ingresó correctamente.\n");
    } else {
        controlarError("No se pudo abrir el archivo 'creditos.dat'.");
    }
}

void buscarCliente() {   //9) Busqueda de cliente
    int opcion;          //La busqueda de clientes funciona, no emite el apellido, el mes trata de emitir con letras
                         //El activo no funciona correctamente
    printf("Seleccione una opción de búsqueda:\n");
    printf("1. Buscar por orden\n");
    printf("2. Buscar por nombre\n");
    printf("Ingrese el número de opción: ");
    validarIngresoEntero(&opcion);

    switch (opcion) {
        case 1:
            buscarCreditoPorOrden();
            break;
        case 2:
            buscarCreditoPorNombre();
            break;
        default:
            printf("Opción inválida. Por favor, seleccione una opción válida.\n");
            break;
    }
}

void buscarCreditoPorOrden() {
    int ordenBuscar;
    printf("Ingrese el número de orden: ");
    validarIngresoEntero(&ordenBuscar);

    FILE* pArchivo = fopen("creditos.dat", "rb");

    if (pArchivo != NULL) {
        Credito credito;
        bool encontrado = false;

        while (fread(&credito, sizeof(Credito), 1, pArchivo) == 1) {
            if (credito.orden == ordenBuscar) {
                imprimirCredito(credito);
                encontrado = true;
                break;
            }
        }

        fclose(pArchivo);

        if (!encontrado) {
            printf("No se encontró ningún crédito con el número de orden especificado.\n");
        }
    } else {
        controlarError("No se pudo abrir el archivo 'creditos.dat'.");
    }
}

void buscarCreditoPorNombre() {
    char nombreBuscar[MAX_NOMBRE];
    printf("Ingrese el nombre del cliente: ");
    ingresarTexto(nombreBuscar, MAX_NOMBRE);

    FILE* pArchivo = fopen("creditos.dat", "rb");

    if (pArchivo != NULL) {
        Credito credito;
        bool encontrado = false;

        while (fread(&credito, sizeof(Credito), 1, pArchivo) == 1) {
            if (strcmp(credito.nombre, nombreBuscar) == 0) {
                imprimirCredito(credito);
                encontrado = true;
            }
        }

        fclose(pArchivo);

        if (!encontrado) {
            printf("No se encontraron créditos para el cliente especificado.\n");
        }
    } else {
        controlarError("No se pudo abrir el archivo 'creditos.dat'.");
    }
}

void imprimirCredito(Credito credito) {
                printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
                printf("|  Orden |     Nombre      |   Apellido      | Importe   |Tipo de crédito  |Dia |   Mes   | Anio | Cuotas | Importe Cuota |   IVA   |   Total Cuota   | Activo |\n");
                printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("| %2d     | %15s | %15s | %9.2f | %15s | %02d | %02d | %04d | %6d | %13.2f |  %6.2f  | %15.2f | %6d |\n",   //falta activo
           credito.orden,
           credito.nombre,
           credito.apellido,
           credito.importe,
           credito.tipoCredito,
           credito.dia,
           credito.mess,
           credito.anio,
           credito.numCuotas,
           credito.importeCuota,
           credito.iva,
           credito.totalCuota),
           credito.activo;

    printf("-----------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
}

void modificarDatos() {    //10) Modificacion de datos
    int numeroOrden;
    FILE* pArchivo = fopen("creditos.dat", "r+b");

    if (pArchivo != NULL) {
        printf("Ingrese el numero de orden: ");
        validarIngresoEntero(&numeroOrden);

        Credito credito;
        bool encontrado = false;

        while (fread(&credito, sizeof(Credito), 1, pArchivo) == 1) {
            if (credito.orden == numeroOrden && credito.activo == 1) {
                encontrado = true;

                printf("\nDatos encontrados:\n");
                printf("Nombre: %s\n", credito.nombre);
                printf("Importe actual: %.2f\n", credito.importe);
                printf("Tipo de credito actual: %s\n", credito.tipoCredito);

                char confirmar;
                printf("¿Estas seguro que desea modificar los datos? (s = si / n = no): ");
                fflush(stdin);
                scanf("%c", &confirmar);
                fflush(stdin);

                if (confirmar == 's') {
                    printf("\nIngrese el nuevo importe: ");
                    validarIngresoFlotante(&credito.importe);

                    printf("Ingrese el nuevo tipo de crédito: ");
                    ingresarTexto(credito.tipoCredito, MAX_NOMBRE);

                    fseek(pArchivo, -sizeof(Credito), SEEK_CUR);
                    fwrite(&credito, sizeof(Credito), 1, pArchivo);
                    printf("\nDatos actualizados correctamente.\n");
                } else {
                    printf("\nOperación cancelada.\n");
                }

                break;
            }
        }

        if (!encontrado) {
            printf("No se encontró un crédito activo con el número de orden especificado.\n");
        }

        fclose(pArchivo);
    } else {
        controlarError("No se pudo abrir el archivo 'creditos.dat'.");
    }
}


void bajaLogica() {  //11) Baja logica por numuero de orden
    int numeroOrden;
    int orden;
    FILE*pArchivo = fopen("creditos.dat", "r+b");
    if (pArchivo != NULL) {
            Credito cliente;

            printf("Ingrese el numero de orden del cliente a dar de baja: "); // Realizar la búsqueda del cliente por número de orden
            validarIngresoEntero(&numeroOrden);
            orden = numeroOrden;  // Asignar el valor ingresado a la variable orden

            while (fread(&cliente, sizeof(Credito), 1, pArchivo) == 1) {
                    if (cliente.orden == orden) {
                        if (cliente.activo == 1) {
                            printf("\nCliente encontrado:\n");
                            printf("Orden: %d\n", cliente.orden);
                            printf("Nombre: %s\n", cliente.nombre);
                            printf("Apellido: %s\n", cliente.apellido);
                            printf("Importe: %.2f\n", cliente.importe);
                            printf("Tipo de crédito: %s\n", cliente.tipoCredito);
                            printf("Día: %d\n", cliente.dia);
                            printf("Mes: %d\n", cliente.mes);
                            printf("Anio: %d\n", cliente.anio);
                            printf("Numero de cuotas: %d\n", cliente.numCuotas);
                            printf("Importe de cuota: %.2f\n", cliente.importeCuota);
                            printf("IVA: %.2f\n", cliente.iva);
                            printf("Total de cuota: %.2f\n", cliente.totalCuota);

                            char confirmacion;
                            printf("\n¿Estas seguro que desea dar de baja a este cliente? (s/n): ");
                            fflush(stdin);
                            scanf("%c", &confirmacion);

                            if (confirmacion == 's') {
                                    cliente.activo = 0;
                                    fseek(pArchivo, -sizeof(Credito), SEEK_CUR);
                                    fwrite(&cliente, sizeof(Credito), 1, pArchivo);
                                    printf("\nCliente dado de baja correctamente.\n");
                            } else {
                                printf("\nOperacion cancelada. El cliente no ha sido dado de baja.\n");
                            }
                        } else {
                            printf("\nError: El cliente ya esta inactivo.\n");
                        }

                        fclose(pArchivo);
                        return;
                    }
                }

                printf("\nError: No se encontro un cliente con el número de orden especificado.\n");
                fclose(pArchivo);
            } else {
                printf("\nError en la apertura del archivo 'creditos.dat'.\n");
            }
}

void bajaFisica() {  //12) Baja física, clientes inactivos
    FILE* pArchivo = fopen("creditos.dat", "r+b");
    if (pArchivo == NULL) {
        controlarError("No se pudo abrir el archivo creditos.dat");
        return;
    }

    FILE* archivoTxt;
    char nombreArchivoTxt[100];

    // Obtener la fecha actual del sistema
    time_t t = time(NULL);
    struct tm* fechaActual = localtime(&t);

    // Construir el nombre del archivo de texto
    strftime(nombreArchivoTxt, sizeof(nombreArchivoTxt), "clientes_bajas_%Y%m%d%H%M%S.xyz", fechaActual);

    archivoTxt = fopen(nombreArchivoTxt, "w");
    if (archivoTxt == NULL) {
        controlarError("No se pudo crear el archivo de texto");
        fclose(pArchivo);
        return;
    }

    // Leer y procesar los registros del archivo binario
    Credito cliente;
    while (fread(&cliente, sizeof(Credito), 1, pArchivo) == 1) {
        if (cliente.activo == 0) {
            // Escribir los datos del cliente en el archivo de texto
            fprintf(archivoTxt, "Orden: %d\n", cliente.orden);
            fprintf(archivoTxt, "Nombre: %s\n", cliente.nombre);
            fprintf(archivoTxt, "Apellido: %s\n", cliente.apellido);
            fprintf(archivoTxt, "Importe: %.2f\n", cliente.importe);
            fprintf(archivoTxt, "Tipo de crédito: %s\n", cliente.tipoCredito);
            fprintf(archivoTxt, "Día: %d\n", cliente.dia);
            fprintf(archivoTxt, "Mes: %d\n", cliente.mes);
            fprintf(archivoTxt, "Año: %d\n", cliente.anio);
            fprintf(archivoTxt, "Número de cuotas: %d\n", cliente.numCuotas);
            fprintf(archivoTxt, "Importe de cuota: %.2f\n", cliente.importeCuota);
            fprintf(archivoTxt, "IVA: %.2f\n", cliente.iva);
            fprintf(archivoTxt, "Total de cuota: %.2f\n", cliente.totalCuota);
            fprintf(archivoTxt, "\n");
        }
    }

    // Marcar los campos del cliente como 0 en el archivo binario
    rewind(pArchivo);
    while (fread(&cliente, sizeof(Credito), 1, pArchivo) == 1) {
        if (cliente.activo == 0) {
            cliente.orden = 0;
            cliente.activo = 0;
            fseek(pArchivo, -sizeof(Credito), SEEK_CUR);
            fwrite(&cliente, sizeof(Credito), 1, pArchivo);
        }
    }

    fclose(pArchivo);
    fclose(archivoTxt);
}


void listarXyz() {  //13) Lista de clientes baja con fecha
    FILE* archivoTxt;
    char nombreArchivoTxt[100];

    // Obtener la fecha actual del sistema
    time_t t = time(NULL);
    struct tm* fechaActual = localtime(&t);

    // Construir el nombre del archivo de texto
    strftime(nombreArchivoTxt, sizeof(nombreArchivoTxt), "clientes_bajas_%Y%m%d%H%M%S.xyz", fechaActual);

    archivoTxt = fopen(nombreArchivoTxt, "r");
    if (archivoTxt == NULL) {
        controlarError("No se pudo abrir el archivo de texto");
        return;
    }

    char linea[100];
    while (fgets(linea, sizeof(linea), archivoTxt) != NULL) {
        printf("%s", linea);  // Imprimir cada línea del archivo de texto
    }

    fclose(archivoTxt);
}

//El menu principal con el que va a interactuar el usuario
void menu() {
    int opcion;
    char preg='n';
    char confirm;
    do {
        printf("\n======== Menu de opciones ===========\n");
        printf("1.  Listar txt\n");
        printf("2.  Crear archivo binario\n");
        printf("3.  Migrar datos\n");
        printf("4.  Listar dat\n");
        printf("5.  Alta cliente\n");
        printf("6.  Buscar cliente\n");
        printf("7.  Modificar datos\n");
        printf("8.  Baja logica\n");
        printf("9.  Baja fisica\n");
        printf("10. Listar xyz\n");
        printf("0.  Salir\n");
        printf("=====================================\n");
        printf("\nIngrese el numero de opcion: ");
        fflush(stdin);
        validarIngresoEntero(&opcion);

        switch (opcion) {
            case 1:
                listarTxt();
                break;
            case 2:
					do{ printf("ATENCION!: Se esta por crear un nuevo archivo 'creditos.dat'\nSi el archivo existe se perdera la informacion anterior.\n\nDesea continuar?...\n's' = si / 'n' = no : ");
						fflush(stdin);
						scanf("%c",&confirm);
                    }while(!((confirm=='s')||(confirm=='n')));
                    if(confirm=='s'){crearArchivoBinario();}else{printf("Operacion abortada, no se produjo ningun cambio.\n");}
                    break;
            case 3:
                migrarDatos();
                printf("Los datos del archivo 'prestamos.csv' se migraron correctamente a 'creditos.bat'\n ");
                printf("\nATENCION!: Se agrego un nuevo campo llamado 'activo'!\n");
                printf("ATENCION!: Ahora los meses estan registrados con letras!\n");
                printf("ATENCION!: Los nombres y los apellidos ahora se encuentran separados!\n");
                break;
            case 4:
                listarDat();
                break;
            case 5:
                altaCliente();
                break;
            case 6:
                buscarCliente();
                break;
            case 7:
                modificarDatos();
                break;
            case 8:
                bajaLogica();
                break;
            case 9:
                bajaFisica();
                break;
            case 10:
                listarXyz();
                break;
            case 0:
                printf("¿Está seguro de que desea salir? (s/n): ");
                fflush(stdin);
                scanf("%c", &preg);
                if (preg == 's') {
                    printf("Saliendo del programa...\n");
                } else if (preg == 'n') {
                    opcion = -1;
                } else {
                    printf("Opción inválida. Continuando en el programa...\n");
                    opcion = -1;
                }
                break;
            default:
                printf("Opción inválida. Por favor, elija una opción válida del menú.\n");
                break;
        }
    } while (opcion != 0 && preg != 's');

    return 0;
}
