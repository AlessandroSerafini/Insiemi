/**************************************************************************/
/* File di implementazione della libreria gestisce insiemi di numeri reali
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
/* inclusione delle librerie */
/*****************************/

#include "operazioni_insiemi.h"

/******************************************/
/* Dichiarazione delle funzioni esportate */
/******************************************/

/* Dichiarazione della funzione che restituisce l'intersezione
 * fra due insiemi calcolata ricorsivamente. */
bool uguaglianza(el_insieme_t *el_insieme_1,    /* Elemento testa
                                                 * del primo
                                                 * insieme */
                 el_insieme_t *el_insieme_2);   /* Elemento testa
                                                 * del secondo
                                                 * insieme */

/* Dichiarazione della funzione che restituisce l'intersezione
* fra due insiemi calcolata ricorsivamente. */
el_insieme_t *intersezione(el_insieme_t *el_insieme_1,    /* Elemento
                                                           * testa del
                                                           * primo
                                                           * insieme */
                           el_insieme_t *el_insieme_2);   /* Elemento
                                                           * testa del
                                                           * secondo
                                                           * insieme */

/* Dichiarazione della funzione che restituisce la differenza
* di due insiemi calcolata ricorsivamente. */
el_insieme_t *differenza(el_insieme_t *el_insieme_1,    /* Elemento testa
                                                         * del primo
                                                         * insieme */
                         el_insieme_t *el_insieme_2);   /* Elemento testa
                                                         * del secondo
                                                         * insieme */

/* Dichiarazione della funzione che restituisce la differenza
* simmetrica di due insiemi calcolata ricorsivamente. */
el_insieme_t *diff_simm(el_insieme_t *el_insieme_1,    /* Elemento testa
                                                        * del primo
                                                        * insieme */
                        el_insieme_t *el_insieme_2);   /* Elemento testa
                                                        * del secondo
                                                        * insieme */

/****************************************/
/* Definizione delle funzioni esportate */
/****************************************/

/* Definizione della funzione che restituisce l'intersezione
 * fra due insiemi calcolata ricorsivamente. */
