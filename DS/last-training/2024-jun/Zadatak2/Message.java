
import java.io.Serializable;

public class Message implements Serializable {

    private String title;
    private String content;

    public Message(String t, String c) {
        this.content = c;
        this.title = t;
    }

    public String getContent() {
        return content;
    }

    public String getTitle() {
        return title;
    }

    public void setContent(String content) {
        this.content = content;
    }

    public void setTitle(String title) {
        this.title = title;
    }

}
