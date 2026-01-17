import java.rmi.Naming;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;

class Server {

    IBroker broker;

    public Server() throws RemoteException {
        try {
            this.broker = new Broker();
            LocateRegistry.createRegistry(1099);
            Naming.rebind("rmi://localhost:1099/broker", broker);
            System.out.println("Server is listening on port 1099");
        } catch (Exception e) {
            System.out.println(e);
        }
    }

    public static void main(String[] args) {
        try {
            new Server();
        } catch (Exception e) {
            System.out.println(e);
        }
    }

}