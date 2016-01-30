/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package FanoCypher;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Point;
import java.util.ArrayList;
import javax.swing.JPanel;

/**
 *
 * @author aleole
 */
public class DrawPanel extends JPanel{
    
    private ArrayList<VisibleNode> visibleNodes = null;
    private int maxLevel = 0;

    public void setVisibleNodes(ArrayList<VisibleNode> nodes){
        visibleNodes = nodes;
    }
    
    public int getMaxLevel(){
        return maxLevel;
    }
    
    public void setMaxLevel(int level){
        maxLevel = level;
    }
    
    @Override
    public void paintComponent(Graphics g){
        super.paintComponent(g);
        
        int width = this.getSize().width / (maxLevel + 1);
        width /= 5;
        
        if(visibleNodes != null){
                for(VisibleNode node : visibleNodes){
                    g.setColor(Color.YELLOW);
                    if(node.leftLink != null){
                        g.drawLine(
                                node.getX() + width / 2,
                                node.getY() + width / 2,
                                node.leftLink.x + width / 2,
                                node.leftLink.y + width / 2);
                    }
                    if(node.rightLink != null){
                        g.drawLine(
                                node.getX() + width / 2,
                                node.getY() + width / 2,
                                node.rightLink.x + width / 2,
                                node.rightLink.y + width / 2);
                    }
                    g.setColor(Color.RED);
                g.drawOval(
                        node.getX(),
                        node.getY(),
                        width,
                        width);
                if(node.getVisibleNodeMessage() != null){
                    g.setColor(Color.CYAN);
                    g.drawString(node.getVisibleNodeMessage(), node.getX(), node.getY());
                }
            }
        }
    }
}
