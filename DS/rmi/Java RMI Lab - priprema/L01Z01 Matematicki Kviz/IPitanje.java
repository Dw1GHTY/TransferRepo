import java.rmi.Remote;
import java.rmi.RemoteException;

public interface IPitanje extends Remote {
    public String vratiTekst() throws RemoteException;
}
