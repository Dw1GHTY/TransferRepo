import java.rmi.Remote;
import java.rmi.RemoteException;

public interface IFacultyManager extends Remote {
    public Exam findIspit(int brojIndeksa) throws RemoteException;
}
