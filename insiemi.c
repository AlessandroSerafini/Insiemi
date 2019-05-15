/********************************************************************/
/*  DESCRIZIONE:
*   Il programma acquisisce da tastiera la cardinalità di due insiemi
*   ed i relativi elementi (sono accettati esclusivamente numeri reali)
*   Tali insiemi vengono utilizzati per effettuare operazioni
*   (uguaglianza, intersezione, differenza e differenza simmetrica)
*   attraverso apposite funzioni di una libreria esterna.
*
*   AUTORE: Serafini Alessandro <a.serafini21@campus.uniurb.it> */
/********************************************************************/

/*****************************/
/* Inclusione delle librerie */
/*****************************/

#include <stdio.h>
#include <ctype.h>
#include "operazioni_insiemi.h"

/********************************/
/* Dichiarazione delle funzioni */
/********************************/

/* Dichiarazione della funzione che acquisisce la cardinalità
 * dell'insieme a seguito di apposita validazione.
 * Se il valore inserito non rispetta il formato
 * (numero intero positivo), l'acquisizione viene ripetuta. */
void acquisisci_cardinalita(int *cardinalita); /* Puntatore alla
                                                * variabile nella quale
                                                * scrivere il valore */

/* Dichiarazione della funzione che libera il buffer */
void libera_buffer();

/* Dichiarazione della funzione che cerca un elemento all'interno
 * di un insieme e restituisce l'esito della ricerca. */
bool cerca_in_insieme(el_insieme_t *el_corrente, /* Elemento testa
                                                  * dell'insieme */
                      float el_ricercato);       /* Valore da ricercare
                                                  * nell'insieme*/

/* Dichiarazione della funzione che acquisisce gli elementi
 * dell'insieme a seguito di apposita validazione. Se il valore
 * inserito non rispetta il formato (numero reale e non
 * precedentemente acquisito), l'acquisizione viene ripetuta. */
void acquisisci_elementi(el_insieme_t **testa, /* Elemento testa
                                                * dell'insieme */
                         int cardinalita);     /* Cardinalità
                                                * dell'insieme*/

/* Dichiarazione della funzione che inserisce all'interno dell'insieme
 * un elemento già sottoposto a validazione. L'elemento
 * viene inserito nella posizione consona (in ordine ascendente)
 * a seconda del proprio valore. */
void inserisci_acquisizione(el_insieme_t **testa,        /* Elemento testa
                                                          * dell'insieme */
                            el_insieme_t *el_acquisito); /* Elemento
                                                          * da inserire */

/* Dichiarazione della funzione che stampa a schermo il valore di
 * ogni elemento di un insieme. */
void stampa_insieme(el_insieme_t *elemento); /* Elemento testa
                                              * dell'insieme da stampare. */

/******************************/
/* Definizione delle funzioni */
/******************************/

/* Definizione della funzione main */
int main()
{
    /* Dichiarazione delle variabili locali alla funzione */
    int          cardinalita_insieme_1,        /* Input: cardinalità
                                                * del primo insieme */
                 cardinalita_insieme_2;        /* Input: cardinalità
                                                * del secondo insieme */
    el_insieme_t *testa_insieme_1      = NULL, /* Lavoro: elemento testa
                                                * del primo insieme */
                 *testa_insieme_2      = NULL, /* Lavoro: elemento testa
                                                * del secondo insieme */
                 *insieme_intersezione = NULL, /* Output: elemento
                                                * testa dell'insieme
                                                * intersezione */
                 *insieme_differenza   = NULL, /* Output: elemento
                                                * testa dell'insieme
                                                * differenza */
                 *insieme_diff_simm    = NULL; /* Output: elemento
                                                * testa dell'insieme
                                                * differenza simmetrica */
    
    /* Stampa a schermo delle istruzioni del software per l'utente */
    printf("\n********************\nINSIEMI\n********************\n");
    printf("\nQuesto software fa uso di una libreria esterna ");
    printf("per effettuare operazioni sugli insiemi.");
    printf("\nGli insiemi in questione sono due e, una volta inserita la ");
    printf("cardinalità (numero intero e maggiore di zero) di ciascuno, ");
    printf("accettano esclusivamente numeri reali ed unici.");
    printf("\nLe operazioni effettuate sono le seguenti:");
    printf("\n- Verifica uguaglianza\n- Intersezione\n");
    printf("- Differenza\n- Differenza simmetrica\n\n");
    
    /* Acquisizione della cardinalità del primo insieme */
    acquisisci_cardinalita(&cardinalita_insieme_1);
    
    if (cardinalita_insieme_1 > 0)
    {
        /* Acquisizione degli elementi del primo insieme
         * se la cardinalità inserita è maggiore di 0 */
        acquisisci_elementi(&testa_insieme_1,
                            cardinalita_insieme_1);
    }
    
    /* Acquisizione della cardinalità del secondo insieme */
    acquisisci_cardinalita(&cardinalita_insieme_2);
    
    if (cardinalita_insieme_2 > 0)
    {
        /* Acquisizione degli elementi del secondo insieme
         * se la cardinalità inserita è maggiore di 0 */
        acquisisci_elementi(&testa_insieme_2,
                            cardinalita_insieme_2);
    }
    
    /* Esecuzione della funzione che calcola
     * l'intersezione fra due insiemi */
    insieme_intersezione = intersezione(testa_insieme_1,
                                        testa_insieme_2);
    
    /* Esecuzione della funzione che calcola
     * la differenza fra due insiemi */
    insieme_differenza = differenza(testa_insieme_1,
                                    testa_insieme_2);
    
    /* Esecuzione della funzione che calcola la
     * differenza simmetrica fra due insiemi */
    insieme_diff_simm = diff_simm(testa_insieme_1,
                                  testa_insieme_2);
    
    /* Comunicazione dell'esito del controllo sull'uguaglianza
     * fra gli insiemi inseriti */
    printf(uguaglianza(testa_insieme_1,
                       testa_insieme_2) ?
           "\n\n[UGUAGLIANZA]: I due insiemi sono uguali" :
           "\n\n[UGUAGLIANZA]: I due insiemi sono diversi");
    
    /* Comunicazione dell'esito del calcolo dell'intersezione
     * fra gli insiemi inseriti */
    printf("\n[INTERSEZIONE]: ");
    stampa_insieme(insieme_intersezione);
    
    /* Comunicazione dell'esito del calcolo della
     * differenza fra gli insiemi inseriti */
    printf("\n[DIFFERENZA]: ");
    stampa_insieme(insieme_differenza);
    
    /* Comunicazione dell'esito del calcolo della
     * differenza simmetrica fra gli insiemi inseriti */
    printf("\n[DIFFERENZA SIMMETRICA]: ");
    stampa_insieme(insieme_diff_simm);
    
    return 0;
}

