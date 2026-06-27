# Sinhronizacija niti — sažetak

## Sadržaj
1. Semafori (opšti koncept)
2. Sinhronizacija niti (problem trke)
3. Mutex
4. Uslovne promenljive
5. POSIX semafori

---

## 1. Semafori (Dijkstra, 1965)

Semafor je celobrojna promenljiva nad kojom se izvršavaju samo dve **atomične** operacije:

```
P(S): if S > 0
        then S = S - 1
        else Blokirati proces na semaforu S

V(S): if postoji proces koji čeka na semaforu S
        then Aktivirati proces iz liste čekanja
        else S = S + 1
```

**Tipovi:** binarni (mutex, 0 ili 1) i opšti (0..N).

**Nedostaci:** mora se striktno poštovati dualizam P/V operacija i njihov redosled — greška dovodi do blokade ili netačnog rada.

---

## 2. Sinhronizacija niti — zašto je potrebna?

- Niti deli isti adresni prostor procesa → mogu pristupati zajedničkim resursima.
- Čitanje bez promene → nema konflikta.
- **Problem trke (race condition)** nastaje kada više niti istovremeno menja isti resurs — rezultat zavisi od redosleda izvršavanja, što ove greške čini teškim za otkrivanje.

Tri mehanizma se obrađuju: **Mutex**, **Uslovne promenljive**, **POSIX semafori**.

---

## 3. Mutex (`<pthread.h>`, tip `pthread_mutex_t`)

Implementacija binarnog semafora za **međusobno isključenje** pri pristupu deljivom resursu.

| Funkcija | Opis |
|---|---|
| `pthread_mutex_init(mutex, attr)` | kreira mutex |
| `pthread_mutex_destroy(mutex)` | briše mutex |
| `pthread_mutex_lock(mutex)` | zaključava — nit postaje vlasnik; ostale se blokiraju |
| `pthread_mutex_unlock(mutex)` | otključava — samo vlasnik može da otključa |

**Bitno:** samo jedna nit u datom trenutku može biti vlasnik mutex-a.

```c
pthread_mutex_t lock;

void *prva_nit(void *args) {
    pthread_mutex_lock(&lock);
    sleep(20);                 // kritična sekcija
    pthread_mutex_unlock(&lock);
}

void *druga_nit(void *args) {
    sleep(3);
    pthread_mutex_lock(&lock);
    printf("Poruka\n");        // kritična sekcija
    pthread_mutex_unlock(&lock);
}

int main() {
    pthread_t t1, t2;
    pthread_mutex_init(&lock, NULL);
    pthread_create(&t1, NULL, (void *)&prva_nit, NULL);
    pthread_create(&t2, NULL, (void *)&druga_nit, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_mutex_destroy(&lock);
    return 0;
}
```

---

## 4. Uslovne promenljive (`pthread_cond_t`)

Koriste se **u kombinaciji sa mutex-om** za sinhronizaciju na osnovu vrednosti nekog zajedničkog resursa.

**Logika:**
- **Prva nit:** zaključa mutex → blokira se na uslovnoj promenljivoj (čeka uslov) → otključa mutex
- **Druga nit:** zaključa mutex → ispuni uslov → signalizira → otključa mutex

| Funkcija | Opis |
|---|---|
| `pthread_cond_init(cond, attr)` | kreira uslovnu promenljivu |
| `pthread_cond_destroy(cond)` | briše je |
| `pthread_cond_wait(cond, mutex)` | blokira nit; **automatski otključava mutex** dok čeka |
| `pthread_cond_signal(cond)` | budi jednu blokiranu nit |
| `pthread_cond_broadcast(cond)` | budi **sve** blokirane niti |

> Važno: `pthread_cond_wait` se poziva samo kad je mutex već zaključan; `pthread_cond_signal`/`broadcast` se pozivaju u kritičnoj sekciji (mutex zaključan).

### Kako tačno radi `pthread_cond_wait`

`pthread_cond_wait(&cond, &lock)` nije obična funkcija koja samo blokira nit dok mutex ostaje zaključan — ona radi tri stvari **atomično**:

1. **Otključa mutex** (`lock`)
2. Blokira nit i stavlja je na listu čekanja vezanu za `cond`
3. Kada je nit kasnije probuđena (signalom), **opet zaključa mutex** pre nego što se `pthread_cond_wait` vrati

Zato signal koji šalje druga nit ne probudi prvu nit "odmah u praktičnom smislu" — probuđena nit mora prvo ponovo da zaključa mutex, što sme da uradi samo kad ga signalizirajuća nit otključa. Zato se uslov provera kroz `while`, a ne `if` — da uhvati eventualnu promenu uslova ili *spurious wakeup* u međuvremenu.

```c
pthread_mutex_t lock;
pthread_cond_t cond;
int x = 0;

void *prva_nit(void *args) {
    pthread_mutex_lock(&lock);
    while (x < 100)
        pthread_cond_wait(&cond, &lock);   // čeka uslov
    pthread_mutex_unlock(&lock);
}

void *druga_nit(void *args) {
    pthread_mutex_lock(&lock);
    while (x < 200) {
        x++;
        if (x == 100)
            pthread_cond_signal(&cond);    // signalizira ispunjenje uslova
    }
    pthread_mutex_unlock(&lock);
}
```

