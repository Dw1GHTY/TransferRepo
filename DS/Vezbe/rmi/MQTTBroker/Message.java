
import java.io.Serializable;

public class Message implements Serializable {

    private String title;
    private String text;

    public Message(String title, String text) {
        this.title = title;
        this.text = text;
    }

    public String getTitle() {
        return this.title;
    }

    public String getText() {
        return this.text;
    }
}
