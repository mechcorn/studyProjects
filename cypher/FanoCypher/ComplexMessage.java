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
public class ComplexMessage implements Comparable<ComplexMessage>{
    private final String message;
    private final Double probability;
    
    public ComplexMessage(String outerMessage, Double outerProbability){
        message = outerMessage;
        probability = outerProbability;
    }
    public String getMessage(){
        return message;
    }
    public Double getProbability(){
        return probability;
    }

    @Override
    public int compareTo(ComplexMessage o) {
        return this.probability > o.probability ? 1 : this.probability < o.probability ? -1 : 0;
    }
}
