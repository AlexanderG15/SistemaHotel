
/*Mi sistema es para uso interno de un hotel, donde el empleado realiza la reservacion y registro
del cliente, fue implementado usando listas doblemente ligadas circulares o cerradas, se muestran
los precios de las habitaciones, el programa calcula el costo y desgloza en iva, desayuno, noches etc.
si la persona paga con tarjeta de credito, se piden algunos datos extras, como banco y tipo de tarjeta,
use estructuras de estructura, para hacer las cuentas y para cuando paguen con tarjeta, 
los precios estan declarados como constantes. LA INFORMACION SE GUARDA EN UN ARCHIVO .TXT
NOMBRE: ISAURA RIZO
FECHA 18 DE MAYO
OBJETIVO: PONER EN PRACTICA LISTAS DOBLEMENTE CIRCULARES/CERRADAS
*/


#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h> //isalpha e isdigit
#include<fstream>
//CONSTANTES PARA LOS PRECIOS
#define STANDAR 550
#define COMPARTIDA 220
#define SUITE 900
#define DESAYUNO 50

using namespace std;
//Aqui defino mi TDA

struct cuenta{
	float total,subtotal,iva,desayuno;
	int noches;
};

struct tarjeta{
	char bancos,visa;
};

struct clientes{
	char nombres[30];
	char apellidoP[20];
	char apellidoM[20];
	int habitacion;
	bool desayuno;
	bool tdc;
	tarjeta mitarjeta;
	cuenta pagar;
	struct clientes *siguiente;
	struct clientes *anterior;
};

	 //inicializo mi apuntador a lista
	 struct clientes *LISTA=NULL; // apuntador es igual a lista 
	 int sw=0,validandoL;
	 
//prototipos 
void agregar(void);
void consultarAtras(void);
void consultarAdelante(void);
void eliminar(void);
void buscar(void);
void minuscula(char *);
void guardar(void);
int validarNum(char numero[10]);
int validarCadenas(char cadena[50]);


int main(){
	
	//declaro convertir como entero 
	int convertir;
	char opcion[2]; // lo declaro como char para
					// poder hacer la validacion de que solo ingrese numeros usando strlen
					
			
	do{
		system("cls");
		cout<<"\n\n";
		cout<<"\t\t-----------------------------------"<<endl;
		cout<<"\t\t|     HOTEL  EL MOCHILERO         |"<<endl;
		cout<<"\t\t-----------------------------------"<<endl;
		cout<<"\n\n";
		cout<<"\t\tOPERACION\t\t\tCODIGO"<<endl;
		cout<<"\t\t--------------------------------------"<<endl;
		cout<<endl;
		cout<<"\t\tREGISTRO DE CLIENTE................[1]"<<endl;
		cout<<endl;
		cout<<"\t\tCONSULTAR RESERVACION AL INICIO....[2]"<<endl;
		cout<<endl;
		cout<<"\t\tCONSULTAR RESERVACION EL FINAL.....[3]"<<endl;
		cout<<endl;
		cout<<"\t\tCANCELACION DE RESERVACION.........[4]"<<endl;
		cout<<endl;
		cout<<"\t\tBUSCAR RESERVACION.................[5]"<<endl;
		cout<<endl;
		cout<<"\t\tCERRAR SISTEMA.....................[6]"<<endl;
		cout<<endl;
		cout<<"\t\t--------------------------------------"<<endl;
		cout<<"\t\tINGRESE LA OPCION: ";cin>>opcion;
		system("cls");
		
		//valido que ingrese numero y no pueda ingresar otro tipo de dato
		
		sw=validarNum(opcion);
		if(sw!=0){
				cout<<"\t\tINGRESE NUMERO 1-6"<<endl;
				}	
		//====================================================	
			
		
		//con atoi paso lo que tiene variable CHAR opcion a la variable INT convertir para poder usarla en el switch ya que solo se puede con int
		convertir = atoi(opcion); 
		//===========================
		switch(convertir){
			case 1:
				agregar();
				break;
			case 2:
				consultarAtras();
				break;	
			case 3:
				consultarAdelante();
				break;
			case 4:
				eliminar();
				break;
			case 5:
				buscar();
				break;	
			case 6:
				cout<<"\t\tGRACIAS POR USAR EL SISTEMA"<<endl;
				break;				
			default:
				cout<<"\t\tESTA OPCION NO ES VALIDA"<<endl;
				break;
	}//switch
	system("pause");
	}while(convertir!=6);
	return 0;	
}//fin main

