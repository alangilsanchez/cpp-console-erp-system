#include <stdio.h>
#include <stdlib.h>
#include <conio.h>	//kbhit--> Determina si se presiona una tecla
#include <locale.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>
#include <math.h>
#include <time.h>



void gotoxy(int x, int y){
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dWPos;
	dWPos.X =x;
	dWPos.Y =y;
	SetConsoleCursorPosition(hcon,dWPos);
}

					 
typedef struct {
	char modelo[10];
	int existencias;
	float precio;
	char ubicacion[20];
}Almacen; //variable de la estructura



Almacen almacen[] = { {"EST123", 1000, 4599, "Estante A"},
					  {"EST456", 980, 7000, "Estante B"},
					  {"EST789", 3000, 5699, "Estante C"},
					  {"EST987", 2000, 3500, "Estante D"},
					  {"EST654", 850, 8500, "Estante E"},
					  {"HOR123", 3000, 3300, "Estante F"},
					  {"HOR456", 2500, 2900, "Estante G"},
					  {"HOR789", 4000, 2500, "Estante H"},
					  {"HOR987", 1000, 9099, "Estante I"},
					  {"HOR654", 850, 9800, "Estante J"} };

typedef struct{
	int idCliente;
	char nombre[25];
	char tel[11];
	char correo[40];
}Cliente;

typedef struct{
	int idDetalle;
	int idPedido;
	char modelo[10];
	int cantidad;
	float precio;
	float subtotal;
	int existencias;
}Detalle;

typedef struct{
	int idPedido;
	char estado[7];
	Cliente cliente;
	Detalle detalle;
	Almacen alm;
}Pedido;

					 
enum MENU { OPC1=1, OPC2, OPC3, OPC4, OPC5, OPC6, OPC7};

FILE *arch = NULL;
Pedido*regis = (Pedido *)malloc(sizeof(Pedido));
//Grupo*regis = (Grupo *)malloc(sizeof(Grupo));

#include "decorar.h"
#include "validaciones.h"
#include "estructura.h"
#include "apuntadores.h"
#include "menu.h"




