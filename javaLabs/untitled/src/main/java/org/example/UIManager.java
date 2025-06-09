package org.example;

import com.almasb.fxgl.dsl.FXGL;
import javafx.scene.text.Text;

public class UIManager {
    private Text scoreText;
    private Text livesText;
    private Text levelText;
    private Text gameOverText;

    public void init() {
        scoreText = FXGL.getUIFactoryService().newText("Score: 0");
        livesText = FXGL.getUIFactoryService().newText("Lives: 3");
        levelText = FXGL.getUIFactoryService().newText("Level: 1");
        scoreText.setTranslateX(10);
        scoreText.setTranslateY(20);
        livesText.setTranslateX(10);
        livesText.setTranslateY(40);
        levelText.setTranslateX(10);
        levelText.setTranslateY(60);
        FXGL.getGameScene().addUINodes(scoreText, livesText, levelText);
    }

    public void update(GameState state) {
        scoreText.setText("Score: " + state.getScore());
        livesText.setText("Lives: " + state.getLives());
        levelText.setText("Level: " + state.getLevel());
    }

    public void showGameOver() {
        gameOverText = FXGL.getUIFactoryService().newText("Game Over! Press ENTER to restart");
        gameOverText.setTranslateX(200);
        gameOverText.setTranslateY(300);
        FXGL.getGameScene().addUINode(gameOverText);
    }

    public void reset() {
        FXGL.getGameScene().clearUINodes();
        scoreText = FXGL.getUIFactoryService().newText("Score: 0");
        livesText = FXGL.getUIFactoryService().newText("Lives: 3");
        levelText = FXGL.getUIFactoryService().newText("Level: 1");
        scoreText.setTranslateX(10);
        scoreText.setTranslateY(20);
        livesText.setTranslateX(10);
        livesText.setTranslateY(40);
        levelText.setTranslateX(10);
        levelText.setTranslateY(60);
        FXGL.getGameScene().addUINodes(scoreText, livesText, levelText);

    }
}

