
import java.rmi.Remote;
import java.rmi.RemoteException;

public interface ICallback extends Remote {

    public void printGeneratedNumber(int number) throws RemoteException;

}
