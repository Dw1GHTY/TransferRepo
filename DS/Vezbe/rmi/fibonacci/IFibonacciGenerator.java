
import java.rmi.Remote;
import java.rmi.RemoteException;

public interface IFibonacciGenerator extends Remote {

    public void generateFibonacciForNumber(int number, ICallback cb) throws RemoteException;
}
