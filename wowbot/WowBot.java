package wowbot;

import java.awt.AWTException;
import java.awt.Desktop;
import java.awt.HeadlessException;
import java.awt.Robot;
import java.awt.Toolkit;
import java.awt.datatransfer.Clipboard;
import java.awt.datatransfer.DataFlavor;
import java.awt.datatransfer.StringSelection;
import java.awt.datatransfer.UnsupportedFlavorException;
import java.awt.event.InputEvent;
import java.awt.event.KeyEvent;
import java.io.IOException;
import java.net.URI;
import java.net.URISyntaxException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.Calendar;
import java.util.Random;

import javax.swing.JOptionPane;


public class WowBot {
	
	/* Variables needed for Robot registration */
	private Robot r;
	Random rand;
	DateTimeFormatter dtf = DateTimeFormatter.ofPattern("yy/MM/dd");
	LocalDateTime now;
	
	//constructor for registration of DK merchants
	public WowBot() {
		rand = new Random();
		try {
			r = new Robot();
		} catch (AWTException e) {
			e.printStackTrace();
		}
		
		String myString = "DONE";
		StringSelection stringSelection = new StringSelection(myString);
		Clipboard clipboard = Toolkit.getDefaultToolkit().getSystemClipboard();
		clipboard.setContents(stringSelection, null);
	}
	
