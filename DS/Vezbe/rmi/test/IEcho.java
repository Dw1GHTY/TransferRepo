
import java.rmi.Remote;
import java.rmi.RemoteException;

interface IEcho extends Remote {

    public String getEcho(String echo) throws RemoteException;

}
