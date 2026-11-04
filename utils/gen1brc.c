// gen1brc.c - generates a 1BRC measurements file and its expected output.
//
// Build:  gcc -O2 -o gen1brc gen1brc.c -lm
// Usage:  ./gen1brc [rows] [measurements_file] [expected_file] [seed]
// Defaults: 1000000000 measurements.txt expected.txt 42
//
// Input format  (one per line):  <station>;<temp with 1 decimal>
// Output format (one line):      {Station=min/mean/max, ...} sorted by name
// Temps are in [-99.9, 99.9]. Mean is rounded half-up to 1 decimal.
//
// This was AI generated

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    const char *name;
    double mean;
} Station;

static const Station STATIONS[] = {
    {"Abha", 18.0},
    {"Abidjan", 26.0},
    {"Abéché", 29.4},
    {"Accra", 26.4},
    {"Addis Ababa", 16.0},
    {"Adelaide", 17.3},
    {"Aden", 29.1},
    {"Ahvaz", 25.4},
    {"Albuquerque", 14.0},
    {"Alexandra", 11.0},
    {"Alexandria", 20.0},
    {"Algiers", 18.2},
    {"Alice Springs", 21.0},
    {"Almaty", 10.0},
    {"Amsterdam", 10.2},
    {"Anadyr", -6.9},
    {"Anchorage", 2.8},
    {"Andorra la Vella", 9.8},
    {"Ankara", 12.0},
    {"Antananarivo", 17.9},
    {"Antsiranana", 25.2},
    {"Arkhangelsk", 1.3},
    {"Ashgabat", 17.1},
    {"Asmara", 15.6},
    {"Assab", 30.5},
    {"Astana", 3.5},
    {"Athens", 19.2},
    {"Atlanta", 17.0},
    {"Auckland", 15.2},
    {"Austin", 20.7},
    {"Baghdad", 22.77},
    {"Baguio", 19.5},
    {"Baku", 15.1},
    {"Baltimore", 13.1},
    {"Bamako", 27.8},
    {"Bangkok", 28.6},
    {"Bangui", 26.0},
    {"Banjul", 26.0},
    {"Barcelona", 18.2},
    {"Bata", 25.1},
    {"Batumi", 14.0},
    {"Beijing", 12.9},
    {"Beirut", 20.9},
    {"Belgrade", 12.5},
    {"Belize City", 26.7},
    {"Benghazi", 19.9},
    {"Bergen", 7.7},
    {"Berlin", 10.3},
    {"Bilbao", 14.7},
    {"Birao", 26.5},
    {"Bishkek", 11.3},
    {"Bissau", 27.0},
    {"Blantyre", 22.2},
    {"Bloemfontein", 15.6},
    {"Boise", 11.4},
    {"Bordeaux", 14.2},
    {"Bosaso", 30.0},
    {"Boston", 10.9},
    {"Bouaké", 26.0},
    {"Bratislava", 10.5},
    {"Brazzaville", 25.0},
    {"Bridgetown", 27.0},
    {"Brisbane", 21.4},
    {"Brussels", 10.5},
    {"Bucharest", 10.8},
    {"Budapest", 11.3},
    {"Bujumbura", 23.8},
    {"Bulawayo", 18.9},
    {"Burnie", 13.1},
    {"Busan", 15.0},
    {"Cabo San Lucas", 23.9},
    {"Cairns", 25.0},
    {"Cairo", 21.4},
    {"Calgary", 4.4},
    {"Canberra", 13.1},
    {"Cape Town", 16.2},
    {"Casablanca", 17.7},
    {"Changsha", 17.4},
    {"Charlotte", 16.1},
    {"Chiang Mai", 25.8},
    {"Chicago", 9.8},
    {"Chihuahua", 18.6},
    {"Chișinău", 10.2},
    {"Chittagong", 25.9},
    {"Chongqing", 18.6},
    {"Christchurch", 12.2},
    {"City of San Marino", 11.8},
    {"Colombo", 27.4},
    {"Columbus", 11.7},
    {"Conakry", 26.4},
    {"Copenhagen", 9.1},
    {"Cotonou", 27.2},
    {"Cracow", 9.3},
    {"Da Lat", 17.9},
    {"Da Nang", 25.8},
    {"Dakar", 24.0},
    {"Dallas", 19.0},
    {"Damascus", 17.0},
    {"Dampier", 26.4},
    {"Dar es Salaam", 25.8},
    {"Darwin", 27.6},
    {"Denpasar", 23.7},
    {"Denver", 10.4},
    {"Detroit", 10.0},
    {"Dhaka", 25.9},
    {"Dikson", -11.1},
    {"Dili", 26.6},
    {"Djibouti", 29.9},
    {"Dodoma", 22.7},
    {"Dolisie", 24.0},
    {"Douala", 26.7},
    {"Dubai", 26.9},
    {"Dublin", 9.8},
    {"Dunedin", 11.1},
    {"Durban", 20.6},
    {"Dushanbe", 14.7},
    {"Edinburgh", 9.3},
    {"Edmonton", 4.2},
    {"El Paso", 18.1},
    {"Entebbe", 21.0},
    {"Erbil", 19.5},
    {"Erzurum", 5.1},
    {"Fairbanks", -2.3},
    {"Fianarantsoa", 17.9},
    {"Flores,  Petén", 26.4},
    {"Frankfurt", 10.6},
    {"Fresno", 17.9},
    {"Fukuoka", 17.0},
    {"Gabès", 19.5},
    {"Gaborone", 21.0},
    {"Gagnoa", 26.0},
    {"Gangtok", 15.2},
    {"Garissa", 29.3},
    {"Garoua", 28.3},
    {"George Town", 27.9},
    {"Ghanzi", 21.4},
    {"Gjoa Haven", -14.4},
    {"Guadalajara", 20.9},
    {"Guangzhou", 22.4},
    {"Guatemala City", 20.4},
    {"Halifax", 7.5},
    {"Hamburg", 9.7},
    {"Hamilton", 13.8},
    {"Hanga Roa", 20.5},
    {"Hanoi", 23.6},
    {"Harare", 18.4},
    {"Harbin", 5.0},
    {"Hargeisa", 21.7},
    {"Hat Yai", 27.0},
    {"Havana", 25.2},
    {"Helsinki", 5.9},
    {"Heraklion", 18.9},
    {"Hiroshima", 16.3},
    {"Ho Chi Minh City", 27.4},
    {"Hobart", 12.7},
    {"Hong Kong", 23.3},
    {"Honiara", 26.5},
    {"Honolulu", 25.4},
    {"Houston", 20.8},
    {"Ifrane", 11.4},
    {"Indianapolis", 11.8},
    {"Iqaluit", -9.3},
    {"Irkutsk", 1.0},
    {"Istanbul", 13.9},
    {"İzmir", 17.9},
    {"Jacksonville", 20.3},
    {"Jakarta", 26.7},
    {"Jayapura", 27.0},
    {"Jerusalem", 18.3},
    {"Johannesburg", 15.5},
    {"Jos", 22.8},
    {"Juba", 27.8},
    {"Kabul", 12.1},
    {"Kampala", 20.0},
    {"Kandi", 27.7},
    {"Kankan", 26.5},
    {"Kano", 26.4},
    {"Kansas City", 12.5},
    {"Karachi", 26.0},
    {"Karonga", 24.4},
    {"Kathmandu", 18.3},
    {"Khartoum", 29.9},
    {"Kingston", 27.4},
    {"Kinshasa", 25.3},
    {"Kolkata", 26.7},
    {"Kuala Lumpur", 27.3},
    {"Kumasi", 26.0},
    {"Kunming", 15.7},
    {"Kuopio", 3.4},
    {"Kuwait City", 25.7},
    {"Kyiv", 8.4},
    {"Kyoto", 15.8},
    {"La Ceiba", 26.2},
    {"La Paz", 23.7},
    {"Lagos", 26.8},
    {"Lahore", 24.3},
    {"Lake Havasu City", 23.7},
    {"Lake Tekapo", 8.7},
    {"Las Palmas de Gran Canaria", 21.2},
    {"Las Vegas", 20.3},
    {"Launceston", 13.1},
    {"Lhasa", 7.6},
    {"Libreville", 25.9},
    {"Lisbon", 17.5},
    {"Livingstone", 21.8},
    {"Ljubljana", 10.9},
    {"Lodwar", 29.3},
    {"Lomé", 26.9},
    {"London", 11.3},
    {"Los Angeles", 18.6},
    {"Louisville", 13.9},
    {"Luanda", 25.8},
    {"Lubumbashi", 20.8},
    {"Lusaka", 19.9},
    {"Luxembourg City", 9.3},
    {"Lviv", 7.8},
    {"Lyon", 12.5},
    {"Madrid", 15.0},
    {"Mahajanga", 26.3},
    {"Makassar", 26.7},
    {"Makurdi", 26.0},
    {"Malabo", 26.3},
    {"Malé", 28.0},
    {"Managua", 27.3},
    {"Manama", 26.5},
    {"Mandalay", 28.0},
    {"Mango", 28.1},
    {"Manila", 28.4},
    {"Maputo", 22.8},
    {"Marrakesh", 19.6},
    {"Marseille", 15.8},
    {"Maun", 22.4},
    {"Medan", 26.5},
    {"Mek'ele", 22.7},
    {"Melbourne", 15.1},
    {"Memphis", 17.2},
    {"Mexicali", 23.1},
    {"Mexico City", 17.5},
    {"Miami", 24.9},
    {"Milan", 13.0},
    {"Milwaukee", 8.9},
    {"Minneapolis", 7.8},
    {"Minsk", 6.7},
    {"Mogadishu", 27.1},
    {"Mombasa", 26.3},
    {"Monaco", 16.4},
    {"Moncton", 6.1},
    {"Monterrey", 22.3},
    {"Montreal", 6.8},
    {"Moscow", 5.8},
    {"Mumbai", 27.1},
    {"Murmansk", 0.6},
    {"Muscat", 28.0},
    {"Mzuzu", 17.7},
    {"N'Djamena", 28.3},
    {"Naha", 23.1},
    {"Nairobi", 17.8},
    {"Nakhon Ratchasima", 27.3},
    {"Napier", 14.6},
    {"Napoli", 15.9},
    {"Nashville", 15.4},
    {"Nassau", 24.6},
    {"Ndola", 20.3},
    {"New Delhi", 25.0},
    {"New Orleans", 20.7},
    {"New York City", 12.9},
    {"Ngaoundéré", 22.0},
    {"Niamey", 29.3},
    {"Nicosia", 19.7},
    {"Niigata", 13.9},
    {"Nouadhibou", 21.3},
    {"Nouakchott", 25.7},
    {"Novosibirsk", 1.7},
    {"Nuuk", -1.4},
    {"Odesa", 10.7},
    {"Odienné", 26.0},
    {"Oklahoma City", 15.9},
    {"Omaha", 10.6},
    {"Oranjestad", 28.1},
    {"Oslo", 5.7},
    {"Ottawa", 6.6},
    {"Ouagadougou", 28.3},
    {"Ouahigouya", 28.6},
    {"Ouarzazate", 18.9},
    {"Oulu", 2.7},
    {"Palembang", 27.3},
    {"Palermo", 18.5},
    {"Palm Springs", 24.5},
    {"Palmerston North", 13.2},
    {"Panama City", 28.0},
    {"Parakou", 26.8},
    {"Paris", 12.3},
    {"Perth", 18.7},
    {"Petropavlovsk-Kamchatsky", 1.9},
    {"Philadelphia", 13.2},
    {"Phnom Penh", 28.3},
    {"Phoenix", 23.9},
    {"Pittsburgh", 10.8},
    {"Podgorica", 15.3},
    {"Pointe-Noire", 26.1},
    {"Pontianak", 27.7},
    {"Port Moresby", 26.9},
    {"Port Sudan", 28.4},
    {"Port Vila", 24.3},
    {"Port-Gentil", 26.0},
    {"Portland (OR)", 12.4},
    {"Porto", 15.7},
    {"Prague", 8.4},
    {"Praia", 24.4},
    {"Pretoria", 18.2},
    {"Pyongyang", 10.8},
    {"Rabat", 17.2},
    {"Rangpur", 24.4},
    {"Reggane", 28.3},
    {"Reykjavík", 4.3},
    {"Riga", 6.2},
    {"Riyadh", 26.0},
    {"Rome", 15.2},
    {"Roseau", 26.2},
    {"Rostov-on-Don", 9.9},
    {"Sacramento", 16.3},
    {"Saint Petersburg", 5.8},
    {"Saint-Pierre", 5.7},
    {"Salt Lake City", 11.6},
    {"San Antonio", 20.8},
    {"San Diego", 17.8},
    {"San Francisco", 14.6},
    {"San Jose", 16.4},
    {"San José", 22.6},
    {"San Juan", 27.2},
    {"San Salvador", 23.1},
    {"Sana'a", 20.0},
    {"Santo Domingo", 25.9},
    {"Sapporo", 8.9},
    {"Sarajevo", 10.1},
    {"Saskatoon", 3.3},
    {"Seattle", 11.3},
    {"Ségou", 28.0},
    {"Seoul", 12.5},
    {"Seville", 19.2},
    {"Shanghai", 16.7},
    {"Singapore", 27.0},
    {"Skopje", 12.4},
    {"Sochi", 14.2},
    {"Sofia", 10.6},
    {"Sokoto", 28.0},
    {"Split", 16.1},
    {"St. John's", 5.0},
    {"St. Louis", 13.9},
    {"Stockholm", 6.6},
    {"Surabaya", 27.1},
    {"Suva", 25.6},
    {"Suwałki", 7.2},
    {"Sydney", 17.7},
    {"Tabora", 23.0},
    {"Tabriz", 12.6},
    {"Taipei", 23.0},
    {"Tallinn", 6.4},
    {"Tamale", 27.9},
    {"Tamanrasset", 21.7},
    {"Tampa", 22.9},
    {"Tashkent", 14.8},
    {"Tauranga", 14.8},
    {"Tbilisi", 12.9},
    {"Tegucigalpa", 21.7},
    {"Tehran", 17.0},
    {"Tel Aviv", 20.0},
    {"Thessaloniki", 16.0},
    {"Thiès", 24.0},
    {"Tijuana", 17.8},
    {"Timbuktu", 28.0},
    {"Tirana", 15.2},
    {"Toamasina", 23.4},
    {"Tokyo", 15.4},
    {"Toliara", 24.1},
    {"Toluca", 12.4},
    {"Toronto", 9.4},
    {"Tripoli", 20.0},
    {"Tromsø", 2.9},
    {"Tucson", 20.9},
    {"Tunis", 18.4},
    {"Ulaanbaatar", -0.4},
    {"Upington", 20.4},
    {"Ürümqi", 7.4},
    {"Vaduz", 10.1},
    {"Valencia", 18.3},
    {"Valletta", 18.8},
    {"Vancouver", 10.4},
    {"Veracruz", 25.4},
    {"Vienna", 10.4},
    {"Vientiane", 25.9},
    {"Villahermosa", 27.1},
    {"Vilnius", 6.0},
    {"Virginia Beach", 15.8},
    {"Vladivostok", 4.9},
    {"Warsaw", 8.5},
    {"Washington, D.C.", 14.6},
    {"Wau", 27.8},
    {"Wellington", 12.9},
    {"Whitehorse", -0.1},
    {"Wichita", 13.9},
    {"Willemstad", 28.0},
    {"Winnipeg", 3.0},
    {"Wrocław", 9.6},
    {"Xi'an", 14.1},
    {"Yakutsk", -8.8},
    {"Yangon", 27.5},
    {"Yaoundé", 23.8},
    {"Yellowknife", -4.3},
    {"Yerevan", 12.4},
    {"Yinchuan", 9.0},
    {"Zagreb", 10.7},
    {"Zanzibar City", 26.0},
    {"Zürich", 9.3},
};
#define NSTATIONS (sizeof(STATIONS) / sizeof(STATIONS[0]))

