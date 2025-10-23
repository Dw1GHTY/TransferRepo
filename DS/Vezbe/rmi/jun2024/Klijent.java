import java.rmi.Naming;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.ArrayList;
import java.util.List;

public class Klijent {
    
    public IBroker b;
    public List<String> subscribedTopics;
    public ICallback callback;

    public Klijent(){
        try {
            b = (IBroker)Naming.lookup("rmi://localhost:1099/service");
            subscribedTopics = new ArrayList<String>();
            callback = new Callback();

            System.out.println("Welcome to chat forums");
            String unos = new String();
            String topic = new String();
            String message = new String();

            while(!unos.equals("x")){
                System.out.println("****************************\n");
                System.out.println("Enter the name of topic to subscribe -> s\n");
                System.out.println("Publish a message to a topic -> p\n");
                System.out.println("Exit -> x");
                unos = System.console().readLine();

                switch (unos) {
                    case "s":
                        System.out.println("Enter topic name: ");
                        topic = System.console().readLine();
                        b.subscribe(topic, callback);
                        break;
                    case "p":
                        System.out.println("Desired topic: ");
                        topic = System.console().readLine();
                        System.out.println("Desired message: ");
                        message = System.console().readLine();
                        Message msg = new Message(topic, message);
                        b.publish(msg);
                        callback.sendMessageToClient();
                    case "x":
                        break;
                    default:
                        break;
                }

                System.out.println("****************************\n");

            }


            
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }

    }

    public static void main(String[] args) {
        new Klijent();

        System.console().readLine();
    }

    //SLEDECE JE CALLBACK I SUBSCRIBE METODA
    public class Callback extends UnicastRemoteObject implements ICallback {

        public Callback() throws RemoteException {}

        
        //register
        public synchronized void sendMessageToClient() throws RemoteException {
            List<String> topics =  b.getTopics();
            for (String topic : topics) {
                if(subscribedTopics.contains(topic)){
                    List<String> messagesInTopic = new ArrayList<String>();
                    messagesInTopic = b.getMessagesInTopic(topic);
                    for (String m : messagesInTopic) {
                        System.out.println(m);
                    }
                }
            }
        }

    }

}
