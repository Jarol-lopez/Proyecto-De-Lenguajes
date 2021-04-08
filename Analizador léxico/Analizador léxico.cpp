#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
using namespace std;

void AnalizadorCaracter(char caracter);// Función para leer caracter a caracter el contenido del archivo entrante y asignarle un estado.
void Estados();//Función para mandar los estados de los caracteres leídos
void PalabrasReservadas();//Función para identificar las palabras reservadas del lenguaje

//TABLA DE SÍMBOLOS en forma de arreglo bidimensional que contiene las palabras reservadas del lenguaje:
const char *reservadas[][2] = {{"para","Ciclo para, para repetir instrucciones"},{"mientras","Ciclo mientras, para repetir instrucciones"},
{"hacer","Ciclo hacer, la misma idea del do while"},{"si","Condicional si, para evaluar condiciones"},
{"sino","Para ejecutar instrucciones en caso de que no se cumpla la condición en el condicional si"},{"opciones","Condicional opciones, la misma idea del switch"},
{"caso","Los casos del condicional opciones"},{"defecto","La opción por defecto del condicional opciones si no se cumple ninguno de los casos"},
{"fin","Para declarar el fin de las estructuras"},{"string","Tipo de dato de cadena"},{"int","Tipo de dato numérico entero"},
{"boolean","Tipo de dato booleano, verdadero, falso, 1 ó 0"},{"float","Tipo de dato numérico decimal"},{"verdadero","Valor verdadero"},{"falso","Valor falso"},
{"inicioprograma","Para declarar el inicio del programa"},{"finprograma","Para declarar el fin del programa"}};

int Tamano=sizeof(reservadas)/sizeof(char *);//El tamano de 'reservadas' y el tamano de memoria del char
char palabraIngresada[70]; //Variable para almacenar los caracteres concatenados que forman las palabras
char temp[1]; //Variable temporal para guardar caracteres de una cadena
enum TEstados{q0,q1,q2,q3,q4,q5,q6,q7,q8,q9,q10,q11,q12,q13,q14,q15,q16,q17,q18,q19,q20}; //Estados

//Iniciando el estado en q0
TEstados Estado=q0;

//Contadores de los elementos de la tabla que se escribirá en el archivo de salida:
int contadorVariables=0;
int contadorNumeros=0;
int contadorPalabrasReservadas=0;
int contadorSimbolos=0;
int contadorSignos=0;
int contadorCiclos=0;
int contadorCondicional=0;


int main(){
	char caracter2; //Variable a usar para leer el contenido del archivo caracter a caracter
	FILE *archivoE; //Archivo de entrada que contendrá el programa en el lenguaje definido
	FILE *archivoS; //Archivo de salida (en él se imprimirá la tabla)
   
	archivoE=fopen("archivoEntrada.txt", "r" ); //Abrimos el archivo que vamos a leer
	archivoS=fopen("archivoSalida.txt", "wt"); //Preparamos el archivo de escritura
   	
    if(archivoE == NULL ) {
		printf("Ha ocurrido un error al intentar abrir el archivo");
    	return 1;
	}
	
	while(true){ // Bucle para leer el archivo
		caracter2=fgetc(archivoE); //la función 'fgetch' toma el contenido del archivo y lo itera caracter a caracter
		
		if(caracter2==EOF){ //EOF:End Of File (fin del archivo), si se llega al final del archivo se termina el proceso
			break;
		}
		
		AnalizadorCaracter(caracter2);
		
		//Se analiza el caracter ';' para contarlo como símbolo 
		if(caracter2==';'){
			contadorSimbolos++;
		}
	}
	
	//Imprimos en consola:
	printf("-----------TABLA DE ELEMENTOS-----------\n");   
	printf("Palabras Reservadas: %d\n", contadorPalabrasReservadas);
	printf("Simbolos: %d\n", contadorSimbolos);
	printf("Ciclos: %d\n", contadorCiclos/2);
	printf("Condicional: %d\n", contadorCondicional/2);
	printf("Variables: %d\n", contadorVariables);
	printf("Numeros: %d\n", contadorNumeros);
	printf("Aritmeticos: %d\n", contadorSignos);
	
	//Escribimos en el archivo de salida:
	fputs("-----------TABLA DE ELEMENTOS-----------\n", archivoS);
	fprintf(archivoS, "Palabras Reservadas: %d", contadorPalabrasReservadas);
	fprintf(archivoS, "\nSimbolos: %d", contadorSimbolos);
	fprintf(archivoS, "\nCiclos: %d", contadorCiclos/2);
	fprintf(archivoS, "\nCondicional: %d", contadorCondicional/2);
	fprintf(archivoS, "\nVariables: %d", contadorVariables);
	fprintf(archivoS, "\nNumeros: %d", contadorNumeros);
	fprintf(archivoS, "\nAritmeticos: %d", contadorSignos);
}

