#include <stdio.h>

void menu ();
void moltiplica ();
void dividi ();
void ins_string();

// aggiungo la funzione per evitare di poter aggiungere molteplici input all'interno di un singolo input
// ad esempio, per evitare che digitando A 3 2 ottenga subito 3*2=6
void clear_stdin() {
	int c = ' ';
	while (c != '\n' && c != EOF)
		c = getchar();
}

int main () 

{
	char scelta = {'\0'};
	menu ();
	// scanf(" %c", &scelta);
	// serve un char ma chiedo un int
	// scanf (" %c", &scelta);
	// in questo modo però posso inserire anche opzioni future
	// ad esempio, A 3 2 mi mostra che 3*2=6
	// richiedo quindi che vengano accettati tutti i caratteri fino allo spazio
	scanf(" %[^\x32|\n]", &scelta);

	clear_stdin();

	switch (scelta)
	{
		case 'A':
								moltiplica();
								break;
		case 'B':
                dividi();
                break;
		case 'C':
                ins_string();
                break;
		// facoltativo: aggiungere default
		default:
								printf("Non hai inserito una scelta valida.\n");
								break; // facoltativo visto che è l'ultimo caso, ma potrebbero sorgere problemi se venisse aggiunto un ulteriore caso

	}

return 0;

}


void menu ()
{
	printf ("Benvenuto, sono un assitente digitale, posso aiutarti a sbrigare alcuni compiti\n");
	printf ("Come posso aiutarti?\n");
	printf ("A >> Moltiplicare due numeri\nB >> Dividere due numeri\nC >> Inserire una stringa\n");

}


void moltiplica ()
{
	short int  a,b = 0;
	printf ("Inserisci i due numeri da moltiplicare:\n");
	// serve uno short int ma chiedi un float 
	// devo anche fare in modo che 
	// scanf ("%f", &a);
	scanf("%hd", &a);
	clear_stdin();
	// chiedi un int ma salvi in un short int
	// scanf ("%d", &b);
	scanf("%hd", &b);
	clear_stdin();
	// se avessi voluto permettere che entrambi i numeri potessero essere inseriti
	// sulla stessa riga, avrei potuto scrivere scanf("%hd %hd", &a, &b)

	// i numeri moltiplicati sono entrambi short int => ottengo un overflow con numeri vicini ai limiti del range del short int
	// meglio utilizzare un int che ha il doppio deei byte disponibili
	// inserendo a = 32767 (max short int) e b = 2, il risultato è -2 (overflow) (diventa positivo il bit di segno perché
	// una moltiplicazione per 2 di un intero espresso in binario corrisponde a uno spostamento dei valori verso i bit più di valenza)
	// infatti: importando limits.h posso vedere che SHRT_MIN=-32768 e SHRT_MAX=32767
	// short è lungo 2 byte = 16 bit, ma uno di questi 16 bit viene utilizzato per indicare il segno (signed).
	// per trovare gli estremi quindi bisogna calcolare 2^15
	// i possibili valori che i fattori possono assumere si trovano in [-32768, 32767]
	// short int prodotto = a * b;
	int prodotto = a * b;
	// per verificare se è possibile overflow prendiamo gli estremi negativi possibili per short (massimo valore assoluto)
	// a = b = -32768
	// e li moltiplichiamo tra loro (otteniamo un numero positivo, che in modulo risulta minore del massimo valore che int, in modulo, può assumere)
	// si vede così che il massimo valore positivo che la variabile può assumere è 1b~
	// sempre usando limits.h si vede che gli estremi dell'int si collocano a +- 2b, quindi non può esserci overflow
	
	// altro problema: non viene verificato se l'input è un numero o meno
	// per farlo conviene iniziare con un char[6] a,b (il valore massimo che uno short può raggiungere richiede 5 caratteri di numero + 1 di segno)
	// poi si analizza carattere per carattere tenendo presente che solo il primo carattere può essere un segno e che se è un numero
	// la stringa non può consistere di 11 cifre. inoltre utilizzando la funzione fgets, viene aggiunto un null-byte per indicare la fine
	// della stringa.
	// solo dopo aver controllato che i vari caratteri sono validi e che giaccia entro i limiti dello short int
	// (confronta grandezze di potenze di 10 successive con il massimo che lo short int può valere)
	// posso convertirlo in un intero con la funzione atoi() che si trova nella libreria string.h
	// lo stesso problema si verifica anche con la funzione dividi()

	printf ("Il prodotto tra %d e %d e': %d", a,b,prodotto);
}


void dividi ()
{
        int  a,b = 0;
        printf ("Inserisci il numeratore:");
        scanf ("%d", &a);
				clear_stdin();
				printf ("Inserisci il denumeratore:");
        scanf ("%d", &b);
				clear_stdin();
				// come per moltiplica() nel caso di entrambi numeri sulla stessa riga

				// non viene verificata divisione per 0
				if (b == 0) {
					printf("Non si può effettuare una divisione per 0.\n");
					return;
				}

				// non effettua una divisione ma calcola l'operazione di modulo (il resto intero di a/b).
        // int divisione = a % b;
				// il rapporto tra due numeri non è necessariamente un numero primo => utilizzo un float
				float divisione	= (float)a/b;

				// se voglio considerare solamente N numeri dopo la virgola posso utilizzare %.Nf al posto di %f
        // printf ("La divisione tra %d e %d e': %d", a,b,divisione);
        printf ("La divisione tra %d e %d e': %f", a,b,divisione);
}





void ins_string () 
{
				// si usa una costante per salvare la lunghezza della stringa per usi futuri
				const short lunghezza = 10;
				char stringa[lunghezza];
        printf ("Inserisci la stringa: ");
				// non viene verificata la lunghezza della stringa
        // scanf ("%s", &stringa);
				// una stringa composta solamente da spazi viene comunque salvata
				fgets(stringa, lunghezza, stdin);
				// aggiungo per verificare facilmente se è avvenuto overflow
				printf("%s\n", stringa);
}

