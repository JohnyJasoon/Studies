public class GameBoard {
    private Cell[][] board;
    private boolean[][] nextState;
    private final int rows;
    private final int cols;

    public GameBoard(int rows, int cols) {
        this.rows = rows;
        this.cols = cols;
        this.board = new Cell[rows][cols];
        this.nextState = new boolean[rows][cols];
        initializeBoard();
    }

    private void initializeBoard() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                board[i][j] = new Cell(false);
            }
        }
    }

    public Cell getCell(int row, int col) {
        return board[row][col];
    }

    public int getRows() {
        return rows;
    }

    public int getCols() {
        return cols;
    }

    public void calculateNextState(int row, int col) {
        int aliveNeighbors = countAliveNeighbors(row, col);
        nextState[row][col] = board[row][col].isAlive() ? (aliveNeighbors == 2 || aliveNeighbors == 3) : (aliveNeighbors == 3);
    }

    public void updateBoard() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                board[i][j].setAlive(nextState[i][j]);
            }
        }
    }

    private int countAliveNeighbors(int row, int col) {
        int count = 0;
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (i == 0 && j == 0) continue;
                int r = (row + i + rows) % rows;
                int c = (col + j + cols) % cols;
                if (board[r][c].isAlive()) count++;
            }
        }
        return count;
    }
}
