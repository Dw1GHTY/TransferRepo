import java.rmi.RemoteException;

public interface IStanje {
    public int vratiMinute() throws RemoteException;
    public int vratiPoruke() throws RemoteException;
    public int vratiInternet() throws RemoteException;
    public float vratiRacun() throws RemoteException;
}
