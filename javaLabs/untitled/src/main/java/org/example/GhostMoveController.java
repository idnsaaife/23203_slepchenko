package org.example;

import com.almasb.fxgl.entity.Entity;
import javafx.geometry.Point2D;
import static com.almasb.fxgl.dsl.FXGL.spawn;

import java.util.*;


public abstract class GhostMoveController extends MoveController implements GhostMover {
    public void setSpawnDelay(double spawnDelay) {
        this.spawnDelay = spawnDelay;
    }

    private double spawnDelay = 0.0;

    public boolean isAlive() {
        return isAlive;
    }

    private boolean isAlive = false;
    private double delayTimer = 0;

    public void setEntity(Entity entity) {
        this.entity = entity;
    }
    private double speed = 200 * 0.25;
    private Entity entity;

    public Entity getEntity() {
        return entity;
    }

    public double getSpeed() {
        return speed;
    }

    public void setSpeed(double speed) {
        this.speed = speed;
    }

    public GhostMoveController(Entity entity) {
        super(entity);
        this.entity = entity;
    }

    public List<Point2D> bfs(Point2D start, Point2D target) {
        int targetX = (int) target.getX();
        int targetY = (int) target.getY();

        if (targetX < 0 || targetX >= Size.MAPWIDTH.size || targetY < 0 || targetY >= Size.MAPHEIGHT.size) {
            targetX = Math.max(0, Math.min(targetX, Size.MAPWIDTH.size - 1));
            targetY = Math.max(0, Math.min(targetY, Size.MAPHEIGHT.size - 1));
            target = new Point2D(targetX, targetY);
        }

        Queue<Point2D> queue = new LinkedList<>();
        HashMap<Point2D, Point2D> cameFrom = new HashMap<>();
        HashSet<Point2D> visited = new HashSet<>();

        queue.add(start);
        visited.add(start);
        cameFrom.put(start, null);

        Direction[] directions = {Direction.UP, Direction.DOWN, Direction.LEFT, Direction.RIGHT};

        while (!queue.isEmpty()) {
            Point2D current = queue.poll();
            if (current.equals(target)) {
                List<Point2D> path = new ArrayList<>();
                while (current != null) {
                    path.add(current);
                    current = cameFrom.get(current);
                }
                Collections.reverse(path);
                return path;
            }
            for (Direction dir : directions) {
                int newX = (int) (current.getX() + dir.getDx());
                int newY = (int) (current.getY() + dir.getDy());
                Point2D neighbor = new Point2D(newX, newY);
                if (Map.getCurrentMapObject(newY, newX) == MapObjects.WALL || Map.getCurrentMapObject(newY, newX) == MapObjects.GHOST_HOUSE)
                    continue;
                if (!visited.contains(neighbor)) {
                    queue.add(neighbor);
                    visited.add(neighbor);
                    cameFrom.put(neighbor, current);
                }
            }
        }
        return Collections.emptyList();
    }

    protected void move(double tpf, Point2D target) {
        double x = entity.getX();
        double y = entity.getY();
        Point2D start = new Point2D(
                (int)(x / Size.WALLSIZE.size),
                (int)(y / Size.WALLSIZE.size)
        );
        List<Point2D> path = bfs(start, target);
        if (path.size() > 1) {
            Point2D nextStep = path.get(1);
            double dx = nextStep.getX() - start.getX();
            double dy = nextStep.getY() - start.getY();
            if (dx == 1) setFutureDirection(Direction.RIGHT);
            else if (dx == -1) setFutureDirection(Direction.LEFT);
            else if (dy == 1) setFutureDirection(Direction.DOWN);
            else if (dy == -1) setFutureDirection(Direction.UP);

        }
        if (PositionController.isAtGridCenter(x, y) && PositionController.canTurn(getFutureDirection(), x, y) && getFutureDirection() != getCurrentDirection()) {
            changeRotation();
            snapToGrid(x,y);
            x = getEntity().getX();
            y = getEntity().getY();
        }
        double newX = x;
        double newY = y;
        newX += getCurrentDirection().getDx() * speed * tpf;
        newY += getCurrentDirection().getDy() * speed * tpf;
        Point2D nextGrid = countGrid(newX, newY);
        int gridX = (int) nextGrid.getX();
        int gridY = (int) nextGrid.getY();
        boolean canMove = gridX >= 0 && gridX < Size.MAPWIDTH.size && gridY >= 0 && gridY < Size.MAPHEIGHT.size && Map.getCurrentMapObject(gridY, gridX) != MapObjects.WALL && Map.getCurrentMapObject(gridY, gridX) != MapObjects.GHOST_HOUSE;
        if (!canMove) {
            Point2D corrected = PositionController.correctGrid(newX, newY, gridX, gridY);
            newX = corrected.getX();
            newY = corrected.getY();
        }
        newX = Math.max(Size.ENTITYRADIUS.size, Math.min(newX, Size.MAPWIDTH.size * Size.WALLSIZE.size - Size.ENTITYRADIUS.size));
        newY = Math.max(Size.ENTITYRADIUS.size, Math.min(newY, Size.MAPHEIGHT.size * Size.WALLSIZE.size - Size.ENTITYRADIUS.size));
        getEntity().setPosition(newX, newY);
    }

