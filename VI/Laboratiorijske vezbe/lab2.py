from functools import reduce;
import operator;
#region Zadatak 1
def poredak(lista1, lista2):
    n = max(len(lista1), len(lista2));
    # postavljanje 0 na pozicijama manje liste
    l1 = lista1 + [0] * (n - len(lista1))
    print(l1);
    l2 = lista2 + [0] * (n - len(lista2))
    print(l2);
    rez = list((x, y, 'Jeste' if y==2*x else 'Nije') for x,y in zip(l1, l2));
    print(rez);
#endregion

#region Zadatak 2
def spojidict(lista1, lista2):
    n = max(len(lista1), len(lista2));
    l1 = lista1 + ['-'] * (n - len(lista1));
    l2 = lista2 + ['-'] * (n - len(lista2));
    rez = list({'Prvi': x, 'Drugi': y} for x,y in zip(l1, l2));
    
    print(rez);
#endregion

#region Zadatak 3
def spoji(lista1, lista2):
    n = max(len(lista1), len(lista2));
    l1 = lista1 + [0] * (n - len(lista1));
    print(l1);
    l2 = lista2 + [0] * (n - len(lista2));
    print(l2);
    rez = list((min(x,y), max(x,y), x+y) for x,y in zip(l1, l2));
    
    print("Rez:\n",rez);
#endregion

#region Zadatak 4
def suma(megaLista):
    rez = [x for x in megaLista];
    print(sum(rez));
#endregion

#region Zadatak 5
# proizvod([[1, 2, 3], [4, 5, 6], [7, 8, 9]], [1, 2, 3])
def proizvod(listaA, listaB):
    brPodlistiA = len(listaB); # u primeru je to = 3
    
    rez = [sum(listaA[x]) * listaB[x] for x in range(brPodlistiA)]
    
    print(rez);
    
#endregion

#region Zadatak 6
def objedini(lista1, lista2):
    n = max(len(lista1), len(lista2));
    l1 = lista1 + [0] * (n - len(lista1));
    l2 = lista2 + [0] * (n - len(lista2));
    
    rez = [(min(x,y), max(x,y)) for x,y in zip(l1,l2)];
    
    print(rez);
#endregion

#region Zadatak 7
# objedini([(1,), (3, 4, 5), (7,), (1, 4, 5), (6, 2, 1, 3)])
def objedini(tupleList):
 
    rez = { t[0]: (list(t[1:]) if len(t) > 1 else None) for t in tupleList }    
    print(rez);
    
#endregion

#region Zadatak 8
def izracunaj(lista):
    rez = [ x if not isinstance(x, list) else (reduce(operator.mul, x, 1)) for x in lista]
    print(rez);
    
    """ Upisujemo u rezultat svaki element koji nije lista, u suprotnom redukujemo/mnozimo celu listu, 
        i tako za svaki element ulazne liste
    """
#endregion

#region Zadatak 9
# isto cu koristiti reduce za sumu elemenata veceg indeksa od onog koji se obradjuje
def zamena(lista, x):
    rez = [ el if el >= x else sum(lista[lista.index(el)+1:]) for el in lista];
    print(rez);
#endregion

#region Zadatak 10
def stepen(lista):
    rez = [lista[x]**lista[x+1] for x in range(len(lista) - 1)]
    print(rez);
#endregion

#region Zadatak 11
def proizvod(lista):
    rez = reduce(operator.mul, [reduce(operator.mul, x, 1) for x in lista], 1);
    print(rez);
    
# i sa rekurzijom
def proizvod(lista):
    return reduce(operator.mul, [x if not isinstance(x, list) else proizvod(x) for x in lista], 1); 
#endregion

#region Zadatak 12
def izracunaj(lista):
    rez = [x**2 if not isinstance(x, list) else reduce(operator.add, list(map(lambda el: el**2, x)), 0) for x in lista];
    print(rez);
#endregion

#region Zadatak 13
def skupi(lista):
    print("Ulaz: ", lista)
#endregion

#region Zadatak 14
def suma(lista):
    rez = reduce(operator.add,[reduce(operator.mul, x, 1) for x in lista], 0);
    
    print(rez);
#endregion

#region Zadatak 15
def promeni(lista, x):
    rez = [((br-x) if br>=x else (br+x)) for br in lista]
    print(rez);
#endregion

#region Zadatak 16
# broj("#FA0EA0") R:FA G:0E B:A0
def broj(rgbBroj):
    print(rgbBroj);
    hexBoja = rgbBroj.lstrip("#")
    print(int(rgbBroj[0:2], 10), int(rgbBroj[2:4], 10), int(rgbBroj[4:6], 10))
#endregion

#region Zadatak 17
#endregion

#region Zadatak 18
#endregion

#region Zadatak 19
#endregion

#region Zadatak 20
#endregion


""" 
min()
max()
sorted()
zip()
map()
filter()
reduce()
"""

def main():
    print("============ START ============");
    # poredak([1, 7, 2, 4], [2, 5, 2]);
    # spojidict([1, 7, 2, 4], [2, 5, 2]);
    # spoji([1, 7, 2, 4], [2, 5, 2]);
    # suma([[1, 2, 3], [4, 5, 6], [7, 8, 9]])
    # proizvod([[1, 2, 3], [4, 5, 6], [7, 8, 9]], [1, 2, 3])
    # objedini([1, 7, 2, 4, 5], [2, 5, 2]);
    # objedini([(1,), (3, 4, 5), (7,), (1, 4, 5), (6, 2, 1, 3)]);
    # izracunaj([1, 5, [1, 5, 3], [4, 2], 2, [6, 3]])
    # zamena([1, 7, 5, 4, 9, 1, 2, 7], 5)
    # stepen([1, 5, 2, 6, 1, 6, 3, 2, 9]);
    # proizvod([[1, 3, 5], [2, 4, 6], [1, 2, 3]])
    # izracunaj([2, 4, [1, 2, 3], [4, 2], 2, [9, 5]])
    # skupi([[1, 3, 5], [2, 4, 6], [1, 2]]) NEURADNJENO
    # suma([[1, 2, 3], [4, 5, 6], [7, 8, 9]])
    # promeni([7, 1, 3, 5, 6, 2], 3)
    broj("#FA0EA0")
if __name__ == "__main__":
    main();