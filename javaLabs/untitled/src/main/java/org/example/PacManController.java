package org.example;
import javafx.geometry.Point2D;
import com.almasb.fxgl.entity.Entity;

public class PacManController extends MoveController implements PacManMover {
    private final Entity pacMan;
    private int score = 0;

    public double getSpeed() {
        return speed;
    }

    private final double speed = 200;
    private final double pacManRadius = Size.ENTITYRADIUS.size;

    public int getScore() {
        return score;
    }
    public PacManController(Entity pacMan) {
        super(pacMan);
        this.pacMan = pacMan;
    }

    @Override
    public void move(double tpf) {
        double x = pacMan.getX();
        double y = pacMan.getY();
        if (PositionController.isAtGridCenter(x, y) && PositionController.canTurn(getFutureDirection(), x, y) && getFutureDirection() != getCurrentDirection()) {
            changeRotation();
            snapToGrid(x,y);
            x = pacMan.getX();
            y = pacMan.getY();
        }
        double newX = x;
        double newY = y;
        newX += getCurrentDirection().getDx() * speed * tpf;
        newY += getCurrentDirection().getDy() * speed * tpf;
        Point2D nextGrid = countGrid(newX, newY);
        int gridX = (int) nextGrid.getX();
        int gridY = (int) nextGrid.getY();
        boolean canMove = gridX >= 0 && gridX < Size.MAPWIDTH.size && gridY >= 0 && gridY < Size.MAPHEIGHT.size && Map.getCurrentMapObject(gridY, gridX) != MapObjects.WALL && Map.getCurrentMapObject(gridY, gridX) != MapObjects.GHOST_HOUSE && Map.getCurrentMapObject(gridY, gridX) != MapObjects.GHOST_GATE;
        if (!canMove) {
            Point2D corrected = PositionController.correctGrid(newX, newY, gridX, gridY);
            newX = corrected.getX();
            newY = corrected.getY();
        }
        newX = Math.max(pacManRadius, Math.min(newX, Size.MAPWIDTH.size * Size.WALLSIZE.size - pacManRadius));
        newY = Math.max(pacManRadius, Math.min(newY, Size.MAPHEIGHT.size * Size.WALLSIZE.size - pacManRadius));
        pacMan.setPosition(newX, newY);
    }

    public void setScore(int score) {
        this.score = score;
    }

    public boolean eatDot() {
        double x = pacMan.getX();
        double y = pacMan.getY();
        Point2D grid = countGrid(x, y);
        int gridX = (int) Math.floor(x / Size.WALLSIZE.size);
        int gridY = (int) Math.floor(y / Size.WALLSIZE.size);
        Entity currentGridEntity = Map.getEntity((int) grid.getY(), (int) grid.getX());
        if (currentGridEntity == null) return false;
        boolean ateDot = isEatDot(currentGridEntity, x, y);

        if (Map.getCurrentMapObject(gridY, gridX) == MapObjects.DOT && ateDot) {
            setScore(score + 15);
            currentGridEntity.removeFromWorld();
            Map.removeEntityFromGrid(gridY, gridX);
            Map.setMapObject(gridY, gridX, MapObjects.EMPTY);
            return true;
        }
        return false;
    }


    private boolean isEatDot(Entity currentGridEntity, double x, double y) {
        if (currentGridEntity == null) return false;
        double dotPositionX = currentGridEntity.getX();
        double dotPositionY = currentGridEntity.getY();
        double distance = Math.sqrt(Math.pow(x - dotPositionX, 2) + Math.pow(y - dotPositionY, 2));
        return distance < pacManRadius + 5;
    }

    public boolean eatBigDot() {
        double x = pacMan.getX();
        double y = pacMan.getY();
        int gridX = (int) Math.floor(x / Size.WALLSIZE.size);
        int gridY = (int) Math.floor(y / Size.WALLSIZE.size);

        Entity currentGridEntity = Map.getEntity(gridY, gridX);
        if (currentGridEntity == null) return false;
        if (isEatDot(currentGridEntity, x, y) && Map.getCurrentMapObject(gridY, gridX) == MapObjects.BIG_DOT) {
            currentGridEntity.removeFromWorld();
            Map.removeEntityFromGrid(gridY, gridX);
            Map.setMapObject(gridY, gridX, MapObjects.EMPTY);
            return true;
        }
        return false;
    }

    public Entity getPacMan() {
        return pacMan;
    }
    public boolean catchGhost(Point2D ghostPos) {
        Point2D pacmanPos = new Point2D(pacMan.getX(), pacMan.getY());
        double dx = pacmanPos.getX() - ghostPos.getX();
        double dy = pacmanPos.getY() - ghostPos.getY();
        double distance = Math.sqrt(dx * dx + dy * dy);
        return distance <= 1.2 * Size.ENTITYRADIUS.size;
    }

    @Override
    public void reset() {
        pacMan.setPosition(Size.WALLSIZE.size + Size.WALLSIZE.size / 2, Size.WALLSIZE.size + Size.WALLSIZE.size / 2);
    }
}

