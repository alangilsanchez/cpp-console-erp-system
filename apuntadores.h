Almacen buscaModelo(char modelo[]){
	setlocale(LC_CTYPE, "Spanish");
	bool bandera = false;
	Almacen dato = {};
	

	if(!(arch=fopen("almacen.xls", "r"))){
		printf("Error al intentar leer archivo");
		exit(1);
	}
	
	while(!feof(arch)){
		fscanf(arch,"%[^\t]\t", dato.modelo);
		fscanf(arch,"%d\t", &dato.existencias);
		fscanf(arch,"%f\t", &dato.precio);
		fscanf(arch,"%[^\n]\n", dato.ubicacion);
		
		if(strcmp(dato.modelo, modelo)==0){
			printf("\nRegistros actuales del almacén\n\n");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),13);
			printf("MODELO\t");
			printf("Total\t");
			printf("Precio\t");
			printf("Ubicación\n");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
			printf("%s\t", dato.modelo);
			printf("%d\t", dato.existencias);
			printf("%.2f\t", dato.precio);
			printf("%s\n\n", dato.ubicacion);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
			fclose(arch);
			return dato;
		}
	}
	if(bandera==false)printf("No se encuentra el registro");
	return dato;
}

void imprime_detalle(){
	setlocale(LC_CTYPE, "Spanish");
	Detalle dato;
	float total=0;
	
	if(!(arch=fopen("detalle.xls", "r"))){
		printf("Error al intentar leer archivo");
		exit(1);
	}
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),13);
	printf("\n\nModelo\tCantidad\tPrecio Unitario\tSub Total\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
	
	while(!feof(arch)){
		fscanf(arch, "%d\t", &dato.idPedido );
		fscanf(arch, "%d\t", &dato.cantidad);
		fscanf(arch, "%f\t", &dato.subtotal);
		fscanf(arch, "%[^\t]\t", dato.modelo);
		fscanf(arch, "%d\t", &dato.existencias);
		fscanf(arch, "%f\n", &dato.precio);
		
		if(dato.idPedido == regis->idPedido){
			printf("%s\t", dato.modelo);
			printf("%d\t\t", dato.cantidad);
			printf("%.2f\t\t", dato.precio);
			printf("%.2f\n", dato.subtotal);
			total=total+dato.subtotal;
		}	
	}
	fclose(arch);
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),13);
	printf("\t\t\tTOTAL\t\t");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
	printf("%.2f", total);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
	
}

