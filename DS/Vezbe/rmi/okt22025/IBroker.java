
import java.rmi.Remote;
import java.rmi.RemoteException;

public interface IBroker extends Remote {

    public void subscribe(String topicTitle, ICallback callback) throws RemoteException;

    public void publish(String topic, Message message) throws RemoteException;

}
