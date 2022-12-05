package epicture.dashboard.model;

public class Photo {
    private String id;
    private String title;
    private String views;
    private String upvote;
    private String downvote;

    public void setViews(String views) {
        this.views = views;
    }
    public String getUpvote() {return upvote;}
    public void setUpvote(String upvote) {this.upvote = upvote;}
    public String getDownvote() {return downvote;}
    public void setDownvote(String downvote) {this.downvote = downvote;}
    public String getId() {
        return id;
    }
    public void setId(String id) {
        this.id = id;
    }
    public String getTitle() {
        return title;
    }
    public void setTitle(String title) {
        this.title = title;
    }
    public String getViews() {
        return views;
    }
}
