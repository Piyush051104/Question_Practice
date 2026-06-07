
package OOPS.TicTacToe;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

enum PieceType{
    X,
    O
}

abstract class Figure{
    private PieceType type;

    public Figure(PieceType type){
        this.type = type;
    }

    public PieceType getPieceType(){
        return type;
    }
}

class Circle extends Figure{
    public Circle(){
        super(PieceType.O);
    }
}

class Cross extends Figure{
    public Cross(){
        super(PieceType.X);
    }
}

class Box {
    private int boxid;
    private Figure figure;

    public Box(int id){
        this.boxid = id;
        this.figure = null;
    }

    public void setFigure(Figure fig){
        if (!isEmpty()) {
            throw new RuntimeException("Box already filled!");
        }
        figure = fig;
    }
    
    public void remFigure(){
        figure = null;
    }

    public Figure getFigureBox(){
        return figure;
    }
    public boolean isEmpty() {
        return figure == null;
    }
    
}

class Player{
    private int id;
    private String name;
    private Figure figure;

    public Player(int id,String name,Figure figure){
        this.id = id;
        this.name = name;
        this.figure = figure;
    }

    public void makeMove(Box box){
        box.setFigure(figure);
    }

    public String getName(){
        return name;
    }
    public Figure getFigure() {
        return figure;
    }
}

class Board {
    private static Board instance;
    private Box[][] board;
    private static final int SIZE = 3;

    // private constructor
    private Board() {
        initBoard();
    }

    // double checked locking
    public static Board getInstance() {
        if (instance == null) {
            synchronized (Board.class) {
                if (instance == null) {
                    instance = new Board();
                }
            }
        }
        return instance;
    }

    // creates 9 Box objects
    private void initBoard() {
        board = new Box[SIZE][SIZE];
        int id = 0;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                board[i][j] = new Box(id++);
            }
        }
    }

    // returns the grid
    public Box[][] getBoard() {
        return board;
    }

    // resets board for new game
    public void resetBoard() {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                board[i][j].remFigure();
            }
        }
    }

    // prints current state
    public void printBoard() {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j].isEmpty()) {
                    System.out.print(" _ ");
                } else {
                    System.out.print(" " + 
                    board[i][j].getFigureBox()
                               .getPieceType() + " ");
                }
            }
            System.out.println();
        }
    }
}

interface WinningStrategy {
    boolean checkWin(Board board, Player player);
}

class RowWinStrategy implements WinningStrategy {

    @Override
    public boolean checkWin(Board board, Player player) {
        Box[][] grid = board.getBoard();
        PieceType playerType = player.getFigure().getPieceType();

        for (int i = 0; i < 3; i++) {          // each row
            boolean rowWin = true;
            for (int j = 0; j < 3; j++) {      // each col in that row
                if (grid[i][j].isEmpty() || 
                    grid[i][j].getFigureBox().getPieceType() != playerType) {
                    rowWin = false;
                    break;
                }
            }
            if (rowWin) return true;
        }
        return false;
    }
}
class ColumnWinStrategy implements WinningStrategy {

    @Override
    public boolean checkWin(Board board, Player player) {
        Box[][] grid = board.getBoard();
        PieceType playerType = player.getFigure().getPieceType();

        for (int j = 0; j < 3; j++) {          // each col
            boolean colWin = true;
            for (int i = 0; i < 3; i++) {      // each row in that col
                if (grid[i][j].isEmpty() || 
                    grid[i][j].getFigureBox().getPieceType() != playerType) {
                    colWin = false;
                    break;
                }
            }
            if (colWin) return true;
        }
        return false;
    }
}
class DiagonalWinStrategy implements WinningStrategy {

    @Override
    public boolean checkWin(Board board, Player player) {
        Box[][] grid = board.getBoard();
        PieceType playerType = player.getFigure().getPieceType();

       
        boolean diag1 = true;
        for (int i = 0; i < 3; i++) {
            if (grid[i][i].isEmpty() || 
                grid[i][i].getFigureBox().getPieceType() != playerType) {
                diag1 = false;
                break;
            }
        }

       
        boolean diag2 = true;
        for (int i = 0; i < 3; i++) {
            if (grid[i][2-i].isEmpty() || 
                grid[i][2-i].getFigureBox().getPieceType() != playerType) {
                diag2 = false;
                break;
            }
        }

        return diag1 || diag2;
    }
}

class Game {
    private List<WinningStrategy> strategies;
    private List<Player> players;
    private int currentPlayer;
    private Board board;
    private Player winner;

    public Game(List<Player> players, List<WinningStrategy> strategies) {
        this.strategies = strategies;
        this.players = players;
        this.board = Board.getInstance(); // Singleton!
        this.winner = null;
        this.currentPlayer = 0;
    }

    
    public void startGame() {
        Scanner sc = new Scanner(System.in);

        while (true) {
            board.printBoard();

            Player current = players.get(currentPlayer);
            System.out.println(current.getName() + "'s turn! Enter row and col (0-2): ");

            int row = sc.nextInt();
            int col = sc.nextInt();

            // validate input
            if (row < 0 || row > 2 || col < 0 || col > 2) {
                System.out.println("Invalid input! Try again.");
                continue;
            }

            Box box = board.getBoard()[row][col];

            // check if box is already filled
            if (!box.isEmpty()) {
                System.out.println("Box already filled! Try again.");
                continue;
            }

            // make the move
            current.makeMove(box);

            // check winner
            if (checkWinner(current)) {
                winner = current;
                break;
            }

            // check draw
            if (isDraw()) {
                break;
            }

            // switch turn
            // 0→1→0→1 keeps alternating
            currentPlayer = (currentPlayer + 1) % players.size();
        }

        // game over
        board.printBoard();
        printResult();
    }

    // ─── checks all strategies for current player ─────
    private boolean checkWinner(Player player) {
        for (WinningStrategy strategy : strategies) {
            if (strategy.checkWin(board, player)) {
                return true;
            }
        }
        return false;
    }

    // ─── checks if all boxes are filled ───────────────
    private boolean isDraw() {
        Box[][] grid = board.getBoard();
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (grid[i][j].isEmpty()) {
                    return false; // still empty box exists
                }
            }
        }
        return true; // all boxes filled, no winner
    }

    // ─── prints final result ───────────────────────────
    private void printResult() {
        if (winner != null) {
            System.out.println("🎉 " + winner.getName() + " wins!");
        } else {
            System.out.println("It's a DRAW!");
        }
    }
}

public class TicTacToe {

    public static void main(String[] args){
        
       
        Player p1 = new Player(1, "Piyush", new Circle());
        Player p2 = new Player(2, "Rahul", new Cross());
        List<Player> players = new ArrayList<>();
        players.add(p1);
        players.add(p2);

        List<WinningStrategy> strategies = new ArrayList<>();
        strategies.add(new ColumnWinStrategy());
        strategies.add(new RowWinStrategy());
        strategies.add(new DiagonalWinStrategy());
        Game g1 = new Game(players, strategies);

        g1.startGame();

        
    }
}
