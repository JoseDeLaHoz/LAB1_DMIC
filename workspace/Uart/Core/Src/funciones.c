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