void agregarDinamico(){
	setlocale(LC_CTYPE, "Spanish");
	bool bandera=true;
	char modelo[7]="";
	int opcion=0;
	int identificador=0;
	int numregistro=0;
	int arroba=0, punto=0;
	Almacen dato = {};
	srand(time(NULL));
	
	printf("\nRegistro Dinámico: ");
	
	regis->idPedido = 00001 + rand()%(99999 - 00001) + 1;
	regis->cliente.idCliente = 00001 + rand()%(999 - 00001) + 1;
	identificador = regis->idPedido;
	printf("\nNumero de Pedido: %d", regis->idPedido);
	//printf("\nId Cliente: %d", regis->cliente.idCliente);
	validaCadena("Nombre: ", regis->cliente.nombre);
	strcpy(regis->estado, "Activo");
	printf("Estado: %s", regis->estado);
	//printf("\nTelefono: ");
	//scanf("%s", regis->cliente.tel);
	do{																									
		printf("\nTelefono: ");						
	    scanf("%s", regis->cliente.tel);
   		fflush(stdin);
		if( !(strlen(regis->cliente.tel)==10) ){				
			continue;
		}
		else{												
			for(int i=0; i<strlen(regis->cliente.tel); i++){
				if( !(isdigit(regis->cliente.tel[i])) ){
					break;
				}
				if(i == (strlen(regis->cliente.tel)-1)){		
					bandera=false;						
				}
			}
		}
    }while(bandera);
	//printf("Correo: ");
	//scanf("%s", regis->cliente.correo);
	bandera=true;
	
	do{	
		arroba=0;
		punto=0;																						
		printf("Correo: ");						
	    scanf("%s", regis->cliente.correo);
   		fflush(stdin);
		
		for(int i=0; i<strlen(regis->cliente.correo); i++){
			if( !(isdigit(regis->cliente.correo[i])) && !(isalpha(regis->cliente.correo[i])) ){
				if( regis->cliente.correo[i]=='@' && arroba==0 ){
					arroba++;
				} 
				else{
					if( regis->cliente.correo[i]=='.' && punto==0 ){
						punto++;
					} 
					else{
						arroba=0;
						punto=0;
						break;
					}
				}
				
			}
		
			if (i <= (strlen(regis->cliente.correo)-1) && arroba == 1 && punto == 1){
				bandera=false;
			}
		}	
    }while(bandera);
	fflush(stdin);
	
	leer_archivo();
	do{
		fflush(stdin);
		printf("\n Id Modelo: ");
		scanf("%s", regis->detalle.modelo);
		dato = buscaModelo(regis->detalle.modelo);
		//registros = registros+1;	
		strcpy(regis->alm.modelo, dato.modelo);
		regis->alm.existencias = dato.existencias;
		regis->alm.precio = dato.precio;
		strcpy(regis->alm.ubicacion, dato.ubicacion);
		regis->detalle.cantidad = validaEntero("Cantidad de productos que desea adquirir: ");
		regis->detalle.subtotal = regis->detalle.cantidad * regis->alm.precio;
		
		dato.existencias=dato.existencias - regis->detalle.cantidad;
		//regis->alm.existencias=regis->alm.existencias - regis->detalle.cantidad;
		
		regis->detalle.existencias = regis->alm.existencias;
		regis->detalle.precio = regis->alm.precio;
			
		if(!(arch=fopen("detalle.xls", "a+"))){
			printf("Error al intentar leer archivo");
			exit(1);
		}
		fprintf(arch, "%d\t", regis->idPedido );
		fprintf(arch, "%d\t", regis->detalle.cantidad);
		fprintf(arch, "%.2f\t", regis->detalle.subtotal);
		fprintf(arch, "%s\t", regis->detalle.modelo);
		fprintf(arch, "%d\t", regis->detalle.existencias);
		fprintf(arch, "%.2f\n", regis->detalle.precio);
		fclose(arch);
		
		printf("¿Desea realizar otro pedido? 1 -> SI / 2 -> NO: ");
		scanf("%d", &opcion);
		numregistro=numregistro+1;
	}while(opcion != 2);
	
	
	
	if(!(arch=fopen("encabezado.xls", "a+"))){
		printf("Error al intentar leer archivo");
		exit(1);
	}

	fprintf(arch, "%d\t", regis->idPedido );
	fprintf(arch, "%d\t", regis->cliente.idCliente);
	fprintf(arch, "%s\t", regis->cliente.nombre );
	fprintf(arch, "%s\t", regis->estado);
	fprintf(arch, "%s\t", regis->cliente.tel);
	fprintf(arch, "%s\n", regis->cliente.correo );
	fclose(arch);
		
	printf("\nRegistro agregado!!\n\n");
	
	system("cls");
	
	printf("Numero de Pedido: %d", regis->idPedido);
	printf("\nId Cliente: %d", regis->cliente.idCliente);
	printf("\nNombre: %s", regis->cliente.nombre);
	printf("\nEstado: %s", regis->estado);
	printf("\nTelefono: %s", regis->cliente.tel);
	printf("\nCorreo: %s", regis->cliente.correo);
	
	imprime_detalle();
}

