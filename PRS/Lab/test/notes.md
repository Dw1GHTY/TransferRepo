- Komunikator je skup od vise procesa koji imaju rank (int vrednost od 0 do br_procesa - 1)
- Rang svakog procesa je njegov identifikator u okviru komunikatora
- MPI_COMM_WORLD je out-of-the-box globalni komunikator kome pripadaju svi procesi, makar bili u nekom
  "lokalnom" komunikatoru

## Proces određuje svoj svoj rang u komunikatoru korišćenjem funkcije:

- int MPI_Comm_rank(MPI_Comm comm, int \*rank);
  //

## Proces može odrediti veličinu komunikatora (tj. broj procesa u njemu) kome pripada korišćenjem funkcije

- int MPI_Comm_size(MPI_Comm comm, int \*size);

## Proces salje blokirajucu poruku drugom procesu funkcijom

- int MPI_Send(void \*buf, int count, MPI_Datatype dtype, int dest, int tag, MPI_Comm comm);

`buf` ukazuje na mesto u memoriji odakle počinje slanje count podataka tipa dtype.
Broj podataka u receive pozivu (MPI_Recv) treba da bude veći ili jednak broju count u MPI_Send.
`dest` je rang procesa kome se šalje poruka
`tag` je proizvoljan broj koji služi za prepoznavanje odgovarajuče poruke na prijemu
`comm` komunikator u okviru koga se odvija komunikacija.

## Funkcija koja implementira prijem sa blokiranjem je

- int MPI_Recv(void *buf, int count, MPI_Datatype dtype, int source, int tag, MPI_Comm comm, MPI_Status *status);

`buf` ukazuje na mesto u memoriji od koje počinje poruka koja je primljena
Maksimalan broj podataka tipa dtype koji se prima određen je drugim i trećim argumentom `count` i `dtype`
Argument `source` je rang izvora poruke
`tag` oznaka poruke a `comm` komunikator u kojem moraju da budu oba procesa

### primer:

- MPI_Recv(c,10,MPI_INT,1,10,MPI_COMM_WORLD,&stat);
- MPI_Recv(&d,1,MPI_DOUBLE,0,19,Comm1,&stat);

## Wildcard-ovi

- MPI_ANY_SOURCE, prima poruku od bilo kog procesa
- MPI_ANY_TAG, prima poruku sa bilo kojom oznakom

### MPI_Send izvrsenje

- Ako je velicina poruke manja ili jednaka baferu, ne blokirajuce se salje i podatak se kopira u bafer primaoca
- Ako je velicina poruke veca od bafera posiljaoc ceka da primalac primi poruku

## Situacija kada sigurno nastaje deadlock

P0
MPI_Recv (from P1)
MPI_Send (to P1)
P1
MPI_Recv (from P0)
MPI_Send (to P0)

## Situacija kada zavisno od veličine sis.bafera nastaje deadlo

P0
MPI_Send (to P1)
MPI_Recv (from P1)
P1
MPI_Send (to P0)
MPI_Recv (from P0)

# Operacije bez blokiranja

- int MPI_Isend(void *buf, int count, MPI_Datatype dtype, int dest, int tag, MPI_Comm comm, MPI_Request *request);
  Na osnovu `request` se proverava (testira) status inicirane operacije ili kompletira njeno izvršenje.
- int MPI_Irecv(void *buf, int count, MPI_Datatype dtype, int source, int tag, MPI_Comm comm, MPI_Request *request);
- int MPI_Wait( MPI_Request *request, MPI_Status *status );
- int MPI_Test( MPI_Request *request, int *flag, MPI_Status \*status );
  Argument `flag` se postavlja na “true” ukoliko je operacija završena, u suprotnom na “false”.

# Grupne operacije

- Grupne operacije su operacije koje se primenjuju nad svim članovima jedne grupe.
- Operacija se izvršava kada svi procesi pozovu odgovarajuću operaciju sa svojim parametrima.
- Svaki proces mora da pozove grupnu operaciju da bi se ona obavila!!!!
- Dele se na operacije za kontrolu procesa, operacije za globalna izračunavanja i operacije za prenos podataka.

- int MPI_Barrier (MPI_Comm comm )
  Proces se blokira na toj naredbi dok svi ostali procesi iz grupe ne dođu do te naredbe

# Operacije za globalna izračunavanja

- int MPI_Reduce ( void* send_buffer, void* recv_buffer, int count, MPI_Datatype datatype, MPI_Op operation, int rank,MPI_Comm comm )
  `send_buffer` -adresa send bafera svih procesa gde se nalaze podaci nad kojima se obavlja operacija redukcije
  `recv_buffer` -adresa receive bafera root procesa
  `count` -broj podataka u send i receive baferu
  `datatype` -tip podataka u send i receive baferu
  `comm` -komunikator
  `rank` -identifikator root procesa
