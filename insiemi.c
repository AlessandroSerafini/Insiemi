#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>

struct Elemento
{
    float           valore;
    struct Elemento *prossimo;
};

//TODO: ATTUALMENTE I METODI RICORSIVI FUNZIONANO SOLO CON LISTE ORDINATE: VA BENE?

void acquisisci_cardinalita(int *cardinalita,
                            bool primo_insieme);

void libera_buffer();

void acquisisci_elementi(struct Elemento **testa,
                         int cardinalita);

bool uguaglianza(struct Elemento *elemento_primo_insieme,
                 struct Elemento *elemento_secondo_insieme);

struct Elemento *calcola_intersezione(struct Elemento *elemento_primo_insieme,
                                      struct Elemento *elemento_secondo_insieme,
                                      struct Elemento *ultimo_elemento_intersezione);

struct Elemento *calcola_differenza(struct Elemento *elemento_primo_insieme,
                                    struct Elemento *elemento_secondo_insieme,
                                    struct Elemento *ultimo_elemento_differenza);

void stampa_insieme(struct Elemento *elemento);

int main()
{
    struct Elemento *testa_primo_insieme   = NULL,
                    *testa_secondo_insieme = NULL,
                    *insieme_intersezione  = NULL,
                    *insieme_differenza    = NULL;
    int             cardinalita_primo_insieme,
                    cardinalita_secondo_insieme;
    acquisisci_cardinalita(&cardinalita_primo_insieme,
                           true);
    acquisisci_elementi(&testa_primo_insieme,
                        cardinalita_primo_insieme);
    acquisisci_cardinalita(&cardinalita_secondo_insieme,
                           false);
    acquisisci_elementi(&testa_secondo_insieme,
                        cardinalita_secondo_insieme);
    
    insieme_intersezione = calcola_intersezione(testa_primo_insieme,
                                                testa_secondo_insieme,
                                                insieme_intersezione);
    
    insieme_differenza = calcola_differenza(testa_primo_insieme,
                                            testa_secondo_insieme,
                                            insieme_differenza);
    
    printf(uguaglianza(testa_primo_insieme,
                       testa_secondo_insieme) ?
           "\n[UGUAGLIANZA]: I due insiemi sono uguali" :
           "\n[UGUAGLIANZA]: I due insiemi sono diversi");
    
    printf("\n[INTERSEZIONE]: ");
    stampa_insieme(insieme_intersezione);
    
    printf("\n[DIFFERENZA]: ");
    stampa_insieme(insieme_differenza);
    
    
    return 0;
}

void libera_buffer()
{
    char c;
    while ((c = getchar()) != '\n' &&
           c != EOF)
    {
    }
}

void acquisisci_cardinalita(int *cardinalita,
                            bool primo_insieme)
{
    //TODO: rinominare in italiano e documentare "peek"
    int  esito_lettura,
         peek;
    bool input_valido = false;
    do
    {
        
        printf(primo_insieme ?
               "Inserisci la cardinalità del primo insieme:\n" :
               "Inserisci la cardinalità del secondo insieme:\n");
        
        esito_lettura = scanf("%d",
                              cardinalita);
        
        if (esito_lettura != 1 ||
            ((peek = getchar()) != EOF &&
             !isspace(peek)) ||
            *cardinalita <= 0)
        {
            printf("[ERRORE]: L'input deve essere un numero intero maggiore di 0!\n");
            libera_buffer();
        }
        else
        {
            input_valido = true;
        }
        
    }
    while (!input_valido);
}

void acquisisci_elementi(struct Elemento **testa,
                         int cardinalita)
{
    
    //TODO: rinominare in italiano e documentare "peek"
    
    int   esito_lettura,
          peek,
          i            = 0;
    float valore_ingresso;
    bool  input_valido = false;
    
    printf("Inserisci gli elementi dell'insieme (uno per riga):\n");
    do
    {
        do
        {
            printf("Inserisci l'elemento %d\n",
                   i + 1);
            esito_lettura = scanf("%f",
                                  &valore_ingresso);
            if (esito_lettura != 1 ||
                ((peek    = getchar()) != EOF &&
                 !isspace(peek)))
            {
                printf("[ERRORE]: L'input deve essere un numero reale!\n");
                libera_buffer();
            }
            else
            {
                struct Elemento *nuovo_elemento = (struct Elemento *) malloc(sizeof(struct Elemento));
                struct Elemento *ultimo         = *testa;
                nuovo_elemento->valore   = valore_ingresso;
                nuovo_elemento->prossimo = NULL;
                
                if (*testa == NULL)
                {
                    *testa = nuovo_elemento;
                }
                else
                {
                    while (ultimo->prossimo != NULL)
                    {
                        ultimo = ultimo->prossimo;
                    }
                    ultimo->prossimo = nuovo_elemento;
                }
                input_valido = true;
                i++;
            }
        }
        while (!input_valido);
    }
    while (i < cardinalita);
}