void consultapedidosActivos(){
	setlocale(LC_CTYPE, "Spanish");
	bool bandera=true;
	char modelo[7]="";
	int opcion=0;
	int idpedido=0;
	char estado[7]="Activo";
	float total=0;
	Detalle dato2;
	Pedido dato = {};
	
	if(!(arch=fopen("encabezado.xls", "r"))){
		printf("Error al intentar leer archivo");
		exit(1);
	}
	while(!feof(arch)){
		fscanf(arch, "%d\t", &dato.idPedido );
		fscanf(arch, "%d\t", &dato.cliente.idCliente);
		fscanf(arch, "%[^\t]\t", dato.cliente.nombre );
		fscanf(arch, "%s\t", dato.estado);
		fscanf(arch, "%s\t", dato.cliente.tel);
		fscanf(arch, "%s\n", dato.cliente.correo );
			
		if(strcmp(dato.estado,estado)==0){
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
			printf("Numero de Pedido: %d", dato.idPedido);
			printf("\nId Cliente: %d", dato.cliente.idCliente);
			printf("\nNombre: %s", dato.cliente.nombre);
			printf("\nEstado: %s", dato.estado);
			printf("\nEstado: ");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),3);
			printf("%s", dato.estado);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
			printf("\nTelefono: %s", dato.cliente.tel);
			printf("\nCorreo: %s", dato.cliente.correo);
			printf("\n-------------------------\n");
		}	
	}
	fclose(arch);
	
	do{
		if(!(arch=fopen("encabezado.xls", "r"))){
			printf("Error al intentar leer archivo");
			exit(1);
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),02);
		idpedido = validaEntero("Ingresa el Id del Pedido: ");
		fflush(stdin);
		
		while(!feof(arch)){
		
			
			fscanf(arch, "%d\t", &dato.idPedido );
			fscanf(arch, "%d\t", &dato.cliente.idCliente);
			fscanf(arch, "%[^\t]\t", dato.cliente.nombre );
			fscanf(arch, "%s\t", dato.estado);
			fscanf(arch, "%s\t", dato.cliente.tel);
			fscanf(arch, "%s\n", dato.cliente.correo );
				
			if(dato.idPedido == idpedido){
				system("cls");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
				printf("Numero de Pedido: %d", dato.idPedido);
				printf("\nId Cliente: %d", dato.cliente.idCliente);
				printf("\nNombre: %s", dato.cliente.nombre);
				printf("\nEstado: %s", dato.estado);
				printf("\nTelefono: %s", dato.cliente.tel);
				printf("\nCorreo: %s", dato.cliente.correo);
				bandera=false;
			}
		}
		if(bandera == true){
			printf("No se encuentra el pedido\n");
		}
		fclose(arch);
	}while(bandera);
	
	
	if(!(arch=fopen("detalle.xls", "r"))){
		printf("Error al intentar leer archivo");
		exit(1);
	}
			
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),13);
	printf("\n\nModelo\tCantidad\tPrecio Unitario\tSub Total\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
			
	while(!feof(arch)){
		fscanf(arch, "%d\t", &dato2.idPedido );
		fscanf(arch, "%d\t", &dato2.cantidad);
		fscanf(arch, "%f\t", &dato2.subtotal);
		fscanf(arch, "%[^\t]\t", dato2.modelo);
		fscanf(arch, "%d\t", &dato2.existencias);
		fscanf(arch, "%f\n", &dato2.precio);
				
		if(dato2.idPedido == idpedido){
			printf("%s\t", dato2.modelo);
			printf("%d\t\t", dato2.cantidad);
			printf("%.2f\t\t", dato2.precio);
			printf("%.2f\n", dato2.subtotal);
			total=total+dato2.subtotal;			
		}	
	}
	fclose(arch);
			
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),13);
	printf("\t\t\tTOTAL\t\t");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
	printf("%.2f", total);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);

}
void consultapedidosEntregados(){
	setlocale(LC_CTYPE, "Spanish");
	bool bandera=true;
	char modelo[7]="";
	int opcion=0;
	int idpedido=0;
	char estado[10]="Entregado";
	float total=0;
	Detalle dato2;
	Pedido dato = {};
	
	if(!(arch=fopen("encabezado.xls", "r"))){
		printf("Error al intentar leer archivo");
		exit(1);
	}
	while(!feof(arch)){
		fscanf(arch, "%d\t", &dato.idPedido );
		fscanf(arch, "%d\t", &dato.cliente.idCliente);
		fscanf(arch, "%[^\t]\t", dato.cliente.nombre );
		fscanf(arch, "%s\t", dato.estado);
		fscanf(arch, "%s\t", dato.cliente.tel);
		fscanf(arch, "%s\n", dato.cliente.correo );
			
		if(strcmp(dato.estado,estado)==0){
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
			printf("Numero de Pedido: %d", dato.idPedido);
			printf("\nId Cliente: %d", dato.cliente.idCliente);
			printf("\nNombre: %s", dato.cliente.nombre);
			printf("\nEstado: ");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
			printf("%s", dato.estado);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
			printf("\nTelefono: %s", dato.cliente.tel);
			printf("\nCorreo: %s", dato.cliente.correo);
			printf("\n-------------------------\n");
		}	
	}
	fclose(arch);
	
	do{
		if(!(arch=fopen("encabezado.xls", "r"))){
			printf("Error al intentar leer archivo");
			exit(1);
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),02);
		idpedido = validaEntero("Ingresa el Id del Pedido: ");
		fflush(stdin);
		
		while(!feof(arch)){
			fscanf(arch, "%d\t", &dato.idPedido );
			fscanf(arch, "%d\t", &dato.cliente.idCliente);
			fscanf(arch, "%[^\t]\t", dato.cliente.nombre );
			fscanf(arch, "%s\t", dato.estado);
			fscanf(arch, "%s\t", dato.cliente.tel);
			fscanf(arch, "%s\n", dato.cliente.correo );
				
			if(dato.idPedido == idpedido){
				system("cls");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
				printf("Numero de Pedido: %d", dato.idPedido);
				printf("\nId Cliente: %d", dato.cliente.idCliente);
				printf("\nNombre: %s", dato.cliente.nombre);
				printf("\nEstado: %s", dato.estado);
				printf("\nTelefono: %s", dato.cliente.tel);
				printf("\nCorreo: %s", dato.cliente.correo);
				bandera=false;
			}
		}
		if(bandera == true){
			printf("No se encuentra el pedido\n");
		}
		fclose(arch);
	}while(bandera);

	
	if(!(arch=fopen("detalle.xls", "r"))){
		printf("Error al intentar leer archivo");
		exit(1);
	}
			
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),13);
	printf("\n\nModelo\tCantidad\tPrecio Unitario\tSub Total\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
			
	while(!feof(arch)){
		fscanf(arch, "%d\t", &dato2.idPedido );
		fscanf(arch, "%d\t", &dato2.cantidad);
		fscanf(arch, "%f\t", &dato2.subtotal);
		fscanf(arch, "%[^\t]\t", dato2.modelo);
		fscanf(arch, "%d\t", &dato2.existencias);
		fscanf(arch, "%f\n", &dato2.precio);
				
		if(dato2.idPedido == idpedido){
			printf("%s\t", dato2.modelo);
			printf("%d\t\t", dato2.cantidad);
			printf("%.2f\t\t", dato2.precio);
			printf("%.2f\n", dato2.subtotal);
			total=total+dato2.subtotal;			
		}	
	}
	fclose(arch);
			
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),13);
	printf("\t\t\tTOTAL\t\t");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
	printf("%.2f", total);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);

}
void consultapedidosCancelados(){
	setlocale(LC_CTYPE, "Spanish");
	bool bandera=true;
	char modelo[7]="";
	int opcion=0;
	int idpedido=0;
	char estado[10]="Cancelado";
	float total=0;
	Detalle dato2;
	Pedido dato = {};
	
	if(!(arch=fopen("encabezado.xls", "r"))){
		printf("Error al intentar leer archivo");
		exit(1);
	}
	while(!feof(arch)){
		fscanf(arch, "%d\t", &dato.idPedido );
		fscanf(arch, "%d\t", &dato.cliente.idCliente);
		fscanf(arch, "%[^\t]\t", dato.cliente.nombre );
		fscanf(arch, "%s\t", dato.estado);
		fscanf(arch, "%s\t", dato.cliente.tel);
		fscanf(arch, "%s\n", dato.cliente.correo );
			
		if(strcmp(dato.estado,estado)==0){
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
			printf("Numero de Pedido: %d", dato.idPedido);
			printf("\nId Cliente: %d", dato.cliente.idCliente);
			printf("\nNombre: %s", dato.cliente.nombre);
			printf("\nEstado: ");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),4);
			printf("%s", dato.estado);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
			printf("\nTelefono: %s", dato.cliente.tel);
			printf("\nCorreo: %s", dato.cliente.correo);
			printf("\n-------------------------\n");
		}	
	}
	fclose(arch);

}

