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

class MousePos {
	  final int x;
	  final int y;
	  MousePos(int x, int y) {this.x=x;this.y=y;}
}

public class wowbot {
	
	/* Variables needed for Robot */
	private Robot r;
	Random rand;
	DateTimeFormatter dtf = DateTimeFormatter.ofPattern("yy/MM/dd");
	LocalDateTime now;

	private MousePos arena2v2 = new MousePos(240, 408);
	private MousePos arena3v3 = new MousePos(240, 420);
	private MousePos arena5v5 = new MousePos(240, 440);
	private MousePos queueJoin = new MousePos(290, 662);
	private MousePos queueAccept = new MousePos(850, 265);
	private MousePos bgPress = new MousePos(180, 695);
	private MousePos bg1 = new MousePos(240, 290);
	private MousePos bg2 = new MousePos(240, 308);
	private MousePos bg3 = new MousePos(240, 330);
	private MousePos bg4 = new MousePos(240, 340);
	private MousePos lowLevelWsg = new MousePos(240, 270);
	private MousePos lowLevelAb = new MousePos(240, 290);
	private MousePos lowLevelAv = new MousePos(240, 308);
	private MousePos acceptRess = new MousePos(900, 265);
	
	public wowbot() {
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
	
	// Start BOT
	void startBot(String bgInput, String factionInput) {
		// 2s thread sleep delay
		try {
			Thread.sleep(2000);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		
		bgInput = "ra"; // Both random BGs and arenas
		//bgInput = "r"; // Random BGs
		//bgInput = "a"; // Random arenas
		factionInput = "ally";
		boolean isLowLevel = false;
		int bgCount = 0; // Keep track of how many BGs / arenas that have been played
		int bgCountMax = 10; // Max amount of bgCount before switching to BG / arena
		boolean isArena = false; // Start with BG
		
		while (true) {
			System.out.println("Args: " + bgInput + ", " + factionInput);
			boolean isAlly = factionInput.toLowerCase().equals("ally");
			switch(bgInput) {
			case "0":
				System.out.println("Starting WSG bot! isAlly: " + isAlly);
				startBgBot(0, 1700, isAlly, isLowLevel); // WSG
				break;
			case "1":
				System.out.println("Starting AB bot! isAlly: " + isAlly);
				startBgBot(1, 650, isAlly, isLowLevel); // AB
				break;
			case "2":
				System.out.println("Starting AV bot! isAlly: " + isAlly);
				startBgBot(2, 1950, isAlly, isLowLevel); // AV
				break;
			case "ra":
				if (bgCount < bgCountMax && isArena) {
					System.out.println("Starting arena bot! isAlly: " + isAlly);
					startArenaBot(100, 250, isAlly); // Random arena
				} else if (bgCount < (bgCountMax/2) && !isArena) {
					System.out.println("Starting random BG bot! isAlly: " + isAlly);
					startBgBot(100, 0, isAlly, isLowLevel); // Random BGs
				} else {
					// This means bgCountMax has been reached
					if (isArena) {
						System.out.println("Switching to playing BGs");
						System.out.println("Starting random BG bot! isAlly: " + isAlly);
						startBgBot(100, 0, isAlly, isLowLevel); // Random BGs
					} else {
						System.out.println("Switching to playing arenas");
						System.out.println("Starting arena bot! isAlly: " + isAlly);
						startArenaBot(100, 250, isAlly); // Random arena
					}
					bgCount = 0;
					isArena = !isArena;
				}
				bgCount++;
				break;
			case "r":
				System.out.println("Starting random BG bot! isAlly: " + isAlly);
				startBgBot(100, 0, isAlly, isLowLevel); // Random BGs
				break;
			case "a": default: 
				System.out.println("Starting arena bot! isAlly: " + isAlly);
				//startArenaBot(0, 250, isAlly); // 2v2
				//startArenaBot(1, 250, isAlly); // 3v3
				//startArenaBot(2, 250, isAlly); // 5v5
				startArenaBot(100, 250, isAlly); // Random arena
				break;
			}
		}
	}

	void startArenaBot(int arenaId, int bgTimer, boolean isAlly) {
		int timeInBg = 0;
		int maxActionTime = 45;
		r.delay(1000);
		// Teleport to arena NPC
		sendKey(KeyEvent.VK_ENTER);
		r.delay(200);
		if (isAlly)
			sendKeys(".go creature 68938"); // select guid from creature where id1=19911; (id from arena npc from wowhead)
		else
			sendKeys(".go creature 4762"); // select guid from creature where id1=19912; (id from arena npc from wowhead)
		sendKey(KeyEvent.VK_ENTER);

		r.delay(5000);
		// /target arena char and interact with him
		sendKey(KeyEvent.VK_ENTER);
		// Enter '/' manually for Linux
		r.delay(200);
		r.keyPress(KeyEvent.VK_SHIFT);
		r.delay(60);
		r.keyPress(KeyEvent.VK_7);
		r.delay(60);
		r.keyRelease(KeyEvent.VK_7);
		r.delay(60);
		r.keyRelease(KeyEvent.VK_SHIFT);
		r.delay(60);
		if (isAlly)
			sendKeys("target beka");
		else
			sendKeys("target zeggon");
		sendKey(KeyEvent.VK_ENTER);
		r.delay(700);
		sendKey(KeyEvent.VK_9);
		r.delay(1300);

		if (arenaId == 100) // Hard coded, 100 means random arena
			arenaId = rand.nextInt(3);
		
		if (arenaId == 2) // Extend bgTimer slightly for 5v5
			bgTimer += 50;

		if (arenaId == 0)
			r.mouseMove(arena2v2.x, arena2v2.y); // 2v2
		else if (arenaId == 1)
			r.mouseMove(arena3v3.x, arena3v3.y); // 3v3
		else
			r.mouseMove(arena5v5.x, arena5v5.y); // 5v5

		// Click
		r.delay(700);
		r.mousePress(InputEvent.BUTTON1_DOWN_MASK);
		r.mouseRelease(InputEvent.BUTTON1_DOWN_MASK);

		r.delay(1000);
		r.mouseMove(queueJoin.x, queueJoin.y); // Join queue
		// Click
		r.delay(500);
		r.mousePress(InputEvent.BUTTON1_DOWN_MASK);
		r.mouseRelease(InputEvent.BUTTON1_DOWN_MASK);
		
		r.delay(3000);
		r.mouseMove(queueAccept.x, queueAccept.y); // Accept queue inv
		// Click
		r.delay(500);
		r.mousePress(InputEvent.BUTTON1_DOWN_MASK);
		r.mouseRelease(InputEvent.BUTTON1_DOWN_MASK);

		r.delay(5000);
		// Click
		r.mousePress(InputEvent.BUTTON1_DOWN_MASK);
		r.mouseRelease(InputEvent.BUTTON1_DOWN_MASK);

		// Wait for arena to start...
		for (int i = 0; i < 5; i++) {
			r.delay(9000);
			if (i == 0) {
				r.keyPress(KeyEvent.VK_W);
				r.delay(1000);
				r.keyRelease(KeyEvent.VK_W);
			} else if (i == 1) {
				r.keyPress(KeyEvent.VK_D);
				r.delay(350);
				r.keyRelease(KeyEvent.VK_D);
			} else {
				// 20 % chance of jumping, else use spell (scroll down)
				if (rand.nextInt(4) == 0) {
					r.keyPress(KeyEvent.VK_SPACE);
					r.delay(100);
					r.keyRelease(KeyEvent.VK_SPACE);
				} else
					r.mouseWheel(1);
				}
		}
		
		// Random spell casting
		for (int i = 0; i < 80 && timeInBg < bgTimer; i++) {
			r.delay(5000); // 5s delay

			// 20 % chance of jumping, else use spell (scroll down)
			if (rand.nextInt(4) == 0) {
				r.keyPress(KeyEvent.VK_SPACE);
				r.delay(200);
				r.keyRelease(KeyEvent.VK_SPACE);
			} else
				r.mouseWheel(1);

			r.delay(1500); // 1.5s delay

			if (timeInBg < maxActionTime) {
				r.keyPress(KeyEvent.VK_W);
				r.delay(100);
				r.keyRelease(KeyEvent.VK_W);
				r.delay(100);
			}

			r.delay(1500);
			// Use E or 4 spell
			if (timeInBg < maxActionTime) {
				if (rand.nextInt(2) == 0) {
					r.keyPress(KeyEvent.VK_T);
					r.delay(100);
					r.keyRelease(KeyEvent.VK_T);
					r.delay(500);
					r.keyPress(KeyEvent.VK_E);
					r.delay(100);
					r.keyRelease(KeyEvent.VK_E);
					r.delay(100);
				}
				else {
					r.keyPress(KeyEvent.VK_4);
					r.delay(100);
					r.keyRelease(KeyEvent.VK_4);
					r.delay(300);
				}
			}

			r.delay(1000);
			// Use R spell
			if (timeInBg < maxActionTime) {
				r.keyPress(KeyEvent.VK_R);
				r.delay(100);
				r.keyRelease(KeyEvent.VK_R);
				r.delay(100);
				// Use shift-w
				r.delay(980);
				r.keyPress(KeyEvent.VK_SHIFT);
				r.delay(35);
				r.keyPress(KeyEvent.VK_W);
				r.delay(35);
				r.keyRelease(KeyEvent.VK_W);
				r.delay(35);
				r.keyRelease(KeyEvent.VK_SHIFT);
				r.delay(35);
			}

			timeInBg += 11;
			//System.out.println("End of loop... timeInBg: " + timeInBg + ", bgTimer: " + bgTimer);
		}
	}
	
	void startBgBot(int bg, int bgTimer, boolean isAlly, boolean isLowLevel) {
		int timeInBg = 0;
		// Open PVP window
		sendKey(KeyEvent.VK_H);
		r.delay(1000);
		r.mouseMove(bgPress.x, bgPress.y); // Press Battlegrounds
		// Click
		r.delay(500);
		r.mousePress(InputEvent.BUTTON1_DOWN_MASK);
		r.mouseRelease(InputEvent.BUTTON1_DOWN_MASK);
		
		// Handle random BG
		if (bg == 100) // Hard coded, 100 means random arena
			bg = rand.nextInt(3);
		// Set correct bgTimer
		if (bg == 0)
			bgTimer = 1700;
		else if (bg == 1)
			bgTimer = 650;
		else
			bgTimer = 1950;

		r.delay(1000);
		if (bg == 0)
			//r.mouseMove(bg1.x, bg1.y); // WSG 1
			r.mouseMove(bg2.x, bg2.y); // WSG 2
		else if (bg == 1)
			//r.mouseMove(bg1.x, bg1.y); // AB 1
			//r.mouseMove(bg2.x, bg2.y); // AB 2
			r.mouseMove(bg3.x, bg3.y); // AB 3
		else
			//r.mouseMove(bg1.x, bg1.y); // AV 1
			//r.mouseMove(bg3.x, bg3.y); // AV 3
			r.mouseMove(bg4.x, bg4.y); // AV 4
		
		// USE THIS IF LOW LEVEL
		if (isLowLevel) {
			if (bg == 0)
				r.mouseMove(lowLevelWsg.x, lowLevelWsg.y); // WSG
			else if (bg == 1)
				r.mouseMove(lowLevelAb.x, lowLevelAb.y); // AB
			else
				r.mouseMove(lowLevelAv.x, lowLevelAv.y); // AV
		}

		// Click
		r.delay(500);
		r.mousePress(InputEvent.BUTTON1_DOWN_MASK);
		r.mouseRelease(InputEvent.BUTTON1_DOWN_MASK);

		r.delay(1000);
		r.mouseMove(queueJoin.x, queueJoin.y); // Join queue
		// Click
		r.delay(500);
		r.mousePress(InputEvent.BUTTON1_DOWN_MASK);
		r.mouseRelease(InputEvent.BUTTON1_DOWN_MASK);
		
		r.delay(3000);
		r.mouseMove(queueAccept.x, queueAccept.y); // Accept queue inv
		// Click
		r.delay(500);
		r.mousePress(InputEvent.BUTTON1_DOWN_MASK);
		r.mouseRelease(InputEvent.BUTTON1_DOWN_MASK);

		r.delay(5000);
		// Click
		r.mousePress(InputEvent.BUTTON1_DOWN_MASK);
		r.mouseRelease(InputEvent.BUTTON1_DOWN_MASK);

		// Wait for BG to start...
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
				r.delay(500); // Ally
			else
				r.delay(450); // Horde
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
						r.delay(130);
					else
						r.delay(70);
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
					//System.out.println("Turning left");
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
					//System.out.println("Turning right");
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
				//System.out.println("Trying to release... Loop count: " + i);
				// First try to accept ress from someone, then try to release
				r.delay(500);
				r.mouseMove(queueAccept.x, queueAccept.y);
				r.delay(500);
				r.mousePress(InputEvent.BUTTON1_DOWN_MASK);
				r.mouseRelease(InputEvent.BUTTON1_DOWN_MASK);
				r.delay(500);
				r.mouseMove(acceptRess.x, acceptRess.y);
				r.delay(500);
				r.mousePress(InputEvent.BUTTON1_DOWN_MASK);
				r.mouseRelease(InputEvent.BUTTON1_DOWN_MASK);
				// Wait 30 sec
				r.delay(14000);
				r.keyPress(KeyEvent.VK_W);
				r.delay(100);
				r.keyRelease(KeyEvent.VK_W);
				r.delay(100);
				r.delay(14500);
				timeInBg += 30;
				// Also use shift-w
				r.keyPress(KeyEvent.VK_SHIFT);
				r.delay(35);
				r.keyPress(KeyEvent.VK_W);
				r.delay(35);
				r.keyRelease(KeyEvent.VK_W);
				r.delay(35);
				r.keyRelease(KeyEvent.VK_SHIFT);
				r.delay(35);
			}
			timeInBg += 14;

			//r.mouseWheel(1);
			// Use R spell
			r.keyPress(KeyEvent.VK_R);
			r.delay(100);
			r.keyRelease(KeyEvent.VK_R);
			r.delay(100);
			//System.out.println("End of loop... timeInBg: " + timeInBg + ", bgTimer: " + bgTimer);
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
