/**
 * This class represents a specific location in a 2D map.  Coordinates are
 * integer values.
 **/


public class Location
{
    /** X coordinate of this location. **/
    public int xCoord;

    /** Y coordinate of this location. **/
    public int yCoord;


    /** Creates a new location with the specified integer coordinates. **/
    public Location(int x, int y)
    {
        xCoord = x;
        yCoord = y;
    }

    /** Creates a new location with coordinates (0, 0). **/
    public Location()
    {
        this(0, 0);
    }

    /** object o와 Location간의 형을 비교해주고 형은 Location이기 때문에 각각의 x,y Coordinate에 접근하여
     * 비교연산을 해줬습니다.
     * 그리고 hashCode는 this.hashCode가 아닌 x,y Coord으로 연산을 해줘서 적당하게 값이 배분될 수 있도록 하였습니다.**/
    public boolean equals(Object o) {
        if (o instanceof Location) {
            Location other = (Location) o;

            if (this.xCoord == other.xCoord && this.yCoord == other.yCoord)
                return true;
            else
                return false;
        }
        else
            return false;
    }

    public int hashCode() {
        final int num = 16;
        int result = 17;

        result = 37 * result + this.xCoord + this.yCoord;

        return result;
    }

}
