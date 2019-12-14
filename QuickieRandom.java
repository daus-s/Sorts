public class QuickieRandom
{
    public static void main(String[] args)
    {
        randomDoubles(16384);
    }
    public static void randomDoubles(int i)
    {
        for (int o = 0; o < i; ++o)
        {
            double d = 512 * Math.random() + 1;
            System.out.println(d);
        }
    }
}
