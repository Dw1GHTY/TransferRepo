from functools import *;
import operator;
from itertools import chain;

"""
### jun 2023
(10 poena) Na programskom jeziku Python napisati funkciju maxTuple(lista1, lista2)
koja za dve liste sa podlistama za koje važi da se broj
elemenata liste i odgovarajućih podliste poklapaju formira listu podlisti uređenih parova
(key, value), gde je key element liste lista1, a value element liste lista2,
i nakon toga određuje par koji je najveći po elementu value. Zabranjeno je korišćenje petlji.

Primer: maxTuple([[1, 2], [3, 4], [5, 6]], [[7, 0], [5, 8], [9, 3]]) = (4, 8)
"""
# ([1,2],[7,0]) ([3,4],[5,8]) ([5,6],[9,3])
def maxTuple(lista1, lista2):
    n = len(lista1)
    rez = [(lista1[i][j], lista2[i][j]) for i in range(n) for j in range(len(lista1[i]))]
    print(rez);
    print("REZULTAT: ", max(rez, key=lambda el: el[1]));


"""
### apr 2023
(10 poena) Na programskom jeziku Python napisati funkciju uredi(lista)
koja za listu cifara zadatu u obliku stringa vraća listu tuple objekata.
Svaki tuple objekat sadrži različitu kombinaciju dve cifre iz unetog broja
pri čemu je na prvoj poziciji veća a na drugoj poziciji manja cifra,
treći element tuple objekta je razlika prve i druge cifre. Zabranjeno je korišćenje petlji.

Primer: uredi("1536") = [(5, 1, 4), (5, 3, 2), (3, 1, 2), (6, 1, 5), (6, 5, 1), (6, 3, 3)]
"""
# svaki sa svakim po dva puta
def uredi(listaCifara):
    lista = [int(x) for x in listaCifara];
    print(lista);
    rez = [(max(lista[x],lista[y]), min(lista[y], lista[x]), abs(lista[x] - lista[y])) for x in range(len(listaCifara) - 1) for y in range(x+1, len(listaCifara), 1)];
    print(rez);


""" 
### okt 2023
(10 poena) 
Na programskom jeziku Python napisati funkciju rezultat(utakmice) 
koja vraća rezultat utakmice sa najvećom razlikom. 
Lista utakmice sadrži onoliko podlisti koliko je grupa na takmičenju.
U svakoj podlisti su rezultati utakmica odigranih u grupi. 
Rezultat se pamti kao par vrednosti, gde je prva vrednost broj poena prvog tima a drugi broj poena drugog tima. 
Zabranjeno je korišćenje petlji.

rezultat([[(60, 50), (88, 76), (85, 97)],   <-- grupa 1
          [(60, 68), (68, 70), (85, 85)],   <-- grupa 2
          [(60, 55), (88, 74), (85, 89)]]   <-- grupa 3
          ) = 18
def rezultat(lista):
    utakmice = reduce(lambda x, y: x + y, lista);   # lista je kolekcija listi, zbir dve liste je lista -> spljosteno
    print(utakmice);
    naj = max(utakmice, key= lambda u: abs(u[0] - u[1]));
    print(naj)
"""
# alternativno
def rezultat(lista):
    sve_utakmice = list(chain(*lista))
    naj = max(sve_utakmice, key=lambda u: abs(u[0] - u[1]))
    print(naj)
    return naj

""" 
### sep 2023
(10 poena) 
Na programskom jeziku Python napisati funkciju qualify(results, Q, q) 
koja vraća listu takmičara koji su se kvalifikovali 
u sledeći krug takmičenja u trčanju na osnovu pravila i postignutih vremena.
Lista results sadrži proizvoljan broj podlisti. 
U svakoj podlisti su rezultati takmičara iz jedne od grupa koji nisu uređeni po vremenu.
Rezultati takmičara se pamte kao uređeni par (broj takmičara, vreme u sekundama). 
U sledeći krug takmičenja direktno se plasira po Q takmičara iz svake grupe sa najboljim vremenima,
dok se od preostalih takmičara iz svih grupa plasira još q sa najboljim rezultatima.
Smatrati da svaka grupa ima najmanje Q+q takmičara i da se vremena svih rezultata takmičara razlikuju.
Zabranjeno je korišćenje petlji.

Uređenje liste takmičara po vremenu moguće je obaviti pozivom funkcije:
sort(results, key=lambda x: x[1])

Primer: 
qualify(
[
    [(1, 44.55), (2, 45.22), (3, 44.33), (4, 46.11)],   <-- grupa 1
    [(5, 46.77), (6, 46.22), (7, 45.88), (8, 44.99)],   <-- grupa 2
    [(9, 44.11), (10, 45.55), (11, 44.44), (12, 46.33)] <-- grupa 3
],
    2, 2
)
= [(3, 44.33), (1, 44.55), (8, 44.99), (7, 45.88), (9, 44.11), (11, 44.44), (2, 45.22), (10, 45.55)]
"""
def qualify(results, Q, q):
    list(map(lambda g: list.sort(g, key=lambda x: x[1]), results))
    
    firstRound = list(chain(*list(map(lambda g: g[0:Q], results))))
    preostali = list(chain(*list(map(lambda g: g[Q:], results))))
    preostali_sorted = sorted(preostali, key=lambda x: x[1])
    lastRound = preostali_sorted[0:q]
    
    print(firstRound + lastRound);
    
    return firstRound + lastRound
    