void numpedido(){
	setlocale(LC_CTYPE, "Spanish");
	bool bandera=true;
	char modelo[7]="";
	int opcion=0;
	int idpedido=0;
	float total=0;
	Detalle dato2;
	Pedido dato = {};
	
	do{
		if(!(arch=fopen("encabezado.xls", "r"))){
			printf("Error al intentar leer archivo");
			exit(1);
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),02);
		idpedido = validaEntero("Ingresa el Id del Pedido: ");
		fflush(stdin);
		
		while(!feof(arch)){
		
			
			fscanf(arch, "%d\t", &dato.idPedido );
			fscanf(arch, "%d\t", &dato.cliente.idCliente);
			fscanf(arch, "%[^\t]\t", dato.cliente.nombre );
			fscanf(arch, "%s\t", dato.estado);
			fscanf(arch, "%s\t", dato.cliente.tel);
			fscanf(arch, "%s\n", dato.cliente.correo );
				
			if(dato.idPedido == idpedido){
				system("cls");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
				printf("Numero de Pedido: %d", dato.idPedido);
				printf("\nId Cliente: %d", dato.cliente.idCliente);
				printf("\nNombre: %s", dato.cliente.nombre);
				printf("\nEstado: %s", dato.estado);
				printf("\nTelefono: %s", dato.cliente.tel);
				printf("\nCorreo: %s", dato.cliente.correo);
				bandera=false;
			}
		}
		if(bandera == true){
			printf("No se encuentra el pedido\n");	
		}
		fclose(arch);
	}while(bandera);
	
	
	if(!(arch=fopen("detalle.xls", "r"))){
		printf("Error al intentar leer archivo");
		exit(1);
	}
			
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),13);
	printf("\n\nModelo\tCantidad\tPrecio Unitario\tSub Total\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
			
	while(!feof(arch)){
		fscanf(arch, "%d\t", &dato2.idPedido );
		fscanf(arch, "%d\t", &dato2.cantidad);
		fscanf(arch, "%f\t", &dato2.subtotal);
		fscanf(arch, "%[^\t]\t", dato2.modelo);
		fscanf(arch, "%d\t", &dato2.existencias);
		fscanf(arch, "%f\n", &dato2.precio);
				
		if(dato2.idPedido == idpedido){
			printf("%s\t", dato2.modelo);
			printf("%d\t\t", dato2.cantidad);
			printf("%.2f\t\t", dato2.precio);
			printf("%.2f\n", dato2.subtotal);
			total=total+dato2.subtotal;			
		}	
	}
	fclose(arch);
			
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),13);
	printf("\t\t\tTOTAL\t\t");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
	printf("%.2f", total);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);

}
void registrarEntrega(){
	setlocale(LC_CTYPE, "Spanish");
	Pedido dato;
	FILE *arch3;
	char estado[7]="Activo";
	int id=0;	
	bool bandera = false;
	
	if(!(arch=fopen("encabezado.xls", "r"))){
		printf("Error al intentar leer archivo");
		exit(1);
	}
	while(!feof(arch)){
		fscanf(arch, "%d\t", &dato.idPedido );
		fscanf(arch, "%d\t", &dato.cliente.idCliente);
		fscanf(arch, "%[^\t]\t", dato.cliente.nombre );
		fscanf(arch, "%s\t", dato.estado);
		fscanf(arch, "%s\t", dato.cliente.tel);
		fscanf(arch, "%s\n", dato.cliente.correo );
			
		if(strcmp(dato.estado,estado)==0){
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
			printf("Numero de Pedido: %d", dato.idPedido);
			printf("\nId Cliente: %d", dato.cliente.idCliente);
			printf("\nNombre: %s", dato.cliente.nombre);
			printf("\nEstado: %s", dato.estado);
			printf("\nTelefono: %s", dato.cliente.tel);
			printf("\nCorreo: %s", dato.cliente.correo);
			printf("\n-------------------------\n");
		}	
	}
	fclose(arch);
	
	if(!(arch=fopen("encabezado.xls", "r"))){
		printf("Error al intentar leer archivo");
		exit(1);
	}
	if(!(arch3=fopen("copy.xls", "a+"))){
		printf("Error al intentar crear archivo");
		exit(1);
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),02);
	id = validaEntero("Ingresa el Id del Pedido a Entregar: ");
	fflush(stdin);
		
	while(!feof(arch)){		
		fscanf(arch, "%d\t", &dato.idPedido );
		fscanf(arch, "%d\t", &dato.cliente.idCliente);
		fscanf(arch, "%[^\t]\t", dato.cliente.nombre );
		fscanf(arch, "%s\t", dato.estado);
		fscanf(arch, "%s\t", dato.cliente.tel);
		fscanf(arch, "%s\n", dato.cliente.correo );
				
		if(dato.idPedido == id){
			system("cls");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
			strcpy(dato.estado, "Entregado");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
			printf("\n----El pedido se ha entregado-----\n\n");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
			printf("Numero de Pedido: %d", dato.idPedido);
			printf("\nId Cliente: %d", dato.cliente.idCliente);
			printf("\nNombre: %s", dato.cliente.nombre);
			printf("\nEstado: %s", dato.estado);
			printf("\nTelefono: %s", dato.cliente.tel);
			printf("\nCorreo: %s", dato.cliente.correo);
			bandera=true;
		}
		
		fprintf(arch3, "%d\t", dato.idPedido );
		fprintf(arch3, "%d\t", dato.cliente.idCliente );
		fprintf(arch3, "%s\t", dato.cliente.nombre );
		fprintf(arch3, "%s\t", dato.estado );
		fprintf(arch3, "%s\t", dato.cliente.tel);
		fprintf(arch3, "%s\n", dato.cliente.correo);
			
	}
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
	if(bandera==false)printf("No se encuentra el registro");	
	else printf("\n\nRegistros del almacén actualizados\n\n");
	
	fclose(arch3);
	fclose(arch);
	remove("encabezado.xls");
	rename("copy.xls", "encabezado.xls");
	
}

