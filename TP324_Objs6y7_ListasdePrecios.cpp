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
#include <limits>
#include <string>
using namespace std;



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
			
			else cout << "> ";
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
		cout << "Ingrese de nuevo: "
		;
		cin >> n;
	}
	return n;
};

/* 				====  		Ordenamientos 		============
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

/*				====   	Visualizaciones		 =========
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
	
	int n = nprecios;
	int i;
	int precios[n];
	cout << "\nCantidad de precios a ingresar [ " << n << " ]"<< endl;
	
	//~ cin>> noskipws >> aux2;
	//~ cin.ignore(std::numeric_limits<int>::max(), '\n');

	
	if (confirmar("Cambiar cantidad"))
	{
		cout << "\nCantidad de meses a ingresar: ";
		n = validarDatos();
		while (n == 0)
		{
			cout << "Cantidad debe ser un numero entero mayor a cero\n> ";
			n = validarDatos();
		}	
		
	}
	
	cout << "\nIngrese los ultimos " << n << " precios, separados por un espacio:\n [ ";
	
	for (i = 0; i<n ; i++)
	{
		precios[i] = validarDatos();
		if (i == n-1)
			{ 
			cout << " ]" << endl;
			cin.ignore(10000,'\n');
			}
			
	}
		
	cout << "\nUsted ingresó: ";
	visualizaPrecios(precios, n);
	

	if (confirmar("Modificar"))
	{
		ingresoDatos(n);
	}
	
	else
	{
		cout << " =========== Orden ASCENDENTE ========== " << endl;
		verAscendente(precios, n);
		cout << " =========== Orden DESCENDENTE ========== " << endl;
		verDescendente(precios, n);
		cout << " =========== Orden Final del Arreglo ========== " << endl;
		visualizaPrecios(precios, n);
	}
}









/*================ MAIN - Ejecucion del Programa ==================
 */
int main()
{
	
	while (true)		// Menu del programa
	{
		
		cout << " ============================================\n\t\tBIENVENIDO\n";
		
		ingresoDatos();
		
	
		if (confirmar("Salir")) {break;}		// Salida del programa

		
		
	}
	cout << "\n\n\t\tHasta Luego...\n";
	return 0;
}

