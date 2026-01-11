void menuProyecto();
void menu1();
void menu2();
void menu4();
void menu(int,int,int &);
void menu_1(int x,int y, int &opc);

void menu(int x, int y, int &opc){
	char tecla='\0'; // ' '
	opc = 1;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
	//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),26);
	gotoxy(x,y);
	printf("%c",16);
	do{
		if(kbhit()){
			tecla=getch();
			//printf("%d", tecla);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0);
			//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),17);
			gotoxy(x,y);
			printf("%c", 16);
			if(opc>1&&tecla==72){	//Flecha arriba
				y--;
				opc--;
			}
			if(opc<7 &&tecla==80){	//Flecha abajo
				y++;
				opc++;
			}
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
			//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),26);
			gotoxy(x,y);
			printf("%c",16);
		}
	}while(tecla!=13); //13--> Enter
}

void menuProyecto(){
	setlocale(LC_CTYPE, "Spanish");
	int respuesta=0;
	int opc = 0;
	int x = 0;
	int y = 0;
	
	while(opc !=7){
		system("color 02");
		x = 25;
		y = 5;
		system("cls");
		//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),48);
		gotoxy(x,y);
		printf("1. Consulta de almacén\n");
		gotoxy(x,++y);
		printf("2. Actualizar almacén\n");
		gotoxy(x,++y);
		printf("3. Registrar Pedido\n");
		gotoxy(x,++y);
		printf("4. Consultar Pedido\n");
		gotoxy(x,++y);
		printf("5. Registrar entrega\n");
		gotoxy(x,++y);
		printf("6. Modificar estado de pedido\n");
		gotoxy(x,++y);
		printf("7. Salir del Sistema\n");
		gotoxy(x,++y);
		//printf("\nDame la opción: ");
		//scanf("%d", &opc);
		menu(22,5,opc);
		//system("color 10");
		system("cls");
		//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),48);
		gotoxy(10,4);
		switch(opc){
			case OPC1:
				printf("Consulta de almacén\n");
				menu1();
				getch();
				break;
			case OPC2:
				printf("Actualizar almacén\n");
				menu2();
				getch();
				break;
			case OPC3:
				printf("Registrar Pedido\n");
				printf("1 para Continuar/ 2 para Salir: ");
				scanf("%d", &respuesta);
				fflush(stdin);
				system("cls");
				if(respuesta==1){
					do{
						printf("Registrar Pedido\n");
						respuesta=0;
						agregarDinamico();
						printf("\n\nDesea realizar otro pedido...1 para Si / 2 para No: ");
						scanf("%d", &respuesta);
						system("cls");
					}while(respuesta==1);
				}
				break;
			case OPC4:
				printf("Consultar Peido\n");
				menu4();
				getch();
				break;
			case OPC5:
				printf("Registrar entrega\n");
				printf("1 para Continuar/ 2 para Salir: ");
				scanf("%d", &respuesta);
				fflush(stdin);
				system("cls");
				if(respuesta==1){
					do{
						printf("Registrar entrega\n");
						respuesta=0;
						registrarEntrega();
						printf("\n\nDesea entregar otro pedido...1 para Si / 2 para No: ");
						scanf("%d", &respuesta);
						system("cls");
					}while(respuesta==1);
				}
				break;
			case OPC6:
				printf("Modificar estado de pedido\n");
				modificaestado();
				break;
			case OPC7:
				system("color 60");
				printf("Adios!! :D");
				exit(0);
			/*default:
				printf("No existe la opción\n");
				getch();
				break;*/
		}
	}
	getch();
}

