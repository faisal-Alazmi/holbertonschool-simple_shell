static void write_num(int n)
{
    int x = n;
    char buf[12];
    int i = 0;

    if (x == 0)
    {
        buf[i++] = '0';
    }
    else
    {
        while (x > 0)
        {
            buf[i++] = (char)('0' + (x % 10));
            x /= 10;
        }
    }
    buf[i] = '\0';
    /* you can print it or do something else */
}
