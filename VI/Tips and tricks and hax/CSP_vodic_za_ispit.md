# Kako se rešavaju CSP zadaci na ispitu (bojenje mape)

## 1. Opšta ideja CSP-a

CSP (Constraint Satisfaction Problem) se definiše preko tri stvari:

- **Promenljive (X)** — šta dodeljujemo (npr. svaka prostorija/region je jedna promenljiva)
- **Domeni (D)** — skup mogućih vrednosti za svaku promenljivu (npr. {bela, siva, plava})
- **Ograničenja (C)** — pravila koja dodela mora da poštuje (npr. susedni regioni ne smeju imati istu boju)

Ograničenja se najlakše predstavljaju **grafom ograničenja**: čvorovi su promenljive, a grane povezuju promenljive koje imaju međusobno ograničenje (susedstvo). Ovaj graf je osnova za sve što sledi.

Rešavanje ide kroz **backtracking pretragu**: u svakom koraku biramo jednu nedodeljenu promenljivu, dodeljujemo joj vrednost, proveravamo ograničenja, i idemo dalje (ili se vraćamo ako smo zaglavili). Tri stvari čine ovu pretragu pametnijom — i baš to se traži na ispitu:

1. **Heuristika za izbor SLEDEĆE PROMENLJIVE** — MRV ili Degree heuristika (DH)
2. **Heuristika za izbor SLEDEĆE VREDNOSTI** za tu promenljivu — LCV (Least Constraining Value)
3. **Forward checking** — tehnika koja posle svake dodele "gleda unapred" i skraćuje domene suseda

Bitno je odmah razdvojiti prve dve stavke: **MRV i DH biraju KOJI ČVOR** dodeljujemo sledeći, dok **LCV bira KOJU VREDNOST** dodeljujemo tom već izabranom čvoru. To su heuristike različite "vrste" i mogu se kombinovati, ali zadatak na ispitu obično traži samo jednu od njih (npr. "MRV i FC", ili "DH i FC", ili samo "LCV").

---

## 2. MRV heuristika (Minimum Remaining Values)

**Pitanje koje postavlja:** Od svih nedodeljenih promenljivih, koja ima **najmanje preostalih (legalnih) vrednosti** u domenu?

**Zašto:** Princip "fail-first" — ako neka promenljiva ima samo 1 ili 2 moguće vrednosti, najbolje je nju rešiti odmah, jer će najverovatnije prva izazvati problem (prazan domen) ako pogrešimo. Bolje je to otkriti odmah, nego kasno u pretrazi.

**Kako se bira:** Gleda se **trenutna veličina domena** (posle svih dosadašnjih forward checking redukcija). Bira se promenljiva sa najmanjim brojem vrednosti. Ako je nerešeno (tie) — koristi se **Degree heuristika kao tie-breaker**.

---

## 3. Degree heuristika (DH)

**Pitanje koje postavlja:** Od svih nedodeljenih promenljivih, koja učestvuje u **najvećem broju ograničenja sa drugim nedodeljenim promenljivama** (najveći "stepen" u grafu ograničenja, računajući samo susede koji još nisu dodeljeni)?

**Zašto:** Dodeljivanjem "najpovezanije" promenljive prvo, najviše sužavamo domene preostalih promenljivih (jer forward checking pogađa najviše suseda odjednom). Ovo je posebno korisno na **početku pretrage**, kada MRV ne može da razdvoji promenljive (svi domeni su još puni i jednaki).

**Napomena:** Kada zadatak kaže "primeniti DH i FC" — DH se koristi kao **glavna heuristika u svakom koraku**, ne samo na početku. Stepen se svaki put preračunava — broje se samo **nedodeljeni** susedi, ne originalni stepen iz početnog grafa.

---

## 4. LCV heuristika (Least Constraining Value)

**Pitanje koje postavlja:** Za VEĆ izabranu promenljivu X (izabranu bilo fiksnim redosledom, bilo preko MRV/DH), koja vrednost iz njenog domena **najmanje ograničava** susede — tj. koja vrednost ostavlja nedodeljenim susedima **najviše preostalih opcija**?

