
import java.rmi.Naming;
import java.rmi.RemoteException;
import java.util.Scanner;

public class Client {

    private IBroker broker;
    private ICallback callback;

    public Client() throws RemoteException {
        try {
            this.broker = (IBroker) Naming.lookup("rmi://localhost:1099/broker");
            this.callback = new Callback();
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    public static void main(String[] args) throws RemoteException {
        try {
            Client app = new Client();
            app.runMenu();

        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    private void runMenu() {
        Scanner sc = new Scanner(System.in);

        while (true) {
            System.out.println("\n=== Broker Client Menu ===");
            System.out.println("1. Subscribe to a topic");
            System.out.println("2. Publish message to a topic");
            System.out.println("3. Exit");
            System.out.print("Choose option: ");

            String option = sc.nextLine();

            try {
                switch (option) {
                    case "1":
                        System.out.print("Enter topic to subscribe to: ");
                        String topicToSub = sc.nextLine();
                        broker.subscribe(topicToSub, callback);
                        System.out.println("Subscribed to topic '" + topicToSub + "'.");
                        break;

                    case "2":
                        System.out.print("Enter topic to publish to (will be created if it doesn't exist): ");
                        String topicToPub = sc.nextLine();
                        System.out.print("Enter message title: ");
                        String title = sc.nextLine();
                        System.out.print("Enter message text: ");
                        String text = sc.nextLine();
                        broker.publish(topicToPub, new Message(title, text));
                        System.out.println("Message published to topic '" + topicToPub + "'.");
                        break;

                    case "3":
                        System.out.println("Exiting...");
                        sc.close();
                        System.exit(0);
                        break;

                    default:
                        System.out.println("Invalid option! Please choose 1–3.");
                        break;
                }
            } catch (Exception e) {
                System.out.println("Error: " + e.getMessage());
            }
        }
    }

    // Inner callback class to handle notifications
    private class Callback extends java.rmi.server.UnicastRemoteObject implements ICallback {

        protected Callback() throws RemoteException {
            super();
        }

        @Override
        public void notifyUser(String topic, Message message) throws RemoteException {
            System.out.println("\n--- New message in topic: " + topic + " ---");
            System.out.println("Title: " + message.getTitle());
            System.out.println("Text: " + message.getText());
            System.out.println("-------------------------------------------");
        }
    }

}