typedef struct
{
    int min, max;
    int64_t sum, count;
} Agg;

// xoshiro256** PRNG
static uint64_t s[4];
static inline uint64_t rotl(uint64_t x, int k) { return (x << k) | (x >> (64 - k)); }
static inline uint64_t next_u64(void)
{
    uint64_t r = rotl(s[1] * 5, 7) * 9, t = s[1] << 17;
    s[2] ^= s[0];
    s[3] ^= s[1];
    s[1] ^= s[2];
    s[0] ^= s[3];
    s[2] ^= t;
    s[3] = rotl(s[3], 45);
    return r;
}
static inline double next_unit(void) { return (next_u64() >> 11) * 0x1.0p-53; }
static void seed_rng(uint64_t seed)
{
    for (int i = 0; i < 4; i++)
    { // splitmix64
        uint64_t z = (seed += 0x9E3779B97F4A7C15ULL);
        z = (z ^ (z >> 30)) * 0xBF58476D1CE4E5B9ULL;
        z = (z ^ (z >> 27)) * 0x94D049BB133111EBULL;
        s[i] = z ^ (z >> 31);
    }
}

// Normal(0, 1) via Box-Muller, caching the second value
static inline double next_gauss(void)
{
    static int have = 0;
    static double spare;
    if (have)
    {
        have = 0;
        return spare;
    }
    double u, v, r;
    do
    {
        u = 2 * next_unit() - 1;
        v = 2 * next_unit() - 1;
        r = u * u + v * v;
    } while (r >= 1 || r == 0);
    double f = sqrt(-2 * log(r) / r);
    spare = v * f;
    have = 1;
    return u * f;
}

