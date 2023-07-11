#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


void volver(char *tecla);


typedef struct Productos Productos;
struct Productos
{
    char nombre[30];
    int cantidad;
    float precio1;
    float precio2;
    int hora;
    int minuto;
};


int main()
{
    
    int opcion_usuario;
    int cantidad_productos;
    char nombre_proveedor[30];
    int cantidad;
    float precio_unitario;
    float precio_venta;
    int borrar_producto;
    FILE *archivo;
    char linea[100];
    char tecla;

    do
    {
        
        printf("\n-----------------MENU-------------\n");
        printf("1. Ver productos\n");
        printf("2. Registrar productos\n");
        printf("3. Borrar productos\n");
        printf("4. Salir del inventario\n");
        printf("------------------------------------\n");
        printf("Por favor seleccione una opcion: ");
        scanf("%d", &opcion_usuario);

        switch (opcion_usuario)
        {
        case 1:
            archivo = fopen("productos.txt", "r");
            if (archivo)
            {
                printf("\n------------------------------------- BODEGA ----------------------------------\n");
                printf("   NOMBRE            CANTIDAD        PRECIO UNITARIO        PRECIO VENTA    \n");
                printf("------------------------------------------------------------------------------------\n");
                
                while (fgets(linea, sizeof(linea), archivo) != NULL)
                {   
                    printf("%s", linea);
                }
            }
            printf("------------------------------------------------------------------------------------\n");

            fclose(archivo);
            volver(&tecla);
            break;

        case 2:
            printf("\nPor favor ingrese la cantidad de prudctos a registrar: ");
            scanf("%d", &cantidad_productos);

            
            Productos *lista = malloc(cantidad_productos * sizeof(Productos));

            for(int i = 0; i < cantidad_productos; i++)
            {
                printf("\nIngrese el nombre del consumidor: ");
                scanf("%s", nombre_proveedor);

                printf("Ingrese la cantidad de elementos del producto: ");
                scanf("%d", &cantidad);

                printf("Ingrese el precio unitario de compra/produccion del prodcuto: ");
                scanf("%f", &precio_unitario);

                printf("Ingrese el precio de venta del producto: ");
                scanf("%f", &precio_venta);
                
                
                strcpy(lista[i].nombre, nombre_proveedor);

                lista[i].cantidad = cantidad;
                lista[i].precio1 = precio_unitario;
                lista[i].precio2 = precio_venta;
            }
            
            
            int ancho_nombre = 0;
            for (int i = 0; i < cantidad_productos; i++)
            {
                int longitud = strlen(lista[i].nombre);
                if (longitud > ancho_nombre)
                {
                    ancho_nombre = longitud;
                }
            }

           
            archivo = fopen("productos.txt", "a");
            for(int i = 0; i < cantidad_productos; i++)
            {
                fprintf(archivo, "   %-*s", ancho_nombre, lista[i].nombre);
                fprintf(archivo, "                %d", lista[i].cantidad);
                fprintf(archivo, "               %.2f", lista[i].precio1);
                fprintf(archivo, "                  %.2f", lista[i].precio2);   
                fprintf(archivo, "\n");
            }
            fclose(archivo);
            free(lista);
            printf("\n");
            volver(&tecla);
            break;
        
        case 3:
            printf("\nPor favor ingrese el numero de linea que desea borrar: ");
            scanf("%d", &borrar_producto);

            archivo = fopen("productos.txt", "r");
            if (archivo)
            {
                
                int total_lineas = 0;
                while (fgets(linea, sizeof(linea), archivo) != NULL)
                {
                    total_lineas++;
                }

                fclose(archivo);

                
                if (borrar_producto >= 1 && borrar_producto <= total_lineas)
                {
                    archivo = fopen("productos.txt", "r");
                    if (archivo)
                    {
                        
                        FILE *temporal = fopen("temporal.txt", "w");
                        if (temporal)
                        {
                            int numero_linea = 1;

                            
                            while (fgets(linea, sizeof(linea), archivo) != NULL)
                            {
                                
                                if (numero_linea != borrar_producto)
                                {
                                    fprintf(temporal, "%s", linea);
                                }
                                numero_linea++;
                            }

                            fclose(temporal);
                            fclose(archivo);

                            
                            
                            remove("productos.txt");   

                            
                            rename("temporal.txt", "productos.txt");

                            printf("\nLinea borrada exitosamente.\n\n");
                        }
                    }
                }
                else
                {
                    printf("\nEl numero de linea esta fuera de rango.\n\n");
                }
            }
            volver(&tecla);
            break;

        case 4:
            printf("\nVuelve pronto!\n");
            break;

        default:
            printf("\nOpcion no valida, intenta otra vez\n\n");
            volver(&tecla);
            break;
        }
    } while (opcion_usuario != 4);

    return 0;
}


void volver(char *tecla)
{
    do
    {
        
        printf("Presiona la tecla 'v' para volver: ");
        scanf(" %c", tecla);

        
        if (!(isalpha(*tecla)))
        {
            printf("\nNo es una letra. Intenta otra vez\n\n");
        }
        
        else if (!(*tecla == 'v' || *tecla == 'V'))
        {
            printf("\nNo es la letra 'v'. Intenta otra vez\n\n");
        }
        
        else
        {
            system("cls");
            break;
        }
    } while (*tecla != 'v' || *tecla != 'V');
}