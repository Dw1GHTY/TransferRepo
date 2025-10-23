import java.rmi.RemoteException;

public interface IOperater {
    public Korisnik vratiKorisnika(String broj) throws RemoteException;
}
