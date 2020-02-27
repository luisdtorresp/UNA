/*
 * Trabajo Practico COmputacion II 324 2019-2
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
#include <cstdio>
using namespace std;



/* =================   		Funciones		   ===============================
 */

bool validarDatos()
{
	
	return true;
};

/* ==================  		Ordenamientos 		============
 * 
 * Utilizan algoritmo de Ordenamiento Shell
 */
 
void intercambiar(int& x, int& y)		// Funcion auxiliar para el ordenamiento
{
	int aux3 = x;
	x = y;
	y = aux3;
}

void ordenAsc(int ar[], int n)
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
				if (ar[j] <= ar[k])
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

void ordenDesc(int ar[], int n)
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
				if (ar[j] >= ar[k])
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

/*===================   	Visualizaciones		 =========
 */

void visualizaPrecios(int ar[], int n) 			// Visualiza lista de precios
{
	for (int i = 0; i<n; ++i)		
	{
		if (i == 0){ cout << "[ ";}
		cout << ar[i] << " ";
		if (i == n-1){ cout << "]" << endl;}
	}
}

void verAscendente(int ar[], int n) 			// Visualiza lista de precios
{
	ordenAsc (ar, n);
	visualizaPrecios(ar, n);
}

void verDescendente(int ar[], int n) 			// Visualiza lista de precios
{
	ordenDesc(ar, n);
	visualizaPrecios(ar, n);
}

void ingresoDatos(int nprecios = 16)
{
	char aux2;
	int n = nprecios;
	int i;
	int precios[n];
	cout << "\nCantidad de precios a ingresar [ " << n << " ]\n\nIntroduzca S para modificar o Enter para continuar..." << endl << "> ";
	
	cin >> noskipws >> aux2;
	cin.ignore(10000,'\n');

	
	if (aux2 == 's' || aux2 == 'S')
	{
		
		cout << "Cantidad de meses a ingresar: ";
		cin >> skipws >> n;
		cin.ignore(10000,'\n');
		//~ //while (!validarDatos())			Usar funcion de validacion
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(10000,'\n');
			cout << " Entrada Invalida " << endl;
			cout << "Ingrese de nuevo: "
			;
			cin >> n;
		}
		
	}
	
	cout << "Ingrese los ultimos " << n << " precios, separados por un espacio:\n [ ";
	
	for (i = 0; i<n ; i++)
	{
		cin >> skipws >> precios[i];
		if (i == n-1)
			{ 
			cout << " ]" << endl;
			cin.ignore(10000,'\n');
			}
			
	}
		
	cout << "Usted ingresó: ";
	visualizaPrecios(precios, n);
	
	//char aux;
	cout << "Modificar? (S/N): ";
	//cin.ignore(10000,'\n');
	cin >> noskipws >> aux2;
	cin.ignore(10000,'\n');
	if (aux2 == 's' || aux2 == 'S')
	{
		ingresoDatos(n);
	}
	
	else
	{
		cout << " =========== Orden ASCENDENTE ========== " << endl;
		verAscendente(precios, n);
		cout << " =========== Orden DESCENDENTE ========== " << endl;
		verDescendente(precios, n);
		visualizaPrecios(precios, n);
	}
}



















/*================ MAIN - Ejecucion del Programa ==================
 */
int main()
{
	
	while (true)
	{
		char aux;
		cout << " ============================================\n\t\tBIENVENIDO\n";
		
		ingresoDatos();
		

		
		/* Salida del programa
		 * */
		cout << "Salir? (S/N): ";
		//cin.ignore(10000,'\n');
		cin >> skipws >> aux;
		cin.ignore(10000,'\n');
		if (aux == 's' || aux == 'S')
		{
			break;
		}		
		
		
	}
	cout << "\n\n\t\tHasta Luego...\n";
	return 0;
}

