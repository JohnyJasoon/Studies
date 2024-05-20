public class GameConfig {
    private final GameBoard gameBoard;
    private final int iterations;

    public GameConfig(GameBoard gameBoard, int iterations) {
        this.gameBoard = gameBoard;
        this.iterations = iterations;
    }

    public GameBoard getGameBoard() {
        return gameBoard;
    }

    public int getIterations() {
        return iterations;
    }
}
