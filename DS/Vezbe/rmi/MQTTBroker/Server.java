
import java.net.MalformedURLException;
import java.rmi.Naming;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;

public class Server {

    private IBroker broker;

    public Server() throws RemoteException, MalformedURLException {
        try {
            LocateRegistry.createRegistry(1099);
            Naming.rebind("rmi://localhost:1099/broker", broker);

            System.out.println("Server listening on port: 1099");
        } catch (Exception e) {
            throw new RemoteException(e.getMessage());
        }
    }

    public static void main(String[] args) throws RemoteException {
        try {
            new Server();

        } catch (Exception e) {
            throw new RemoteException(e.getMessage());
        }
    }
}
