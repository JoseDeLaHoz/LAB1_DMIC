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

