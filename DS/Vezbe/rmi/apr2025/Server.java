
import java.rmi.Naming;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;

public class Server {

    private ITempManager managerClient;

    public Server() throws RemoteException {
        try {

            LocateRegistry.createRegistry(1099);
            this.managerClient = new TempManager(22, 0.3);
            Naming.rebind("rmi://localhost:1099/tempManager", managerClient);

            System.out.println("Server is listening on port: 1099");

        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    public static void main(String[] args) throws RemoteException {
        try {
            new Server();
        } catch (Exception e) {

        }
    }

}
