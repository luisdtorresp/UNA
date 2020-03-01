/*
 * Trabajo Practico Computacion II (324) 2019-2 Universidad Nacional Abierta - Venezuela
 * 
 * Copyright 2020 Programado por Luis Torres <luisdtorresp@gmail.com>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * 
 * 
 */



#include <iostream>
#include <limits>
#include <string>
using namespace std;

/* =================	ESTRUCTURA DE DATOS		==============================
 */
struct listaPrecios 
{
	int n;
	int precios[999];
};

/* =================   		Funciones		   ===============================
 */
bool confirmar(string msj)
{
	char check;
	cout << msj << "? (S/N): ";
		//cin.ignore(10000,'\n');
		while (check != 's' || check != 'S' || check != 'n' || check != 'N')
		{
			cin >> skipws >> check;
			cin.ignore(10000,'\n');
			if (check == 's' || check == 'S')
			{
				return true;
			}		
			else if (check == 'n' || check == 'N') {break;}
			
			else cout << "Introduzca S ó N > ";
		}
	return false;
}


int validarDatos()
{
	int n;
	cin >> skipws >> n;
	//cin.ignore(10000,'\n');
	//~ //while (!validarDatos())			Usar funcion de validacion
	while (cin.fail() || n < 0)
	{
		cin.clear();
		cin.ignore(std::numeric_limits<int>::max(),'\n');
		cout << " Entrada Invalida " << endl;
		if (n < 0){ cout << "Solo se permiten numeros enteros positivos" << endl;}
		cout << "Ingrese de nuevo: ";
		cin >> n;
	}
	return n;
};

/* 				====  	Ordenamientos 		=====
 * 
 * Utilizan algoritmo de Ordenamiento Shell
 */
 
void intercambiar(int& x, int& y)		// Funcion auxiliar para el ordenamiento
{
	int aux3 = x;
	x = y;
	y = aux3;
}

void ordenAlgShell(int ar[], int n, char orden = 'a')
{
	
	
	int salto, i, j, k;
	salto = n / 2;
	while (salto > 0)
	{
		for (i = salto; i < n; i++)
		{
			j = i - salto;
			while (j >= 0)
			{
				k = j + salto;
				
				// Orden Ascedente o Descente segun sea elegido
				if (((orden == 'a' || orden == 'A') && ar[j] <= ar[k]) || ((orden == 'd' || orden == 'D' )&& ar[j] >= ar[k]))
					{j = -1;}			 // par de elementos ordenado
				else
				{
					intercambiar(ar[j], ar[j+1]);
					j -= salto;
				}
			}
		}
		salto = salto / 2;
	}
	return;
}


int estaOrdenada(int ar[], int n)		// Funcion auxiliar para la busqueda binaria
{
	int i,j;
	for ( i = 0; i < (n-1); i++)
	{
		if (ar[i] > ar[i+1])
		{ 
			for ( j = 0; j < (n-1); j++)
			{
				if (ar[j] < ar[j+1]){ return -1;}			//No esta ordenada
			}
			return 2;		// Ordenada Descendentemente
		}
	}
	return 0; 		// Ordenada Ascendentemente
	
}

/*				====   	Visualizaciones		=====
 */

void visualizaPrecios(const int ar[], int n, char orden = 'o') 			// Visualiza lista de precios
{
	int i;
	int arNuevo[n];
	for (i = 0; i<n; i++)			//Copiar Arreglo para no modificar el orden en que fue ingresado
	{	arNuevo[i] = ar[i];	}
	
		
	switch (orden)				// Evaluar el tipo de orden para mostrar
	{
		case 'a':
			ordenAlgShell(arNuevo, n, 'a');
			cout << "\n =========== Orden ASCENDENTE ========== " << endl;
			visualizaPrecios(arNuevo, n);
			break;
			
		case 'd':
			ordenAlgShell(arNuevo, n, 'd');
			cout << "\n =========== Orden DESCENDENTE ========== " << endl;
			visualizaPrecios(arNuevo, n);
			break;
			
		default:			// Orden ingresado
			for ( i = 0; i<n; ++i)		
			{
				if (i == 0){ cout << "[ ";}
				cout << arNuevo[i] << " ";
				if (i == n-1){ cout << "]" << endl;}
			}
	}
}


listaPrecios ingresoDatos(int nprecios = 16)
{
	int i;
	listaPrecios datos;
	
	datos.n = nprecios;
	datos.precios[nprecios] = {0};
	//int precios[n];
		
	cout << "\nCantidad de precios a ingresar [ " << datos.n << " ]"<< endl;
	
	//~ cin>> noskipws >> aux2;
	//~ cin.ignore(std::numeric_limits<int>::max(), '\n');

	
	if (confirmar("Cambiar cantidad"))
	{
		cout << "\nCantidad de meses a ingresar: ";
		datos.n = validarDatos();
		while (datos.n == 0 || datos.n > 999)
		{
			if (datos.n == 0)
			{
				cout << "Cantidad debe ser un numero entero mayor a cero\n> ";
				datos.n = validarDatos();
			}
			else 
			{
				cout << "Cantidad debe ser un numero menor que 1000\n> ";
				datos.n = validarDatos();
			}			
		}	
		
	}
	
	cout << "\nIngrese los ultimos " << datos.n << " precios, separados por un espacio:\n [ ";
	
	for (i = 0; i<datos.n ; i++)
	{
		datos.precios[i] = validarDatos();
		if (i == datos.n-1)
			{ 
			cout << " ]" << endl;
			cin.ignore(10000,'\n');
			}
			
	}
		
	cout << "\nUsted ingresó: ";
	visualizaPrecios(datos.precios, datos.n);
	

	if (confirmar("Modificar"))
	{
		datos = ingresoDatos(datos.n);
	}

	return datos;
}


