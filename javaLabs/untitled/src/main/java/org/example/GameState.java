package org.example;

public class GameState {
    private int score = 0;
    private Mode gameMode = Mode.SCATTER;
    private int lives = 3;
    private int level = 1;
    private int totalDots = 0;

    public boolean isGameOver() {
        return isGameOver;
    }

    public void setGameOver(boolean gameOver) {
        isGameOver = gameOver;
    }

    private boolean isGameOver = false;

    public int getMaxDotsAtLevel() {
        return maxDotsAtLevel;
    }

    public void setScore(int score) {
        this.score = score;
    }
    private final  int maxDotsAtLevel = 128;//кол-во точек которые съел на уровне

    public void reset() {
        this.gameMode = Mode.SCATTER;
        this.lives = 3;
        this.level = 1;
        this.score = 0;
        this.totalDots = 0;
    }

    public void resetNewLevel() {
        this.gameMode = Mode.SCATTER;
        this.totalDots = 0;

    }

    public int getScore() {
        return score;
    }

    public void addScore(int points) {
        this.score += points;
    }

    public void addTotalDots(int dots) {
        this.totalDots += dots;
    }

    public void lostLife() {
        if (lives > 0){
            lives--;
        }
    }

    public int getLives() {
        return lives;
    }

    public int getLevel() {
        return level;
    }

    public Mode getGameMode() {
        return gameMode;
    }

    public void setGameMode(Mode gameMode) {
        this.gameMode = gameMode;
    }

    public void setLevel(int level) {
        this.level = level;
    }

    public int getTotalDots() {
        return totalDots;
    }

}

