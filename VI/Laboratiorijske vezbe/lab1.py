#region Zadatak 1
def parni(lista):
    dict = {'Parni': [], 'Neparni': []};
    for x in lista:
        if x % 2 == 0:
            # add to parni
            dict['Parni'].append(x);
        else:
            # add to neparni
            dict['Neparni'].append(x);
    else:      
        print("Rezultat: ", dict.items());
#endregion

#region Zadatak 2
def numlista(lista):
    rez = {};
    tip = '';
    for x in lista:
        tip = type(x).__name__
        if tip not in rez:
            rez[tip] = [];
        rez[tip].append(x);
    print(rez);
#endregion

#region Zadatak 3
def uredi(lista, n, val):
    for x in range(len(lista)):
        print(x);
        if x < n:
            lista[x] += val;
        else:
            lista[x] -= val;
    print(lista);
#endregion

#region Zadatak 4
def zbir(lista):
    rez = [];
    for x in range(0, len(lista) - 1, 1):        
        rez.append(lista[x] + lista[x+1]);
    print(rez);

#endregion

#region Zadatak 5
def brojel(*args):
    rez = [];
    for x in args:
        if type(x) != type(rez):
            rez.append(-1);
        else:
            rez.append(len(x));
    print(rez);
#endregion

#region Zadatak 6
def razlika(lista1, lista2):
    rez = [];
    for x in range(len(lista1)):
        if lista1[x] not in lista2:
            rez.append(lista1[x]);
    print(rez);                 
#endregion

#region Zadatak 7
def operacija(toupleList):
    rez = [];
    sum = 0;
    for touple in toupleList:
        for y in range(len(touple)):
            print(y, ": ", touple[y]);  
            sum += touple[y];
        rez.append(sum);
        sum = 0;          
    print(rez);        
#endregion

#region Zadatak 8
def izmeni(lista):
    rez = []
    noviEl = 0;
    for x in range(len(lista)):
        print("Za el broj => ", x);
        for y in range(0, x + 1, 1):
            print("Ima: ", lista[y]);
            noviEl += lista[y];
        rez.append(noviEl);
        noviEl = 0;
    print(rez);     
#endregion

#region Zadatak 9
def prosek(megaLista):
    rez = [];
    sumaEl = 0;
    for lista in megaLista:
        print(lista);
        for el in lista:
            sumaEl += el
        rez.append(sumaEl / len(lista));
        sumaEl = 0;
    print(rez);
#endregion

#region Zadatak 10
def izbroj_rek(lista, n):
    for el in lista:
        if type(el).__name__ == list.__name__:
            n=n+izbroj_rek(el, 0);
        else: 
            n=n+1
    return n;

def izbroj(lista):
    return izbroj_rek(lista, 0);
#endregion

#region Zadatak 11
def razlika(lista):
    rez = [];
    for x in range(0, len(lista) - 1, 1):
         rez.append(lista[x] - lista[x + 1]);
    print(rez);

#endregion

#region Zadatak 12
def presek(lista1, lista2):
    rez = [];
    for x in lista1:
        for y in lista2:
            if int(x) == int(y) and x not in rez:
                rez.append(x);
                if y != x and y not in rez:
                    rez.append(y)
    print(rez);
#endregion

#region Zadatak 13
def izmeni(lista):
    dict = {};
    for x in range(len(lista)):
        if x % 2 == 0:
            lista[x] += 1;
            if dict.keys().__contains__('pp'):
                dict['pp'].append(lista[x]);
            else:
                dict['pp']=[lista[x]];
            
        else:
            lista[x] -= 1;
            if dict.keys().__contains__('np'):
                dict['np'].append(lista[x]);
            else:
                dict['np']=[lista[x]];
    print(dict)
#endregion

#region Zadatak 14
def unija(lista1, lista2):
    rez = [];
    for x in lista1:
        rez.append(x);
    for y in lista2:
        if y not in rez:
            rez.append(y);
    print(rez);


#endregion

#region Zadatak 15
def izdvoji(*liste):
    rez = [];
    for x in range(len(liste)):
        print("lista br: ", x);
        print("el: ", liste[x]);
        print("velicina: ", len(liste[x]));
        if x < len(liste[x]):
            rez.append(liste[x][x]);
        else:
            rez.append(0);
        print();
    print(rez);
#endregion

#region Zadatak 16
def brojanje(d):
    brojac = {}
    for x in d.values():
        tip = type(x).__name__
        if tip not in brojac:
            brojac[tip] = 0
        brojac[tip] += 1
    rez = list(brojac.items())
    print(rez)
    return rez
#endregion

#region Zadatak 17
def kreiraj(n):
    rez = [];
    sum = 0;
    for x in range(n+1):
        print(x);
        sum+=x;
        rez.append((x, sum ** 2));
    print(rez);
        

#endregion

#region Zadatak 18
def kreiraj(megaLista):
    rez = [];
    for x in range(len(megaLista) - 1):
        podlista = [];
        for el in megaLista[x]:
            if el not in megaLista[x+1]:
                print("Element ", el, "nije u susednoj listi");
                podlista.append(el);
        rez.append(podlista);
        print("++++++++++")
    print(rez);
#endregion

#region Zadatak 19
def stepenuj(lista):
    rez = [];
    step = 1;
    for toup in lista:
        step = toup[0];
        print(step);
        for x in range(1 ,len(toup), 1):
            step = step ** toup[x];
            print(step);
        rez.append(step);
    print(rez);
#endregion

#region Zadatak 20

# Napomena: int("Broj u bazi N", N) može da se koristi za prevođenje iz baze N u bazu 10.
def boje(hex_boja):
    hex_boja = hex_boja.lstrip("#")
    rez = {
        "Red": int(hex_boja[0:2], 16),
        "Green": int(hex_boja[2:4], 16),
        "Blue": int(hex_boja[4:6], 16)
    }
    print(rez.items());
#endregion

def main():
    # parni([2,3,5,1,6, 0]);
    # numlista(["Prvi", "Drugi", 2, 4, [3, 5]]);
    # uredi([1, 2, 3, 4, 5], 3, 1)
    # zbir([1, 2, 3, 4, 5]);
    # brojel([1, 2], [3, 4, 5], 'el', ['1', 1]);
    # razlika([1, 4, 6, "2", "6", "look"], ["look",4, 5, "2"]);
    # izmeni([1, 2, 4, 7, 9]);
    # prosek([[1, 4, 6, 2], [4, 6, 2, 7], [3, 5], [5, 6, 2, 7]]);
    # print(izbroj([1, [1, 3, [2, 4, 5, [5, 5], 4]], [2, 4], 4, 6])); 
    # razlika([8, 5, 3, 1, 1])
    # presek([5, 4, "1", "8", 3, 7], [1, 9, "1"])
    # izmeni([8, 6, 3, 1, 1])
    # unija([5, 4, "1", "8", 7], [1, 9, "1"])
    # izdvoji([5, 4, 4], [1, 9, 1], [5, 6], [4, 6, 10, 12])
    # brojanje({1 : 4, 2 : [2, 3], 3 : [5, 6], 4 : 'test', 5 : 9, 6 : 8});
    # kreiraj(4);
    # kreiraj([[1, 2, 3], [2, 4, 5], [4, 5, 6, 7], [1, 5]])
    # stepenuj([(1, 4, 2), (2, 5, 1), (2, 2, 2, 2), (5, )]);
    boje("#FA1AA0");
if __name__ == "__main__":
    main();