/*				====	Busquedas	====
 *
 *		Utiliza algoritmo de Busqueda Binaria, la cual requiere que la lista
 *		este ordenada, en esta implementacion puede ser en forma ascendente
 *		o descendente para esto utiliza el retorno de la función auxiliar estaOrdenada(),
 *		por defecto realiza la busqueda en una lista con orden ascendente.
 */
int busqBinaria(int ar[], int n, int valor,int orden = 0)
{
	int ptmedio, bajo, alto;
	int valorCentral;
	bajo = 0;
	alto = n - 1;
	
	while (bajo <= alto)
	
	{
		ptmedio = (bajo + alto)/2;
		valorCentral = ar[ptmedio];
		if (valor == valorCentral)
			{return ptmedio;}
			
		else if (orden == 2)
		{		
			if (valor < valorCentral)
				{bajo = ptmedio + 1;}
			else
				{alto = ptmedio - 1;}
		}
		
		else
		{
			if (valor < valorCentral)
				{alto = ptmedio - 1;}
			else
				{bajo = ptmedio + 1;}
		}
	}
	return -1;
}

void buscarDatos(listaPrecios lista)
{
	int buscar, ordenada, i;
	int copiaPrecios[lista.n];
	for (i = 0; i<lista.n; i++)			//Copiar Arreglo para no modificar el orden en que fue ingresado
		{copiaPrecios[i] = lista.precios[i];}
		
	ordenada = estaOrdenada(lista.precios, lista.n);
	
	if (ordenada == -1)
	{

		ordenAlgShell(copiaPrecios, lista.n);	  
	}
	 
	cout << "Ingrese el precio a buscar: ";
	buscar = busqBinaria (copiaPrecios, lista.n, validarDatos(), ordenada);
	if (buscar != -1)
	{
		cout << "\n>  Elemento encontrado!" << endl;
		cout << "\t Se encuentra en la posicion " << buscar+1 << " de la lista de precios." << endl;
		if (ordenada == 2)
			{cout << "\t (Orden Descendente)" << endl;}
		else 
			{cout << "\t (Orden Ascendente)" << endl;}
	}
	else
	{
		cout << "Elemento no encontrado en la lista de precios.\n";
	}
}




/*================ 		MAIN - Ejecucion del Programa	 ========================
 */
int main()
{
	
	cout << "\n======================================================================\n\t\t\tBIENVENID@\n";
    cout << "\n __________    ________     __________       _______     ___     ___";
	cout << "\n|          |  |		\\  |          |    /        '.  |   |   |   |";
	cout << "\n|___    ___|  |   |¨¨¨\\  \\ '------,   /   /___/¨¨\\   |  |   |   |   |";
	cout << "\n    |  |      |   |   /  /   ____/   /           /   /  |   |___|   |";
	cout << "\n    |  |      |   '--/  /  ,´       /       ____/   /   |           | ";     
	cout << "\n    |  |      |    ____/   |__     \\      ,´       /    |_______    |  ";
	cout << "\n    |  |      |   |            \\    \\    /    ,---´             |   |";
	cout << "\n    |  |      |   |        ____/     |  /    /_______           |   |  ";
	cout << "\n    |  |      |   |       /         /  /            /           |   |";
	cout << "\n    |__|      |___|      |________ /  |____________/            |___|\n\n";
	
	bool salida = false;
	while (!salida)		// Menu del programa
	{
		int seleccion;
		
		
		
		cout << "\n\n> Modulos del programa:" << endl;
		cout << "\n\t1) Obj.6    (Ultimos Precios del arroz)";
		cout << "\n\t2) Obj.7    (Buscar precio de Rosas)" << endl;
		cout << "\n\t99) Salir del Programa" << endl;
		cout << "\n  Seleccione una opción:  ";
		seleccion = validarDatos();
		
		switch (seleccion)
		{
			case 1:
				listaPrecios preciosArroz;
				cout << "\n\n  ¨¨¨¨¨¨¨¨¨¨¨¨\tSUPERMERCADO\t¨¨¨¨¨¨¨¨¨¨¨¨" << endl;
				preciosArroz = ingresoDatos();
				visualizaPrecios(preciosArroz.precios, preciosArroz.n, 'd');  // Ver en orden Descendente
				if (confirmar("\nDesea buscar la posicion de un elemento"))
				{buscarDatos(preciosArroz);}
				cout << "\n =========== Orden original del Arreglo ========== " << endl;
				visualizaPrecios(preciosArroz.precios, preciosArroz.n);
							
				break;
			
			case 2:
				{
				listaPrecios rosas;
				rosas.n = 16;
				int i, preciosPredet[] = {17,19,21,22,24,26,29,31,32,33,35,36,37,39,40,45};  // Valores preestablecidos por el Trabajo Practico
				for (i = 0; i<rosas.n; i++)
				{ rosas.precios[i] = preciosPredet[i];}
				
				cout << "\n\n  **********\tFLORISTERIA\t***********" << endl;
				if (confirmar("\nDesea consultar algun precio para la rosas"))
				{buscarDatos(rosas);}
				}
				break;
				
			case 99:
				if (confirmar("\nSalir")) { salida = true;}		// Salida del programa
				break;
			
			
			default:
				cout << "\nDebe ingresar una de las opciones mostradas\n";
		}
		
		
	}
	
	cout << "\n\n\t\tHasta Luego...\n";
	cout << "\n======================================================================" << endl;
	return 0;
}

