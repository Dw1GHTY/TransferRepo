import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

public class Broker extends UnicastRemoteObject implements IBroker {
    
    public HashMap<String, List<String>> forum;
    public HashMap<String, List<ICallback>> subscribedUsers;

    public Broker() throws RemoteException{
        forum = new HashMap<String, List<String>>();
        subscribedUsers = new HashMap<String, List<ICallback>>();
    }




    
    public void subscribe(String desiredTopic, ICallback cb) throws RemoteException {
        if(subscribedUsers.containsKey(desiredTopic)){
            //subscribe-uje klijenta u zeljeni topic ako takav postoji
            subscribedUsers.put(desiredTopic, null);
            subscribedUsers.get(desiredTopic).add(cb);
        } else{
            System.out.println("Topic ne postoji");
        }
    }

    public void publish(Message poruka) throws RemoteException {
        //ako postoji topic koji odgovara naslovu poruke, dodaje sadrzaj u listu za taj topic
        if(forum.containsKey(poruka.getNaslov())){
            forum.get(poruka.getNaslov()).add(poruka.getSadrzaj());
        } else {
        //u suprotnom pravi topic i dodaje tu poruku u forum i u listu topica za callback
            createTopic(poruka.getNaslov());
            forum.get(poruka.getNaslov()).add(poruka.getSadrzaj());
            subscribedUsers.keySet().add(poruka.getNaslov());
        }   
    }
    public void createTopic(String topicName) throws RemoteException {
        forum.put(topicName, null);
    }

    public ArrayList<String> getTopics() throws RemoteException {
        ArrayList<String> listOfTopics = new ArrayList<String>();
        for (String topic : forum.keySet()) {
            listOfTopics.add(topic);
        }
        return listOfTopics;
    }
    public List<String> getMessagesInTopic(String topic) throws RemoteException {
        return forum.get(topic);
    }
}
