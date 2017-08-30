## Yahoo Wetter (XML/RSS-Feed)

![](../../images/YahooWeather.png)

- - -

Mittels Yahoo Weather kann das aktuelle Wetter und eine Vorhersage für einen Bestimmten Ort abgefragt werden.

**Links**

*   [Website](https://weather.yahoo.com/)
*   [API](https://developer.yahoo.com/weather/)
*   [Where On Earth ID (WOEID) Suche](http://zourbuth.com/tools/woeid/)

### Beispiel: Abfrage für Zürich 

Aufruf mittels curl

```xml
    curl http://query.yahooapis.com/v1/public/yql  \
           -d q="select * from weather.forecast where woeid=784794"    -d format=xml                        
```

```xml
<?xml version="1.0" encoding="UTF-8"?>
<query xmlns:yahoo="http://www.yahooapis.com/v1/base.rng" yahoo:count="1" yahoo:created="2016-07-22T13:17:05Z"
    yahoo:lang="en-US">
    <results>
        <channel>
            <yweather:units xmlns:yweather="http://xml.weather.yahoo.com/ns/rss/1.0" distance="mi" pressure="in"
                speed="mph" temperature="F" />
            <title>Yahoo! Weather - Zurich, ZH, CH</title>
            <link>http://us.rd.yahoo.com/dailynews/rss/weather/Country__Country/*https://weather.yahoo.com/country/state/city-784794/</link>
            <description>Yahoo! Weather for Zurich, ZH, CH</description>
            <language>en-us</language>
            <lastBuildDate>Fri, 22 Jul 2016 03:17 PM CEST</lastBuildDate>
            <ttl>60</ttl>
            <yweather:location xmlns:yweather="http://xml.weather.yahoo.com/ns/rss/1.0" city="Zurich"
                country="Switzerland" region=" ZH" />
            <yweather:wind xmlns:yweather="http://xml.weather.yahoo.com/ns/rss/1.0" chill="72" direction="150"
                speed="11" />
            <yweather:atmosphere xmlns:yweather="http://xml.weather.yahoo.com/ns/rss/1.0" humidity="72"
                pressure="957.0" rising="0" visibility="16.1" />
            <yweather:astronomy xmlns:yweather="http://xml.weather.yahoo.com/ns/rss/1.0" sunrise="5:54 am"
                sunset="9:10 pm" />
            <image>
                <title>Yahoo! Weather</title>
                <width>142</width>
                <height>18</height>
                <link>http://weather.yahoo.com</link>
                <url>http://l.yimg.com/a/i/brand/purplelogo//uh/us/news-wea.gif</url>
            </image>
            <item>
                <title>Conditions for Zurich, ZH, CH at 02:00 PM CEST</title>
                <geo:lat xmlns:geo="http://www.w3.org/2003/01/geo/wgs84_pos#">47.38427</geo:lat>
                <geo:long xmlns:geo="http://www.w3.org/2003/01/geo/wgs84_pos#">8.52959</geo:long>
                <link>http://us.rd.yahoo.com/dailynews/rss/weather/Country__Country/*https://weather.yahoo.com/country/state/city-784794/</link>
                <pubDate>Fri, 22 Jul 2016 02:00 PM CEST</pubDate>
                <yweather:condition xmlns:yweather="http://xml.weather.yahoo.com/ns/rss/1.0" code="39"
                    date="Fri, 22 Jul 2016 02:00 PM CEST" temp="72" text="Scattered Showers" />
                <yweather:forecast xmlns:yweather="http://xml.weather.yahoo.com/ns/rss/1.0" code="4" date="22 Jul 2016"
                    day="Fri" high="77" low="66" text="Thunderstorms" />
                <yweather:forecast xmlns:yweather="http://xml.weather.yahoo.com/ns/rss/1.0" code="47" date="23 Jul 2016"
                    day="Sat" high="76" low="64" text="Scattered Thunderstorms" />
                <yweather:forecast xmlns:yweather="http://xml.weather.yahoo.com/ns/rss/1.0" code="39" date="24 Jul 2016"
                    day="Sun" high="78" low="63" text="Scattered Showers" />
                <yweather:forecast xmlns:yweather="http://xml.weather.yahoo.com/ns/rss/1.0" code="47" date="25 Jul 2016"
                    day="Mon" high="77" low="64" text="Scattered Thunderstorms" />
                <yweather:forecast xmlns:yweather="http://xml.weather.yahoo.com/ns/rss/1.0" code="47" date="26 Jul 2016"
                    day="Tue" high="75" low="64" text="Scattered Thunderstorms" />
                <yweather:forecast xmlns:yweather="http://xml.weather.yahoo.com/ns/rss/1.0" code="4" date="27 Jul 2016"
                    day="Wed" high="75" low="61" text="Thunderstorms" />
                <yweather:forecast xmlns:yweather="http://xml.weather.yahoo.com/ns/rss/1.0" code="30" date="28 Jul 2016"
                    day="Thu" high="76" low="60" text="Partly Cloudy" />
                <yweather:forecast xmlns:yweather="http://xml.weather.yahoo.com/ns/rss/1.0" code="30" date="29 Jul 2016"
                    day="Fri" high="79" low="59" text="Partly Cloudy" />
                <yweather:forecast xmlns:yweather="http://xml.weather.yahoo.com/ns/rss/1.0" code="39" date="30 Jul 2016"
                    day="Sat" high="80" low="58" text="Scattered Showers" />
                <yweather:forecast xmlns:yweather="http://xml.weather.yahoo.com/ns/rss/1.0" code="30" date="31 Jul 2016"
                    day="Sun" high="78" low="59" text="Partly Cloudy" />
                <description></description>
                <guid isPermaLink="false" />
            </item>
        </channel>
    </results>
</query>
```

### Links

*  [mbed OS V2 Variante](https://developer.mbed.org/compiler/#import:/teams/smdiotkit2ch/code/YahooWeather/)
