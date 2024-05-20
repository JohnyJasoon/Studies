import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.CyclicBarrier;
import java.util.concurrent.TimeUnit;

public class ParallelProcessor {
    private final GameBoard board;
    private final int threadCount;
    private final ExecutorService executorService;
    private final CyclicBarrier barrier;

    public ParallelProcessor(GameBoard board, int threadCount) {
        this.board = board;
        this.threadCount = threadCount;
        this.executorService = Executors.newFixedThreadPool(threadCount);
        this.barrier = new CyclicBarrier(threadCount, board::updateBoard);
    }

    public void startProcessing() {
        for (int i = 0; i < threadCount; i++) {
            int startCol = i * (board.getCols() / threadCount);
            int endCol = (i + 1) * (board.getCols() / threadCount);
            executorService.submit(new Worker(i, startCol, endCol));
        }
    }

    public void shutdown() throws InterruptedException {
        executorService.shutdown();
        executorService.awaitTermination(Long.MAX_VALUE, TimeUnit.NANOSECONDS);
    }

    private class Worker implements Runnable {
        private final int threadId;
        private final int startCol;
        private final int endCol;

        public Worker(int threadId, int startCol, int endCol) {
            this.threadId = threadId;
            this.startCol = startCol;
            this.endCol = endCol;
        }

        @Override
        public void run() {
            try {
                int processedRows = 0;
                for (int i = 0; i < board.getRows(); i++) {
                    for (int j = startCol; j < endCol; j++) {
                        board.calculateNextState(i, j);
                        processedRows++;
                    }
                }
                barrier.await();

                // Raportowanie działania wątku
                System.out.printf("tid %d: rows: 0:%d (%d) cols: %d:%d (%d)%n", threadId, board.getRows() - 1, board.getRows(), startCol, endCol - 1, processedRows);
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }
}
