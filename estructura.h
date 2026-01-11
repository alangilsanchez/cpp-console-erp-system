void imprimirEstructura(){
	setlocale(LC_CTYPE, "Spanish");
	
	printf("\n\n----------Registros del Almacén----------\n\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),13);
	printf("MODELO\t");
	printf("Total\t");
	printf("Precio\t");
	printf("Ubicación\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);

	for(int i=0; i<10; i++){
		printf("%s\t", almacen[i].modelo);
		printf("%d\t", almacen[i].existencias);
		printf("%.2f\t", almacen[i].precio);
		printf("%s\n", almacen[i].ubicacion);
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
}

void crear_archivo(){
	//if(!(arch=fopen("almacen.txt", "w"))){
	if(!(arch=fopen("almacen.xls", "w"))){
		printf("Error al intentar crear el archivo");
		exit(1);
	}
	
	for(int i=0; i<10; i++){
		fprintf(arch,"%s\t", almacen[i].modelo);
		fprintf(arch,"%d\t", almacen[i].existencias);
		fprintf(arch,"%f\t", almacen[i].precio);
		fprintf(arch,"%s\n", almacen[i].ubicacion);
		
	}
	
	fclose(arch);
}

void leer_archivo(){
	setlocale(LC_CTYPE, "Spanish");
	Almacen dato;
	
	//if(!(arch=fopen("almacen.txt", "r"))){
	if(!(arch=fopen("almacen.xls", "r"))){
		printf("Error al intentar leer el archivo");
		exit(1);
	}
	
	printf("\n\n---------Registros en el Archivo---------\n\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),13);
	printf("MODELO\t");
	printf("Total\t");
	printf("Precio\t");
	printf("Ubicación\n");
	
	while(!feof(arch)){
		fscanf(arch,"%[^\t]\t", dato.modelo);
		fscanf(arch,"%d\t", &dato.existencias);
		fscanf(arch,"%f\t", &dato.precio);
		fscanf(arch,"%[^\n]\n", dato.ubicacion);
		
		//if
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
		printf("%s\t", dato.modelo);
		printf("%d\t", dato.existencias);
		printf("%.2f\t", dato.precio);
		printf("%s\n", dato.ubicacion);
	}
	fclose(arch);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
}

void consulta_estufas(){
	setlocale(LC_CTYPE, "Spanish");
	Almacen dato;
	
	if(!(arch=fopen("almacen.xls", "r"))){
		printf("Error al intentar leer el archivo");
		exit(1);
	}
	
	printf("\n\n----------Registros del Almacén----------\n\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),13);
	printf("MODELO\t");
	printf("Total\t");
	printf("Precio\t");
	printf("Ubicación\n");
	
	while(!feof(arch)){
		fscanf(arch,"%[^\t]\t", dato.modelo);
		fscanf(arch,"%d\t", &dato.existencias);
		fscanf(arch,"%f\t", &dato.precio);
		fscanf(arch,"%[^\n]\n", dato.ubicacion);
		
		if(dato.modelo[0]=='E' && dato.modelo[1]=='S' && dato.modelo[2]=='T'){
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
			printf("%s\t", dato.modelo);
			printf("%d\t", dato.existencias);
			printf("%.2f\t", dato.precio);
			printf("%s\n", dato.ubicacion);
		}	
	}
	
	fclose(arch);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
}

void consulta_hornos(){
	setlocale(LC_CTYPE, "Spanish");
	Almacen dato;
	
	if(!(arch=fopen("almacen.xls", "r"))){
		printf("Error al intentar leer el archivo");
		exit(1);
	}
	
	printf("\n\n----------Registros del Almacén----------\n\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),13);
	printf("MODELO\t");
	printf("Total\t");
	printf("Precio\t");
	printf("Ubicación\n");
	
	while(!feof(arch)){
		fscanf(arch,"%[^\t]\t", dato.modelo);
		fscanf(arch,"%d\t", &dato.existencias);
		fscanf(arch,"%f\t", &dato.precio);
		fscanf(arch,"%[^\n]\n", dato.ubicacion);
		
		if(dato.modelo[0]=='H' && dato.modelo[1]=='O' && dato.modelo[2]=='R'){
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
			printf("%s\t", dato.modelo);
			printf("%d\t", dato.existencias);
			printf("%.2f\t", dato.precio);
			printf("%s\n", dato.ubicacion);
		}	
	}
	
	fclose(arch);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
}

void modiRegAlmacen(){
	setlocale(LC_CTYPE, "Spanish");
	Almacen dato;
	FILE *arch2;
	char modelo[7];
	bool bandera=false;
	int respuesta=0;
	char estante[10]="ESTANTE ";
	char ubicacion[2]="";
	
	
	if(!(arch=fopen("almacen.xls", "r"))){
		printf("Error al intentar leer el archivo");
		exit(1);
	}
	if(!(arch2=fopen("copia.xls", "a+"))){
		printf("Error al intentar leer el archivo");
		exit(1);
	}
	
	printf("\nDame el modelo a modificar: ");
	scanf("%s",modelo);
	
	while(!feof(arch)){
		fscanf(arch,"%[^\t]\t", dato.modelo);
		fscanf(arch,"%d\t", &dato.existencias);
		fscanf(arch,"%f\t", &dato.precio);
		fscanf(arch,"%[^\n]\n", dato.ubicacion);
		
		if(strcmp(dato.modelo,modelo)==0){
			printf("\nDatos actuales del modelo\n\n");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),13);
			printf("Modelo\tExistencias\tPrecio\tUbicacion\n");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
			printf("%s\t", dato.modelo);
			printf("%d\t\t", dato.existencias);
			printf("%.2f\t", dato.precio);
			printf("%s\n", dato.ubicacion);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
			
			printf("\nDesea cambiar el numero de existencias del modelo? ");
			printf("1 para Si / 2 para No: ");
			scanf("%d", &respuesta);
			if(respuesta==1){
				dato.existencias = validaEntero("\nNueva existencia: ");
			}
			respuesta=0;
			printf("\nDesea cambiar el precio del modelo? ");
			printf("1 para Si / 2 para No: ");
			scanf("%d", &respuesta);
			if(respuesta==1){
				dato.precio = validaEntero("\nNuevo precio del modelo: ");
			}
			respuesta=0;
			printf("\nDesea cambiar la ubicacion del Estante? ");
			printf("1 para Si / 2 para No: ");
			scanf("%d", &respuesta);
			
			if(respuesta==1){
				fflush(stdin);
				validaCadena("Nueva ubicación en el almacen: ", ubicacion);
				strcat(estante,ubicacion);
				strcpy(dato.ubicacion,estante);
			}
			
			bandera=true;
		}
		fprintf(arch2,"%s\t",dato.modelo);
		fprintf(arch2,"%d\t",dato.existencias);
		fprintf(arch2,"%f\t",dato.precio);
		fprintf(arch2,"%s\n",dato.ubicacion);
	}
	if(bandera==false)printf("No se encuentra el registro");
	else printf("\nDatos actualizados\n\n");
	fclose(arch2);
	fclose(arch);
	remove("almacen.xls");
	rename("copia.xls","almacen.xls");
}

void agRegAlmacen(){
	setlocale(LC_CTYPE, "Spanish");
	Almacen dato;
	int i=0;
	char estante[10]="ESTANTE ";
	char modelo[7]="";
	bool bandera=true;
	
	if(!(arch=fopen("almacen.xls", "a+"))){
		printf("Error al intentar leer el archivo");
		exit(1);
	}
	
	printf("\nAgregar Registro:\n");
	printf("El modelo en caso de ser horno las primer 3 letras son HOR, en caso de estufa son EST, seguido de 3 numeros\n\n");
	
	while(bandera){
		i=0;
		printf("Modelo: ");
		scanf("%s", modelo);
		
		for(i=0; i<10; i++){
			if(strcmp(almacen[i].modelo,modelo)==0){
				printf("El modelo ya esta registrado\n");
				break;
			}		
		}

		if(i==10){
			if(modelo[0]=='E' || modelo[0]=='H'){
				if(modelo[1]=='S' || modelo[1]=='O'){
					if(modelo[2]=='T' || modelo[2]=='R'){
						strcpy(dato.modelo, modelo);
						dato.existencias = validaEntero("Existencias: ");
						dato.precio = validaFlotante("Precio: ");
						validaCadena("Ubicacion del ESTANTE: ", dato.ubicacion);
						
						strcat(estante,dato.ubicacion);
						strcpy(dato.ubicacion,estante);
							
						fprintf(arch,"%s\t",dato.modelo);
						fprintf(arch,"%d\t",dato.existencias);
						fprintf(arch,"%f\t",dato.precio);
						fprintf(arch,"%s\n",dato.ubicacion);
						
						bandera=false;
					}
				}
			}
		}
	}
	
	printf("\nRegistro agregado\n\n");
	
	fclose(arch);
}
