import java.net.MalformedURLException;
import java.rmi.Naming;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;

public class Server {

    IFacultyManager facultyManager;

    public Server() throws RemoteException, MalformedURLException {
        try {
            this.facultyManager = new FacultyManager();
            LocateRegistry.createRegistry(1099);
            Naming.rebind("rmi://localhost:1099/facultyManager", facultyManager);
            System.out.println("Server lsitening at port: 1099");
        } catch (Exception e) {
            throw new RemoteException(e.getMessage(), e);
        }
    }

    public static void main(String[] args) {
        try {
            Server server = new Server();
        } catch (RemoteException | MalformedURLException e) {
            System.err.println("Server failed to start: " + e.getMessage());
            e.printStackTrace();
        }
    }

}
