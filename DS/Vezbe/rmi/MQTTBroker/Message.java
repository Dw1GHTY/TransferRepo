import java.io.Serializable;

public class Message implements Serializable {
    private string title;
    private string text;

    public Message(String title, String text) {
        this.title = title;
        this.text = text;
    }

    public string getTitle() {
        return this.title;
    }

    public string getText() {
        return this.text;
    }
}
