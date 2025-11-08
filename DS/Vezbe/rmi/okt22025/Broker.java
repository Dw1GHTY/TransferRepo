
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Broker extends UnicastRemoteObject implements IBroker {

    private Map<String, List<Message>> forum;
    private Map<String, List<ICallback>> subscribersToNotify;

    public Broker() throws RemoteException {
        this.forum = new HashMap<>();
        this.subscribersToNotify = new HashMap<>();
    }

    @Override
    public synchronized void subscribe(String topicTitle, ICallback callback) throws RemoteException {
        try {
            // Automatically create topic if it doesn't exist
            if (!this.forum.containsKey(topicTitle)) {
                createTopic(topicTitle);
                System.out.println("Topic '" + topicTitle + "' did not exist. Created automatically on subscribe.");
            }

            this.subscribersToNotify.get(topicTitle).add(callback);
            System.out.println("New subscriber added for topic: " + topicTitle);

        } catch (Exception e) {
            System.out.println("Error in subscribe(): " + e.getMessage());
        }
    }

    @Override
    public synchronized void publish(String topic, Message message) throws RemoteException {
        try {
            if (!this.forum.containsKey(topic)) {
                createTopic(topic);
                System.out.println("Topic '" + topic + "' did not exist. Created automatically on publish.");
            }

            this.forum.get(topic).add(message);

            for (ICallback cb : this.subscribersToNotify.get(topic)) {
                try {
                    cb.notifyUser(topic, message);
                } catch (RemoteException re) {
                    System.out.println("Failed to notify one subscriber: " + re.getMessage());
                }
            }

        } catch (Exception e) {
            System.out.println("Error in publish(): " + e.getMessage());
        }
    }

    private void createTopic(String newTopic) {
        this.forum.put(newTopic, new ArrayList<>());
        this.subscribersToNotify.put(newTopic, new ArrayList<>());
    }
}