//===============================================================
int validarCadenas(char cadena[50]){
	int i=0, validandoL=0, j;
	j=strlen(cadena); //se asigna el numero de caracteres que tiene la cadena a J
	
	while(i<j&&validandoL==0){
	
		if(isalpha(cadena[i])!=0||cadena[i]==32) // 32 para que acepte espacios tambien 
		{
			i++; //si es una letra avanza de lo contrario entra al else para salirse del ciclo
		}else{
			validandoL=1;
		}	
	}	
 return validandoL;
}
//===============================================================
//funcion que valida que solo sean numeros 
int validarNum(char numero[10]){

	int i=0,sw=0,j;
	j=strlen(numero);
	
	while(i<j &&sw==0){
		if(isdigit(numero[i])!=0){
			i++;
		}else{
			sw=1;
		}
	}
	return sw;
}//fin funcion
//===============================================================
void minuscula(char *cadena){
   int largo;
   largo = strlen(cadena);
   for (int i=0; i<largo; i++)
     cadena[i]=tolower(cadena[i]) ;	
   return;
}
//===============================================================
void buscar(void){
	//declarar e inicializar apuntador
	struct clientes *copia=LISTA;
	char opcionBuscar[2];
	int convertir;
	//validamos que no este vacia
		if(copia==NULL){
			cout<<"\t\t NO HAY RESERVACIONES REGISTRADAS"<<endl;
			return;
		}
		//consultar
		
		//switch para elegir como vamos a buscar 
		cout << "\t\t\t---------------------------" << endl;
		cout << "\t\t\t|BUSQUEDA DE RESERVACIONES|" << endl;
		cout << "\t\t\t---------------------------" << endl;
		cout<<"\n\n";
		
		cout<<"\t\t-----------------------------" << endl;
		cout<<"\t\tPOR NOMBRE................[1]"<<endl;
		cout<<"\t\tPOR APELLIDOS.............[2]"<<endl;
		cout<<"\t\tTIPO DE HABITACION........[3]"<<endl;
		cout<<"\t\tPOR PAGO CON TARJETA......[4]"<<endl;
		cout<<"\t\t-----------------------------" << endl;
		cout<<"\t\tINGRESE LA OPCION:";cin>>opcionBuscar;
		//funcion para que solo pueda ingresar numeros
		int sw=0;
		sw=validarNum(opcionBuscar);
		if(sw!=0){
				cout<<"\t\tINGRESE NUMERO 1-4";
		}	
		
		// convierto a entero el char para poder usarlo en el swich
		convertir = atoi(opcionBuscar);
		
		system("cls");
		switch(convertir){
			case 1:	
					char nombre[30];
					char resp; //para preguntar si desea regresar 
					do{
					
					cout << "\t\t\t--------------------------" << endl;
					cout << "\t\t\t|      RESERVACIONES     |" << endl;
					cout << "\t\t\t--------------------------" << endl;
					cout<<"\t\tNOMBRE: ";
					fflush(stdin);
					cin.getline(nombre,30);
					fflush(stdin);
					minuscula(nombre);
					do{	
					if(strcmp(copia->nombres,nombre)==0){
						cout<<endl;
						cout<<"\t\t|NOMBRES: "<<copia->nombres<<endl;
						cout<<"\t\t|APELLIDO PATERNO: "<<copia->apellidoP<<endl;
						cout<<"\t\t|APELLIDO MATERNO: "<<copia->apellidoM<<endl;
						cout<<"\t\t|TIPO DE HABITACION: "<<copia->habitacion<<endl;
						cout<<"\t\t|DESAYUNO INCLUIDO [1]SI [0]N0: "<<copia->desayuno<<endl;
						cout<<"\t\t|PAGO CON TDC [1]SI [0]N0: "<<copia->tdc<<endl;
						if(copia->tdc==1){
						cout<<"\t\t|BANCO: "<<copia->mitarjeta.bancos<<endl;
						cout<<"\t\t|TIPO: "<<copia->mitarjeta.visa<<endl;	
						}
						cout<<"\t\t*********************************" << endl;
					}
					copia=copia->siguiente;
					}while(copia!=LISTA);
					cout<<"\t\tVOLVER A BUSCAR POR NOMBRE? s/S: "; cin>>resp;
					system("cls");
					}while(resp=='s'||resp=='S');
					
					
					return;
					break;
					
			
			case 2:	
					
					char apellidos[20];
					
					do{
					cout << "\t\t\t--------------------------" << endl;
					cout << "\t\t\t|      RESERVACIONES     |" << endl;
					cout << "\t\t\t--------------------------" << endl;
			
					cout<<"\t\tAPELLIDO: ";
					fflush(stdin);
					cin.getline(apellidos,20);
					fflush(stdin);
					minuscula(apellidos);
					do{
					if(strcmp(copia->apellidoP,apellidos)==0||strcmp(copia->apellidoM,apellidos)==0){
						cout<<endl;
						cout<<"\t\t|NOMBRES: "<<copia->nombres<<endl;
						cout<<"\t\t|APELLIDO PATERNO: "<<copia->apellidoP<<endl;
						cout<<"\t\t|APELLIDO MATERNO: "<<copia->apellidoM<<endl;
						cout<<"\t\t|TIPO DE HABITACION: "<<copia->habitacion<<endl;
						cout<<"\t\t|DESAYUNO INCLUIDO [1]SI [0]N0: "<<copia->desayuno<<endl;
						cout<<"\t\t|PAGO CON TDC [1]SI [0]N0: "<<copia->tdc<<endl;
						if(copia->tdc==1){
						cout<<"\t\t|BANCO: "<<copia->mitarjeta.bancos<<endl;
						cout<<"\t\t|TIPO: "<<copia->mitarjeta.visa<<endl;	
						
						}
						cout<<"\t\t*********************************" << endl;
						}

						copia=copia->siguiente;
					}while(copia!=LISTA);
					
					cout<<"\t\tVOLVER A BUSCAR POR APELLIDO? s/S: "; cin>>resp;
					system("cls");
					}while(resp=='s'||resp=='S');
					return;
					break;	
					
			case 3:	
			
					int tipo;
					do{
					
					cout << "\t\t\t--------------------------" << endl;
					cout << "\t\t\t|      RESERVACIONES     |" << endl;
					cout << "\t\t\t--------------------------" << endl;
					do{
					cout<<"\t\tTIPO DE HABITACION: ";cin>>tipo;
					}while(tipo<1||tipo>3);
					do{
					if(copia->habitacion==tipo){
						cout<<endl;
						cout<<"\t\t|NOMBRES: "<<copia->nombres<<endl;
						cout<<"\t\t|APELLIDO PATERNO: "<<copia->apellidoP<<endl;
						cout<<"\t\t|APELLIDO MATERNO: "<<copia->apellidoM<<endl;
						cout<<"\t\t|TIPO DE HABITACION: "<<copia->habitacion<<endl;
						cout<<"\t\t|DESAYUNO INCLUIDO [1]SI [0]N0: "<<copia->desayuno<<endl;
						cout<<"\t\t|PAGO CON TDC [1]SI [0]N0: "<<copia->tdc<<endl;
						if(copia->tdc==1){
						cout<<"\t\t|BANCO: "<<copia->mitarjeta.bancos<<endl;
						cout<<"\t\t|TIPO: "<<copia->mitarjeta.visa<<endl;	
						}
						cout<<"\t\t*********************************" << endl;
						}else{
							cout<<"\t\tNO HAY REGISTROS DE ESTE TIPO"<<endl;
						}	
						copia=copia->siguiente;
					}while(copia!=LISTA);
					
					cout<<"\t\tVOLVER A BUSCAR POR TIPO? s/S: "; cin>>resp;
					system("cls");
					}while(resp=='s'||resp=='S');
					return;
					break;	
						
			case 4: 
					    cout <<"\t\t\t----------------------------" << endl;
						cout <<"\t\t\t| RESERVACIONES CON TARJETA |" << endl;
						cout <<"\t\t\t----------------------------" << endl;
					do{	
					if(copia->tdc==1){
						cout<<endl;
						cout<<"\t\t|NOMBRES: "<<copia->nombres<<endl;
						cout<<"\t\t|APELLIDO PATERNO: "<<copia->apellidoP<<endl;
						cout<<"\t\t|APELLIDO MATERNO: "<<copia->apellidoM<<endl;
						cout<<"\t\t|TIPO DE HABITACION: "<<copia->habitacion<<endl;
						cout<<"\t\t|DESAYUNO INCLUIDO [1]SI [0]N0: "<<copia->desayuno<<endl;
						cout<<"\t\t|PAGO CON TDC [1]SI [0]N0: "<<copia->tdc<<endl;
						if(copia->tdc==1){
						cout<<"\t\t|BANCO: "<<copia->mitarjeta.bancos<<endl;
						cout<<"\t\t|TIPO: "<<copia->mitarjeta.visa<<endl;	
						}
						cout<<"\t\t*********************************" << endl;
					}
					copia=copia->siguiente;
					}while(copia!=LISTA);
					return;
					break;
						
					default:
						cout<<"\t\tOPCION NO VALIDA"<<endl;
						
		}//switch
		
}//fin buscar
//===============================================================
void eliminar(void){
	// Declarar e inicializar apuntador
	struct clientes *borrar=LISTA;
	char resp;
	
	// Validar no este vacía
	if ( borrar == NULL ) {
		cout << "\t\tNO HAY CLIENTES REGISTRADOS" << endl;
		return;
	}
	
	// Eliminar
	// a) Un único nodo
	if ( LISTA == LISTA->siguiente) {
	cout << "\t\t\t------------------------------" << endl;
	cout << "\t\t\t|CANCELACION DE RESERVACIONES|" << endl;
	cout << "\t\t\t------------------------------" << endl;
	cout<<"\n\n";	
	
	cout<<"\t\t|NOMBRES: "<<borrar->nombres<<endl;
	cout<<"\t\t|APELLIDO PATERNO: "<<borrar->apellidoP<<endl;
	cout<<"\t\t|APELLIDO MATERNO: "<<borrar->apellidoM<<endl;
	cout<<"\t\t|TIPO DE HABITACION "<<borrar->habitacion<<endl;
	cout<<"\t\t|[1]STANDAR            |$550"<<endl;
	cout<<"\t\t|[2]COMPARTIDA         |$220"<<endl;
	cout<<"\t\t|[3]SUITE              |$900"<<endl;
	cout<<"\t\t|DESAYUNO INCLUIDO (1-SI 0-N0):"<<borrar->desayuno<<endl;
	cout<<"\t\t|PAGO CON TARJETA (1-SI 0-N0):"<<borrar->tdc<<endl;
	cout<<"\t\t********************************" << endl;
    cout<<"\t\tSEGURO QUE DESEA ELIMINARLO? (S/s): "; cin >> resp;
     
      if ( resp=='S' || resp=='s') {
      	 LISTA=NULL;
      	 free(borrar);
      	 cout <<"\t\tREGISTRO ELIMINADO..." << endl;
      	 system("pause");
	  } // if
	  return;
	} // if
	
	// 2 ó más nodos
	do {
	cout << "\t\t\t------------------------------" << endl;
	cout << "\t\t\t|CANCELACION DE RESERVACIONES|" << endl;
	cout << "\t\t\t------------------------------" << endl;
	cout<<"\n\n";	
	
	cout<<"\t\t|NOMBRES: "<<borrar->nombres<<endl;
	cout<<"\t\t|APELLIDO PATERNO: "<<borrar->apellidoP<<endl;
	cout<<"\t\t|APELLIDO MATERNO: "<<borrar->apellidoM<<endl;
	cout<<"\t\t|TIPO DE HABITACION "<<borrar->habitacion<<endl;
	cout<<"\t\t|[1]STANDAR            |$550"<<endl;
	cout<<"\t\t|[2]COMPARTIDA         |$220"<<endl;
	cout<<"\t\t|[3]SUITE              |$900"<<endl;
	cout<<"\t\t|DESAYUNO INCLUIDO (1-SI 0-N0):"<<borrar->desayuno<<endl;
	cout<<"\t\t|PAGO CON TARJETA (1-SI 0-N0):"<<borrar->tdc<<endl;
	cout<<"\t\t********************************" << endl;
	
    cout<<"\t\tSEGURO QUE DESEA ELIMINARLO? (S/s): "; cin >> resp;
      if ( resp=='S' || resp=='s') {
         while ( LISTA->siguiente != borrar ) {		 
              LISTA=LISTA->siguiente;
         }
         LISTA->siguiente = LISTA->siguiente->siguiente;
         LISTA->siguiente->siguiente->anterior = LISTA;
         free(borrar);
         cout <<"\t\tREGISTRO ELIMINADO" << endl;
         return;
	  } // if 
	  borrar=borrar->siguiente;	
	} while ( LISTA != borrar);
	cout << "\t\tTODOS LOS CLIENTES FUERON MOSTRADOS..." << endl;
	return;
} // eliminar	
//===============================================================
void consultarAdelante(void){
	
	// Declararamos e inicializar variable apuntador
	struct clientes *copia=LISTA;
	
	// Validar no este vacía
	// Validar no este vacía
	if ( copia == NULL ) {
		cout << "\t\tNO HAY CLIENTES REGISTRADOS" << endl;
		return;
	}
	
	// Imprimir la lista
	cout << "\t\t\t--------------------------" << endl;
	cout << "\t\t\t|      RESERVACIONES     |" << endl;
	cout << "\t\t\t--------------------------" << endl;
	do {
	cout<<endl;	
	cout<<"\t\t--------------------------------------------"<<endl;
	cout<<"\t\tNombres: "<<copia->nombres<<endl;
	cout<<"\t\tApellido paterno: "<<copia->apellidoP<<endl;
	cout<<"\t\tApellido materno: "<<copia->apellidoM<<endl;
	
	cout<<endl;
	if(copia->habitacion==1){
		cout<<"\t\tHabitacion: Standar"<<endl;
	}else{
		if(copia->habitacion==2){
			cout<<"\t\tHabitacion: Compartida"<<endl;	
		}else{
				cout<<"\t\tHabitacion: Suite"<<endl;				
		}
	}
	
	if(copia->desayuno==1){
	cout<<"\t\tDesayuno: Incluido"<<endl;
	}else{
		cout<<"\t\tDesayuno: No incluido"<<endl;
	}
		if(copia->tdc==1){
		cout<<"\t\tMetodo de pago: Tarjeta"<<endl;
		cout<<"\t\tBanco:"<<copia->mitarjeta.bancos<<endl;
		cout<<"\t\tTipo:"<<copia->mitarjeta.visa<<endl;	
	}else{
		cout<<"\t\tMetodo de pago: Efectivo"<<endl;
	}
	cout<<"\t\t--------------------------------------------"<<endl;
    copia=copia->siguiente;
	} while( copia != LISTA);
	return;
} 
 // consultarAdelante
