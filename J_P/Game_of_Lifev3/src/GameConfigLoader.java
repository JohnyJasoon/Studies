import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class GameConfigLoader {
    public static GameConfig loadFromFile(String filename) throws FileNotFoundException {
        Scanner scanner = new Scanner(new File(filename));

        int rows = scanner.nextInt();
        int cols = scanner.nextInt();
        int iterations = scanner.nextInt();

        GameBoard board = new GameBoard(rows, cols);

        int numberOfLiveCells = scanner.nextInt();
        for (int i = 0; i < numberOfLiveCells; i++) {
            int row = scanner.nextInt();
            int col = scanner.nextInt();
            board.getCell(row, col).setAlive(true);
        }

        scanner.close();
        return new GameConfig(board, iterations);
    }
}
