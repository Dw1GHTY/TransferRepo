# Kako se rešavaju CSP zadaci na ispitu (bojenje mape)

## 1. Opšta ideja CSP-a

CSP (Constraint Satisfaction Problem) se definiše preko tri stvari:

- **Promenljive (X)** — šta dodeljujemo (npr. svaka prostorija/region je jedna promenljiva)
- **Domeni (D)** — skup mogućih vrednosti za svaku promenljivu (npr. {bela, siva, plava})
- **Ograničenja (C)** — pravila koja dodela mora da poštuje (npr. susedni regioni ne smeju imati istu boju)

Ograničenja se najlakše predstavljaju **grafom ograničenja**: čvorovi su promenljive, a grane povezuju promenljive koje imaju međusobno ograničenje (susedstvo). Ovaj graf je osnova za sve što sledi.

Rešavanje ide kroz **backtracking pretragu**: u svakom koraku biramo jednu nedodeljenu promenljivu, dodeljujemo joj vrednost, proveravamo ograničenja, i idemo dalje (ili se vraćamo ako smo zaglavili). Dve stvari čine ovu pretragu pametnijom — i baš to se traži na ispitu:

1. **Heuristika za izbor SLEDEĆE promenljive** — MRV ili Degree heuristika
2. **Forward checking** — tehnika koja posle svake dodele "gleda unapred" i skraćuje domene suseda

---

## 2. MRV heuristika (Minimum Remaining Values)

**Pitanje koje postavlja:** Od svih nedodeljenih promenljivih, koja ima **najmanje preostalih (legalnih) vrednosti** u domenu?

**Zašto:** Princip "fail-first" — ako neka promenljiva ima samo 1 ili 2 moguće vrednosti, najbolje je nju rešiti odmah, jer će najverovatnije prva izazvati problem (prazan domen) ako pogrešimo. Bolje je to otkriti odmah, nego kasno u pretrazi.

**Kako se bira:** Gleda se **trenutna veličina domena** (posle svih dosadašnjih forward checking redukcija). Bira se promenljiva sa najmanjim brojem vrednosti. Ako je nerešeno (tie) — koristi se **Degree heuristika kao tie-breaker**.

---

## 3. Degree heuristika (DH)

**Pitanje koje postavlja:** Od svih nedodeljenih promenljivih, koja učestvuje u **najvećem broju ograničenja sa drugim nedodeljenim promenljivama** (najveći "stepen" u grafu ograničenja, računajući samo susede koji još nisu dodeljeni)?

**Zašto:** Dodeljivanjem "najpovezanije" promenljive prvo, najviše sužavamo domene preostalih promenljivih (jer forward checking pogađa najviše suseda odjednom). Ovo je posebno korisno na **početku pretrage**, kada MRV ne može da razdvoji promenljive (svi domeni su još puni i jednaki).

**Napomena:** Kada zadatak kaže "primeniti DH i FC" — DH se koristi kao **glavna heuristika u svakom koraku**, ne samo na početku.

---

## 4. Forward Checking (FC)

Posle **svake** dodele vrednosti promenljivoj X:

- Za svaku **nedodeljenu** promenljivu koja je susedna sa X (ima ograničenje sa njom), **ukloni iz njenog domena** vrednost koja je upravo dodeljena X-u.
- Ako neki domen postane **prazan skup** → to je slepa ulica → vraćamo se (**backtrack**) i probamo drugu vrednost za prethodnu promenljivu.
- Ako nijedan domen nije prazan → nastavljamo na sledeći korak (biramo sledeću promenljivu po heuristici).

---

## 5. "Recept" za ispit — redosled koraka

1. Definisati CSP: promenljive, domeni, **graf ograničenja** (eksplicitno napisati listu suseda)
2. Izračunati stepen (broj suseda) svake promenljive — treba za DH i za tie-breaking
3. U svakom koraku: izabrati sledeću promenljivu po heuristici (MRV ili DH)
4. Dodeliti joj prvu preostalu vrednost iz domena (pošto LCV nije traženo, redosled boja je proizvoljan/leksikografski)
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

## 6. Šta ako ispit traži slučaj sa backtrackingom?

Ako u nekom koraku **domen postane prazan** posle forward checking-a:
1. Vraćamo se na **prethodno dodeljenu promenljivu**
2. Probamo **sledeću preostalu vrednost** iz njenog domena (ako je ima)
3. Ponovo primenjujemo forward checking od te tačke
4. Ako nijedna vrednost ne radi → vraćamo se još jedan korak unazad

Na ispitu je dovoljno da eksplicitno napišeš: *"Domen promenljive X je postao prazan → backtrack na promenljivu Y, probamo sledeću vrednost."*

## 7. Ključni saveti za ispit

- **Uvek prvo nacrtaj/napiši graf ograničenja** (lista suseda) — sve ostalo zavisi od njega.
- Kad heuristika (MRV ili DH) da **nerešeno (tie)**, to je normalno — samo eksplicitno napiši koju si vrednost proizvoljno izabrao/la i zašto (npr. "biramo promenljivu sa manjim indeksom").
- MRV se računa nad **trenutnim** (već skraćenim) domenima, ne nad početnim.
- Stepen za DH se računa samo prema **nedodeljenim** susedima — ne prema svim susedima iz originalnog grafa.
- Posle **svake** dodele — odmah radi forward checking, pre nego što biraš sledeću promenljivu.
- Uvek na kraju **proveri sva ograničenja** da potvrdiš da je rešenje ispravno.
