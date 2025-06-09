package org.example;

import java.util.ArrayList;

public class ModeManager {
    private final GameState gameState;
    private final ArrayList<GhostMoveController> ghostControllers;
    private final double[] modeSchedule = {5, 20, 5, 20, 3, 20, 3};
    private double modeTimer = modeSchedule[0];
    private int modeIndex = 0;
    private double frightenedTimer;
    private Mode modeBeforeFrightened;

    public ModeManager(GameState gameState, ArrayList<GhostMoveController> ghostControllers) {
        this.gameState = gameState;
        this.ghostControllers = ghostControllers;
    }

    public void update(double tpf) {
        if (gameState.getGameMode() != Mode.FRIGHTENED) {
            modeTimer -= tpf;
            if (modeTimer <= 0) {
                modeIndex++;
                if (modeIndex < modeSchedule.length) {
                    gameState.setGameMode((modeIndex % 2 == 0) ? Mode.SCATTER : Mode.CHASE);
                    modeTimer = modeSchedule[modeIndex];
                } else {
                    gameState.setGameMode(Mode.CHASE);
                    modeTimer = Double.MAX_VALUE;
                }
            }
        } else {
            frightenedTimer -= tpf;
            if (frightenedTimer <= 0) {
                for (GhostMoveController ghostController : ghostControllers) {
                    ghostController.offFrightenedMode();
                }
                gameState.setGameMode(modeBeforeFrightened);
            }
        }
    }

    public void startFrightenedMode(Mode currentMode) {
        if (gameState.getGameMode() != Mode.FRIGHTENED) {
            modeBeforeFrightened = currentMode;
        }
        for (GhostMoveController ghostController : ghostControllers) {
            ghostController.onFrightenedMode();
        }
        gameState.setGameMode(Mode.FRIGHTENED);
        frightenedTimer = 10;
    }

    public void reset() {
        modeTimer = modeSchedule[0];
        modeIndex = 0;
    }
}