""" 
(10 poena) Na programskom jeziku Python napisati funkciju prosek(temp) koja određuje prosečnu temperaturu za mesec, 
čiji se podaci o temperaturama po danima šalju kao parametar funkcije. 
Temperature sadrže podliste koje se sastoje od neodređenog broja merenja za svaki dan u toku meseca. 
Termometar povremeno vraća pogrešne vrednosti, 
pa je prvo potrebno za svaki dan odrediti medijalnu vrednost, 
a zatim upotrebiti tako dobijene vrednosti za svaki dan i izračunati prosečnu vrednost temperature za ceo mesec.

Medijalna vrednost je broj koji razdvaja donju i gornju polovinu sortiranog uzorka, 
a u slučaju da se radi o nizu sa parnim brojem elemenata,
za medijalnu vrednost se uzima aritmetička sredina 2 vrednosti koje su kandidati za medijanu.
Zabranjeno je korišćenje petlji (osim u comprehension sintaksi).

Primer: prosek([[8, -15, 4, 9], [3, 2, 33], [2, 4, 4], [8, 2, 12], [3, 5, 1, 15]]) = 5
"""
def prosek(lista):
     print();
     
     
""" 
(10 poena) Takmičenje timova u fudbalu je organizovano u dve faze, 
grupnoj i eliminacionoj. Na takmičenju učestvuje n timova koji su u grupnoj fazi podeljeni u k grupa.
U eliminacionu fazu prolazi ukupno m timova. 
Iz svake grupe direktno prolazi prvih p timova i još q (q<k) najbolje plasiranih timova 
iz svih grupa koji su zauzeli p+1 mesto u grupi (m=p·k+q).
Plasman tima u grupi se određuje na osnovu broja osvojenih bodova i gol razlike.
Na programskom jeziku Python napisati funkciju prolazak(rez, n, k, m, p, q)
koja određuje spisak timova koji su pošli u drugu fazu takmičenja
na osnovu rezultata iz grupne faze (rez).

Parametar rez predstavlja listu uređenih četvorki oblika (tim, grupa, broj bodova, gol razlika).
Smatrati da su parametri funkcije takvi da uvek postoji jedinstveno rešenje.

prolazak
([
    ("T1", 1, 3, 1), ("T2", 3, 7, 4), ("T3", 2, 6, 1), 
    ("T4", 2, 3, 0), ("T5", 3, 5, 2), ("T6", 1, 4, 1),
    ("T7", 1, 4, 2), ("T8", 1, 6, 3), ("T9", 2, 9, 7),
    ("T10", 3, 1, -2), ("T11", 3, 3, -1), ("T12", 2, 0, -4)], 12, 3, 8, 3, 2)
=> ["T8", "T7", "T9", "T3", "T2", "T5", "T6", "T1"]
"""
""" 
rez - rezultati
n - broj timova
k - broj grupa
m - metrika za koliko jos se plasira
p - broj koji prolazi po grupi
q - jos ovoliko najbolje plasiranih
"""
def prolazak(rez, n, k, m, p, q):
    print(rez);
     
    
""" 
(10 poena) Na programskom jeziku Python napisati funkciju prebroji(text, limit)
koja vraća listu karaktera koji se u zadatom string-u 
javljaju više od zadatog broja puta. 
String se prosleđuje parametrom text, 
dok se broj ponavljanja koji treba prekoračiti prosleđuje parametrom limit.
Zabranjeno je korišćenje petlji (osim u comprehension sintaksi).

Primeri: prebroji("aabcdd", 1) = ["a", "d"]
prebroji("abacaddda", 3) = ["a"]
"""
# def prebroji(text, limit):
#     nadjeni = {}; # karakter : brPonavljanja
#     list( if x not in for x in text)
#     print(rez);
    
    
""" 
januar 2026
"""    
def prebroji(text, limit):
    rez = list(set(list(filter(lambda x: text.count(x) > limit, text))));
    print(rez);
    
""" 
2026 apr
"""
# prosecna temp jednog dana = (dan[1] + dan[2])/2
# a svih dana zajedno je suma prosecnih temp / brojem dana
def medianTemp(temp1, temp2):
    return (temp1 + temp2) / 2;
def najstabilniji_dan(podaci):
    prosecnaTemp = reduce(lambda x, y: x + medianTemp(y[1], y[2]), podaci, 0) / len(podaci);
    print(rez);
    
    
""" 2025 okt """

    
def main():
    print("============ START ============");
    # maxTuple([[1, 2], [3, 4], [5, 6]], [[7, 0], [5, 8], [9, 3]])
    # uredi("1536");
    # rezultat([[(60, 50), (88, 76), (85, 97)], [(60, 68), (68, 70), (85, 85)], [(60, 55), (88, 74), (85, 89)]]);
    # test();
    # qualify([[(1, 44.55), (2, 45.22), (3, 44.33), (4, 46.11)],[(5, 46.77), (6, 46.22), (7, 45.88), (8, 44.99)],[(9, 44.11), (10, 45.55), (11, 44.44), (12, 46.33)]],2, 2);
    # prosek([[8, -15, 4, 9], [3, 2, 33], [2, 4, 4], [8, 2, 12], [3, 5, 1, 15]]);
    # prolazak([("T1", 1, 3, 1), ("T2", 3, 7, 4), ("T3", 2, 6, 1), ("T4", 2, 3, 0), ("T5", 3, 5, 2), ("T6", 1, 4, 1),("T7", 1, 4, 2), ("T8", 1, 6, 3), ("T9", 2, 9, 7),
    # ("T10", 3, 1, -2), ("T11", 3, 3, -1), ("T12", 2, 0, -4)], 12, 3, 8, 3, 2);
    # prebroji("aabcdd", 1);
    # prebroji('aabcddffff', 1);
    najstabilniji_dan([("Ponedeljak", 10, 20), ("Utorak", 12, 18), ("Sreda", 15, 26), ("Cetvrtak", 14, 19), ("Petak", 13, 17)]);
if __name__ == "__main__":
    main();