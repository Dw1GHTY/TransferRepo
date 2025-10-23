import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.HashMap;

public class Kviz extends UnicastRemoteObject implements IKviz {
    public int brojPoena;
    public int trenutnoPitanje;
    public HashMap<Integer, Pitanje> pitanja;
    public HashMap<Pitanje, String> odgovori; 

    public Kviz() throws RemoteException {
        pitanja = new HashMap<Integer, Pitanje>();
        odgovori = new HashMap<Pitanje, String>();

        Pitanje p1 = new Pitanje("1+1", "1", "2", "3");
        String o1 = "b";
        Pitanje p2 = new Pitanje("2 * 5", "8", "3", "10");
        String o2 = "c";
        Pitanje p3 = new Pitanje("2-1", "0", "1", "-10");
        String o3 = "b";

        //? inicijalizacija pitanja
        pitanja.put(1, p1);
        pitanja.put(2, p2);
        pitanja.put(3, p3);

        //? inicijalizacija odgovora
        odgovori.put(p1, o1);
        odgovori.put(p2, o2);
        odgovori.put(p3, o3);
    }


    public void pocetak() throws RemoteException{
        this.brojPoena = 0;
        this.trenutnoPitanje = 1;
    }
    public Pitanje vratiPitanje() throws RemoteException{
        return pitanja.get(trenutnoPitanje);
    }
    public void odgovori(String odg) throws RemoteException{
        Pitanje p = vratiPitanje();
        if(odg.equals(odgovori.get(p)))
            this.brojPoena++;
        //?prelazi na sledece pitanje
        this.trenutnoPitanje++;
    }
    public int vratiBrojPoena() throws RemoteException{
        return this.brojPoena;
    }


}
