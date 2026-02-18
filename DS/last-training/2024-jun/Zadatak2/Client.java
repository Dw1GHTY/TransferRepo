
import java.rmi.Naming;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.Scanner;

public class Client {

    public IBroker broker;
    public ICallback cb;

    public Client() throws RemoteException {
        try {
            System.out.println("========== Welcome ========== ");

            IBroker broker = (IBroker) Naming.lookup("rmi://localhost:1099/broker");
            cb = new Callback();

            Scanner sc = new Scanner(System.in);
            String input = "";

            while (!input.equals("x")) {
                System.out.println("\nOptions:\n[p] publish\n[s] subscribe\n[x] quit");
                System.out.print("> ");
                input = sc.nextLine();

                switch (input) {
                    case "p":
                        System.out.print("Enter topic name: ");
                        String pTopic = sc.nextLine();
                        System.out.print("Enter message content: ");
                        String content = sc.nextLine();

                        Message msg = new Message(pTopic, content);
                        broker.publish(pTopic, msg);
                        System.out.println("Message published!");
                        break;

                    case "s":
                        System.out.print("Enter topic to subscribe: ");
                        String sTopic = sc.nextLine();
                        broker.subscribe(cb, sTopic);
                        System.out.println("Subscribed to " + sTopic);
                        break;

                    case "x":
                        System.out.println("Exiting...");
                        break;

                    default:
                        System.out.println("Invalid option. Try again.");
                        break;
                }
            }

        } catch (Exception e) {
            System.err.println("Client Error: " + e.getMessage());
            e.printStackTrace();
        }
    }

    public static void main(String args[]) throws RemoteException {

        try {
            new Client();
        } catch (Exception e) {
            System.out.println(e);
        }

    }

    public class Callback extends UnicastRemoteObject implements ICallback {

        public Callback() throws RemoteException {
            try {

            } catch (Exception e) {
                System.out.println(e);
            }
        }

        public void notifyUser(Message msg) throws RemoteException {
            try {
                System.out.println("New message received:");
                System.out.println("Title: " + msg.getTitle());
                System.out.println("Message: " + msg.getContent());
            } catch (Exception e) {
                System.out.println(e);
            }
        }
    }
}
