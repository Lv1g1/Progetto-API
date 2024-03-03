# Progetto-API
Prova Finale di Algoritmi e Principi dell'Informatica 2022-2023

Voto: 30/30 con Lode

---

## Realizzazione
- Linguaggio utilizzato: C (C11, VLA ammessi)
- Libreria: Standard C (libc)
- Nessun utilizzo di multithreading
- Dati in ingresso forniti tramite stdin, risultati restituiti tramite stdout

---

## Progetto CercaPercorso
Autostrada: lista di stazioni di servizio
- Ogni stazione è identificata dalla sua distanza (numero naturale) dall'inizio dell'autostrada
- Ogni stazione è dotata di un insieme di veicoli elettrici con autonomia data da un intero positivo

---

## Obiettivo
- Trovare il percorso con il minor numero di tappe tra due stazioni, utilizzando un veicolo diverso in ogni tappa, scelto tra quelli disponibili nella stazione di servizio.
- Importante: il percorso è solo pianificato, quindi non verranno spostate autovetture durante la richiesta del percorso.

---

## Comandi e Risposte Attese

- `aggiungi-stazione distanza numero-auto auto-1 ... auto-n`
  - Aggiunge una stazione all'autostrada, identificata dalla distanza e con un numero di veicoli specificato. Le autonomie di ogni veicolo sono elencate dopo il numero di veicoli. Se esiste già una stazione alla distanza data, l'aggiunta non avviene.
  - Output atteso: aggiunta / non aggiunta

- `demolisci-stazione distanza`
  - Rimuove la stazione di servizio alla distanza indicata, se presente. Se non esiste una stazione alla distanza indicata, non effettua alcuna operazione e stampa "non demolita".
  - Output atteso: demolita / non demolita

- `aggiungi-auto distanza-stazione autonomia-auto`
  - Aggiunge un'auto con l'autonomia specificata alla stazione alla distanza specificata, a condizione che la stazione esista. Nota: è possibile avere più veicoli con la stessa autonomia.
  - Output atteso: aggiunta / non aggiunta

- `rottama-auto distanza-stazione autonomia-auto`
  - Rimuove un'auto con l'autonomia specificata dalla stazione alla distanza specificata. Se la stazione non esiste o non esiste un veicolo con l'autonomia specificata nella stazione, non esegue alcuna operazione tranne stampare "non rottamata".
  - Output atteso: rottamata / non rottamata

- `pianifica-percorso stazione-partenza stazione-arrivo`
  - Pianifica il percorso con il minor numero di tappe tra la stazione di partenza e quella di arrivo, se esiste. Le stazioni sono identificate dalle loro distanze.
  - Output atteso:
    - Se il percorso esiste: sequenza delle stazioni che compongono il percorso, in ordine di percorrenza, includendo la stazione di partenza e quella di arrivo. Le stazioni sono stampate come numeri interi, separati da spazi, su una sola riga.
    - Se il percorso non esiste: nessun percorso

**Nota:** l'autostrada ha due sensi di percorrenza!

---

## Percorsi Ambigui
Tra due stazioni possono esistere più percorsi con la stessa lunghezza. L'implementazione deve scegliere il percorso che, nella sua parte finale, preferisce sempre le stazioni più vicine all'inizio dell'autostrada. Cioè, le stazioni con il numero più basso possibile. Questa regola non è influenzata dal senso di percorrenza.

---

## Esempio

### Input

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

### Output

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

