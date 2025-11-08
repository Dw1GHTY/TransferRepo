
import java.rmi.Remote;
import java.rmi.RemoteException;

public interface ICallback extends Remote {

    public void subscribeToTopic(String wantedTopic) throws RemoteException;

    public void notifySubscribers(Message message) throws RemoteException;
}
