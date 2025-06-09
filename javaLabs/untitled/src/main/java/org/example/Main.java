package org.example;

import com.almasb.fxgl.app.GameApplication;
import com.almasb.fxgl.app.GameSettings;
import com.almasb.fxgl.entity.Entity;
import javafx.scene.paint.Color;
import javafx.scene.input.KeyCode;

import static com.almasb.fxgl.dsl.FXGL.*;

public class Main extends GameApplication {
    private PacManController pacManController;
    private GameLogicController gameLogicController;
    private GameState gameState = new GameState();
    private UIManager uiManager = new UIManager();
    private final double wallSize = Size.WALLSIZE.size;
    private final int width = (int) wallSize * Size.MAPWIDTH.size;
    private final int height = (int) wallSize * Size.MAPHEIGHT.size;


    @Override
    protected void initSettings(GameSettings settings) {
        settings.setWidth(width);
        settings.setHeight(height);
        settings.setTitle("Pac-Man");
    }

    @Override
    protected void initGame() {
        getGameScene().setBackgroundColor(Color.BLACK);
        getGameWorld().addEntityFactory(new PacManFactory());
        Map.init();
        initGameController();
    }

    private void initGameController() {
        Entity pacMan = spawn("pacman", wallSize + wallSize / 2, wallSize + wallSize / 2);
        Entity blinky = spawn("blinky", 9*wallSize + wallSize/2, 7*wallSize + wallSize/2);
        Entity pinky = spawn("pinky", 9*wallSize + wallSize/2, 7*wallSize + wallSize/2);
        Entity clyde = spawn("clyde", 9*wallSize + wallSize/2, 7*wallSize + wallSize/2);
        pacManController = new PacManController(pacMan);
        gameLogicController = new GameLogicController(pacManController, blinky, pinky, clyde, gameState);
    }

    @Override
    protected void initInput() {
        onKey(KeyCode.UP, () -> {
            if (!gameState.isGameOver()) {
                pacManController.setFutureDirection(Direction.UP);
            }
        });
        onKey(KeyCode.DOWN, () -> {
            if (!gameState.isGameOver()) {
                pacManController.setFutureDirection(Direction.DOWN);
            }
        });
        onKey(KeyCode.LEFT, () -> {
            if (!gameState.isGameOver()) {
                pacManController.setFutureDirection(Direction.LEFT);
            }
        });
        onKey(KeyCode.RIGHT, () -> {
            if (!gameState.isGameOver()) {
                pacManController.setFutureDirection(Direction.RIGHT);
            }
        });
        onKey(KeyCode.ENTER, () -> {
            if (gameState.isGameOver()) {
                restartGame();
            }
        });
    }

    private void restartGame() {
        gameLogicController.restart();
        uiManager.reset();
    }

    @Override
    protected void initUI() {
        uiManager.init();
    }


    @Override
    protected void onUpdate(double tpf) {
        if (gameState.isGameOver())  {
            uiManager.showGameOver();
            return;
        }
        uiManager.update(gameState);
        gameLogicController.update(tpf);
        uiManager.update(gameState);
    }

    public static void main(String[] args) {
        launch(args);
    }
}
