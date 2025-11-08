
import java.rmi.Remote;
import java.rmi.RemoteException;

public interface ICallback extends Remote {

    public void notifyUser(String topic, Message message) throws RemoteException;

}
