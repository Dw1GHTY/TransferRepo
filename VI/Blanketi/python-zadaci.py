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
    
    
def main():
    print("============ START ============");
    # maxTuple([[1, 2], [3, 4], [5, 6]], [[7, 0], [5, 8], [9, 3]])
    # uredi("1536");
    # rezultat([[(60, 50), (88, 76), (85, 97)], [(60, 68), (68, 70), (85, 85)], [(60, 55), (88, 74), (85, 89)]]);
    # test();
    # qualify([[(1, 44.55), (2, 45.22), (3, 44.33), (4, 46.11)],[(5, 46.77), (6, 46.22), (7, 45.88), (8, 44.99)],[(9, 44.11), (10, 45.55), (11, 44.44), (12, 46.33)]],2, 2);
    prosek([[8, -15, 4, 9], [3, 2, 33], [2, 4, 4], [8, 2, 12], [3, 5, 1, 15]]);
if __name__ == "__main__":
    main();