import java.io.FileNotFoundException;

public class GameOfLifeMain {
    public static void main(String[] args) {
        try {
            GameConfig gameConfig = GameConfigLoader.loadFromFile("configFile.txt");
            GameBoard board = gameConfig.getGameBoard();
            int iterations = gameConfig.getIterations();

            int numberOfThreads = Runtime.getRuntime().availableProcessors();
            ParallelProcessor processor = new ParallelProcessor(board, numberOfThreads);

            for (int i = 0; i < iterations; i++) {
                processor.startProcessing();
                Visualization.display(board);
                Thread.sleep(500); // Opóźnienie
            }

        } catch (FileNotFoundException e) {
            System.err.println("Konfiguracyjny plik nie znaleziony.");
            e.printStackTrace();
        } catch (InterruptedException e) {
            System.err.println("Przerwano działanie programu.");
            e.printStackTrace();
        }
    }
}