	// Start bot
	void startBot(String bgInput, String factionInput) {
		// 2s thread sleep delay
		try {
			Thread.sleep(2000);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		
		bgInput = "2";
		factionInput = "ally";
		
		while (true) {
			System.out.println("Args: " + bgInput + ", " + factionInput);
			boolean isAlly = factionInput.toLowerCase().equals("ally");
			switch(bgInput) {
			case "0":
				System.out.println("Starting WSG bot! isAlly: " + isAlly);
				startBgBot(0, 1700, isAlly); // WSG
				break;
			case "1":
				System.out.println("Starting AB bot! isAlly: " + isAlly);
				startBgBot(1, 600, isAlly); // AB
				break;
			case "2": default:
				System.out.println("Starting AV bot! isAlly: " + isAlly);
				startBgBot(2, 1900, isAlly); // AV
				break;
			}
		}
	}
	
	void startBgBot(int bg, int bgTimer, boolean isAlly) {
		int timeInBg = 0;
		// Open pvp window
		sendKey(KeyEvent.VK_H);
		r.delay(1000);
		// Press Battlegrounds
		r.mouseMove(200, 530);
		// Click
		r.delay(500);
		r.mousePress(InputEvent.BUTTON1_DOWN_MASK);
		r.mouseRelease(InputEvent.BUTTON1_DOWN_MASK);

		r.delay(1000);
		if (bg == 0)
			//r.mouseMove(240, 240); // WSG when WSG at second?
			r.mouseMove(240, 250); // WSG when WSG at third
		else if (bg == 1)
			//r.mouseMove(240, 250); // AB
			r.mouseMove(240, 260); // AB when AB at fourth
		else
			//r.mouseMove(240, 260); // AV
			r.mouseMove(240, 280); // AV when AV at fifth
		// Click
		r.delay(500);
		r.mousePress(InputEvent.BUTTON1_DOWN_MASK);
		r.mouseRelease(InputEvent.BUTTON1_DOWN_MASK);

		r.delay(1000);
		r.mouseMove(290, 505); // Join queue
		// Click
		r.delay(500);
		r.mousePress(InputEvent.BUTTON1_DOWN_MASK);
		r.mouseRelease(InputEvent.BUTTON1_DOWN_MASK);
		
		r.delay(3000);
		r.mouseMove(710, 220); // Accept queue inv
		// Click
		r.delay(500);
		r.mousePress(InputEvent.BUTTON1_DOWN_MASK);
		r.mouseRelease(InputEvent.BUTTON1_DOWN_MASK);

		r.delay(5000);
		// Click
		r.mousePress(InputEvent.BUTTON1_DOWN_MASK);
		r.mouseRelease(InputEvent.BUTTON1_DOWN_MASK);

		// Wait for bg to start...
		if (bg == 0) {
			r.delay(1000);
			r.keyPress(KeyEvent.VK_D);
			r.delay(500);
			r.keyRelease(KeyEvent.VK_D);
			r.delay(500);
			r.keyPress(KeyEvent.VK_W);
			r.delay(1700);
			r.keyRelease(KeyEvent.VK_W);
			r.delay(1000);
			r.keyPress(KeyEvent.VK_A);
			if (isAlly)
				r.delay(495); // Ally
			else
				r.delay(455); // Horde
			r.keyRelease(KeyEvent.VK_A);
			r.delay(500);
			r.keyPress(KeyEvent.VK_W);
			r.delay(1500);
			r.keyRelease(KeyEvent.VK_W);
			r.delay(46000);
		} else {
			for (int i = 0; i < 5; i++) {
				r.delay(9000);
				r.keyPress(KeyEvent.VK_W);
				r.delay(1000);
				r.keyRelease(KeyEvent.VK_W);

				// Turn slightly in AV beginning
				if (bg == 2 && i == 0) {
					r.delay(100);
					r.keyPress(KeyEvent.VK_A);
					r.delay(100);
					r.keyRelease(KeyEvent.VK_A);
				} else if (bg == 2 && i == 4) {
					r.delay(100);
					r.keyPress(KeyEvent.VK_D);
					if (isAlly)
						r.delay(150);
					else
						r.delay(80);
					r.keyRelease(KeyEvent.VK_D);
				}
			}
		}
		
		// Random walking and some spell casts
		for (int i = 0; i < 80 && timeInBg < bgTimer; i++) {
			r.delay(2000);
			r.keyPress(KeyEvent.VK_W);
			r.delay(100);
			r.keyRelease(KeyEvent.VK_W);
			r.delay(100);
			
			// Auto run
			r.delay(500);
			r.keyPress(KeyEvent.VK_ALT);
			r.delay(60);
			r.keyPress(KeyEvent.VK_X);
			r.delay(60);
			r.keyRelease(KeyEvent.VK_X);
			r.delay(60);
			r.keyRelease(KeyEvent.VK_ALT);
			
			r.delay(9500);
			// 20 % chance of jumping, else use spell (scroll down)
			//if (rand.nextInt(10) == 0) // 10 % chance
			if (rand.nextInt(4) == 0) {
				r.keyPress(KeyEvent.VK_SPACE);
				r.delay(500);
				r.keyRelease(KeyEvent.VK_SPACE);
			} else
				r.mouseWheel(1);

			r.delay(1500);
			r.keyPress(KeyEvent.VK_W);
			r.delay(100);
			r.keyRelease(KeyEvent.VK_W);
			r.delay(100);

			// 50 % chance of turning left / right
			// Don't turn in AB / AV until a few minutes have passed 
			if (bg == 0 || timeInBg > 150) {
				if (rand.nextInt(2) == 0) {
					System.out.println("Turning left");
					r.keyPress(KeyEvent.VK_A);
					r.delay(500);
					r.keyRelease(KeyEvent.VK_A);
					// 50 % chance of turning some more
					if (rand.nextInt(2) == 0) {
						r.delay(200);
						r.keyPress(KeyEvent.VK_A);
						r.delay(200);
						r.keyRelease(KeyEvent.VK_A);
					}
				}
				else {
					System.out.println("Turning right");
					r.keyPress(KeyEvent.VK_D);
					r.delay(500);
					r.keyRelease(KeyEvent.VK_D);
					// 50 % chance of turning some more
					if (rand.nextInt(2) == 0) {
						r.delay(200);
						r.keyPress(KeyEvent.VK_D);
						r.delay(200);
						r.keyRelease(KeyEvent.VK_D);
					}
				}
			}
			
			// 30 % chance of clicking release and wait for 30 sec
			if (rand.nextInt(3) == 0) {
				System.out.println("Trying to release... Loop count: " + i);
				// Click
				r.delay(500);
				r.mouseMove(730, 220);
				r.delay(500);
				r.mousePress(InputEvent.BUTTON1_DOWN_MASK);
				r.mouseRelease(InputEvent.BUTTON1_DOWN_MASK);
				// Wait 30 sec
				r.delay(15000);
				r.keyPress(KeyEvent.VK_W);
				r.delay(100);
				r.keyRelease(KeyEvent.VK_W);
				r.delay(100);
				r.delay(14500);
				timeInBg += 30;
			}
			timeInBg += 14;

			//r.mouseWheel(1);
			// Use R spell
			r.keyPress(KeyEvent.VK_R);
			r.delay(100);
			r.keyRelease(KeyEvent.VK_R);
			r.delay(100);
			System.out.println("End of loop... timeInBg: " + timeInBg + ", bgTimer: " + bgTimer);
		}
		
		// rand.nextInt(100) < 34
	}
	
    //enter the incoming String info, then press End and Enter
    void enterInfo(String info){
        sendKeys(info);
		//sendKey(KeyEvent.VK_END);
        sendEndKey();
		sendKey(KeyEvent.VK_ENTER);
    }
    
    //clean rest of the field by entering space a few times
    void sendEndKey() {
    	for (int i = 0; i < 5; i++) {
			r.delay(35);
			r.keyPress(KeyEvent.VK_SPACE);
			r.delay(35);
			r.keyRelease(KeyEvent.VK_SPACE);
			r.delay(35);
    	}
    }
	
	//execute specific key
	void sendKey(int key) {
		//r.delay(20);
		r.delay(70);
		r.keyPress(key);
		//r.delay(20);
		r.delay(70);
		r.keyRelease(key);
		//r.delay(20);
		r.delay(70);
	}
	
	//execute the characters in string key 
	void sendKeys(String keys) {
	    for (char c : keys.toCharArray()) {
	    	if(c == 'Å') {
	    		keyPress('Å');
	    	}else if (c == 'Ä') {
	    		keyPress('Ä');
	    	}else if (c == 'Ö') {
	    		keyPress('Ö');
	    	}else if (c == 'å') {
	    		keyPress('å');
	    	}else if (c == 'ä') {
	    		keyPress('ä');
	    	}else if (c == 'ö') {
	    		keyPress('ö');
	    	}else if (c == '&') {
	    		keyPress('&');
	    	}else if (c == '#') {
	    		keyPress('#');
	    	}else if (c == '!') {
	    		keyPress('!');
	    	}else if (c == '/') {
	    		keyPress('/');
	    	}else if (c == ':') {
	    		keyPress(':');
	    	}else if (c == '@') {
	    		keyPress('@');
	    	}else {
				int keyCode = KeyEvent.getExtendedKeyCodeForChar(c);
				if (KeyEvent.CHAR_UNDEFINED == keyCode) {
					throw new RuntimeException(
						"Key code not found for character '" + c + "'");
				}
				//r.delay(20);
				r.delay(60);
				r.keyPress(keyCode);
				//r.delay(20);
				r.delay(60);
				r.keyRelease(keyCode);
				//r.delay(20);
				r.delay(60);
	    	}
	    }
	}
	
	//press keys via altNumpad
	public void keyPress(char characterKey){
	    switch (characterKey){
	        case '!': altNumpad("33"); break;
	        case '"': altNumpad("34"); break;
	        case '#': altNumpad("35"); break;
	        case '$': altNumpad("36"); break;
	        case '%': altNumpad("37"); break;
	        case '&': altNumpad("38"); break;
	        case '\'': altNumpad("39"); break;
	        case '(': altNumpad("40"); break;
	        case ')': altNumpad("41"); break;
	        case '*': altNumpad("42"); break;
	        case '+': altNumpad("43"); break;
	        case ',': altNumpad("44"); break;
	        case '-': altNumpad("45"); break;
	        case '.': altNumpad("46"); break;
	        case '/': altNumpad("47"); break;
	        case '0': altNumpad("48"); break;
	        case ':': altNumpad("58"); break;
	        case '@': altNumpad("64"); break;
	        case 'å': altNumpad("134"); break;
	        case 'ä': altNumpad("132"); break;
	        case 'ö': altNumpad("148"); break;
	        case 'Å': altNumpad("143"); break;
	        case 'Ä': altNumpad("142"); break;
	        case 'Ö': altNumpad("153"); break;
	        default: return;
	    }
	}

	//altNumpad for special characters
	private void altNumpad(int... numpadCodes){
	    if (numpadCodes.length == 0) {
	        return;
	    }
	    r.keyPress(KeyEvent.VK_ALT);

	    for (int NUMPAD_KEY : numpadCodes){
	        r.keyPress(NUMPAD_KEY);
	        r.keyRelease(NUMPAD_KEY);
	    }
	    r.keyRelease(KeyEvent.VK_ALT);
	}

	//altNumpad for special characters
	private void altNumpad(String numpadCodes){
	    if (numpadCodes == null || !numpadCodes.matches("^\\d+$")){
	        return;
	    }               
	    r.keyPress(KeyEvent.VK_ALT);
		
	    for (char charater : numpadCodes.toCharArray()){
	        int NUMPAD_KEY = getNumpad(charater);
	        if (NUMPAD_KEY != -1){
	            r.keyPress(NUMPAD_KEY);
	            r.keyRelease(NUMPAD_KEY);
	        }
	    }
	    r.keyRelease(KeyEvent.VK_ALT);        
	}

	//get numpad keyevents
	private int getNumpad(char numberChar){
	    switch (numberChar){
	        case '0' : return KeyEvent.VK_NUMPAD0;
	        case '1' : return KeyEvent.VK_NUMPAD1;
	        case '2' : return KeyEvent.VK_NUMPAD2;
	        case '3' : return KeyEvent.VK_NUMPAD3;
	        case '4' : return KeyEvent.VK_NUMPAD4;
	        case '5' : return KeyEvent.VK_NUMPAD5;
	        case '6' : return KeyEvent.VK_NUMPAD6;
	        case '7' : return KeyEvent.VK_NUMPAD7;
	        case '8' : return KeyEvent.VK_NUMPAD8;
	        case '9' : return KeyEvent.VK_NUMPAD9;
	        default: return -1;
	    }
	}
	
	//click on the screen with Robot 
	void click(int x, int y) throws AWTException{
		r.mouseMove(x, y);    
		r.mousePress(InputEvent.BUTTON1_DOWN_MASK);
		r.mouseRelease(InputEvent.BUTTON1_DOWN_MASK);
	}

	//mark and drag on the screen with Robot 
	void selectAndCopy(int x, int y) throws AWTException{
		/*
		r.mouseMove(x, y);    
		r.mousePress(InputEvent.BUTTON1_DOWN_MASK);
		r.mouseMove(x, y);
		r.delay(200);
		r.mouseRelease(InputEvent.BUTTON1_DOWN_MASK);
		//r.keyPress(KeyEvent.CTRL_DOWN_MASK);

		r.keyPress(KeyEvent.VK_CONTROL);
		r.delay(60);
		r.keyPress(KeyEvent.VK_C);
		r.delay(60);
		r.keyRelease(KeyEvent.VK_CONTROL);
		r.delay(60);
		r.keyRelease(KeyEvent.VK_C);
		*/
		r.mouseMove(x, y);
		// first click
		r.mousePress(InputEvent.BUTTON1_DOWN_MASK);
		r.mouseRelease(InputEvent.BUTTON1_DOWN_MASK);
		// second click
		r.mousePress(InputEvent.BUTTON1_DOWN_MASK);
		r.mouseRelease(InputEvent.BUTTON1_DOWN_MASK);
		r.delay(100);
		r.keyPress(KeyEvent.VK_CONTROL);
		r.delay(60);
		r.keyPress(KeyEvent.VK_C);
		r.delay(60);
		r.keyRelease(KeyEvent.VK_CONTROL);
		r.delay(60);
		r.keyRelease(KeyEvent.VK_C);
	}
}