---

## 5. POSIX semafori (`<semaphore.h>`, tip `sem_t`)

Implementacija **opšteg semafora** (binarni i n-arni). Nemaju vlasnika — svaka nit može izvršiti bilo koju operaciju (nema kontrole ko zove `sem_wait` a ko `sem_post`).

| Funkcija | Opis |
|---|---|
| `sem_init(sem, pshared, value)` | `pshared` je **uvek 0** (samo za niti); `value` je početna vrednost |
| `sem_destroy(sem)` | briše semafor |
| `sem_wait(sem)` | P operacija — uzima "tiket" |
| `sem_post(sem)` | V operacija — vraća "tiket" |

### Mnemonika

- **P** (od *proberen* — pokušati) = "hoću da uđem / uzmem resurs" → smanjuje vrednost. U POSIX-u: `sem_wait`.
- **V** (od *verhogen* — povećati) = "završio sam / vraćam resurs" → povećava vrednost. U POSIX-u: `sem_post`.

Semafor se najlakše zamišlja kao **brojač slobodnih "tiketa"**.

### Tri tipična obrasca za zadatke

**1. Binarni semafor kao zamena za mutex** (inicijalna vrednost 1):
```c
sem_t mutex;
sem_init(&mutex, 0, 1);

sem_wait(&mutex);
// kritična sekcija
sem_post(&mutex);
```

**2. Semafor kao "signal da se nešto desilo"** (inicijalna vrednost 0):
```c
sem_t ready;
sem_init(&ready, 0, 0);   // 0 = "još se nije desilo"

// Nit A:
sem_post(&ready);         // javlja da je spremno

// Nit B:
sem_wait(&ready);         // čeka dok A ne javi
```

**3. Brojeći semafor kao "broj slobodnih mesta"** (proizvođač-potrošač):

| Semafor | Početna vrednost | Značenje |
|---|---|---|
| `empty` | N | broj slobodnih mesta u baferu |
| `full` | 0 | broj popunjenih mesta |
| `mutex` | 1 | ekskluzivni pristup baferu |

```c
#define N 100
int buf[N];
sem_t mutex, empty, full;

void *producer(void *args) {
    for (int i = 0; i < 10000; i++) {
        sem_wait(&empty);      // čeka slobodno mesto
        sem_wait(&mutex);
        // upisivanje podataka u bafer
        sem_post(&mutex);
        sem_post(&full);       // signalizira da postoji podatak
    }
}

void *consumer(void *args) {
    for (int i = 0; i < 10000; i++) {
        sem_wait(&full);       // čeka da postoji podatak
        sem_wait(&mutex);
        // očitavanje podataka iz bafera
        sem_post(&mutex);
        sem_post(&empty);      // signalizira slobodno mesto
    }
}

int main() {
    pthread_t proizvodjac, potrosac;

    sem_init(&mutex, 0, 1);
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, N);

    pthread_create(&proizvodjac, NULL, (void *)&producer, NULL);
    pthread_create(&potrosac, NULL, (void *)&consumer, NULL);

    pthread_join(proizvodjac, NULL);
    pthread_join(potrosac, NULL);

    sem_destroy(&mutex);
    sem_destroy(&full);
    sem_destroy(&empty);

    return 0;
}
```

### Zašto je redosled `wait(empty)` → `wait(mutex)` bitan (čest deadlock)

Ako se redosled zameni:
```c
sem_wait(&mutex);   // POGREŠNO prvo mutex
sem_wait(&empty);
```
dolazi do **deadlock-a**: proizvođač zaključa `mutex`, zatim pokuša `sem_wait(&empty)` — ako je bafer pun, blokira se, **ali drži mutex**. Potrošač onda ne može da uđe ni da pročita podatak (treba mu `mutex`) da bi oslobodio mesto (`sem_post(&empty)`). Niko se ne pomera.

**Pravilo:** semafor koji broji **resurse** (`empty`, `full`) se uvek čeka **pre** mutexa koji štiti pristup. Mutex se drži najkraće moguće, samo tokom stvarnog čitanja/upisa.

---

## Rezime — poređenje mehanizama

| Mehanizam | Zaglavlje | Tip | Glavna upotreba |
|---|---|---|---|
| Mutex | `<pthread.h>` | `pthread_mutex_t` | Strogo međusobno isključenje |
| Uslovna promenljiva | `<pthread.h>` | `pthread_cond_t` | Čekanje na ispunjenje uslova (uz mutex) |
| POSIX semafor | `<semaphore.h>` | `sem_t` | Brojanje resursa (n-arni), nema vlasnika |

## Opšti obrazac za rešavanje zadataka sa semaforima

1. **Identifikuj resurs koji se deli** (bafer, brojač, niz, lista...)
2. **Identifikuj uslove čekanja** — ko čeka šta (npr. "potrošač čeka da ima nešto za čitanje")
3. Za svaki uslov čekanja → **jedan signalni semafor inicijalizovan na 0**
4. Ako više niti pristupa istom deljenom resursu i menja ga → **mutex semafor inicijalizovan na 1**
5. Pazi na redosled: **signalni semafori prvo, mutex tek kad uđeš u kritičnu sekciju**