# phil
# phil
void precise_usleep(long time_ms)
{
    long start;
    long now;

    start = get_time();
    while (1)
    {
        now = get_time();
        if ((now - start) >= time_ms)
            break;
        usleep(500); // dors très peu pour éviter de bloquer le CPU
    }
}
