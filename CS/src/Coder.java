public class Coder
{

    public Coder()
    {
    }

    public static int encrypt(int key, int p)
    {
        return code(key, p);
    }

    public static int decrypt(int key, int c)
    {
        return code(key, c);
    }

    public static int code(int key, int pc)
    {
        seed = key;
        return dice(0x10000) ^ pc;
    }

    public static int dice(int n)
    {
        int hi = seed / 0x1f31d;
        int lo = seed % 0x1f31d;
        int t = 16807 * lo - 2836 * hi;
        seed = t <= 0 ? t + 0x7fffffff : t;
        return seed % n;
    }

    private static int seed;
    private static final int a = 16807;
    private static final int m = 0x7fffffff;
    private static final int q = 0x1f31d;
    private static final int r = 2836;
}