void modificaestado(){
	setlocale(LC_CTYPE, "Spanish");
	Pedido dato;
	FILE *arch4;
	FILE *arch5;
	char estado[7]="Activo";
	char estado2[10]="Cancelado";
	int id=0;
	int opc=0;
	bool bandera = false;
	
	do{
		system("cls");
		printf("¿Qué desea hacer?\n\n");
		printf("1.- Cancelar un pedido\n");
		printf("2.- Reactivar un pedido\n");
		printf("0.- Regresar\n");
		opc = validaEntero("Selecciona una opción: ");
		system("cls");
		switch(opc){
			case 1:
				if(!(arch=fopen("encabezado.xls", "r"))){
					printf("Error al intentar leer archivo");
					exit(1);
				}
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
				printf("Pedidos Activos\n");
				while(!feof(arch)){
					fscanf(arch, "%d\t", &dato.idPedido );
					fscanf(arch, "%d\t", &dato.cliente.idCliente);
					fscanf(arch, "%[^\t]\t", dato.cliente.nombre );
					fscanf(arch, "%s\t", dato.estado);
					fscanf(arch, "%s\t", dato.cliente.tel);
					fscanf(arch, "%s\n", dato.cliente.correo );
						
					if(strcmp(dato.estado,estado)==0){			
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
						printf("Numero de Pedido: %d", dato.idPedido);
						printf("\nId Cliente: %d", dato.cliente.idCliente);
						printf("\nNombre: %s", dato.cliente.nombre);
						printf("\nEstado: %s", dato.estado);
						printf("\nTelefono: %s", dato.cliente.tel);
						printf("\nCorreo: %s", dato.cliente.correo);
						printf("\n-------------------------\n");
					}	
				}
				fclose(arch);
				
				if(!(arch=fopen("encabezado.xls", "r"))){
					printf("Error al intentar leer archivo");
					exit(1);
				}
				if(!(arch4=fopen("copi.xls", "a+"))){
					printf("Error al intentar leer archivo");
					exit(1);
				}
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
				id = validaEntero("\nIngresa el Id del pedido a cancelar: ");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
				
				while(!feof(arch)){
					fscanf(arch, "%d\t", &dato.idPedido );
					fscanf(arch, "%d\t", &dato.cliente.idCliente);
					fscanf(arch, "%[^\t]\t", dato.cliente.nombre );
					fscanf(arch, "%s\t", dato.estado);
					fscanf(arch, "%s\t", dato.cliente.tel);
					fscanf(arch, "%s\n", dato.cliente.correo );
						
					if(id == dato.idPedido){			
						strcpy(dato.estado, "Cancelado");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
						printf("\n------El pedido ha sido cancelado-------\n\n");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
						printf("Numero de Pedido: %d", dato.idPedido);
						printf("\nId Cliente: %d", dato.cliente.idCliente);
						printf("\nNombre: %s", dato.cliente.nombre);
						printf("\nEstado: %s", dato.estado);
						printf("\nTelefono: %s", dato.cliente.tel);
						printf("\nCorreo: %s", dato.cliente.correo);
						bandera=true;
					}	
					fprintf(arch4, "%d\t", dato.idPedido );
					fprintf(arch4, "%d\t", dato.cliente.idCliente );
					fprintf(arch4, "%s\t", dato.cliente.nombre );
					fprintf(arch4, "%s\t", dato.estado );
					fprintf(arch4, "%s\t", dato.cliente.tel);
					fprintf(arch4, "%s\n", dato.cliente.correo);
				}
				fclose(arch4);
				fclose(arch);
				remove("encabezado.xls");
				rename("copi.xls", "encabezado.xls");
				
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
				if(bandera==false)printf("No se encuentra el registro");
				else printf("\nPedidos actualizados\n\n");
				getch();
				break;
			case 2:
				if(!(arch=fopen("encabezado.xls", "r"))){
					printf("Error al intentar leer archivo");
					exit(1);
				}
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
				printf("Pedidos Cancelados\n");
				while(!feof(arch)){
					fscanf(arch, "%d\t", &dato.idPedido );
					fscanf(arch, "%d\t", &dato.cliente.idCliente);
					fscanf(arch, "%[^\t]\t", dato.cliente.nombre );
					fscanf(arch, "%s\t", dato.estado);
					fscanf(arch, "%s\t", dato.cliente.tel);
					fscanf(arch, "%s\n", dato.cliente.correo );
						
					if(strcmp(dato.estado,estado2)==0){			
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
						printf("Numero de Pedido: %d", dato.idPedido);
						printf("\nId Cliente: %d", dato.cliente.idCliente);
						printf("\nNombre: %s", dato.cliente.nombre);
						printf("\nEstado: %s", dato.estado);
						printf("\nTelefono: %s", dato.cliente.tel);
						printf("\nCorreo: %s", dato.cliente.correo);
						printf("\n-------------------------\n");
					}	
				}
				fclose(arch);
				
				if(!(arch=fopen("encabezado.xls", "r"))){
					printf("Error al intentar leer archivo");
					exit(1);
				}
				if(!(arch5=fopen("otra.xls", "a+"))){
					printf("Error al intentar leer archivo");
					exit(1);
				}
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
				id = validaEntero("\nIngresa el Id del pedido a reactivar: ");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
				
				while(!feof(arch)){
					fscanf(arch, "%d\t", &dato.idPedido );
					fscanf(arch, "%d\t", &dato.cliente.idCliente);
					fscanf(arch, "%[^\t]\t", dato.cliente.nombre );
					fscanf(arch, "%s\t", dato.estado);
					fscanf(arch, "%s\t", dato.cliente.tel);
					fscanf(arch, "%s\n", dato.cliente.correo );
						
					if(id == dato.idPedido){			
						strcpy(dato.estado, "Activo");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
						printf("\n-------El pedido ha sido reactivado-------\n\n");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
						printf("Numero de Pedido: %d", dato.idPedido);
						printf("\nId Cliente: %d", dato.cliente.idCliente);
						printf("\nNombre: %s", dato.cliente.nombre);
						printf("\nEstado: %s", dato.estado);
						printf("\nTelefono: %s", dato.cliente.tel);
						printf("\nCorreo: %s", dato.cliente.correo);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
						bandera=true;
					}	
					fprintf(arch5, "%d\t", dato.idPedido );
					fprintf(arch5, "%d\t", dato.cliente.idCliente );
					fprintf(arch5, "%s\t", dato.cliente.nombre );
					fprintf(arch5, "%s\t", dato.estado );
					fprintf(arch5, "%s\t", dato.cliente.tel);
					fprintf(arch5, "%s\n", dato.cliente.correo);
				}
				fclose(arch5);
				fclose(arch);
				remove("encabezado.xls");
				rename("otra.xls", "encabezado.xls");
				
				if(bandera==false)printf("No se encuentra el registro");
				else printf("\nPedidos actualizados\n\n");
				getch();
				break;
			case 0:
				break;
			default:
				printf("Opcion no válida\n");
				getch();
				break;
		}
	}while(opc!=0);
}
