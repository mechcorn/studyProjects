package GuiJdbcPddDb4;

/**
 *
 * @author aleole
 */
public class Answer {
    private String content;
    private boolean isRight;
    
    public Answer(String outerContent, boolean outerIsRight){
        content = outerContent;
        isRight = outerIsRight;
    }
    
    public String getContent(){
        return content;
    }
    
    public boolean isRight(){
        return isRight;
    }
    
    public void setRight(){
        isRight = true;
    }
}
