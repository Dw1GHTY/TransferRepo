import java.rmi.RemoteException;
import java.rmi.Remote;

interface IBroker extends Remote {
    public void publish(Message topicMessage, String topicTitle) throws RemoteException;

    public void subscribe(String wantedTopic) throws RemoteException;

}