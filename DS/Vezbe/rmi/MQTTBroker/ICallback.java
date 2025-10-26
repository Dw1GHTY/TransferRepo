import java.rmi.RemoteException;
import java.rmi.Remote;

public interface ICallback extends Remote {
    public void subscribeClient();
}