**Zašto:** MRV i DH rade po principu "fail-first" (žele da brzo otkriju slepe ulice). LCV radi suprotno — princip **"succeed-first"**: bira vrednost koja najmanje verovatno vodi u slepu ulicu, čuvajući što više opcija susedima za kasnije.

**Kako se računa, korak po korak, za svaku kandidat-vrednost v iz domena od X:**
1. Pogledaj sve **nedodeljene** susede od X.
2. Za svakog takvog suseda proveri da li se vrednost *v* nalazi u njegovom trenutnom domenu.
3. Ako da, to se broji kao "1 pogodak" (jedna opcija bi mu bila oduzeta kad bi X uzeo tu vrednost).
4. Saberi pogotke za sve susede — to je "cena" vrednosti *v*.
5. Vrednost sa **najmanjom cenom** (najmanje pogodaka) se bira prva.

**Bitna napomena o simetriji:** Ako su svi domeni još potpuno puni i simetrični (npr. na samom početku pretrage, pre ijedne dodele), LCV **ne može da razdvoji boje** — sve boje "koštaju" isto, jer još ništa nije asimetrično smanjeno. LCV počinje da daje pravi signal tek kada su neki domeni već neravnomerno smanjeni prethodnim dodelama. Kad se to desi (tie), boju biraš proizvoljno/po redosledu iz domena (isto kao i kod MRV/DH tie-breaka).

**Ako zadatak traži ISKLJUČIVO LCV** (bez MRV/DH): to znači da nemaš heuristiku za biranje SLEDEĆE PROMENLJIVE — kroz promenljive ideš fiksnim, prirodnim redosledom (onako kako su numerisane/obeležene u zadatku), a LCV koristiš samo da odlučiš kojom bojom da počneš probu za svaku od njih.

---

## 5. Forward Checking (FC)

Posle **svake** dodele vrednosti promenljivoj X:

- Za svaku **nedodeljenu** promenljivu koja je susedna sa X (ima ograničenje sa njom), **ukloni iz njenog domena** vrednost koja je upravo dodeljena X-u.
- Ako neki domen postane **prazan skup** → to je slepa ulica → vraćamo se (**backtrack**) i probamo drugu vrednost za prethodnu promenljivu.
- Ako nijedan domen nije prazan → nastavljamo na sledeći korak (biramo sledeću promenljivu po heuristici).

Napomena: čak i kad zadatak eksplicitno ne traži FC (npr. čist LCV zadatak), moraš neformalno pratiti domene suseda kroz ceo postupak — bez toga ne možeš ni da izračunaš LCV "cenu" niti da uočiš kad dođe do konflikta.

---

## 6. Uporedni pregled sve tri heuristike

| | MRV | DH (Degree) | LCV |
|---|---|---|---|
| Šta bira | sledeću **promenljivu** | sledeću **promenljivu** | sledeću **vrednost** za već izabranu promenljivu |
| Glavni kriterijum | najmanji preostali domen | najveći (efektivni) stepen prema nedodeljenim susedima | vrednost koja najmanje smanjuje domene suseda |
| Princip | "fail-first" — brzo otkriti slepe ulice | "najviše propagacije" — brzo suziti ostatak grafa | "succeed-first" — izbeći pravljenje slepe ulice |
| Da li gleda domene suseda | ne direktno (gleda sopstveni domen čvora) | ne | da — to mu je jedini kriterijum |
| Da li gleda stepen suseda | ne (osim kao tie-breaker) | da — glavni kriterijum | ne |
| Kad ne daje signal (tie) | svi domeni jednake veličine | svi stepeni jednaki | svi domeni suseda još puni/simetrični |
| Provera praznog domena | posle svake dodele, nezavisno od heuristike | isto | isto |

---

## 7. "Recept" za ispit — redosled koraka

