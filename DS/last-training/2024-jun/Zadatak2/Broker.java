
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Broker extends UnicastRemoteObject implements IBroker {

    public Map<String, Message> messages;
    public Map<String, List<ICallback>> subscribers;

    public Broker() throws RemoteException {

        this.messages = new HashMap<>();
        this.subscribers = new HashMap<>();
    }

    public void subscribe(ICallback cb, String topicName) throws RemoteException {
        try {
            if (subscribers.containsKey(topicName)) {
                this.subscribers.computeIfAbsent(topicName, k -> new ArrayList<>()).add(cb);
            }
        } catch (Exception e) {
            System.out.println(e);
        }

    }

    public void publish(String wantedTopic, Message msg) throws RemoteException {
        try {
            this.messages.put(wantedTopic, msg);
            List<ICallback> subs = this.subscribers.get(wantedTopic);

            if (subs != null) {
                for (ICallback cb : subs) {
                    cb.notifyUser(msg);
                }
            } else {
                System.out.println("No subscribers for topic: " + wantedTopic);
            }
        } catch (Exception e) {
            System.out.println("Publish error: " + e);
        }
    }

    public void createTopic(String topicName) throws RemoteException {
        try {
            this.messages.put(topicName, null);
        } catch (Exception e) {
            System.out.println(e);
        }
    }
}
