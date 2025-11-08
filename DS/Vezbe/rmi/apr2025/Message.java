
import java.io.Serializable;

public class Message implements Serializable {

    private String action;

    public Message(String action) {
        this.action = action;
    }

    public String getAction() {
        return action;
    }

    public void setAction(String action) {
        this.action = action;
    }

}
