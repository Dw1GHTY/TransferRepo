
import java.rmi.Naming;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;

public class Server {

    public Broker broker;

    public Server() throws RemoteException {
        try {
            broker = new Broker();
            LocateRegistry.createRegistry(1099);
            Naming.rebind("rmi://localhost:1099/broker", broker);
            System.out.println("Server is listening on port: 1099");
        } catch (Exception e) {
            System.out.println(e);
        }
    }

    public static void main(String args[]) throws RemoteException {
        try {
            new Server();
        } catch (Exception e) {
            System.out.println(e);
        }
    }

}
