import java.lang.reflect.Array;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Broker extends UnicastRemoteObject implements IBroker {

    private Map<String, List<Message>> topics;
    private Map<String, List<ICallback>> subscribers;

    public Broker() throws RemoteException {
        super();
        try {
            this.topics = new HashMap<String, List<Message>>();
            this.subscribers = new HashMap<String, List<ICallback>>();
        } catch (Exception e) {
            System.out.println(e);
        }
    }

    public void createTopic(String newTopic) {
        this.topics.put(newTopic, new ArrayList<Message>());
        this.subscribers.put(newTopic, new ArrayList<ICallback>());
    }

    public void subscribe(ICallback clientCb, String topic) throws RemoteException {
        try {
            this.subscribers.get(topic).add(clientCb);
        } catch (Exception e) {
            System.out.println(e);
        }
    }

    public void publish(String topic, Message message) throws RemoteException {
        try {
            Boolean topicExists = this.topics.containsKey(topic);

            if (topicExists) {
                this.topics.get(topic).add(message);
            } else {
                createTopic(topic);
                this.topics.get(topic).add(message);
            }
            // ? i sada notify sve klijente
            for (ICallback clientCb : this.subscribers.get(topic)) {
                clientCb.notifySubscriber(message);
            }
        } catch (Exception e) {
            System.out.println(e);
        }
    }
}