void AnalizadorCaracter(char caracter){
		
		if(caracter==32 || caracter=='}'||caracter=='{'||caracter=='('||caracter==')'||caracter==';'){
			Estados();
		}
		
		if( caracter>='A' && caracter<='Z' ){
			if(Estado==q0){
				Estado=q1;
			}else if(Estado==q1||Estado==q2){
				Estado=q2;
			}else if(Estado!=q0 && Estado!=q1 && Estado!=q2){
				exit(-1);
			}
		}
		
		if(caracter>='a' && caracter<='z'){
			if(Estado==q0){
				temp[0]=caracter; 
				strcat(palabraIngresada,temp); 
				Estado=q3;
			}else if(Estado==q1||Estado==q2){
				Estado=q2;
			}else if(Estado==q3){
				temp[0]=caracter; 
				strcat(palabraIngresada,temp);
				Estado=q3;
			}else{
				exit(-1);
			}
		}
		
		if(caracter<='9'&&caracter>='0'){
			if(Estado==q0){
				Estado=q4;
			}else if(Estado==q4||Estado==q5){
				Estado=q5;
			}else if(Estado==q13||Estado==q6){
				Estado=q6;
			}else if(Estado==q1||Estado==q2){
				Estado=q2;
			}else if(Estado==q7){
				Estado=q4;
			}else{
				exit(-1);
			}
		}
		
		if(caracter=='+'){
			if(Estado==q0){
				Estado=q8;
			}else if(Estado==q8){
				Estado=q17;
			}
		}
		
		if(caracter=='.'){
			if((caracter)<'1' || (caracter)>='9'){
				Estado=q19;
			}else{
				if(Estado==q4||Estado==q5&&((caracter)=='1'||(caracter)=='2'
					||(caracter)=='3'||(caracter)=='4'||(caracter)=='5'||(caracter)=='6'
					||(caracter)=='7'||(caracter)=='8'||(caracter)=='9')){
					Estado=q20;
				}else if(Estado!=q4 && Estado!=q5){
					exit(-1);
				}
			}
		}
		
		if(caracter=='^'){
			if(Estado==q0){
				Estado=q18;
			}else{
				exit(-1);
			} 
		}
		
		if(caracter=='-'){
			if(Estado==q0){
				Estado=q7;
			}else if(Estado==q12){
				Estado=q10;
			}else if(Estado==q7){
				Estado=q17;
			}
		}
		
		if(caracter=='='){
			if(Estado==q0){
				Estado=q9;
			}else if(Estado==q18){
				Estado=q11;
			}else if(Estado==q12){
				Estado=q16;
			}else if(Estado==q13){
				Estado=q15;
			}
		}
		
		if(caracter=='/'||caracter=='*'){
			if(Estado==q0){
				Estado=q18;
			}else{
				exit(-1);
			}
		}
		
		if(caracter=='<'){                
			if(Estado==q0){
				Estado=q12;
			}else{
				exit(-1);
			}
		}
		
		if(caracter=='>'){   
			if(Estado==q0){
				Estado=q14;
			}else{
				exit(-1);
			}
		}	
		
		if(caracter=='!'){
			if(Estado==q0){
				Estado=q18;
			}else{
				exit(-1);
			} 
		}
}

void Estados(){
	
	switch(Estado){
			case 1:contadorVariables++; // Suma variables A ... Z
			break;
			case 2:contadorVariables++; //  A ... Z	 a ... z  0 ... 9	
			break;
			case 3: PalabrasReservadas(); // Para las palabras reservadas
			break;
			case 4:contadorNumeros++; //Para lo números 0 ... 9
			break;
			case 5:contadorNumeros++; // Para los números 0 ... 9
			break;
			case 6:contadorNumeros++; // 0 ... 9
			break;
			case 7:contadorSignos++; // Para el signo '-'
			break;
			case 8:contadorSignos++; // Para el signo  '+'
			break;
			case 9:contadorSimbolos++; // Para el símbolo '='
			break;
			case 10:contadorSignos++; // Para el signo '-'
			break;
			case 11:contadorSimbolos++; // Para el símbolo '=
			break;
			case 12:contadorSimbolos++; // Para el símbolo '<'
			break;
			case 14:contadorSimbolos++; // Para el símbolo '/' '>'
			break;
			case 15:contadorSimbolos++; // Para el símbolo '=' 
			break;
			case 16:contadorSimbolos++; // Para los símbolo '/' '=' ';'
			break;
			case 17:contadorSignos++; // Para el signo '-' '+'
			break;
			case 18:contadorSignos++; // Para los signos  '/' '*' '^' '!'
			break;
			case 19:contadorSimbolos++; // Para los símbolos '.' '\n' '\t' etc... 
			break;
			case 20:contadorNumeros++; 	//Para los números .   0 ... 9
			break;
			default:
				break;
			}	
			
			Estado = q0;	
}

//Función utilizada para verificar las palabras han sido definidas como reservadas
void PalabrasReservadas(){
	for(int i=0;i<Tamano;i++){
		//utilizaremos la función 'strcmp' que se encarga de comparar caracter por caracter dos strings e identificaremos las palabras reservadas
		if(strcmp(reservadas[i],palabraIngresada)==0){
			
			//Contar Ciclo 'para'
			if(strcmp(reservadas[0],palabraIngresada)==0){
				contadorCiclos++;
			}

			//Contar Ciclo 'mientras'
			if(strcmp(reservadas[1],palabraIngresada)==0){
				contadorCiclos++;
			}
				
			//Contar Ciclo 'hacer'
			if(strcmp(reservadas[2],palabraIngresada)==0){
				contadorCiclos++;
			}
			
			//Contar Condicional 'si'
			if(strcmp(reservadas[3],palabraIngresada)==0){
				contadorCondicional++;
			}
				
			//Contar Condicional 'opciones'
			if(strcmp(reservadas[5],palabraIngresada)==0){
				contadorCondicional++;
			}
			
			//Cuenta las palabras reservadas que encuentre
			contadorPalabrasReservadas++;
			palabraIngresada[0]='\0';
			break;
		}
		if(i==(Tamano)-1){
			exit(-1);
		}
	}		
}
