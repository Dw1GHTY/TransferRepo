# Kako se rešavaju ID3 zadaci na ispitu

## 1. Opšta ideja

ID3 gradi **stablo odluke** iz tabele primera oblika (atribut1, atribut2, ..., atributN, klasa). Svaki unutrašnji čvor stabla je neki atribut, svaka grana iz njega je jedna vrednost tog atributa, a listovi su klase (kod nas obično Da/Ne, Pao/Položio i sl.).

Ideja algoritma: u svakom koraku pitamo se **koji atribut najbolje "razdvaja" primere po klasi** — i njega stavljamo kao sledeći čvor. Mera "koliko dobro razdvaja" je **informaciona dobit**, koja se računa preko **entropije**.

**Opis ID3 algoritma (rekurzivno):**

1. Ako svi primeri u skupu pripadaju istoj klasi → napravi **list** sa tom klasom.
2. U suprotnom:
   - a) Nađi atribut sa najvećom informacionom dobiti.
   - b) Dodaj granu za svaku vrednost tog atributa.
   - c) Rasporedi primere u odgovarajuće podskupove (po vrednosti izabranog atributa).
   - d) Za svaki podskup ponovi ceo postupak (koristeći preostale atribute, bez onog koji je već iskorišćen na tom putu kroz stablo).

Zaustavljanje se dešava kada: svi primeri pripadaju istoj klasi (list), ili nema više atributa za deljenje, ili najbolja dobit nije veća od 0.

---

## 2. Entropija i informaciona dobit — formule

**Entropija skupa S** (mera "nereda"/nečistoće po klasama):

$$H(S) = \sum_{i=1}^{k} -p(C_i)\cdot \log_2 p(C_i)$$

gde je $p(C_i)$ procenat primera iz S koji pripadaju klasi $C_i$.

- Ako su svi primeri iste klase → $H(S)=0$ (čist skup, nema neizvesnosti).
- Ako je tačno 50/50 (dve klase) → $H(S)=1$ (maksimalna neizvesnost za dve klase).

**Informaciona dobit atributa A** za skup S:

$$Gain(S,A) = H(S) - \sum_{v \in vrednosti(A)} \frac{|S_v|}{|S|}\cdot H(S_v)$$

gde je $S_v$ podskup primera iz S kod kojih atribut A ima vrednost v.

Drugim rečima: od ukupne entropije oduzmeš **ponderisani prosek entropija podskupova** koje bi taj atribut napravio. Atribut koji najviše smanji entropiju (najveći Gain) se bira.

---

## 3. "Recept" za ispit — koraci

1. Izračunaj $H(S)$ za **ceo** polazni skup (broj primera po klasi → procenti → uzmi log₂ vrednost sa liste datih vrednosti).
2. Za **svaki preostali atribut** izračunaj $Gain(S,A)$:
   - podeli primere po vrednostima tog atributa,
   - za svaki podskup izračunaj entropiju,
   - napravi ponderisani prosek i oduzmi od $H(S)$.
3. Izaberi atribut sa **najvećom dobiti** → to je koren (ili sledeći čvor u toj grani).
4. Podeli primere po vrednostima izabranog atributa — svaka vrednost postaje grana.
5. Za svaki podskup:
   - ako su **svi primeri iste klase** → napravi **list** s tom klasom (entropija = 0, gotovo za tu granu),
   - ako **nema više atributa** a skup nije čist → list sa **većinskom klasom**,
   - inače → **ponovi korake 1–5** na tom podskupu, koristeći preostale atribute (bez atributa koji je već iskorišćen na tom putu).
6. Nastavi dok sve grane ne završe u listu.
7. (Ako se traži) Izvedi **IF-THEN pravila** — svaki put od korena do lista je jedno pravilo (AND svih uslova na putu ⟹ klasa u listu).

---

## 4. Ključni saveti za ispit

- **Uvek prvo izbroj klase u celom skupu** (koliko Da/Ne, Pao/Položio...) — to ti daje $H(S)$ na početku.
- Iskoristi **date log₂ vrednosti** sa blanketa — one su tu tačno zato da ne moraš da računaš logaritme; samo prepoznaj koji razlomak (npr. 3/7, 5/14...) odgovara kojoj datoj vrednosti.
- Kad je podskup **čist** (svi primeri iste klase), tu se **odmah staje** — ne deli se dalje, entropija je 0.
- **Ne koristi ponovo atribut** koji je već iskorišćen na tom putu kroz stablo (ali se isti atribut *može* ponovo koristiti u nekoj drugoj grani stabla, ako tamo nije još upotrebljen).
- Ako neki atribut potpuno razdvoji podskup (svaka njegova vrednost vodi u čist podskup), njegova dobit je maksimalna moguća (jednaka lokalnoj entropiji tog podskupa) — to je znak da je to skoro sigurno pravi izbor.
- Ako dva atributa imaju **istu (najveću) dobit** — to je tie; na ispitu samo napiši da je izbor proizvoljan i nastavi sa jednim od njih (dosledno).
- Na kraju uvek možeš **proveriti stablo** tako što provučeš svaki red iz tabele kroz njega — treba da dâ tačno onu klasu koja piše u tabeli.

