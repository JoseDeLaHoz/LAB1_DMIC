/*
 * funciones.c
 *
 *  Created on: Sep 12, 2022
 *      Author: javie
 */

#include <stdio.h>

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
	printf("\n\rPara desplegar la lista de comandos disponible escriva 'help'");
	printf("\r\n");
}

void help(void) {
	//printf("\x1b[2J"); //Clear the screen
	printf("\n\rPara más información de un comando específico, escriba 'help <comando>'");
	printf("\n\r Donde <comando> es uno de los siguientes:");
	printf("\n\r\t ledcontrol");
	printf("\n\r\t LFSR");
	printf("\n\r\t tiempo");
	printf("\n\r\t temp");
	printf("\n\r\t regE");
	printf("\n\r\t impresion");
	printf("\r\n");
}

void ledcontrol(void){
	printf("\n\r Hace titilar un led a una velocidad configurable.");
	printf("\n\r ledcontrol [frecuencia]");
	printf("\n\r\t    frecuencia\t determina la velocidad de encendido y apagado del led (0.1, 0.2,..., 1,.., 10) Hz");
	printf("\r\n");
}

void LFSR(void){
	printf("\n\r Genera una secuencia de números pseudoaleatorios.");
	printf("\n\r LFSR [algoritmo]");
	printf("\n\r\t algoritmo\t permite escoger el algoritmo de generación de la secuencia de números");
	printf("\n\r\t\t al1 genera la secuencia de números con la técnica de XOR's");
	printf("\n\r\t\t al2 genera la secuencia de números con la técnica dada por la página");
	printf("\r\n");
}

void tiempo(void){
	printf("\n\r Toma la fecha y hora del RTC y lo presenta en pantalla.");
	printf("\n\r tiempo [vacio]");
	printf("\n\r\t vacio\t este comando no requiere de un argumento");
	printf("\r\n");
}

void temp(void){
	printf("\n\r Toma y almacena la temperatura del periférico de la tarjeta núcleo.");
	printf("\n\r temp [vacio]");
	printf("\n\r\t vacio\t este comando no requiere de un argumento");
	printf("\r\n");
}

void regE(void){
	printf("\n\r Permite gestionar los registros de ejecución almacenados en la memoria no volátil.");
	printf("\n\r regE [acción]");
	printf("\n\r\t    acción:");
	printf("\n\r\t\t    r  permite leer los datos guardados en los registros");
	printf("\n\r\t\t    w  permite modificar o escribir por primera vez en los registros");
	printf("\n\r\t\t    s  muestra el estado de los registros");
	printf("\r\n");
}

void impresion(void){
	printf("\n\r Permite determinar si durante la ejecución de al secuencia pseudoaleatoria se imprimen");
	printf("\n\r los números o solo se indica que se está corriendo la secuencia.");
	printf("\n\r impresion [eleccion]");
	printf("\n\r\t    eleccion:");
	printf("\n\r\t\t    d deshabilita la impresión de los números de la secuencia y emite una señal de ejecución");
	printf("\n\r\t\t    e  habilita la impresión de los números de la secuencia");
	printf("\r\n");
}

void ImprimirMensajeGanador(char* nombre) {


    printf("\r\n");
    printf("\r\n                          oooo$$$$$$$$$$$$oooo");
    printf("\r\n                      oo$$$$$$$$$$$$$$$$$$$$$$$$o");
    printf("\r\n                   oo$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$o         o$   $$ o$");
    printf("\r\n   o $ oo        o$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$o       $$ $$ $$o$");
    printf("\r\noo $ $ ~$      o$$$$$$$$$    $$$$$$$$$$$$$    $$$$$$$$$o       $$$o$$o$");
    printf("\r\n~$$$$$$o$     o$$$$$$$$$      $$$$$$$$$$$      $$$$$$$$$$o    $$$$$$$$");
    printf("\r\n  $$$$$$$    $$$$$$$$$$$      $$$$$$$$$$$      $$$$$$$$$$$$$$$$$$$$$$$");
    printf("\r\n  $$$$$$$$$$$$$$$$$$$$$$$    $$$$$$$$$$$$$    $$$$$$$$$$$$$$  ~~~$$$");
    printf("\r\n   ~$$$~~~$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$     ~$$$");
    printf("\r\n    $$$   o$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$     ~$$$o");
    printf("\r\n   o$$~   $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$       $$$o");
    printf("\r\n   $$$    $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" "$$$$$$ooooo$$$$o");
    printf("\r\n  o$$$oooo$$$$$  $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$   o$$$$$$$$$$$$$$$$$");
    printf("\r\n  $$$$$$$$~$$$$   $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$     $$$$~~~~~~~~");
    printf("\r\n ~~~~       $$$$    ~$$$$$$$$$$$$$$$$$$$$$$$$$$$$~      o$$$");
    printf("\r\n            ~$$$o     ~~~$$$$$$$$$$$$$$$$$$~$$~         $$$");
    printf("\r\n              $$$o          ~$$~~$$$$$$~~~~           o$$$");
    printf("\r\n               $$$$o                                o$$$~");
    printf("\r\n                ~$$$$o      o$$$$$$o~$$$$o        o$$$$");
    printf("\r\n                  ~$$$$$oo     ~~$$$$o$$$$$o   o$$$$~~");
    printf("\r\n                     ~~$$$$$oooo  ~$$$o$$$$$$$$$~~~");
    printf("\r\n                        ~~$$$$$$$oo $$$$$$$$$$");
    printf("\r\n                                ~~~~$$$$$$$$$$$");
    printf("\r\n                                    $$$$$$$$$$$$");
    printf("\r\n                                     $$$$$$$$$$~");
    printf("\r\n                                      ~$$$~~  ");
    printf("\r\n");
    printf("\r\n               ¡¡¡ Felicidades %s, adivinaste el numero !!!", nombre);
}

/**
 *
 */
void ImprimirMensajeNoGanador(void){
    printf("\r\n");
    printf("\r\n       ###########");
    printf("\r\n      ##         ##");
    printf("\r\n      #  ~~   ~~  #");
    printf("\r\n      # (*)   (*) #");
    printf("\r\n      (     ^  '  )");
    printf("\r\n       |         |");
    printf("\r\n       |  <===>  |");
    printf("\r\n        \\       /");
    printf("\r\n       /  -----  \\");
    printf("\r\n    ---    \\X/    ---");
    printf("\r\n   /       |x|       \\");
    printf("\r\n  |        |x|        |");
    printf("\r\n");
    printf("\r\n  Lo siento, esta vez no hubo suerte !!!");

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