//===============================================================
void consultarAtras(void){
	
	// Declararamos e inicializar variable apuntador
	struct clientes *copia=LISTA;
	
	// Validar no este vacía
	// Validar no este vacía
	if ( copia == NULL ) {
		cout << "\t\tNO HAY CLIENTES REGISTRADOS" << endl;
		return;
	}
	
	// Imprimir la lista
	cout << "\t\t\t--------------------------" << endl;
	cout << "\t\t\t|      RESERVACIONES     |" << endl;
	cout << "\t\t\t--------------------------" << endl;
	do {
	cout<<endl;	
	cout<<"\t\t--------------------------------------------"<<endl;
	cout<<"\t\tNombres: "<<copia->nombres<<endl;
	cout<<"\t\tApellido paterno: "<<copia->apellidoP<<endl;
	cout<<"\t\tApellido materno: "<<copia->apellidoM<<endl;
	
	cout<<"\t\tNoches: "<<copia->pagar.noches;
	
	cout<<endl;
	if(copia->habitacion==1){
		cout<<"\t\tHabitacion: Standar"<<endl;
	}else{
		if(copia->habitacion==2){
			cout<<"\t\tHabitacion: Compartida"<<endl;	
		}else{
				cout<<"\t\tHabitacion: Suite"<<endl;				
		}
	}
	
	if(copia->desayuno==1){
	cout<<"\t\tDesayuno: Incluido"<<endl;
	}else{
		cout<<"\t\tDesayuno: No incluido"<<endl;
	}
		if(copia->tdc==1){
		cout<<"\t\tMetodo de pago: Tarjeta"<<endl;
		cout<<"\t\tBanco:"<<copia->mitarjeta.bancos<<endl;
		cout<<"\t\tTipo:"<<copia->mitarjeta.visa<<endl;	
	}else{
		cout<<"\t\tMetodo de pago: Efectivo"<<endl;
	}
	cout<<"\t\t--------------------------------------------"<<endl;
    copia=copia->anterior;
	} while( copia != LISTA);
	return;
} // consultarAtras()
//===============================================================
void agregar(void){
	//1 declarar el apuntador
	
	ofstream apArchivo;  
	apArchivo.open("C:/Users/Ysa/Desktop/datos.txt", ios::app); //esta linea se cambia por la direccion donde quieres que se guarde el archivo txt
																//si no la cambias no abrira
    if ( ! apArchivo ) {
        cout << "Problema al abrir archivo --> datos.txt" <<endl;
        return ;
    } // if
	
	struct clientes *nuevo;
	int i=0; //rcorrer nombre
	//2 reservar memoria
	nuevo=new(clientes);
	// 3 validar el apuntador
	if(nuevo==NULL){
		cout<<"\t\t\tNO HAY MEMORIA SUFICIENTE"<<endl;
		return;
	} 
	
	// 4 Solicitar datos de la nueva computadora
	cout<<"\t\t\t-------------------"<<endl;
	cout<<"\t\t\t|REGISTRO DE DATOS|"<<endl;
	cout<<"\t\t\t-------------------"<<endl;
	cout<<endl;
	
	do{
	cin.clear();		
	fflush(stdin);
	cout<<"\t\t|NOMBRE: ";
	cin.getline(nuevo->nombres,30);
	minuscula(nuevo->nombres); //funcion para convertir todo a minusculas
	validandoL=validarCadenas(nuevo->nombres); //funcion para validar que solo ingrese letras
	}while(validandoL!=0); //mientras validandoL sea diferente a 0 eso significa que ingreso algo que no es una letra
						  //entonces lo vuelve a solicitar
	
	do{
	cin.clear();
	fflush(stdin);
	cout<<"\t\t|APELLIDO PATERNO: ";
	cin.getline(nuevo->apellidoP,20);
	minuscula(nuevo->apellidoP);
	validandoL=validarCadenas(nuevo->apellidoP); //funcion para validar que solo ingrese letras
	}while(validandoL!=0);
	
	do{
	cin.clear();
	fflush(stdin);
	cout<<"\t\t|APELLIDO MATERNO: ";
	cin.getline(nuevo->apellidoM,20);
	fflush(stdin);
	minuscula(nuevo->apellidoM);
	validandoL=validarCadenas(nuevo->apellidoM);//funcion para validar que solo ingrese letras
	}while(validandoL!=0);
	
	do{
	cin.clear();
    fflush(stdin);
	cout<<"\t\t|NOCHES: ";
	cin>>nuevo->pagar.noches;
	if(nuevo->pagar.noches>31||nuevo->pagar.noches<1){
	cout<<"\t\tINGRESE NUMERO ENTRE 1 Y 31"<<endl;
	}
	}while(nuevo->pagar.noches<1||nuevo->pagar.noches>90||cin.fail()); //SE CICLA CUANDO INGRESO NUMEROS Y LETRAS

	do{	
	cin.clear();
	fflush(stdin);	
	cout<<"\t\t|---------------------------\n";
	cout<<"\t\t|HABITACION"<<endl;
	cout<<"\t\t|[1]Standar            |$550"<<endl;
	cout<<"\t\t|[2]Compartida         |$220"<<endl;
	cout<<"\t\t|[3]Suite              |$900"<<endl;
	cout<<"\t\t|-------------------------- ";
	cin>>nuevo->habitacion;
	if(nuevo->habitacion<1||nuevo->habitacion>3||cin.fail()){
	cout<<"\t\tINGRESE NUMERO ENTRE 1 Y 3"<<endl;
	}
	}while(nuevo->habitacion<1||nuevo->habitacion>3||cin.fail());

	do{
	cin.clear();
	fflush(stdin);
	cout<<"\t\t|DESAYUNO INCLUIDO $50"<<endl;
	cout<<"\t\t|[1]SI [0]N0--------------- ";
	cin>>nuevo->desayuno;
	if(nuevo->desayuno>1||nuevo->desayuno<0||cin.fail()){
	cout<<"\t\tINGRESE 0 o 1"<<endl;
	}
	}while(nuevo->desayuno<0||nuevo->desayuno>1||cin.fail());
	
	do{
	cin.clear();
	fflush(stdin);	
	cout<<"\t\t|TARJETA[1] EFECTIVO[0]---- ";
	cin>>nuevo->tdc;
	if(nuevo->tdc>1||nuevo->tdc<0||cin.fail()){
	cout<<"\t\tINGRESE 0 o 1"<<endl;
	}
	}while(nuevo->tdc<0||nuevo->tdc>1||cin.fail());
	if(nuevo->tdc==1){	
		do{
		cout<<"\t\t|\tBANCO"<<endl;	
		cout<<"\t\t|CitiBanamex............[C]"<<endl;
		cout<<"\t\t|Santander..............[S]"<<endl;
		cout<<"\t\t|Bancomer...............[B]"<<endl;
		cout<<"\t\t|-------------------------- ";cin>>nuevo->mitarjeta.bancos;
		
		
		}while(nuevo->mitarjeta.bancos!='C'&&nuevo->mitarjeta.bancos!='c'&&nuevo->mitarjeta.bancos!='s'&&nuevo->mitarjeta.bancos!='S'&&nuevo->mitarjeta.bancos!='b'&&nuevo->mitarjeta.bancos!='B');
		
		do{
		cout<<"\t\t|[V]VISA [M]MASTER"<<endl;
		cout<<"\t\t|-------------------------- ";cin>>nuevo->mitarjeta.visa;
		}while(nuevo->mitarjeta.visa!='v'&&nuevo->mitarjeta.visa!='V'&&nuevo->mitarjeta.visa!='m'&&nuevo->mitarjeta.visa!='M');
		}
		
		//******************************************************************************
		//if para sacar las cuentas 
		if(nuevo->habitacion==1&&nuevo->desayuno==1){	
		nuevo->pagar.desayuno=DESAYUNO*nuevo->pagar.noches;
		nuevo->pagar.iva=(nuevo->pagar.noches*STANDAR)*.16;
		nuevo->pagar.subtotal=nuevo->pagar.noches*STANDAR;
		nuevo->pagar.total=(nuevo->pagar.iva+nuevo->pagar.subtotal)+nuevo->pagar.desayuno;
		cout<<endl;
	
		cout<<"\t\t|***** CUENTA A PAGAR ***** "<<endl;
		cout<<"\t\t|NOCHES:"<<nuevo->pagar.subtotal<<endl;
		cout<<"\t\t|IVA: "<<nuevo->pagar.iva<<endl;
		cout<<"\t\t|DESAYUNO:"<<	nuevo->pagar.desayuno<<endl;
		cout<<"\t\t|TOTAL: "<<nuevo->pagar.total<<endl;
		}else{
			if(nuevo->habitacion==1&&nuevo->desayuno==0){
					nuevo->pagar.iva=(nuevo->pagar.noches*STANDAR)*.16;
					nuevo->pagar.subtotal=nuevo->pagar.noches*STANDAR;
					nuevo->pagar.total=(nuevo->pagar.iva+nuevo->pagar.subtotal);
					cout<<endl;
					cout<<"\t\t|***** CUENTA A PAGAR ***** "<<endl;
					cout<<"\t\t|NOCHES:"<<nuevo->pagar.subtotal<<endl;
					cout<<"\t\t|IVA: "<<nuevo->pagar.iva<<endl;
					cout<<"\t\t|TOTAL: "<<nuevo->pagar.total<<endl;	
			}	
		}
		if(nuevo->habitacion==2&&nuevo->desayuno==1){	
		nuevo->pagar.desayuno=DESAYUNO*nuevo->pagar.noches;
		nuevo->pagar.iva=(nuevo->pagar.noches*COMPARTIDA)*.16;
		nuevo->pagar.subtotal=nuevo->pagar.noches*COMPARTIDA;
		nuevo->pagar.total=(nuevo->pagar.iva+nuevo->pagar.subtotal)+nuevo->pagar.desayuno;
		cout<<endl;
		cout<<"\t\t|***** CUENTA A PAGAR ***** "<<endl;
		cout<<"\t\t|NOCHES:"<<nuevo->pagar.subtotal<<endl;
		cout<<"\t\t|IVA: "<<nuevo->pagar.iva<<endl;
		cout<<"\t\t|DESAYUNO:"<<	nuevo->pagar.desayuno<<endl;
		cout<<"\t\t|TOTAL: "<<nuevo->pagar.total<<endl;
		}else{
			if(nuevo->habitacion==2&&nuevo->desayuno==0){
					nuevo->pagar.iva=(nuevo->pagar.noches*COMPARTIDA)*.16;
					nuevo->pagar.subtotal=nuevo->pagar.noches*COMPARTIDA;
					nuevo->pagar.total=(nuevo->pagar.iva+nuevo->pagar.subtotal);
						cout<<endl;
						cout<<"\t\t|***** CUENTA A PAGAR ***** "<<endl;
						cout<<"\t\t|NOCHES:"<<nuevo->pagar.subtotal<<endl;
						cout<<"\t\t|IVA: "<<nuevo->pagar.iva<<endl;
						cout<<"\t\t|TOTAL: "<<nuevo->pagar.total<<endl;
			}	
		}
		if(nuevo->habitacion==3&&nuevo->desayuno==1){	
		nuevo->pagar.desayuno=DESAYUNO*nuevo->pagar.noches;
		nuevo->pagar.iva=(nuevo->pagar.noches*SUITE)*.16;
		nuevo->pagar.subtotal=nuevo->pagar.noches*SUITE;
		nuevo->pagar.total=(nuevo->pagar.iva+nuevo->pagar.subtotal)+nuevo->pagar.desayuno;
		cout<<endl;
		cout<<"\t\t|***** CUENTA A PAGAR ***** "<<endl;
		cout<<"\t\t|NOCHES:"<<nuevo->pagar.subtotal<<endl;
		cout<<"\t\t|IVA: "<<nuevo->pagar.iva<<endl;
		cout<<"\t\t|DESAYUNO:"<<	nuevo->pagar.desayuno<<endl;
		cout<<"\t\t|TOTAL: "<<nuevo->pagar.total<<endl;
		}else{
			if(nuevo->habitacion==3&&nuevo->desayuno==0){
					nuevo->pagar.iva=(nuevo->pagar.noches*SUITE)*.16;
					nuevo->pagar.subtotal=nuevo->pagar.noches*SUITE;
					nuevo->pagar.total=(nuevo->pagar.iva+nuevo->pagar.subtotal);
					cout<<endl;
						cout<<"\t\t|***** CUENTA A PAGAR ***** "<<endl;
						cout<<"\t\t|NOCHES:"<<nuevo->pagar.subtotal<<endl;
						cout<<"\t\t|IVA: "<<nuevo->pagar.iva<<endl;
						cout<<"\t\t|TOTAL: "<<nuevo->pagar.total<<endl;
			}	
		}
		
	
	//5) actualizar apuntadores y agregarlo a la lista
	//a) lista vacia
	if(LISTA==NULL){
		nuevo->siguiente=nuevo;
		nuevo->anterior=nuevo;
		LISTA=nuevo; //con esto se agrega el nodo
	}else{
		//asi se guarda y actualiza 
		nuevo->siguiente=LISTA->siguiente;
		nuevo->anterior=LISTA;
		//==================================
		LISTA->siguiente->anterior=nuevo;
		LISTA->siguiente=nuevo;		
	}//if else
	cout<<"\t\tRESERVACION EXITOSA!"<<endl;
	//*****************************************************************************************
	
	struct clientes *copia=LISTA;	
	// Imprimir la lista
	apArchivo << "\t\t\t--------------------------" << endl;
	apArchivo << "\t\t\t|      RESERVACIONES     |" << endl;
	apArchivo	<< "\t\t\t--------------------------" << endl;
	do {
	apArchivo<<endl;	
	apArchivo<<"\t\t--------------------------------------------"<<endl;
	apArchivo<<"\t\tNombres: "<<copia->nombres<<endl;
	apArchivo<<"\t\tApellido paterno: "<<copia->apellidoP<<endl;
	apArchivo<<"\t\tApellido materno: "<<copia->apellidoM<<endl;
	
	apArchivo<<endl;
	if(copia->habitacion==1){
		apArchivo<<"\t\tHabitacion: Standar"<<endl;
	}else{
		if(copia->habitacion==2){
			apArchivo<<"\t\tHabitacion: Compartida"<<endl;	
		}else{
				apArchivo<<"\t\tHabitacion: Suite"<<endl;				
		}
	}
	if(copia->desayuno==1){
	apArchivo<<"\t\tDesayuno: Incluido"<<endl;
	}else{
	apArchivo<<"\t\tDesayuno: No incluido"<<endl;
	}
		if(copia->tdc==1){
	apArchivo<<"\t\tMetodo de pago: Tarjeta"<<endl;
	apArchivo<<"\t\tBanco:"<<copia->mitarjeta.bancos<<endl;
	apArchivo<<"\t\tTipo:"<<copia->mitarjeta.visa<<endl;	
	}else{
		apArchivo<<"\t\tMetodo de pago: Efectivo"<<endl;
	}
	apArchivo<<"\t\t--------------------------------------------"<<endl;
    copia=copia->siguiente;
	} while( copia != LISTA);
	return;			
}

//agrega
