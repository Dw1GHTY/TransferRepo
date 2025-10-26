import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

public class Broker extends UnicastRemoteObject implements IBroker {
    private Map<String, List<Message>> topics; // topics koji sadrze messages

    public Broker() throws RemoteException {
        this.topics = new HashMap<String, List<Message>>();
    }

    public void publish(Message topicMessage, String topicTitle,) throws RemoteException {
        // ! provera da li postoji topic sa message.title
        List<Message> topic = this.topics.get(topicTitle);
        if (topic == null) {
            createTopic(topicTitle);
        }
        topic.add(topicMessage);

    }

    public void createTopic(String topicTitle) {
        this.topics.put(topicTitle, null);
    }
}
