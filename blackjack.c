/**
 * @file BlackJack.c
 *
 * @brief TODO
 *
 * @author  Ismael <ismael@ismael-XPS-13-9380>
 * @version 2025-12-24
 *
 **/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "intro.h"
#include "stdbool.h"
#include "dibujo.h"

char cartas [14][3] = {"0","A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};

typedef enum palos {PALO, CUADRADO, TRIANGULO, CIRCULO} palo_t;

void pedir (int *actual, int *total, int *mostrar, bool crupier, bool pintar);

void UI (int *mostrar, int *total, int *mostrar_crup, int *total_crup, float apuesta);

void ajustar_cuentas (float *fondos, float *universidad);

void pinta_carta (int palo,int numero);

int main (void) {
    
    clear_terminal();
    int j_actual;
    int j_total;
    int carta_mostrar;
    int *mostrar = &carta_mostrar;
    int *j_act_ptr = &j_actual;
    int *j_tot_ptr = &j_total;
   
    
    int c_actual;
    int c_total;
    int c_mostrar;
    int *c_act_ptr = &c_actual;
    int *c_tot_ptr = &c_total;
    int *c_mos_ptr = &c_mostrar;
    
    float apuesta;
    float fondos = 1000;
    float *fondos_ptr = &fondos;
    float universidad_hijos = 10000;
    float *uni_ptr = &universidad_hijos;
    bool juego = true;
    int input;
    bool doblar = false;
    
    

    do{
        
    j_actual = 0;
    j_total= 0;
    c_actual = 0;
    c_total = 0;
    juego = true;
    doblar = false;
    
    if (fondos <= 0) {
        ajustar_cuentas (fondos_ptr, uni_ptr);
    }
    
    printf("\n================================================================================");
    printf("\n=========================CRAZY          WIN=====================================");
    printf("\n================================================================================");
    printf("\nBienvenido al simulador de Blackjack\n");
    sleep (1);
    printf("Aquí podrás elegir otra forma para gastar los fondos universitarios de tus hijos\n");
    sleep(1);
    printf("Elige la cantidad a apostar (fondos = %.2f euros)\n", fondos);
    printf("Escribe 0 para hacer CASH OUT\n");
    do {
        apuesta = get_user_float();
        if (apuesta > fondos) {
            printf("No puedes apostar mas dinero del que tienes\n");
        }
        else if(apuesta < 0) {
            printf("No puedes apostar dinero negativo\n");
        }
    } while ((apuesta > fondos) || (apuesta < 0));
    
    if (apuesta == 0) {
        clear_terminal();
        printf("Parece que vas a llevarte el dinero que has apostado\n");
        sleep (2);
        printf("Vaya, parece que el servidor que tenia tu dinero se ha caido\n");
        sleep (2);
        printf("De hecho,no hay ningun registro de que hayas apostado nada\n");
        sleep (2);
        printf("De hecho, se han borrado todas las pruebas de que este casino siquiera existia\n");
        sleep (2);
        printf("Es como si este casino nunca hubiese existido\n");
        sleep (2);
        printf("Asi que parece que te quedaste sin dinero\n");
        sleep (2);
        printf("Que hemos aprendido hoy?\n");
        sleep (2);
        printf("La casa siempre gana\n");
        sleep(2);            
        printf("Para mas programas puedes comprar la subscripcion a Codigos Lamsallak por 12.99 euros/mes \n");
        sleep(2);
        printf("Aunque viendo como has manejado el dinero dudo que puedas :(\n");
        return 0;
    }
    
    printf ("%2f",apuesta);
    
    clear_terminal();
    
    srand (clock());
    
    pedir (j_act_ptr, j_tot_ptr, mostrar, false, true);
    
    printf ("carta recibida: %s, total:%d\n", cartas[carta_mostrar], *j_tot_ptr);
    
    pedir (j_act_ptr, j_tot_ptr, mostrar, false, true);
    
    printf ("carta recibida:%s, total:%d\n", cartas[carta_mostrar], *j_tot_ptr);
    
    printf ("CRUPIER\n");
    
    pedir (c_act_ptr, c_tot_ptr, c_mos_ptr, true, false);
    
    pedir (c_act_ptr, c_tot_ptr, c_mos_ptr, true, true);
    
    printf("Escriba cualquier numero para continuar\n");
    
    get_user_int();
    
    if (j_total == 21) {
        printf("Sumas 21, por lo que ganas automaticamente\n");
        sleep (2);
        fondos = fondos + apuesta*2;
        juego = false;
        clear_terminal();
    }
    
    while (juego == true) {
        UI (mostrar, j_tot_ptr, c_mos_ptr, c_tot_ptr, apuesta);
        input = get_user_int();
        if (input == 1) {
            clear_terminal();
            if (doblar == false) {
                pedir (j_act_ptr, j_tot_ptr, mostrar, false, true);
                if (j_total > 21) {
                    juego = false;
                    printf ("carta recibida:%s, total:%d\n", cartas[carta_mostrar], j_total);
                    printf ("Te has pasado de 21\n");
                    sleep (1);
                    printf ("PIERDES\n");
                    fondos = fondos - apuesta;
                    sleep (5);
                    clear_terminal();
                }
            }
            else {
            printf ("No puedes pedir mas cartas porque has doblado la apuesta\n");
            sleep (2);
            }
        }
        else if (input == 2) {
            juego = false;
            clear_terminal();
            printf ("TOTAL Crupier: %d\n", *c_tot_ptr);
            sleep (2);
            
            if (c_total < 17) {
                do{ 
                    printf ("El crupier pide otra carta:\n");
                    pedir (c_act_ptr, c_tot_ptr, c_mos_ptr, true, true);
                    printf ("CRUPIER recibe: %s, total:%d\n", cartas[c_mostrar], c_total);
                    sleep (2);
                } while (c_total < 17);
            }
            printf ("El crupier no pide mas cartas:\n");
            sleep (1);
            printf ("TOTAL Crupier: %d\n", *c_tot_ptr);
            printf ("TOTAL TU: %d\n", *j_tot_ptr);
            if (c_total > 21) {
                printf ("El crupier se ha pasado de 21\n");
                sleep (2);
                printf ("GANAS\n");
                sleep (5);
                fondos = fondos + apuesta;
            }
            else if (j_total > c_total) {
                printf ("GANAS\n");
                sleep (5);
                fondos = fondos + apuesta;
            }
            else if (j_total < c_total) {
                printf ("PIERDES\n");
                 sleep (5);
                 fondos = fondos - apuesta;
            }
            else {
                printf ("EMPATE\n");
                 sleep (5);
            }
            clear_terminal();
        }
        else if (input == 3) {
            clear_terminal();
            if (doblar ==  false) {
                if (fondos < 2*apuesta) {
                    printf ("No puedes doblar porque no tienes suficiente dinero\n");
                    sleep (2);
                }
                else {
                    apuesta = 2*apuesta;
                    pedir (j_act_ptr, j_tot_ptr, mostrar, false, true);
                    printf ("carta recibida:%s, total:%d\n", cartas[carta_mostrar], j_total);
                    if (j_total > 21) {
                        juego = false;
                        printf ("carta recibida:%s, total:%d\n", cartas[carta_mostrar], j_total);
                        printf ("Te has pasado de 21\n");
                        sleep (1);
                        printf ("PIERDES\n");
                        fondos = fondos - apuesta;
                        sleep (5);
                        clear_terminal();
                    }
                    printf ("No vas a poder pedir mas cartas ni volver a doblar\n");
                    sleep (2);
                    doblar = true;
            }
        }
                else {
                    printf ("No puedes volver a doblar\n");
                    sleep (2);
                }
        }
    }
    
    juego = true;
    
    
    } while (true);
    


    
    
    return 0;
}

void pedir (int *actual, int *total, int *mostrar, bool crupier, bool pintar) {
    int random = 0;
    int palo;
        
    random = (rand () % 12) + 1;
    palo = rand() % 4;
    
    *mostrar = random;
    
    if (pintar == true) {
        pinta_carta (palo, *mostrar);
    }
    
    if (random > 10) {
        random = 10;
    }
    else if (random == 1) {
        if (crupier == false){
            int input = 0;
            do {
                printf ("Ha salido A, puedes elegir entre que valga 1 o 11, elige\n");
                printf ("el valor que quieres que tome:");
                printf ("AHORA MISMO TIENES %d\n", *total);
                input = get_user_int();
                if (input == 1) {
                    random = 1;
                }
                else if (input == 11) {
                    random = 11;
                }
                else {
                    clear_terminal();
                }
            } while (input != 1 && input != 11);
        } 
        else {
            if ((*total + 11) > 21) {
                random = 1;
            }
            else {
                random = 11;
            }
        }
    }
    
    
    *actual = random;
    
    *total += *actual;

    
}

void UI (int *mostrar, int *total, int *mostrar_crup, int *total_crup, float apuesta) {
    clear_terminal();
    
    printf("\n================================================================================");
    printf("\n=========================CRAZY          WIN=====================================");
    printf("\n================================================================================\n");
    printf ("\nAPUESTA = %.2f\n\nCRUPIER:\n", apuesta);
    printf ("CARTAS:  %s    *", cartas[*mostrar_crup]);
    printf ("\n\n\nTU:\n");
    printf ("ultima carta recibida:%s, total:%d\n", cartas[*mostrar], *total);
    printf ("\n\nElije que hacer:\n 1)pedir otra carta, 2)quedarse, 3)doblar\n");
}

void ajustar_cuentas (float *fondos, float *universidad) {
        float tmp;
        clear_terminal();
        printf("Te has quedado sin dinero\n");
        sleep (2);
        if (*universidad > 0) {
            printf("Pero te queda el fondo universitario de tus hijos :)\n");
            sleep (2);  
            printf("Venga va se que vas a gastarlo en las apuestas\n");
            sleep (2);  
            printf("Yo no juzgo :)\n");
            sleep (2);  
            printf ("FONDO UNIVERSITARIO: %.2f\n", *universidad);
            do {
                printf("Elije cuanto sacar\n");
                tmp = get_user_float();
                if (tmp > *universidad) {
                    printf("No puedes endeudar al puto banco\n");
                } else if (tmp < 1) {
                    printf("Venga va sabes que quieres llevarte al menos 1 euro\n");                    
                }
            } while ((tmp > *universidad) || (tmp < 1)) ;
            *fondos = tmp;
            *universidad = *universidad - tmp;
        }
        else {
            printf("Y tambien te has gastado todo el dinero de tus hijos\n");
            sleep (2);  
            printf("Eso tiene merito\n");
            sleep (2);  
            printf("Te voy a dar 1000 porque total les vas a perder igual\n");
            *fondos = 1000;
            sleep (2);  
        }
        clear_terminal();
}

void pinta_carta (int palo,int numero) {
    crea_ventana("CARTA",400,400);
    switch (palo) {
        case PALO:
            crea_circulo (50, 50, 50, "negro");
            crea_texto (100, 100, cartas[numero], "negro", 300);
            break;
        case CUADRADO:
            crea_rectangulo (25, 25, 75, 75, "negro");
            crea_texto (100, 100, cartas[numero], "negro", 300);
            break;
        case TRIANGULO:
            crea_circulo (50, 50, 50, "rojo");
            crea_texto (100, 100, cartas[numero], "rojo", 300);
            break;
        case CIRCULO:  
            crea_rectangulo (25, 25, 75, 75, "rojo");
            crea_texto (100, 100, cartas[numero], "rojo", 300);
            break;
    }
    pinta();
    sleep(2);
    destruye_ventana();
}


