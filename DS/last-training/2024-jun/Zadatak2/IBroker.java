
import java.rmi.Remote;
import java.rmi.RemoteException;

public interface IBroker extends Remote {

    public void subscribe(ICallback cb, String topicName) throws RemoteException;

    public void publish(String wantedTopic, Message msg) throws RemoteException;
}
