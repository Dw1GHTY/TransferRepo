
import java.rmi.Remote;
import java.rmi.RemoteException;

public interface ITempManager extends Remote {

    public void execTempAdjustment(double sensorTemperature) throws RemoteException;

    public void sendMessage(Message message) throws RemoteException;
}
