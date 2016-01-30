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
public class TrithemiusCoder extends Coder{
    private int[] digitalKey = null;
    private int[] digitalMessage = null;
    private int[] reformedDigitalMessage = null;
    private int[] serviceDigitalArray = null;
    private char[] originalMessage = null;
    private char[] reformedLiteralMessage = null;
    private char[] codeWord = null;
    private boolean onlyCyrLet = true;
    
    public TrithemiusCoder(boolean showProc, String outerCodeWord, String outerOrigMessage){
        super(showProc);
        if(!outerCodeWord.equals("")){
            codeWord = outerCodeWord.toCharArray();
            originalMessage = outerOrigMessage.toCharArray();
            //получим цифровой ключ из кодового слова
            digitalKey = new int[codeWord.length];
            for(int i = 0; i < codeWord.length; i++){
                if(chars.get(codeWord[i]) != null){
                    digitalKey[i] = chars.get(codeWord[i]);
                }else{
                    JOptionPane.showMessageDialog(
                            null,
                            "В кодовом слове допускаются только строчные буквы кириллицы.");
                    onlyCyrLet = false;
                    break;
                }
            }
            if(onlyCyrLet){
                //получим цифровое представление исходного сообщения
                //100 - любой незнакомый символ, заменяется на пробел
                digitalMessage = new int[originalMessage.length];
                for(int i = 0; i < originalMessage.length; i++){
                    digitalMessage[i] = chars.get(originalMessage[i]) != null ? chars.get(originalMessage[i]) : 100;
                }
                //получим вспомогательный массив размером с digitalMessage из повторяющегося digitalKey
                serviceDigitalArray = new int[originalMessage.length];
                int j = 0;//индекс для движения по массиву digitalKey
                for(int i = 0; i < serviceDigitalArray.length; i++){
                    j = j < digitalKey.length ? j : 0;
                    serviceDigitalArray[i] = digitalKey[j];
                    j++;
                }
            }
        }else{
            JOptionPane.showMessageDialog(null, "Задайте кодовое слово");
            onlyCyrLet = false;
        }
    }
    
    public void trithemiusEncodeMessage(){
        if(onlyCyrLet){
            //сдвинем буквы сообщения вдоль алфавита...
            reformedDigitalMessage = new int[originalMessage.length];
            for(int i =0; i < originalMessage.length; i++){
                if(digitalMessage[i] != 100){
                    reformedDigitalMessage[i]
                        = (digitalMessage[i] + serviceDigitalArray[i]) < 31
                        ? digitalMessage[i] + serviceDigitalArray[i]
                        : digitalMessage[i] + serviceDigitalArray[i] - 31;
                }else{
                    reformedDigitalMessage[i] = 100;
                }
            }
        }
    }
    
    public void trithemiusDecodeMessage(){
        //сдвинем буквы обратно...
        if(onlyCyrLet){
            reformedDigitalMessage = new int[originalMessage.length];
            for(int i = 0; i < originalMessage.length; i++){
                if(digitalMessage[i] != 100){
                    reformedDigitalMessage[i]
                            = digitalMessage[i] - serviceDigitalArray[i] < 0
                            ? digitalMessage[i] - serviceDigitalArray[i] + 31
                            : digitalMessage[i] - serviceDigitalArray[i];
                }else{
                    reformedDigitalMessage[i] = 100;
                }
            }
        }
    }
    
    public String presentMessage(String action){
        if(onlyCyrLet){
            //заменим числа на буквы...
            reformedLiteralMessage = new char[originalMessage.length];
            for(int i = 0; i < reformedLiteralMessage.length; i++){
                reformedLiteralMessage[i]
                    = inverseChars.get(reformedDigitalMessage[i]) != null
                    ? inverseChars.get(reformedDigitalMessage[i]) : ' ';
            }
            if(showProc){//покажем таблицу
                serviceTable = new JTable(buildTableModel(action));
                JOptionPane.showMessageDialog(null, new JScrollPane(serviceTable));
            }
            return new String(reformedLiteralMessage);
        }
        return null;
    }
    
    public DefaultTableModel buildTableModel(String action){
        //names of columns
        Object[][] multiDimArray = new Object[originalMessage.length][3];
        for(int i = 0; i < multiDimArray.length; i++){
            for(int j = 0; j < multiDimArray[i].length; j++){
                multiDimArray[i][j] = (j == 0)
                        ? digitalMessage[i]
                        : (j == 1) ? serviceDigitalArray[i]
                        : new  StringBuilder()
                                .append(digitalMessage[i])
                                .append(action)
                                .append(serviceDigitalArray[i])
                                .append(" = ")
                                .append(action.equals(" + ") ? digitalMessage[i] + serviceDigitalArray[i] : digitalMessage[i] - serviceDigitalArray[i]);
            }
        }
        return new DefaultTableModel(multiDimArray, new Object[]{"Сообщение", "Ключ", action});
    }
    
    
}