/* Definizione della funzione che acquisisce la cardinalità
 * dell'insieme a seguito di apposita validazione.
 * Se il valore inserito non rispetta il formato
 * (numero intero positivo), l'acquisizione viene ripetuta. */
void acquisisci_cardinalita(int *cardinalita) /* Input: Puntatore alla
                                               * variabile nella quale
                                               * scrivere il valore. */
{
    /* Dichiarazione delle variabili locali alla funzione */
    int  esito_lettura,               /* Lavoro: numero di valori
                                       * inseriti nell'acquisizione */
         carattere;                   /* Lavoro: carattere utile per
                                       * liberare il buffer */
    bool acquisizione_valida = false; /* Lavoro: Valore che stabilisce
                                       * se l'input inserito è corretto */
    
    do
    {
        /* Comunicazione all'utente per l'inserimento
         * della cardinalità dell'insieme */
        printf("Inserisci la cardinalità dell'insieme:\n");
        
        /* Acquisizione del valore */
        esito_lettura  = scanf("%d",
                               cardinalita);
        
        /* Validazione del valore come descritto in fase di definizione
         * della funzione. Nel caso in cui il valore non sia valido,
         * l'acquisizione viene nuovamente richiesta. */
        if (esito_lettura != 1)
        {
            /* Comunicazione all'utente dell'errore in fase di acquisizione
             * e specifica del formato corretto */
            printf("[ERRORE]: L'input deve essere un numero intero!\n");
        }
        else
        {
            /* Acquisizione valida: impostazione del relativo valore */
            acquisizione_valida = true;
        }
        /* Liberazione del buffer */
        if ((carattere = getchar()) != EOF &&
            !isspace(carattere))
        {
            libera_buffer();
        }
        
    }
    while (!acquisizione_valida);
}

/* Definizione della funzione che libera il buffer */
void libera_buffer()
{
    /* Dichiarazione variabili locali */
    char c; /* Lavoro: carattere utile a svuotare il buffer */
    
    while ((c = getchar()) != '\n' &&
           c != EOF)
    {
    }
}

/* Definizione della funzione che cerca un elemento all'interno
 * di un insieme e restituisce l'esito della ricerca. */
bool cerca_in_insieme(el_insieme_t *el_corrente, /* Lavoro: Elemento testa
                                                  * dell'insieme*/
                      float el_ricercato)        /* Lavoro: Valore da
                                                  * ricercare
                                                  * nell'insieme*/
{
    /* Dichiarazione delle variabili locali alla funzione */
    bool trovato; /* Output: risultato della ricerca dell'elemento */
    
    if (el_corrente == NULL)
    {
        /* Se l'elemento non è stato trovato imposto
         * il valore di ritorno di conseguenza. */
        trovato = false;
    }
    else if (el_corrente->valore == el_ricercato)
    {
        /* Se l'elemento è stato trovato imposto
         * il valore di ritorno di conseguenza. */
        trovato = true;
    }
    else
    {
        /* Altrimenti ripeto la ricerca all'elemento successivo */
        trovato = cerca_in_insieme(el_corrente->prossimo,
                                   el_ricercato);
    }
    
    /* Restituisco l'esito della ricerca */
    return (trovato);
}

