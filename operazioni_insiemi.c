/**************************************************************************/
/* File di implementazione della libreria gestisce insiemi di numeri reali
 * esportando le seguenti quattro funzioni. La prima funzione ha come
 * parametri di ingresso due insiemi e stabilisce ricorsivamente se
 * sono uguali. La seconda funzione ha come  parametri di ingresso due
 * insiemi e restituisce la loro intersezione calcolata ricorsivamente.
 * La terza funzione ha come parametri di ingresso due insiemi e restituisce
 * la loro differenza calcolata ricorsivamente. La quarta funzione ha come
 * parametri di ingresso due insiemi e restituisce la loro differenza
 * simmetrica calcolata ricorsivamente.  */
/**************************************************************************/

/*****************************/
/* inclusione delle librerie */
/*****************************/

#include "operazioni_insiemi.h"

/******************************************/
/* Dichiarazione delle funzioni esportate */
/******************************************/

/* Dichiarazione della funzione che restituisce l'intersezione
 * fra due insiemi calcolata ricorsivamente. */
bool verifica_uguaglianza(el_insieme_t *el_primo_insieme,    /* Elemento testa
                                                              * del primo insieme */
                          el_insieme_t *el_secondo_insieme); /* Elemento testa
                                                              * del secondo insieme */

/* Dichiarazione della funzione che restituisce l'intersezione
* fra due insiemi calcolata ricorsivamente. */
el_insieme_t *calcola_intersezione(el_insieme_t *el_primo_insieme,    /* Elemento testa
                                                                       * del primo insieme */
                                   el_insieme_t *el_secondo_insieme); /* Elemento testa
                                                                       * del secondo insieme */

/* Dichiarazione della funzione che restituisce la differenza
* di due insiemi calcolata ricorsivamente. */
el_insieme_t *calcola_differenza(el_insieme_t *el_primo_insieme,    /* Elemento testa
                                                                     * del primo insieme */
                                 el_insieme_t *el_secondo_insieme); /* Elemento testa
                                                                     * del secondo insieme */

/* Dichiarazione della funzione che restituisce la differenza
* simmetrica di due insiemi calcolata ricorsivamente. */
el_insieme_t *calcola_diff_simm(el_insieme_t *el_primo_insieme,    /* Elemento testa
                                                                    * del primo insieme */
                                el_insieme_t *el_secondo_insieme); /* Elemento testa
                                                                    * del secondo insieme */

/****************************************/
/* Definizione delle funzioni esportate */
/****************************************/

/* Definizione della funzione che restituisce l'intersezione
 * fra due insiemi calcolata ricorsivamente. */
bool verifica_uguaglianza(el_insieme_t *el_primo_insieme,   /* Elemento testa
                                                             * del primo insieme */
                          el_insieme_t *el_secondo_insieme) /* Elemento testa
                                                             * del secondo insieme */
{
    /* Dichiarazione delle variabili locali alla funzione */
    bool risultato = true; /* Output: valore che indica se i due insiemi sono uguali */
    
    /* Verifica che il primo insieme non sia terminato */
    if (el_primo_insieme != NULL)
    {
        if (el_secondo_insieme != NULL)
        {
            /* Se nemmeno il secondo insieme è terminato,
             * verifico l'uguaglianza dei due valori in esame */
            if (el_primo_insieme->valore == el_secondo_insieme->valore)
            {
                /* Nel caso in cui i due valori corrispondano,
                 * eseguo il controllo per i prossimi due elementi */
                risultato = verifica_uguaglianza(el_primo_insieme->prossimo,
                                                 el_secondo_insieme->prossimo);
            }
            else
            {
                /* Nel caso in cui gli elementi siano diversi,
                 * allora non si ha l'uguaglianza */
                risultato = false;
            }
        }
        else
        {
            /* Nel caso in cui il primo insieme non sia terminato
             * ed il secondo si, allora non si ha l'uguaglianza */
            risultato = false;
        }
    }
    else
    {
        /* Nel caso in cui il primo insieme sia terminato, l'uguaglianza
         * si ha solo nel caso in cui lo sia anche il secondo */
        risultato = (el_secondo_insieme == NULL);
    }
    
    /* Restituzione del risultato dell'uguaglianza */
    return (risultato);
}

