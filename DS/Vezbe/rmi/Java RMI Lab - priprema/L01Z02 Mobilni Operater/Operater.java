import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.HashMap;

public class Operater extends UnicastRemoteObject implements IOperater {
    
    public HashMap<String, Korisnik> imenik;    

    public Operater() throws RemoteException {

    }
    
    public Korisnik vratiKorisnika(String broj) throws RemoteException{
        return imenik.get(broj);
    }
}