// Writes tenths as "-12.3"; returns bytes written
static inline int put_tenths(char *p, long t)
{
    char *start = p;
    if (t < 0)
    {
        *p++ = '-';
        t = -t;
    }
    long ip = t / 10;
    if (ip >= 10)
        *p++ = '0' + ip / 10;
    *p++ = '0' + ip % 10;
    *p++ = '.';
    *p++ = '0' + t % 10;
    return (int)(p - start);
}

static int cmp_idx(const void *a, const void *b)
{
    return strcmp(STATIONS[*(const int *)a].name, STATIONS[*(const int *)b].name);
}

int main(int argc, char **argv)
{
    long long rows = argc > 1 ? atoll(argv[1]) : 1000000000LL;
    const char *mpath = argc > 2 ? argv[2] : "measurements.txt";
    const char *epath = argc > 3 ? argv[3] : "expected.txt";
    uint64_t seed = argc > 4 ? strtoull(argv[4], NULL, 10) : 42;
    seed_rng(seed);

    size_t nlen[NSTATIONS];
    Agg agg[NSTATIONS];
    for (size_t i = 0; i < NSTATIONS; i++)
    {
        nlen[i] = strlen(STATIONS[i].name);
        agg[i] = (Agg){1000, -1000, 0, 0};
    }

    FILE *out = fopen(mpath, "wb");
    if (!out)
    {
        perror(mpath);
        return 1;
    }

    enum
    {
        BUF = 1 << 22
    };
    static char buf[BUF + 256];
    size_t pos = 0;

    for (long long i = 0; i < rows; i++)
    {
        int st = (int)(next_u64() % NSTATIONS);
        long t = lround((STATIONS[st].mean + 10.0 * next_gauss()) * 10.0);
        if (t > 999)
            t = 999;
        if (t < -999)
            t = -999;

        memcpy(buf + pos, STATIONS[st].name, nlen[st]);
        pos += nlen[st];
        buf[pos++] = ';';
        pos += put_tenths(buf + pos, t);
        buf[pos++] = '\n';
        if (pos >= BUF)
        {
            fwrite(buf, 1, pos, out);
            pos = 0;
        }

        Agg *a = &agg[st];
        if (t < a->min)
            a->min = (int)t;
        if (t > a->max)
            a->max = (int)t;
        a->sum += t;
        a->count++;

        if ((i & 0x3FFFFFF) == 0 && i)
            fprintf(stderr, "\r%lld / %lld", i, rows);
    }
    fwrite(buf, 1, pos, out);
    fclose(out);
    fprintf(stderr, "\rwrote %lld rows to %s\n", rows, mpath);

    int order[NSTATIONS], n = 0;
    for (size_t i = 0; i < NSTATIONS; i++)
        if (agg[i].count)
            order[n++] = (int)i;
    qsort(order, n, sizeof(int), cmp_idx);

    FILE *exp = fopen(epath, "wb");
    if (!exp)
    {
        perror(epath);
        return 1;
    }
    char tmp[16];
    fputc('{', exp);
    for (int k = 0; k < n; k++)
    {
        Agg *a = &agg[order[k]];
        long mean = (long)floor((double)a->sum / (double)a->count + 0.5); // round half up
        if (k)
            fputs(", ", exp);
        fputs(STATIONS[order[k]].name, exp);
        fputc('=', exp);
        fwrite(tmp, 1, put_tenths(tmp, a->min), exp);
        fputc('/', exp);
        fwrite(tmp, 1, put_tenths(tmp, mean), exp);
        fputc('/', exp);
        fwrite(tmp, 1, put_tenths(tmp, a->max), exp);
    }
    fputs("}\n", exp);
    fclose(exp);
    fprintf(stderr, "wrote expected results for %d stations to %s\n", n, epath);
    return 0;
}