/* Definizione della funzione che restituisce l'intersezione
* fra due insiemi calcolata ricorsivamente. */
el_insieme_t *calcola_intersezione(el_insieme_t *el_primo_insieme,   /* Elemento testa
                                                                      * del primo insieme */
                                   el_insieme_t *el_secondo_insieme) /* Elemento testa
                                                                      * del secondo insieme */
{
    /* Dichiarazione delle variabili locali alla funzione */
    el_insieme_t *nuovo_el = NULL;
    
    if (el_primo_insieme != NULL &&
        el_secondo_insieme != NULL)
    {
        if (el_primo_insieme->valore < el_secondo_insieme->valore)
        {
            nuovo_el = calcola_intersezione(el_primo_insieme->prossimo,
                                            el_secondo_insieme);
        }
        else if (el_primo_insieme->valore > el_secondo_insieme->valore)
        {
            nuovo_el = calcola_intersezione(el_primo_insieme,
                                            el_secondo_insieme->prossimo);
        }
        else
        {
            nuovo_el = (el_insieme_t *) malloc(sizeof(el_insieme_t));
            nuovo_el->valore   = el_primo_insieme->valore;
            nuovo_el->prossimo = calcola_intersezione(el_primo_insieme->prossimo,
                                                      el_secondo_insieme->prossimo);
        }
    }
    return (nuovo_el);
}

/* Definizione della funzione che restituisce la differenza
* di due insiemi calcolata ricorsivamente. */
el_insieme_t *calcola_differenza(el_insieme_t *el_primo_insieme,   /* Elemento testa
                                                                    * del primo insieme */
                                 el_insieme_t *el_secondo_insieme) /* Elemento testa
                                                                    * del secondo insieme */
{
    /* Dichiarazione delle variabili locali alla funzione */
    el_insieme_t *nuovo_el = NULL;
    
    if (el_primo_insieme != NULL)
    {
        if (el_secondo_insieme != NULL)
        {
            if (el_primo_insieme->valore < el_secondo_insieme->valore)
            {
                nuovo_el = (el_insieme_t *) malloc(sizeof(el_insieme_t));
                nuovo_el->valore   = el_primo_insieme->valore;
                nuovo_el->prossimo = calcola_differenza(el_primo_insieme->prossimo,
                                                        el_secondo_insieme);
            }
            else if (el_primo_insieme->valore > el_secondo_insieme->valore)
            {
                nuovo_el = calcola_differenza(el_primo_insieme,
                                              el_secondo_insieme->prossimo);
            }
            else
            {
                nuovo_el = calcola_differenza(el_primo_insieme->prossimo,
                                              el_secondo_insieme->prossimo);
            }
        }
        else
        {
            nuovo_el = (el_insieme_t *) malloc(sizeof(el_insieme_t));
            nuovo_el->valore   = el_primo_insieme->valore;
            nuovo_el->prossimo = calcola_differenza(el_primo_insieme->prossimo,
                                                    el_secondo_insieme);
        }
    }
    return (nuovo_el);
}

/* Definizione della funzione che restituisce la differenza
* simmetrica di due insiemi calcolata ricorsivamente. */
el_insieme_t *calcola_diff_simm(el_insieme_t *el_primo_insieme,   /* Elemento testa
                                                                   * del primo insieme */
                                el_insieme_t *el_secondo_insieme) /* Elemento testa
                                                                   * del secondo insieme */
{
    /* Dichiarazione delle variabili locali alla funzione */
    el_insieme_t *nuovo_el = NULL;
    
    if (el_primo_insieme != NULL &&
        el_secondo_insieme != NULL)
    {
        if (el_primo_insieme->valore < el_secondo_insieme->valore)
        {
            nuovo_el = (el_insieme_t *) malloc(sizeof(el_insieme_t));
            nuovo_el->valore   = el_primo_insieme->valore;
            nuovo_el->prossimo = calcola_diff_simm(el_primo_insieme->prossimo,
                                                   el_secondo_insieme);
        }
        else if (el_primo_insieme->valore > el_secondo_insieme->valore)
        {
            nuovo_el = (el_insieme_t *) malloc(sizeof(el_insieme_t));
            nuovo_el->valore   = el_secondo_insieme->valore;
            nuovo_el->prossimo = calcola_diff_simm(el_primo_insieme,
                                                   el_secondo_insieme->prossimo);
        }
        else
        {
            nuovo_el = calcola_diff_simm(el_primo_insieme->prossimo,
                                         el_secondo_insieme->prossimo);
        }
    }
    else if (el_primo_insieme != NULL &&
             el_secondo_insieme == NULL)
    {
        nuovo_el = (el_insieme_t *) malloc(sizeof(el_insieme_t));
        nuovo_el->valore   = el_primo_insieme->valore;
        nuovo_el->prossimo = calcola_diff_simm(el_primo_insieme->prossimo,
                                               el_secondo_insieme);
        
    }
    else if (el_primo_insieme == NULL &&
             el_secondo_insieme != NULL)
    {
        nuovo_el = (el_insieme_t *) malloc(sizeof(el_insieme_t));
        nuovo_el->valore   = el_secondo_insieme->valore;
        nuovo_el->prossimo = calcola_diff_simm(el_primo_insieme,
                                               el_secondo_insieme->prossimo);
    }
    return (nuovo_el);
}