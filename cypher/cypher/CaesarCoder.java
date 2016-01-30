/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cypher;

import javax.swing.JOptionPane;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.table.DefaultTableModel;

/**
 *
 * @author aleole
 */
public class CaesarCoder extends Coder{
    private int caesarShift;
    private char[] originalMessage = null;
    private char[] reformedLiteralMessage = null;
    
    public CaesarCoder(boolean showProc, int caesarShift, String outerOrigMessage){
        super(showProc);
        this.caesarShift = caesarShift;
        originalMessage = outerOrigMessage.toCharArray();
    }
        
    public String caesarСodeMessage(){
        reformedLiteralMessage = new char[originalMessage.length];
        for(int i = 0; i < originalMessage.length; i++){
            if(chars.get(originalMessage[i]) == null){
                reformedLiteralMessage[i] = ' ';
            }else if(chars.get(originalMessage[i]) + caesarShift < 0){
                reformedLiteralMessage[i]
                        = inverseChars.get(31 + chars.get(originalMessage[i]) + caesarShift);
            }else{
                reformedLiteralMessage[i]
                    = inverseChars.get((chars.get(originalMessage[i]) + caesarShift)%31);
            }
        }
        if(showProc){//покажем таблицу
                serviceTable = new JTable(buildTableModel());
                JOptionPane.showMessageDialog(null, new JScrollPane(serviceTable));
            }
        return new String(reformedLiteralMessage);
    }
    
    public DefaultTableModel buildTableModel(){
        //names of columns
        Object[][] multiDimArray = new Object[originalMessage.length][2];
        for(int i = 0; i < multiDimArray.length; i++){
            for(int j = 0; j < multiDimArray[i].length; j++){
                multiDimArray[i][j] = (j == 0)
                        ? (chars.get(originalMessage[i]) != null ? chars.get(originalMessage[i]) : 100)
                        : (chars.get(originalMessage[i]) != null ? chars.get(originalMessage[i]) + caesarShift : 100);
            }
        }
        return new DefaultTableModel(multiDimArray, new Object[]{"Без сдвига", "Со сдвигом"});
    }
}