bool uguaglianza(el_insieme_t *el_insieme_1,   /* Lavoro: Elemento testa
                                                * del primo insieme */
                 el_insieme_t *el_insieme_2)   /* Lavoro: Elemento testa
                                                * del secondo insieme */
{
    /* Dichiarazione delle variabili locali alla funzione */
    bool risultato = true; /* Output: valore che indica se
                            * i due insiemi sono uguali */
    
    /* Verifica che il primo insieme non sia terminato */
    if (el_insieme_1 != NULL)
    {
        if (el_insieme_2 != NULL)
        {
            /* Se nemmeno il secondo insieme è terminato,
             * verifico l'uguaglianza dei due valori in esame */
            if (el_insieme_1->valore == el_insieme_2->valore)
            {
                /* Nel caso in cui i due valori corrispondano,
                 * eseguo il controllo per i prossimi due elementi */
                risultato = uguaglianza(el_insieme_1->prossimo,
                                        el_insieme_2->prossimo);
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
        risultato = (el_insieme_2 == NULL);
    }
    
    /* Restituzione del risultato dell'uguaglianza */
    return (risultato);
}

/* Definizione della funzione che restituisce l'intersezione
* fra due insiemi calcolata ricorsivamente. */
el_insieme_t *intersezione(el_insieme_t *el_insieme_1,   /* Lavoro: Elemento
                                                          * testa del primo
                                                          * insieme */
                           el_insieme_t *el_insieme_2)   /* Lavoro: Elemento
                                                          * testa del secondo
                                                          * insieme */
{
    /* Dichiarazione delle variabili locali alla funzione */
    el_insieme_t *nuovo_el = NULL; /* Output: Elemento testa
                                    * dell'insieme intersezione */
    
    /* Verifica che gli insiemi non siano terminati */
    if (el_insieme_1 != NULL &&
        el_insieme_2 != NULL)
    {
        if (el_insieme_1->valore < el_insieme_2->valore)
        {
            /* Nel caso in cui l'elemento del primo insieme sia minore dell'elemento
             * del secondo insieme, eseguo il controllo fra il successivo elemento
             * del primo insieme e l'elemento del secondo insieme */
            nuovo_el = intersezione(el_insieme_1->prossimo,
                                    el_insieme_2);
        }
        else if (el_insieme_1->valore > el_insieme_2->valore)
        {
            /* Nel caso in cui l'elemento del primo insieme sia maggiore dell'elemento
             * del secondo insieme, eseguo il controllo fra l'elemento del primo
             * insieme e il successivo elemento del secondo insieme */
            nuovo_el = intersezione(el_insieme_1,
                                    el_insieme_2->prossimo);
        }
        else
        {
            /* Altrimenti, nel caso in cui gli elementi dei due elementi siano uguali,
             * aggiungo l'elemento del primo insieme all'insieme intersezione ed eseguo
             * il controllo sui prossimi due elementi degli insiemi */
            nuovo_el = (el_insieme_t *) malloc(sizeof(el_insieme_t));
            nuovo_el->valore   = el_insieme_1->valore;
            nuovo_el->prossimo = intersezione(el_insieme_1->prossimo,
                                              el_insieme_2->prossimo);
        }
    }
    
    /* Restituzione del risultato dell'intersezione */
    return (nuovo_el);
}

/* Definizione della funzione che restituisce la differenza
* di due insiemi calcolata ricorsivamente. */
el_insieme_t *differenza(el_insieme_t *el_insieme_1, /* Lavoro: Elemento
                                                      * testa del primo
                                                      * insieme */
                         el_insieme_t *el_insieme_2) /* Lavoro: Elemento
                                                      * testa del secondo
                                                      * insieme */
{
    /* Dichiarazione delle variabili locali alla funzione */
    el_insieme_t *nuovo_el = NULL; /* Output: Elemento testa
                                    * dell'insieme differenza */
    
    /* Verifica che il primo insieme non sia terminato */
    if (el_insieme_1 != NULL)
    {
        /* Verifica che nemmeno il secondo insieme non sia terminato */
        if (el_insieme_2 != NULL)
        {
            if (el_insieme_1->valore < el_insieme_2->valore)
            {
                /* Nel caso in cui l'elemento del primo insieme sia minore
                 * dell'elemento del secondo insieme, aggiungo l'elemento del primo
                 * insieme all'insieme differenza ed eseguo il controllo fra il
                 * successivo elemento del primo insieme e l'elemento del
                 * secondo insieme */
                nuovo_el = (el_insieme_t *) malloc(sizeof(el_insieme_t));
                nuovo_el->valore   = el_insieme_1->valore;
                nuovo_el->prossimo = differenza(el_insieme_1->prossimo,
                                                el_insieme_2);
            }
            else if (el_insieme_1->valore > el_insieme_2->valore)
            {
                /* Nel caso in cui l'elemento del primo insieme sia maggiore
                 * dell'elemento del secondo insieme, eseguo il controllo fra
                 * l'elemento del primo insieme e il successivo elemento
                 * del secondo insieme */
                nuovo_el = differenza(el_insieme_1,
                                      el_insieme_2->prossimo);
            }
            else
            {
                /* Altrimenti, nel caso in cui gli elementi dei due elementi
                 * siano uguali, eseguo il controllo sui prossimi
                 * due elementi degli insiemi */
                nuovo_el = differenza(el_insieme_1->prossimo,
                                      el_insieme_2->prossimo);
            }
        }
        else
        {
            /* Nel caso in cui il primo insieme non sia terminato ed il secondo
             * insieme lo sia, aggiungo l'elemento del primo insieme all'insieme
             * differenza ed eseguo il controllo fra il successivo elemento del
             * primo insieme e l'elemento del secondo insieme */
            nuovo_el = (el_insieme_t *) malloc(sizeof(el_insieme_t));
            nuovo_el->valore   = el_insieme_1->valore;
            nuovo_el->prossimo = differenza(el_insieme_1->prossimo,
                                            el_insieme_2);
        }
    }
    
    /* Restituzione del risultato della differenza */
    return (nuovo_el);
}

/* Definizione della funzione che restituisce la differenza
* simmetrica di due insiemi calcolata ricorsivamente. */
el_insieme_t *diff_simm(el_insieme_t *el_insieme_1, /* Lavoro: Elemento
                                                     * testa del primo
                                                     * insieme */
                        el_insieme_t *el_insieme_2) /* Lavoro: Elemento
                                                     * testa del secondo
                                                     * insieme */
{
    /* Dichiarazione delle variabili locali alla funzione */
    el_insieme_t *nuovo_el = NULL; /* Output: Elemento testa
                                    * dell'insieme differenza simmetrica */
    
    /* Verifica che gli insiemi non siano terminati */
    if (el_insieme_1 != NULL &&
        el_insieme_2 != NULL)
    {
        if (el_insieme_1->valore < el_insieme_2->valore)
        {
            /* Nel caso in cui l'elemento del primo insieme sia minore dell'elemento
             * del secondo insieme, aggiungo l'elemento del primo insieme all'insieme
             * differenza simmetrica ed eseguo il controllo fra il successivo
             * elemento del primo insieme e l'elemento del secondo insieme */
            nuovo_el = (el_insieme_t *) malloc(sizeof(el_insieme_t));
            nuovo_el->valore   = el_insieme_1->valore;
            nuovo_el->prossimo = diff_simm(el_insieme_1->prossimo,
                                           el_insieme_2);
        }
        else if (el_insieme_1->valore > el_insieme_2->valore)
        {
            /* Nel caso in cui l'elemento del primo insieme sia maggiore
             * dell'elemento del secondo insieme, aggiungo l'elemento del secondo
             * insieme all'insieme differenza simmetrica ed eseguo il controllo fra
             * l'elemento del primo insieme e il successivo elemento
             * del secondo insieme */
            nuovo_el = (el_insieme_t *) malloc(sizeof(el_insieme_t));
            nuovo_el->valore   = el_insieme_2->valore;
            nuovo_el->prossimo = diff_simm(el_insieme_1,
                                           el_insieme_2->prossimo);
        }
        else
        {
            /* Altrimenti, nel caso in cui gli elementi dei due elementi siano
             * uguali, eseguo il controllo sui prossimi
             * due elementi degli insiemi */
            nuovo_el = diff_simm(el_insieme_1->prossimo,
                                 el_insieme_2->prossimo);
        }
    }
    else if (el_insieme_1 != NULL &&
             el_insieme_2 == NULL)
    {
        /* Nel caso in cui il primo insieme non sia terminato ed il secondo insieme
         * lo sia, aggiungo l'elemento del primo insieme all'insieme differenza
         * simmetrica ed eseguo il controllo fra il successivo elemento del primo
         * insieme e l'elemento del secondo insieme */
        nuovo_el = (el_insieme_t *) malloc(sizeof(el_insieme_t));
        nuovo_el->valore   = el_insieme_1->valore;
        nuovo_el->prossimo = diff_simm(el_insieme_1->prossimo,
                                       el_insieme_2);
        
    }
    else if (el_insieme_1 == NULL &&
             el_insieme_2 != NULL)
    {
        /* Nel caso in cui il primo insieme sia terminato ed il secondo insieme
         * non lo sia, aggiungo l'elemento del secondo insieme all'insieme differenza
         * simmetrica ed eseguo il controllo fra l'elemento del primo insieme e il
         * successivo elemento del secondo insieme */
        nuovo_el = (el_insieme_t *) malloc(sizeof(el_insieme_t));
        nuovo_el->valore   = el_insieme_2->valore;
        nuovo_el->prossimo = diff_simm(el_insieme_1,
                                       el_insieme_2->prossimo);
    }
    
    /* Restituzione del risultato della differenza simmetrica */
    return (nuovo_el);
}