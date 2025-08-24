import java.rmi.Remote;
import java.rmi.RemoteException;
import java.util.List;
public interface IBroker extends Remote{

    public void publish(Message poruka) throws RemoteException;
    
    //subscribe -> zahteva callback
    public void subscribe(String desiredTopic, ICallback cb) throws RemoteException;

    public void createTopic(String topicName) throws RemoteException;

    public List<String> getTopics() throws RemoteException;
    public List<String> getMessagesInTopic(String topic) throws RemoteException;
}