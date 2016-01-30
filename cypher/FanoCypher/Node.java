/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package FanoCypher;

/**
 *
 * @author aleole
 */
public class Node {//объект этого класса представляет собой узел дерева
    private final String message;
    private final int level;
    private boolean leaf = false;
    private Node leftNode;
    private Node rightNode;
    
    public Node(String outerMessage, int outerLevel){
        message = outerMessage;
        level = outerLevel;
    }
    
    public String getNodeMessage(){
        return message;
    }
    
    public int getLevel(){
        return level;
    }
    
    public boolean isLeaf(){
        return leaf;
    }
    public void setLeaf(boolean isLeaf){
        leaf = isLeaf;
    }
    public Node getLeftNode(){
        return leftNode;
    }
    public void setLeftNode(Node outerNode){
        leftNode = outerNode;
    }
    public Node getRightNode(){
        return rightNode;
    }
    public void setRightNode(Node outerNode){
        rightNode = outerNode;
    }
}
