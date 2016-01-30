/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package FanoCypher;

import java.util.ArrayList;

/**
 *
 * @author aleole
 */
public class FanoCoder {
    private final ArrayList<ComplexMessage> messages;
    
    public FanoCoder(){
        messages = new ArrayList<>();
        messages.add(new ComplexMessage("A6", 0.0625));
        messages.add(new ComplexMessage("A7", 0.0625));
        messages.add(new ComplexMessage("A5", 0.125));
        messages.add(new ComplexMessage("A4", 0.125));
        messages.add(new ComplexMessage("A3", 0.125));
        messages.add(new ComplexMessage("A1", 0.25));
        messages.add(new ComplexMessage("A2", 0.25));
    }
    
    public ArrayList<ComplexMessage> getMessages(){
        return messages;
    }
}
