# Progetto CercaPercorso

### Descrizione
Questo progetto è stato realizzato come Prova Finale per il corso di Algoritmi e Principi dell'Informatica nel periodo accademico 2022-2023. Il progetto è stato valutato con il massimo punteggio di 30/30 con Lode.

### Realizzazione
Il progetto è stato sviluppato utilizzando il linguaggio C, rispettando lo standard C11 con l'ammissione di Variable Length Arrays (VLA). La libreria utilizzata è la Standard C (libc). Non è stato utilizzato il multithreading. I dati in ingresso vengono forniti tramite stdin, mentre i risultati vengono restituiti tramite stdout.

### Struttura del Progetto
Il progetto, denominato CercaPercorso, si focalizza sull'implementazione di un'autostrada rappresentata come una lista di stazioni di servizio. Ogni stazione è identificata dalla sua distanza dall'inizio dell'autostrada e contiene un insieme di veicoli elettrici, ognuno caratterizzato da un'autonomia specifica.

### Obiettivo
L'obiettivo principale del progetto è trovare il percorso con il minor numero di tappe tra due stazioni, utilizzando un veicolo diverso in ogni tappa, selezionato tra quelli disponibili nella stazione di servizio. È importante sottolineare che il percorso è solo pianificato e non comporta lo spostamento effettivo di autovetture durante la richiesta del percorso.

### Comandi e Risposte Attese
Il sistema supporta diversi comandi per gestire le stazioni di servizio e pianificare i percorsi tra di esse. Ogni comando ha una specifica risposta attesa, garantendo una corretta interazione con l'utente.

- `aggiungi-stazione`: Aggiunge una stazione all'autostrada con specifica distanza e un numero di veicoli elettrici, ciascuno con un'autonomia definita.
- `demolisci-stazione`: Rimuove una stazione di servizio specificata dalla distanza.
- `aggiungi-auto`: Aggiunge un veicolo elettrico con specifica autonomia a una stazione di servizio.
- `rottama-auto`: Rottama un veicolo elettrico specificato in una determinata stazione.
- `pianifica-percorso`: Pianifica il percorso con il minor numero di tappe tra due stazioni date.

### Implementazione dei Percorsi Ambigui
Nel caso in cui esistano più percorsi con la stessa lunghezza tra due stazioni, l'implementazione privilegia il percorso che, nella sua parte finale, preferisce le stazioni più vicine all'inizio dell'autostrada, ossia quelle con il numero più basso.

### Esempio di Utilizzo
Di seguito è riportato un esempio di utilizzo del sistema con input e output corrispondenti:

#### Input
```
aggiungi-stazione 20 3 5 10 15
aggiungi-stazione 4 3 1 2 3
aggiungi-stazione 30 0
demolisci-stazione 3
demolisci-stazione 4
aggiungi-auto 30 40
aggiungi-stazione 50 3 20 25 7
rottama-auto 20 8
rottama-auto 9999 5
rottama-auto 50 7
pianifica-percorso 20 30
pianifica-percorso 20 50
pianifica-percorso 50 30
pianifica-percorso 50 20
aggiungi-auto 50 30
pianifica-percorso 50 20
```

#### Output
```
aggiunta
aggiunta
aggiunta
non demolita
demolita
aggiunta
aggiunta
non rottamata
non rottamata
rottamata
20 30
20 30 50
50 30
50 30 20
aggiunta
```

### Test
Per verificare il corretto funzionamento del programma, sono disponibili 111 test all'interno della cartella `test`. È possibile eseguirli utilizzando lo script `test.py`.

### Referenze
- `main.c`: Il programma principale da sviluppare.
- `specifica.pdf`: Descrizione dettagliata dei requisiti del programma.
- `test.py`: Script in Python per eseguire i test disponibili.
