/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cypher;

import java.util.HashMap;
import javax.swing.JTable;

/**
 *
 * @author aleole
 */
public abstract class Coder {
    protected HashMap<Character, Integer> chars = null;
    protected HashMap<Integer, Character> inverseChars = null;
    protected boolean showProc = false;
    protected JTable serviceTable = null;
    
    public Coder(boolean showProc){
        this.showProc = showProc;
        chars = new HashMap<Character, Integer>();
        chars.put('а', 0);
        chars.put('б', 1);
        chars.put('в', 2);
        chars.put('г', 3);
        chars.put('д', 4);
        chars.put('е', 5);
        chars.put('ё', 5);
        chars.put('ж', 6);
        chars.put('з', 7);
        chars.put('и', 8);
        chars.put('й', 9);
        chars.put('к', 10);
        chars.put('л', 11);
        chars.put('м', 12);
        chars.put('н', 13);
        chars.put('о', 14);
        chars.put('п', 15);
        chars.put('р', 16);
        chars.put('с', 17);
        chars.put('т', 18);
        chars.put('у', 19);
        chars.put('ф', 20);
        chars.put('х', 21);
        chars.put('ц', 22);
        chars.put('ч', 23);
        chars.put('ш', 24);
        chars.put('щ', 25);
        chars.put('ы', 26);
        chars.put('ь', 27);
        chars.put('ъ', 27);
        chars.put('э', 28);
        chars.put('ю', 29);
        chars.put('я', 30);
        inverseChars = new HashMap<Integer, Character>();
        chars.forEach((k,v)->inverseChars.put(v, k));
    }
}