    public boolean catchPacman(Point2D pacmanPos) {
        Point2D ghostPos = new Point2D(entity.getX(), entity.getY());
        double dx = pacmanPos.getX() - ghostPos.getX();
        double dy = pacmanPos.getY() - ghostPos.getY();
        double distance = Math.sqrt(dx * dx + dy * dy);
        return distance <=  1.17 * Size.ENTITYRADIUS.size;
    }

    public void onFrightenedMode() {
        Entity colorGhost = getEntity();
        Point2D currentPosition = colorGhost.getPosition();
        colorGhost.removeFromWorld();
        Entity frightenedGhost = spawn("frightenedGhost", currentPosition.getX(), currentPosition.getY());
        this.entity = frightenedGhost;
    }

    @Override
    public void reset() {
        getEntity().setPosition(9*Size.WALLSIZE.size + Size.WALLSIZE.size/2, 7*Size.WALLSIZE.size + Size.WALLSIZE.size/2);
        isAlive = false;
        delayTimer = 0;
    }

    protected void revive(double tpf) {
        if (!isAlive) {
            delayTimer += tpf;
            if (delayTimer >= spawnDelay) {
                isAlive = true;
            }
        }
    }
    public Direction chooseBestDirectionToFright(Point2D pacmanPos, double tpf) {
        Double maxDistance = Double.MIN_VALUE;
        Direction bestDir = Direction.UP;
        Direction[] directions = {Direction.UP, Direction.DOWN, Direction.LEFT, Direction.RIGHT};
        for (Direction dir : directions) {
            double newX = entity.getX() + dir.getDx() * speed * tpf;
            double newY = entity.getY() + dir.getDy() * speed * tpf;
            double dx = pacmanPos.getX() - newX;
            double dy = pacmanPos.getY() - newY;
            double distance = Math.sqrt(dx * dx + dy * dy);
            Point2D nextGrid = countGrid(newX, newY);
            int gridX = (int) nextGrid.getX();
            int gridY = (int) nextGrid.getY();
            boolean canMove = gridX >= 0 && gridX < Size.MAPWIDTH.size && gridY >= 0 && gridY < Size.MAPHEIGHT.size && Map.getCurrentMapObject(gridY, gridX) != MapObjects.WALL && Map.getCurrentMapObject(gridY, gridX) != MapObjects.GHOST_HOUSE;
            if (distance > maxDistance && canMove) {
                maxDistance = distance;
                bestDir = dir;
            }
        }
        return bestDir;
    }

    @Override
    public void frightenedMove(double tpf, Point2D pacmanPos, Direction pacmanDir) {
        revive(tpf);
        if (!isAlive()) {
            return;
        }
        double x = entity.getX();
        double y = entity.getY();
        if (PositionController.isAtGridCenter(x, y)) {
            Direction bestDir = chooseBestDirectionToFright(pacmanPos, tpf);
            if (PositionController.canTurn(bestDir, x, y)) {
                setFutureDirection(bestDir);
                changeRotation();
                snapToGrid(x, y);
                x = entity.getX();
                y = entity.getY();

            }
        }
        double newX = x;
        double newY = y;
        newX += getCurrentDirection().getDx() * speed * tpf;
        newY += getCurrentDirection().getDy() * speed * tpf;
        Point2D nextGrid = countGrid(newX, newY);
        move(tpf, nextGrid);
    }

    public abstract void offFrightenedMode();
}
