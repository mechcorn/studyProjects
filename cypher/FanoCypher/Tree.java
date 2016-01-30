/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package FanoCypher;

import java.util.ArrayList;
import java.util.Collections;

/**
 *
 * @author aleole
 */
public class Tree {//объект этого класса представляет собой дерево
    private Node root;//корень дерева
    private int maxLevel = 0;//максимальный уровень дерева
  
    public Tree(ArrayList<ComplexMessage> iData){
        root = make(iData, 0);
    }
    
    public Node getRoot(){
        return root;
    }
    
    public int getMaxlevel(){
        return maxLevel;
    }
    
    public Node make(ArrayList<ComplexMessage> outerSource, int outerLevel){//создаёт узлы и связывает их с левыми и правыми поддеревьями
        if(maxLevel < outerLevel){
            maxLevel = outerLevel;
        }
        Node node = null;
        if(outerSource.size() > 1){//узел будет промежуточным, будем формировать узлы следующего уровня
            node = new Node(null, outerLevel);
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//разбиваем множество сообщений на две группы так,
//чтобы суммарные вероятности сообщений каждой из групп были
//как можно более близки друг к другу
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//упорядочим список по убыванию
            Collections.sort(outerSource, Collections.reverseOrder());
//определим половину суммарной вероятности текущего списка
            double sum = 0;
            for(ComplexMessage item : outerSource){
                sum += item.getProbability();
            }
            double sumHalf = sum / 2;
//разбиваем список на две группы
            ArrayList<ComplexMessage> leftArray = new ArrayList<>();
            ArrayList<ComplexMessage> rightArray = new ArrayList<>();
            double limit = 0;
            for(ComplexMessage item : outerSource){
                limit += item.getProbability();
                if(limit > sumHalf){
                    rightArray.add(item);
                }else{
                    leftArray.add(item);
                }
            }
            node.setLeftNode(make(leftArray, outerLevel + 1));
            node.setRightNode(make(rightArray, outerLevel + 1));
        }else{//узел будет терминальным, завершаем построение дерева
            node = new Node(outerSource.get(0).getMessage(), outerLevel);
            node.setLeaf(true);
        }
        return node;
    }
}
