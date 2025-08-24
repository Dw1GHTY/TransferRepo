import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

//! UnicastRemoteObject jer ce da se menja kroz koriscenje aplikacije
public class Korisnik extends UnicastRemoteObject implements IKorisnik {
    
    public String broj;
    public int minuti;
    public int poruke;
    public int internet;
    public int minutiTarifa;    //!  tarifu dinara po minuti
    public int porukeTarifa;    //!  tarifu dinara po poruci
    public int internetTarifa;  //! tarifu dinara po megabajtu interneta 
    
    public Korisnik(
        String broj, int min, int por, int internet, int minT, int porT, int internetT
    ) throws RemoteException {
        this.broj = broj;
        this.minuti = min;
        this.poruke = por;
        this.internet = internet;
        this.minutiTarifa = minT;
        this.porukeTarifa = porT;
        this.internetTarifa = internetT;    
    }
    
    public void uplatiMinute(int minuti) throws RemoteException {

    }
    public void uplatiPoruke(int poruke) throws RemoteException {

    }
    public void uplatiInternet(int internet) throws RemoteException {

    }
    public Stanje vratiStanje() throws RemoteException {

    }
}
