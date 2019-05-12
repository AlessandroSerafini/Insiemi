#include "operazioni_insiemi.h"

bool verifica_uguaglianza(el_insieme_t *el_primo_insieme,
                          el_insieme_t *el_secondo_insieme);

el_insieme_t *calcola_intersezione(el_insieme_t *el_primo_insieme,
                                   el_insieme_t *el_secondo_insieme);

el_insieme_t *calcola_differenza(el_insieme_t *el_primo_insieme,
                                 el_insieme_t *el_secondo_insieme);

el_insieme_t *calcola_diff_simm(el_insieme_t *el_primo_insieme,
                                el_insieme_t *el_secondo_insieme);


bool verifica_uguaglianza(el_insieme_t *el_primo_insieme,
                          el_insieme_t *el_secondo_insieme)
{
    bool risultato = true;
    if (el_primo_insieme != NULL)
    {
        if (el_secondo_insieme != NULL)
        {
            if (el_primo_insieme->valore == el_secondo_insieme->valore)
            {
                risultato = verifica_uguaglianza(el_primo_insieme->prossimo,
                                                 el_secondo_insieme->prossimo);
            }
            else
            {
                risultato = false;
            }
        }
        else
        {
            risultato = false;
        }
    }
    else
    {
        risultato = (el_secondo_insieme == NULL);
    }
    
    return (risultato);
}

el_insieme_t *calcola_intersezione(el_insieme_t *el_primo_insieme,
                                   el_insieme_t *el_secondo_insieme)
{
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

el_insieme_t *calcola_differenza(el_insieme_t *el_primo_insieme,
                                 el_insieme_t *el_secondo_insieme)
{
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

el_insieme_t *calcola_diff_simm(el_insieme_t *el_primo_insieme,
                                el_insieme_t *el_secondo_insieme)
{
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