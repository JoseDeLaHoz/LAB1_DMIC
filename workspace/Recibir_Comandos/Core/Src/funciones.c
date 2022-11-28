/*
 * funciones.c
 *
 *  Created on: Sep 12, 2022
 *      Author: javie
 */

#include <stdio.h>
#include <math.h>

/**
 *
 */

void Saludo(void) {
	printf("\x1b[2J"); //Clear the screen
	printf("\n\r***************************************************************");
	printf("\n\r* Universidad Escuela Colombiana de Ingenieria Julio Garavito *");
	printf("\n\r*                    DMIC - B - 2022                          *");
	printf("\n\r*\t Jose De La Hoz                                       *");
	printf("\n\r*\t Jhan Carlos Reyes                                    *");
	printf("\n\r*\t Esneider Silva                                       *");
	printf("\n\r*\t\t'GENERADOR DE NUMEROS PSEUDOALEATORIO'        *");
	printf("\n\r* Desarrollado para una tarjeta NUCLE0-F767ZI                 *");
	printf("\n\r***************************************************************");
	printf("\r\n");
	printf("\n\rPara una mejor experiencia, habilite la opcion de eco local en su terminal");
	printf("\r\n");
}


void ImprimirError (void) {
    printf("\r\n");
    printf("\r\n  _____    _____    _____    _____   _____ ");
    printf("\r\n |  ___|  |  _  \\  |  _  \\  /     \\ |  _  \\");
    printf("\r\n |  ___|  |     /  |     / |   |  | |     /");
    printf("\r\n |_____|  |__|__\\  |__|__\\  \\____/  |__|__\\");
    printf("\r\n");
    printf("\r\nDato ingresado invalido !!!");

}

void Help(void) {
	printf("\n\rPara mÃ¡s informaciÃ³n de un comando especÃ­fico, escriba 'help <comando>'");
	printf("\n\r Donde <comando> es uno de los siguientes:");
	printf("\n\r\t ledc");
	printf("\n\r\t lfsr");
	printf("\n\r\t time");
	printf("\n\r\t temp");
	printf("\n\r\t rege");
	printf("\n\r\t prin");
	printf("\r\n");
}

void Ledc(void){
	printf("\n\r Hace titilar un led a una velocidad configurable.");
	printf("\n\r ledcontrol <argumento>");
	printf("\n\r\t    argumento\t determina la frecuencia de encendido y apagado del led (0.1, 0.2,..., 1,.., 10) Hz");
	printf("\n\r\t    los posibles valores del argumento estÃ¡n entre 1 y 100");
	printf("\r\n");
}


void Lfsr(void){
	printf("\n\r Genera una secuencia de nÃºmeros pseudoaleatorios.");
	printf("\n\r LFSR <argumento>");
	printf("\n\r\t argumento:\t permite escoger el algoritmo de generaciÃ³n de la secuencia de nÃºmeros");
	printf("\n\r\t\t x genera la secuencia de nÃºmeros con la tÃ©cnica de XOR's");
	printf("\n\r\t\t p genera la secuencia de nÃºmeros con la tÃ©cnica dada por la pÃ¡gina");
	printf("\r\n");
}

void Time(void){
	printf("\n\r Toma la fecha y hora del RTC y lo presenta en pantalla.");
	printf("\n\r\t tiempo [vacio]");
	printf("\n\r\t\t  este comando no requiere de un argumentos");
	printf("\r\n");
}

void Temp(void){
	printf("\n\r Toma la temperatura del perifÃ©rico de la tarjeta nÃºcleo y la presenta en la terminal.");
	printf("\n\r\t temp [vacio]");
	printf("\n\r\t\t este comando no requiere de un argumentos");
	printf("\r\n");
}

void Rege(void){
	printf("\n\r Permite gestionar los registros de ejecuciÃ³n almacenados en la memoria no volÃ¡til.");
	printf("\n\r\t rege <argumento>");
	printf("\n\r\t\t    r  permite leer los datos guardados en los registros");
	printf("\n\r\t\t    w  permite modificar o escribir por primera vez en los registros");
	printf("\n\r\t\t    s  muestra el estado de los registros");
	printf("\r\n");
}

void Prin(void){
	printf("\n\r Permite determinar si durante la ejecuciÃ³n de al secuencia pseudoaleatoria se imprimen");
	printf("\n\r los nÃºmeros o solo se indica que se estÃ¡ corriendo la secuencia.");
	printf("\n\r\t impresion <argumento>");
	printf("\n\r\t\t    d deshabilita la impresiÃ³n de los nÃºmeros de la secuencia y emite una seÃ±al de ejecuciÃ³n");
	printf("\n\r\t\t    e  habilita la impresiÃ³n de los nÃºmeros de la secuencia");
	printf("\r\n");
}