1. Definisati CSP: promenljive, domeni, **graf ograničenja** (eksplicitno napisati listu suseda)
2. Izračunati stepen (broj suseda) svake promenljive — treba za DH i za tie-breaking
3. U svakom koraku: izabrati sledeću promenljivu — po MRV ili DH heuristici (ako je tražena), ili fiksnim redosledom (ako zadatak traži samo LCV)
4. Odabrati vrednost za tu promenljivu — po LCV heuristici (ako je tražena), ili prvu preostalu iz domena (ako LCV nije tražen)
5. Primeniti forward checking na sve nedodeljene susede
6. Proveriti prazne domene → backtrack ako treba
7. Ponavljati dok sve promenljive nisu dodeljene

---

# PRIMER 1 — MRV + Forward Checking

**Zadatak:** Mapa stana sa 5 prostorija, boje: **bela (B), siva (S), plava (P)**

```
[ 1 ][   2   ][ 3 ]
[  4  ][   5   ]
```

Iz rasporeda prostorija se vidi da soba **2** (širока, gore) graniči i sa 4 i sa 5 (jer 2 leži iznad granice između 4 i 5), a soba 1 graniči samo sa 4, soba 3 samo sa 5.

**Graf ograničenja (susedi):**

| Promenljiva | Susedi | Stepen |
|---|---|---|
| 1 | 2, 4 | 2 |
| 2 | 1, 3, 4, 5 | 4 |
| 3 | 2, 5 | 2 |
| 4 | 1, 2, 5 | 3 |
| 5 | 2, 3, 4 | 3 |

Domeni na početku: D1=D2=D3=D4=D5 = {B, S, P}

### Korak po korak

**Korak 1.** Svi domeni imaju 3 vrednosti → MRV nerešeno (tie) → tie-break preko stepena: najveći stepen ima **X2** (stepen 4) → **biramo X2**.
Dodela: **X2 = B**
Forward checking (ukloni B iz suseda 1,3,4,5):
D1={S,P}, D3={S,P}, D4={S,P}, D5={S,P} → nijedan domen nije prazan ✓

**Korak 2.** Preostale: {1,3,4,5}, sve imaju po 2 vrednosti → MRV tie → tie-break preko stepena *prema nedodeljenim susedima*: deg(1)=1 (samo 4), deg(3)=1 (samo 5), deg(4)=2 (1 i 5), deg(5)=2 (3 i 4) → tie između 4 i 5 → biramo **X4** (manji indeks).
Dodela: **X4 = S**
Forward checking (ukloni S iz nedodeljenih suseda 1 i 5; sused 2 je već dodeljen):
D1: {S,P} → **{P}**, D5: {S,P} → **{P}** → nijedan domen nije prazan ✓

**Korak 3.** Preostale: {1,3,5}. Domeni: D1={P} (1), D3={S,P} (2), D5={P} (1) → MRV bira između 1 i 5 (oba veličine 1) → tie-break preko stepena prema nedodeljenim: deg(1)=0 (2 i 4 su dodeljeni), deg(5)=1 (3 je nedodeljen) → **biramo X5**.
Dodela: **X5 = P** (jedina vrednost)
Forward checking (ukloni P iz nedodeljenog suseda 3; 2 i 4 su već dodeljeni):
D3: {S,P} → **{S}** → nije prazan ✓

**Korak 4.** Preostale: {1,3}. D1={P} (1), D3={S} (1) → tie, stepen prema nedodeljenim oboma = 0 → proizvoljno biramo **X1**.
Dodela: **X1 = P** (jedina vrednost)
Forward checking: susedi 1 su 2 i 4, oba već dodeljena → nema šta da se propagira.

**Korak 5.** Preostala: {3}. D3={S}.
Dodela: **X3 = S** (jedina vrednost)

### Rešenje

| Soba | 1 | 2 | 3 | 4 | 5 |
|---|---|---|---|---|---|
| Boja | plava | bela | siva | siva | plava |

Provera svih ograničenja (1-2, 2-3, 2-4, 2-5, 1-4, 3-5, 4-5): sve zadovoljene ✓ — **rešenje pronađeno bez backtrackinga.**

---

# PRIMER 2 — Degree Heuristika + Forward Checking

**Zadatak:** Mapa okruga (7 regiona), boje: **žuta (Ž), crvena (C), plava (P)**

