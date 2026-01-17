import java.rmi.Naming;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.Scanner;

public class Client {

    private IBroker broker;
    private Callback clientCb;

    public Client() throws RemoteException {
        try {
            this.clientCb = new Callback();
            // PAŽNJA: Ovde mora da se gadja isto ime kao u Server.java (/broker)
            this.broker = (IBroker) Naming.lookup("rmi://localhost:1099/broker");
        } catch (Exception e) {
            System.out.println("Greska pri povezivanju sa serverom: " + e);
        }
    }

    // --- Pomoćne metode za pozivanje iz konzole ---
    public void sub(String topic) {
        try {
            broker.subscribe(clientCb, topic);
            System.out.println(">> Pretplacen na topic: " + topic);
        } catch (RemoteException e) {
            System.out.println("Greska pri subscribe: " + e);
        }
    }

    public void pub(String topic, String title, String content) {
        try {
            Message msg = new Message(title, content);
            broker.publish(topic, msg);
            System.out.println(">> Poruka poslata!");
        } catch (RemoteException e) {
            System.out.println("Greska pri publish: " + e);
        }
    }
    // ----------------------------------------------

    // Tvoja Callback klasa (sada ispravna sa UnicastRemoteObject)
    public class Callback extends UnicastRemoteObject implements ICallback {
        public Callback() throws RemoteException {
            super();
        }

        public void notifySubscriber(Message message) throws RemoteException {
            try {
                System.out.println("\n!!! STIGLA PORUKA !!!");
                System.out.println("Naslov: " + message.getTitle());
                System.out.println("Sadrzaj: " + message.getContent());
                System.out.println("----------------------\n");
            } catch (Exception e) {
                System.out.println(e);
            }
        }
    }

    // MAIN METODA - Konzolni interfejs
    public static void main(String[] args) {
        try {
            Client client = new Client();
            Scanner scanner = new Scanner(System.in);

            System.out.println("Klijent pokrenut. Izaberite opciju:");

            while (true) {
                System.out.println("1. Subscribe na topic");
                System.out.println("2. Publish poruku");
                System.out.println("3. Izlaz");
                System.out.print("Unos: ");

                String opcija = scanner.nextLine();

                if (opcija.equals("1")) {
                    System.out.print("Unesi ime topica: ");
                    String topic = scanner.nextLine();
                    client.sub(topic);

                } else if (opcija.equals("2")) {
                    System.out.print("Unesi ime topica: ");
                    String topic = scanner.nextLine();
                    System.out.print("Naslov poruke: ");
                    String title = scanner.nextLine();
                    System.out.print("Sadrzaj poruke: ");
                    String content = scanner.nextLine();

                    client.pub(topic, title, content);

                } else if (opcija.equals("3")) {
                    System.out.println("Gasenje...");
                    System.exit(0);
                }
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}