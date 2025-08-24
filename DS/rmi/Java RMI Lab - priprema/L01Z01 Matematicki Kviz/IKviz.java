import java.rmi.Remote;
import java.rmi.RemoteException;

public interface IKviz extends Remote {
    public void pocetak() throws RemoteException;
    public Pitanje vratiPitanje() throws RemoteException;
    public void odgovori(String odg) throws RemoteException;
    public int vratiBrojPoena() throws RemoteException;    
}