---

# PRIMER — potpuno rešen (Septembar 2025, zadatak 6 — odobravanje kredita)

**Atributi:** Prihod {Nizak, Srednji, Visok}, Kreditna istorija {Loša, Dobra}, Zaposlenost {Zaposlen, Nezaposlen}, Starost {Mladi, Srednjih godina, Stariji} → **Odobren kredit** {Da, Ne}

| # | Prihod | Kreditna istorija | Zaposlenost | Starost | Odobren kredit |
|---|---|---|---|---|---|
|1| Nizak | Loša | Nezaposlen | Mladi | Ne |
|2| Nizak | Loša | Zaposlen | Srednjih god. | Ne |
|3| Srednji | Dobra | Zaposlen | Stariji | Da |
|4| Visok | Dobra | Zaposlen | Mladi | Da |
|5| Nizak | Dobra | Nezaposlen | Stariji | Ne |
|6| Visok | Loša | Zaposlen | Srednjih god. | Da |
|7| Srednji | Dobra | Zaposlen | Mladi | Da |
|8| Nizak | Loša | Zaposlen | Stariji | Ne |
|9| Visok | Dobra | Zaposlen | Stariji | Da |
|10| Srednji | Loša | Nezaposlen | Srednjih god. | Ne |
|11| Nizak | Dobra | Zaposlen | Mladi | Da |
|12| Visok | Loša | Nezaposlen | Stariji | Ne |
|13| Srednji | Dobra | Zaposlen | Srednjih god. | Da |
|14| Nizak | Loša | Zaposlen | Mladi | Ne |

## Korak 1 — Entropija celog skupa

14 primera: **7 Da, 7 Ne** → $p(Da)=p(Ne)=0.5$

$$H(S) = -0.5\log_2(0.5) - 0.5\log_2(0.5) = -0.5(-1)-0.5(-1) = 1$$

## Korak 2 — Dobit svakog atributa (koren)

**Prihod:** Nizak (6: 1Da,5Ne), Srednji (4: 3Da,1Ne), Visok (4: 3Da,1Ne)
- H(Nizak) = $-0.166\log_2(0.166)-0.833\log_2(0.833) = 0.166(2.585)+0.833(0.263) = 0.648$
- H(Srednji)=H(Visok) = $-0.75\log_2(0.75)-0.25\log_2(0.25)=0.75(0.415)+0.25(2)=0.811$
- Ponderisano: $\frac{6}{14}(0.648)+\frac{4}{14}(0.811)+\frac{4}{14}(0.811)=0.741$
- **Gain(Prihod) = 1 − 0.741 = 0.259**

**Kreditna istorija:** Loša (7: 1Da,6Ne), Dobra (7: 6Da,1Ne)
- H(Loša)=H(Dobra) = $-0.1428\log_2(0.1428)-0.857\log_2(0.857)=0.1428(2.807)+0.857(0.222)=0.591$
- Ponderisano: $\frac{7}{14}(0.591)+\frac{7}{14}(0.591)=0.591$
- **Gain(Kreditna istorija) = 1 − 0.591 = 0.409**

**Zaposlenost:** Zaposlen (10: 7Da,3Ne), Nezaposlen (4: 0Da,4Ne)
- H(Zaposlen) = $-0.7\log_2(0.7)-0.3\log_2(0.3)=0.7(0.5146)+0.3(1.737)=0.881$
- H(Nezaposlen) = 0 (čist skup — sve Ne)
- Ponderisano: $\frac{10}{14}(0.881)+\frac{4}{14}(0)=0.630$
- **Gain(Zaposlenost) = 1 − 0.630 = 0.370**

**Starost:** Mladi (5: 3Da,2Ne), Srednjih god. (4: 2Da,2Ne), Stariji (5: 2Da,3Ne)
- H(Mladi)=H(Stariji) = $-0.6\log_2(0.6)-0.4\log_2(0.4)=0.6(0.737)+0.4(1.3219)=0.971$
- H(Srednjih god.) = 1 (50/50)
- Ponderisano: $\frac{5}{14}(0.971)+\frac{4}{14}(1)+\frac{5}{14}(0.971)=0.979$
- **Gain(Starost) = 1 − 0.979 = 0.021**