Regioni: Beograd (Be), Podunavski (Po), Braničevski (Br), Borski (Bo), Šumadijski (Šu), Pomoravski (Pm), Rasinski (Ra)

**Graf ograničenja (susedi, na osnovu mape):**

| Region | Susedi | Stepen |
|---|---|---|
| Beograd | Podunavski, Šumadijski | 2 |
| Podunavski | Beograd, Braničevski, Pomoravski, Šumadijski | 4 |
| Braničevski | Podunavski, Borski, Pomoravski | 3 |
| Borski | Braničevski | 1 |
| Šumadijski | Beograd, Podunavski, Pomoravski, Rasinski | 4 |
| Pomoravski | Podunavski, Braničevski, Šumadijski, Rasinski | 4 |
| Rasinski | Šumadijski, Pomoravski | 2 |

Domeni na početku: svi = {Ž, C, P}

### Korak po korak

**Korak 1.** Svi domeni su puni (3) → gledamo direktno **stepen** (DH je glavna heuristika): najveći stepen (4) imaju Po, Šu, Pm → tie → biramo **Podunavski** (proizvoljan izbor između vezanih).
Dodela: **Po = Ž**
Forward checking (ukloni Ž iz suseda Be, Br, Pm, Šu):
D(Be)={C,P}, D(Br)={C,P}, D(Pm)={C,P}, D(Šu)={C,P} → nema praznih ✓

**Korak 2.** Nedodeljeni: {Be,Br,Bo,Šu,Pm,Ra}. Stepen prema nedodeljenim susedima:
Be=1 (Šu), Br=2 (Bo,Pm), Bo=1 (Br), **Šu=3** (Be,Pm,Ra), **Pm=3** (Br,Šu,Ra), Ra=2 (Šu,Pm)
Tie između Šu i Pm (stepen 3) → biramo **Šumadijski**.
Dodela: **Šu = C**
Forward checking (ukloni C iz nedodeljenih suseda Be, Pm, Ra; Po je već dodeljen):
D(Be)={C,P}→**{P}**, D(Pm)={C,P}→**{P}**, D(Ra)={Ž,C,P}→**{Ž,P}** → nema praznih ✓

**Korak 3.** Nedodeljeni: {Be,Br,Bo,Pm,Ra}. Stepen prema nedodeljenim:
Be=0, **Br=2** (Bo,Pm), Bo=1 (Br), **Pm=2** (Br,Ra), Ra=1 (Pm)
Tie između Br i Pm (stepen 2) → tie-break preko MRV: D(Br)={C,P} (2), D(Pm)={P} (1) → **biramo Pomoravski** (manji domen).
Dodela: **Pm = P** (jedina vrednost)
Forward checking (ukloni P iz nedodeljenih suseda Br i Ra; Po, Šu već dodeljeni):
D(Br)={C,P}→**{C}**, D(Ra)={Ž,P}→**{Ž}** → nema praznih ✓

**Korak 4.** Nedodeljeni: {Be,Br,Bo,Ra}. Stepen prema nedodeljenim: Be=0, **Br=1** (Bo), Bo=1 (Br), Ra=0.
Tie između Br i Bo → tie-break MRV: D(Br)={C} (1), D(Bo)={Ž,C,P} (3) → **biramo Braničevski**.
Dodela: **Br = C** (jedina vrednost)
Forward checking (ukloni C iz nedodeljenog suseda Bo; Po, Pm već dodeljeni):
D(Bo)={Ž,C,P}→**{Ž,P}** → nije prazan ✓

**Korak 5.** Nedodeljeni: {Be,Bo,Ra}. Svi imaju stepen 0 prema nedodeljenim → MRV tie-break: D(Be)={P} (1), D(Ra)={Ž} (1), D(Bo)={Ž,P} (2) → tie Be/Ra → proizvoljno biramo **Beograd**.
Dodela: **Be = P** (jedina vrednost) — nema nedodeljenih suseda za FC.

