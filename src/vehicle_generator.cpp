/*  prende in input:
        - un puntatore agli svincoli o alla struttura dell'autostrada
        - un double con l'istante di partenza del veicolo precedente
    genera un veicolo secondo indicazioni


    Il simulatore genera un determinato numero di veicoli scegliendo casualmente:
        la targa nel formato [due lettere - tre cifre - due lettere]
        lo svincolo di ingresso;
        lo svincolo di uscita;
        data e orario di ingresso;
        il profilo di velocità.

        data e orario di ingresso sono generate a partire dall'istante del veicolo precedente,
        più un offset compreso nell'intervallo [0.5-10] (in teoria, non è chiaro da consegna)

    es.
    
    generate_vehicle(Vector<Svincolo> s (oppure Highway h)){
        //leggi file
        genera targa
        prendi coppia di svincoli
        genera data e orario di partenza

        genera profilo di velocità
        new Vector<Speed> 
        for(...)
        
        return new Vehicle(...);
    }


*/