**Najveća dobit: Kreditna istorija (0.409) → koren stabla.**

## Korak 3 — Grana "Loša" (primeri 1,2,6,8,10,12,14 → 1 Da, 6 Ne)

$H(Loša) = 0.591$ (izračunato gore)

Preostali atributi: Prihod, Zaposlenost, Starost.

- **Prihod:** Nizak(4: sve Ne, H=0), Srednji(1: Ne, H=0), Visok(2: 1Da,1Ne, H=1) → ponderisano $=\frac{2}{7}(1)=0.286$ → **Gain=0.591−0.286=0.306**
- Zaposlenost: ponderisano $=0.464$ → Gain=0.128
- Starost: ponderisano $=0.393$ → Gain=0.198

**Najveća dobit: Prihod (0.306)** → deli granu "Loša" po Prihodu:
- Nizak → svi Ne → **list: Ne**
- Srednji → jedini primer Ne → **list: Ne**
- Visok → primeri 6 (Da) i 12 (Ne), mešano → deli dalje. Zaposlenost i Starost oba savršeno razdvajaju ova 2 primera (tie) → biramo **Zaposlenost**:
  - Zaposlen → **list: Da** (primer 6)
  - Nezaposlen → **list: Ne** (primer 12)

## Korak 4 — Grana "Dobra" (primeri 3,4,5,7,9,11,13 → 6 Da, 1 Ne)

$H(Dobra) = 0.591$

- Prihod: ponderisano $=0.286$ → Gain=0.306
- **Zaposlenost:** Zaposlen(6: svi Da, H=0), Nezaposlen(1: Ne, H=0) → ponderisano $=0$ → **Gain=0.591−0=0.591** (savršeno razdvaja!)
- Starost: ponderisano $=0.393$ → Gain=0.198

**Najveća dobit: Zaposlenost (0.591)** → deli granu "Dobra":
- Zaposlen → svi primeri Da → **list: Da**
- Nezaposlen → jedini primer (5) Ne → **list: Ne**

## Konačno stablo

```
Kreditna istorija
├── Loša
│     └── Prihod
│           ├── Nizak      → Ne
│           ├── Srednji    → Ne
│           └── Visok
│                 └── Zaposlenost
│                       ├── Zaposlen    → Da
│                       └── Nezaposlen  → Ne
└── Dobra
      └── Zaposlenost
            ├── Zaposlen    → Da
            └── Nezaposlen  → Ne
```

**IF-THEN pravila iz stabla:**
1. AKO Kreditna istorija=Loša I Prihod=Nizak ⟹ Ne
2. AKO Kreditna istorija=Loša I Prihod=Srednji ⟹ Ne
3. AKO Kreditna istorija=Loša I Prihod=Visok I Zaposlenost=Zaposlen ⟹ Da
4. AKO Kreditna istorija=Loša I Prihod=Visok I Zaposlenost=Nezaposlen ⟹ Ne
5. AKO Kreditna istorija=Dobra I Zaposlenost=Zaposlen ⟹ Da
6. AKO Kreditna istorija=Dobra I Zaposlenost=Nezaposlen ⟹ Ne

Provera: svih 14 primera iz tabele klasifikuje se ovim stablom tačno onako kako piše u koloni "Odobren kredit" — nema grešaka.

Interesantno: atribut **Starost** se u ovom slučaju **uopšte nije iskoristio** u konačnom stablu — imao je najmanju informacionu dobit u svakom koraku, pa je uvek "izgubio". Ovo se u praksi dešava (isto kao u primeru sa vremenom/košarkom iz predavanja, gde je "vlažnost" ispao nebitan atribut).

---

## 5. Kako ovo primeniti na druga dva zadatka sa tvojih blanketa

Postupak je **identičan** — menja se samo tabela:

- **April 2026 (zad. 7):** atributi Dužina pripreme, Prisustvo na časovima, Način pripreme, Kvalitet sna → Ishod ispita. 14 primera, dat isti set log₂ vrednosti.
- **April 2025 (zad. 6):** atributi Žanr, Trajanje, Ocena kritike → Vredi gledati. 20 primera (malo duže računanje jer ima više redova, ali princip isti).

Za oba: prvo prebroj klase u celom skupu → $H(S)$, pa za svaki atribut izračunaj Gain po istom obrascu kao gore, izaberi najveći, podeli, i rekurzivno ponovi na svakom podskupu dok ne dobiješ čiste listove.
