/**************************************************************************/
/* File di intestazione della libreria gestisce insiemi di numeri reali
 * esportando le seguenti quattro funzioni. La prima funzione ha come
 * parametri di ingresso due insiemi e stabilisce ricorsivamente se
 * sono uguali. La seconda funzione ha come parametri di ingresso due
 * insiemi e restituisce la loro intersezione calcolata ricorsivamente.
 * La terza funzione ha come parametri di ingresso due insiemi e restituisce
 * la loro differenza calcolata ricorsivamente. La quarta funzione ha come
 * parametri di ingresso due insiemi e restituisce la loro differenza
 * simmetrica calcolata ricorsivamente.  */
/**************************************************************************/

/*****************************/
/* Inclusione delle librerie */
/*****************************/

#include <stdbool.h>
#include <stdlib.h>

/************************************/
/* Ridefinizione dei tipi esportati */
/************************************/

// TODO: chiedere a marco se questo tipo custom va definito anche all'interno del programma test (funziona anche senza)

typedef struct el_insieme
{
    float             valore;
    struct el_insieme *prossimo;
} el_insieme_t;

/********************************************/
/* Ridichiarazione delle funzioni esportate */
/********************************************/

/* Ridichiarazione della funzione che stabilisce
 * ricorsivamente se due insiemi sono uguali. */
extern bool verifica_uguaglianza(el_insieme_t *el_primo_insieme,    /* Elemento testa
                                                                     * del primo
                                                                     * insieme */
                                 el_insieme_t *el_secondo_insieme); /* Elemento
                                                                     * testa del
                                                                     * secondo insieme */

/* Ridichiarazione della funzione che restituisce l'intersezione
 * fra due insiemi calcolata ricorsivamente. */
extern el_insieme_t *calcola_intersezione(el_insieme_t *el_primo_insieme,    /* Elemento
                                                                              * testa del
                                                                              * primo
                                                                              * insieme */
                                          el_insieme_t *el_secondo_insieme); /* Elemento
                                                                              * testa del
                                                                              * secondo
                                                                              * insieme */

/* Ridichiarazione della funzione che restituisce la differenza
 * di due insiemi calcolata ricorsivamente. */
extern el_insieme_t *calcola_differenza(el_insieme_t *el_primo_insieme,    /* Elemento
                                                                            * testa del
                                                                            * primo insieme */
                                        el_insieme_t *el_secondo_insieme); /* Elemento testa
                                                                            * del secondo
                                                                            * insieme */

/* Ridichiarazione della funzione che restituisce la differenza
 * simmetrica di due insiemi calcolata ricorsivamente. */
extern el_insieme_t *calcola_diff_simm(el_insieme_t *el_primo_insieme,    /* Elemento testa
                                                                           * del primo
                                                                           * insieme */
                                       el_insieme_t *el_secondo_insieme); /* Elemento testa
                                                                           * del secondo
                                                                           * insieme */