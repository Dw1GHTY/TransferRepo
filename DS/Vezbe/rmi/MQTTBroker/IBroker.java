
import java.rmi.Remote;
import java.rmi.RemoteException;

interface IBroker extends Remote {

    public void publish(Message topicMessage, String topicTitle) throws RemoteException;

    public void subscribe(String wantedTopic, ICallback clientCb) throws RemoteException;

}
