/**
 * This class stores the basic state necessary for the A* algorithm to compute a
 * path across a map.  This state includes a collection of "open waypoints" and
 * another collection of "closed waypoints."  In addition, this class provides
 * the basic operations that the A* pathfinding algorithm needs to perform its
 * processing.
 **/

import java.util. *;
import java.util.HashMap;


public class AStarState
{
    /** This is a reference to the map that the A* algorithm is navigating. **/
    private Map2D map;

    private Map<Location,Waypoint>OpenWayPoints = new HashMap<>();
    private Map<Location,Waypoint>ClosedWayPoints = new HashMap<>();


    /**
     * Initialize a new state object for the A* pathfinding algorithm to use.
     **/
    public AStarState(Map2D map)
    {
        if (map == null)
            throw new NullPointerException("map cannot be null");

        this.map = map;
    }

    /** Returns the map that the A* pathfinder is navigating. **/
    public Map2D getMap()
    {
        return map;
    }


    /**
     * This method scans through all open waypoints, and returns the waypoint
     * with the minimum total cost.  If there are no open waypoints, this method
     * returns <code>null</code>.
     **/
    /** minpoint를 설정하여 초기값을 NULL으로 잡아줌으로서 hashMap에 접근할 수 있는데 도움이 되게끔 하였다.
     *  그리고 최솟값 min을 통해 지속적으로 totalCost를 비교하며 Waypoint p1이 for문을 거치는 동안 최솟값을 가질 수 있게끔
     *  조건문에 비교연산을 걸었다.**/
    public Waypoint getMinOpenWaypoint()
    {
        Waypoint minpoint = null;

        float min = 0;

        if (OpenWayPoints.isEmpty() == true)
            return null;
        else {
            for (Waypoint p1 : OpenWayPoints.values()) {
                if (minpoint == null || min > p1.getTotalCost()) {
                    minpoint = p1;
                    min = p1.getTotalCost();
                }
            }
            return minpoint;
        }
    }

    /**
     * This method adds a waypoint to (or potentially updates a waypoint already
     * in) the "open waypoints" collection.  If there is not already an open
     * waypoint at the new waypoint's location then the new waypoint is simply
     * added to the collection.  However, if there is already a waypoint at the
     * new waypoint's location, the new waypoint replaces the old one ONLY
     * IF the new waypoint's "previous cost" value is less than the current
     * waypoint's "previous cost" value.
     **/
    /** GetPreviousCost는 waypoint class 안에 있으므로 OpenwayPoints가 아닌 waypoint형을 통해 접근해야한다.
     * 그리고 pp2를 통해 location을 받아 newWP와 cost를 비교하면서 기존 location값에 waypoint를 추가하였다.
     * newWP에 대한 waypoint가 없는 경우는 location을 가지고 확인하여 openwaypoints에 추가하는 형식으로 조건을 걸었다.
     *  **/
    public boolean addOpenWaypoint(Waypoint newWP)
    {
        Waypoint p2 = newWP;
        Waypoint pp2 = OpenWayPoints.get(p2.getLocation());

        if (OpenWayPoints.get(newWP.getLocation()) == null) {
            OpenWayPoints.put(newWP.getLocation(), newWP);
            return true;
        }
        else if (OpenWayPoints.containsValue(newWP.prevWaypoint))  {
            if ( newWP.getPreviousCost() < pp2.getPreviousCost() ) {
                OpenWayPoints.put(p2.getLocation(), newWP);
            }
            return true;
        }
        else
            return false;

        //if (getPrevious().Waypoint.loc != newWP.loc && getPrevious.waypoint != newWP.prevWaypoint)
        //return !(pp2.getLocation().equals(newWP.getLocation()));
    }


    /** Returns the current number of open waypoints. **/
    /** 경유지를 반환하는 것이 결국 openwaypoints의 element 개수를 구하는것과 같다고 생각할 수 있기 때문에 이의 사이즈를
     * 구하는 method를 찾아 리턴해주었다.**/
    public int numOpenWaypoints()
    {
        return OpenWayPoints.size();
    }


    /**
     * This method moves the waypoint at the specified location from the
     * open list to the closed list.
     **/
    /** hashmap의 collection의 기본 method인 remove, put의 원리를 이용하는데
     * 바로 remove를 하면 기존 값에 참조할 수 없으므로 lo에 선언을 해두고 remove를 진행하였다.
     * 그리고 이를 closewaypoint에 추가하였다.**/

    public void closeWaypoint(Location loc)
    {
        Location lo = loc;
        Waypoint p3 = OpenWayPoints.get(loc);

        OpenWayPoints.remove(loc);
        ClosedWayPoints.put(lo, p3);
    }

    /**
     * Returns true if the collection of closed waypoints contains a waypoint
     * for the specified location.
     **/
    /** 이 또한 hashmap의 기본 method로 key를 포함하는지 안하는지를 알 수 있는데
     * 지정된 위치가 나타나면 즉, 이에 대응하는 값이 존재하면으로 해석할 수 있기 때문에 containkey를 사용하였다. **/
    public boolean isLocationClosed(Location loc)
    {
        return ClosedWayPoints.containsKey("loc");
    }
}