**Korak 6.** Nedodeljeni: {Bo,Ra}. D(Ra)={Ž} (1) < D(Bo)={Ž,P} (2) → biramo **Rasinski**.
Dodela: **Ra = Ž** (jedina vrednost) — nema nedodeljenih suseda za FC.

**Korak 7.** Preostao: **Borski**. D(Bo)={Ž,P} → biramo prvu vrednost: **Bo = Ž**

### Rešenje

| Region | Beograd | Podunavski | Braničevski | Borski | Šumadijski | Pomoravski | Rasinski |
|---|---|---|---|---|---|---|---|
| Boja | plava | žuta | crvena | žuta | crvena | plava | žuta |

Provera svih 10 ograničenja: sve zadovoljene ✓ — **rešenje pronađeno bez backtrackinga.**

---

# PRIMER 3 — LCV heuristika (bez MRV/DH)

**Zadatak (ilustracija istog principa kao "samo LCV" zadaci na ispitu):** Isti raspored soba kao u Primeru 1 (5 soba), ali boje su sada **crvena (R), plava (P), zelena (Z)**, i zadatak traži **isključivo LCV** (bez MRV/DH i bez eksplicitnog FC).

**Graf ograničenja je isti kao u Primeru 1:** 1-2, 2-3, 2-4, 2-5, 1-4, 3-5, 4-5

**Kako biramo SLEDEĆU PROMENLJIVU:** pošto nema MRV ni DH, ideš fiksnim redosledom po numeraciji: **1, 2, 3, 4, 5**.

**Kako biramo VREDNOST za svaku:** LCV — vrednost koja najmanje "pogađa" nedodeljene susede. Redosled boja pri jednakosti: R, pa P, pa Z.

Domeni na početku: D1=D2=D3=D4=D5 = {R, P, Z}

### Korak po korak

**Korak 1. Promenljiva 1** (prva po fiksnom redosledu). Susedi: 2, 4 — oba nedodeljena, oba domena puna {R,P,Z}.
LCV cena za svaku boju: R→pogađa 2 i 4 (2 pogotka), P→2 pogotka, Z→2 pogotka. **Sve tri boje su izjednačene** (domeni suseda su još simetrični) → biramo prvu po redosledu: **1 = R**.
Ažuriranje domena suseda (1 i 4 su jedini susedi od 1): D2: {R,P,Z}→{P,Z}, D4: {R,P,Z}→{P,Z}.

**Korak 2. Promenljiva 2.** Domen: {P,Z}. Nedodeljeni susedi: 3 {R,P,Z}, 4 {P,Z}, 5 {R,P,Z}.
LCV cena: P → pogađa 3 (ima P), 4 (ima P), 5 (ima P) = **3 pogotka**. Z → pogađa 3, 4, 5 (sve tri imaju Z) = **3 pogotka**. Ponovo tie (obe boje su još svuda prisutne) → biramo prvu po redosledu: **2 = P**.
Ažuriranje suseda (3, 4, 5): D3: {R,P,Z}→{R,Z}, D4: {P,Z}→**{Z}** (ostala samo jedna vrednost!), D5: {R,P,Z}→{R,Z}.

**Korak 3. Promenljiva 3.** Domen: {R,Z}. Nedodeljeni sused: samo 5 {R,Z} (2 je već dodeljen).
LCV cena: R → pogađa 5 (ima R) = 1 pogodak. Z → pogađa 5 (ima Z) = 1 pogodak. Tie → biramo prvu po redosledu: **3 = R**.
Ažuriranje suseda (5): D5: {R,Z}→**{Z}**.

**Korak 4. Promenljiva 4.** Domen: {Z} — nema izbora, forsirana vrednost.
Provera sa već dodeljenim susedima (1=R, 2=P): Z≠R ✓, Z≠P ✓ → **4 = Z**.
Ažuriranje suseda (5 je jedini nedodeljeni sused od 4): D5: {Z} → **{} PRAZAN DOMEN!**

**Zastoj!** Domen promenljive 5 je postao prazan → **backtrack**. Vraćamo se na poslednju promenljivu koja je imala alternativu — to je **promenljiva 3** (promenljiva 4 nije imala izbor, njen domen je već bio veličine 1).

