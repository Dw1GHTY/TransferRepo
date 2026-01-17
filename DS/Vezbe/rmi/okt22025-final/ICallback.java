import java.rmi.Remote;
import java.rmi.RemoteException;

public interface ICallback extends Remote {
    public void notifySubscriber(Message message) throws RemoteException;
}