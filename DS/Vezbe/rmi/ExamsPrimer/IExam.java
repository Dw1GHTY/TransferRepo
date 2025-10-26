import java.rmi.Remote;
import java.rmi.RemoteException;

public interface IExam extends Remote{

    public void prijaviIspit(Student s) throws RemoteException;
    public int brojPrijavljenih(int idIspita) throws RemoteException;     
}