import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

public class Stanje extends UnicastRemoteObject implements IStanje {
    
    public String broj;
    public int minuti;
    public int poruke;
    public int internet;
    public float racun;

    public Stanje(String broj, int minuti, int poruke, int internet, float racun) throws RemoteException {
        this.broj = broj;
        this.minuti = minuti;
        this.poruke = poruke;
        this.internet = internet;
        this.racun = racun;
    }


    public int vratiMinute() throws RemoteException {
        return this.minuti;
    }
    public int vratiPoruke() throws RemoteException {
        return this.poruke;
    }
    public int vratiInternet() throws RemoteException {
        return this.internet;
    }
    public float vratiRacun() throws RemoteException {
        return this.racun;
    }

}
