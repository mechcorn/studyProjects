/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package GuiJdbcPddDb4;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author aleole
 */
public class UrlAddressJdbc {
    private final StringBuilder sb;
    private String driverType;
    private String host;
    private String port;
    private String database;
    private String login;
    private String psswrd;
    private String netConfigPath = "D:\\netconfig.txt";
    
    public UrlAddressJdbc(){
        try {
            FileReader fr = new FileReader(netConfigPath);
            BufferedReader br = new BufferedReader(fr);
            String inputLine;
            String[] records = null;
            if(br != null){
                while((inputLine = br.readLine()) != null){
                    
                    if(inputLine.toCharArray()[0] != '#'){
                        records = inputLine.trim().split("(\\p{Blank})+");
                    }
                }
                driverType = records[0].trim();
                host = records[1].trim();
                port = records[2].trim();
                database = records[3].trim();
                login = records[4].trim();
                psswrd = records[5].trim();
            }
        } catch (IOException ex) {
            System.out.println("Error: " + ex.getMessage());
            Logger.getLogger(UrlAddressJdbc.class.getName()).log(Level.SEVERE, null, ex);
        }
        sb = new StringBuilder();
        sb.append("jdbc:");
        sb.append(driverType);
        sb.append("://");
        sb.append(host);
        sb.append(':');
        sb.append(port);
        sb.append('/');
        sb.append(database);
    }
    
    public String getAddress(){
        return sb.toString();
    }
    
    public String getGuestLogin(){
        return login;
    }
    
    public String getGuestPassword(){
        return psswrd;
    }
}