bool uguaglianza(struct Elemento *elemento_primo_insieme,
                 struct Elemento *elemento_secondo_insieme)
{
    bool risultato;
    if (elemento_primo_insieme == NULL &&
        elemento_secondo_insieme == NULL)
    {
        risultato = true;
    }
    if (elemento_primo_insieme != NULL &&
        elemento_secondo_insieme != NULL)\

    {
        risultato = (elemento_primo_insieme->valore == elemento_secondo_insieme->valore) &&
                    uguaglianza(elemento_primo_insieme->prossimo,
                                elemento_secondo_insieme->prossimo);
    }
    return risultato;
}

struct Elemento *calcola_intersezione(struct Elemento *elemento_primo_insieme,
                                      struct Elemento *elemento_secondo_insieme,
                                      struct Elemento *ultimo_elemento_intersezione)
{
    struct Elemento *nuovo_elemento_intersezione = NULL;
    if (elemento_primo_insieme != NULL &&
        elemento_secondo_insieme != NULL)
    {
        if (elemento_primo_insieme->valore < elemento_secondo_insieme->valore)
        {
            nuovo_elemento_intersezione = calcola_intersezione(elemento_primo_insieme->prossimo,
                                                               elemento_secondo_insieme,
                                                               nuovo_elemento_intersezione);
        }
        else if (elemento_primo_insieme->valore > elemento_secondo_insieme->valore)
        {
            nuovo_elemento_intersezione = calcola_intersezione(elemento_primo_insieme,
                                                               elemento_secondo_insieme->prossimo,
                                                               nuovo_elemento_intersezione);
        }
        else if (!ultimo_elemento_intersezione ||
                 ultimo_elemento_intersezione->valore != elemento_primo_insieme->valore)
        {
            nuovo_elemento_intersezione = (struct Elemento *) malloc(sizeof(struct Elemento));
            nuovo_elemento_intersezione->valore   = elemento_primo_insieme->valore;
            nuovo_elemento_intersezione->prossimo = calcola_intersezione(elemento_primo_insieme->prossimo,
                                                                         elemento_secondo_insieme->prossimo,
                                                                         nuovo_elemento_intersezione);
        }
    }
    return nuovo_elemento_intersezione;
}

struct Elemento *calcola_differenza(struct Elemento *elemento_primo_insieme,
                                    struct Elemento *elemento_secondo_insieme,
                                    struct Elemento *ultimo_elemento_differenza)
{
    struct Elemento *nuovo_elemento_differenza = NULL;
    if (elemento_primo_insieme != NULL &&
        elemento_secondo_insieme != NULL)
    {
        if (elemento_primo_insieme->valore > elemento_secondo_insieme->valore)
        {
            nuovo_elemento_differenza = calcola_differenza(elemento_primo_insieme,
                                                           elemento_secondo_insieme->prossimo,
                                                           ultimo_elemento_differenza);
        }
        else if (elemento_primo_insieme->valore == elemento_secondo_insieme->valore)
        {
            nuovo_elemento_differenza = calcola_differenza(elemento_primo_insieme->prossimo,
                                                           elemento_secondo_insieme,
                                                           ultimo_elemento_differenza);
        }
        else if (!ultimo_elemento_differenza ||
                 ultimo_elemento_differenza->valore != elemento_primo_insieme->valore)
        {
            nuovo_elemento_differenza = (struct Elemento *) malloc(sizeof(struct Elemento));
            nuovo_elemento_differenza->valore   = elemento_primo_insieme->valore;
            nuovo_elemento_differenza->prossimo = calcola_differenza(elemento_primo_insieme->prossimo,
                                                                       elemento_secondo_insieme,
                                                                       nuovo_elemento_differenza);
        }
    }
    return nuovo_elemento_differenza;
}


void stampa_insieme(struct Elemento *elemento)
{
    printf("{");
    while (elemento != NULL)
    {
        printf("%1.f",
               elemento->valore);
        if (elemento->prossimo != NULL)
        {
            printf(", ");
        }
        elemento = elemento->prossimo;
    }
    printf("}");
}