void menu1(){
	setlocale(LC_CTYPE, "Spanish");
	int opc = 0;
	int x = 0;
	int y = 0;
	
	while(opc !=3){
		system("color 02");
		x = 25;
		y = 5;
		system("cls");
		gotoxy(x,y);
		printf("a) Consulta general de todo el almacén\n");
		gotoxy(x,++y);
		printf("b) Estufas (modelos)\n");
		gotoxy(x,++y);
		printf("c) Hornos de Microondas (modelos)\n");
		gotoxy(x,++y);
		printf("d) Regresar\n");
		gotoxy(x,++y);
		menu(22,5,opc);
		system("cls");
		gotoxy(10,4);
		switch(opc){
			case OPC1:
				printf("Consulta general del almacén\n");
				imprimirEstructura();
				//crear_archivo();
				leer_archivo();
				getch();
				break;
			case OPC2:
				printf("Estufas (modelos)\n");
				consulta_estufas();
				getch();
				break;
			case OPC3:
				printf("Hornos de Microondas (modelos)\n");
				consulta_hornos();
				getch();
				menu1();
				break;
			case OPC4:
				menuProyecto();
				getch();
				break;
		}
	}
	getch();
}
void menu2(){
	setlocale(LC_CTYPE, "Spanish");
	int respuesta=0;
	int opc = 0;
	int x = 0;
	int y = 0;
	
	while(opc !=3){
		system("color 02");
		x = 25;
		y = 5;
		system("cls");
		gotoxy(x,y);
		printf("a) Modifica registros\n");
		gotoxy(x,++y);
		printf("b) Agrega registros\n");
		gotoxy(x,++y);
		printf("c) Regresar\n");
		gotoxy(x,++y);
		menu(22,5,opc);
		system("cls");
		gotoxy(10,4);
		switch(opc){
			case OPC1:
				printf("Modifica registros\n");
				printf("1 para Continuar/ 2 para Salir: ");
				scanf("%d", &respuesta);
				system("cls");
				if(respuesta==1){
					do{
						printf("Modifica registros\n");
						respuesta=0;
						leer_archivo();
						modiRegAlmacen();
						leer_archivo();
						printf("\nDesea modificar otro registro...1 para Si / 2 para No: ");
						scanf("%d", &respuesta);
						system("cls");
					}while(respuesta==1);
				}
				break;
			case OPC2:
				respuesta=0;
				printf("Agrega registros\n");
				printf("1 para Continuar/ 2 para Salir: ");
				scanf("%d", &respuesta);
				system("cls");
				if(respuesta==1){
					do{
						printf("Modifica registros\n");
						respuesta=0;
						agRegAlmacen();
						leer_archivo();
						printf("\nDesea agregar otro registro...1 para Si / 2 para No: ");
						scanf("%d", &respuesta);
						system("cls");
					}while(respuesta==1);
				}
				break;
			case OPC3:
				menuProyecto();
				getch();
				break;
		}
	}
	getch();
	
}

void menu4(){
	setlocale(LC_CTYPE, "Spanish");
	int opc = 0;
		int respuesta=0;
	int x = 0;
	int y = 0;
	
	while(opc !=3){
		system("color 02");
		x = 25;
		y = 5;
		system("cls");
		gotoxy(x,y);
		printf("a) Pedidos Activos\n");
		gotoxy(x,++y);
		printf("b) Pedidos Entregados\n");
		gotoxy(x,++y);
		printf("c) Pedidos Cancelados\n");
		gotoxy(x,++y);
		printf("d) Número de pedido\n");
		gotoxy(x,++y);
		printf("e) Regresar\n");
		gotoxy(x,++y);
		menu(22,5,opc);
		system("cls");
		gotoxy(10,4);
		switch(opc){
			case OPC1:
				printf("Pedidos Activos\n");
				printf("1 para Continuar/ 2 para Salir: ");
				scanf("%d", &respuesta);
				system("cls");
				if(respuesta==1){
					do{
						printf("Pedidos Activos\n");
						respuesta=0;
						consultapedidosActivos();
						printf("\n\nDesea consultar otro pedido...1 para Si / 2 para No: ");
						scanf("%d", &respuesta);
						system("cls");
					}while(respuesta==1);
				}
				break;
			case OPC2:
				printf("Pedidos Entregados\n");
				printf("1 para Continuar/ 2 para Salir: ");
				scanf("%d", &respuesta);
				system("cls");
				if(respuesta==1){
					do{
						printf("Pedidos Entregados\n");
						respuesta=0;
						consultapedidosEntregados();
						printf("\n\nDesea consultar otro pedido...1 para Si / 2 para No: ");
						scanf("%d", &respuesta);
						system("cls");
					}while(respuesta==1);
				}
				break;
			case OPC3:
				printf("Pedidos Cancelados\n");
				printf("1 para Continuar/ 2 para Salir: ");
				scanf("%d", &respuesta);
				system("cls");
			
				if(respuesta==1){
					printf("Pedidos Cancelados\n");
					consultapedidosCancelados();
					getch();
				}
				menu4();
				break;
			case OPC4:
				printf("Número de pedido\n");
				printf("1 para Continuar/ 2 para Salir: ");
				scanf("%d", &respuesta);
				system("cls");
				if(respuesta==1){
					do{
						printf("Número de pedido\n");
						respuesta=0;
						numpedido();
						printf("\n\nDesea consultar otro pedido...1 para Si / 2 para No: ");
						scanf("%d", &respuesta);
						system("cls");
					}while(respuesta==1);
				}
				break;
			case OPC5:
				menuProyecto();
				getch();
				break;
		}
	}
	getch();
}
