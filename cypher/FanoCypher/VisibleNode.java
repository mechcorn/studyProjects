/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package FanoCypher;

import java.awt.Point;

/**
 *
 * @author aleole
 */
public class VisibleNode {
    private String message = null;//сообщение в узле дерева
    private final Point point = new Point();//координаты узла дерева
    public Point leftLink;//координаты левого потомка (при наличии) для показывания связи
    public Point rightLink;//координаты правого потомка (при наличии) для показывания связи
    public int id;
    public String getVisibleNodeMessage(){
        return message;
    }
    
    public void setVisibleNodeMessage(String message){
        this.message = message;
    }
    
    public int getX(){
        return point.x;
    }
    
    public int getY(){
        return point.y;
    }
    
    public void setX(int x){
        this.point.x = x;
    }
    
    public void setY(int y){
        this.point.y = y;
    }
}
