
import java.net.MalformedURLException;
import java.rmi.Naming;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.Scanner;

public class Client {

    private IBroker broker;
    private ICallback client;

    public Client() throws RemoteException, MalformedURLException {
        try {
            this.broker = (IBroker) Naming.lookup("rmi://localhost:1099/broker");

        } catch (Exception e) {
            throw new RemoteException(e.getMessage());
        }
    }

    public static void main(String[] args) {
        try {
            new Client();

            Scanner scanner = new Scanner(System.in);
        } catch (Exception e) {
            // TODO: handle exception
        }
    }

    class Callback extends UnicastRemoteObject implements ICallback {

        public Callback() throws RemoteException {
        }

        public void subscribeToTopic(String wantedTopic) throws RemoteException {
            try {
                broker.subscribe(wantedTopic, client);
            } catch (Exception e) {
                throw new RemoteException(e.getMessage());
            }
        }

        public void notifySubscribers(Message message) throws RemoteException {
            try {
                System.out.println("New message in topic " + message.getTitle() + ": " + message.getText());
            } catch (Exception e) {
                throw new RemoteException(e.getMessage());
            }

        }
    }

}