**Korak 3 (ponovo, backtrack).** Vraćamo domene na stanje pre koraka 3: D3={R,Z}, D5={R,Z}. Probamo **sledeću LCV vrednost za 3: Z** (pošto R nije uspelo).
Dodela: **3 = Z**.
Ažuriranje suseda (5): D5: {R,Z}→**{R}**.

**Korak 4 (ponovo).** D4 je i dalje {Z} (4 nije sused od 3, pa se nije menjalo). Forsirano: **4 = Z**. Provera sa 1=R, 2=P: Z≠R ✓, Z≠P ✓.
Ažuriranje suseda (5): D5: {R} → Z nije u domenu (nema šta da se briše) → D5 ostaje **{R}** → nije prazan ✓

**Korak 5. Promenljiva 5.** Domen: {R} — forsirano. Provera sa dodeljenim susedima (2=P, 3=Z, 4=Z): R≠P ✓, R≠Z ✓, R≠Z ✓ → **5 = R**.

### Rešenje

| Soba | 1 | 2 | 3 | 4 | 5 |
|---|---|---|---|---|---|
| Boja | crvena | plava | zelena | zelena | crvena |

Provera svih ograničenja: sve zadovoljene ✓ — **ovaj put JE bio potreban jedan backtrack.**

**Pouka ovog primera:** LCV smanjuje šansu za slepu ulicu, ali je ne garantuje potpuno — naročito na početku pretrage kad su domeni suseda još simetrični pa LCV ne može ništa da razdvoji (kao u koracima 1 i 2 iznad), tie-break izbor je i dalje suštinski proizvoljan i može odvesti u ćorsokak. Kad se to desi, backtrack radiš na potpuno isti način kao kod MRV/DH — samo što sledeći put probaš **sledeću vrednost po LCV redosledu**, ne sledeću promenljivu.

---

## 8. Šta ako ispit traži slučaj sa backtrackingom?

Ako u nekom koraku **domen postane prazan** posle forward checking-a (ili posle proste provere kod LCV-only zadataka):
1. Vraćamo se na **prethodno dodeljenu promenljivu koja je imala više od jedne moguće vrednosti** (promenljiva sa forsiranom, jedinom vrednošću se preskače — ona nije imala alternativu)
2. Probamo **sledeću preostalu vrednost** iz njenog domena, po redosledu koji heuristika propisuje (LCV redosled, ili prosto sledeća u nizu)
3. Ponovo primenjujemo forward checking (ili proveru domena) od te tačke
4. Ako nijedna vrednost ne radi → vraćamo se još jedan korak unazad

Na ispitu je dovoljno da eksplicitno napišeš: *"Domen promenljive X je postao prazan → backtrack na promenljivu Y, probamo sledeću vrednost."*

## 9. Ključni saveti za ispit

- **Uvek prvo nacrtaj/napiši graf ograničenja** (lista suseda) — sve ostalo zavisi od njega.
- Kad heuristika (MRV, DH ili LCV) da **nerešeno (tie)**, to je normalno — samo eksplicitno napiši koju si vrednost proizvoljno izabrao/la i zašto (npr. "biramo promenljivu/boju sa manjim indeksom/redosledom").
- MRV se računa nad **trenutnim** (već skraćenim) domenima, ne nad početnim.
- Stepen za DH se računa samo prema **nedodeljenim** susedima — ne prema svim susedima iz originalnog grafa.
- LCV ne daje signal dok su domeni suseda simetrični — to je normalno, ne greška; signal se pojavljuje tek kad prethodne dodele naprave asimetriju.
- Ako zadatak traži **samo LCV** (bez MRV/DH), promenljive biraš fiksnim/prirodnim redosledom — LCV se odnosi isključivo na izbor boje.
- Posle **svake** dodele — odmah radi forward checking (ili bar proveru domena), pre nego što biraš sledeću promenljivu.
- Uvek na kraju **proveri sva ograničenja** da potvrdiš da je rešenje ispravno.
