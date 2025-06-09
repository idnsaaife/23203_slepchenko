package org.example;

import com.almasb.fxgl.entity.Entity;
import javafx.geometry.Point2D;

import java.util.ArrayList;

public class GameLogicController {
    private final GameState gameState;
    private final PacManController pacManController;
    private final ArrayList<GhostMoveController> ghostControllers;
    private final ModeManager modeManager;


    public GameLogicController(PacManController pacManController, Entity blinky, Entity pinky, Entity clyde, GameState gameState) {
        this.pacManController = pacManController;
        this.ghostControllers = new ArrayList<>();
        ghostControllers.add(new BlinkyController(blinky));
        ghostControllers.add(new PinkyController(pinky));
        ghostControllers.add(new ClydeController(clyde));
        this.gameState = gameState;
        this.modeManager = new ModeManager(gameState, ghostControllers);
    }

    public void update(double tpf) {
        modeManager.update(tpf);
        pacManController.move(tpf);

        if (pacManController.eatDot()) {
            gameState.addScore(15);
            gameState.addTotalDots(1);
        }

        if (pacManController.eatBigDot()) {
            modeManager.startFrightenedMode(gameState.getGameMode());
        }

        for (GhostMoveController ghostController : ghostControllers) {
            switch (gameState.getGameMode()) {
                case CHASE  :
                    ghostController.chaseMove(tpf, new Point2D(pacManController.getPacMan().getX(), pacManController.getPacMan().getY()), pacManController.getCurrentDirection());
                    if (ghostController.catchPacman(new Point2D(pacManController.getPacMan().getX(), pacManController.getPacMan().getY()))) {
                        onPacmanCaught();
                        return;
                    }
                    break;
                case SCATTER :
                    ghostController.scatterMove(tpf);
                    if (ghostController.catchPacman(new Point2D(pacManController.getPacMan().getX(), pacManController.getPacMan().getY()))) {
                        onPacmanCaught();
                        return;
                    }
                    break;
                case FRIGHTENED :
                    ghostController.frightenedMove(tpf, new Point2D(pacManController.getPacMan().getX(), pacManController.getPacMan().getY()), pacManController.getCurrentDirection());
                    if (pacManController.catchGhost(new Point2D(ghostController.getEntity().getX(),ghostController.getEntity().getY() ))) {
                        ghostController.reset();
                        pacManController.setScore(gameState.getScore() + 100);
                        gameState.setScore(pacManController.getScore());
                    };
                    break;
            }
        }

        if (gameState.getTotalDots() == gameState.getMaxDotsAtLevel()) {
            gameState.setLevel(gameState.getLevel() + 1);
            for (GhostMoveController ghostController : ghostControllers) {
                    ghostController.setSpeed((ghostController.getSpeed() < pacManController.getSpeed())  ? ghostController.getSpeed() + pacManController.getSpeed() * 0.25 : ghostController.getSpeed());
                    ghostController.reset();
                    if (gameState.getGameMode() == Mode.FRIGHTENED) {
                        ghostController.offFrightenedMode();
                    }
            }
            Map.reset();
            gameState.resetNewLevel();
            pacManController.reset();
            modeManager.reset();
        }
    }


    private void onPacmanCaught() {
        gameState.lostLife();
        pacManController.reset();
        for (GhostMoveController ghostController : ghostControllers) {
            ghostController.reset();
        }

     if (gameState.getLives() == 0) {
            gameState.setGameOver(true);

    }
    }

    public void restart() {
        gameState.reset();
        pacManController.setScore(0);
        modeManager.reset();
        Map.reset();
        gameState.setGameOver(false);
    }


}