/* Definizione della funzione che acquisisce gli elementi
 * dell'insieme a seguito di apposita validazione. Se il valore
 * inserito non rispetta il formato (numero reale e non
 * precedentemente acquisito), l'acquisizione viene ripetuta. */
void acquisisci_elementi(el_insieme_t **testa, /* Lavoro: Elemento testa
                                                * dell'insieme */
                         int cardinalita)      /* Lavoro: Cardinalità
                                                * dell'insieme*/
{
    /* Dichiarazione delle variabili locali alla funzione */
    int   esito_lettura,               /* Lavoro: numero di valori
                                        * inseriti nell'acquisizione */
          carattere,                   /* Lavoro: carattere utile per
                                        * liberare il buffer */
          i                   = 0;     /* Lavoro: indice della
                                        * cardinalità dell'insieme */
    float valore_ingresso;             /* Lavoro: Valore nel quale
                                        * scrivere l'acquisizione */
    bool  acquisizione_valida = false; /* Lavoro: Valore che stabilisce
                                        * se l'input inserito è corretto */
    
    /* Comunicazione all'utente per l'inserimento
     * degli elementi dell'insieme */
    printf("Inserisci gli elementi dell'insieme (uno per riga):\n");
    do
    {
        do
        {
            /* Comunicazione all'utente per l'inserimento
             * dello specifico elemento */
            printf("Inserisci l'elemento %d\n",
                   i + 1);
            
            /* Acquisizione del valore */
            esito_lettura = scanf("%f",
                                  &valore_ingresso);
            
            /* Validazione del valore come descritto in fase di definizione
             * della funzione. Nel caso in cui il valore non sia valido,
             * l'acquisizione viene nuovamente richiesta. */
            if (esito_lettura != 1)
            {
                printf("[ERRORE]: L'input deve essere ");
                printf("un numero reale!\n");
            }
            else if (cerca_in_insieme(*testa,
                                      valore_ingresso))
            {
                printf("[ERRORE]: Questo valore è già ");
                printf("stato acquisito precedentemente!\n");
            }
            else
            {
                /* Validazione superata: inserimento dell'elemento
                 * nella consona posizione all'interno dell'insieme */
                el_insieme_t *nuovo_el = (el_insieme_t *) malloc(sizeof(el_insieme_t));
                nuovo_el->valore   = valore_ingresso;
                nuovo_el->prossimo = NULL;
                inserisci_acquisizione(testa,
                                       nuovo_el);
                acquisizione_valida = true;
                i++;
            }
            
            /* Eventuale liberazione del buffer */
            if ((carattere = getchar()) != EOF &&
                !isspace(carattere))
            {
                libera_buffer();
            }
        }
        while (!acquisizione_valida);
    }
    while (i < cardinalita);
}

/* Definizione della funzione che inserisce all'interno dell'insieme
 * un elemento già sottoposto a validazione. L'elemento
 * viene inserito nella posizione consona (in ordine ascendente)
 * a seconda del proprio valore. */
void inserisci_acquisizione(el_insieme_t **testa,       /* Lavoro: Elemento
                                                         * testa
                                                         * dell'insieme */
                            el_insieme_t *el_acquisito) /* Input: Elemento
                                                         * da inserire */
{
    /* Dichiarazione delle variabili locali alla funzione */
    el_insieme_t *el_corrente; /* Lavoro: elemento iterato dell'insieme */
    
    if (*testa == NULL ||
        (*testa)->valore > el_acquisito->valore)
    {
        /* Inserimento dell'elemento in testa in caso di insieme vuoto
         * o valore minore del primo elemento. */
        el_acquisito->prossimo = *testa;
        *testa = el_acquisito;
    }
    else
    {
        /* Inserimento dell'elemento nella posizione
         * consona in base al valore */
        el_corrente = *testa;
        while (el_corrente->prossimo != NULL &&
               el_corrente->prossimo->valore < el_acquisito->valore)
        {
            el_corrente = el_corrente->prossimo;
        }
        el_acquisito->prossimo = el_corrente->prossimo;
        el_corrente->prossimo  = el_acquisito;
    }
}

/* Definizione della funzione che stampa a schermo il valore di
 * ogni elemento di un insieme. */
void stampa_insieme(el_insieme_t *elemento) /* Lavoro: Elemento testa
                                             * dell'insieme da stampare. */
{
    printf("{");
    while (elemento != NULL)
    {
        /* Stampa di ogni elemento dell'insieme separato da virgola */
        printf("%lf",
               elemento->valore);
        if (elemento->prossimo != NULL)
        {
            printf(", ");
        }
        elemento = elemento->prossimo;
    }
    printf("}");
}