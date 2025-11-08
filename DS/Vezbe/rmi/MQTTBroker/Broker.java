
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Broker extends UnicastRemoteObject implements IBroker {

    private Map<String, List<Message>> topics;
    private Map<String, List<ICallback>> subscribedToTopic;

    public Broker() throws RemoteException {
        try {
            this.topics = new HashMap< String, List<Message>>();
            this.subscribedToTopic = new HashMap<String, List<ICallback>>();

        } catch (Exception e) {
            throw new RemoteException(e.getMessage());
        }
    }

    public void publish(Message topicMessage, String topicTitle) throws RemoteException {

        try {
            //! add 
            List<Message> topic = this.topics.get(topicTitle);
            if (topic == null) {
                createTopic(topicTitle);
            }
            topic.add(topicMessage);

            //! notify subscribed clients with callback
            List<ICallback> clientsToNotify = subscribedToTopic.get(topicMessage.getTitle());
            for (ICallback cb : clientsToNotify) {
                cb.notifySubscribers(topicMessage);
            }

        } catch (Exception e) {
            throw new RemoteException(e.getMessage());
        }

    }

    public void subscribe(String wantedTopic, ICallback clientCb) throws RemoteException {
        try {
            this.subscribedToTopic.get(wantedTopic).add(clientCb);
        } catch (Exception e) {
            throw new RemoteException(e.getMessage());
        }
    }

    public void createTopic(String topicTitle) {
        this.topics.put(topicTitle, null);
    }
}
