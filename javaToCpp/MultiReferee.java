import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.BufferedReader;
import java.io.PrintStream;
import java.io.PrintWriter;
import java.io.StringReader;
import java.io.StringWriter;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.TreeMap;
import java.util.Map.Entry;
import java.util.Collections;
import java.util.Properties;
import java.util.Random;
import java.util.Scanner;
import java.util.Set;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import java.util.stream.Collectors;
import java.util.stream.Stream;

abstract class MultiReferee{

	private int nbTurnsMax = 0;
	private int currentTurn = 0;
	private int frame = 0;
	private Boolean continuer = true;
	private ArrayList <ArrayList <PlayerReferee> > scoreFinal = new ArrayList <ArrayList <PlayerReferee> >();
	
	private ArrayList <PlayerReferee> players = new ArrayList <PlayerReferee>();

	protected MultiReferee(InputStream is, PrintStream out, PrintStream err){
		Initialiser(is, out, err);
		DonnerInputInitial();
		for(currentTurn = 0; currentTurn < nbTurnsMax && continuer; currentTurn++){
			Tour();
		}
		Collections.reverse(scoreFinal);
		PrintClassement();
	}
	
	private void Initialiser(InputStream is, PrintStream out, PrintStream err){
		int nbPlayers = getMinimumPlayerCount();
		nbTurnsMax = getMaxRoundCount(nbPlayers);
		Properties prop = new Properties();
		prop.put("seed", String.valueOf(new Random(System.currentTimeMillis()).nextLong()));
		prop.put("shipsPerPlayer", "1");
		prop.put("barrelCount", "10");
		prop.put("mineCount", "10");
		try{
			initReferee(nbPlayers, prop);
		}catch(InvalidFormatException e){}
		for(int i = 0; i < nbPlayers; i++){
			players.add(new PlayerReferee(i, is, out, err));
		}
	}

	private void DonnerInputInitial(){
		for(PlayerReferee player : players){
			int i = player.GetId();
			player.PrintErr("Input initial joueur " + String.valueOf(i) + " :");
			for(String input : getInitInputForPlayer(i)){
				player.PrintInput(input);
			}
		}
	}

	private void Tour(){
		ArrayList <PlayerReferee> exaequos = new ArrayList <PlayerReferee>();
		prepare(currentTurn);
		for(Iterator <PlayerReferee> it = players.iterator(); it.hasNext();){
			PlayerReferee player = it.next();
			int i = player.GetId();
			player.PrintErr("===========================");
			player.PrintErr("Tour " + String.valueOf(currentTurn) + " :");
			player.PrintErr("Input joueur " + String.valueOf(i) + " :");
			for(String input : getInputForPlayer(currentTurn, i)){
				player.PrintInput(input);
			}
			try{
				frame++;
				String output = player.ReadOutput();
				try{
					handlePlayerOutput(frame, currentTurn, i, new String[] {output});
				}
				catch(InvalidInputException e){
					player.PrintErr("PERDU !");
					exaequos.add(player);
					it.remove();
				}
				catch(LostException e){
					player.PrintErr("PERDU !");
					exaequos.add(player);
					it.remove();
				}
				catch(WinException e){
					player.PrintErr("GAGNÉ !");
					continuer = false;
					while(it.hasNext()){
						exaequos.add(it.next());
						it.remove();
					}
				}
			}catch(IOException e){
				it.remove();
			}
		}
		if(!exaequos.isEmpty()){
			scoreFinal.add(exaequos);
		}
		try{
			updateGame(currentTurn);
		}
		catch(GameOverException e){
			Map <Integer, ArrayList <PlayerReferee> > scores = new TreeMap <Integer, ArrayList <PlayerReferee> >();
			for(PlayerReferee player : players){
				Integer score = new Integer(getScore(player.GetId()));
				if(!scores.containsKey(score)){
					ArrayList <PlayerReferee> array = new ArrayList <PlayerReferee>();
					scores.put(score, array);
				}
				scores.get(score).add(player);
			}
			for(Map.Entry<Integer, ArrayList <PlayerReferee> > entry : scores.entrySet()){
				scoreFinal.add(entry.getValue());
			}
			players.clear();
		}
		if(players.size() == 1){
			continuer = false;
			PlayerReferee winner = players.get(0);
			winner.PrintErr("GAGNÉ !");
			ArrayList <PlayerReferee> array = new ArrayList <PlayerReferee>();
			array.add(winner);
			scoreFinal.add(array);
		}
	}
	
	private void PrintClassement(){
		int i = 1;
		for(ArrayList <PlayerReferee> array : scoreFinal){
			System.out.print(String.valueOf(i) + " : ");
			for(PlayerReferee player : array){
				System.out.print("joueur" + String.valueOf(player.GetId()) + " ");
			}
			System.out.println("");
			i++;
		}
	}

	abstract void initReferee(int playerCount, Properties prop) throws InvalidFormatException;

	abstract Properties getConfiguration();

	abstract void prepare(int round);

	abstract int getExpectedOutputLineCountForPlayer(int playerIdx);

	abstract void handlePlayerOutput(int frame, int round, int playerIdx, String[] outputs) throws InvalidInputException, LostException, WinException;

	abstract void updateGame(int round) throws GameOverException;

	abstract void populateMessages(Properties p);

	abstract String[] getInitInputForPlayer(int playerIdx);

	abstract String[] getInputForPlayer(int round, int playerIdx);

	abstract String[] getInitDataForView();

	abstract String[] getFrameDataForView(int round, int frame, boolean keyFrame);

	abstract String getGameName();

	abstract String getHeadlineAtGameStartForConsole();

	abstract int getMinimumPlayerCount();

	abstract boolean showTooltips();

	abstract String[] getPlayerActions(int playerIdx, int round);

	abstract boolean isPlayerDead(int playerIdx);

	abstract String getDeathReason(int playerIdx);

	abstract int getScore(int playerIdx);

	abstract String[] getGameSummary(int round);

	abstract void setPlayerTimeout(int frame, int round, int playerIdx);

	abstract int getMaxRoundCount(int playerCount);

	abstract int getMillisTimeForRound();


	protected void addToolTip(int idPlayer, String msg){}
	protected String translate(String a, int b, int c, int d){return"";}
	protected String translate(String a, int b, int c){return"";}

}
