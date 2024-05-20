public class Visualization {
    public static void display(GameBoard board) {
        clearConsole();
        for (int i = 0; i < board.getRows(); i++) {
            for (int j = 0; j < board.getCols(); j++) {
                System.out.print(board.getCell(i, j).isAlive() ? "X" : ".");
            }
            System.out.println();
        }
    }

    private static void clearConsole() {
        try {
            final String os = System.getProperty("os.name");
            if (os.contains("Windows")) {
                new ProcessBuilder("cmd", "/c", "cls").inheritIO().start().waitFor();
            } else {
                System.out.print("\033[H\033[2J");
                System.out.flush();
            }
        } catch (Exception e) {
            System.err.println("Błąd podczas czyszczenia konsoli: " + e.getMessage());
        }
    }
}
